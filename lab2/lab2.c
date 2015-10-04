#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "vbe.h"
#define WAIT_TIME_S 15
int main(void){
	vg_init(0x103);   /* Mudar para modo de video */
	vg_draw_line(0,0,100,20,0x04);
	sleep(WAIT_TIME_S);
	vg_exit();
	return 1;
}
