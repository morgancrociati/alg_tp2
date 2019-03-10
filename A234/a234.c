#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include "a234.h"
#include "pile.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

int hauteur(Arbre234 a)
{
	int h0, h1, h2, h3;

	//Si le noeud courrant n'existe pas ou qu'il est vide
	if (a == NULL || a->t == 0)
		return 0;

	h0 = hauteur(a->fils[0]);
	h1 = hauteur(a->fils[1]);
	h2 = hauteur(a->fils[2]);
	h3 = hauteur(a->fils[3]);

	return 1 + max(max(h0, h1), max(h2, h3));
}

int NombreCles(Arbre234 a)
{
	if(a == NULL || a->t == 0)
		return 0;
	else
		//Un noeud existant et non vide à un nombre de clef égal à son type moins 1
		return (a->t - 1) + NombreCles(a->fils[0]) + NombreCles(a->fils[1]) + NombreCles(a->fils[2]) + NombreCles(a->fils[3]);
}

int CleMax(Arbre234 a)
{
	if (a->t == 0)
	{
		printf("Pas de cle max\n");
		return 0;
	}
	else if (a->t == 2)
	{
		if (a->fils[2]->t == 0)
			return a->cles[1];
		else
			return CleMax(a->fils[2]);
	}
	else if (a->t == 3)
	{
		if (a->fils[2]->t == 0)
			return a->cles[1];
		else
			return CleMax(a->fils[2]);
	}
	else
	{
		if (a->fils[3]->t == 0)
			return a->cles[2];
		else
			return CleMax(a->fils[3]);
	}
}

int CleMin(Arbre234 a)
{
	if (a->t == 0)
	{
		printf("Pas de cle min\n");
		return 0;
	}
	else if (a->t == 2)
	{
		if (a->fils[1]->t == 0)
			return a->cles[1];
		else
			return CleMin(a->fils[1]);
	}
	else if (a->t == 3)
	{
		if (a->fils[0]->t == 0)
			return a->cles[0];
		else
			return CleMin(a->fils[0]);
	}
	else
	{
		if (a->fils[0]->t == 0)
			return a->cles[0];
		else
			return CleMin(a->fils[0]);
	}
	return 0;
}

Arbre234 RechercherCle(Arbre234 a, int cle)
{
	if (a == NULL || a->t == 0)
	{
		printf("cle non trouvé\n");
		return NULL;
	}
	else if (a->t == 2)
	{
		if (cle == a->cles[1])
			return a;
		else if (cle < a->cles[1])
			return RechercherCle(a->fils[1], cle);
		else
			return RechercherCle(a->fils[2], cle);
	}
	else if (a->t == 3)
	{
		if (cle == a->cles[0] || cle == a->cles[1] || cle == a->cles[2])
			return a;
		else if (cle < a->cles[0])
			return RechercherCle(a->fils[0], cle);
		else if (cle > a->cles[1] && cle < a->cles[2])
			return RechercherCle(a->fils[1], cle);
		else
		{
			return RechercherCle(a->fils[2], cle);
		}
	}
	else
	{
		if (cle == a->cles[0] || cle == a->cles[1] || cle == a->cles[2] || cle == a->cles[3])
			return a;
		else if (cle < a->cles[0])
			return RechercherCle(a->fils[0], cle);
		else if (cle > a->cles[1] && cle < a->cles[2])
			return RechercherCle(a->fils[1], cle);
		else if (cle > a->cles[2] && cle < a->cles[3])
			return RechercherCle(a->fils[2], cle);
		else
		{
			return RechercherCle(a->fils[3], cle);
		}
	}
}

