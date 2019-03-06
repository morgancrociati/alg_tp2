#include <stdlib.h>

#include "a234.h"
#include "pile.h"


ppile_t creer_pile ()
{
	ppile_t p = (ppile_t)malloc(sizeof(pile_t));
	p->sommet = 0;
	return p;
}

int pile_vide (ppile_t p)
{
	return (p->sommet == 0);
}

int pile_pleine (ppile_t p)
 {
	return (p->sommet == MAX_PILE_SIZE);
} 

pnoeud234 depiler (ppile_t p)
{
	if(p->sommet <= 0){
		return NULL;
	}
	p->sommet--;
  return p->Tab[p->sommet];

}

int empiler (ppile_t p, pnoeud234 pn)
  {
	if(p->sommet >= MAX_PILE_SIZE){
		return 0;
	}
  if(pn==NULL)return 2;
  p->Tab[p->sommet] = pn;
	p->sommet++;
  return 1;
}