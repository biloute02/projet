/*
 * Fonctions relatives au tri des tableaux de données.
 */
#ifndef TRI_H
#define TRI_H
#include"def.h"
#include"outils.h"
#define MODE 1 // 1:mode débugage

//Tri rapide (pivot, partionnement, appels récursifs) p : première indice du tableau, n : taille du tableau
void triRapideCode(int p, int r, int n, donnees tab[n]){
	if (r-p+1<2) return;
	int i, j, len;
	i=p, j=p;
	len=sizeof(tab[p].code_postal);
	//pivot
	donnees pivot, temp;
	pivot=tab[r];	
	//partionnement
	for (i; i<r; i++){
		if (strcmp(tab[i].code_postal,pivot.code_postal)<=0){
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
	triRapideCode(p, j-1, n, tab);
	triRapideCode(j+1, r, n, tab);
}

//Tri rapide
void triRapide(int n, donnees tab[n]){
	if (MODE) printf("Tri rapide\n");
	int p=0;
	triRapideCode(p, n-1, n, tab);	
}

//Tri fusion
void triFusionCode(int p, int r, int n, donnees tab[n]){
	//Séparation du tableau en deux parties
	if (r-p+1<2) return;
	int q;
	q=(r+p)/2;
	//Appels récursifs sur les deux sous-parties
	triFusionCode(p, q, n, tab);
	triFusionCode(q+1, r, n, tab);
	//On fusionne les deux parties triées
	int i, j, k1=0, k2=0;
	//donnees tab1[q-p+2], tab2[r-q+1+2];
	donnees *tab1, *tab2;
	tab1 = malloc(sizeof(donnees)*(q-p+2));
	tab2 = malloc(sizeof(donnees)*(r-q+1+2));
	size_t len=sizeof(tab1[0].code_postal);
	for (i=p, j=0; i<=q; i++, j++){
		tab1[j]=tab[i];
	}
	tab1[j]=(struct donnees){{0},{0},{0},{"99999\0"}};//problème si numero, ville ou rue nulles
	for (j=0; i<=r; i++, j++){
		tab2[j]=tab[i];
	}	
	tab2[j]=(struct donnees){{0},{0},{0},{"99999\0"}};
	for (i=p;i<=r;i++){
		if (strcmp(tab1[k1].code_postal,tab2[k2].code_postal)>0){
			tab[i]=tab2[k2];
			k2++;
		}
		else {
			tab[i]=tab1[k1];
			k1++;
		}
	}
	free(tab1);
	free(tab2);
}

//Tri fusion
void triFusion(int n, donnees tab[n]){
	//afficheTab(0, n, tab);
	if (MODE) printf("Tri fusion\n");
	int p=0;
	triFusionCode(p, n-1, n, tab);
	//afficheTab(0, n, tab);
}


//Tri par insertion d'un tableau de données
void triInsertion(int n, donnees tab[n]){
	if (MODE) printf("Tri insertion\n");
	int i, j, len;
        donnees	val;
	len=sizeof(val.code_postal);
	for (i=1;i<n;i++){
		val=tab[i];
		j=i;
		while (j>0&&strcmp(tab[j-1].code_postal,val.code_postal)>0){
			tab[j]=tab[j-1];
			j--;
		}
		tab[j]=val;
	}
}

//Tri par sélection 
void triSelection(int n, donnees tab[n]){
	if (MODE) printf("Tri selection\n");
	int i, j, len;
	donnees val;
	len=sizeof(val.code_postal);	
	for (i=0;i<n-1;i++){
		val=tab[i];
		for (j=i+1;j<n;j++){
			if (strcmp(tab[j].code_postal,val.code_postal)>0) val=tab[j];
		}
		tab[j-1]=tab[i];	
		tab[i]=val;
	}
}

//Inverse toutes les valeurs entre i et j
void InverseTab( int i, int j, donnees tableau[j+1]) {
    int h;
    donnees passage;
    for(h=i; h<=(i+j)/2; h++) {
        passage=tableau[h];
        tableau[h]=tableau[j-(h-i)];
        tableau[j-(h-i)]=passage;
    }
}

//Max parmi ceux d'indices inférieurs ou égal à 'i'
int LeMax(int i, donnees tableau[i]) {
    int k, max=0;
    for(k=0; k<i; k++) {
        if (strcmp(tableau[k].code_postal, tableau[max].code_postal)>0) {
            max=k;
        }
    }
    return max;
}

//Tri crêpes
void triBreton(int i, donnees tableau[i]) {
    if (MODE) printf("Tri Breton\n");
    int c, d;
    for(c=i; c>=1; c--) {
        d=LeMax(c, tableau);
        if(d!=c) {
            InverseTab( 0, d, tableau);
            InverseTab( 0, c-1, tableau);
        }
    }
}
#endif
