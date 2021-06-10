#include <common/console.h>
#include <common/project.h>
#include <os.h>

int main(void)
{
	OS_ERR err;

	stdio_init();
	OSInit(&err);
	start_project();
	
	return 0;
}