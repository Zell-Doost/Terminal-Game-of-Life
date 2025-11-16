

CC=gcc

CFLAGS=-g -Wall -pedantic -std=gnu99

O=linux

LIBS= -lncurses -lm 

OBJS= 						\
			$(O)/ruleEnforcement.o

all:	$(O)/gameOfLife

clean:
	rm -f *.o *~ *.flc
	rm -f linux/*

$(O)/gameOfLife:		$(OBJS) $(O)/main.o
	$(CC) $(OBJS) $(O)/main.o \
		-o $(O)/gameOfLife $(LIBS)

$(O)/%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
