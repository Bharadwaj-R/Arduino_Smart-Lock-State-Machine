#include "KeypadHandler.h"

uint8_t columnScan[4] = {FIRST_COLUMN, SECOND_COLUMN, THIRD_COLUMN, FOURTH_COLUMN};
uint8_t scan = 0;
uint8_t rowInput = B00000000;
uint8_t keyCode = 0;

void SetupKeypad()
{
    pinMode(PORTB, INPUT_PULLUP);  // the whole port B will read 1 by default B11111111
    pinMode(PORTD, OUTPUT);
    digitalWrite(PORTD, B00000000);
}

char ScanKeypad()
{
    for(scan = 0; scan < 4; scan++)
    {   
        digitalWrite(PORTD, columnScan[scan%4]);
        rowInput = PINB;
        keyCode = columnScan[scan%4] ^ rowInput;        

        switch (keyCode)
        {
        case BUTTON_0_PRESSED:
            return '0';
        break;
        
        case BUTTON_1_PRESSED:
            return '1';
        break;
        
        case BUTTON_2_PRESSED:
            return '2';
        break;
        
        case BUTTON_3_PRESSED:
            return '3';
        break;
        
        case BUTTON_4_PRESSED:
            return '4';
        break;
        
        case BUTTON_5_PRESSED:
            return '5';
        break;
        
        case BUTTON_6_PRESSED:
            return '6';
        break;
        
        case BUTTON_7_PRESSED:
            return '7';
        break;
        
        case BUTTON_8_PRESSED:
            return '8';
        break;
        
        case BUTTON_9_PRESSED:
            return '9';
        break;

        case BUTTON_star_PRESSED:
            return '*';
        break;
        
        case BUTTON_hash_PRESSED:
            return '#';
        break;
        
        case BUTTON_A_PRESSED:
            return 'A';
        break;
        
        case BUTTON_B_PRESSED:
            return 'B';
        break;
        
        case BUTTON_C_PRESSED:
            return 'C';
        break;
        
        case BUTTON_D_PRESSED:
            return 'D';
        break;

        default:
            return '\0';
        break;
        
        }
    }
}