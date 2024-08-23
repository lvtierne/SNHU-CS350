/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== gpiointerrupt.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* Morse code definitions */
#define DOT_DURATION 500000 // 500 ms
#define DASH_DURATION 1500000 // 1500 ms
#define BETWEEN_PARTS 500000 // 500 ms
#define BETWEEN_LETTERS 1500000 // 3 * 500 ms
#define BETWEEN_WORDS 3500000 // 7 * 500 ms

/* Morse code for SOS and OK */
const char* sos = "...---...";
const char* ok = "---.-.-";

volatile bool toggleMessage = false;
volatile bool currentMessageIsSOS = true;
volatile bool messageComplete = true;

/*
 *  ======== gpioButtonFxn0 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_0.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void gpioButtonFxn0(uint_least8_t index)
{
    toggleMessage = true;
}

/*
 *  ======== gpioButtonFxn1 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_1.
 *  This may not be used for all boards.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void gpioButtonFxn1(uint_least8_t index)
{
    toggleMessage = true;
}

/*
 *  ======== timerCallback ========
 *  Callback function for the Timer interrupt.
 */
void timerCallback(Timer_Handle myHandle, int_fast16_t status)
{
    static const char* message;
    static int state = 0;
    static int subState = 0;
    static int delay = 0;

    if (messageComplete) {
        if (toggleMessage) {
            currentMessageIsSOS = !currentMessageIsSOS;
            toggleMessage = false;
        }
        message = currentMessageIsSOS ? sos : ok;
        messageComplete = false;
        state = 0;
        subState = 0;
        delay = 0;
    }

    if (delay > 0) {
        delay--;
        return;
    }

    char currentSymbol = message[state];
    switch (subState) {
        case 0: // Symbol start
            if (currentSymbol == '.') {
                GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
                delay = DOT_DURATION / 500000;
                subState = 1;
            } else if (currentSymbol == '-') {
                GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_ON);
                delay = DASH_DURATION / 500000;
                subState = 1;
            } else { // Inter-letter or inter-word space
                subState = 2;
                delay = (currentSymbol == ' ') ? BETWEEN_WORDS / 500000 : BETWEEN_LETTERS / 500000;
            }
            break;
        case 1: // Symbol end
            GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
            GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF);
            delay = BETWEEN_PARTS / 500000;
            subState = 2;
            break;
        case 2: // Between parts
            state++;
            if (message[state] == '\0') {
                state = 0;
                messageComplete = true;
                delay = BETWEEN_WORDS / 500000;
            }
            subState = 0;
            break;
    }
}

/*
 *  ======== initTimer ========
 *  Initialize the Timer.
 */
void initTimer(void)
{
    Timer_Handle timer0;
    Timer_Params params;

    Timer_init();
    Timer_Params_init(&params);
    params.period = 500000; // 500,000 us (500 ms)
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;

    timer0 = Timer_open(CONFIG_TIMER_0, &params);
    if (timer0 == NULL) {
        /* Failed to initialized timer */
        while (1) {}
    }
    if (Timer_start(timer0) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        while (1) {}
    }
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Call driver init functions */
    GPIO_init();

    /* Configure the LED and button pins */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_LED_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    /* Turn off LEDs */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
    GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF);

    /* Install Button callback */
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioButtonFxn0);
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

    /* Enable interrupts for button 1 if available */
    if (CONFIG_GPIO_BUTTON_0 != CONFIG_GPIO_BUTTON_1)
    {
        GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
        GPIO_setCallback(CONFIG_GPIO_BUTTON_1, gpioButtonFxn1);
        GPIO_enableInt(CONFIG_GPIO_BUTTON_1);
    }

    /* Initialize the Timer */
    initTimer();

    return (NULL);
}
