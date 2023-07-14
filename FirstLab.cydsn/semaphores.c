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
#include "semaphores.h"

#define RIGHT 500
#define LEFT 2500
#define MIDDLE 1500

#define LONGPAUSE 1500
#define SHORTPAUSE 500

/* update the selected servo position passed in
   parameter according to the potentiometer value*/
void updateSemaphorePosition (int selectedServo) {
    
    AMux_FastSelect(0); // Potentiometer selected
    
    ADC_DelSig_StartConvert();
    
    int result;    
    if ( ADC_DelSig_IsEndConversion( ADC_DelSig_WAIT_FOR_RESULT ) )
    {
        result = ADC_DelSig_GetResult32(); // result in more or less [0, 0xFFFF]
        result = (result / 32) + RIGHT - 39; // result in [500; 2500]
        
        if (selectedServo == 1)
            PWM_1_WriteCompare(result);
        else if (selectedServo == 2)
            PWM_2_WriteCompare(result);
    }
}

/* put the flags up */
void verticalFlags (void) {
    PWM_1_WriteCompare(RIGHT);
    PWM_2_WriteCompare(LEFT);
}

/* put the flags horizontally */
void horizontalFlags (void) {
    PWM_1_WriteCompare(MIDDLE);
    PWM_2_WriteCompare(MIDDLE);
}

/* put the flags down */
void flagsDown (void) {
    PWM_1_WriteCompare(LEFT);
    PWM_2_WriteCompare(RIGHT);
}

/* wave flags to get attention according to the signaling code */
void displayAttentionSemaphoreMessage (void) {
    
    PWM_1_WriteCompare( (LEFT + MIDDLE) / 2 );
    PWM_2_WriteCompare( (RIGHT + MIDDLE) / 2 );
    CyDelay(SHORTPAUSE);
    
    for (int i = 0; i < 3; i++){
        PWM_1_WriteCompare( (RIGHT + MIDDLE) / 2 );
        PWM_2_WriteCompare( (LEFT + MIDDLE) / 2 );
        CyDelay(SHORTPAUSE);
        
        PWM_1_WriteCompare( (LEFT + MIDDLE) / 2 );
        PWM_2_WriteCompare( (RIGHT + MIDDLE) / 2 );
        CyDelay(SHORTPAUSE);
    }
    
    PWM_1_WriteCompare( (RIGHT + MIDDLE) / 2 );
    PWM_2_WriteCompare( (LEFT + MIDDLE) / 2 );
    CyDelay(SHORTPAUSE*2);
    
}

/* display the morse message passed in parameter using
   the semaphore morse code 
   - putting the flags up means '.'
   - putting the flags horizontally means '-'
   - putting the flags down can either mean a separation
     between two identical letters or mean a space character,
     depending on how much time the flags stay down */
void displayMessageAsSemaphoreMorseCode (char msg[]) {
    const int LENGTH = strlen(msg);
    
    displayAttentionSemaphoreMessage();
    
    char lastChar = 'e'; // empty
    for (int j = 0; j < LENGTH; j++)
    {
        if (msg[j] == lastChar && lastChar != ' ' && lastChar != '/') {
            flagsDown();
            CyDelay(SHORTPAUSE);
        }
        
        if (msg[j] == '.') {
            verticalFlags();
            CyDelay(SHORTPAUSE);
        }
        
        else if (msg[j] == '-') {
            horizontalFlags();
            CyDelay(SHORTPAUSE);
        }
        
        else if (msg[j] == ' ') {
            flagsDown();
            CyDelay(LONGPAUSE);
        }
        
        lastChar = msg[j];
    }
    
    flagsDown();
    CyDelay(LONGPAUSE);
};

/* [] END OF FILE */
