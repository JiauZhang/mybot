#include <common/string.h>

int strcmp(const char *cs, const char *ct)
{
	while (*cs == *ct) {
		if (*cs == '\0')
			return 0;
		
		cs++;
		ct++;
	}
	
	return *cs < *ct ? -1 : 1;
}

unsigned int atoui(const char *str)
{
	unsigned int num = 0;
	
	while (*str != '\0') {
		num += 10 * (*(str++) - '0');
	}
	
	return num;
}

int atoi(const char *str)
{
	int num;
	
	if (*str == '-')
		num = -((int)atoui(++str));
	else
		num = atoui(str);
	
	return num;
}