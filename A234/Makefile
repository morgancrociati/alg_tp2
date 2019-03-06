all: a234

OPTIONS_COMPIL=-Wall -g -c

a234: a234.o lire_affichage.o ajout_cle.o pile.o
	gcc -o a234 a234.o lire_affichage.o ajout_cle.o pile.o

a234.o: a234.c a234.h
	gcc $(OPTIONS_COMPIL) -std=gnu99 a234.c

lire_affichage.o: lire_affichage.c a234.h
	gcc $(OPTIONS_COMPIL) lire_affichage.c

ajout_cle.o : ajout_cle.c a234.h
	gcc $(OPTIONS_COMPIL) ajout_cle.c

pile.o: pile.c pile.h
	gcc $(OPTIONS_COMPIL) pile.c

clean:
	rm -rf a234 *.o *~
