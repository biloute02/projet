/*
 * Fonctions de recherche de code postaux dans un tableau
 */
#ifndef RECHERCHE_H
#define RECHERCHE_H
#include"def.h"
#define MODE 1 // 1 : mode débugage

//Recherche séquentielle d'un code postal dans un tableau non trié.
int rechercheSequentielle(char codePostal[6], int maxNL, donnees tab[maxNL]){
	if (MODE) printf("Recherche séquentielle\n");
	int i;
	int compt=0;
	printf("Résulat de la recherche:\nNUMBER,STREET,CITY,POSTCODE\n");
	for (i=0;i<maxNL;i++){
		if (!strcmp(codePostal,tab[i].code_postal)){
			printf("%s,%s,%s,%s\n",tab[i].numero,tab[i].rue,tab[i].ville,tab[i].code_postal);
			compt+=1;
		}
	}
	putchar('\n');
	return compt;
}	

//Recherche dichotomique d'un code postal qui inclut un tri fusion.
int rechercheDichotomique(char codePostal[6], int maxNL, donnees tab[maxNL]){
	if (MODE) printf("Recherche dichotomique\n");
	int p=0, q, r=maxNL-1;
	char comp, test=1;
	triFusion(maxNL, tab);
	while (test){
		test=0;
		q=(p+r)/2;
		comp=strcmp(codePostal,tab[q].code_postal);	
		if (comp>0){
			//Problème si codePostal n'existe pas. Comme p<=q<r.
			//On regarde si p==q. La dichotomie est alors dans une boucle. test reste à 0. 
			if (p!=q){; 
				p=q;
				test=1;
			}
		} else if (comp<0){
			r=q;
			test=1;
		} else {
			p=q;
			test=0;
		}
	}
	//p est soi dans la liste des codes postaux, soit au code postal inférieur à celui recherché.
	//Si p est au milieu des codes postaux recherchés, on se positionne au premier élément (on décrémente p).
	while (strcmp(tab[p].code_postal,codePostal)==0){
		p--;
	}
	//Maintenant on fixe r au premier élément et on le laisse aller jusqu'au dernier.
	r=p+1;	
	printf("\nRésulat de la recherche:\nNUMBER,STREET,CITY,POSTCODE\n");
	while (strcmp(tab[r].code_postal,codePostal)==0){
		printf("%s,%s,%s,%s\n",tab[r].numero,tab[r].rue,tab[r].ville,tab[r].code_postal);
		r++;
	}
	//On obtient p, indice avant le premier résulat et r, indice après le dernier résultat.
	//Le nombre d'éléments affichés vaut r-p+1.
	return r-p-1;
}

#endif 
