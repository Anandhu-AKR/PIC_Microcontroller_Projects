# PIC Microcontroller Keypad to LCD Project

## 💡 Overview
This project demonstrates using a **PIC18F4550 microcontroller** to interface a **4x4 keypad** with a **16x2 LCD**. When a key is pressed, the corresponding character is displayed on the LCD in real time.

---

## 🛠️ Hardware Requirements
- **Microcontroller**: PIC18F4550
- **Display**: 16x2 LCD (e.g., LM016L)
- **Input**: 4x4 Keypad
- **Resistors**: 10kΩ (4 units) for keypad pull-ups

### Connections
- LCD data pins → **PORTB**
- LCD RS, EN → **RA0**, **RA1**
- Keypad rows → **PORTD bits 0–3**
- Keypad columns → **PORTD bits 4–7** with 10kΩ pull-ups

---

## 💻 Software Requirements
- **Compiler**: MPLAB XC8 (or compatible PIC compiler)
- **Header**: `<pic18.h>` for PIC18F4550 configuration

---

## 📌 Pin Configuration

| Component      | Pin Description | PIC18F4550 Port | Notes                         |
|----------------|-----------------|-----------------|-------------------------------|
| LCD RS         | Register Select | RA0             | Control instruction/data      |
| LCD EN         | Enable          | RA1             | Triggers LCD read/write       |
| LCD D0–D7      | Data Bus        | PORTB (RB0–RB7) | 8-bit parallel data           |
| Keypad Rows    | R1–R4           | RD7–RD4         | Output — activated one at a time |
| Keypad Columns | C1–C4           | RD3–RD0         | Input — read pressed state    |

---

### 🧮 Matrix Keypad Basics

A **4x4 keypad** has 4 rows and 4 columns. Every key press shorts a row and a column. To detect which key is pressed:
1. Set **one row LOW** (others HIGH).
2. Read the **column inputs**:
   - If one column reads LOW → that key is pressed.
3. Cycle through all rows one by one.

---

### 🔁 Scanning Algorithm Used

We scan one row at a time by outputting a **specific pattern** to `PORTD` and then reading the column lines:

```c
PORTD = 0x7F;  // 0111 1111 → RD7=0 (Row 1 active), RD6–RD4=1, RD3–RD0 are column inputs
PORTD & 0x0F → reads the lower nibble (RD3–RD0)

We check for expected patterns using switch-case

Expected Input Values from Columns:


| Column | Input Pattern | Binary   | Hex   |
|--------|----------------|----------|-------|
| C1     | 1110           | 0b1110   | 0x0E  |
| C2     | 1101           | 0b1101   | 0x0D  |
| C3     | 1011           | 0b1011   | 0x0B  |
| C4     | 0111           | 0b0111   | 0x07  |

### 🧠 Explanation of Hex Values

- The **column bits** are connected to `PORTD` pins **RD3 to RD0**.
- The **rows** are controlled by **RD7 to RD4**.
- For example:  
  `PORTD = 0x7F = 0111 1111`  
  → This sets **RD7 = 0**, which **activates Row 1** (active-low logic).
- When a key in **Row 1** is pressed, one of the **column pins is pulled low**, resulting in distinct patterns like:
  - `0x0E` (C1 low), `0x0D` (C2 low), etc.
- These patterns are used in `switch()` statements in code to **identify which key is pressed**.

---

## 🔘 Keypad Character Mapping

|       | Col 1 | Col 2 | Col 3 | Col 4 |
|-------|-------|-------|-------|-------|
| Row 1|   1   |   2   |   3   |   4   |
| Row 2|   5   |   6   |   7   |   8   |
| Row 3|   A   |   B   |   C   |   D   |
| Row 4|   E   |   F   |   G   |   H   |

---

## 📟 PORTD Row Selection Values

Each row is activated by setting its corresponding bit in `PORTD` to `0` (active-low):

| Row | `PORTD` Value | Binary        |
|-----|----------------|----------------|
| R1  | 0x7F           | 0111 1111      |
| R2  | 0xBF           | 1011 1111      |
| R3  | 0xDF           | 1101 1111      |
| R4  | 0xEF           | 1110 1111      |


```

## ⚡ Circuit Diagram
![Schematic](keypad.png)

---

## 🧑‍💻 Code

