#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include <pic16f628a.h>

volatile unsigned char buffer[0x20], addr = 0x00, head = 0x00;

void USART_init(void){
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    
    TXSTAbits.SYNC = 1;
    RCSTAbits.SPEN = 1;
    TXSTAbits.CSRC = 0;

    PIE1bits.RCIE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    RCSTAbits.CREN = 1;
}

void interrupt message(void){
    if(PIR1bits.RCIF == 1){
        buffer[head] = RCREG;
        head = (head+1) & 0x1F;
    }
}

void main(void) {
    unsigned char tail = 0x00;
    USART_init();
    while(1){
        if(head != tail){
            EEPROM_WRITE(addr, buffer[tail]);
            addr++;
            tail = (tail+1) & 0x1F;
        }
        if(addr >= 0x80){
            PIE1bits.RCIE = 0;
            INTCONbits.GIE = 0;
            INTCONbits.PEIE = 0;
            break;
        }
    }
    while(1){
        
    }
}