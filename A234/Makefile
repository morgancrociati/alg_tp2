CC = gcc
CO = -Wall -Werror -g

all: test_a234

test_a234: test_a234.o a234.o lire_affichage.o ajout_cle.o pile.o
	$(CC) $(CO) -o $@ $^

test_a234.o: test_a234.c a234.h
	$(CC) $(CO) -c $<

a234.o: a234.c a234.h
	$(CC) $(CO) -c $<

lire_affichage.o: lire_affichage.c a234.h
	$(CC) $(CO) -c $<

ajout_cle.o : ajout_cle.c a234.h
	$(CC) $(CO) -c $<

pile.o: pile.c pile.h
	$(CC) $(CO) -c $<

clean:
	rm test_a234 *.o
