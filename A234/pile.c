#include <stdlib.h>
#include <assert.h>

#include "a234.h"
#include "pile.h"

ppile_t creer_pile()
{
	ppile_t p = (ppile_t)malloc(sizeof(pile_t));
	assert(p != NULL); //Mémoire pleine
	p->sommet = 0;
	return p;
}

int pile_vide(ppile_t p)
{
	assert(p != NULL); //Pile inexistante
	return (p->sommet == 0);
}

int pile_pleine(ppile_t p)
{
	assert(p != NULL); //Pile inexistante
	return (p->sommet == MAX_PILE_SIZE);
}

pnoeud234 depiler(ppile_t p)
{
	assert(p != NULL); //Pile inexistante
	if (p->sommet <= 0)
		return NULL; //Pile vide
	p->sommet--;
	return p->Tab[p->sommet];
}

int empiler(ppile_t p, pnoeud234 pn)
{
	assert(p != NULL); //Pile inexistante
	if (p->sommet >= MAX_PILE_SIZE)
		return 2; //Pile pleine
	if (pn == NULL)
		return 3; //Essaie d'empilement d'un element vide
	p->Tab[p->sommet] = pn;
	p->sommet++;
	return 1;
}