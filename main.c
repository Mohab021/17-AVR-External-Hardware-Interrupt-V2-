
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "AVR_Ports.h"
#include "AVR_GPIO_Declarations.h"
#include "avr/interrupt.h" //this Library is for Vectored Interrupt

int main(void)
{
	Pin_Direction(C, 2, input); //Input SW to turn on all LEDs
	Pin_Direction(D, 2, input); //Input for Interrupt 0
	Pin_Direction(D, 3, input); //Input for Interrupt 1
	Pin_Direction(B, 2, input); //Input for Interrupt 2
	Pin_Direction(B, 0, output); //LED0 output
	Pin_Direction(A, 2, output); //LED1 output
	Pin_Direction(A, 3, output); //LED2 output

	GICR |= (1<<INT0) | (1<<INT1) | (1<<INT2); //Set all three Interrupt Pins (0b11100000)
	MCUCR |= (1<<ISC10); //Write 1 to ISC10 (sense control for any logical change on INT1), Write 0 to all ISC00, ISC01, ISC11 (sense control for low level on INT0)
	MCUCSR |= (1<<ISC2); //Write 1 to ISC2 (sense control for rising edge on INT2)
	sei(); //Set Global Interrupt = 1

	while(1)
	{
		if(Pin_Read(C, 2) == 0) //pin is connected to ground (SW-ON)
		{
			Pin_Set(B, 0); //Set LED0
			Pin_Set(A, 2); //Set LED1
			Pin_Set(A, 3); //Set LED2
		}
	}
}

//Interrupt Service Routine for Interrupt 0
ISR(INT0_vect) //Default event for interrupting = when sense low level on INT0
{
	Pin_Reset(B,0); //Reset LED0 immediately
	_delay_ms(50); //Software de-bouncing control delay to avoid multiple occurrences of an interrupt at the same time
}

//Interrupt Service Routine for Interrupt 1
ISR(INT1_vect) //Default event for interrupting = when sense any logical change on INT1
{
	Pin_Reset(A,2); //Reset LED1 immediately
	_delay_ms(50); //Software de-bouncing control delay to avoid multiple occurrences of an interrupt at the same time
}

//Interrupt Service Routine for Interrupt 2
ISR(INT2_vect) //Default event for interrupting = when sense rising edge on INT2
{
	Pin_Reset(A,3); //Reset LED2 immediately
	_delay_ms(50); //Software de-bouncing control delay to avoid multiple occurrences of an interrupt at the same time
}
