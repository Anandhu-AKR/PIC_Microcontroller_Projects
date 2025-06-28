PIC18F4580 LED Project
This project utilizes a PIC18F4580 microcontroller to control 8 LEDs (connected to PORTD, RD0-RD7) via 5 tactile buttons (connected to PORTB, RB0-RB4 with pull-up resistors). Each button press initiates a distinct LED illumination pattern. The repository includes comprehensive instructions for simulating the project using Proteus Design Suite and compiling the firmware with MPLAB IDE.

Project Overview
Microcontroller: PIC18F4580

Inputs: 5 push buttons connected to PORTB pins RB0-RB4 (configured with pull-up resistors).

Outputs: 8 LEDs connected to PORTD pins RD0-RD7 (with current-limiting resistors).

LED Patterns:

RB0: Sequential lighting of LEDs from RD0 to RD7.

RB1: All LEDs blink synchronously.

RB2: Alternating pattern between 0xAA (10101010) and 0x55 (01010101).

RB3: Alternating pattern between 0xCC (11001100) and 0x33 (00110011).

RB4: Diagonal lighting pattern (0x81, 0x42, 0x24, 0x18).

Files
led_patterns.c: The embedded C source code for the PIC18F4580 microcontroller.

schematic.png: The circuit schematic diagram (visual representation of component connections).

Schematic Diagram
Below is the circuit schematic for this project. This diagram illustrates the connections between the PIC18F4580 microcontroller, the push buttons, and the LEDs.

Note: This is a placeholder image. Please replace schematic.png in your project directory with the actual circuit diagram.

Step-by-Step Guide to Build and Simulate the Project
Prerequisites
Before proceeding, ensure you have the following software installed:

MPLAB X IDE with the XC8 Compiler (downloadable from Microchip's official website).

Proteus Design Suite (downloadable from Labcenter Electronics' official website).

A fundamental understanding of microcontroller programming and circuit simulation is recommended.

Step 1: Set Up the Project in MPLAB X IDE
Install MPLAB X IDE and XC8 Compiler:
If not already installed, download and install MPLAB X IDE and the XC8 compiler from the Microchip website.

Create a New Project:

Open MPLAB X IDE.

Navigate to File > New Project.

Select Microchip Embedded > Standalone Project, then click Next.

Choose PIC18F4580 as the device, then click Next.

Select XC8 as the compiler, then click Next.

Provide a suitable project name (e.g., LED_Patterns) and specify a location for your project files. Click Finish.

Add the Source Code:

In the Projects window (typically on the left), right-click the Source Files folder.

Select New > C Main File.

Name the file led_patterns.c and click Finish.

Copy and paste the following C code into the newly created led_patterns.c file:

#include <pic18.h>

// Configuration bits for PIC18F4580
#pragma config OSC = HS         // High Speed Oscillator
#pragma config WDT = OFF        // Watchdog Timer disabled
#pragma config LVP = OFF        // Low-Voltage Programming disabled
#pragma config PWRT = ON        // Power-up Timer enabled

// Delay function
void delay() {
    // Simple delay loop for basic timing. Adjust values for different delays.
    // Approx. 500 * 500 = 250,000 instruction cycles.
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            // Do nothing
        }
    }
}

// Pattern 1: Sequential lighting (RD0 to RD7)
void pattern1() {
    for (int i = 0; i < 8; i++) {
        LATD = (1 << i); // Turn on one LED at a time
        delay();
    }
    LATD = 0x00; // Turn off all LEDs after sequence
}

// Pattern 2: Blink all LEDs
void pattern2() {
    LATD = 0xFF; // All LEDs ON
    delay();
    LATD = 0x00; // All LEDs OFF
    delay();
    LATD = 0xFF; // All LEDs ON again
    delay();
    LATD = 0x00; // Turn off all LEDs after sequence
}

// Pattern 3: Alternating 0xAA/0x55 pattern
void pattern3() {
    LATD = 0xAA; // 10101010 (LEDs D7,D5,D3,D1 ON)
    delay();
    LATD = 0x55; // 01010101 (LEDs D6,D4,D2,D0 ON)
    delay();
    LATD = 0xAA;
    delay();
    LATD = 0x00; // Turn off all LEDs after sequence
}

// Pattern 4: Alternating 0xCC/0x33 pattern
void pattern4() {
    LATD = 0xCC; // 11001100 (LEDs D7,D6,D3,D2 ON)
    delay();
    LATD = 0x33; // 00110011 (LEDs D5,D4,D1,D0 ON)
    delay();
    LATD = 0xCC;
    delay();
    LATD = 0x00; // Turn off all LEDs after sequence
}

// Pattern 5: Diagonal pattern (0x81, 0x42, 0x24, 0x18)
void pattern5() {
    LATD = 0x81; // 10000001 (RD7, RD0 ON)
    delay();
    LATD = 0x42; // 01000010 (RD6, RD1 ON)
    delay();
    LATD = 0x24; // 00100100 (RD5, RD2 ON)
    delay();
    LATD = 0x18; // 00011000 (RD4, RD3 ON)
    delay();
    LATD = 0x00; // Turn off all LEDs after sequence
}

