
#include "AVR_GPIO_Declarations.h"

void Port_Direction (char base, char state) //use DDRX
{
	if (state == output)
	*(volatile unsigned char *)(base+1) = 0xff; //1
	else
	*(volatile unsigned char *)(base+1) = 0x00; //0
}

void Pin_Direction (char base, char pin, char state) //use DDRX
{
	if (state == output)
	*(volatile unsigned char *)(base+1) |= (1<<pin); //1
	else
	*(volatile unsigned char *)(base+1) &= ~(1<<pin); //0
}

void Pin_Set (char base, char pin) //use PORTX
{
	*(volatile unsigned char *)(base+2) |= (1<<pin); //1
}

void Pin_Reset (char base, char pin) //use PORTX
{
	*(volatile unsigned char *)(base+2) &= ~(1<<pin); //0
}

char Port_Read (char base) //use PINX
{
	return *(volatile unsigned char *)(base);
}

void Port_Write (char base, char value) //use PORTX
{
	*(volatile unsigned char *)(base+2) = value;
}

char Pin_Read (char base, char pin) //use PINX
{
	unsigned char pin_value;
	pin_value = *(volatile unsigned char *)(base) & (1<<pin);
	
	if (pin_value) return 1;
	else return 0;
}

void Pin_Write (char base, char pin, char value) //use PORTX
{
	if(value == 1)
	{
		*(volatile unsigned char *)(base+2) |= (1<<pin); //1
	}
	else
	{
		*(volatile unsigned char *)(base+2) &= ~(1<<pin); //0
	}
}
