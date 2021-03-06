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
#include "xuartps.h"
#include "xparameters.h"
#include "xgpio.h"
#include<stdlib.h>
#include "xtime_l.h"




#define GPIO_CHANNEL 1
#define setBit(reg,bit)  reg |=(1<<bit)
#define setBits(regg,bit)  regg |=(1<<bit)
#define PORTB  *((u16*)0x20)
#define PORTA  *((u16*)0x0A)
#define ledG  0x3
#define ledY 0x5
#define  ledR 0x6
#define clock_freq 50000000 //system clock freq
#define desired_freq 1 //1hz


/*functions prototyping*/
void displayi(u16* reg ,u16 num );
void displayj(u16* reg ,u16 num );


int div_value = clock_freq/(2* desired_freq) - 1; // count/sec

void delay(int tm){ //delay function /ms
	int k,l;
	for (k=0;k<tm;k++)
	for(l=0; l<(div_value/1000) ;l++); //1275 //24999999 for 1hz,
}



/*main function*/

int main(void)
{

	XTime start, end; // to measure the precision of countdown clock

	init_platform();
	print("Initializing....\n\r");

    XGpio seg;
        int xStatus = XGpio_Initialize(&seg,XPAR_AXI_GPIO_0_DEVICE_ID);
        if(XST_SUCCESS != xStatus) {
            print("Failed to initialize ssd GPIO");
        }
        XGpio_SetDataDirection(&seg, GPIO_CHANNEL, 0x0000);//set segment pins as output

    XGpio led;
        int yStatus = XGpio_Initialize(&led,XPAR_AXI_GPIO_1_DEVICE_ID);
        if(XST_SUCCESS != yStatus) {
            print("Failed to initialize led GPIO");
        }
        XGpio_SetDataDirection(&led, GPIO_CHANNEL, 0x0);//set led pins as output


    void display_number(int number){
        	unsigned char seg_code[]={0, 1, 2, 3, 4, 5, 6, 7,8,9};
        	unsigned char temp;
        	int m, num;

        	for(m=0;m<100;m++){//counts up to 99
        		num=number;
        		temp=num/10;

        		//tens display value
        		displayj(&PORTA,seg_code[temp]);
        		XGpio_DiscreteWrite(&seg,GPIO_CHANNEL,PORTA);
        		delay(10);//display

        		//ones display value
        		temp =num%10;
        		displayi(&PORTB,seg_code[temp]);
        		XGpio_DiscreteWrite(&seg,GPIO_CHANNEL,PORTB);
        		delay(10);//display
        	}

        }




     int cnt;
     void control_display(int sec,  u8 led_value ){
    	 // u8 led_value
        	XGpio_DiscreteWrite(&led, GPIO_CHANNEL, led_value);
        	// Code to control display
        	for(cnt=sec; cnt>=0; cnt--){
        	    display_number(cnt);
        	    	}
        }




    while(1)

    {
    	//red light and countdown timer
    	XTime_GetTime(&start);
    	control_display(60, ledR);
    	XTime_GetTime(&end);

    	printf("RED Output took %llu clock cycles.\n", 2*(end - start));
    	printf("Output took %.2f ms.\n",
    			1.0 * (end - start) / (COUNTS_PER_SECOND/1000));

    	//delay(10);

    	//green light and countdown timer
    	XTime_GetTime(&start);
    	control_display(60, ledG);
    	XTime_GetTime(&end);
    	printf("GREEN Output took %llu clock cycles.\n", 2*(end - start));
    	printf("Output took %.2f ms.\n",
    	    			1.0 * (end - start) / (COUNTS_PER_SECOND/1000));

    	//delay(10);

    	//yellow light and countdown timer
    	XTime_GetTime(&start);
    	control_display(05, ledY);
    	XTime_GetTime(&end);
    	printf("YELLOW Output took %llu clock cycles.\n", 2*(end - start));
    	printf("Output took %.2f ms.\n",
    	    	    			1.0 * (end - start) / (COUNTS_PER_SECOND/1000));
    	//delay(10);

    }


    return 0;
}







/*
 * This is a function which:
 *   >>takes address of output register and num required to be displayed
 *   >>outputs value on register according to required number and 7-segment configuration
 *   S3 S2 S1 gfedcba >>pin configuration
 */



//display for ones(right ssd)
void displayi(u16* reg,u16 num)
{
	switch(num)                   /*check on required number to choose the right case*/
	{
			case 0:
				*reg=0b1101000000;      /*assign this output to the value of given register*/
				break;
			case 1:
				*reg=0b1101111001;
				break;
			case 2:
				*reg=0b1100100100;
				break;
			case 3:
				*reg=0b1100110000;
				break;
			case 4:
				*reg=0b1100011001;
				break;
			case 5:
				*reg=0b1100010010;
				break;
			case 6:
				*reg=0b1100000010;
				break;
			case 7:
				*reg=0b1101111000;
				break;
			case 8:
				*reg=0b1100000000;
				break;
			case 9:
				*reg=0b1100010000;
				break;
			default:
				*reg=0b1100010000;
				break;
	}
}




//display for tens(left ssd)
void displayj(u16* reg, u16 num)
{
	switch(num)                   //check on required number to choose the right case//
	{
	case 0:
					*reg=0b1011000000;      /*assign this output to the value of given register*/
					break;
				case 1:
					*reg=0b1011111001;
					break;
				case 2:
					*reg=0b1010100100;
					break;
				case 3:
					*reg=0b1010110000;
					break;
				case 4:
					*reg=0b1010011001;
					break;
				case 5:
					*reg=0b1010010010;
					break;
				case 6:
					*reg=0b1010000010;
					break;
				case 7:
					*reg=0b1011111000;
					break;
				case 8:
					*reg=0b1010000000;
					break;
				case 9:
					*reg=0b1010010000;
					break;
				default:
					*reg=0b1010010010;
					break;
	}
}




