
SOURCES =	lex.yy.c kersh.tab.c util.c

OBJECTS	=	$(SOURCES:.c=.o)


all : flexbison

lex.yy.c: kersh.l
	flex  kersh.l

lex.yy.o: kersh.tab.c

kersh.tab.c: kersh.y
	bison -d kersh.y


flexbison: $(OBJECTS)
	gcc -o ktype $^

.c.o:
	gcc -c $*.c


clean :
	-rm *.o
	-rm *.output
	-rm ktype
	-rm *.yy.c
	-rm *.tab.c
	-rm *.tab.h

