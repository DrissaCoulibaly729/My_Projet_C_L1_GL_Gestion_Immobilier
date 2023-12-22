/**************************************BIBLIOTHEQUE*****************************************************/

#include<stdio.h>

/***************************************CONSTATE*****************************************************/



/*************************************PROTOTYPE*****************************************************/

int myStrlen(char ch[]) ;
										/*
											c’est une fonction qui recoit une chaine de
											caractères puis retourne son nombre de caractères.
										*/

void myStrcpy(char ch1[], char ch2[]) ;
										/*
											c’est une procédure qui recoit deux
											chaines de caracteres puis copie ch2 dans ch1
										*/
void myStrupr(char ch[]);
										/*
											c’est une procédure qui recoit une chaine de
											caractères puis convertit tous ses caracteres en majuscules
										*/
void myStrlwr(char ch[]) ;
										/*
											c’est une procédure qui recoit une chaine de
											caractères puis convertit tous ses caracteres en minuscules
										*/
int myStrchr(char ch[], char x);
										/*
											c’est une fonction qui recoit une chaine de
											caracteres ch et un caractère x puis retourne 1 si x est présent dans ch
										*/
int myStrstr(char ch1[], char ch2[]);
										/*
											c’est une fonction qui recoit deux chaines de caracteres
											ch1 et ch2 puis retourne 1 si ch2 est présente dans ch1 sinon -1
										*/
int myStrcmp(char ch1[], char ch2[]);
										/*
											c’est une fonction qui recoit deux chaines de caracteres
											ch1 et ch2 puis retourne 1 si ch1 et ch2 sont identiques sinon -1
										*/
void myConjugaison(char verb[]) ;
										/*
											c’est une procédure qui recoit un verbe du premier groupe
											puis le conjugue au présent de l’indicatif
										*/
char myExtrai(char ch1[],int pos, int p,char ch2[]);
