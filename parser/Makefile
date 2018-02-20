
SOURCES =	lex.yy.c kersh.tab.c util.c parse.c symbols.c types.c

OBJECTS	=	$(SOURCES:.c=.o)

BIN	=	cpars

CFLAGS = -g -DYYERROR_VERBOSE -DYYDEBUG -I../include

all : $(BIN)

lex.yy.c: kersh.l
	flex  kersh.l

lex.yy.o: kersh.tab.c

kersh.tab.c: kersh.y
#	bison -v -d kersh.y
	bison -d kersh.y


$(BIN): $(OBJECTS)
	gcc -o $(BIN) $^

tags: FORCE
	ctags *.c *.h

FORCE:


.c.o:
	gcc $(CFLAGS) -c $*.c


clean :
	-rm *.o
	-rm ${BIN}
	-rm *.yy.c
	-rm *.tab.c
	-rm *.tab.h
	-rm *.output
	-rm *.d

depend: $(SOURCES)

%.d: %.c
	$(CC) $(CFLAGS) -M $<  >  $@


include $(SOURCES:.c=.d)

