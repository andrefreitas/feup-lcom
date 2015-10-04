#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "vbe.h"

/* Constants for VBE 0x105 mode */

#define VRAM_PHYS_ADDR    0xD0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8

/* Private global variables */

static char *video_mem;		/* Process address to which VRAM is mapped */

static unsigned hres;		/* Horizontal screen resolution in pixels */
static unsigned vres;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void * vg_init(unsigned long mode) {
	/* (1) Declarar variáveis */
	struct reg86u r;
	struct mem_range range;
	vbe_mode_info_t vmi;
	/* (2) Definir estrutura */
	r.u.b.intno = 0x10;
	r.u.b.ah = 0x4F;
	r.u.b.al = 0x02;
	r.u.w.bx = 1 << 14 | mode;
	sys_int86(&r);
	/* (3) Obter Informações */
	vbe_get_mode_info(mode, &vmi);
	/* (4) Definir o espaço de endereçamento */
	range.mr_base = vmi.PhysBasePtr;
	range.mr_limit = range.mr_base + vmi.XResolution * vmi.YResolution
	*(vmi.BitsPerPixel / 8);
	/* (5) Entrar em modo previlegiado */
	sys_privctl(SELF, SYS_PRIV_ADD_MEM, &range);
	/* OBJECTIVO FINAL: mapear o endereço para o video_mem */
	video_mem = vm_map_phys(SELF, (void *) range.mr_base, vmi.XResolution
	* vmi.YResolution * (vmi.BitsPerPixel / 8));
	/* (6) Alterar variáveis globais */
	hres = vmi.YResolution;
	vres = vmi.XResolution;
	bits_per_pixel = vmi.BitsPerPixel;
}

int vg_fill(unsigned long color) {
	int i,j;
	for (i=0; i<=vres; i++)
		for (j=0; j<=hres; j++){
		vg_set_pixel(i,j,color);
		}
	return 0;
}

int vg_set_pixel(unsigned long x, unsigned long y, unsigned long color) {
	*(video_mem+y*hres+x)=color;
	return 0;
}

long vg_get_pixel(unsigned long x, unsigned long y) {
	return *(video_mem + y * hres + x);
}

int vg_draw_line(unsigned long xi, unsigned long yi, unsigned long xf, unsigned long yf, unsigned long color) {
	int i,j,aux;
	/* Swap values if needed */
	if (xf<xi & yf<yi){
		aux=xf;
		xf=xi;
		xi=aux;
		aux=yf;
		yf=yi;
		yi=aux;
	}
	for (i=xi,j=yi; i<xf; i++){
			vg_set_pixel(i,j,color);
			if (yf>yi) j++;
		}

	return 0;
}

int vg_exit() {
  struct reg86u reg86;

  reg86.u.b.intno = 0x10; /* BIOS video services */

  reg86.u.b.ah = 0x00;    /* Set Video Mode function */
  reg86.u.b.al = 0x03;    /* 80x25 text mode*/

  if( sys_int86(&reg86) != OK ) {
      printf("\tvg_exit(): sys_int86() failed \n");
      return 1;
  } else
      return 0;
}
