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
