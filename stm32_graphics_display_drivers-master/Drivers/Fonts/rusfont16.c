/**
  ******************************************************************************
  * @file    font16.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file provides text font16 for STM32xx-EVAL's LCD driver. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fonts.h"

/** @addtogroup Utilities
  * @{
  */
  
/** @addtogroup STM32_EVAL
  * @{
  */ 

/** @addtogroup Common
  * @{
  */

/** @addtogroup FONTS
  * @brief      This file provides text font16 for STM32xx-EVAL's LCD driver.
  * @{
  */  

/** @defgroup FONTS_Private_Types
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup FONTS_Private_Defines
  * @{
  */
/**
  * @}
  */ 


/** @defgroup FONTS_Private_Macros
  * @{
  */
/**
  * @}
  */ 
  

/** @defgroup FONTS_Private_Variables
  * @{
  */
// 
//  Font data for Courier New 12pt
// 

const uint8_t RuFont16_Table[] = 
{
	// @0 ' ' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @32 '!' (11 pixels wide)
	0x00, 0x00, //            
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x00, 0x00, //            
	0x0C, 0x00, //     ##     
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @64 '"' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x1D, 0xC0, //    ### ### 
	0x1D, 0xC0, //    ### ### 
	0x08, 0x80, //     #   #  
	0x08, 0x80, //     #   #  
	0x08, 0x80, //     #   #  
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @96 '#' (11 pixels wide)
	0x00, 0x00, 0x38, 0x00, 0x08, 0x00, 0x08, 0x00, 0x0f, 0x80, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 
0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x08, 

	// @128 '$' (11 pixels wide)
	0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 
0x21, 0x08, 0x3f, 0xfc, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @160 '%' (11 pixels wide)
	0x78, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x0f, 0xe0, 0x08, 0x30, 0x08, 0x10, 
0x08, 0x10, 0x08, 0x30, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @192 '&' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x10, 0x11, 0x10, 0x11, 0x10, 0x11, 0x10, 
0x11, 0x10, 0x11, 0x10, 0x11, 0x10, 0x1f, 0xf8, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00,  

	// @224 ''' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x07, 0x00, //      ###   
	0x07, 0x00, //      ###   
	0x02, 0x00, //       #    
	0x02, 0x00, //       #    
	0x02, 0x00, //       #    
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @256 '(' (11 pixels wide)
	0x00, 0x00, //            
	0x03, 0x00, //       ##   
	0x03, 0x00, //       ##   
	0x06, 0x00, //      ##    
	0x0E, 0x00, //     ###    
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0E, 0x00, //     ###    
	0x06, 0x00, //      ##    
	0x03, 0x00, //       ##   
	0x03, 0x00, //       ##   
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @288 ')' (11 pixels wide)
	0x00, 0x00, //            
	0x18, 0x00, //    ##      
	0x18, 0x00, //    ##      
	0x0C, 0x00, //     ##     
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x0C, 0x00, //     ##     
	0x1C, 0x00, //    ###     
	0x18, 0x00, //    ##      
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @320 '*' (11 pixels wide)
	0x00, 0x00, //            
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x3F, 0xC0, //   ######## 
	0x3F, 0xC0, //   ######## 
	0x0F, 0x00, //     ####   
	0x1F, 0x80, //    ######  
	0x19, 0x80, //    ##  ##  
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @352 '+' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x04, 0x00, //      #     
	0x04, 0x00, //      #     
	0x04, 0x00, //      #     
	0x3F, 0x80, //   #######  
	0x04, 0x00, //      #     
	0x04, 0x00, //      #     
	0x04, 0x00, //      #     
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @384 ',' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x06, 0x00, //      ##    
	0x04, 0x00, //      #     
	0x0C, 0x00, //     ##     
	0x08, 0x00, //     #      
	0x08, 0x00, //     #      
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @416 '-' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x3F, 0x80, //   #######  
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @448 '.' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @480 '/' (11 pixels wide)
	0x00, 0xC0, //         ## 
	0x00, 0xC0, //         ## 
	0x01, 0x80, //        ##  
	0x01, 0x80, //        ##  
	0x03, 0x00, //       ##   
	0x03, 0x00, //       ##   
	0x06, 0x00, //      ##    
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x18, 0x00, //    ##      
	0x18, 0x00, //    ##      
	0x30, 0x00, //   ##       
	0x30, 0x00, //   ##       
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @512 '0' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3e, 0x20, 0x21, 0x20, 0x21, 0x20, 
0x21, 0x20, 0x3e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @544 '1' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x3e, 0x00, 0x21, 0x00, 0x21, 0x00, 
0x21, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @576 '2' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x23, 0x00, 0x01, 0x00, 0x0f, 0x00, 0x01, 0x00, 0x01, 0x00, 
0x23, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @608 '3' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0xe0, 0x13, 0x30, 0x12, 0x10, 0x1e, 0x10, 0x12, 0x10, 
0x12, 0x10, 0x13, 0x30, 0x11, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @640 '4' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x0f, 0x00, 
0x11, 0x00, 0x31, 0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @672 '5' (11 pixels wide)
	0x20, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x08, 0x3f, 0x88, 0x20, 0x48, 0x20, 0x48, 
0x20, 0x48, 0x20, 0x48, 0x3f, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @704 '6' (11 pixels wide)
	0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x3f, 0x80, 0x20, 0x40, 0x20, 0x40, 
0x20, 0x40, 0x20, 0x40, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @736 '7' (11 pixels wide)
	0x00, 0x00, 0x0f, 0x00, 0x10, 0xc0, 0x20, 0x40, 0x00, 0x60, 0x00, 0x20, 0x03, 0xe0, 0x00, 0x20, 
0x00, 0x20, 0x20, 0x40, 0x30, 0xc0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @768 '8' (11 pixels wide)
	0x00, 0x00, 0x20, 0xf0, 0x21, 0x8c, 0x21, 0x04, 0x22, 0x06, 0x22, 0x02, 0x3e, 0x02, 0x22, 0x02, 
0x22, 0x06, 0x21, 0x04, 0x21, 0x8c, 0x20, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @800 '9' (11 pixels wide)
	0x00, 0x00, 0x1f, 0xc0, 0x30, 0x40, 0x20, 0x40, 0x20, 0x40, 0x30, 0x40, 0x0f, 0xc0, 0x0c, 0x40, 
0x18, 0x40, 0x10, 0x40, 0x30, 0x40, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	// @832 ':' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @864 ';' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x03, 0x00, //       ##   
	0x03, 0x00, //       ##   
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x06, 0x00, //      ##    
	0x04, 0x00, //      #     
	0x08, 0x00, //     #      
	0x08, 0x00, //     #      
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @896 '<' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0xC0, //         ## 
	0x03, 0x00, //       ##   
	0x04, 0x00, //      #     
	0x18, 0x00, //    ##      
	0x60, 0x00, //  ##        
	0x18, 0x00, //    ##      
	0x04, 0x00, //      #     
	0x03, 0x00, //       ##   
	0x00, 0xC0, //         ## 
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @928 '=' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x7F, 0xC0, //  ######### 
	0x00, 0x00, //            
	0x7F, 0xC0, //  ######### 
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @960 '>' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x60, 0x00, //  ##        
	0x18, 0x00, //    ##      
	0x04, 0x00, //      #     
	0x03, 0x00, //       ##   
	0x00, 0xC0, //         ## 
	0x03, 0x00, //       ##   
	0x04, 0x00, //      #     
	0x18, 0x00, //    ##      
	0x60, 0x00, //  ##        
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @992 '?' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x1F, 0x00, //    #####   
	0x31, 0x80, //   ##   ##  
	0x31, 0x80, //   ##   ##  
	0x01, 0x80, //        ##  
	0x07, 0x00, //      ###   
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x00, 0x00, //            
	0x0C, 0x00, //     ##     
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @1024 '@' (11 pixels wide)
	0x00, 0x00, //            
	0x0E, 0x00, //     ###    
	0x11, 0x00, //    #   #   
	0x21, 0x00, //   #    #   
	0x21, 0x00, //   #    #   
	0x27, 0x00, //   #  ###   
	0x29, 0x00, //   # #  #   
	0x29, 0x00, //   # #  #   
	0x27, 0x00, //   #  ###   
	0x20, 0x00, //   #        
	0x11, 0x00, //    #   #   
	0x0E, 0x00, //     ###    
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @1056 'A' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x07, 0x00, 0x05, 0x00, 0x0d, 0x80, 0x08, 0x80, 0x08, 0x80, 
0x18, 0xc0, 0x1f, 0xc0, 0x10, 0x40, 0x30, 0x60, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1088 'B' (11 pixels wide)
	0x00, 0x00, 0x3f, 0x80, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x3f, 0x80, 0x20, 0x40, 
0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1120 'C' (11 pixels wide)
	0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 
0x20, 0x40, 0x20, 0x40, 0x3f, 0xe0, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 

	// @1152 'D' (11 pixels wide)
	0x1f, 0x80, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 
0x30, 0x80, 0x20, 0x80, 0x7f, 0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 

	// @1184 'E' (11 pixels wide)
	0x00, 0x00, 0x3f, 0xc0, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x3f, 0x80, 0x20, 0x00, 
0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1216 'F' (11 pixels wide)
	0x01, 0x00, 0x07, 0xc0, 0x09, 0x20, 0x11, 0x10, 0x11, 0x10, 0x11, 0x10, 0x11, 0x10, 0x09, 0x20, 
0x07, 0xc0, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 

	// @1248 'G' (11 pixels wide)
	0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 
0x10, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x40, 

	// @1280 'H' (11 pixels wide)
	0x08, 0xc0, 0x08, 0x80, 0x05, 0x00, 0x07, 0x00, 0x02, 0x00, 0x05, 0x00, 0x0d, 0x80, 0x08, 0x80, 
0x10, 0x40, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1312 'I' (11 pixels wide)
	0x20, 0x60, 0x20, 0xe0, 0x20, 0xa0, 0x21, 0x20, 0x20, 0x20, 0x22, 0x20, 0x24, 0x20, 0x24, 0x20, 
0x28, 0x20, 0x30, 0x20, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1344 'J' (11 pixels wide)
	0x61, 0x06, 0x11, 0x08, 0x19, 0x18, 0x09, 0x10, 0x0d, 0x30, 0x07, 0xe0, 0x0d, 0x30, 0x19, 0x18, 
0x31, 0x08, 0x21, 0x0c, 0x61, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1376 'K' (11 pixels wide)
	0x10, 0xe0, 0x11, 0x80, 0x11, 0x00, 0x11, 0x00, 0x13, 0x00, 0x1c, 0x00, 0x13, 0x00, 0x11, 0x00, 
0x10, 0x80, 0x10, 0xc0, 0x10, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1408 'L' (11 pixels wide)
	0x0f, 0xe0, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 
0x08, 0x20, 0x08, 0x20, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1440 'M' (11 pixels wide)
	0x00, 0x00, 0x18, 0x30, 0x18, 0x30, 0x18, 0x30, 0x14, 0x50, 0x14, 0x50, 0x10, 0x10, 0x12, 0x90, 
0x12, 0x90, 0x12, 0x90, 0x11, 0x10, 0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1472 'N' (11 pixels wide)
	0x00, 0x00, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x1f, 0xe0, 0x10, 0x20, 
0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1504 'O' (11 pixels wide)
	0x00, 0x00, 0x07, 0x80, 0x18, 0x60, 0x10, 0x20, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 
0x20, 0x10, 0x10, 0x20, 0x18, 0x60, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1536 'P' (11 pixels wide)
	0x00, 0x00, 0x1f, 0xe0, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 
0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1568 'Q' (11 pixels wide)
	0x00, 0x00, 0x10, 0x40, 0x10, 0x40, 0x10, 0x40, 0x10, 0x40, 0x10, 0x40, 0x18, 0xc0, 0x0f, 0xc0, 
0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1600 'R' (11 pixels wide)
	0x00, 0x00, 0x3f, 0x80, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x20, 0xc0, 0x3f, 0x80, 0x20, 0x00, 
0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1632 'S' (11 pixels wide)
	0x00, 0x00, 0x07, 0x80, 0x18, 0x40, 0x30, 0x20, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 
0x20, 0x20, 0x10, 0x20, 0x18, 0x40, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1664 'T' (11 pixels wide)
	0x00, 0x00, 0x7f, 0xc0, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 
0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1696 'U' (11 pixels wide)
	0x00, 0x00, 0x20, 0x60, 0x20, 0x40, 0x10, 0xc0, 0x18, 0x80, 0x09, 0x80, 0x0d, 0x00, 0x07, 0x00, 
0x06, 0x00, 0x02, 0x00, 0x04, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1728 'V' (11 pixels wide)
	0x00, 0x00, 0x3f, 0x00, 0x20, 0x80, 0x20, 0x80, 0x20, 0x80, 0x20, 0x80, 0x3f, 0x80, 0x20, 0xc0, 
0x20, 0x40, 0x20, 0x40, 0x20, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1760 'W' (11 pixels wide)
	0x00, 0x00, 0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 
0x21, 0x08, 0x21, 0x08, 0x21, 0x08, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x04, 0x80, 0x07, 0x00, 

	// @1792 'X' (11 pixels wide)
	0x00, 0x00, 0x20, 0x60, 0x20, 0xe0, 0x20, 0xa0, 0x21, 0x20, 0x20, 0x20, 0x22, 0x20, 0x24, 0x20, 
0x24, 0x20, 0x28, 0x20, 0x30, 0x20, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1824 'Y' (11 pixels wide)
	0x09, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x3f, 0x80, 
0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @1856 'Z' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x18, 0x80, 0x10, 0x80, 0x00, 0x80, 0x00, 0x80, 0x03, 0x00, 
0x00, 0xc0, 0x00, 0x40, 0x10, 0x40, 0x18, 0xc0, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	// @1888 '[' (11 pixels wide)
	0x00, 0x00, //            
	0x07, 0x80, //      ####  
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x07, 0x80, //      ####  
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @1920 '\' (11 pixels wide)
	0x30, 0x00, //   ##       
	0x30, 0x00, //   ##       
	0x18, 0x00, //    ##      
	0x18, 0x00, //    ##      
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x06, 0x00, //      ##    
	0x03, 0x00, //       ##   
	0x03, 0x00, //       ##   
	0x01, 0x80, //        ##  
	0x01, 0x80, //        ##  
	0x00, 0xC0, //         ## 
	0x00, 0xC0, //         ## 
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @1952 ']' (11 pixels wide)
	0x00, 0x00, //            
	0x1E, 0x00, //    ####    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x1E, 0x00, //    ####    
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @1984 '^' (11 pixels wide)
	0x04, 0x00, //      #     
	0x0A, 0x00, //     # #    
	0x0A, 0x00, //     # #    
	0x11, 0x00, //    #   #   
	0x20, 0x80, //   #     #  
	0x20, 0x80, //   #     #  
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @2016 '_' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0xFF, 0xE0, // ###########

	// @2048 '`' (11 pixels wide)
	0x08, 0x00, //     #      
	0x04, 0x00, //      #     
	0x02, 0x00, //       #    
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @2080 'a' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x10, 0x80, 0x00, 0x80, 0x07, 0x80, 
0x18, 0x80, 0x10, 0x80, 0x11, 0x80, 0x1e, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2112 'b' (11 pixels wide)
	0x0f, 0x80, 0x10, 0x00, 0x20, 0x00, 0x2e, 0x00, 0x31, 0x00, 0x20, 0x80, 0x20, 0x80, 0x20, 0x80, 
0x20, 0x80, 0x11, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2144 'c' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 
0x21, 0x00, 0x21, 0x00, 0x3f, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2176 'd' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 
0x21, 0x00, 0x21, 0x00, 0x7f, 0x80, 0x40, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2208 'e' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x18, 0x80, 0x10, 0x80, 0x1f, 0x80, 0x10, 0x00, 
0x10, 0x00, 0x18, 0x80, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2240 'f' (11 pixels wide)
	0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x3f, 0x80, 0x4e, 0xc0, 0x44, 0x40, 0x44, 0x40, 0x44, 0x40, 0x44, 0x40, 
0x4e, 0xc0, 0x3f, 0x80, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2272 'g' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 
0x10, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2304 'h' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x1b, 0x00, 0x0a, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x0a, 0x00, 0x11, 0x00, 
0x31, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 

	// @2336 'i' (11 pixels wide)
	0x00, 0x00,  0x00, 0x00, 0x21, 0x00, 0x23, 0x00, 0x21, 0x00, 0x21, 0x00, 0x29, 0x00, 0x21, 0x00, 0x31, 0x00, 0x21, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2368 'j' (11 pixels wide)
	0x00, 0x00,0x64, 0xc0, 0x24, 0x80, 0x15, 0x00, 0x0e, 0x00, 0x15, 0x00, 0x24, 0x80, 0x24, 0x80, 0x44, 0x40, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  

	// @2400 'k' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x23, 0x00,0x24, 0x00, 0x2c, 0x00, 0x38, 0x00, 0x2c, 0x00, 0x24, 0x00, 0x22, 0x00, 0x23, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  

	// @2432 'l' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x61, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2464 'm' (11 pixels wide)
	0x00, 0x00,0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 0x29, 0x40, 0x29, 0x40, 0x26, 0x40, 0x26, 0x40, 0x24, 0x40, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2496 'n' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00,0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x3f, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   

	// @2528 'o' (11 pixels wide)
	0x00,  0x00, 0x00, 0x00,0x1e, 0x00,0x33, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x33, 0x00, 0x1e, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2560 'p' (11 pixels wide)
	0x3f, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 

	// @2592 'q' (11 pixels wide)
	0x00, 0x00,0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x31, 0x00, 0x1f, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  

	// @2624 'r' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x33, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x21, 0x00, 0x33, 0x00, 0x2e, 0x00, 
0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2656 's' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x32, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 
0x33, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2688 't' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 
0x08, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2720 'u' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x61, 0x00, 0x22, 0x00, 0x22, 0x00, 0x12, 0x00, 0x14, 0x00, 0x14, 0x00, 
0x0c, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2752 'v' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x21, 0x00, 0x21, 0x00, 0x3e, 0x00, 0x21, 0x00, 
0x21, 0x00, 0x21, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2784 'w' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x40, 0x44, 0x40, 0x44, 0x40, 0x44, 0x40, 0x44, 0x40, 
0x44, 0x40, 0x44, 0x40, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2816 'x' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x21, 0x00, 0x23, 0x00, 0x21, 0x00, 
0x21, 0x00, 0x29, 0x00, 0x21, 0x00, 0x31, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2848 'y' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x31, 0x00, 0x21, 0x00, 
0x3f, 0x00, 0x20, 0x00, 0x20, 0x00, 0x31, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

	// @2880 'z' (11 pixels wide)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x22, 0x00, 0x02, 0x00, 
0x0c, 0x00, 0x02, 0x00, 0x02, 0x00, 0x22, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	// @2912 '{' (11 pixels wide)
	0x00, 0x00, //            
	0x06, 0x00, //      ##    
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x18, 0x00, //    ##      
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x0C, 0x00, //     ##     
	0x06, 0x00, //      ##    
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @2944 '|' (11 pixels wide)
	0x00, 0x00, //            
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @2976 '}' (11 pixels wide)
	0x00, 0x00, //            
	0x0C, 0x00, //     ##     
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x03, 0x00, //       ##   
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x06, 0x00, //      ##    
	0x0C, 0x00, //     ##     
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            

	// @3008 '~' (11 pixels wide)
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x18, 0x00, //    ##      
	0x24, 0x80, //   #  #  #  
	0x03, 0x00, //       ##   
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
	0x00, 0x00, //            
};

