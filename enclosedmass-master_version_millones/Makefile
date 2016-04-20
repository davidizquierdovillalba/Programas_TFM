#
# Note: CC, CPPFLAGS and LDFLAGS are set by the modules.
# Need a compiler and hdf5 modules loaded for this to work.
#
CC=gcc
#CPPFLAGS=-I/home/david/TFM/enclosedmass-master
#LDFLAGS=-L/home/david/TFM/enclosedmass-master

.SUFFIXES:
.SUFFIXES: .c .o

DEPS = allvars.h proto.h
OBJ =  allvars.o assigncell.o get_nparticles.o read_gadget.o linkedlist.o main.o

.c.o: $(DEPS)
	$(CC) -g $(CPPFLAGS) -c $< -o $*.o 


enclosedmass: $(OBJ)
	$(CC) -g -o $@ $^ $(CPPFLAGS) $(LDFLAGS) -lm

clean:
	\rm -f *.o read_gadget


#CFLAGS=-I<directorio1> -I<directorio2> ...
#OBJETOS=<objeto1> <objeto2> ...
#FUENTES=<fuente	1> <fuente2> ...

#MiEjecutable: $(OBJETOS)
#<tab>cc $(OBJETOS) -o MiEjecutable

#depend:
#<tab>makedepend $(CFLGAS) $(FUENTES) 
