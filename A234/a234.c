#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"
#include "pile.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

int hauteur(Arbre234 a)
{
    int h0, h1, h2, h3;

    if (a == NULL)
        return 0;

    if (a->t == 0)
        return 0;

    h0 = hauteur(a->fils[0]);
    h1 = hauteur(a->fils[1]);
    h2 = hauteur(a->fils[2]);
    h3 = hauteur(a->fils[3]);

    return 1 + max(max(h0, h1), max(h2, h3));
}

int NombreCles(Arbre234 a)
{
    if (a == NULL || a->t == 0)
        return 0;
    else
        return (a->t - 1) + NombreCles(a->fils[0]) + NombreCles(a->fils[1]) + NombreCles(a->fils[2]) + NombreCles(a->fils[3]);
}

int CleMax(Arbre234 a)
{
    if (a->t == 0)
    {
        printf("Erreur: pas de cle maximal\n");
        return 0;
    }
    else if (a->t == 2)
    {
        if (a->fils[2]->t == 0)
            return a->cles[1];
        else
            return CleMax(a->fils[2]);
    }
    else
    {
        if (a->fils[a->t - 1]->t == 0)
            return a->cles[a->t - 2];
        else
            return CleMax(a->fils[a->t - 1]);
    }
}

int CleMin(Arbre234 a)
{
    if (a->t == 0)
    {
        printf("Erreur: pas de cle minimal\n");
        return 0;
    }
    else if (a->t == 2)
    {
        if (a->fils[1]->t == 0)
            return a->cles[1];
        else
            return CleMin(a->fils[1]);
    }
    else
    {
        if (a->fils[0]->t == 0)
            return a->cles[0];
        else
            return CleMin(a->fils[0]);
    }
}

Arbre234 RechercherCle(Arbre234 a, int cle)
{
    if (a == NULL || a->t == 0)
        return NULL;
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
        if (cle == a->cles[0] || cle == a->cles[1])
            return a;
        else if (cle < a->cles[0])
            return RechercherCle(a->fils[0], cle);
        else if (cle < a->cles[1])
            return RechercherCle(a->fils[1], cle);
        else
            return RechercherCle(a->fils[2], cle);
    }
    else
    {
        if (cle == a->cles[0] || cle == a->cles[1] || cle == a->cles[2])
            return a;
        else if (cle < a->cles[0])
            return RechercherCle(a->fils[0], cle);
        else if (cle < a->cles[1])
            return RechercherCle(a->fils[1], cle);
        else if (cle < a->cles[2])
            return RechercherCle(a->fils[2], cle);
        else
            return RechercherCle(a->fils[3], cle);
    }
}

int somme_noeud(Arbre234 a)
{
    if (a == NULL || a->t == 0)
    {
        return 0;
    }
    else if (a->t == 2)
    {
        return a->cles[1];
    }
    else if (a->t == 3)
    {
        return a->cles[0] + a->cles[1];
    }
    else //if (a->t == 4)
    {
        return a->cles[0] + a->cles[1] + a->cles[2];
    }
}

Arbre234 noeud_max(Arbre234 a)
{
    int i, somme, tmpSomme;
    Arbre234 noeud = a;
    Arbre234 tmpNoeud;
    if (a == NULL || a->t == 0)
    {
        return NULL;
    }
    else if (a->t == 2)
    {
        somme = a->cles[1];
        for (i = 1; i <= 2; i++)
        {
            if (a->fils[i]->t != 0)
            {
                tmpNoeud = noeud_max(a->fils[i]);
                tmpSomme = somme_noeud(tmpNoeud);
                if (somme < tmpSomme)
                {
                    somme = tmpSomme;
                    noeud = tmpNoeud;
                }
            }
        }
    }
    else if (a->t == 3)
    {
        somme = a->cles[0] + a->cles[1];
        for (i = 0; i <= 2; i++)
        {
            if (a->fils[i]->t != 0)
            {
                tmpNoeud = noeud_max(a->fils[i]);
                tmpSomme = somme_noeud(tmpNoeud);
                if (somme < tmpSomme)
                {
                    somme = tmpSomme;
                    noeud = tmpNoeud;
                }
            }
        }
    }
    else //if (a->t == 4)
    {
        somme = a->cles[0] + a->cles[1] + a->cles[2];
        for (i = 0; i <= 3; i++)
        {
            if (a->fils[i]->t != 0)
            {
                tmpNoeud = noeud_max(a->fils[i]);
                tmpSomme = somme_noeud(tmpNoeud);
                if (somme < tmpSomme)
                {
                    somme = tmpSomme;
                    noeud = tmpNoeud;
                }
            }
        }
    }
    return noeud;
}

