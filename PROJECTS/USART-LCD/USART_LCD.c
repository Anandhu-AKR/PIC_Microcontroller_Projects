#include <xc.h>

void command(int cmd);
void data(int data);
void delay();
void trans(char c);
char rec();

void delay() {
    int i, j;
    for (i = 0; i < 500; i++) {
        for (j = 0; j < 500; j++) {
        }
    }
}

void command(int cmd) {
    LATD = cmd;
    RA0= 0;
    RA1 = 1;
    delay();
    RA1 = 0;
}

void data(int data) {
    LATD = data;
    RA0= 1;
    RA1 = 1;
    delay();
    RA1 = 0;
}

void trans(char c){
    
    TXREG=c;
    while(TXIF==0);
        TXIF=0;
        
    
    
}

char rec(){
    while(RCIF==0);
    return(RCREG);
    
}

void main(void) {

    TRISC=0X80;
    TXSTA=0X24;
    RCSTA=0X90;
    SPBRG=129;
    
    
    TRISD = 0x00;
    TRISA = 0x00;
    ADCON1=0x0f;
    
    
    delay();

    command(0x38);
    command(0x80);
    command(0x06);
    command(0x0E);
    command(0x01);
    
    char a;
    
    while(1){
        a=rec();
        data(a);
        trans(a);
    }
}