sFONT RuFont16 = {
  RuFont16_Table,
  11, /* Width */
  16, /* Height */
};

/**
  * @}
  */ 


/** @defgroup FONTS_Private_Function_Prototypes
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup FONTS_Private_Functions
  * @{
  */
    
/**
  * @}
  */
  
/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/*P.S.
python code for conerting is below:

font_dict = {
    'ъ':'#',    
    'Щ':'$',
    'Ъ':'%',
    'щ':'&',
    
    'ы':'0',
    'ь':'1',
    'э':'2',
    'ю':'3',
    'я':'4',
    'Ы':'5',
    'Ь':'6',
    'Э':'7',
    'Ю':'8',
    'Я':'9',

    'А':'A',
    'Б':'B',
    'Ц':'C',
    'Д':'D',
    'Е':'E',
    'Ф':'F',
    'Г':'G',
    'Х':'H',
    'И':'I',
    'Ж':'J',
    'К':'K',
    'Л':'L',
    'М':'M',
    'Н':'N',
    'О':'O',
    'П':'P',
    'Ч':'Q',
    'Р':'R',
    'С':'S',
    'Т':'T',
    'У':'U',    
    'В':'V',
    'Ш':'W',
    'Й':'X',
    'Ё':'Y',
    'З':'Z',

    'а':'a',
    'б':'b',
    'ц':'c',    
    'д':'d',
    'е':'e',
    'ф':'f',
    'г':'g',
    'х':'h',
    'и':'i',    
    'ж':'j',
    'к':'k',
    'л':'l',
    'м':'m',
    'н':'n',
    'о':'o',
    'п':'p',
    'ч':'q',
    'р':'r',
    'с':'s',
    'т':'t',
    'у':'u',
    'в':'v',
    'ш':'w',   
    'й':'x',    
    'ё':'y',
    'з':'z',

    ' ':' ',
    '.':'.',
    ',':',',
    ':':':',
    ';':';',
    '!':'!',
    '?':'?'    
    }


while(1):
    print('type:')
    inp = input()
    if inp == 'q':
        break
    outp = ''

    for s in inp:
        outp = outp + font_dict[s]

    print('converted:')
    print(outp)
    }


while(1):
    print('type:')
    inp = input()
    if inp == 'q':
        break
    outp = ''

    for s in inp:
        outp = outp + font_dict[s]

    print('converted:')
    print(outp)
*/

