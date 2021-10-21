#include <common/console.h>
#include <common/project.h>
#include <os.h>

int main(void)
{
	OS_ERR err;

	stdio_init();
	CPU_IntDis();
	OSInit(&err);
	CPU_IntEn();

	prints("\nOS initialization ");
	if (err == OS_ERR_NONE)
		prints("succeed!\n");
	else
		prints("failed!\n");

	start_project();
	
	return 0;
}