Arbre234 noeud_max_nr(Arbre234 a)
{
    unsigned int taillePile;
    pnoeud234 tmp;

    ppile_t noeudCourant = creer_pile();
    ppile_t noeudRes = creer_pile();

    if (empiler(noeudCourant, a) != 1)
        return NULL;
    if (empiler(noeudRes, a) != 1)
        return NULL;

    while (!pile_vide(noeudCourant))
    {
        taillePile = noeudCourant->sommet;

        while (taillePile > 0)
        {
            tmp = depiler(noeudCourant);

            if (tmp->t == 2)
            {
                if (tmp->fils[1]->t != 0)
                {
                    if (empiler(noeudCourant, tmp->fils[1]) != 1)
                        return NULL;
                    if (empiler(noeudRes, tmp->fils[1]) != 1)
                        return NULL;
                }
                if (tmp->fils[2]->t != 0)
                {
                    if (empiler(noeudCourant, tmp->fils[2]) != 1)
                        return NULL;
                    if (empiler(noeudRes, tmp->fils[2]) != 1)
                        return NULL;
                }
            }
            else if (tmp->t == 3)
            {
                if (tmp->fils[0]->t != 0)
                {
                    if (empiler(noeudCourant, tmp->fils[0]) != 1)
                        return NULL;
                    if (empiler(noeudRes, tmp->fils[0]) != 1)
                        return NULL;
                }
                if (tmp->fils[1]->t != 0)
                {
                    if (empiler(noeudCourant, tmp->fils[1]) != 1)
                        return NULL;
                    if (empiler(noeudRes, tmp->fils[1]) != 1)
                        return NULL;
                }
                if (tmp->fils[2]->t != 0)
                {
                    if (empiler(noeudCourant, tmp->fils[2]) != 1)
                        return NULL;
                    if (empiler(noeudRes, tmp->fils[2]) != 1)
                        return NULL;
                }
            }
            else if (tmp->t == 4)
            {
                if (tmp->fils[0]->t != 0)
                {
                    if (empiler(noeudCourant, tmp->fils[0]) != 1)
                        return NULL;
                    if (empiler(noeudRes, tmp->fils[0]) != 1)
                        return NULL;
                }
                if (tmp->fils[1]->t != 0)
                {
                    if (empiler(noeudCourant, tmp->fils[1]) != 1)
                        return NULL;
                    if (empiler(noeudRes, tmp->fils[1]) != 1)
                        return NULL;
                }
                if (tmp->fils[2]->t != 0)
                {
                    if (empiler(noeudCourant, tmp->fils[2]) != 1)
                        return NULL;
                    if (empiler(noeudRes, tmp->fils[2]) != 1)
                        return NULL;
                }
                if (tmp->fils[3]->t != 0)
                {
                    if (empiler(noeudCourant, tmp->fils[3]) != 1)
                        return NULL;
                    if (empiler(noeudRes, tmp->fils[3]) != 1)
                        return NULL;
                }
            }
            taillePile--;
        }
    }

    tmp = depiler(noeudRes);
    int max = somme_noeud(tmp);
    Arbre234 res = tmp;

    while (!pile_vide(noeudRes))
    {
        tmp = depiler(noeudRes);
        if (max < somme_noeud(tmp))
        {
            max = somme_noeud(tmp);
            res = tmp;
        }
    }
    return res;
}