void main(void) {
    // Configure TRISB for PORTB (RB0-RB4 as inputs for buttons)
    TRISB = 0xFF; // All PORTB pins as input
    // Configure TRISD for PORTD (RD0-RD7 as outputs for LEDs)
    TRISD = 0x00; // All PORTD pins as output
    // Configure ADCON1 to set all AN pins as digital I/O (disable analog functions)
    ADCON1 = 0x0F;

    // Main program loop
    while (1) {
        // Check button states (buttons are active-low due to pull-ups)
        if (PORTBbits.RB0 == 0) { // If Button 1 (RB0) is pressed
            pattern1();
        } else if (PORTBbits.RB1 == 0) { // If Button 2 (RB1) is pressed
            pattern2();
        } else if (PORTBbits.RB2 == 0) { // If Button 3 (RB2) is pressed
            pattern3();
        } else if (PORTBbits.RB3 == 0) { // If Button 4 (RB3) is pressed
            pattern4();
        } else if (PORTBbits.RB4 == 0) { // If Button 5 (RB4) is pressed
            pattern5();
        } else {
            LATD = 0x00; // Turn off all LEDs if no button is pressed
        }
    }

    return; // This return is technically unreachable due to the while(1) loop
}

Save the file (Ctrl + S or File > Save).

Configure Project Settings:

Right-click on your project name in the Projects window and select Properties.

In the Configuration window, ensure the Configuration Bits are set as follows (these are defined in the #pragma config directives in the code, but it's good to verify):

Oscillator Selection: HS (High Speed oscillator)

Watchdog Timer Enable: OFF

Power-up Timer Enable: ON

Click Apply and then OK.

Build the Project:

Click the Build Project icon (looks like a hammer) on the toolbar, or press F11.

Monitor the Output window for build messages. A successful build will generate a .hex file (e.g., LED_Patterns.X.production.hex) in your project's dist/default/production directory.

Step 2: Simulate the Circuit in Proteus
Install Proteus:
If not already installed, download and install Proteus Design Suite from the Labcenter Electronics website.

Create a New Project:

Open Proteus.

Click New Project from the start page or go to File > New Project.

Provide a project name (e.g., LED_Patterns_Simulation) and choose a location. Click Next.

Select Create a schematic from the selected template and click Next, then Finish.

Draw the Circuit:

Refer to the schematic.png file (or the placeholder image above) for the circuit layout.

Add the following components to your schematic from the Component Selection tool (press P to pick devices):

PIC18F4580 (Microcontroller)

BUTTON (5 push buttons)

RES (Resistors for pull-ups, e.g., 10kΩ, and current-limiting for LEDs, e.g., 220Ω)

LED (8 LEDs, choose desired color, e.g., LED-RED)

CRYSTAL (8 MHz crystal oscillator)

CAP (Capacitors, typically 22pF for crystal)

POWER and GROUND terminals.

Wire the components according to the schematic:

Connect RB0-RB4 to buttons with pull-up resistors to VCC.

Connect RD0-RD7 to LEDs with current-limiting resistors to ground.

Connect the 8MHz crystal and two 22pF capacitors to OSC1 and OSC2 pins of the PIC.

Ensure proper power (VCC) and ground (GND) connections to the PIC18F4580.

Load the Compiled Code:

Double-click on the PIC18F4580 component in your Proteus schematic.

In the Edit Component dialog box, locate the Program File field.

Click the folder icon (...) to browse and select the .hex file generated by MPLAB X IDE (e.g., path/to/your/LED_Patterns.X/dist/default/production/LED_Patterns.X.production.hex).

Ensure the Processor Clock Frequency is set to 8MHz (to match the crystal).

Click OK.

Run the Simulation:

Click the Play button (the green triangle icon) located at the bottom left of the Proteus workspace to start the simulation.

Click each button (RB0-RB4) in the simulation to observe the corresponding LED patterns on PORTD:

RB0: LEDs should light up sequentially from RD0 to RD7.

RB1: All LEDs should blink simultaneously.

RB2: LEDs should show an alternating 0xAA/0x55 pattern.

RB3: LEDs should show an alternating 0xCC/0x33 pattern.

RB4: LEDs should display a diagonal pattern sequence.

Verify that the observed patterns match the expected behavior.

Step 3: Hardware Implementation (Optional)
For those who wish to implement this project on physical hardware:

Program the PIC18F4580: Use a suitable PIC programmer (e.g., Microchip PICkit 3, PICkit 4) to flash the generated .hex file onto your PIC18F4580 microcontroller.

Assemble the Circuit: Build the circuit on a breadboard or custom PCB, following the exact connections shown in the schematic diagram.

Test: Apply power and press the physical buttons to observe the LED patterns on the actual hardware.

Troubleshooting
MPLAB Build Errors:

Check for syntax errors in led_patterns.c.

Ensure the Configuration Bits in Project Properties are correctly set (especially Oscillator and Watchdog Timer).

Verify that the XC8 compiler is properly installed and selected.

Proteus Simulation Issues:

Double-check all component connections in the schematic.

Ensure the correct .hex file is loaded into the PIC18F4580 properties.

Verify the Processor Clock Frequency in Proteus matches your crystal (8MHz).

Confirm pull-up resistors are correctly implemented for buttons.

Hardware Issues:

Ensure the power supply (5V) is correctly connected and stable.

Verify all wiring connections for continuity and correctness.

Check LED polarity and resistor values.

Confirm the PIC is correctly programmed.

Resources
MPLAB X IDE Download

XC8 Compiler Download

Proteus Design Suite (Labcenter Electronics)

PIC18F4580 Datasheet (This is a common link, verify latest from Microchip site)

License
This project is released under the MIT License. Feel free to use, modify, and distribute it for any purpose.
