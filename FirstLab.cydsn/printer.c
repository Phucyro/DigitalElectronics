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

#include "printer.h"

/*
    displays a character at the
    first place of the LCD screen
*/
void printChar (char c) {
    LCD_Screen_ClearDisplay();
    LCD_Screen_Position(0,0);
    LCD_Screen_PutChar(c);
    
    CyDelay(50);
}

/*
    print the string passed in parameter according
    to the length of the string
*/
void adequatePrint(char param[]) {
    
    const int LENGTH = strlen(param);
    
    if (LENGTH > 16)
        scrollingPrint(param);
    else
        staticPrint(param);
    
}

/*
    displays the string passed in parameter
*/
void staticPrint(char param[]) {
    LCD_Screen_ClearDisplay();
    
    const int LENGTH = strlen(param);
    
    LCD_Screen_Position(0,0);
    for (int i = 0; i < 8; i++) {
        if (i == LENGTH) // the whole msg has been printed
            break;        
        LCD_Screen_PutChar( param[i] );
    }
    
    LCD_Screen_Position(1,0);    
    for (int i = 8; i < 16; i++) {
        if (i >= LENGTH) // the whole msg has been printed
            break;        
        LCD_Screen_PutChar( param[i] );
    }
    
    CyDelay(1500);
    LCD_Screen_ClearDisplay();
}

/*
    scrolls the string passed in parameter on the LCD screen for
    as long as the whole string has not been entirely showed on screen
*/
void scrollingPrint( char param[] ) {
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
    
    for (int j = 0; j < LENGTH + 1; j++)
    {
        /* updates the variables to print */
        for (int i = 0; i < 7; i++) {
            firstRow[i] = firstRow[i+1];
        }
        firstRow[7] = secondRow[0];
        for (int i = 0; i < 7; i++) {
            secondRow[i] = secondRow[i+1];    
        }
        
        if (j < LENGTH) // puts the next character to display
            secondRow[7] = param[j]; // at the end of the screen
        else
            secondRow[7] = ' ';
        
        /* displays the value of the variables */
        LCD_Screen_Position(0,0);
        LCD_Screen_PrintString(firstRow);
        LCD_Screen_Position(1,0);
        LCD_Screen_PrintString(secondRow);
        
        CyDelay(500);
        
    }
    
    CyDelay(1500);
    LCD_Screen_ClearDisplay();
}

/* [] END OF FILE */
