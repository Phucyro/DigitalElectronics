/*******************************************************************************
* File Name: LCD_Screen_PM.c
* Version 2.20
*
* Description:
*  This file provides the API source code for the Static Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_Screen.h"


static LCD_Screen_BACKUP_STRUCT LCD_Screen_backup;


/*******************************************************************************
* Function Name: LCD_Screen_SaveConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Screen_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_Screen_RestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Screen_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_Screen_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Screen_Sleep(void) 
{
    LCD_Screen_backup.enableState = LCD_Screen_enableState;
    LCD_Screen_SaveConfig();
    LCD_Screen_Stop();
}


/*******************************************************************************
* Function Name: LCD_Screen_Wakeup
********************************************************************************
*
* Summary:
*  Wakes the component from sleep mode. Configures DMA and enables the component
*  for normal operation.
*
* Parameters:
*  LCD_Screen_enableState - Global variable.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - Function completed successfully.
*       CYRET_LOCKED - The object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Screen_Wakeup(void) 
{
    LCD_Screen_RestoreConfig();

    if(LCD_Screen_backup.enableState == 1u)
    {
        LCD_Screen_Enable();
    }
}


/* [] END OF FILE */
