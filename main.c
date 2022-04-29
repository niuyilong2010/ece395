#include "LPC11xx.h"
#include <stdio.h>
#include <rt_misc.h>

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
}

void ledOn()
{
	LPC_GPIO0->DATA &= ~(1<<7);
	LPC_GPIO0->DATA &= ~(1<<4); //also make a step
}

void ledOff()
{						 
	LPC_GPIO0->DATA |= (1<<7);
	LPC_GPIO0->DATA |= (1<<4); //also make a step
}

int main()
{
	int i, j = 0;
	SER_init();
	configureGPIO();
	LPC_GPIO0->DATA |= (1<<9); //en = 1
	LPC_GPIO0->DATA |= (1<<8); //dir = 1
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
			char a[4];
			a[0] = getkey();
			a[1] = getkey();
			a[2] = getkey();
			a[3] = getkey();
			(void)sendchar((int)a[0]);
			(void)sendchar((int)a[1]);
			int step_count = (int)a[0] + ((int)a[1] << 4);
			int dir = a[2] & 0x1;
			LPC_GPIO0->DATA |= (1<<9); //en = 1
			for (i = 0; i < 0x0008FFF; i++) {}
			if (dir == 1) {
				LPC_GPIO0->DATA |= (1<<8);
			} else {
				LPC_GPIO0->DATA &= ~(1<<8);
			}
			for (i = 0; i < 0x0008FFF; i++) {}
			for (j = 0 ; j < step_count; j++) {
				ledOff();
				//printf("Led Off, Iteration %d\n\r", j);
				//for (i = 0; i < 0x000FFFFF; i++)
				for (i = 0; i < 0x00000FFF; i++)
				{
				}
				ledOn();
				//printf("Led On, Iteration %d\n\r", j);
				//for (i = 0; i < 0x00000FFF; i++)
				for (i = 0; i < 0x00000FFF; i++)
				{
				}
			}
	}
}
