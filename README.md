# SNHU-CS350
Emerging Systems Architecture & Tech 2024

## Module 8 Journal

### Milestone Three Artifact

**Artifact Overview:**

In Milestone Three, I developed a project using the TI CC3220x LAUNCHXL to implement a Morse code message display via LEDs. This involved creating a synchronous state machine to manage LED blinking patterns, integrating timer and interrupt functionalities, and using TI Code Composer Studio (CCS) for development and debugging.

**Project Goals:**

- Design a state machine to control LED blinking in Morse code.
- Implement timer-based state machine management.
- Use interrupts to detect button presses and change the Morse code message.
- Develop and submit a state machine diagram created with draw.io.

**Files Submitted:**

1. **Zipped Workspace:** Contains all project files and source code.
2. **Video Demonstration:** A 1-minute video showing the LEDs blinking Morse code and demonstrating button functionality.
3. **Lab Questions Document:** Answers to the questions from the Milestone Three Timer Interrupt Lab Guide.
4. **State Machine Diagram:** PDF of the state machine diagram created with draw.io.

**Project Reflection:**

1. **Summary of the Project:**
   - The goal was to create a system on the TI CC3220x LAUNCHXL that uses LEDs to display Morse code and changes the pattern based on button presses. The project involved using CCS for coding, compiling, and debugging.

2. **What Went Well:**
   - The state machine was successfully implemented, and the LEDs accurately displayed Morse code patterns.
   - Timer and interrupt functionalities were effectively integrated.
   - Comprehensive state machine documentation was created.

3. **Areas for Improvement:**
   - Enhanced error handling for timer and interrupt code.
   - Expanded documentation with more detailed state transition explanations.

4. **Tools and Resources Added:**
   - Gained hands-on experience with CCS and hardware debugging.
   - Used draw.io for creating technical diagrams.

5. **Transferable Skills:**
   - Skills in state machine design, interrupt handling, and hardware interfacing are applicable to other embedded systems projects.
   - Experience with CCS and embedded hardware will benefit future coursework and projects.

6. **Maintainability and Adaptability:**
   - The code is modular, well-commented, and adaptable for different messages or hardware setups.
   - Documentation and code structure follow best practices for maintainability and readability.

---

### Milestone Two Artifact

**Artifact Overview:**

In Milestone Two, I used TI Code Composer Studio (CCS) to program the TI CC3220x LAUNCHXL to control an LED based on serial input from the console. This project involved creating a state machine to manage LED control with minimal RAM usage and integrating UART and GPIO functionalities.

**Project Goals:**

- Design a state machine to control an LED based on UART input.
- Implement UART character reading without buffering.
- Develop and submit a state machine diagram created with draw.io.

**Files Submitted:**

1. **Zipped Workspace:** Contains all project files and source code.
2. **Video Demonstration:** A 10-second video showing the LED control in response to serial input (ON/OFF commands).
3. **Lab Questions Document:** Answers to the questions from the Milestone Two UART GPIO Lab Guide.
4. **State Machine Diagram:** PDF of the state machine diagram created with draw.io.

**Project Reflection:**

1. **Summary of the Project:**
   - The objective was to control the red LED on the TI CC3220x LAUNCHXL based on user input from the console. The state machine was designed to handle commands like ON and OFF using only one byte of RAM.

2. **What Went Well:**
   - Successfully implemented UART communication and LED control using a state machine.
   - Effective use of GPIO for LED management with minimal RAM usage.

3. **Areas for Improvement:**
   - Improved UART input handling with more robust error checking.
   - Enhanced state machine documentation with clearer explanations.

4. **Tools and Resources Added:**
   - Gained practical experience with UART and GPIO management.
   - Used draw.io for creating and documenting the state machine.

5. **Transferable Skills:**
   - Proficiency in UART communication and GPIO control is useful for various embedded systems applications.
   - Skills in state machine design and minimal resource management are applicable to other projects.

6. **Maintainability and Adaptability:**
   - Code is designed to be modular and easily adapted for different commands or hardware configurations.
   - Documentation follows best practices for clarity and ease of maintenance.

---

Feel free to explore the files and documentation in the repository to understand the project in more detail.
