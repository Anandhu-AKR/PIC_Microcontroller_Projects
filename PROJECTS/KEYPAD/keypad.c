    #include <pic18.h>

void delay();
void command(int);
void dat(char);
char key();


void delay() {
    int i, j;
    for (i = 0; i < 600; i++) {
        for (j = 0; j < 200; j++) {
        }
    }
}

void command(int cmd) {
    LATB = cmd;
    RA0= 0;
    RA1 = 1;
    delay();
    RA1 = 0;
}

void dat(char data) {
    LATB = data;
    RA0= 1;
    RA1 = 1;
    delay();
    RA1 = 0;
}

void main(void) {
    
    
    TRISA=0X00;
    TRISB = 0x00;
    ADCON1 = 0x0F;
    TRISC = 0x00;
    TRISD=0X0F;
  
    command(0x38);
    command(0x80);
    command(0x06);
    command(0x0E);
    command(0x01);
    
    char b;
    
    while(1){
        b=key();
        dat(b);
    }
    
    
    
    
    
}

char key(){
    int e;
    while(1){
        PORTD=0X7F;
        e=PORTD&0X0F;
        
        switch(e){
            case(0X07):
                return '4';
            case(0X0B):
                return '3';
            case(0X0D):
                return '2';
            case(0X0E):
                return '1';
                
        }
        
        PORTD=0XBF;
        e=PORTD&0X0F;
        
        switch(e){
            case(0X07):
                return '8';
            case(0X0B):
                return '7';
            case(0X0D):
                return '6';
            case(0X0E):
                return '5';
        }
        
        PORTD=0XDF;
        e=PORTD&0X0F;
        
        switch(e){
            case(0X07):
                return 'D';
            case(0X0B):
                return 'C';
            case(0X0D):
                return 'B';
            case(0X0E):
                return 'A';
        }
        
        PORTD=0XEF;
        e=PORTD&0X0F;
        
        switch(e){
            case(0X07):
                return 'H';
            case(0X0B):
                return 'G';
            case(0X0D):
                return 'F';
            case(0X0E):
                return 'E';
        }
    }
}
