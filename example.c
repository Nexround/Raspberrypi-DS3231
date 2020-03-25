#include <stdio.h>
#include "ds3231lib.h"

int main(int argc, char **argv)
{
	fd = DS3231_Init();
	if (fd)
	{	
		//in TimeOutput function,you have 3 choices(from 1 to 3) to decide how to display the info from DS3231.
		//case 1 : YYYY/MM/DD 
		//case 2 : HH:MM:SS (AM/PM)
		//case 3 : YYYY/MM/DD DoW HH:MM:SS (AM/PM) 
		TimeOutput(3);

		//temperature is represented as a 10-bit code with a resolution of +0.25°C.
		//The temperature is read on initial application of VCCand once every 64 seconds afterwards.
		//this function can set the CONV bit to 1 forces the temperature sensor to convert the temperature into digital code and execute the TCXO algorithmto update the capacitance array to the oscillator.
		TemperatureOutput();

		//to use specific data,you need to run FormatTime() function,then you can use struct Clock which includes every single data read from DS3231 registers.
		FormatTime();
		printf("%d %d %d %d %d %d %d\n", Clock.year, Clock.month, Clock.date, Clock.day, Clock.hour, Clock.min, Clock.sec);
	}
	else
		printf("Failed to Connect!");
 	return 0;
}
