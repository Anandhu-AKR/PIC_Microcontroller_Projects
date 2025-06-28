# PIC18F4580 Dual Motor Control with LCD

This project demonstrates controlling two DC motors using a PIC18F4580 microcontroller and an L293D motor driver IC, with status display on a 16x2 LCD.

---

## 💡 Overview

- Microcontroller: PIC18F4580
- Motor Driver IC: L293D
- Motors: 2 DC motors
- Display: 16x2 LCD for showing status messages (e.g., "Forward", "Reverse", "Stop")

---

## ⚙️ Connections

### L293D Motor Driver

| L293D Pin | PIC Pin | Description      |
|-----------|---------|------------------|
| IN1       | RD0     | Motor 1 control  |
| IN2       | RD1     | Motor 1 control  |
| IN3       | RD2     | Motor 2 control  |
| IN4       | RD3     | Motor 2 control  |
| EN1 & EN2 | VCC     | Enable inputs (logic high) |

> 💬 Note: Motors are connected to OUT1/OUT2 and OUT3/OUT4 on L293D.

---

## 💻 Code Highlights

```
#include <pic18.h>

void delay() {
    int i, j;
    for(i = 0; i < 50000; i++) {
        for(j = 0; j < 50000; j++) {}
    }
}

void forward() {
    LATD = 0x1D;  // Example: Motors forward
}

void reverse() {
    LATD = 0x06;  // Example: Motors reverse
}

void stop() {
    LATD = 0x00;  // Stop motors
}

void main(void) {
    TRISD = 0x00;  // PORTD as output
    ADCON1 = 0x0F; // All digital

    while(1) {
        if (RB == 1) {
            forward();
            delay();
        }
    }
}
```

💬 Note: The condition (`if(RB == 1)`) should be replaced with your actual button or logic condition.

---

## 🗺 LCD Connection (Typical)

| LCD Pin | PIC Pin | Description        |
|---------|---------|--------------------|
| RS      | RC0     | Register Select    |
| RW      | RC1     | Read/Write         |
| E       | RC2     | Enable             |
| D4–D7   | RD4–RD7 | Data lines         |

---

## 🧪 Simulation & Hardware

**Simulation (Proteus):**
- Add PIC18F4580
- Add L293D and two DC motors
- Add 16x2 LCD
- Wire as per schematic
- Load compiled .hex file
- Simulate motor control and LCD messages

**Hardware:**
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

---

✅ Copy this whole block as your README.md — it is fully formatted and ready! Let me know if you'd also like to embed schematic images or extra diagrams.
```

Want help adding a schematic or wiring diagram too? 😊
