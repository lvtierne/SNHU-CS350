# SNHU-CS350
Emerging Sys Arch &amp; Tech 2024 Zybook Help!
## 1.8 RIMS implicitly defined I/O variables: Participation Activities

### 1.8.1: RIMS B outputs and A inputs.
Write a C program in RIMS that repeatedly executes: B = 7. Note that outputs B2, B1, and B0 become 1s, because 7 is 00000111 in binary (note that 7 appears under the output pins in RIMS). Next, set the input switches such that A3=1, A2=0, A1=0, and A0=1, with the other inputs 0, and note that 9 appears below RIMS' input pins (because 00001001 is 9 in binary).
```c
#include "RIMS.h"
void main() {
    unsigned char input_state = 0x9; // Hexadecimal representation of input A3=1, A2=0, A1=0, A0=1 (9 in decimal)
    
    while (1) {
        B = 7; // Set B to 7 repeatedly
        
        // Note: Inputs A should not be written to directly in RIMS simulations
    }
}
```
### 1.8.2: Set RIMS B output to A plus 1.
Write and execute a C program for RIMS that sets B equal to A plus 1.
```c
#include "RIMS.h"
void main() {
    while (1) {
        B = A + 1; // Set B equal to A plus 1
        
        // Note: RIMS typically handles input A and output B through simulation
    }
}
```
### 1.8.3: RIMS B output overflow.
Write a C program for RIMS that sets B = 300. Note that the value actually output on B is not 300, because an unsigned char has a range of 0 to 255.
```c
#include "RIMS.h"
void main() {
    while (1) {
        B = 300 % 256; // Set B to 300, but wrap around using modulus operation
        
        // Note: RIMS typically handles output B through simulation
    }
}
```
### 1.8.4: Airbag system.
A car has a sensor that sets A to the passenger's weight (e.g., if the passenger weighs 130 pounds, A7..A0 will equal 10000010). Write a RIM C program that enables the car's airbag system (B0=1) if the passenger's weight is 105 pounds or greater. Also, illuminate an "Airbag off" light (by setting B1=1) if weight > 5 pounds but weight < 105 pounds.
```c
#include "RIMS.h"
void main() {
    while (1) {
        // Read the passenger's weight from input A (A7..A0)
        unsigned char weight = A;
        
        // Check conditions based on the passenger's weight
        if (weight >= 105) {
            B0 = 1; // Enable airbag system (B0=1)
            B1 = 0; // Turn off "Airbag off" light (B1=0)
        } else if (weight > 5 && weight < 105) {
            B0 = 0; // Disable airbag system (B0=0)
            B1 = 1; // Illuminate "Airbag off" light (B1=1)
        } else {
            B0 = 0; // Disable airbag system (B0=0)
            B1 = 0; // Turn off "Airbag off" light (B1=0)
        }
        
        // Delay or other operations as needed
    }
}
```


## 1.10 Bitwise operators
### 1.10.5: Setting RIMS output.
Write a while loop containing a single C statement for RIMS that sets B to A except that B1 and B0 are always 0. Hint: Use bitwise AND. Test in RIMS.
```c
#include "RIMS.h"

void main() {
    while (1) {
        B = A & 0xFC;  // 0xFC = 1111 1100 in binary, clears B1 and B0
    }
}
```

## 1.11 Shift operators
### 1.11.2: RIMS I/O with shifting.
Write a single C statement for RIMS that sets B3-B0 to A5-A2 and sets other output bits to 0s. Test in RIMS.
```c
#include "RIMS.h"

void main() {
    while (1) {
        B = (A & 0x3C) >> 2;  // Mask and shift A5-A2 to B3-B0
    }
}
```

### 1.11.3: Parking lot sensors.
A parking lot has eight spaces, each with a sensor connected to RIM input A7, A6, ..., or A0. A RIM input being 1 means a car is detected in the corresponding space. Spaces A7 and A6 are reserved handicapped parking. Write a RIM C program that: (1) Sets B0 to 1 if both handicapped spaces are full, and (2) Sets B7..B5 equal to the number of available non-handicapped spaces.
```c
#include "RIMS.h"

void main() {
    unsigned char availableSpaces;
    unsigned char i;

    while (1) {
        // Check if both handicapped spaces (A7 and A6) are full
        if ((A & 0xC0) == 0xC0) { // 0xC0 is 11000000 in binary
            B = B | 0x01; // Set B0 to 1 if both handicapped spaces are full
        } else {
            B = B & 0xFE; // Set B0 to 0 otherwise
        }

        // Count the number of available non-handicapped spaces (A5 to A0)
        availableSpaces = 0;
        for (i = 0; i < 6; i++) {
            if (!(A & (1 << i))) { // Check if the space i (A[i]) is available
                availableSpaces++;
            }
        }
        
        // Set B7..B5 to the number of available non-handicapped spaces
        B = (B & 0x1F) | (availableSpaces << 5); // Clear B7..B5 and set them to availableSpaces count
    }
```
#### Explanation:
- Variable Declarations:
  - Moved unsigned char availableSpaces; and unsigned char i; outside of the while loop to ensure they are properly declared before use.
