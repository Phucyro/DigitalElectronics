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
#include "translator.h"

char* msgToMorse(char msg[]) {
    
    const int LENGTH = strlen(msg);
    
    char translation[LENGTH*7]; // the maximal numbers of characters
                                // needed to representent any character
                                // in morse code is 7

    strcpy(translation, "");
    
    for (int i = 0; i < LENGTH; i++)
    {
        char* code = charToMorse( msg[i] );
        
        strcat(translation, code);
        strcat(translation, " ");
        
    }
    
    strcat(translation, "\0"); // null character means end of string
    char* morse = translation;
    
    return morse;
}

char* charToMorse(char c) {
    
    char* code = "";
    
    switch (c)
    {
        /* space */
        case ' ':
            code = " / ";
            break;
        
        /* all letters of the latin alphabet */
        case 'a':
        case 'A':
            code = ".-";
            break;
        case 'b':
        case 'B':
            code = "-...";
            break;
        case 'c':
        case 'C':
            code = "-.-.";
            break;
        case 'd':
        case 'D':
            code = "-..";
            break;
        case 'e':
        case 'E':
            code = ".";
            break;
        case 'f':
        case 'F':
            code = "..-.";
            break;
        case 'g':
        case 'G':
            code = "--.";
            break;
        case 'h':
        case 'H':
            code = "....";
            break;
        case 'i':
        case 'I':
            code = "..";
            break;
        case 'j':
        case 'J':
            code = ".---";
            break;
        case 'k':
        case 'K':
            code = "-.-";
            break;
        case 'l':
        case 'L':
            code = ".-..";
            break;
        case 'm':
        case 'M':
            code = "--";
            break;
        case 'n':
        case 'N':
            code = "-.";
            break;
        case 'o':
        case 'O':
            code = "---";
            break;
        case 'p':
        case 'P':
            code = ".--.";
            break;
        case 'q':
        case 'Q':
            code = "--.-";
            break;
        case 'r':
        case 'R':
            code = ".-.";
            break;
        case 's':
        case 'S':
            code = "...";
            break;
        case 't':
        case 'T':
            code = "-";
            break;
        case 'u':
        case 'U':
            code = "..-";
            break;
        case 'v':
        case 'V':
            code = "...-";
            break;
        case 'w':
        case 'W':
            code = ".--";
            break;
        case 'x':
        case 'X':
            code = "-..-";
            break;
        case 'y':
        case 'Y':
            code = "-.--";
            break;
        case 'z':
        case 'Z':
            code = "--..";
            break;
        
        /* numbers */
        case '0':
            code = "-----";
            break;
        case '1':
            code = ".----";
            break;
        case '2':
            code = "..---";
            break;
        case '3':
            code = "...--";
            break;
        case '4':
            code = "....-";
            break;
        case '5':
            code = ".....";
            break;
        case '6':
            code = "-....";
            break;
        case '7':
            code = "--...";
            break;
        case '8':
            code = "---..";
            break;
        case '9':
            code = "----.";
            break;
        
        /* symbols */
        case '.':
            code = ".-.-.-";
            break;
        case ',':
            code = "--..--";
            break;
        case '?':
            code = "..--..";
            break;
        case '\'':
            code = ".----.";
            break;
        case '!':
            code = "-.-.-----.";
            break;
        case '/':
            code = "-..-.";
            break;
        case '(':
            code = "-.--.";
            break;
        case ')':
            code = "-.--.-";
            break;
        case '&':
            code = ".-...";
            break;
        case ':':
            code = "---...";
            break;
        case ';':
            code = "-.-.-.";
            break;
        case '=':
            code = ".---.";
            break;
        case '+':
            code = ".-.-.";
            break;
        case '-':
            code = "-....-";
            break;
        case '_':
            code = "..--.-";
            break;
        case '"':
            code = ".-..-.";
            break;
        case '$':
            code = "...-..-";
            break;
        case '@':
            code = ".--.-.";
            break;
        default:
            break;
    }
    
    return code;
}


/* [] END OF FILE */
