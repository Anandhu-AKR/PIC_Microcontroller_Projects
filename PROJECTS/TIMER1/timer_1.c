#include <pic18.h>

void timer();

void main(void) {
    
    TRISD=0X00;
    TMR1L=0X96;
    TMR1H=0XE7;
    T1CON=0X79;
    
    while(1){
        LATD=0XFF;
        timer();
        LATD=0X00;
        timer();
    }
    
    
    
    
}

void timer(){
    while(TMR1IF==0);
    TMR1IF=0;
    TMR1L=0X96;
    TMR1H=0XE7;
}