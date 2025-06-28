# PIC18F4580 LED Project

This project utilizes a **PIC18F4580 microcontroller** to control 8 LEDs (connected to PORTD, RD0–RD7) via 5 tactile buttons (connected to PORTB, RB0–RB4 with pull-up resistors). Each button press initiates a distinct LED illumination pattern.

The repository includes comprehensive instructions for simulating the project using Proteus Design Suite and compiling the firmware with MPLAB X IDE.

---

## 🚦 Project Overview

- **Microcontroller**: PIC18F4580
- **Inputs**: 5 push buttons connected to PORTB (RB0–RB4), configured with pull-up resistors
- **Outputs**: 8 LEDs connected to PORTD (RD0–RD7) with current-limiting resistors

### LED Patterns

| Button | Pattern                                      |
|-----------|-----------------------------------------------|
| RB0      | Sequential lighting of LEDs from RD0 to RD7  |
| RB1      | All LEDs blink synchronously                |
| RB2      | Alternating pattern: 0xAA ↔ 0x55          |
| RB3      | Alternating pattern: 0xCC ↔ 0x33          |
| RB4      | Diagonal lighting pattern: 0x81, 0x42, 0x24, 0x18 |

---

## 💾 Files

- `led_patterns.c`: Embedded C source code for PIC18F4580
- `schematic.png`: Circuit schematic diagram

---

## 🗺️ Schematic Diagram

![Schematic](blink.png)

---

## ⚙️ Step-by-Step Guide

### ✅ Prerequisites

- **MPLAB X IDE** with **XC8 Compiler** ([Download](https://www.microchip.com/mplab/mplab-x-ide))
- **Proteus Design Suite** ([Download](https://www.labcenter.com))
- Basic understanding of microcontroller programming and circuit simulation

---

### 💻 Step 1: Set Up the Project in MPLAB X IDE

1. **Install MPLAB X IDE and XC8 Compiler** (if not already installed).
2. **Create a new project**:
   - File > New Project > Microchip Embedded > Standalone Project
   - Select device: `PIC18F4580`
   - Select compiler: `XC8`
   - Name the project (e.g., `LED_Patterns`), choose a location, click Finish.
3. **Add source code**:
   - Right-click `Source Files` > New > C Main File > Name: `led_patterns.c`
   - Copy and paste the following code:

```c
#include <pic18.h>

// Configuration bits
#pragma config OSC = HS, WDT = OFF, LVP = OFF, PWRT = ON

void delay() {
    for (int i = 0; i < 500; i++)
        for (int j = 0; j < 500; j++);
}

void pattern1() {
    for (int i = 0; i < 8; i++) {
        LATD = (1 << i);
        delay();
    }
    LATD = 0x00;
}

void pattern2() {
    LATD = 0xFF;
    delay();
    LATD = 0x00;
    delay();
    LATD = 0xFF;
    delay();
    LATD = 0x00;
}

void pattern3() {
    LATD = 0xAA;
    delay();
    LATD = 0x55;
    delay();
    LATD = 0xAA;
    delay();
    LATD = 0x00;
}

void pattern4() {
    LATD = 0xCC;
    delay();
    LATD = 0x33;
    delay();
    LATD = 0xCC;
    delay();
    LATD = 0x00;
}

void pattern5() {
    LATD = 0x81;
    delay();
    LATD = 0x42;
    delay();
    LATD = 0x24;
    delay();
    LATD = 0x18;
    delay();
    LATD = 0x00;
}

void main(void) {
    TRISB = 0xFF;  // PORTB as input
    TRISD = 0x00;  // PORTD as output
    ADCON1 = 0x0F; // All digital

    while (1) {
        if (PORTBbits.RB0 == 0) pattern1();
        else if (PORTBbits.RB1 == 0) pattern2();
        else if (PORTBbits.RB2 == 0) pattern3();
        else if (PORTBbits.RB3 == 0) pattern4();
        else if (PORTBbits.RB4 == 0) pattern5();
        else LATD = 0x00;
    }
}
### ⚙️ Configure Project Settings

- Verify oscillator selection: `HS`
- Watchdog Timer: `OFF`
- Power-up Timer: `ON`

---

### 🔨 Build Project

- Click the hammer icon or press `F11`
- Check for `.hex` file in `dist/default/production/`

---

### 🧪 Step 2: Simulate in Proteus

#### Create new project

- Open Proteus and start a new project.

#### Add components

- PIC18F4580
- Push buttons
- Resistors (pull-up: ~10kΩ; LED current-limiting: ~220Ω)
- LEDs
- Crystal (8MHz)
- Capacitors (22pF)
- VCC and GND

#### Wire as per schematic

- Buttons to RB0–RB4 with pull-ups
- LEDs to RD0–RD7 with series resistors
- Crystal and capacitors on OSC1/OSC2 pins
- Proper power and ground connections

#### Load `.hex` file

- Double-click PIC component > set **Program File** to `.hex`
- Set **Clock frequency**: `8MHz`

#### Run simulation

- Click **Play** (green triangle)
- Press virtual buttons and observe LED patterns

---

### 🔧 Step 3: Hardware Implementation (Optional)

- Program PIC18F4580 with a programmer (e.g., PICkit 3/4)
- Assemble circuit on breadboard or PCB
- Test physically by pressing buttons

---

### 🛠️ Troubleshooting

#### MPLAB X

- Check syntax errors
- Verify configuration bits
- Ensure correct compiler selection

#### Proteus

- Verify all wiring connections
- Ensure correct `.hex` file loaded
- Match clock frequency (8MHz)
- Check pull-up resistor connections

#### Hardware

- Check power supply (5V)
- Verify wiring and continuity
- Check LED orientation and resistor values
- Confirm correct PIC programming

---

### 📚 Resources

- [MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)
- [XC8 Compiler](https://www.microchip.com/mplab/compilers)
- [Proteus Design Suite](https://www.labcenter.com)
- [PIC18F4580 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/39637c.pdf)
