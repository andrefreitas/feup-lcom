#include <minix/syslib.h>
#include <minix/drivers.h>

int timer_set_rate(unsigned long timer, unsigned long rate) {
	    unsigned long registoControlo;
		unsigned long sTimer;
		unsigned long div;
		/* Dicas importantes:
		 * Temos de especificar o registo de controlo e depois o lsb e msb.
		 * Para fazer debugging, usamos o comando date no minix e verificamos que o tempo
		 * incrementa mais rapidamente.
		 */
		/* (1) Especificar o Registo de Controlo */
		switch(timer){
			case 0:  {
				registoControlo=0x3E;
				sTimer=0x40;
			}
				break;
			case 1:{
				registoControlo=0xFC;
				sTimer=0x41;
			}
				break;
			case 2:{
				registoControlo=0xBE;
				sTimer=0x42;
			}
				break;
			default: return 1;
		}
		/* (2) Mandar para o porto 43 */
		sys_outb(0x43,registoControlo);
		/* (3) Mandar para o timer o LSB e MSB */
		div=1193182/rate;
		sys_outb(sTimer,(div<<4)>>4); /* LSB */
		sys_outb(sTimer,div>>4); /* MSB */
		return 0;
}

int timer_get_status(unsigned long timer, u8_t *st) {
	unsigned long registoControlo;
	unsigned long sTimer;
	unsigned long info;
	/*(1) Especificar registo de controlo */
	switch(timer){
		case 0:{
			registoControlo=0xC2;
			sTimer=0x40;
			break;
		}
		case 1:{
			registoControlo=0xC4;
			sTimer=0x41;
			break;
		}
		case 2:
		{
			registoControlo=0xC8;
			sTimer=0x42;
			break;
		}
		default:
			return 1;
	}
	/* (2) Mandar para o Porto 43h */
	sys_outb(0x43,registoControlo);
	/* (3) Ler do timer em causa */
	sys_inb(sTimer,&info);
	*st=info;
	return 0;
	/* Debug Teste
	* timer_get_status(0,&i);
	* printf("Estado: %x", i);
	 */
}

int timer_show_status(unsigned long timer) {
	unsigned char i;
	unsigned char output, nullCount, access, programMode, bcd;
	timer_get_status(timer,&i);
	/* (1) Fazer shifts para decompor o conteudo i */
	/* Format: ONAAPPPB, usando mascaras com e logicos */
	output=i>>7;
	nullCount=(i&0x40)>>6;
	access=(i&0x30)>>4;
	programMode=(i&0xE)>>1;
	bcd=(i&0x1);
	/* (2) Human Friendly output */
	printf("----------------------\n");
	printf("Returned Status: %x\n",i);
	printf("Output: %x\nnullCount: %x\nAccess: %x \nProgrammed Mode %x \nBCD: %x", output,nullCount,access,programMode,bcd);
	printf("\n----------------------\n");
	return 0;
}

unsigned long timer_subscribe_int(void ) {

}

int timer_unsubscribe_int() {
    /* To complete ... */  
}
