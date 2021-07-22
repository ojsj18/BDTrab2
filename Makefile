#Autores: Giovani G Marciniak e Ovídio Junior
#GRR20182981
#GRR20182667
#Modificado em 22/07/2021

CFLAGS  = -Wall

all: escalona

escalona: main.o transacoes.o listas.o 
	$(LINK.c) -o $@ -Bstatic main.o transacoes.o listas.o 

main.o: main.c
	$(COMPILE.c) main.c

transacoes.o: transacoes.c transacoes.h
	$(COMPILE.c) transacoes.c

listas.o: listas.c listas.h
	$(COMPILE.c) listas.c

clean:
	$(RM) *.o escalona