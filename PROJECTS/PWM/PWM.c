#include <xc.h>

void delay();

void main(void) {
    
    //osc
    TRISD=0X00;
    TMR0L=0;
    T0CON=0XC7;
    
    //PWM
    TRISC=0x20;
    CCP1CON=0X0C;   
    TMR2ON=1;
    TMR2=0X00;
    
    int i;
    while(1){
        for(i=0;i<256;i++){
            CCPR1L=i;
            delay();
        }
    }
    
    
    return;
}

void delay(){
    int i,j;
    
    for(i=0;i<500;i++){
        for(j=0;j<500;j++){
    }
}
}