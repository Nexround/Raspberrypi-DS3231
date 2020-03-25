#include "ds3231lib.h"

uint8_t REG_ADDRESSES[17] = {	DS3231_REG_SECOND,
															DS3231_REG_MINUTE,
															DS3231_REG_HOUR, 
															DS3231_REG_DAY, 
															DS3231_REG_DATE, 
															DS3231_REG_MONTH, 
															DS3231_REG_YEAR, 
															DS3231_REG_A1S, 
															DS3231_REG_A1M, 
															DS3231_REG_A1H, 
															DS3231_REG_A1D, 
															DS3231_REG_A2M, 
															DS3231_REG_A2H,
															DS3231_REG_A2D,
															DS3231_REG_CONTROL,
															DS3231_REG_HTEMP,
															DS3231_REG_LTEMP	};

int fd;
uint8_t DS3231Reg[17];
const char *week[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
char whichDay[5];
bool hourMode;
char meridiem[2][3] = {"AM", "PM"};
char stateOfTime[3] = "";
uint8_t byteData[16];
//sec, min ,hour, day, date, month, year, a1s, a1m, a1h, a1d, a2m, a2h, a2d, htemp, ltemp
char formatedTime[8][5] = {"0", "0", "0", "0", "0", "0", "20", "0"}; //sec, min ,hour, day, date, month, year, ampm
struct DS3231_Read DS3231;

int DS3231_Init( )
{
	int fd_DS3231 = wiringPiI2CSetup(DS3231_ADDRESS);
	return (fd_DS3231);
}

uint8_t BCD_to_Byte(uint8_t value)
{
	return ((((value & 0xf0) >> 4) * 10) + (value & 0x0f));
}

uint8_t Byte_to_BCD(uint8_t value)
{
	return ((((value % 100) / 10) << 4) | (value % 10));
}

void TimeOutput(int mode)
{
	FormatTime();
	switch (mode)
	{
		case 1 : printf("%s:%s:%s %s\n", formatedTime[2], formatedTime[1], formatedTime[0], stateOfTime); break;
		
		case 2 : printf("%s/%s/%s %s %s:%s:%s %s\n", formatedTime[6], formatedTime[5], formatedTime[4], whichDay, formatedTime[2], formatedTime[1], formatedTime[0], stateOfTime); break;

		case 3 : printf("%s/%s/%s", formatedTime[6], formatedTime[5], formatedTime[4]);
	}
	
}

void ByteData()
{
	DS3231_REG_Read();
	for (int i = 0; i < 7; i++)
	{
		byteData[i] = BCD_to_Byte(DS3231Reg[i]);
	}
}

void FormatTime()
{
	ByteData();
	if ((DS3231Reg[2] & 0x40) != 0) //判断12小时或24小时模式，bit6高位为12小时模式
	{
		hourMode = true;
		
		if ((DS3231Reg[2] & 0x20) != 0) //判断AM/PM，bit5高位为PM
		{
			strcpy(stateOfTime, meridiem[1]);
		}
		else
			strcpy(stateOfTime, meridiem[0]);
	}
	else
		hourMode = false;
	
	for (int i = 0; i < 6; i++) //为时间前补0
	{
		if (i == 2) //判断时间模式
		{
			if ((int)(byteData[2]) / 10 < 1 && !hourMode)
			{
				char _temp[2];
				sprintf(_temp, "%d", byteData[2]);
				strcat(formatedTime[4], _temp);
			}
			else
			{	
				char _temp[3];
				sprintf(_temp, "%d", byteData[2]);
				strcpy(formatedTime[4], _temp);
			}
		}

		if ((int)(byteData[i]) / 10 < 1)
		{
			char _temp[3];
			sprintf(_temp, "%d", byteData[i]);
			strcat(formatedTime[i], _temp);
		}
		else
		{	
			char _temp[3];
			sprintf(_temp, "%d", byteData[i]);
			strcpy(formatedTime[i], _temp);
		}
	}
	char _temp[3];
	sprintf(_temp, "%d", byteData[6]);
	strcat(formatedTime[6], _temp);//为年份前加20
	strcpy(whichDay, week[ (int)(byteData[3]) ]);

	DS3231.sec = byteData[0];
	DS3231.min = byteData[1];
	DS3231.hour = byteData[2];
	DS3231.day = byteData[3];
	DS3231.date = byteData[4];
	DS3231.month = byteData[5];
	DS3231.year = byteData[6];
}

void DS3231_REG_Read()
{
	for (int i = 0; i < 16; i++)
	{
		DS3231Reg[i] = wiringPiI2CReadReg8(fd, REG_ADDRESSES[i]);
	}
}

void TemperatureOutput()
{
	uint8_t CONV = 0b00100000; //Setting this Convert Temperature bit to 1
	uint8_t _temp = wiringPiI2CReadReg8(fd, DS3231_REG_CONTROL);
	wiringPiI2CWriteReg8(fd, DS3231_REG_CONTROL, (_temp | CONV)); 
	byteData[14] = wiringPiI2CReadReg8(fd, REG_ADDRESSES[14]);
	byteData[15] = wiringPiI2CReadReg8(fd, REG_ADDRESSES[15]);
	float ht = (float)(byteData[14]);
	float lt = (float)(byteData[15] >> 6) * 0.25;
	float temperature = ht + lt;
	printf("%.2f\n", temperature);
}

void setSecond(uint8_t _wsec)
{
	wiringPiI2CWriteReg8(fd, DS3231_REG_SECOND, Byte_to_BCD(_wsec));
}

void setMinute(uint8_t _wmin)
{
	wiringPiI2CWriteReg8(fd, DS3231_REG_MINUTE, Byte_to_BCD(_wmin));
}

void setHour(uint8_t _whour)
{
	wiringPiI2CWriteReg8(fd, DS3231_REG_HOUR, Byte_to_BCD(_whour));
}

void setDay(uint8_t _wday)
{
	wiringPiI2CWriteReg8(fd, DS3231_REG_DAY, Byte_to_BCD(_wday));
}

void setDate(uint8_t _wdate)
{
	wiringPiI2CWriteReg8(fd, DS3231_REG_DATE, Byte_to_BCD(_wdate));
}

void setMonth(uint8_t _wmon)
{
	wiringPiI2CWriteReg8(fd, DS3231_REG_MONTH, Byte_to_BCD(_wmon));
}

void setYear(uint8_t _wyear)
{
	wiringPiI2CWriteReg8(fd, DS3231_REG_YEAR, Byte_to_BCD(_wyear));
}

void setClockMode(bool h12)
{
	if (h12) 
	{
		uint8_t _temp = wiringPiI2CReadReg8(fd, DS3231_REG_HOUR);
		wiringPiI2CWriteReg8(fd, DS3231_REG_HOUR, (_temp | 0b01000000));
		
	}
	else
	{
		uint8_t _temp = wiringPiI2CReadReg8(fd, DS3231_REG_HOUR);
		wiringPiI2CWriteReg8(fd, DS3231_REG_HOUR, (_temp & 0b10111111));
	}
}

void getSystemTime( )
{
	time_t timer;
	time(&timer);
	printf("%s", ctime(&timer));
}

void writeSysTimetoDS( )
{
	time_t timer = time(NULL);
	struct tm *p;
	time(&timer);
	p = localtime(&timer);

	setSecond((uint8_t)p->tm_sec);
	setMinute((uint8_t)p->tm_min);
	setHour((uint8_t)p->tm_hour);
	setDay((uint8_t)p->tm_wday);
	setDate((uint8_t)p->tm_mday);
	setMonth((uint8_t)(p->tm_mon) + 1);
	setYear((uint8_t)(p->tm_year - 100));
	setClockMode(false);
}
