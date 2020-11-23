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