
#ifndef AVR_GPIO_DECLARATIONS_H_
#define AVR_GPIO_DECLARATIONS_H_

#include "AVR_Input_and_Output.h"

void Port_Direction (char base, char state);
void Pin_Direction (char base, char pin, char state);
void Pin_Set (char base, char pin);
void Pin_Reset (char base, char pin);
char Port_Read (char base);
void Port_Write (char base, char value);
char Pin_Read (char base, char pin);
void Pin_Write (char base, char pin, char value);

#endif /* AVR_GPIO_DECLARATIONS_H_ */