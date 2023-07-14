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
#include "lightsensor.h"

/* return 1 if the value mesured by the photoresistor is great
   because that would mean there is no ambient light ---
   constant RESISTOR_VALUE_IN_THE_DARK defines the value from
   which we consider the photoresistor is in the dark */
int isNight (void) {
    int result;
    int res_mV;
    
    AMux_Select(1); // Photoresistor selected
    
    ADC_DelSig_StartConvert();
    
    if ( ADC_DelSig_IsEndConversion( ADC_DelSig_WAIT_FOR_RESULT ) )
    {
        
        result = ADC_DelSig_GetResult32();
        res_mV = ADC_DelSig_CountsTo_mVolts(result);
    }


    if (res_mV > RESISTOR_VALUE_IN_THE_DARK)
        return 1;
    else
        return 0;
}

/* [] END OF FILE */
