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

#include "lighter.h"

/* switches all the LEDs to on if they were off
   and reciprocally */
void toggleAllLights (void) {
    Pin_D1_Write ( ~Pin_D1_Read() );
    Pin_D2_Write ( ~Pin_D2_Read() );
    Pin_D3_Write ( ~Pin_D3_Read() );
    Pin_D4_Write ( ~Pin_D4_Read() );
}

/* [] END OF FILE */
