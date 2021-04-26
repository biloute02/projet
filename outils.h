/*
 * Fonctions utiles pour le tri, la recherche, le chargement d'un tableau.
 */
#ifndef OUTILS_H
#define OUTILS_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"def.h"
#define MODE 1 // 1:mode debugage

//définition de strsep si elle n'est pas incluse dans la librairie standard c
char *strsep (char **stringp, const char *delim){
      	char *begin, *end;  
	begin = *stringp;  
	if (begin == NULL) return NULL;  
	end = begin + strcspn (begin, delim);  
	if (*end) {  *end++ = '\0';  *stringp = end; }  
	else *stringp = NULL;  return begin; 
}

//affiche tout ou une partie du tableau 
void afficheTab(int i, int NL, donnees tabD[NL]){
	printf("\nNUMBER,STREET,CITY,POSTCODE\n");
	for (i; i<NL; i++){
		printf("%s,%s,%s,%s\n", tabD[i].numero, tabD[i].rue, tabD[i].ville, tabD[i].code_postal);
	}
	putchar('\n');
}

//melanger un tableau
void melangeTab(int n, donnees tab[n]){
	if (MODE) printf("Melange tableau\n");
	int i, alea;
	double r;
	donnees temp;
	for (i=0;i<n;i++){
		r=rand();
		r=r/(RAND_MAX-1);
		alea=(int)(r*n);
		temp=tab[alea];
		tab[alea]=tab[i];
		tab[i]=temp;
	}
}

//permet de faire une copie d'un tableau dans un autre tableau de même longueur
void copieTab(int NL, donnees tabDCopie[NL],donnees tabD[NL]){
	if (MODE) printf("Copie tableau\n");
	int i, j;
	for (i=0; i<NL; i++){
		for (j=0; j<50; j++){  
			tabDCopie[i].numero[j]=tabD[i].numero[j];
			tabDCopie[i].rue[j]=tabD[i].rue[j];
			tabDCopie[i].ville[j]=tabD[i].ville[j];
			tabDCopie[i].code_postal[j]=tabD[i].code_postal[j];
		}
	}
}

//Affiche la taille maximale des objets de la structure dans un tableau
void maxDonnees(int NL, donnees tab[NL]){
	size_t maxNumero=0, maxRue=0, maxVille=0, maxCode_postal=0;
       	int i;
	for (i=0;i<NL;i++){
		if (strlen(tab[i].numero)>maxNumero) maxNumero=strlen(tab[i].numero);	
		if (strlen(tab[i].rue)>maxRue) maxRue=strlen(tab[i].rue);	
		if (strlen(tab[i].ville)>maxVille) maxVille=strlen(tab[i].ville);	
		if (strlen(tab[i].code_postal)>maxCode_postal) maxCode_postal=strlen(tab[i].code_postal);
	}
	printf("Numero : %zu\nRue : %zu\nVille : %zu\nCode_postal : %zu\n", maxNumero, maxRue, maxVille, maxCode_postal);
}

#endif
