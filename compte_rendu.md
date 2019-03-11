# **Algorithmique avancée**

# **TP 2** - [Arbre 2-3-4](https://fr.wikipedia.org/wiki/Arbre_2-3-4 "Page Wikipedia")

## Analyse des fonctions:

---

```C
//Fonction récursive renvoyant le nombre de clef d'un arbre 2-3-4
int NombreCles (Arbre234 a)
```

Pour la fonction `NombreCles` nous avons tout d'abord fais des conditions pour chacun des cas possibles (en fonction des types). Puis nous avons remarqué que le nombre de clef(s) d'un noeud non nul et non vide est égal à son type moins 1 (plus le nombre de clef(s) de ses fils). Nous avons donc pu supprimer toutes les conditions relatif au type du noeud.

---

```C
//Fonction récursive renvoyant la clef maximal d'un arbre 2-3-4
int CleMax (Arbre234 a)
```

Pour la fonction `CleMax` nous avons aussi d'abord réalisé toutes les conditions en fonction du type du noeud courant. Et nous avons trouvé que le max se trouvait toujours soit dans le fils le plus à droite du noeud courant soit, si il était vide, la clef la plus à droite du noeud courant. Or être "le plus à droite" est lié au type du noeud, donc nous pensions pouvoir trouver un moyen d'enlever la majoritée de nos conditions comme dans la fonction `NombreCles`.

Mais cela ne fut pas possible car dans l'implémentation fournis d'un arbre 2-3-4, les données (fils et clefs) sont stocké de différente manière en fonction du type du noeud dans le quelle elles sont.

* Le type 2 stock ses données partant de 1.
* Les types 3 et 4 stockent leur données en partant de 0.

Nous avons donc séparé le type 2, des types 3 et 4 dans notre fonction.

```C
//Conditions utilisé pour les types 3 et 4
if(a->fils[a->t - 1]->t == 0)
    return a->cles[a->t - 2];
else 
    return CleMax(a->fils[a->t - 1]);
```

---

```C
//Fonction récursive renvoyant la clef minimal d'un arbre 2-3-4
int CleMin (Arbre234 a)
```

La fonction `CleMin` est relativement similaire à la fonction `CleMax` dans son fonctionnement sauf que la clef minimale se trouve le plus à gauche. On doit aussi séparer le type 2, des types 3 et 4 dans la fonction. Car l'élément le plus à gauche se trouve soit en position 1 (pour le type 2) ou en position 0 (pour les types 3 et 4).  

```C
//Conditions utilisé pour les types 3 et 4
//Pour avoir les conditions utilisé par le type 2 il suffit de remplacer les [0] en [1]
if(a->fils[0]->t==0)
    return a->cles[0];
else 
    return CleMin(a->fils[0]);
```

---

```C
//Fonction récursive renvoyant le noeud contenant la clef spécifié (ou NULL si elle n'ait pas trouvé)
Arbre234 RechercherCle (Arbre234 a, int cle)
```

Dans `RechercherCle` on regarde tout d'abord si la clef recherchée ne se trouve pas dans les clefs de notre noeud courant. Si elle ne s'y trouve pas, alors on recherche dans le fils pouvant contenir cette clef. 

---

```C
//Fonction récursive renvoyant le noeud avec la somme de clef la plus grand de l'arbre donné
Arbre234 noeud_max (Arbre234 a)
//Fonction non-récursive renvoyant le noeud avec la somme de clef la plus grand de l'arbre donné
Arbre234 noeud_max_nr (Arbre234 a)
```

Nous avons décidé de réaliser cette fonction en récursif et en non-récursif pour voir les différences en termes de compléxité. Pour réaliser ces 2 fonctions, nous avons eu recours à une fonction externe calculant la somme des clefs d'un noeud appelée `somme_noeud`.

```C
//Fonction renvoyant la somme des clefs du noeud envoyé
int somme_noeud(Arbre234 a)
```

Pour `noeud_max_nr` nous utilisons deux piles pour stocker nos noeuds. Une pile nous permet de parcourir tout notre arbre et une autre pile nous permet de stocker tous les noeuds de l'arbre. On parcours donc tout l'arbre en stockant les noeuds. Puis on compare chacune des sommes des clefs de nos noeuds pour trouver le maximum.

Pour la version récursive, `noeud_max`, on calcule la somme des clefs de notre cellule courante, et on la compare avec le résultat de `noeud_max` des fils de notre noeuds (si ils sont non vide) . On renvoit la valeur maximale entre ces valeurs.

Les deux fonctions ne sont pas similaire dans leurs implémentations mais donnent le même résultat. La version récursive est plus courte et plus efficace que la version non-récursive, car la version récursive compare et parcours en même temps tandis que la version non-récursive parcours puis compare.

---

```C
//Fonction non-récursive affichant toutes les clefs de l'arbre par la largeur
void Afficher_Cles_Largeur (Arbre234 a)
```

`Afficher_Cles_Largeur` affiche les clefs des noeuds étages par étages. On traite donc des noeuds étages par étages en utilisant 2 piles (une pile pour les noeuds courant à afficher et une autre pour les suivants). On affiche tous les noeuds d'un étage tout en stockant dans une pile les fils de ces noeuds. On fait cela tant qu'il reste des fils aux noeuds courant.

---


```C
//Fonction récursive affichant toutes les clefs d'un arbre 2-3-4 par ordre croissant
void Affichage_Cles_Triees_Recursive (Arbre234 a)
//Fonction non-récursive affichant toutes les clefs d'un arbre 2-3-4 par ordre croissant
void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
```

Ces deux fonctions permettent d'afficher toutes les clefs d'un arbre 2-3-4 par ordre croissant. Pour faire cela il faut se rappeler le fonctionnement des arbres 2-3-4 car ils sont déjà triés (de part leur structure).

`Affichage_Cles_Triees_Recursive` affiche de manière logique toutes les clefs par ordre croissant. On lit toutes les clefs de gauche à droite.

`Affichage_Cles_Triees_NonRecursive` lit toutes les clefs de notre arbre en les stockant. Puis trie toutes les clefs avant de les afficher.

---


```C
//Fonction supprimant une clef d'un arbre 2-3-4 tout en gardant leur logique
void Detruire_Cle (Arbre234 *a, int cle)
```

Pour réaliser la fonction `Detruire_Cle`, nous avons créé une fonction permettant d'ajouter un noeud à un arbre.

```C
//Fonction récursive ajoutant un noeud à un arbre 2-3-4
Arbre234 ajouter_noeud(Arbre234 *a, Arbre234 b)
```

Dans la fonction `ajouter_noeud`, on ajoute à l'arbre donné la clef du noeud donné. Puis on appelle la fonction `ajouter_noeud` sur les fils du noeud donné.

La fonction `Detruire_Cle` est séparé en plusieurs étape:
1. Trouver le noeud ayant la clef passé en argument dans l'arbre.
    * Si il ne fut pas trouvé on renvoit alors le même arbre 2-3-4 sans modification.
2. On garde en mémoire les fils que le noeud avait.
3. On ajoute à un arbre temporaire ses fils (ainsi que les autres clefs du noeud si il en avait d'autre).
4. On ajoute à l'arbre donné en argument, l'arbre temporaire précédent (on rappel qu'un arbre est aussi un noeud)
5. L'étape finale est de retrier l'arbre avant de le renvoyer
    * On réalise cette étape car il se peut que l'arbre obtenue ne respecte pas la norme d'un arbre 2-3-4


---