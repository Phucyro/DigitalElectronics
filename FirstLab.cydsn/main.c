/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "keypad.h"

#include "printer.h"
#include "lighter.h"
#include "translator.h"
#include "lightsensor.h"
#include "soundhandler.h"
#include "semaphores.h"

#include "morse.h"

#include "math.h"

#define MAX_MESSAGE_LENGTH 50
char userMessage[MAX_MESSAGE_LENGTH];

uint8 rxData;
int aMessageIsReadyToBeSendflag;

CY_ISR ( Rx_Handler ) {
    uint8_t status = 0;
    do {
        // Checks if no UART Rx errors
        status = UART_ReadRxStatus();
        if (( status & UART_RX_STS_PAR_ERROR ) |
        ( status & UART_RX_STS_STOP_ERROR ) |
        ( status & UART_RX_STS_BREAK ) |
        ( status & UART_RX_STS_OVERRUN ) ) {
            // Parity , framing , break or overrun error
            LCD_Screen_Position(1 ,0);
            LCD_Screen_PrintString("UART err");
        }
        // Check that rx buffer is not empty and get rx data
        if ( ( status & UART_RX_STS_FIFO_NOTEMPTY ) != 0){
            rxData = UART_ReadRxData();
            
            if (rxData != '\n') {
                char strToConcat[2] = "\0\0";
                strToConcat[0] = rxData;
                strcat(userMessage, strToConcat);
            }
            
            else 
                aMessageIsReadyToBeSendflag = 1;
            
        }
    } while (( status & UART_RX_STS_FIFO_NOTEMPTY ) != 0);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts */
    
    LCD_Screen_Start();
    keypadInit();
    
    ADC_DelSig_Start();
    
    Timer_Start();
    
    initVector();
    
    VDAC_Start();
    
    char keyPressed;
    char lastKeyPressed;
    
    int j =  0;
    
    PWM_1_Start();
    PWM_2_Start();
    
    int selectedServo = 1;
    
    UART_Start();
    Rx_Int_StartEx( Rx_Handler );
    
    for(;;)
    {   
        if (Pin_SW1_Read()) {
            
            toggleAllLights(); // turn on the lights
            
            while ( Pin_SW1_Read() ) {
                    int overFlow = getTC();
                    if (overFlow) {
                        setVDACvalue (j);
                        if (++j > 99)
                            j = 0;
                    }
            }
            
            toggleAllLights(); // turn off the lights
        }
            
        else if (Pin_SW2_Read())
            emitShortSignalWithBlinking();
            
        else if (Pin_SW3_Read())
            emitLongSignalWithBlinking();
        
        else if (Pin_SW4_Read())
        {
            if (selectedServo == 1)
                selectedServo = 2;
            else if (selectedServo == 2)
                selectedServo = 1;
            updateSemaphorePosition(selectedServo);
            CyDelay(500); // it prevents accidentally pressing
                          // the button several times in a row
        }
        
        updateSemaphorePosition(selectedServo);
        
        keyPressed = keypadScan();
        if (keyPressed != 'z' && keyPressed != '*') { // first user input on the keyboard
                                                      // must be different than the '*'            
            lastKeyPressed = keyPressed;
            printChar(lastKeyPressed);
            
            while (keyPressed != '*') {
                keyPressed = keypadScan();
                
                if (keyPressed != 'z' && keyPressed !='*') {
                    lastKeyPressed = keyPressed;
                    printChar(lastKeyPressed);
                }
            }
            
            
            
            char* prerecordedMessage = getPrerecordedMessage(lastKeyPressed);
            
            sendMessage(prerecordedMessage);
        }
        
                
        if ( aMessageIsReadyToBeSendflag ) // the strings are differents
        { 
            
            sendMessage(userMessage);
            
            strcpy(userMessage, ""); // userMessage is reset
            aMessageIsReadyToBeSendflag = 0;
        }
        
    }
}

/* [] END OF FILE */
