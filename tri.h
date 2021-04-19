#include"def.h"

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

//tri par insertion d'un tableau de données
void triInsertion(int n, donnees tab[n]){
	int i, j;
        donnees	val;
	for (i=1;i<n;i++){
		val=tab[i];
		j=i;
		while (j>0&&aSupb(sizeof(val.code_postal),tab[j-1].code_postal,val.code_postal)){
			tab[j]=tab[j-1];
			j--;
		}
		tab[j]=val;
	}
}