```c
#include <pic18.h>  // Include device-specific header for PIC18F4550

// Function Prototypes
void delay();
void command(int);
void dat(char);
char key();

/**
 * Delay function - crude software delay using nested loops
 * You can tune loop counts depending on your clock frequency
 */
void delay() {
    int i, j;
    for (i = 0; i < 600; i++) {
        for (j = 0; j < 200; j++) {
            // Do nothing - just waste time
        }
    }
}

/**
 * Send a command to the LCD
 * cmd: 8-bit command to send (e.g., 0x01 to clear, 0x80 to go to line 1, etc.)
 */
void command(int cmd) {
    LATB = cmd;  // Send command to PORTB (connected to LCD data pins)
    RA0 = 0;     // RS = 0 → Command mode
    RA1 = 1;     // Enable pulse (E = 1)
    delay();     // Short delay
    RA1 = 0;     // E = 0 → Latch the command
}

/**
 * Send data (character) to the LCD
 * data: ASCII character to display
 */
void dat(char data) {
    LATB = data;  // Send data to PORTB
    RA0 = 1;      // RS = 1 → Data mode
    RA1 = 1;      // Enable pulse (E = 1)
    delay();      // Short delay
    RA1 = 0;      // E = 0 → Latch the data
}

/**
 * Main function
 * Initializes ports, LCD, and starts scanning keypad to display input on LCD
 */
void main(void) {
    TRISA = 0x00;   // Set all PORTA pins as output (RA0:RS, RA1:E)
    TRISB = 0x00;   // Set PORTB as output (LCD data lines)
    ADCON1 = 0x0F;  // Configure all PORTA/PORTB pins as digital I/O
    TRISC = 0x00;   // PORTC can be used if needed; set as output
    TRISD = 0x0F;   // RD0–RD3 (Rows) as input (0), RD4–RD7 (Columns) as output (1)

    // LCD Initialization sequence
    command(0x38);  // 8-bit, 2-line, 5x8 font
    command(0x80);  // Move cursor to beginning of first line
    command(0x06);  // Increment cursor
    command(0x0E);  // Display ON, Cursor ON
    command(0x01);  // Clear display

    char b;
    while (1) {
        b = key();   // Scan keypad for input
        dat(b);      // Display received key on LCD
    }
}

/**
 * Keypad scanning function (4x4 matrix)
 * PORTD bits RD7-RD4 are rows (outputs), RD3-RD0 are columns (inputs)
 * The function sets one row LOW at a time and reads the columns
 * Returns the corresponding character when a key is pressed
 */
char key() {
    int e;

    while (1) {
        // ROW1 LOW, others HIGH → PORTD = 0111 1111b = 0x7F
        PORTD = 0x7F;
        e = PORTD & 0x0F;  // Read lower 4 bits (columns)
        switch (e) {
            case 0x07: return '4';  // 0111
            case 0x0B: return '3';  // 1011
            case 0x0D: return '2';  // 1101
            case 0x0E: return '1';  // 1110
        }

        // ROW2 LOW → PORTD = 1011 1111b = 0xBF
        PORTD = 0xBF;
        e = PORTD & 0x0F;
        switch (e) {
            case 0x07: return '8';
            case 0x0B: return '7';
            case 0x0D: return '6';
            case 0x0E: return '5';
        }

        // ROW3 LOW → PORTD = 1101 1111b = 0xDF
        PORTD = 0xDF;
        e = PORTD & 0x0F;
        switch (e) {
            case 0x07: return 'D';
            case 0x0B: return 'C';
            case 0x0D: return 'B';
            case 0x0E: return 'A';
        }

        // ROW4 LOW → PORTD = 1110 1111b = 0xEF
        PORTD = 0xEF;
        e = PORTD & 0x0F;
        switch (e) {
            case 0x07: return 'H';
            case 0x0B: return 'G';
            case 0x0D: return 'F';
            case 0x0E: return 'E';
        }
    }
}

```

## ▶️ Usage
- Compile using MPLAB XC8.
- Program the PIC18F4550 with the generated hex file.
- Connect the circuit as per schematic.
- Power on; LCD will show pressed keys live.

## ⚠️ Limitations
- Basic delay; adjust based on clock frequency.
- No keypad debounce; add for improved reliability.
- Code assumes a specific keypad layout — verify with your hardware.

## 📄 License
This project is shared for educational purposes only. Unauthorized reproduction or distribution is prohibited.

## 🙏 Acknowledgments
Designed and tested on a PIC18F4550 development board with a standard 16x2 LCD module.

## 📚 Resources
- [PIC18F4550 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/39632e.pdf)
- [16x2 LCD Datasheet](https://www.sparkfun.com/datasheets/LCD/HDM16216H-5.pdf)
- [Proteus Design Suite](https://www.labcenter.com/)
