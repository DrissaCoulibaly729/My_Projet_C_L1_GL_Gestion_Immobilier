#ifndef IMMOBILIERE_H_INCLUDED
#define IMMOBILIERE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>




#define FICHIER_BAILLEUR "bailleurs.bin"
#define FICHIER_LOCATION "locations.bin"
#define FICHIER_CLIENT "clients.bin"
#define FICHIER_CONTRAT "contrats.bin"
#define FICHIER_PAIEMENT "paiements.bin"
#define FICHIER_UTILISATEURS "utilisateurs.bin"


/*********************************************************/
typedef struct
{
	int jour,mois,annee;
}DATE;
                          /*
                          structure Date
                          */

typedef enum {
    MAISON,
    APPARTEMENT,
    STUDIO
} TypeLocation;
                          /*
                          structure Type location
                          */

typedef struct {
    int id,CIN,tel;
    char nom[50],prenom[50],adresse[100];
} BAILLEUR;
                          /*
                          structure Bailleur
                          */

typedef struct {
    int id,bailleurId,type;
    char libelle[50],adresse[100];
    float prix;
} LOCATION;
                          /*
                          structure Location
                          */

typedef struct {
    int id,CIN,tel;
    char nom[50],prenom[50],email[100],loginGest[20];
} CLIENT;

typedef struct {
    int id,modePaiement,clientId,locationId;
    char loginGest[20];
    DATE date_DEB,date_FIN; /*date_FIN doit etre vide au moment de l'ajout contrat et
     doit etre modifier au moment de la modification contrat et ildoit etre > a la date_DEB*/
} CONTRAT;

typedef struct {
    int id,contratId,clientId;
    char loginGest[20];
   DATE datePaiement;
} PAIEMENT;

typedef struct {
	int typeUser,id;
    char nom[50],prenom[50],login[20],password[50],email[100];
} USER;

/***************************************************************/
void ajouterBailleur(BAILLEUR bailleur);
void modifierBailleur(int bailleurId, BAILLEUR bailleur);
void supprimerBailleur(int bailleurId);
BAILLEUR chercherBailleur(int bailleurId);
void afficherBailleurs();
/****************************************************************/
int choisirTypelocation(void);
void ajouterLocation(LOCATION location);
void modifierLocation(int locationId, LOCATION location);
void supprimerLocation(int locationId);
LOCATION chercherLocation(int locationId);
void afficherLocations();
/*****************************************************************/
void ajouterClient(CLIENT client);
void modifierClient(int clientId, CLIENT client);
void supprimerClient(int clientId);
CLIENT chercherClient(int clientId);
void afficherClients();
/**************************************************************/
int choisirLemodepaiement(void);
void ajouterContrat(CONTRAT contrat); //Date fin est vide
void modifierContrat(int contratId, CONTRAT contrat);
void supprimerContrat(int contratId);
CONTRAT chercherContrat(int contratId);
void afficherContrats();
/********************************************************************/
void ajouterPaiement(PAIEMENT paiement);
void afficherPaiements();
void enregistrerPaiement(int idContrat,  DATE datePaiement);
/********************************************************************/
int typeUser();
void ajouterUtilisateur(USER utilisateur); //Le mots de passe doit etre chiffre
void modifierUtilisateur(char login [], USER utilisateur);
void supprimerUtilisateur(char login []);
USER chercherUtilisateur(char login []);
void afficherUtilisateurs();
/******************************************************************/
void rechercherContratsClient(int clientId);
/*un Client a un Contrat si il y'a sont l'id dans le fichier contrat et si la date_FIN de sont contrat
dans le fichier contrat est vide*/
void rechercherLocationsDisponibles(TypeLocation type);
/*une location est disponible si il y'a pas sont l'id dans le fichier contrat ou si sa date_FIN dans le
fichier contrat n'est pas vide*/
void rechercherUtilisateurParLoginEmail(char login);
/****************************************************************/
void rechercherUtilisateurParLogin();
void rechercherUtilisateurParEmail();
int verifemailunique(char email []);//c'est une function qui doit verifier si l'Email existe dans le fichier user il retourne 1 si oui et 0 si non
int verifloginunique(char login []);//c'est une function qui doit verifier si le login existe dans le fichier user il retourne 1 si oui et 0 si non
int verifCINunique(int CIN);//c'est une function qui doit verifier si le CIN existe dans le fichier bailleur et Client il retourne 1 si oui et 0 si non
int veriftelunique(int tel);//c'est une function qui doit verifier si le Tel existe dans le fichier bailleur et Client il retourne 1 si oui et 0 si non
void chiffrementMotDePasse(char motDePasse[]);
void dechiffrementMotDePasse(char motDePasse[]);
int saisirVariableCIN();
int saisirVariableTEL();
int saisirVariable();
int contratExiste(DATE date_FIN);//c'est une fonction qui prend la date_Fin retourne 1 si la date fin est vide sinon 0
USER authentifierUtilisateur(char login[], char password[]);//le mots de passe doit etre dechiffre avant de compare
DATE scanDate(char N[]);
int verifDate(char N[]);
void printDate(DATE date, char N[]);
void menu();


#endif // IMMOBILIERE_H_INCLUDED
