#ifdef EMUL

#include <stdio.h>
#include <stdlib.h>

#else

#include <minix/drivers.h>
#include <sys/video.h>
#include <sys/mman.h>

#endif

#include <assert.h>

#include "vt_info.h"

/* Color definitions */

#define	BLACK	0x00	
#define RED	(0x01 << 2)
#define GREEN	(0x01 << 1)
#define BLUE	0x01 
#define WHITE	(RED | GREEN | BLUE)

/* Shift size for background and foreground colors */

#define BACK	12	
#define FORE	8


/* Other character attributes */

#define BRIGHT	0x08	
#define BLINK	0x80

/*Character codes to draw single border frames */

#define VERT_BAR 	0xB3 
#define HOR_BAR 	0xC4
#define LL_CORNER 	0xC0
#define UL_CORNER	0xDA
#define LR_CORNER	0xD9
#define UR_CORNER	0xBF

/* Private global variables */

static char *video_mem;		/* Process address to which VRAM is mapped */

static unsigned scr_width;	/* Width of screen in columns */
static unsigned scr_lines;	/* Height of screen in lines */

void vt_fill(char ch, char attr) {
	int i;
	char *ptr;
	ptr = video_mem;
	/* Algorithm: print the char then print the attribute
	 * scr_width*scr_lines times
	 */
	for(i = 0; i< scr_width*scr_lines; i++, ptr++) {
			*(ptr)=ch;
			ptr++;
			*(ptr)=attr;
	}
  
}

void vt_blank(void) {

	vt_fill(0,0);

}

int vt_print_char(char ch, int r, int c, char attr) {
	char *ptr;
	ptr = video_mem;
	ptr=ptr+(r-1)*2*scr_width+(c-1)*2;
	*ptr=ch;
	*(++ptr)=attr;

}

int vt_print_string(char *str, int r, int c, char attr) {
	char *ptr;
	int i=0;
	ptr = video_mem;
	ptr=ptr+(r-1)*2*scr_width+(c-1)*2;
	for (i=0; i<strlen(str);i++){
		*ptr=*(str+i);
		ptr++;
		*ptr=attr;
	}

}

int vt_print_int(int num, int r, int c, char attr) {
	char *ptr;
	int i=0;
	int aux=0;
	ptr = video_mem;
	ptr=ptr+(r-1)*2*scr_width+(c-1)*2;
	/* (1) Reverse the number */
	while(num>0)
	{
	    aux*= 10;
	    aux+= num%10;
	    num /= 10;
	}
	num=aux;
	/* (2) Print the number */
	while(num){
		*ptr=0x30+num%10;
		num/=10;
		ptr++;
		*ptr=attr;
		ptr++;
	}
}


int vt_draw_frame(int width, int height, int r, int c, char attr) {
	int i,j;
	for (i=0; i<height; i++)
		for (j=0;j<width; j++){
			vt_print_char(219,r+i,c+j,attr);
		}

}

/* Needed only for emulation: does not emulate attributes */

void vt_update_display(void) {
  int i, j;
  for(i = 0; i < scr_lines; i++) {
      for(j = 0; j <  scr_width; j++)
	  printf("%c", (*(video_mem + i*scr_width*2 + j*2)) & 0xFF);
      printf("\n");
  }
}

#ifdef EMUL
char *vt_init(vt_info_t *vi_p) {

  /* No need for memory mapping */

  /* Save text mode resolution */
  
  video_mem = vi_p->vram_base;

  scr_lines = vi_p->scr_lines;
  scr_width = vi_p->scr_width;

  return video_mem;
}

#else

char *vt_init(vt_info_t *vi_p) {

  int r;
  struct mem_range mr;

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes)(vi_p->vram_base);
  mr.mr_limit = mr.mr_base + vi_p->vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
	  panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vi_p->vram_size);

  if(video_mem == MAP_FAILED)
	  panic("video_txt couldn't map video memory");

  /* Save text mode resolution */

  scr_lines = vi_p->scr_lines;
  scr_width = vi_p->scr_width;

  return video_mem;
}

#endif