void Afficher_Cles_Largeur(Arbre234 a)
{
    unsigned int etage = 0;
    pnoeud234 tmp;

    ppile_t noeudCourant = creer_pile();
    ppile_t noeudSuivant = creer_pile();
    ppile_t tmpP;
    if (empiler(noeudCourant, a) != 1)
        return;

    while (!pile_vide(noeudCourant))
    {
        printf("niveau %d: ", etage);
        etage++;

        while (!pile_vide(noeudCourant))
        {
            tmp = depiler(noeudCourant);

            if (tmp->t == 2)
            {
                printf("%d ", tmp->cles[1]);
                if (tmp->fils[1]->t != 0 && empiler(noeudSuivant, tmp->fils[1]) != 1)
                    return;
                if (tmp->fils[2]->t != 0 && empiler(noeudSuivant, tmp->fils[2]) != 1)
                    return;
            }
            else if (tmp->t == 3)
            {
                printf("%d %d ", tmp->cles[0], tmp->cles[1]);
                if (tmp->fils[0]->t != 0 && empiler(noeudSuivant, tmp->fils[0])  != 1)
                    return;
                if (tmp->fils[1]->t != 0 && empiler(noeudSuivant, tmp->fils[1]) != 1)
                    return;
                if (tmp->fils[2]->t != 0 && empiler(noeudSuivant, tmp->fils[2]) != 1)
                    return;
            }
            else if (tmp->t == 4)
            {
                printf("%d %d %d ", tmp->cles[0], tmp->cles[1], tmp->cles[2]);
                if (tmp->fils[0]->t != 0 && empiler(noeudSuivant, tmp->fils[0]) != 1)
                    return;
                if (tmp->fils[1]->t != 0 && empiler(noeudSuivant, tmp->fils[1]) != 1)
                    return;
                if (tmp->fils[2]->t != 0 && empiler(noeudSuivant, tmp->fils[2]) != 1)
                    return;
                if (tmp->fils[3]->t != 0 && empiler(noeudSuivant, tmp->fils[3]) != 1)
                    return;
            }
            taillePile--;
        }
        tmpP = noeudCourant;
        noeudCourant = noeudSuivant;
        noeudSuivant = tmpP;
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
    unsigned int taillePile;
    pnoeud234 tmp;

    int cpt = 0;

    ppile_t noeudCourant = creer_pile();

    int cle[MAX_PILE_SIZE];

    if (empiler(noeudCourant, a) != 1)
        return;

    while (!pile_vide(noeudCourant))
    {
        taillePile = noeudCourant->sommet;

        while (taillePile > 0)
        {
            tmp = depiler(noeudCourant);
            if (tmp->t == 2)
            {
                cle[cpt] = tmp->cles[1];
                cpt++;
                if (tmp->fils[1]->t != 0 && empiler(noeudCourant, tmp->fils[1]) != 1)
                    return;
                if (tmp->fils[2]->t != 0 && empiler(noeudCourant, tmp->fils[2]) != 1)
                    return;
            }
            else if (tmp->t == 3)
            {
                cle[cpt] = tmp->cles[0];
                cpt++;
                cle[cpt] = tmp->cles[1];
                cpt++;
                if (tmp->fils[0]->t != 0 && empiler(noeudCourant, tmp->fils[0]) != 1)
                    return;
                if (tmp->fils[1]->t != 0 && empiler(noeudCourant, tmp->fils[1]) != 1)
                    return;
                if (tmp->fils[2]->t != 0 && empiler(noeudCourant, tmp->fils[2]) != 1)
                    return;
            }
            else if (tmp->t == 4)
            {
                cle[cpt] = tmp->cles[0];
                cpt++;
                cle[cpt] = tmp->cles[1];
                cpt++;
                cle[cpt] = tmp->cles[2];
                cpt++;
                if (tmp->fils[0]->t != 0 && empiler(noeudCourant, tmp->fils[0]) != 1)
                    return;
                if (tmp->fils[1]->t != 0 && empiler(noeudCourant, tmp->fils[1]) != 1)
                    return;
                if (tmp->fils[2]->t != 0 && empiler(noeudCourant, tmp->fils[2]) != 1)
                    return;
                if (tmp->fils[3]->t != 0 && empiler(noeudCourant, tmp->fils[3]) != 1)
                    return;
            }
            taillePile--;
        }
    }
    int j, k, c;
    for (j = 0; j < cpt; j++)
    {
        for (k = j + 1; k < cpt; k++)
        {
            if (cle[j] > cle[k])
            {
                c = cle[j];
                cle[j] = cle[k];
                cle[k] = c;
            }
        }
    }
    for (j = 0; j < cpt; j++)
    {
        printf("%d ", cle[j]);
    }
}

Arbre234 ajouter_noeud(Arbre234 *a, Arbre234 b)
{

    if (b == NULL || b->t == 0)
        return *a;
    else if (b->t == 2)
    {
        ajouter_cle(a, b->cles[1], 0, NULL);
        ajouter_noeud(a, b->fils[1]);
        ajouter_noeud(a, b->fils[2]);
        return *a;
    }
    else if (b->t == 3)
    {
        ajouter_cle(a, b->cles[0], 0, NULL);
        ajouter_cle(a, b->cles[1], 0, NULL);
        ajouter_noeud(a, b->fils[0]);
        ajouter_noeud(a, b->fils[1]);
        ajouter_noeud(a, b->fils[2]);
        return *a;
    }
    else
    {
        ajouter_cle(a, b->cles[0], 0, NULL);
        ajouter_cle(a, b->cles[1], 0, NULL);
        ajouter_cle(a, b->cles[2], 0, NULL);
        ajouter_noeud(a, b->fils[0]);
        ajouter_noeud(a, b->fils[1]);
        ajouter_noeud(a, b->fils[2]);
        ajouter_noeud(a, b->fils[3]);
        return *a;
    }
}

void Detruire_Cle(Arbre234 *a, int cle)
{
    Arbre234 b = RechercherCle(*a, cle);
    if (b == NULL)
    {
        return;
    }
    else
    {
        Arbre234 c = NULL;
        if (b->t == 0)
        {
            return;
        }
        else if (b->t == 2)
        {
            Arbre234 tmp1 = b->fils[1];
            Arbre234 tmp2 = b->fils[2];
            c = ajouter_noeud(&c, tmp1);
            c = ajouter_noeud(&c, tmp2);
        }
        else if (b->t == 3)
        {
            for (int i = 0; i < 2; i++)
            {
                if (b->cles[i] != cle)
                    ajouter_cle(&c, b->cles[i], 0, NULL);
            }
            Arbre234 tmp0 = b->fils[0];
            Arbre234 tmp1 = b->fils[1];
            Arbre234 tmp2 = b->fils[2];
            c = ajouter_noeud(&c, tmp0);
            c = ajouter_noeud(&c, tmp1);
            c = ajouter_noeud(&c, tmp2);
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                if (b->cles[i] != cle)
                    ajouter_cle(&c, b->cles[i], 0, NULL);
            }
            Arbre234 tmp0 = b->fils[0];
            Arbre234 tmp1 = b->fils[1];
            Arbre234 tmp2 = b->fils[2];
            Arbre234 tmp3 = b->fils[3];
            c = ajouter_noeud(&c, tmp0);
            c = ajouter_noeud(&c, tmp1);
            c = ajouter_noeud(&c, tmp2);
            c = ajouter_noeud(&c, tmp3);
        }
        if (b == *a)
            *a = NULL;
        else
            free(b);
        *a = ajouter_noeud(a, c);
    }
      free(b);
    *a=ajouter_noeud(a,c);
    Arbre234 f=NULL;
    f=ajouter_noeud(&f,*a);
    *a=f;
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

    //printf ("Nombre niveaux: %d\n", hauteur (a)) ;

    //printf("Nombre cle : %d\n", NombreCles(a));

    //printf("CleMax: %d\n",CleMax(a));
    printf("\nParcours largeur:\n");
    Afficher_Cles_Largeur(a);
    printf("\n");

    //printf("cle trié r: ");Affichage_Cles_Triees_Recursive(a);printf("\n");
    //printf("cle trié nr: ");Affichage_Cles_Triees_NonRecursive(a);printf("\n");

    //a=RechercherCle(a,50);
    Detruire_Cle(&a, 50);
    //a=noeud_max(a);
    afficher_arbre(a, 0);
    return 0;
  //a=RechercherCle(a,200);
  //a=noeud_max(a);
  afficher_arbre(a,0);
  return 0;
}
