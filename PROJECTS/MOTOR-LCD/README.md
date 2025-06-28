# PIC18F4580 Dual Motor Control with LCD

This project demonstrates controlling two DC motors using a PIC18F4580 microcontroller and an L293D motor driver IC, with status display on a 16x2 LCD.

---

## 💡 Overview

- **Microcontroller**: PIC18F4580
- **Motor Driver IC**: L293D
- **Motors**: 2 DC motors
- **Display**: 16x2 LCD for showing status messages (e.g., "Forward", "Reverse", "Stop")

---

## ⚙️ Connections

### L293D Motor Driver

| L293D Pin | PIC Pin | Description                |
|------------|----------|----------------------------|
| IN1        | RD0     | Motor 1 control          |
| IN2        | RD1     | Motor 1 control          |
| IN3        | RD2     | Motor 2 control          |
| IN4        | RD3     | Motor 2 control          |
| EN1 & EN2  | VCC     | Enable inputs (logic high) |

> 💬 **Note**: Motors are connected to OUT1/OUT2 and OUT3/OUT4 on L293D.

---

## 🗺️ LCD Connection (Typical)

| LCD Pin | PIC Pin | Description      |
|----------|----------|------------------|
| RS      | RA0     | Register Select |
| RW      | RA1     | Read/Write      |
| E       | NA     | Controlled via code |
| D0–D7   | RC0–RC7 | Data lines      |

---

## 💻 Code Highlights

```c
#include <pic18.h>

void delay1() {
    int i, j;
    for (i = 0; i < 500; i++) {
        for (j = 0; j < 500; j++) {
        }
    }
}
void delay2() {
    int i, j;
    for (i = 0; i < 1000; i++) {
        for (j = 0; j < 1000; j++) {
        }
    }
}

void command(int cmd) {
    LATC = cmd;
    RA0 = 0;
    RA1 = 1;
    delay1();   
    RA1 = 0;
}

void data(int data) {
    LATC = data;
    RA0 = 1;
    RA1 = 1;
    delay1();
    RA1 = 0;
}

void forward() {
    LATD = 0x1D;
}

void reverse() {
    LATD = 0x2E;
}

void stop() {
    LATD = 0x00;
}

void lcd_print(char* str) {
    while (*str) {
        data(*str++);
    }
}

void main(void) {
    TRISD = 0x00;
    TRISB = 0xFF;
    ADCON1 = 0x0F;
    TRISC = 0x00;
    TRISA0 = 0;
    TRISA1 = 0;
    
    delay1();

    command(0x38);
    command(0x80);
    command(0x06);
    command(0x0E);
    command(0x01);

    while (1) {
        if (RB0 == 0) {
            command(0x01);
            command(0x80);
            
            forward();
            lcd_print("FORWARD");
            
            delay2();
            stop();
            command(0X01);
        } else if (RB1 == 0) {
            command(0x01);
            command(0x80);
            
            reverse();
            lcd_print("REVERSE");
            
            delay2();
            stop();
            command(0X01);
        } else {
            stop();
        }
    }
}

```
## 💬 Note
The condition checks RB0 and RB1 (active low). Change logic as needed for your actual hardware buttons.

---

## 🗺 Schematic Diagram
*(Insert your schematic diagram image or link here)*

---

## 🧪 Simulation & Hardware

### Simulation (Proteus)
- Add PIC18F4580
- Add L293D and two DC motors
- Add 16x2 LCD
- Wire as per schematic
- Load compiled `.hex` file
- Simulate motor control and LCD messages

### Hardware
- Program the PIC using a PICkit
- Assemble the circuit on breadboard or PCB
- Test motors and LCD output

---

## 🛠 Future Enhancements
- Add more button-based motor control modes
- Implement speed control using PWM
- Improve LCD status updates

---

## 📚 Resources
- PIC18F4580 Datasheet
- L293D Datasheet
- Proteus Design Suite

---

## 💬 License
This project is released under the MIT License. Feel free to use, modify, and share!
