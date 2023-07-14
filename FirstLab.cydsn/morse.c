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
#include "morse.h"

#include "lighter.h"
#include "printer.h"
#include "soundhandler.h"
#include "lightsensor.h"
#include "translator.h"
#include "semaphores.h"

#define MAX_MESSAGE_LENGTH 50

#define TI_DELAY 250
#define TAAH_DELAY 750

/* play a sound for as long as the duration
   value passed in parameter */
void emitSoundSignal (int duration) {
    int j = 0;
    int timeElapsed = 0;
    
    while (timeElapsed < duration * 1000) {
        int overFlow = getTC();
        if (overFlow) {
            setVDACvalue (j);
            if (++j > 99)
                j = 0;
            timeElapsed += 50;
        }
    } 
}

/* play a sound for as long as a ti signal */
void emitShortSoundSignal (void) {
    emitSoundSignal(TI_DELAY);
}

/* play a sound for as long as a taah signal */
void emitLongSoundSignal (void) {
    emitSoundSignal(TAAH_DELAY);
}

/* emit a short morse signal using the LEDs */
void emitShortSignalWithBlinking (void) {
    
    toggleAllLights(); // turn on the lights
    emitShortSoundSignal();
    toggleAllLights(); // turn off the lights
}

/* emit a long morse signal using the LEDs */
void emitLongSignalWithBlinking (void) {
    
    toggleAllLights(); // turn on the lights
    emitLongSoundSignal();
    toggleAllLights(); // turn off the lights
}

void sendMessage(char message[]) {
    int night = isNight();
    
    const int MSG_LENGTH = strlen(message);
            
    char morseMessage[MSG_LENGTH * 7]; // 7 is the max length of the
                                       // morse equivalent of any character
            
    strcpy(morseMessage, msgToMorse(message)); // morseMessage := msgToMorse(userMessage)
            
    adequatePrint(message);
    emitMorseMessage(morseMessage, night);
    if (! night) displayMessageAsSemaphoreMorseCode(morseMessage);

    
}

/* emit the morse message passed in parameter with sound 
   if the parameter is set to 1, LEDs are also used */
void emitMorseMessage(char param[], int night) {
    LCD_Screen_ClearDisplay();
    
    const int LENGTH = strlen(param);
    
    char firstRow[8] = "        ";
    char secondRow[8] = "        ";
    
    /* displays a blank screen for one second */
    LCD_Screen_Position(0,0);
    LCD_Screen_PrintString(firstRow);
    LCD_Screen_Position(1,0);
    LCD_Screen_PrintString(secondRow);
    CyDelay(250);
    
    for (int j = 0; j < LENGTH; j++)
    {
        /* updates the variables to print */
        for (int i = 0; i < 7; i++) {
            firstRow[i] = firstRow[i+1];
        }
        firstRow[7] = secondRow[0];
        for (int i = 0; i < 7; i++) {
            secondRow[i] = secondRow[i+1];    
        }
        
        secondRow[7] = param[j];
        
        /* displays the value of the variables */
        LCD_Screen_Position(0,0);
        LCD_Screen_PrintString(firstRow);
        LCD_Screen_Position(1,0);
        LCD_Screen_PrintString(secondRow);
        
        UART_PutChar(param[j]);
         
        if (secondRow[7] == '.') {
            if (night)
                emitShortSignalWithBlinking();
            else
                emitShortSoundSignal();
        }
        
        else if (secondRow[7] == '-') {
            if (night)
                emitLongSignalWithBlinking();
            else
                emitLongSoundSignal();
        }
        
        else if (secondRow[7] == ' ')
            CyDelay(TAAH_DELAY);
        else if (secondRow[7] == '/')
            CyDelay(TI_DELAY);
        
        CyDelay(TI_DELAY);
    }
    
    CyDelay(500);
    LCD_Screen_ClearDisplay();
    UART_PutChar(0x0A); // line feed
}

/* return the prerecorded message associated
   with the character passed in parameter */
char* getPrerecordedMessage (char c) {
 
    char* prerecordedMessage = "";
    
    switch (c)
    {
        case '1':
            prerecordedMessage = "SOS";
            break;
        case '2':
            prerecordedMessage = "BEAMS";
            break;
        case '3':
            prerecordedMessage = "Coucou :-)";
            break;
        case '4':
            prerecordedMessage = "Au revoir !";
            break;
        case '5':
            prerecordedMessage = "+-+ UrLab +-+";
            break;
        case '6':
            prerecordedMessage = "Scientia vincere tenebras";
            break;
        case '7':
            prerecordedMessage = "O Belgique...";
            break;
        case '8':
            prerecordedMessage = "Allo ?";
            break;
        case '9':
            prerecordedMessage = "CI ! CI ! CI ! S*x & chopes !";
            break;
        case '0':
            prerecordedMessage = "One Two Three Viva l'Algerie !"; // choix de Robin #DZ
            break;
        case '#':
            prerecordedMessage = "Hello World !";
            break;
    }
    
    return prerecordedMessage;
}


/* [] END OF FILE */
