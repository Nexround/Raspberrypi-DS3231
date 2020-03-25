#include <stdio.h>
#include "ds3231lib.h"

int main(int argc, char **argv)
{
	fd = DS3231_Init();
	if (fd)
	{	
		ByteData();
		TimeOutput(2);
		TemperatureOutput();
	}
	else
		printf("Failed to Connect!");
 	return 0;
}
