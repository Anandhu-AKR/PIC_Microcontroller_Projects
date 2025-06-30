#include <xc.h>

void main(void) {

    TRISC=0X80;
    TXSTA=0X24;
    RCSTA=0X90;
    SPBRG=129;
    
    
    char *message="HELLO";
    char i=0;
    while(message[i] != '\0'){
        TXREG= message[i];
        
        while(TXIF==0);
        TXIF=0;
        i++;
    }
    
    while(1);
    
}
