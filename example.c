#include <stdio.h>
#include "ds3231lib.h"

int main(int argc, char **argv)
{
	fd = DS3231_Init();
	if (fd)
	{	
		//in TimeOutput function,you have 3 choices(from 1 to 3) to decide how to display the info from DS3231.
		TimeOutput(3);
		//case 1 : YYYY/MM/DD 
		//case 2 : HH:MM:SS (AM/PM)
		//case 3 : YYYY/MM/DD DoW HH:MM:SS (AM/PM) 
		TemperatureOutput();
	}
	else
		printf("Failed to Connect!");
 	return 0;
}
