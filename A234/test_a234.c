#include <stdio.h>
#include "a234.h"

Arbre234 arbre = NULL;

void help(void)
{
	printf("\
Commande possible (commande: description):\n\
\t 0: Lire un arbre\n\
\t 1: Ajouter une clef à l'arbre\n\
\t 2: Détruire une clef de l'arbre\n\
\t 3: Afficher l'arbre\n\
\t 4: Hauteur de l'arbre\n\
\t 5: Nombre de clef total de l'arbre\n\
\t 6: Obtenir la clef maximale de l'arbre\n\
\t 7: Obtenir la clef minimale de l'arbre\n\
\t 8: Trouver une clef dans l'arbre\n\
\t 9: Obtenir le noeud maximal récursivement\n\
\t10: Obtenir le noeud maximal non-récursivement\n\
\t11: Afficher l'arbre en largeur\n\
\t12: Afficher les clefs trié de l'arbre récursivement\n\
\t13: Afficher les clefs trié de l'arbre non-récursivement\n\
\t-1: Quitter le programme\n\
\t__: Affichage de l'aide\n\
");
}

int securite(void){
	return arbre != NULL;
}

void affichage_noeud(Arbre234 a){
	if(a == NULL || a->t == 0){
		printf("Noeud vide ou inexistant\n");
	}
	else if(a->t == 2){
		printf("(%d)\n", a->cles[1]);
	}
	else if(a->t == 3){
		printf("(%d, %d)\n", a->cles[0], a->cles[1]);
	}
	else if(a->t == 4){
		printf("(%d, %d, %d)\n", a->cles[0], a->cles[1], a->cles[2]);
	}
}

void redirection(int input)
{
	Arbre234 tmp;
	char string[200];
	int clef;
	switch (input)
	{
	case 0: //lire_arbre
		printf("Emplacement du fichier: ");
		scanf("%s", string);
		arbre = lire_arbre(string);
		if(arbre == NULL)
			printf("Erreur: fichier non trouvé ou non reconnue\n");
		break;
	case 1: //ajouter_cle
		printf("Entrer la clef à ajouter: ");
		scanf("%d", &clef);
		ajouter_cle(&arbre, clef, 0, NULL);
		break;
	case 2: //Detruire_Cle
		printf("Entrer une clef à détruire: ");
		scanf("%d", &clef);
		Detruire_Cle(&arbre, clef);
		break;
	case 3: //afficher_arbre
		afficher_arbre(arbre, 0);
		break;
	case 4: //hauteur
		clef = hauteur(arbre);
		printf("Hauteur de l'arbre == %d\n", clef);
		break;
	case 5: //NombreCles
		clef = NombreCles(arbre);
		printf("Nombre de clef de l'arbre == %d\n", clef);
		break;
	case 6: //CleMax
		clef = CleMax(arbre);
		printf("Clef maximale de l'arbre == %d\n", clef);
		break;
	case 7: //CleMin
		clef = CleMin(arbre);
		printf("Clef minimale de l'arbre == %d\n", clef);
		break;
	case 8: //RechercherCle
		printf("Entrer une clef à trouver: ");
		scanf("%d", &clef);
		tmp = RechercherCle(arbre, clef);
		if(tmp != NULL)
			printf("Clef trouvé!\n");
		else
			printf("Clef non trouvé!\n");
		break;
	case 9: //noeud_max
		tmp = noeud_max(arbre);
		affichage_noeud(tmp);
		break;
	case 10: //noeud_max_nr
		tmp = noeud_max_nr(arbre);
		affichage_noeud(tmp);
		break;
	case 11: //Afficher_Cles_Largeur
		Afficher_Cles_Largeur(arbre);
		break;
	case 12: //Affichage_Cles_Triees_Recursive
		Affichage_Cles_Triees_Recursive(arbre);
		printf("\n");
		break;
	case 13: //Affichage_Cles_Triees_NonRecursive
		Affichage_Cles_Triees_NonRecursive(arbre);
		printf("\n");
		break;
	case -1:
		return;
	default:
		help();
		return;
	}

}

int main(int narg, char **args)
{
	int input;
	help();
	do
	{
		printf("$ ");
		scanf("%d", &input);
		redirection(input);
	} while (input != -1);
	return 1;
}