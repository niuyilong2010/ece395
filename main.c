#include "LPC11xx.h"
#include <stdio.h>
#include <rt_misc.h>
#define PULSE_WIDTH 0x00004FFF
#define PULSE_WIDTH_BOT	0x0000FFFF

/* Import external functions from Serial.c file                               */
extern void SER_init (void);

void configureGPIO()
{
	//Enable CLKOUT
	/*
	LPC_IOCON->PIO0_1 &= ~0x3F; // Select clkout function for P0.1
	LPC_IOCON->PIO0_1 |= 0x01;
	LPC_SYSCON->CLKOUTCLKSEL = 0x00; // IRC: 0x00 System osci: 0x01 WTD: 0x02 Main clk: 0x03
	LPC_SYSCON->CLKOUTUEN = 0x01; // Update clock
	LPC_SYSCON->CLKOUTUEN = 0x00; // Toggle update register once
	LPC_SYSCON->CLKOUTUEN = 0x01;
	while ( !(LPC_SYSCON->CLKOUTUEN & 0x01) ); // Wait until updated
	LPC_SYSCON->CLKOUTDIV = 1; // Divided by 255
	*/

	//set port 0_7 to output (high current drain in LPC1114)
    LPC_GPIO0->DIR |= (1<<7);
	//set port 0_4 to output (high current drain in LPC1114)
    LPC_GPIO0->DIR |= (1<<4);
	//set port 0_8 to output (high current drain in LPC1114)
    LPC_GPIO0->DIR |= (1<<8);
	//set port 0_9 to output (high current drain in LPC1114)
    LPC_GPIO0->DIR |= (1<<9);
	//set port 0_3 to output (high current drain in LPC1114)
    LPC_GPIO0->DIR |= (1<<3);
	//set port 0_10 to output (high current drain in LPC1114)
    LPC_GPIO0->DIR |= (1<<5);
	//set port 0_11 to output (high current drain in LPC1114)
    LPC_GPIO0->DIR |= (1<<11);
		
		
	//set port 0_2 to input
    LPC_GPIO0->DIR &= ~(1<<2);
	//set port 0_1 to input
    LPC_GPIO0->DIR &= ~(1<<1);
}

void ledOn()
{
	LPC_GPIO0->DATA &= ~(1<<7);
}

void ledOff()
{
	LPC_GPIO0->DATA |= (1<<7);
}

void topOn()
{
	LPC_GPIO0->DATA &= ~(1<<4); //also make a step
}

void topOff()
{						 
	LPC_GPIO0->DATA |= (1<<4); //also make a step
}

void botOn()
{
	LPC_GPIO0->DATA &= ~(1<<3); //also make a step
}

void botOff()
{						 
	LPC_GPIO0->DATA |= (1<<3); //also make a step
}

int main()
{
	int i, j = 0;
	SER_init();
	configureGPIO();
	LPC_GPIO0->DATA |= (1<<9); //en = 1
	LPC_GPIO0->DATA |= (1<<8); //dir = 1
	LPC_GPIO0->DATA |= (1<<11); //en = 1
	LPC_GPIO0->DATA |= (1<<5); //dir = 1
	for (i = 0; i < 0x000FFFF; i++) {}
	/*while (1)
	{
		ledOn();
		printf("Led On, Iteration %d\n\r", j);
		for (i = 0; i < 0x00000FFF; i++)
		{
		}
		ledOff();
		printf("Led Off, Iteration %d\n\r", j);
		for (i = 0; i < 0x00000FFF; i++)
		{
		}
		j++;
	}*/
	while (1) {
			char a[8];
			a[0] = getkey();
			a[1] = getkey();
			a[2] = getkey();
			a[3] = getkey();
			a[4] = getkey();
			a[5] = getkey();
			a[6] = getkey();
			a[7] = getkey();
			int top_step_count = (int)a[0] + ((int)a[1] << 8);
			int bot_step_count = (int)a[4] + ((int)a[5] << 8);
			int top_dir = a[2] & 0x1;
			int bot_dir = a[6] & 0x1;
			LPC_GPIO0->DATA |= (1<<9); //en = 1
			LPC_GPIO0->DATA |= (1<<11); //en = 1
			for (i = 0; i < 0x0008FFF; i++) {}
			if (top_dir == 1) {
				LPC_GPIO0->DATA |= (1<<8);
			} else {
				LPC_GPIO0->DATA &= ~(1<<8);
			}
			if (bot_dir == 1) {
				LPC_GPIO0->DATA |= (1<<5);
			} else {
				LPC_GPIO0->DATA &= ~(1<<5);
			}
			for (i = 0; i < 0x0008FFF; i++) {}
			for (j = 0 ; j < top_step_count; j++) {
				
				// check limit switch
				if (!(LPC_GPIO0->DATA & (1<<2)) || !(LPC_GPIO0->DATA & (1<<1))) {
					ledOn();
					LPC_GPIO0->DATA &= ~(1<<9); //en = 0
					LPC_GPIO0->DATA &= ~(1<<11); //en = 0
					break;
				} else {
					ledOff();
				}
				
				
				if (bot_step_count > 0) {
					botOff();
				}
				topOff();
				for (i = 0; i < PULSE_WIDTH; i++)
				{
				}
				if (bot_step_count > 0) {
					botOn();
					bot_step_count--;
				}
				topOn();
				for (i = 0; i < PULSE_WIDTH; i++)
				{
				}
			}
			while (bot_step_count > 0) {
				
				// check limit switch
				if (!(LPC_GPIO0->DATA & (1<<2)) || !(LPC_GPIO0->DATA & (1<<1))) {
					ledOn();
					LPC_GPIO0->DATA &= ~(1<<9); //en = 0
					LPC_GPIO0->DATA &= ~(1<<11); //en = 0
					break;
				} else {
					ledOff();
				}
				
				
				botOff();
				for (i = 0; i < PULSE_WIDTH; i++)
				{
				}
				botOn();
				for (i = 0; i < PULSE_WIDTH; i++)
				{
				}
				bot_step_count--;
			}
			LPC_GPIO0->DATA &= ~(1<<9); //en = 0
			LPC_GPIO0->DATA &= ~(1<<11); //en = 0
			(void)sendchar((int)a[6]);
			(void)sendchar((int)bot_dir);
	}
}
