#ifndef DEF_H
#define DEF_H

/* 
Element : taille maximale
Numero : 5
Rue : >100
Ville : 45
Code_postal : 5
--> tElement = taille maximale +1 ('\0' terminant la chaîne)
    tElement > 1 
*/

enum taille{tNumero=6, tRue=46, tVille=46, tCode_postal=6}; //Mode pour avoir des lignes complètes
//enum taille{tNumero=1, tRue=1, tVille=1, tCode_postal=6}; //Mode optimisé au tri du code_postal

typedef struct donnees {
    char numero[tNumero], rue[tRue], ville[tVille], code_postal[tCode_postal];
} donnees; 

#endif
