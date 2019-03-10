#ifndef _PILE_H_
#define _PILE_H_

#define MAX_PILE_SIZE 50

typedef struct pile
{
	int sommet;
	pnoeud234 Tab[MAX_PILE_SIZE];
} pile_t, *ppile_t;

ppile_t creer_pile();

int pile_vide(ppile_t p);

int pile_pleine(ppile_t p);

pnoeud234 depiler(ppile_t p);

int empiler(ppile_t p, pnoeud234 pn);

#endif
