#ifndef RECHERCHE_H
#define RECHERCHE_H
#include"def.h"
#define MODE 1 // 1 : mode débugage

//
int rechercheSequentielle(char codePostal[6], int maxNL, donnees tab[maxNL]){
	if (MODE) printf("Recherche séquentielle");
	int i;
	int compt=0;
	printf("\nRésulat de la recherche:\nNUMBER,STREET,CITY,POSTCODE\n");
	for (i=0;i<maxNL;i++){
		if (!strcmp(codePostal,tab[i].code_postal)){
			printf("%s,%s,%s,%s\n",tab[i].numero,tab[i].rue,tab[i].ville,tab[i].code_postal);
			compt+=1;
		}
	}
	putchar('\n');
	return compt;
}	

/*
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
			p=q;
		} else if (comp<0){
			r=q;
		} else {
			p=q;
			r=q;
			test=0;
		}
	}
	
	printf("\nRésulat de la recherche:");	
	afficheTab(p,q-1,tab);
	return q-p+1;
	}
}
*/

int rechercheLineaire(char codePostal[6], int maxNL, donnees tab[maxNL]){
}

#endif 
