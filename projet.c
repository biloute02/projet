#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"def.h"
#include"tri.h"
#define NL 50000 //Nombre de lignes maximum du fichier à chargé (excepté la première) <---
#define TT 30000 //Temps en miliseconde maximal pour le tri d'un tableau

#define fonTRI triInsertion //Indiquer la fonction de tri à utiliser pour trier le tableau <---
#define STR_VALUE(arg) #arg 
#define HELLO(name) STR_VALUE(name) 
#define strTRI HELLO(fonTRI)


donnees tabD[NL];
donnees tabDCopie[NL];

void afficheTab(){
	int i;
	for (i=0; i<NL; i++){
		printf("%s,%s,%s,%s\n", tabD[i].numero, tabD[i].rue, tabD[i].ville, tabD[i].code_postal);
	}
}

void copieTab(donnees tabDcopie[NL],donnees tabD[NL]){
	int i, j;
	for (i=0; i<NL; i++){
		for (j=0; j<50; j++){  
			tabDCopie[i].numero[j]=tabD[i].numero[j];
			tabDCopie[i].rue[j]=tabD[i].numero[j];
			tabDCopie[i].ville[j]=tabD[i].numero[j];
			tabDCopie[i].code_postal[j]=tabD[i].numero[j];
		}
	}
	printf("Copié!\n");
}

int main(){	
	int i, j;
	char ligne[200];
	char* ligneCopie;//copie de ligne
	char* token;
	FILE* france=fopen("./france.csv","r"); //Fichier à lire
	FILE* temps=fopen("./tempsChargement.csv","w"); //Fichier des temps de chargement
	clock_t debut=clock(), fin; int duree; //Mesure des temps de chargement

	//chargement du tableau
	fgets(ligne, 200, france);
	printf("NUMBER,STREET,CITY,POSTCODE\n");
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
	fclose(france);
	fclose(temps);
	
	//tri du tableau chargé
	i=0;
	duree=0;
	temps=fopen("./temps"strTRI".csv","w");
	while(duree<TT&&i<=NL){
		copieTab(tabDCopie,tabD);
		debut=clock();
		fonTRI(i,tabDCopie);
		fin=clock();
		duree=1000*(fin-debut)/CLOCKS_PER_SEC;
		fprintf(temps,"%d,%d\n",i,duree);
		i=i+10000;
	}
	fclose(temps);
	return 0;
}


				
