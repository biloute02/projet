#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"def.h" 
#include"outils.h"
#define NL 500000 //Nombre de lignes maximum du fichier à chargé (excepté la première) <---

#define TRI 1 // 1 : étudier une fonction de trie, 0 : sinon
#define fonTRI triRapide //Indiquer la fonction de tri dont on veut étudier la complexité (triSelection,triInsertion,triRapide,triFusion) <---
#define TT 30 //Temps en seconde maximal pour le tri d'un tableau <---
#define STR_VALUE(arg) #arg 
#define HELLO(name) STR_VALUE(name) 
#define strTRI HELLO(fonTRI)
#include"tri.h"//Fonctions de tri 

#define RECHERCHE 1 // 1 : activer la recherche d'éléments dans le tableau, 0 : sinon
#include"recherche.h"//Fonctions de recherche d'élément 

donnees tabD[NL];
donnees tabDCopie[NL];

int main(){	
	int i, j, maxi;
	char ligne[200];
	char* ligneCopie;//copie de ligne
	char* token;
	FILE* france=fopen("./france.csv","r"); //Fichier à lire
	FILE* temps=fopen("./tempsChargement.csv","w"); //Fichier des temps de chargement
	clock_t debut=clock(), fin; int duree; //Mesure des temps de chargement

	//chargement du tableau
	printf("Chargement tableau\n");
	fgets(ligne, 200, france);
	for (i=0; i<NL; i++){
		if (fgets(ligne, 200, france)==NULL) break; 
		ligneCopie=strdup(ligne);
		for (j=0; ligneCopie!=NULL; j++){
			token=strsep(&ligneCopie,",");    
			if (j==2) strcpy(tabD[i].numero,token);
			else if (j==3) strcpy(tabD[i].rue,token);
			else if (j==5) strcpy(tabD[i].ville,token);
			else if (j==8) strcpy(tabD[i].code_postal,token);
		}
		if ((i+1)%100000==0){
			fin=clock();
			duree=1000*(fin-debut)/CLOCKS_PER_SEC;
			fprintf(temps,"%d,%d\n",i+1,duree);
		}
	}
	maxi=i;
	fclose(france);
	fclose(temps);

	//tri du tableau chargé
	if (TRI){
		i=0;
		duree=0;
		srand(time(NULL));
		copieTab(NL,tabDCopie,tabD);
		temps=fopen("./temps"strTRI".csv","w");
		while(duree<TT*1000&&i<=maxi){
			melangeTab(NL,tabDCopie);
			printf("i : %d\n",i);
			debut=clock();
			fonTRI(i,tabDCopie);
			fin=clock();
			duree=1000*(fin-debut)/CLOCKS_PER_SEC;
			fprintf(temps,"%d,%d\n",i,duree);
			printf("duree(ms) : %d\n\n",duree);	
			i=i+20000;
		}
		fclose(temps);
	}

	//recherche d'un élément du tableau
	if (RECHERCHE){
	}

	return 0;
}



				
