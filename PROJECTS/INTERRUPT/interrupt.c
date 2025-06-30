#include <xc.h>

void delay();
void main(void) {
    
    TRISD=0X00;
    TRISB=0xFF;
    ADCON1=0x0F;
    GIE=1;
    PEIE=1;
    INT0IE=1;
    
        
    return;
}


void __interrupt() isr(void){
    
    while(INT0IF==1){
         LATD=0XCC;
         delay();
         LATD=0x33;
         delay();
         LATD=0X00;
         INT0IF=0;
    }
     
}

void delay() {
    int i, j;
    for (i = 0; i < 600; i++) {
        for (j = 0; j < 600; j++) {
        }
    }
}

