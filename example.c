#include <stdio.h>
#include "ds3231lib.h"

int main(int argc, char **argv)
{
	char choose;
	fd = DS3231_Init();
	if (fd)
	{	
		ByteData();
		TimeOutput(2);
		TemperatureOutput();
		
	}
	else
		printf("Failed to Connect!");

	printf("Do you want to write system time to DS3231?Y/N");
	scanf("%c", &choose);
	if (choose == 'y' || choose == 'Y')
	{	
		writeSysTimetoDS();
		printf("Done.\n");
	}
	else 
		return 0;
 	return 0;
}