/*void Init_somme_cle(Arbre234 a){
  if(a==NULL)
    return;
  
  if(a->t==0){
    return;
  }
  else if(a->t==2){
    a->somme=a->cles[1];
    Init_somme_cle(a->fils[1]);
    Init_somme_cle(a->fils[2]);   
  }
  else if(a->t==3){
    a->somme=a->cles[0]+ a->cles[1];
    Init_somme_cle(a->fils[0]);
    Init_somme_cle(a->fils[1]);
    Init_somme_cle(a->fils[2]);  
  }
  else{
    a->somme=a->cles[0]+ a->cles[1]+ a->cles[2];
    Init_somme_cle(a->fils[0]);
    Init_somme_cle(a->fils[1]);
    Init_somme_cle(a->fils[2]);  
    Init_somme_cle(a->fils[3]); 
  }
}*/

//incomplet
Arbre234 noeud_max(Arbre234 a)
{
	/*
    Retourne le noeud avec la somme maximale des cles internes
  */
	unsigned int etage = 0;
	unsigned int taillePile;
	pnoeud234 tmp;

	int i;
	ppile_t noeudCourant = creer_pile();
	ppile_t noeudRes = creer_pile();
	int max = 0;
	Arbre234 res;
	i = empiler(noeudCourant, a);
	if (i != 1)
		return NULL;
	i = empiler(noeudRes, a);
	if (i != 1)
		return NULL;

	while (!pile_vide(noeudCourant))
	{
		etage++;
		taillePile = noeudCourant->sommet;

		while (taillePile > 0)
		{
			tmp = depiler(noeudCourant);
			if (tmp->t == 0)
			{
			}
			else if (tmp->t == 2)
			{
				if (tmp->fils[1]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[1]);
					if (i != 1)
						return NULL;
					i = empiler(noeudRes, tmp->fils[1]);
					if (i != 1)
						return NULL;
				}
				if (tmp->fils[2]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[2]);
					if (i != 1)
						return NULL;
					i = empiler(noeudRes, tmp->fils[2]);
					if (i != 1)
						return NULL;
				}
			}
			else if (tmp->t == 3)
			{
				if (tmp->fils[0]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[0]);
					if (i != 1)
						return NULL;
					i = empiler(noeudRes, tmp->fils[0]);
					if (i != 1)
						return NULL;
				}
				if (tmp->fils[1]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[1]);
					if (i != 1)
						return NULL;
					i = empiler(noeudRes, tmp->fils[1]);
					if (i != 1)
						return NULL;
				}
				if (tmp->fils[2]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[2]);
					if (i != 1)
						return NULL;
					i = empiler(noeudRes, tmp->fils[2]);
					if (i != 1)
						return NULL;
				}
			}
			else
			{

				if (tmp->fils[0]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[0]);
					if (i != 1)
						return NULL;
					i = empiler(noeudRes, tmp->fils[0]);
					if (i != 1)
						return NULL;
				}
				if (tmp->fils[1]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[1]);
					if (i != 1)
						return NULL;
					i = empiler(noeudRes, tmp->fils[1]);
					if (i != 1)
						return NULL;
				}
				if (tmp->fils[2]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[2]);
					if (i != 1)
						return NULL;
					i = empiler(noeudRes, tmp->fils[2]);
					if (i != 1)
						return NULL;
				}
				if (tmp->fils[3]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[3]);
					if (i != 1)
						return NULL;
					i = empiler(noeudRes, tmp->fils[3]);
					if (i != 1)
						return NULL;
				}
			}
			taillePile--;
		}
	}

	for (int j = 0; j < noeudRes->sommet; j++)
	{
		if (noeudRes->Tab[j]->t == 2)
		{
			if (noeudRes->Tab[j]->cles[1] > max)
			{
				max = noeudRes->Tab[j]->cles[1];
				res = noeudRes->Tab[j];
			}
		}
		if (noeudRes->Tab[j]->t == 3)
		{
			if (noeudRes->Tab[j]->cles[0] + noeudRes->Tab[j]->cles[1] > max)
			{
				max = noeudRes->Tab[j]->cles[0] + noeudRes->Tab[j]->cles[1];
				res = noeudRes->Tab[j];
			}
		}
		if (noeudRes->Tab[j]->t == 4)
		{
			if (noeudRes->Tab[j]->cles[0] + noeudRes->Tab[j]->cles[1] + noeudRes->Tab[j]->cles[2] > max)
			{
				max = noeudRes->Tab[j]->cles[0] + noeudRes->Tab[j]->cles[1] + noeudRes->Tab[j]->cles[2];
				res = noeudRes->Tab[j];
			}
		}
	}
	return res;
}

