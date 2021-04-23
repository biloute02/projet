#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"def.h" 
#include"outils.h"
#define NL 1000000 // Nombre de lignes du fichier (sauf première) (Nombre de ligne dans france.csv : 27381996)<---

#define TRI 0 // 1 : étudier une fonction de trie, 0 : sinon
#define fonTRI triFusion //Indiquer la fonction de tri dont on veut étudier la complexité (triSelection,triInsertion,triRapide,triFusion,triBreton) <---
#define TT 30 //Temps en seconde maximal pour le tri d'un tableau <---
#define STR_VALUE(arg) #arg 
#define TO_STR(name) STR_VALUE(name) 
#define strTRI TO_STR(fonTRI)
#include"tri.h"//Fonctions de tri 

#define RECHERCHE 0 // 1 : activer la recherche d'éléments dans le tableau, 0 : sinon
#include"recherche.h"//Fonctions de recherche d'éléments 

donnees tab[NL];
donnees tabCopie[NL];

int main(){	
	int i, j;
	int maxNL; //Nombre de ligne chargé dans le tableau (si NL>nombre de ligne du document)
	char ligne[1024];
	char* ligneCopie;//Copie de ligne
	char* token;
	FILE* france=fopen("./france.csv","r"); //Fichier à lire
	FILE* temps=fopen("./tempsChargement.csv","w"); //Fichier des temps de chargement
	clock_t debut, fin; int duree; //Mesure des temps de calcul

	//Chargement du tableau
	printf("Chargement tableau\n");
	fgets(ligne, 200, france);
	for (i=0; i<NL; i++){
		if (fgets(ligne, 1024, france)==NULL) break; 
		ligneCopie=strdup(ligne);
		for (j=0; ligneCopie!=NULL; j++){
			token=strsep(&ligneCopie,",");
			if (j==2) strncpy(tab[i].numero,token,tNumero-1); //dernier indice contenant \0
			else if (j==3) strncpy(tab[i].rue,token,tRue-1);
			else if (j==5) strncpy(tab[i].ville,token,tVille-1);
			else if (j==8) strncpy(tab[i].code_postal,token,tCode_postal-1);
		}
		if ((i+1)%100000==0){
			fin=clock();
			duree=1000*(fin-debut)/CLOCKS_PER_SEC;
			fprintf(temps,"%d,%d\n",i+1,duree);
		}
	}
	maxNL=i; //Nombre d'élément dans le tableau
	fclose(france);
	fclose(temps);

	//Tri du tableau chargé
	if (TRI){
		i=0; 
		duree=0;
		srand(time(NULL));
		copieTab(maxNL,tabCopie,tab);
		temps=fopen("./temps"strTRI".csv","w");
		while(duree<TT*1000&&i<=maxNL){
			melangeTab(maxNL,tabCopie);
			printf("NL : %d\n",i);
			debut=clock();
			fonTRI(i,tabCopie);
			fin=clock();
			duree=1000*(fin-debut)/CLOCKS_PER_SEC;
			fprintf(temps,"%d,%d\n",i,duree);
			printf("duree(ms) : %d\n\n",duree);	
			i=i+1000000;
		}
		fclose(temps);
	}
	
	//Recherche d'un élément du tableau
	if (RECHERCHE){
	}

	return 0;
}



				