- Loop Structure:
  - The while (1) loop ensures the program runs continuously.
- Bitwise Operations:
  - Corrected the bitwise operations to set and clear bits based on the conditions described.
- This should now compile without syntax errors in the RIMS environment. Ensure you test this updated version to verify its functionality. If issues persist, double-check the specific compiler or simulator requirements for the RIMS system you are using.
 

### 1.11.1: RIMS bit manipulation.
1.) Set B2 to 1 if A6 or A4 are 1
```c
#include "RIMS.h"

int main() {
    while (1) {
        char A6 = (A >> 6) & 0x01;  // Read A6 (bit 6 of A)
        char A4 = (A >> 4) & 0x01;  // Read A4 (bit 4 of A)

        // Set B2 based on A6 or A4
        if (A6 || A4) {
            B = B | (1 << 2);  // Set B2 to 1 if A6 or A4 is 1
        } else {
            B = B & ~(1 << 2); // Set B2 to 0 otherwise
        }
    }

    return 0;
}
```
<p align="center">
  <img src="https://github.com/lvtierne/SNHU-CS350/assets/136281319/ada584a9-d355-4e4c-8d1e-beb2022f60fb" alt="Image 1" style="border: 2px solid #000; width: 50%; margin: 10px;">
</p>

2.) Set B6 to 1 if both A1 and A7 are 1. Or set B6 to 1 if A4 is 1
```c
#include "RIMS.h"

int main() {
    while (1) {
        char A1 = (A >> 1) & 0x01;  // Read A1 (bit 1 of A)
        char A4 = (A >> 4) & 0x01;  // Read A4 (bit 4 of A)
        char A7 = (A >> 7) & 0x01;  // Read A7 (bit 7 of A)

        // Set B6 based on the conditions
        if ((A1 && A7) || A4) {
            B = B | (1 << 6);  // Set B6 to 1 if both A1 and A7 are 1, or if A4 is 1
        } else {
            B = B & ~(1 << 6); // Set B6 to 0 otherwise
        }
    }

    return 0;
}
```
<p align="center">
  <img src="https://github.com/lvtierne/SNHU-CS350/assets/136281319/8087cea5-0a39-470f-ae55-b5023504cc87" alt="Image 2" style="border: 2px solid #000; width: 50%; margin: 10px;">
</p>

3.) Set B's upper nibble to A's upper nibble, and B's lower nibble to 14
```c
#include "RIMS.h"

int main() {
    while (1) {
        char upperNibble = A & 0xF0; // Extract the upper nibble from A (bits 7-4)
        char lowerNibble = 0x0E;     // 14 in hexadecimal (binary: 00001110)

        B = upperNibble | lowerNibble; // Combine the upper nibble of A with 14

    }
    return 0;
}
```
<p align="center">
  <img src="https://github.com/lvtierne/SNHU-CS350/assets/136281319/aee88d19-4cb2-456d-a759-e696a48853fa" alt="Image 3" style="border: 2px solid #000; width: 50%; margin: 10px;">
</p>

4.) Set B's upper nibble to A's lower nibble, and B's lower nibble to 4
```c
#include "RIMS.h"

int main() {
   while(1) {
      char lowerNibbleOfA = A & 0x0F; // Extract the lower nibble from A (bits 3-0)
      char upperNibble = lowerNibbleOfA << 4; // Shift the lower nibble to the upper nibble position
      char lowerNibble = 0x04; // 4 in hexadecimal (binary: 00000100)

      B = upperNibble | lowerNibble; // Combine the upper nibble from A's lower nibble with 4
   }
   return 0;
}
```
<p align="center">
  <img src="https://github.com/lvtierne/SNHU-CS350/assets/136281319/5222d337-396d-4b12-afac-4bbfca6b3a2f" alt="Image 4" style="border: 2px solid #000; width: 50%; margin: 10px;">
</p>


## 1.12 Bit access functions
### 1.12.4: Consecutive 1s.
Write a program that sets B0 = 1 if a sequence of three consecutive 1s appears anywhere on input A (e.g., 11100000 and 10111101 have such sequences, while 11001100 does not), using a C for loop and the GetBit() function.

Note: Inlining is currently only supported in the Windows-based RIMS. To use the above GetBit function in the web-based RIMS, remove: inline
```c
#include "RIMS.h"
int main() {
    char foundSequence = 0;
    char i;

    while (1) {
        // Check for three consecutive 1s in bits A7 to A0
        for (i = 0; i <= 5; i++) {
            if ((A & (1 << i)) && (A & (1 << (i+1))) && (A & (1 << (i+2)))) {
                foundSequence = 1;
                break; // Exit the loop if sequence is found
            }
        }

        B0 = foundSequence; // Set B0 to 1 if sequence is found, otherwise 0
    }

    return 0;
}
```






