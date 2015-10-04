# Makefile for lab1 (based on that of hello).
PROG=	lab1
SRCS=	lab1.c video_txt.c 

DPADD+=	${LIBDRIVER} ${LIBSYS} libvt.a
LDADD+=	-lvt -ldriver -lsys 
LDFLAGS+= -L. 

MAN=

BINDIR?= /usr/sbin

.include <bsd.prog.mk>
