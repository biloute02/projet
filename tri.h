/*
 * Fonctions relatives au tri des tableaux de données.
 */
#ifndef TRI_H
#define TRI_H
#include"def.h"
#include"outils.h"
#define MODE 1 // 1:mode debugage

//tri rapide (pivot, partionnement, appels récursifs) p : première indice du tableau, n : taille du tableau
void partionner(int p, int r, int n, donnees tab[n]){
	if (r-p+1<2) return;
	int i, j, len;
	i=p, j=p;
	len=sizeof(tab[p].code_postal);
	//pivot
	donnees pivot, temp;
	pivot=tab[r];	
	//partionnement
	for (i; i<r;i++){
		if (!aSupb(len,tab[i].code_postal,pivot.code_postal)){
			temp=tab[i];
			tab[i]=tab[j];	
			tab[j]=temp;
			j++;
		}
	}
	temp=tab[j];
	tab[j]=pivot;
	tab[r]=temp;
	//appels récursifs
	partionner(p, j-1, n, tab);
	partionner(j+1, r, n, tab);
}

//tri rapide
void triRapide(int n, donnees tab[n]){
	if (MODE) printf("Tri rapide\n");
	int p=0;
	partionner(p, n-1, n, tab);	
}

//tri par insertion d'un tableau de données
void triInsertion(int n, donnees tab[n]){
	if (MODE) printf("Tri insertion\n");
	int i, j, len;
        donnees	val;
	len=sizeof(val.code_postal);
	for (i=1;i<n;i++){
		val=tab[i];
		j=i;
		while (j>0&&aSupb(len,tab[j-1].code_postal,val.code_postal)){
			tab[j]=tab[j-1];
			j--;
		}
		tab[j]=val;
	}
}

//tri par sélection 
void triSelection(int n, donnees tab[n]){
	if (MODE) printf("Tri selection\n");
	int i, j, len;
	donnees val;
	len=sizeof(val.code_postal);	
	for (i=0;i<n-1;i++){
		val=tab[i];
		for (j=i+1;j<n;j++){
			if (aSupb(len,tab[j].code_postal,val.code_postal)) val=tab[j];
		}
		tab[j-1]=tab[i];	
		tab[i]=val;
	}
}

#endif
