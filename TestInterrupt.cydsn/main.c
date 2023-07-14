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

CY_ISR( Pin_SW1_Handler )
{
    Pin_D1_Write( ~Pin_D1_Read() );
    CyDelay( 500 );
    
    Pin_SW1_ClearInterrupt();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    Pin_SW1_Int_StartEx( Pin_SW1_Handler );

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