void Afficher_Cles_Largeur(Arbre234 a) //on utilise une pile
{
	/*
    Afficher le cles de l'arbre a avec
    un parcours en largeur
  */
	unsigned int etage = 0;
	unsigned int taillePile;
	pnoeud234 tmp;

	int i;
	ppile_t noeudCourant = creer_pile();
	i = empiler(noeudCourant, a);
	if (i != 1)
		return;

	while (!pile_vide(noeudCourant))
	{
		printf("niveau %d: ", etage);
		etage++;
		taillePile = noeudCourant->sommet;

		while (taillePile > 0)
		{
			tmp = depiler(noeudCourant);
			if (tmp->t == 0)
			{
			}
			else if (tmp->t == 2)
			{
				printf("%d ", tmp->cles[1]);
				if (tmp->fils[1]->t != 0)
					i = empiler(noeudCourant, tmp->fils[1]);
				if (i != 1)
					return;
				if (tmp->fils[2]->t != 0)
					i = empiler(noeudCourant, tmp->fils[2]);
				if (i != 1)
					return;
			}
			else if (tmp->t == 3)
			{
				printf("%d %d ", tmp->cles[0], tmp->cles[1]);
				if (tmp->fils[0]->t != 0)
					i = empiler(noeudCourant, tmp->fils[0]);
				if (i != 1)
					return;
				if (tmp->fils[1]->t != 0)
					i = empiler(noeudCourant, tmp->fils[1]);
				if (i != 1)
					return;
				if (tmp->fils[2]->t != 0)
					i = empiler(noeudCourant, tmp->fils[2]);
				if (i != 1)
					return;
			}
			else
			{
				printf("%d %d %d ", tmp->cles[0], tmp->cles[1], tmp->cles[2]);
				if (tmp->fils[0]->t != 0)
					i = empiler(noeudCourant, tmp->fils[0]);
				if (i != 1)
					return;
				if (tmp->fils[1]->t != 0)
					i = empiler(noeudCourant, tmp->fils[1]);
				if (i != 1)
					return;
				if (tmp->fils[2]->t != 0)
					i = empiler(noeudCourant, tmp->fils[2]);
				if (i != 1)
					return;
				if (tmp->fils[3]->t != 0)
					i = empiler(noeudCourant, tmp->fils[3]);
				if (i != 1)
					return;
			}
			taillePile--;
		}
		printf("\n");
	}
}

void Affichage_Cles_Triees_Recursive(Arbre234 a)
{
	if (a == NULL || a->t == 0)
		return;
	else if (a->t == 2)
	{
		Affichage_Cles_Triees_Recursive(a->fils[1]);
		printf("%d ", a->cles[1]);
		Affichage_Cles_Triees_Recursive(a->fils[2]);
	}
	else if (a->t == 3)
	{
		Affichage_Cles_Triees_Recursive(a->fils[0]);
		printf("%d ", a->cles[0]);
		Affichage_Cles_Triees_Recursive(a->fils[1]);
		printf("%d ", a->cles[1]);
		Affichage_Cles_Triees_Recursive(a->fils[2]);
	}
	else
	{
		Affichage_Cles_Triees_Recursive(a->fils[0]);
		printf("%d ", a->cles[0]);
		Affichage_Cles_Triees_Recursive(a->fils[1]);
		printf("%d ", a->cles[1]);
		Affichage_Cles_Triees_Recursive(a->fils[2]);
		printf("%d ", a->cles[2]);
		Affichage_Cles_Triees_Recursive(a->fils[3]);
	}
}

