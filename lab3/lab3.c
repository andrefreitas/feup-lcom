#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
int main(){
	sef_startup();
	/* Relogio mais lento */
	timer_set_rate(0,30);
	timer_show_status(0);
	return 0;
}
