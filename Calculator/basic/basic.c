/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_types.h"		// Added for integer type definitions
#include "seg7_display.h"	// Added for 7-segment definitions
#include "gpio_init.h"
#include "math.h"


int main()
{
    init_platform();

	int status;

    // Initialize the GPIOs
    status = initGpio();
	if (status != XST_SUCCESS) {
		printf("GPIOs initialization failed!\n\r");
		cleanup_platform();
		return 0;
	}

	// Setup the Interrupt System
	status = setUpInterruptSystem();
	if (status != XST_SUCCESS) {
		printf("Interrupt system setup failed!\n\r");
		cleanup_platform();
		return 0;
	}

	// Declare and define required variables
	float operand1 = 0.0;
	float operand2 = 0.0;
	u16 method = 0;
	float output = 0.0;


	while (1)
	{

		// Read the input operands
		operand1 = XGpio_DiscreteRead(&SLIDE_SWITCHES,1)%64;
		operand2 = (XGpio_DiscreteRead(&SLIDE_SWITCHES,1)/64)%64;

		// Read the input method
		method = XGpio_DiscreteRead(&SLIDE_SWITCHES,1)/4096;

		//Implement calculation
		switch(method){
			case 1:		//add
				output = operand1 + operand2;
				break;
			case 2:		//minus
				output = operand1 - operand2;
				break;
			case 4:		//multiply
				output = operand1 * operand2;
				break;
			case 8:		//divide
				output = operand1 / operand2;
				break;
			//extra
			case 3:		//root
				output = pow(operand1, 1.0/operand2);
				break;
			default:
				output = 0.0;
				break;
		}

		// Call the method to display output on decoder
		displayNumber(output);
		// Call the method to display output on LEDS
		XGpio_DiscreteWrite(&LED_OUT, 1, output);

	}

    cleanup_platform();
    return 0;
}
