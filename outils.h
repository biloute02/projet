/*
 * Fonctions utiles pour le tri, la recherche, les temps de calcul.
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
	if (*end) {  *end++ = '\0';  *stringp = end;  }  
	else *stringp = NULL;  return begin; 
}

//affiche tout ou une partie du tableau 
void afficheTab(int NL, donnees tabD[NL]){
	int i;
	printf("NUMBER,STREET,CITY,POSTCODE\n");
	for (i=0; i<NL; i++){
		printf("%s,%s,%s,%s\n", tabD[i].numero, tabD[i].rue, tabD[i].ville, tabD[i].code_postal);
	}
}

//comparer deux chaines de charactères de même longueur. Renvoie 1 si a>b ou 0 si a<=b
char aSupb(int n, char a[n], char b[n]){
	int i=0;
	while (a[i]!='\0'||b[i]!='\0'){
		if (a[i]>b[i]) return 1;
		else if (a[i]<b[i]) return 0;
		i++;
	}
	if (a[i]>b[i]) return 1;
	else return 0; // cas où a égale b
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

//permet de faire une copie du tableau pour le tri
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

#endif
