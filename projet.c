#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include"def.h"//Définitions des types de données du projet 
#include"tri.h"//Fonctions de tri 
#include"recherche.h"//Fonctions de recherche d'éléments 
#include"outils.h"//Fonctions non-classés
#define MAXNL 27381995 // Nombre de lignes total moins un dans france.csv
#define NL 30000000 // Nombre de lignes du fichier france.csv à charger pour les test de tri et de recherche (>MAXNL pour lire tout le fichier)

#define TRI 0 // 1 : étudier une fonction de trie, 0 : sinon <---
#define fonTRI triFusion //Indiquer la fonction de tri pour étudier sa complexité (triSelection,triInsertion,triRapide,triFusion,triBreton) <---
#define TT 30 //Temps en seconde maximal pour le tri d'un tableau <---
#define STR_VALUE(arg) #arg 
#define TO_STR(name) STR_VALUE(name) 
#define strTRI TO_STR(fonTRI)

#define RECHERCHE 1 // 1 : activer la recherche d'éléments dans le tableau, 0 : sinon <---
#define fonRECHERCHE rechercheSequentielle //Indiquer la fonction de recherche (rechercheSequentielle,rechercheDichotomique) <---
#define strRECHERCHE TO_STR(fonRECHERCHE)

donnees tab[MAXNL];

int main(){	
	if (TRI&&RECHERCHE) printf("ATTENTION : Tri et Recherche activés. Pour plus de convenance, sélectionnez l'un des deux modes\n\n");
	
	int i, j;
	int maxNL; //Nombre de ligne chargé dans le tableau (si NL>nombre de ligne du document)
	char ch; //Entrée (y/n)
	FILE* france; //Fichier à lire
	FILE* temps; //Fichier des temps de calcul
	clock_t debut, fin; int duree; //Mesure des temps de calcul

	printf("Etude de tri : %d\n Algorithme de tri : "strTRI"\n Nombre de lignes à trier : %d\n", TRI, NL);
	printf("Recherche d'éléments : %d\n Algorithme de recherche : "strRECHERCHE"\n" , RECHERCHE);
	printf(" Rechercher sur le nombre de ligne chargé : %d\n\n",NL);
	printf("Continuer ?(y/n)\n");
	ch=getchar();
	if (ch=='n'||ch==EOF) return 0; printf("\n");

	//Chargement du tableau
	char ligne[1024];
	char* ligneCopie;//Copie de ligne
	char* token,* adr;
	temps=fopen("./tempsChargement.csv","w");
	france=fopen("./france.csv","r");
	printf("Chargement tableau\n");
	fgets(ligne, 200, france);
	for (i=0; i<NL; i++){
		if (fgets(ligne, 1024, france)==NULL) break; 
		ligneCopie=strdup(ligne);
		adr=ligneCopie;
		for (j=0; ligneCopie!=NULL; j++){
			token=strsep(&ligneCopie,",");
			if (j==2) strncpy(tab[i].numero,token,tNumero-1); //dernier indice contenant \0
			else if (j==3) strncpy(tab[i].rue,token,tRue-1);
			else if (j==5) strncpy(tab[i].ville,token,tVille-1);
			else if (j==8) strncpy(tab[i].code_postal,token,tCode_postal-1);
		}
		free(adr);	
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
		temps=fopen("./temps"strTRI".csv","w");
		while(duree<TT*1000&&i<=maxNL){
			melangeTab(maxNL,tab);
			printf("NL : %d\n",i);
			debut=clock();
			fonTRI(i,tab);
			fin=clock();
			duree=1000*(fin-debut)/CLOCKS_PER_SEC;
			fprintf(temps,"%d,%d\n",i,duree);
			printf("Duree(ms) : %d\n\n",duree);	
			i=i+20000;
		}
		fclose(temps);
		printf("\nRésultats enregistrés dans temps"strTRI".csv\n");
	}
	
	//Recherche d'éléments du tableau
	if (RECHERCHE){
		int compt;
		char ch;
		char codePostal[6]={0};
		temps=fopen("./temps"strRECHERCHE".csv","w");
		fprintf(temps,"Code postal, Nombre d'éléments, Nombre de lignes chargées, Temps(affichage compris)\n");
		do {
			printf("\nEntre un code postal -00000- à rechercher\n");
			do {	
				while ((ch=getchar())!='\n'&&ch!=EOF);
			} while (!scanf("%5s", codePostal));
			debut=clock();
			compt=fonRECHERCHE(codePostal,maxNL,tab);
			fin=clock();
			duree=1000*(fin-debut)/CLOCKS_PER_SEC;
			fprintf(temps,"%s,%d,%d,%d\n",codePostal,compt,maxNL,duree);
			printf("Code postal recherché : %s\n", codePostal);
			printf("Nombre d'éléments trouvés : %d\n", compt);
			printf("Duree(ms) : %d\n\n", duree);
			printf("Voulez-vous rechercher une autre adresse ?(y/n)\n");
			while ((ch=getchar())!='\n'&&ch!=EOF);
			ch=getchar();
		} while (ch!='n'&&ch!=EOF);
		fclose(temps);
		printf("\nRésultats enregistrés dans temps"strRECHERCHE".csv\n");

	}

	return 0;
}