void Affichage_Cles_Triees_NonRecursive(Arbre234 a)
{
	/* 
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */
	unsigned int etage = 0;
	unsigned int taillePile;
	pnoeud234 tmp;

	int cpt = 0;
	int i;
	ppile_t noeudCourant = creer_pile();
	int cle[50];
	i = empiler(noeudCourant, a);
	if (i != 1)
		return;

	while (!pile_vide(noeudCourant))
	{
		etage++;
		taillePile = noeudCourant->sommet;

		while (taillePile > 0)
		{
			tmp = depiler(noeudCourant);
			if (tmp->t == 0)
			{
			}
			else if (tmp->t == 2)
			{
				cle[cpt] = tmp->cles[1];
				cpt++;
				if (tmp->fils[1]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[1]);
					if (i != 1)
						return;
				}
				if (tmp->fils[2]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[2]);
					if (i != 1)
						return;
				}
			}
			else if (tmp->t == 3)
			{
				cle[cpt] = tmp->cles[0];
				cpt++;
				cle[cpt] = tmp->cles[1];
				cpt++;
				if (tmp->fils[0]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[0]);
					if (i != 1)
						return;
				}
				if (tmp->fils[1]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[1]);
					if (i != 1)
						return;
				}
				if (tmp->fils[2]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[2]);
					if (i != 1)
						return;
				}
			}
			else
			{
				cle[cpt] = tmp->cles[0];
				cpt++;
				cle[cpt] = tmp->cles[1];
				cpt++;
				cle[cpt] = tmp->cles[2];
				cpt++;
				if (tmp->fils[0]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[0]);
					if (i != 1)
						return;
				}
				if (tmp->fils[1]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[1]);
					if (i != 1)
						return;
				}
				if (tmp->fils[2]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[2]);
					if (i != 1)
						return;
				}
				if (tmp->fils[3]->t != 0)
				{
					i = empiler(noeudCourant, tmp->fils[3]);
					if (i != 1)
						return;
				}
			}
			taillePile--;
		}
	}
	for (int j = 0; j < cpt; j++)
	{
		for (int k = j + 1; k < cpt; k++)
		{
			if (cle[j] > cle[k])
			{
				int c = cle[j];
				cle[j] = cle[k];
				cle[k] = c;
			}
		}
	}
	for (int j = 0; j < cpt; j++)
	{
		printf("%d ", cle[j]);
	}
}

//incomplet
void Detruire_Cle(Arbre234 *a, int cle)
{
	/*
    retirer la cle de l'arbre a
  */
	Arbre234 b = RechercherCle(*a, cle);
}

int main(int argc, char **argv)
{
	Arbre234 a;

	if (argc != 2)
	{
		fprintf(stderr, "il manque le parametre nom de fichier\n");
		exit(-1);
	}

	a = lire_arbre(argv[1]);

	printf("==== Afficher arbre ====\n");

	afficher_arbre(a, 0);

	printf("Nombre niveaux: %d\n", hauteur(a));

	printf("Nombre cle : %d\n", NombreCles(a));

	printf("CleMax: %d\n", CleMax(a));
	printf("CleMin: %d\n", CleMin(a));
	printf("\nParcours largeur:\n");
	Afficher_Cles_Largeur(a);
	printf("\n");

	//printf("cle trié r: ");Affichage_Cles_Triees_Recursive(a);printf("\n");
	//printf("cle trié nr: ");Affichage_Cles_Triees_NonRecursive(a);printf("\n");

	//a=RechercherCle(a,80);
	//Detruire_Cle(&a,50);
	//ajouter_cle(&a,79,0,a);

	//afficher_arbre(a,0);
	a = noeud_max(a);
	afficher_arbre(a, 0);
	return 0;
}
