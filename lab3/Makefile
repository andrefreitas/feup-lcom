# Makefile for lab3 (based on that of hello).
PROG=	lab3
SRCS=	speaker.c timer.c lab3.c

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+=	-ldriver -lsys 
LDFLAGS+= -L. 

MAN=

BINDIR?= /usr/sbin

.include <bsd.prog.mk>

clean:
	rm -rf *o lab3
