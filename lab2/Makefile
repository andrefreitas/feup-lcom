# Makefile for lab2 (based on that of hello).
PROG=	lab2
SRCS=	vbe.c video_gr.c lab2.c

DPADD+=	${LIBDRIVER} ${LIBSYS} liblm.a
LDADD+=	-llm -ldriver -lsys 
LDFLAGS+= -L. 

MAN=

BINDIR?= /usr/sbin

.include <bsd.prog.mk>
