#include <pic18.h>

// Delay function
void delay() {
    int i, j;
    for (i = 0; i < 500; i++) {
        for (j = 0; j < 500; j++) {
        }
    }
}

// Pattern 1: Sequential lighting
void pattern1() {
    int i;
    for (i = 0; i < 8; i++) {
        LATD = 1 << i;
        delay();
    }
    LATD = 0x00;
}

// Pattern 2: Blink all LEDs
void pattern2() {
    LATD = 0xFF;
    delay();
    LATD = 0x00;
    delay();
    LATD = 0xFF;
    delay();
}

// Pattern 3: Alternating pattern
void pattern3() {
    LATD = 0xAA; // 10101010
    delay();
    LATD = 0x55; // 01010101
    delay();
    LATD = 0xAA;
    delay();
}

// Pattern 4: Checkerboard pattern
void pattern4() {
    LATD = 0xCC; // 11001100
    delay();
    LATD = 0x33; // 00110011
    delay();
    LATD = 0xCC;
    delay();
}

// Pattern 5: Diagonal pattern
void pattern5() {
    LATD = 0x81; // 10000001
    delay();
    LATD = 0x42; // 01000010
    delay();
    LATD = 0x24; // 00100100
    delay();
    LATD = 0x18; // 00011000
    delay();
    LATD = 0x00;
}

void main(void) {
    // Configure PORTB as input (for buttons)
    TRISB = 0xFF;
    // Configure PORTD as output (for LEDs)
    TRISD = 0x00;
    // Configure all pins as digital (disable analog)
    ADCON1 = 0x0F;

    while (1) {
        if (PORTBbits.RB0 == 0) { // Button 1 pressed
            pattern1();
        } else if (PORTBbits.RB1 == 0) { // Button 2 pressed
            pattern2();
        } else if (PORTBbits.RB2 == 0) { // Button 3 pressed
            pattern3();
        } else if (PORTBbits.RB3 == 0) { // Button 4 pressed
            pattern4();
        } else if (PORTBbits.RB4 == 0) { // Button 5 pressed
            pattern5();
        } else {
            LATD = 0x00; // All LEDs off if no button pressed
        }
    }
    
    return;
}