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
#include "soundhandler.h"

double vector[100];

/* fill the global variable "vector" with values of a sinus */
void initVector (void) {
    for (int i = 0; i < 100; i++){
        vector[i] = sin( ((i * 3.6) * (PI/180) ) );
    }
}

/* return the value of the TC bit of the timer */
int getTC (void) {
    return 0x80 & Timer_ReadStatusRegister(); // mask
}

/* set the value for the VDAC to the jth element of
   the global variable vector adapted to be within
   the range excepted by the VDAC_SetValue function */
void setVDACvalue (int j) {
    int result = (vector[j] * 128) + 128;
    if (result >= 256) {
        result = 255; // result in [0,255]
    }
    VDAC_SetValue(result);
}

/* [] END OF FILE */
