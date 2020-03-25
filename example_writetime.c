#include <stdio.h>
#include "ds3231lib.h"

int main()
{
  char choose;
  fd = DS3231_Init();
  if(fd)
  {
    printf("Do you want to write system time to DS3231? [Y/n]");
	  scanf("%c", &choose);
  }
	else
		printf("Failed to Connect!");
	if (choose == 'y' || choose == 'Y')
	{	
		//writeSysTimetoDS() function will synchronize DS3231's time with system time.
		//Attention: the time will be same as shell command "date",it won't care about the timezone.
		writeSysTimetoDS();
		printf("Done.\n");
	}
	else 
		return 0;
  return 0;
}