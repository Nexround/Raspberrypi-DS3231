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
	if (choose == 'y' || choose == 'Y')
	{	
		writeSysTimetoDS();
		printf("Done.\n");
	}
	else 
		return 0;
  return 0;
}