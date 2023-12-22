/****************************************************************/
#include"immobiliere.h"









/*************************************************************************/
// Fonctions pour les bailleurs

void ajouterBailleur(BAILLEUR bailleur) {
    FILE* fichier = fopen(FICHIER_BAILLEUR, "ab");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    printf("****************************** Saisir des informations du Bailleur ******************************\n");
    do{
    	 printf("Saisir le Nom du Bailleur\n");
    	 fflush(stdin);
    	gets(bailleur.nom);
    }while(bailleur.nom[0]==32 && bailleur.nom[strlen(bailleur.nom)-1]==32);
	do{
		printf("Saisir le Prenom du Bailleur\n");
    	gets(bailleur.prenom);
	}while(bailleur.prenom[0]==32 || bailleur.prenom[strlen(bailleur.prenom)-1]==32);
	do{
		printf("Saisir l'Adresse du Bailleur\n");
   		gets(bailleur.adresse);
	}while(bailleur.adresse[0]==32 || bailleur.adresse[strlen(bailleur.adresse)-1]==32);
    	printf("Saisir le Numero de la carte Numero d'identite(maximum 7 chiffre)\n");
        do{
        	bailleur.CIN=saisirVariableCIN();
        }while(verifCINunique(bailleur.CIN)==0);

    printf("Saisir le Numero du Telephone\n");
             do{
                bailleur.tel=saisirVariableTEL();
            }while(veriftelunique(bailleur.tel)==0);


    fseek(fichier, 0, SEEK_END);
    bailleur.id = ftell(fichier) / sizeof(BAILLEUR) + 1;

    fwrite(&bailleur, sizeof(BAILLEUR), 1, fichier);

    fclose(fichier);
     printf("Le bailleur a ete ajouter avec succes et a comme id : %d\n",bailleur.id);
}

void modifierBailleur(int bailleurId, BAILLEUR bailleur) {
    int confirm,confirm1;
    FILE* fichier = fopen(FICHIER_BAILLEUR, "rb+");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    BAILLEUR tmp;
    while (fread(&tmp, sizeof(BAILLEUR), 1, fichier)) {
        if (tmp.id == bailleurId) {

                 printf("****************************** Saisir des informations du Bailleur ******************************\n");
    do{
    	 printf("Saisir le Nouveau Nom du Bailleur\n");
    	 fflush(stdin);
    	gets(bailleur.nom);
    }while(bailleur.nom[0]==32 || bailleur.nom[strlen(bailleur.nom)-1]==32);
	do{
		printf("Saisir le Nouveau Prenom du Bailleur\n");
    	gets(bailleur.prenom);
	}while(bailleur.prenom[0]==32 || bailleur.prenom[strlen(bailleur.prenom)-1]==32);
	do{
		printf("Saisir le Nouveau Adresse du Bailleur\n");
   		gets(bailleur.adresse);
	}while(bailleur.adresse[0]==32 || bailleur.adresse[strlen(bailleur.adresse)-1]==32);

            printf("voulez-vous Modifier le CIN\n");
            printf("1-OUI\n");
            printf("2-NON\n");
            printf("Votre choix : ");
            do{
                confirm=saisirVariable();
                 if (confirm !=1 || confirm !=2)
               {
                    printf("invalide ressaisir a nouveau\n");
                }
            }while(confirm!=1 && confirm!=2);
            if (confirm==1)
            {
                printf("Saisir le Numero de la carte Numero d'identite(maximum 7 chiffre)\n");
                do{
                    bailleur.CIN=saisirVariableCIN();
                }while(verifCINunique(bailleur.CIN)==0);
            }else{bailleur.CIN=tmp.CIN;}

            printf("voulez-vous Modifier le Tel\n");
            printf("1-OUI\n");
            printf("2-NON\n");
            printf("Votre choix : ");
            do{
                confirm1=saisirVariable();
                 if (confirm1 !=1 && confirm1 !=2)
               {
                    printf("invalide ressaisir a nouveau\n");
                }
            }while(confirm1!=1 && confirm1!=2);
            if (confirm1==1)
            {
               printf("Saisir le Numero du Telephone\n");
             do{
                bailleur.tel=saisirVariableTEL();
             }while(veriftelunique(bailleur.tel)==0);
            }else{bailleur.tel=tmp.tel;}
            fseek(fichier, -sizeof(BAILLEUR), SEEK_CUR);
            bailleur.id=tmp.id;
            fwrite(&bailleur, sizeof(BAILLEUR), 1, fichier);
            return;
            printf("Le bailleur avec l id %d a ete Modifier avec succes \n",bailleurId);
        }
    }
    printf("Aucun Bailleur avec cet ID n'a ete trouve.\n");
    fclose(fichier);
}

void supprimerBailleur(int bailleurId) {
    FILE* fichier = fopen(FICHIER_BAILLEUR, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    FILE* fichierTemp = fopen("temp.bin", "wb");
    if (fichierTemp == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    BAILLEUR bailleur;
    while (fread(&bailleur, sizeof(BAILLEUR), 1, fichier)) {
        if (bailleur.id != bailleurId) {
            fwrite(&bailleur, sizeof(BAILLEUR), 1, fichierTemp);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    remove(FICHIER_BAILLEUR);
    rename("temp.bin", FICHIER_BAILLEUR);
    printf("Le bailleur avec l id %d a ete supprime avec succes\n",bailleurId);
}

BAILLEUR chercherBailleur(int bailleurId) {
    BAILLEUR bailleur;
    FILE* fichier = fopen(FICHIER_BAILLEUR, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    while (fread(&bailleur, sizeof(BAILLEUR), 1, fichier)) {
        if (bailleur.id == bailleurId) {

            fclose(fichier);
            return bailleur;
        }
    }

    fclose(fichier);
    return;
}

void afficherBailleurs() {
    FILE* fichier = fopen(FICHIER_BAILLEUR, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    BAILLEUR bailleur;
    while (fread(&bailleur, sizeof(BAILLEUR), 1, fichier)) {
        printf("ID : %d\n", bailleur.id);
        printf("Nom : %s\n", bailleur.nom);
        printf("Prenom : %s\n", bailleur.prenom);
        printf("Adresse : %s\n", bailleur.adresse);
        printf("Telephone : %d\n", bailleur.tel);
        printf("CIN : %d\n", bailleur.CIN);
        printf("------------------------\n");
    }

    fclose(fichier);
}

/***************************************************************************/

// Fonctions pour les locations

int choisirTypelocation(void)
{
	LOCATION location;
//Enumeration des Types
	printf("1-Maison\n");
	printf("2-Appartement\n");
	printf("3-Studio\n");
	do{
		scanf("%d",&location.type);
		if(location.type<=0 && location.type>3){
            printf("Ce type de location n'existe\n");
		}
	}while(location.type<=0 || location.type>3);
//Retoure du choix
	return location.type;
}

void ajouterLocation(LOCATION location) {
    BAILLEUR bailleur;
    FILE* fichier = fopen(FICHIER_LOCATION, "ab");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    printf("****************************** Saisir des informations de la location ******************************\n");

    printf("Saisir l'id du bailleur de cette location\n");
    scanf("%d",&location.bailleurId);
    bailleur=chercherBailleur(location.bailleurId);
    if(bailleur.id!=location.bailleurId)
    {
        printf("bailleur avec l'id %d est introuvable\n", location.bailleurId);
        return;
    }

    do{
    	 printf("Saisir le Libelle\n");
    	 fflush(stdin);
    	 gets(location.libelle);
    }while(location.libelle[0]==32 || location.libelle[strlen(location.libelle)-1]==32);
	do{
		printf("Saisir l'Adresse du Location\n");
   		gets(location.adresse);
	}while(location.adresse[0]==32 || location.adresse[strlen(location.adresse)-1]==32);
	printf("Choisir le type de la location\n");
	location.type=choisirTypelocation();
	do{
		printf("Saisir le Prix de la location\n");
		scanf("%f",&location.prix);
	}while(location.prix<=0);

    fseek(fichier, 0, SEEK_END);
    location.id = ftell(fichier) / sizeof(LOCATION) + 1;

    fwrite(&location, sizeof(LOCATION), 1, fichier);

    fclose(fichier);
    printf("La Location a ete ajouter avec succes et a comme id : %d et a comme proprietaire %s %s avec id %d\n",location.id,bailleur.nom,bailleur.prenom,bailleur.id);
}

void modifierLocation(int locationId, LOCATION location) {
    BAILLEUR bailleur;
    FILE* fichier = fopen(FICHIER_LOCATION, "rb+");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    LOCATION tmp;
    while (fread(&tmp, sizeof(LOCATION), 1, fichier)) {
        if (tmp.id == locationId) {

    printf("****************************** Saisir des informations de la location ******************************\n");

                    printf("Saisir l'id du bailleur de cette location\n");
                    scanf("%d",&location.bailleurId);
                    bailleur=chercherBailleur(location.bailleurId);
                    if(bailleur.id!=location.bailleurId)
                    {
                        printf("bailleur avec l'id %d est introuvable\n", location.bailleurId);
                        return;
                    }

                do{
                     printf("Saisir le Libelle\n");
                     fflush(stdin);
                     gets(location.libelle);
                }while(location.libelle[0]==32 || location.libelle[strlen(location.libelle)-1]==32);
                do{
                    printf("Saisir l'Adresse du Location\n");
                    gets(location.adresse);
                }while(location.adresse[0]==32 || location.adresse[strlen(location.adresse)-1]==32);
                printf("Choisir le type de la location\n");
                location.type=choisirTypelocation();
                do{
                    printf("Saisir le Prix de la location\n");
                    scanf("%f",&location.prix);
                }while(location.prix<=0);

                fseek(fichier, -sizeof(LOCATION), SEEK_CUR);
                location.id=tmp.id;
            fwrite(&location, sizeof(LOCATION), 1, fichier);
            break;
        }
    }

    fclose(fichier);
    printf("La Location a ete Modifier avec succes et a comme id : %d et a comme proprietaire %s %s avec id %d\n",locationId,bailleur.nom,bailleur.prenom,bailleur.id);
}

void supprimerLocation(int locationId) {
    FILE* fichier = fopen(FICHIER_LOCATION, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    FILE* fichierTemp = fopen("temp.bin", "wb");
    if (fichierTemp == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    LOCATION location;
    while (fread(&location, sizeof(LOCATION), 1, fichier)) {
        if (location.id != locationId) {
            fwrite(&location, sizeof(LOCATION), 1, fichierTemp);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    remove(FICHIER_LOCATION);
    rename("temp.bin", FICHIER_LOCATION);
    printf("Location avec id %d a ete supprime avec succes",locationId);
}

LOCATION chercherLocation(int locationId) {
    LOCATION location;
    FILE* fichier = fopen(FICHIER_LOCATION, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    while (fread(&location, sizeof(LOCATION), 1, fichier)) {
        if (location.id == locationId) {
            fclose(fichier);
            return location;
        }
    }

    fclose(fichier);
    return ;
}

void afficherLocations() {
    FILE* fichier = fopen(FICHIER_LOCATION, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    LOCATION location;
    while (fread(&location, sizeof(LOCATION), 1, fichier)) {
        printf("ID : %d\n", location.id);
        printf("ID Bailleur : %d\n", location.bailleurId);
        printf("Libellé : %s\n", location.libelle);
        printf("Adresse : %s\n", location.adresse);
           switch(location.type)
            {
                case 1 :
                    printf("Type : Maison\n");
                    break;
                case 2 :
                    printf("Type : Appartement\n");
                    break;
                default :
                    printf("Type : Studio\n");
                    break;
            }
        printf("Prix : %.2f\n", location.prix);
        printf("------------------------\n");
    }

    fclose(fichier);
}
/******************************************************************/

// Fonctions pour les clients

void ajouterClient(CLIENT client) {
    USER utilisateur;
    int cpt,verif;
    FILE* fichier = fopen(FICHIER_CLIENT, "ab");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

     printf("****************************** Saisir des informations du Client ******************************\n");

     printf("Saisir Votre Login avant d'ajouter Le Client\n");
     scanf("%s",&client.loginGest);
        utilisateur=chercherUtilisateur(client.loginGest);
        if(strcmp(utilisateur.login,client.loginGest)!=0){
            printf("Utilisateur introuvable\n");
            return;
        }
    do{
    	 printf("Saisir le Nom du Client\n");
    	 fflush(stdin);
    	 gets(client.nom);
    }while(client.nom[0]==32 || client.nom[strlen(client.nom)-1]==32);
	do{
		printf("Saisir le Prenom du Client\n");
    	gets(client.prenom);
	}while(client.prenom[0]==32 || client.prenom[strlen(client.prenom)-1]==32);
	do{
		printf("Saisir l'Email du Client sans(@gmail.com)\n");
   		gets(client.email);
   		verif=verifemailunique(client.email);
   		if (strchr(client.email,'@')!=NULL || strcasecmp(client.email,"gmail")==0 || strchr(client.email,'.')!=NULL || verif==0)
   		{
   			cpt=1;
   		}else{cpt=0;}
	}while(client.email[0]==32 || client.email[strlen(client.email)-1]==32 || cpt==1);

    	printf("Saisir la carte Numero d'identite a 7 chiffre\n");
    	do{
            client.CIN=saisirVariableCIN();
        }while(verifCINunique(client.CIN)==0);

    printf("Saisir le Numero du Telephone\n");
            do{
                client.tel=saisirVariableTEL();
            }while(veriftelunique(client.tel)==0);

    fseek(fichier, 0, SEEK_END);
    client.id = ftell(fichier) / sizeof(CLIENT) + 1;

    fwrite(&client, sizeof(CLIENT), 1, fichier);

    fclose(fichier);
    printf("Le Client a ete ajouter avec succes et a comme id : %d\n",client.id);
}

void modifierClient(int clientId, CLIENT client) {
    USER utilisateur;
    int cpt,verif,confirm,confirm1,confirm3;
    FILE* fichier = fopen(FICHIER_CLIENT, "rb+");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    CLIENT tmp;
    while (fread(&tmp, sizeof(CLIENT), 1, fichier)) {
        if (tmp.id == clientId) {

                printf("****************************** Saisir des informations du Client ******************************\n");

                printf("Saisir Votre Login avant d'ajouter Le Client\n");
                scanf("%s",&client.loginGest);
                utilisateur=chercherUtilisateur(client.loginGest);
                if(strcmp(utilisateur.login,client.loginGest)!=0){
                    printf("Utilisateur introuvable\n");
                    return;
                }
    do{
    	 printf("Saisir le Nom du Client\n");
    	 fflush(stdin);
    	 gets(client.nom);
    }while(client.nom[0]==32 || client.nom[strlen(client.nom)-1]==32);
	do{
		printf("Saisir le Prenom du Client\n");
    	gets(client.prenom);
	}while(client.prenom[0]==32 || client.prenom[strlen(client.prenom)-1]==32);
        printf("voulez-vous Modifier l Email\n");
            printf("1-OUI\n");
            printf("2-NON\n");
            printf("Votre choix : ");
            do{
                confirm3=saisirVariable();
                if (confirm3 !=1 && confirm3 !=2)
               {
                    printf("invalide ressaisir a nouveau\n");
                }
            }while(confirm3!=1 && confirm3!=2);
            if (confirm3==1)
            {
            	do{
            		printf("Saisir l'Email du Client sans(@gmail.com)\n");
               		gets(client.email);
                    verif=verifemailunique(client.email);
               		if (strchr(client.email,'@')!=NULL || strcasecmp(client.email,"gmail")==0 || strchr(client.email,'.')!=NULL || verif==0)
               		{
               			cpt=1;
               		}else{cpt=0;}
	           }while(client.email[0]==32 || client.email[strlen(client.email)-1]==32 || cpt==1);
            }else{strcpy(client.email,tmp.email);}
    	 printf("voulez-vous Modifier le CIN\n");
            printf("1-OUI\n");
            printf("2-NON\n");
            printf("Votre choix : ");
            do{
                confirm=saisirVariable();
                if (confirm !=1 && confirm !=2)
                {
                   printf("invalide ressaisir a nouveau\n");
                }
            }while(confirm!=1 && confirm!=2);
            if (confirm==1)
            {
                printf("Saisir le Numero de la carte Numero d'identite(maximum 7 chiffre)\n");
                do{
                    client.CIN=saisirVariableCIN();
                }while(verifCINunique(client.CIN)==0);
            }else{client.CIN=tmp.CIN;}

            printf("voulez-vous Modifier le Tel\n");
            printf("1-OUI\n");
            printf("2-NON\n");
            printf("Votre choix : ");
            do{
                confirm1=saisirVariable();
                if (confirm1 !=1 && confirm1 !=2)
                {
                   printf("invalide ressaisir a nouveau\n");
                }
            }while(confirm1!=1 && confirm1!=2);
            if (confirm1==1)
            {
               printf("Saisir le Numero du Telephone\n");
             do{
                client.tel=saisirVariableTEL();
             }while(veriftelunique(client.tel)==0);
            }else{client.tel=tmp.tel;}

            fseek(fichier, -sizeof(CLIENT), SEEK_CUR);
            client.id=tmp.id;
            fwrite(&client, sizeof(CLIENT), 1, fichier);
            printf("Le Client a ete Modifier avec succes et a comme id : %d\n",clientId);
            break;
        }
    }

    fclose(fichier);
}

void supprimerClient(int clientId) {
    FILE* fichier = fopen(FICHIER_CLIENT, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    FILE* fichierTemp = fopen("temp.bin", "wb");
    if (fichierTemp == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    CLIENT client;
    while (fread(&client, sizeof(CLIENT), 1, fichier)) {
        if (client.id != clientId) {
            fwrite(&client, sizeof(CLIENT), 1, fichierTemp);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    remove(FICHIER_CLIENT);
    rename("temp.bin", FICHIER_CLIENT);
    printf("Le Client avec id : %d a ete supprime avec succes\n",clientId);
}

CLIENT chercherClient(int clientId) {
    CLIENT client;
    FILE* fichier = fopen(FICHIER_CLIENT, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    while (fread(&client, sizeof(CLIENT), 1, fichier)) {
        if (client.id == clientId) {


            fclose(fichier);
            return client;
        }
    }

    fclose(fichier);
    return;
}

void afficherClients() {
    FILE* fichier = fopen(FICHIER_CLIENT, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    CLIENT client;
    while (fread(&client, sizeof(CLIENT), 1, fichier)) {
        printf("ID : %d\n", client.id);
        printf("Nom : %s\n", client.nom);
        printf("Prénom : %s\n", client.prenom);
        printf("Email : %s@gmail.com\n", client.email);
         printf("CIN : %d\n", client.CIN);
        printf("Téléphone : %d\n", client.tel);
        printf("Ce client a ete Ajouter par %s",client.loginGest);
        printf("------------------------\n");
    }

    fclose(fichier);
}
/**************************************************************/

// Fonctions pour les contrats

int choisirLemodepaiement(void)
{
	CONTRAT contrat;
	printf("1-Orange Money\n");
	printf("2-Paypal\n");
	printf("3-Espece\n");
	printf("4-Cheque\n");
	printf("5-Carte Bancaire\n");
	do{
		scanf("%d",&contrat.modePaiement);
		if(contrat.modePaiement<=0 && contrat.modePaiement>5){
            printf("Ce type de location n'existe\n");
		}
	}while(contrat.modePaiement<=0 || contrat.modePaiement>5);
//Retoure du choix
	return contrat.modePaiement;
}

void ajouterContrat(CONTRAT contrat) {
    CLIENT client;
    LOCATION location;
    USER utilisateur;

    printf("Saisir Votre Login avant d'ajouter Le Contrat\n");
    scanf("%s",&contrat.loginGest);
    utilisateur=chercherUtilisateur(contrat.loginGest);
    if(strcmp(utilisateur.login,contrat.loginGest)!=0){
    printf("Utilisateur introuvable\n");
    return;
    }

    printf("Saisir l'id du client de cette Contrat\n");
    scanf("%d",&contrat.clientId);
    client=chercherClient(contrat.clientId);
    if(client.id!=contrat.clientId)
    {
        printf("Client avec l'id %d est introuvable\n", contrat.clientId);
        return;
    }

    printf("Saisir l'id de la location de cette Contrat\n");
    scanf("%d",&contrat.locationId);
    location=chercherLocation(contrat.locationId);
    if(location.id!=contrat.locationId)
    {
        printf("Location avec l'id %d est introuvable\n", contrat.locationId);
        return;
    }

    char saisirDatedebut[20],saisirDatefin[20];
    FILE* fichier = fopen(FICHIER_CONTRAT, "ab");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

	do{
		printf("Entre la date de debut du contrat avec le Format jj/mm/aaaa\n");
		fflush(stdin);
		gets(saisirDatedebut);
		contrat.date_DEB=scanDate(saisirDatedebut);
		verifDate(saisirDatedebut);
	}while(verifDate(saisirDatedebut)==-1);
	contrat.date_FIN.jour=-1;
    contrat.date_FIN.mois=-1;
    contrat.date_FIN.annee=-1;
	printf("Choisir le mode de Paiement\n");
	contrat.modePaiement=choisirLemodepaiement();

    fseek(fichier, 0, SEEK_END);
    contrat.id = ftell(fichier) / sizeof(CONTRAT) + 1;
    fwrite(&contrat, sizeof(CONTRAT), 1, fichier);

    fclose(fichier);
    printf("Contrat ajouter avec succes et a comme id %d avec l id du client %d et l id de la location %d ",contrat.id,contrat.clientId,contrat.locationId);
}

void modifierContrat(int contratId, CONTRAT contrat) {
     CLIENT client;
    LOCATION location;
    USER utilisateur;
    int confirm;

    printf("Saisir Votre Login avant d'ajouter Le Contrat\n");
    scanf("%s",&contrat.loginGest);
    utilisateur=chercherUtilisateur(contrat.loginGest);
    if(strcmp(utilisateur.login,contrat.loginGest)!=0){
    printf("Utilisateur introuvable\n");
    return;
    }

    printf("Saisir l'id du client de cette Contrat\n");
    scanf("%d",&contrat.clientId);
    client=chercherClient(contrat.clientId);
    if(client.id!=contrat.clientId)
    {
        printf("Client avec l'id %d est introuvable\n", contrat.clientId);
        return;
    }

    printf("Saisir l'id de la location de cette Contrat\n");
    scanf("%d",&contrat.locationId);
    location=chercherLocation(contrat.locationId);
    if(location.id!=contrat.locationId)
    {
        printf("Client avec l'id %d est introuvable\n", contrat.clientId);
        return;
    }

    char saisirDatedebut[20],saisirDatefin[20];
    FILE* fichier = fopen(FICHIER_CONTRAT, "rb+");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    CONTRAT tmp;
    while (fread(&tmp, sizeof(CONTRAT), 1, fichier)) {
        if (tmp.id == contratId) {

                do{
                    printf("Entre la date de debut du contrat avec le Format jj/mm/aaaa\n");
                    fflush(stdin);
                    gets(saisirDatedebut);
                    contrat.date_DEB=scanDate(saisirDatedebut);
                    verifDate(saisirDatedebut);
                }while(verifDate(saisirDatedebut)==-1);
                    printf("voulez-vous Ajouter une Date de Fin contrat \n");
                    printf("1-OUI\n");
                    printf("2-NON\n");
                    printf("Votre choix : ");
                do{
                    confirm=saisirVariable();
                    if (confirm !=1 && confirm !=2)
                    {
                       printf("invalide ressaisir a nouveau\n");
                    }
                }while(confirm!=1 && confirm!=2);
                if (confirm==1)
                {
                    do{
                        printf("Entre la date de fin du contrat avec le Format jj/mm/aaaa\n");
                        fflush(stdin);
                        gets(saisirDatefin);
                        contrat.date_FIN=scanDate(saisirDatefin);
                        verifDate(saisirDatefin);
                    }while(verifDate(saisirDatefin)==-1);
                }else{
                        contrat.date_FIN.jour=-1;
                        contrat.date_FIN.mois=-1;
                        contrat.date_FIN.annee=-1;
                }
                printf("Choisir le mode de Paiement\n");
                contrat.modePaiement=choisirLemodepaiement();

            fseek(fichier, -sizeof(CONTRAT), SEEK_CUR);
            contrat.id=tmp.id;
            fwrite(&contrat, sizeof(CONTRAT), 1, fichier);
            printf("Contrat a ete Modifier avec succes et a comme id %d avec l id du client %d et l id de la location %d ",contratId,contrat.clientId,contrat.locationId);
            break;
        }
    }

    fclose(fichier);
}

void supprimerContrat(int contratId) {
    FILE* fichier = fopen(FICHIER_CONTRAT, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    FILE* fichierTemp = fopen("temp.bin", "wb");
    if (fichierTemp == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    CONTRAT contrat;
    while (fread(&contrat, sizeof(CONTRAT), 1, fichier)) {
        if (contrat.id != contratId) {
            fwrite(&contrat, sizeof(CONTRAT), 1, fichierTemp);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    remove(FICHIER_CONTRAT);
    rename("temp.bin", FICHIER_CONTRAT);
    printf("contrat avec id %d a ete supprime avec succes",contratId);
}

CONTRAT chercherContrat(int contratId) {
    CONTRAT contrat;
    FILE* fichier = fopen(FICHIER_CONTRAT, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    while (fread(&contrat, sizeof(CONTRAT), 1, fichier)) {
        if (contrat.id == contratId) {

            fclose(fichier);
            return contrat;
        }
    }

    fclose(fichier);
    return;
}

void afficherContrats() {
    char saisirdateFin[20],saisirdateDeb[20];
    FILE* fichier = fopen(FICHIER_CONTRAT, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    CONTRAT contrat;
    while (fread(&contrat, sizeof(CONTRAT), 1, fichier)) {
        printf("ID : %d\n", contrat.id);
        printf("ID Client : %d\n", contrat.clientId);
        printf("ID Location : %d\n", contrat.locationId);
        printf("Date début : ");
        printDate(contrat.date_DEB,saisirdateFin);
           if(contrat.date_FIN.jour!=-1)
            {
                printf("Date fin : ");
                printDate(contrat.date_FIN,saisirdateFin);
	        }else{printf("Date fin : \n");}
	        printf("Ce Contrat a ete ajouter par %s",contrat.loginGest);
        printf("------------------------\n");
    }

    fclose(fichier);
}
/*********************************************************/

// Fonctions pour les paiements

void ajouterPaiement(PAIEMENT paiement) {
    CONTRAT contrat;
    CLIENT client;
    USER utilisateur;

    printf("Saisir Votre Login avant d'ajouter Le Paiement\n");
    scanf("%s",&paiement.loginGest);
    utilisateur=chercherUtilisateur(paiement.loginGest);
    if(strcmp(utilisateur.login,paiement.loginGest)!=0){
    printf("Utilisateur introuvable\n");
    }

    printf("Saisir l'id du client de cette Paiement\n");
    scanf("%d",&paiement.clientId);
    client=chercherClient(paiement.clientId);
    if(client.id!=paiement.clientId)
    {
        printf("Client avec l'id %d est introuvable\n", paiement.clientId);
        return;
    }

    printf("Saisir l'id de la location de cette paiement\n");
    scanf("%d",&paiement.contratId);
    contrat=chercherContrat(paiement.contratId);
    if(contrat.id!=paiement.contratId)
    {
        printf("Contrat avec l'id %d est introuvable\n", contrat.clientId);
        return;
    }

    char saisirDate[11];
    FILE* fichier = fopen(FICHIER_PAIEMENT, "ab");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    do{
		printf("Entre la date de paiement avec le Format jj/mm/aaaa\n");
		fflush(stdin);
		gets(saisirDate);
		paiement.datePaiement=scanDate(saisirDate);
		verifDate(saisirDate);
	}while(verifDate(saisirDate)==-1);
	 fseek(fichier, 0, SEEK_END);
    paiement.id = ftell(fichier) / sizeof(CONTRAT) + 1;
    fwrite(&paiement, sizeof(PAIEMENT), 1, fichier);

    fclose(fichier);
    printf("paiement ajouter avec succes et a comme id %d avec id du client %d et celle du contrat %d \n",paiement.id,paiement.clientId,paiement.contratId);
}

void afficherPaiements() {
    PAIEMENT paiement;
     char saisirdatepaie[20];
    FILE* fichier = fopen(FICHIER_PAIEMENT, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    while (fread(&paiement, sizeof(PAIEMENT), 1, fichier)) {
        printf("ID Paiement : %d\n", paiement.id);
        printf("ID Contrat : %d\n", paiement.contratId);
        printf("ID Client : %d\n", paiement.clientId);
        printf("Date Paiement : ");
        printDate(paiement.datePaiement,saisirdatepaie);
        printf("Ce paiement a ete Ajouter par %s",paiement.loginGest);
        printf("------------------------\n");
    }

    fclose(fichier);
}

void enregistrerPaiement(int idContrat,  DATE datePaiement) {
    char date[20];
    PAIEMENT paiement;
    // Rechercher le contrat dans le fichier binaire des contrats
    CONTRAT contrat,ct;
    ct=chercherContrat(idContrat);
    if (ct.id!=idContrat) {
        printf("Le contrat avec l'ID %d n'a pas été trouvé.\n", idContrat);
        return;
    }

    // Rechercher le client dans le fichier binaire des clients
    CLIENT client,cl;
    cl=chercherClient(ct.clientId);
    if (cl.id!=ct.clientId) {
        printf("Le client avec l ID %d n a pas ete trouve.\n", ct.clientId);
        return;
    }


    // Convertir la date du paiement en une chaîne de caractères formatée
    char datePaiementStr[100];
    snprintf(datePaiementStr, sizeof(DATE), "%04d-%02d-%02d", datePaiement.annee, datePaiement.mois, datePaiement.jour);

    // Créer le nom du fichier texte avec les informations du paiement
    char nomFichier[100];
    snprintf(nomFichier, sizeof(nomFichier), "%s_CT%d_CL%d.txt", datePaiementStr, idContrat, contrat.clientId);

    // Ouvrir le fichier texte en mode écriture
    FILE* fichierPaiement = fopen(nomFichier, "w");
    if (fichierPaiement == NULL) {
        printf("Erreur lors de l'ouverture du fichier de paiement.\n");
        return;
    }

    // Écrire les informations dans le fichier texte
    fprintf(fichierPaiement, "Date du paiement : ");
    printDate(datePaiement,date);
    fprintf(fichierPaiement, "ID du contrat : %d\n", idContrat);
    fprintf(fichierPaiement, "ID du client : %d\n", ct.clientId);
    fprintf(fichierPaiement, "Nom du client : %s\n", cl.nom);
    fprintf(fichierPaiement, "Login du Gestionnaire : %s\n", paiement.loginGest);
    // ... Écrire les autres informations selon vos besoins

    // Fermer le fichier texte
    fclose(fichierPaiement);


    printf("Le paiement a ete enregistre avec succes.\n");
}

/********************************************************************/

// Fonctions pour les utilisateurs

int typeUser()
{
	 USER utilisateur;
//Enumeration des Types
	printf("1-Administrateur\n");
	printf("2-Gestionnaire\n");
	do{
		scanf("%d",&utilisateur.typeUser);
		if(utilisateur.typeUser<=0 && utilisateur.typeUser>3){
            printf("Ce type de location n'existe\n");
		}
	}while(utilisateur.typeUser<=0 || utilisateur.typeUser>2);
//Retoure du choix
	return utilisateur.typeUser;
}

void ajouterUtilisateur(USER utilisateur) {
    int cpt,verif1,verif;
    FILE* fichier = fopen(FICHIER_UTILISATEURS, "ab");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    printf("****************************** Saisir des informations du user ******************************\n");
    do{
    	 printf("Saisir le Nom du USER\n");
    	 fflush(stdin);
    	 gets(utilisateur.nom);
    }while(utilisateur.nom[0]==32 || utilisateur.nom[strlen(utilisateur.nom)-1]==32);
	do{
		printf("Saisir le Prenom du USER\n");
    	gets(utilisateur.prenom);
	}while(utilisateur.prenom[0]==32 || utilisateur.prenom[strlen(utilisateur.prenom)-1]==32);
	do{
		printf("Saisir l'Email du USER sans(@gmail.com)\n");
   		gets(utilisateur.email);
        verif1=verifemailunique(utilisateur.email);
   		if (strchr(utilisateur.email,'@')!=NULL || strcasecmp(utilisateur.email,"gmail")==0 || strchr(utilisateur.email,'.')!=NULL || verif1==0)
   		{
   			cpt=1;
   		}else{cpt=0;}
	}while(utilisateur.email[0]==32 || utilisateur.email[strlen(utilisateur.email)-1]==32 || cpt==1);
	do{
		printf("Saisir le login du USER\n");
    	gets(utilisateur.login);
        verif=verifloginunique(utilisateur.login);
	}while(utilisateur.login[0]==32 || utilisateur.login[strlen(utilisateur.login)-1]==32 || verif==0);
    do{
		printf("Saisir le Pasword du USER\n");
    	gets(utilisateur.password);
    	chiffrementMotDePasse(utilisateur.password);
    }while(strlen(utilisateur.password)<8);
    	printf("Vous voulez etre quel type de USER\n");
    	utilisateur.typeUser=typeUser();

    fwrite(&utilisateur, sizeof(USER), 1, fichier);

    fclose(fichier);
    printf("Utilisateur a ete inscrit avec succes et a comme login %s",utilisateur.login);
}

void modifierUtilisateur(char login[], USER utilisateur) {

    int confirm3,confirm1;

    FILE* fichier = fopen(FICHIER_UTILISATEURS, "rb+");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

   USER tmp;
    while (fread(&tmp, sizeof(USER), 1, fichier)) {
        int cpt,verif,verif1;
        if (strcmp(tmp.login, login) == 0) {

                 printf("****************************** Saisir des informations du user ******************************\n");
                do{
                     printf("Saisir le Nom du USER\n");
                     fflush(stdin);
                     gets(utilisateur.nom);
                }while(utilisateur.nom[0]==32 || utilisateur.nom[strlen(utilisateur.nom)-1]==32);
                do{
                    printf("Saisir le Prenom du USER\n");
                    gets(utilisateur.prenom);
                }while(utilisateur.prenom[0]==32 || utilisateur.prenom[strlen(utilisateur.prenom)-1]==32);
                     printf("voulez-vous Modifier l Email\n");
                     printf("1-OUI\n");
                     printf("2-NON\n");
                     printf("Votre choix : ");
                do{
                    confirm3=saisirVariable();
                    if (confirm3 !=1 && confirm3 !=2)
                {
                   printf("invalide ressaisir a nouveau\n");
                }
                }while(confirm3!=1 && confirm3!=2);
                if (confirm3==1)
                {
                    do{
                        printf("Saisir l'Email du USER sans(@gmail.com)\n");
                        gets(utilisateur.email);
                        verif=verifemailunique(utilisateur.email);
                        if (strchr(utilisateur.email,'@')!=NULL || strcasecmp(utilisateur.email,"gmail")==0 || strchr(utilisateur.email,'.')!=NULL || verif==0)
                        {
                            cpt=1;
                        }else{cpt=0;}
                   }while(utilisateur.email[0]==32 || utilisateur.email[strlen(utilisateur.email)-1]==32 || cpt==1);
                }else{strcpy(utilisateur.email,tmp.email);}
                    printf("voulez-vous Modifier le login\n");
                     printf("1-OUI\n");
                     printf("2-NON\n");
                     printf("Votre choix : ");
                    do{
                        confirm1=saisirVariable();
                         if (confirm1 !=1 && confirm1 !=2)
                        {
                           printf("invalide ressaisir a nouveau\n");
                        }

                    }while(confirm1!=1 && confirm1!=2);
                    if (confirm1==1)
                {
                    do{
                        printf("Saisir le login du USER\n");
                        gets(utilisateur.login);
                         verif=verifloginunique(utilisateur.login);
                    }while(utilisateur.login[0]==32 || utilisateur.login[strlen(utilisateur.login)-1]==32 || verif==0);
                    login=utilisateur.login;
                }else{strcpy(utilisateur.login,tmp.login);}
                do{
                    printf("Saisir le Pasword du USER\n");
                    gets(utilisateur.password);
                    chiffrementMotDePasse(utilisateur.password);
                }while(strlen(utilisateur.password)<8);
                    printf("Vous voulez etre quel type de USER\n");
                    utilisateur.typeUser=typeUser();

            fseek(fichier, -sizeof(USER), SEEK_CUR);
            fwrite(&utilisateur, sizeof(USER), 1, fichier);
            break;
        }
    }

    fclose(fichier);
     printf("Utilisateur a ete modifier avec succes et a comme login %s",login);
}

void supprimerUtilisateur(char login []) {
    FILE* fichier = fopen(FICHIER_UTILISATEURS, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    FILE* fichierTemp = fopen("temp.bin", "wb");
    if (fichierTemp == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    USER utilisateur;
    while (fread(&utilisateur, sizeof(USER), 1, fichier)) {
        if (strcmp(utilisateur.login, login) != 0) {
            fwrite(&utilisateur, sizeof(USER), 1, fichierTemp);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    remove(FICHIER_UTILISATEURS);
    rename("temp.bin",FICHIER_UTILISATEURS);
     printf("Utilisateur avec login %s a ete supprime avec succes. \n",login);
}

USER chercherUtilisateur(char login []) {
    USER utilisateur;
    FILE* fichier = fopen(FICHIER_UTILISATEURS, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return ;
    }

    while (fread(&utilisateur, sizeof(USER), 1, fichier)) {
        if (strcmp(utilisateur.login, login) == 0) {

                 printf("Nom : %s\n", utilisateur.nom);
                printf("Prénom : %s\n", utilisateur.prenom);
                printf("Login : %s\n", utilisateur.login);
                printf("Email : %s@gmail.com\n", utilisateur.email);
                printf("Type utilisateur : %s\n", utilisateur.typeUser == 1 ? "Administrateur" : "Gestionnaire");

            fclose(fichier);
            return utilisateur;
        }
    }

    fclose(fichier);
    return ;
}

void afficherUtilisateurs() {
    FILE* fichier = fopen(FICHIER_UTILISATEURS, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    USER utilisateur;
    while (fread(&utilisateur, sizeof(USER), 1, fichier)) {
        printf("Nom : %s\n", utilisateur.nom);
        printf("Prénom : %s\n", utilisateur.prenom);
        printf("Login : %s\n", utilisateur.login);
        //printf("Mots de Passe : %s\n",utilisateur.password);
        printf("Email : %s@gmail.com\n", utilisateur.email);
        printf("Type utilisateur : %s\n", utilisateur.typeUser == 1 ? "Administrateur" : "Gestionnaire");
        printf("------------------------\n");
    }

    fclose(fichier);
}
/*********************************************************************/

void rechercherContratsClient(int clientId) {
    char saisirdateFin[20],saisirdateDeb[20];
    FILE *fileContrats = fopen(FICHIER_CONTRAT, "rb");

    if (fileContrats == NULL) {
        printf("Erreur lors de l'ouverture du fichier contrats.bin\n");
        return; // Vous pouvez adapter le code pour renvoyer une valeur spécifique indiquant une erreur
    }

    CONTRAT contrat;
    int contratTrouve = 0;

    while (fread(&contrat, sizeof(CONTRAT), 1, fileContrats)) {
        if (contrat.clientId == clientId && contratExiste(contrat.date_FIN)==0) {
            contratTrouve ++;
            printf("ID : %d\n", contrat.id);
	        printf("ID Client : %d\n", contrat.clientId);
	        printf("ID Location : %d\n", contrat.locationId);
	        printf("Date début : ");
            printDate(contrat.date_DEB,saisirdateFin);
	        if(contrat.date_FIN.jour!=-1)
            {
                printf("Date fin : ");
                printDate(contrat.date_FIN,saisirdateFin);
	        }else{printf("Date fin : \n");}
        	printf("------------------------\n");
        }
    }

    fclose(fileContrats);

    if (contratTrouve!=0) {
    	 printf("le client avec id %d a %d  contrat en cours\n",clientId,contratTrouve);
        return ; // Le client a un contrat en cours, on le retourne
    } else {
        printf("le client avec id %d n'a pas de contrat en cours\n",clientId);
        return;
    }
}

void rechercherLocationsDisponibles(TypeLocation type) {
    FILE *fileContrats = fopen(FICHIER_CONTRAT, "rb");
    FILE *fileLocations = fopen(FICHIER_LOCATION, "rb");

    if (fileContrats == NULL || fileLocations == NULL) {
        printf("Erreur lors de l'ouverture des fichiers contrats.bin ou locations.bin\n");
        return; // Vous pouvez adapter le code pour renvoyer une valeur spécifique indiquant une erreur
    }

    LOCATION location;
    int contratTrouve = 0;

    while (fread(&location, sizeof(LOCATION), 1, fileLocations)) {
        if (location.type == type) {
            rewind(fileContrats); // Revenir au début du fichier des contrats pour chaque location

            // Parcourir les contrats pour vérifier si l'id de la location existe ou si la date_FIN n'est pas vide
            CONTRAT contrat;
            while (fread(&contrat, sizeof(CONTRAT), 1, fileContrats)) {
                if (contrat.locationId == location.id || contratExiste(contrat.date_FIN)==0) {
                    contratTrouve ++;
          			 printf("ID : %d\n", location.id);
				     printf("ID Bailleur : %d\n", location.bailleurId);
				     printf("Libellé : %s\n", location.libelle);
				     printf("Adresse : %s\n", location.adresse);
           switch(location.type)
            {
                case 1 :
                    printf("Type : Maison\n");
                    break;
                case 2 :
                    printf("Type : Appartement\n");
                    break;
                default :
                    printf("Type : Studio\n");
                    break;
            }
        printf("Prix : %.2f\n", location.prix);
        printf("------------------------\n");
                }
            }

            if (contratTrouve!=0) {
                fclose(fileContrats);
                fclose(fileLocations);
                return; // La location est disponible, on la retourne
            }
        }
    }

    fclose(fileContrats);
    fclose(fileLocations);
    return;
}

void rechercherUtilisateurParLoginEmail(char login)
{
	int choix;
	    printf("Veuillez choisir une option de recherche :\n");
	    printf("1. Rechercher par login\n");
	    printf("2. Rechercher par email\n");
	    printf("Votre choix : ");
	    choix=saisirVariable();

	    switch (choix) {
	        case 1:
	            rechercherUtilisateurParLogin();
	            break;
	        case 2:
	            rechercherUtilisateurParEmail();
	            break;
	        default:
	            printf("Option de recherche invalide.\n");
	            break;
	    }
}
/***************************************************************************/
void rechercherUtilisateurParLogin() {
    char login[100];
    printf("Veuillez saisir le login de l'utilisateur : ");
    scanf("%s", login);

    // Rechercher l'utilisateur par login
    FILE* fichierUtilisateurs = fopen(FICHIER_UTILISATEURS, "rb");
    if (fichierUtilisateurs == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        return;
    }

    USER utilisateur;
    int utilisateurTrouve = 0;

    while (fread(&utilisateur, sizeof(USER), 1, fichierUtilisateurs) == 1) {
        if (strcmp(utilisateur.login, login) == 0) {
            // Afficher les informations de l'utilisateur
             printf("Nom : %s\n", utilisateur.nom);
            printf("Prénom : %s\n", utilisateur.prenom);
            printf("Login : %s\n", utilisateur.login);
            printf("Email : %s@gmail.com\n", utilisateur.email);
            printf("Type utilisateur : %s\n", utilisateur.typeUser == 1 ? "Administrateur" : "Gestionnaire");
            printf("------------------------\n");
            utilisateurTrouve = 1;
            break;  // Sortir de la boucle si l'utilisateur est trouvé
        }
    }

    fclose(fichierUtilisateurs);

    if (!utilisateurTrouve) {
        printf("Aucun utilisateur avec le login '%s' n'a été trouvé.\n", login);
    }
}


void rechercherUtilisateurParEmail() {
    char email[100];
    printf("Veuillez saisir l'email de l'utilisateur : ");
    scanf("%s", email);

    // Rechercher l'utilisateur par email
    FILE* fichierUtilisateurs = fopen(FICHIER_UTILISATEURS, "rb");
    if (fichierUtilisateurs == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        return;
    }

    USER utilisateur;
    int utilisateurTrouve = 0;

    while (fread(&utilisateur, sizeof(USER), 1, fichierUtilisateurs) == 1) {
        if (strcmp(utilisateur.email, email) == 0) {
             // Afficher les informations de l'utilisateur
            printf("Nom : %s\n", utilisateur.nom);
            printf("Prénom : %s\n", utilisateur.prenom);
            printf("Login : %s\n", utilisateur.login);
            printf("Email : %s@gmail.com\n", utilisateur.email);
            printf("Type utilisateur : %s\n", utilisateur.typeUser == 1 ? "Administrateur" : "Gestionnaire");
            printf("------------------------\n");
            utilisateurTrouve = 1;
            break;  // Sortir de la boucle si l'utilisateur est trouvé
        }
    }

    fclose(fichierUtilisateurs);

    if (!utilisateurTrouve) {
        printf("Aucun utilisateur avec l'email '%s' n'a été trouvé.\n", email);
    }
}

int verifemailunique(char email [])
{
     // Rechercher l'existence du email saisir dans le fichier utilisateur
    FILE* fichierUtilisateurs = fopen(FICHIER_UTILISATEURS, "rb");
    if (fichierUtilisateurs == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        return;
    }
    USER utilisateur;

    while (fread(&utilisateur, sizeof(USER), 1, fichierUtilisateurs)) {
        if (strcmp(utilisateur.email, email) == 0) {
            printf("ce email existe deja\n");
                return 0;
              // Sortir de la boucle si un utilisateur a le meme email
        }
    }
    fclose(fichierUtilisateurs);
    // Rechercher l'existence d' email dans le fichier client
    FILE* fichie = fopen(FICHIER_CLIENT, "rb");
    if (fichie == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        return;
    }

   CLIENT client;

    while (fread(&client, sizeof(CLIENT), 1, fichie)) {
        if (strcmp(client.email, email) == 0) {
            printf("ce email existe deja\n");
                return 0;
            break;  // Sortir de la boucle si un utilisateur a le meme email
        }
    }

    fclose(fichie);
    return 1;
}

int verifloginunique(char login [])
{
      FILE* fichierUtilisateurs = fopen(FICHIER_UTILISATEURS, "rb");

    if (fichierUtilisateurs == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        return;
    }

   USER utilisateur;

    while (fread(&utilisateur, sizeof(USER), 1, fichierUtilisateurs)) {
        if (strcmp(utilisateur.login, login) == 0) {
            printf("login deja existe\n");
            return 0;
        }
    }

    fclose(fichierUtilisateurs);
    return 1;
}

int verifCINunique(int CIN)
{
      FILE* fichie = fopen(FICHIER_BAILLEUR, "rb");

    if (fichie == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        return;
    }
   BAILLEUR bailleur;

    while (fread(&bailleur, sizeof(BAILLEUR), 1, fichie)) {
        if (bailleur.CIN== CIN) {
            printf("CIN deja existe\n");
            return 0;
        }
    }
    fclose(fichie);

     FILE* fichier = fopen(FICHIER_CLIENT, "rb");

    if (fichie == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        return;
    }

   CLIENT client;

    while (fread(&client, sizeof(CLIENT), 1, fichie)) {
        if (client.CIN==CIN) {
            printf("CIN deja existe ressaisir a nouveau\n");
            return 0;
        }
    }

    fclose(fichie);

    return 1;
}

int veriftelunique(int tel)
{
      FILE* fichie = fopen(FICHIER_BAILLEUR, "rb");

    if (fichie == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        return;
    }

   BAILLEUR bailleur;

    while (fread(&bailleur, sizeof(BAILLEUR), 1, fichie)) {
        if (bailleur.tel==tel) {
            printf("Ce numero existe deja existe\n");
            return 0;
        }
    }

    fclose(fichie);

     FILE* fichier = fopen(FICHIER_CLIENT, "rb");

    if (fichie == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        return;
    }

   CLIENT client;

    while (fread(&client, sizeof(CLIENT), 1, fichie)) {
        if (client.tel==tel) {
            printf("Ce numero existe deja existe\n");
            return 0;
        }
    }

    fclose(fichie);

    return 1;
}

void chiffrementMotDePasse(char motDePasse[]) {
    //  un chiffrement par décalage

    int i = 0;
    char caractere;

    while (motDePasse[i] != '\0') {
        caractere = motDePasse[i];

        // Appliquer le chiffrement (par décalage dans cet exemple)
        if (caractere >= 'a' && caractere <= 'z') {
            caractere = 'a' + (caractere - 'a' + 1) % 26;
        } else if (caractere >= 'A' && caractere <= 'Z') {
            caractere = 'A' + (caractere - 'A' + 1) % 26;
        }

        motDePasse[i] = caractere;
        i++;
    }
}

void dechiffrementMotDePasse(char motDePasse[]) {
    // Implémentation du déchiffrement du mot de passe (correspondant à l'algorithme de chiffrement utilisé)

    int i = 0;
    char caractere;

    while (motDePasse[i] != '\0') {
        caractere = motDePasse[i];

        // Appliquer le déchiffrement (par décalage inverse dans cet exemple)
        if (caractere >= 'a' && caractere <= 'z') {
            caractere = 'a' + (caractere - 'a' - 1 + 26) % 26;
        } else if (caractere >= 'A' && caractere <= 'Z') {
            caractere = 'A' + (caractere - 'A' - 1 + 26) % 26;
        }

        motDePasse[i] = caractere;
        i++;
    }
}

int saisirVariableCIN()
{
      char N[10];
    int verif,i,val;
     do{
         verif=0;
       		do{
            gets(N);
        if(strlen(N)!=7 || N[0]==32 || N[strlen(N)-1]==32)
        {
            printf("CNI invalide ressayer\n");
        }
    }while(strlen(N)!=7 || N[0]==32 || N[strlen(N)-1]==32);

        for(i=0;i<7;i++){
        if(N[i]>='0' && N[i]<='9'){
            verif++;
        }else{verif=0;}
        }
        }while(verif!=7);
        val=atoi(N);
	return val;
}
										/*
											Saisir une variable
										*/
int saisirVariableTEL()
{
	    char N[9];
	int verif,i,val;
	do{
	    verif=0;
	    do{
	    	gets(N);
	    	if(strlen(N)!=9 || N[0]!=55)
	    	{
	    		printf("Numero incorrecte Ressayer\n");
	    	}
	    }while(strlen(N)!=9 || N[0]!=55 || (N[1]!=55 && N[1]!=56 && N[1]!=53 && N[1]!=54 && N[0]!=48));

	for(i=0;i<9;i++){
	if(N[i]>='0' && N[i]<='9'){
	    verif++;
	}else{verif=0;}
	}
	}while(verif!=9);
	val=atoi(N);
	return val;
}

int saisirVariable()
{
    char N[4];
	int verif,i,val;
	do{
	    verif=0;
	    fflush(stdin);
	    	gets(N);

	for(i=0;i<strlen(N);i++){
	if(N[i]>'0' && N[i]<='9'){
	    verif++;
	}else{verif=0;}
	}
	}while(verif!=strlen(N));
	val=atoi(N);
	return val;
}

int contratExiste(DATE date_FIN) {
    FILE *file = fopen(FICHIER_CONTRAT, "rb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier contrats.bin\n");
        return 0;
    }

    CONTRAT contrat;

    while (fread(&contrat, sizeof(CONTRAT), 1, file) == 1) {
        if (contrat.date_FIN.jour != -1 &&
            contrat.date_FIN.mois != -1 &&
            contrat.date_FIN.annee != -1) {
            fclose(file);
            return 1;  // La date de fin existe, contrat trouvé
        }
    }

    fclose(file);
    return 0;  // La date de fin n'existe pas, contrat non trouvé
}

USER authentifierUtilisateur(char login[100], char password[100]) {
    FILE *fileUsers = fopen(FICHIER_UTILISATEURS, "rb");
    if (fileUsers == NULL) {
        printf("Erreur lors de l'ouverture du fichier users.bin\n");
        return;
    }

    USER utilisateur;

    while (fread(&utilisateur, sizeof(USER), 1, fileUsers) == 1) {
        if (strcmp(utilisateur.login, login) == 0) {
            dechiffrementMotDePasse(utilisateur.password); // Déchiffrement du mot de passe

            if (strcmp(utilisateur.password, password) == 0) {
                fclose(fileUsers);
                return utilisateur; // L'utilisateur est authentifié
            } else {
                fclose(fileUsers);
               return;
            }
        }
    }

    fclose(fileUsers);
     return;
}

DATE scanDate(char N[])
{
	DATE date;
	int verif,jour,mois,annee;
	//Verification du format
	verif=sscanf(N,"%d/%d/%d",&jour,&mois,&annee);
	if(verif==3)
	{
		//Verification de la validation du jour, mois et annnee
		if((jour>0 && jour<=31) && (mois>0 && mois<=12) && annee>=1000)
		{
			date.jour=jour;
			date.mois=mois;
			date.annee=annee;
			return date;
		}
		else
		{
			printf("Date invalid\n");
			return date;
		}
	}
	else
	{
		printf("Date invalid\n");
		return date;
	}

}

int verifDate(char N[])
{
	int verif,jour,mois,annee;
    verif=sscanf(N,"%d/%d/%d",&jour,&mois,&annee);
	if(verif==3)
	{
		//Verification de la validation du jour, mois et annnee
		if((jour>0 && jour<=31) && (mois>0 && mois<=12) && annee>=1000)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else
	{

		return -1;
	}

}

void printDate(DATE date, char N[])
{
	printf("%d/%d/%d\n",date.jour,date.mois,date.annee);
}

void menu()
{
     int choix;
    char login[100],saisirDate[20],buffer[100];;
    char motDePasse[100];
    BAILLEUR bailleur;
    USER user,utilisateur;
    CLIENT client;
    CONTRAT contrat;
    LOCATION location;
    PAIEMENT paiement;
    DATE datePaiement;
    int bailleurId,locationId,contratId,clientId;

		    printf("\t\t\t--------------------- Application de Gestion Immobiliere --------------------\n");
    //ajouterUtilisateur(user);
    printf("\t\t\t\tVeuillez vous connecter :\n");
    printf("\t\t\t\t\tLogin : ");
    scanf("%s", &login);
    printf("\t\t\t\t\tMot de passe : ");
    scanf("%s", &motDePasse);

     utilisateur = authentifierUtilisateur(login, motDePasse);
    if (strcmp(utilisateur.login,login)!=0 || strcmp(utilisateur.password,motDePasse)!=0) {
        printf("Identifiant ou mot de passe incorrect.\n");
        return 0;
    }
    system("cls");
     printf("\t\t\t--------------------- Application de Gestion Immobiliere --------------------\n");
     printf("\n\t\t\t\t\tBienvenue, %s %s !\n", utilisateur.prenom, utilisateur.nom);

     if (utilisateur.typeUser == 1)
    {
        do
        {
            printf("\n\t\t\t\t\t----- Menu Administrateur -----\n");
            printf("\t\t\t\t\t1. Gestion des Utilisateurs\n");
            printf("\t\t\t\t\t2. Gestion des Bailleurs\n");
            printf("\t\t\t\t\t3. Gestion des Locations\n");
            printf("\t\t\t\t\t4. Quitter\n");

            printf("\t\t\t\t\tChoix : ");
            choix=saisirVariable();

            switch (choix)
            {
                case 1:
                    system("cls");
                    // Gestion des Utilisateurs
                    printf("\t\t\t--------------------- Application de Gestion Immobiliere --------------------\n");
                    printf("\n\t\t\t\t\tGestion des Utilisateurs :\n");
                    printf("\t\t\t\t\ta. Ajouter un Nouveau Utilisateur\n");
                    printf("\t\t\t\t\tb. Modifier les informations d'un Utilisateur\n");
                    printf("\t\t\t\t\tc. Supprimer un Utilisateur\n");
                    printf("\t\t\t\t\td. Rechercher un Utilisateur\n");
                    printf("\t\t\t\t\te. Afficher les utilisateurs Utilisateur\n");

                    printf("\n\t\t\t\t\tVeuillez s?ectionner une option : ");
                    fgets(buffer, sizeof(buffer), stdin);

                    switch (buffer[0])
                    {
                        case 'a':
                            ajouterUtilisateur(utilisateur);
                            break;
                        case 'b':
                             printf("\t\t\t\t\t Saisir le Login de l'utilisateur a modifier : ");
                             scanf("%s", &login);
                            modifierUtilisateur(login,utilisateur);
                            break;
                        case 'c':
                             printf("\t\t\t\t\t Saisir le Login de l'utilisateur a Supprimer : ");
                             scanf("%s", &login);
                            supprimerUtilisateur(login);
                            break;
                        case 'd':
                            rechercherUtilisateurParLogin();
                            break;
                        case 'e':
                            afficherUtilisateurs();
                            break;
                        default:
                             printf("\t\t\t\t\tOption invalide ! Veuillez r?ssayer.\n");
                    }

                    break;
                case 2:

                    // Gestion des Bailleurs
                    printf("\n\t\t\t\t\tGestion des Bailleurs :\n");
                    printf("\t\t\t\t\ta. Ajouter un Bailleur\n");
                    printf("\t\t\t\t\tb. Modifier les informations d'un Bailleur\n");
                    printf("\t\t\t\t\tc. Supprimer un Bailleur\n");
                    printf("\t\t\t\t\td. Afficher un Bailleur\n");

                    printf("\n\t\t\t\t\tVeuillez s?ectionner une option : ");
                    fgets(buffer, sizeof(buffer), stdin);

                    switch (buffer[0])
                    {
                        case 'a':
                            ajouterBailleur(bailleur);
                            break;
                        case 'b':
                            printf("\t\t\t\t\tsaisir l'id du bailleur a modifier\n");
                            bailleurId=saisirVariable();
                            modifierBailleur(bailleurId,bailleur);
                            break;
                        case 'c':
                            printf("\t\t\t\t\tsaisir l'id du bailleur a supprime\n");
                            bailleurId=saisirVariable();
                            supprimerBailleur(bailleurId);
                            break;
                        case 'd':
                            afficherBailleurs();
                            break;
                        default:
                            printf("\t\t\t\t\tOption invalide ! Veuillez ressayer.\n");
                    }

                    break;
                case 3:

                        // Gestion des Locations
                    printf("\n\t\t\t\t\tGestion des Locations :\n");
                    printf("\t\t\t\t\ta. Ajouter une Nouvelle Location\n");
                    printf("\t\t\t\t\tb. Modifier les informations d'une Location\n");
                    printf("\t\t\t\t\tc. Supprimer une Location\n");
                    printf("\t\t\t\t\td. Afficher les informations d'une Location\n");

                    printf("\n\t\t\t\t\tVeuillez s?ectionner une option : ");
                    fgets(buffer, sizeof(buffer), stdin);

                    switch (buffer[0])
                    {
                        case 'a':
                            ajouterLocation(location);
                            break;
                        case 'b':
                            printf("\t\t\t\t\tsaisir l'id de la location a modifier\n");
                            locationId=saisirVariable();
                            modifierLocation(locationId,location);
                            break;
                        case 'c':
                            printf("\t\t\t\t\tsaisir l'id de la location a supprime\n");
                            locationId=saisirVariable();
                            supprimerLocation(locationId);
                            break;
                        case 'd':
                            afficherLocations();
                            break;
                        default:
                            printf("\t\t\t\t\tOption invalide ! Veuillez r?ssayer.\n");
                        }

                        break;
                case 4:
                    printf("\t\t\t\t\tAu revoir !!!\n");
                    break;
                default:
                     printf("\t\t\t\t\tChoix invalide.\n");
                    break;
            }
        }while(choix<4);

    } else if (utilisateur.typeUser == 2)
    {
        do
        {
            printf("\n\t\t\t----- Menu Gestionnaire -----\n");
            printf("\t\t\t\t\t1. Gestion des Clients\n");
            printf("\t\t\t\t\t2. Gestion des Contrats\n");
            printf("\t\t\t\t\t3. Gestion des Paiements\n");
            printf("\t\t\t\t\t4. Quitter\n");

            printf("\t\t\t\t\tChoix : ");
            choix=saisirVariable();

            switch (choix)
            {
                case 1:

                        // Gestion des Clients
                    printf("\n\t\t\t\t\tGestion des Clients :\n");
                    printf("\t\t\t\t\ta. Ajouter un Nouveau Client\n");
                    printf("\t\t\t\t\tb. Modifier les information d un Client\n");
                    printf("\t\t\t\t\tc. Rechercher les Contrats d'un Client\n");
                    printf("\t\t\t\t\td. Supprimer un Client\n");
                    printf("\t\t\t\t\te. Afficher les information d un Client\n");

                    printf("\n\t\t\t\t\tVeuillez s?ectionner une option : ");
                    fgets(buffer, sizeof(buffer), stdin);

                    switch (buffer[0])
                    {
                        case 'a':
                            ajouterClient(client);
                            break;
                        case 'b':
                            printf("\t\t\t\t\tsaisir l'id du Client a modifier\n");
                            clientId=saisirVariable();
                            modifierClient(clientId,client);
                            break;
                        case 'c':
                            printf("\t\t\t\t\tsaisir l'id du Client a chercher\n");
                            clientId=saisirVariable();
                            rechercherContratsClient(clientId);
                            break;
                        case 'd':
                            printf("\t\t\t\t\tsaisir l'id du Client a supprime\n");
                            clientId=saisirVariable();
                            supprimerClient(clientId);
                            break;
                        case 'e':
                            afficherClients();
                            break;
                        default:
                            printf("\t\t\t\t\tOption invalide ! Veuillez r?ssayer.\n");
                    }

                    break;
                case 2:

                            // Gestion des Contrats
                    printf("\n\t\t\t\t\tGestion des Contrats :\n");
                    printf("\t\t\t\t\ta. Ajouter un Contrat pour un Client Existant\n");
                    printf("\t\t\t\t\tb. Modifier un Contrat\n");
                    printf("\t\t\t\t\tc. Supprimer un contrat\n");
                    printf("\t\t\t\t\te. Afficher un Contrat\n");

                    printf("\n\t\t\t\t\tVeuillez s?ectionner une option : ");
                    fgets(buffer, sizeof(buffer), stdin);

                    switch (buffer[0])
                    {
                        case 'a':
                            ajouterContrat(contrat);
                            break;
                        case 'b':
                            printf("\t\t\t\t\tsaisir l'id du Contrat a modifier\n");
                            contratId=saisirVariable();
                            modifierContrat(contratId,contrat);
                            break;
                        case 'c':
                            printf("\t\t\t\t\tsaisir l'id du Contrat a supprime\n");
                            contratId=saisirVariable();
                            supprimerContrat(contratId);
                            break;
                        case 'e':
                            afficherContrats();
                            break;
                        default:
                            printf("\t\t\t\t\tOption invalide ! Veuillez r?ssayer.\n");
                    }


                    break;
                case 3:

                        // Gestion des Paiements
                    printf("\n\t\t\t\t\tGestion des Paiements :\n");
                    printf("\t\t\t\t\ta. Ajouter un Paiement\n");
                    printf("\t\t\t\t\tb. Enregistrer un Paiement\n");
                    printf("\t\t\t\t\tc. Afficher un Paiement\n");

                    printf("\n\t\t\t\t\tVeuillez s?ectionner une option : ");
                    fgets(buffer, sizeof(buffer), stdin);

                    switch (buffer[0])
                    {
                        case 'a':
                            ajouterPaiement(paiement);
                            break;
                        case 'b':
                            printf("\t\t\t\t\tsaisir l'id du Contrat a enregistre\n");
                            contratId=saisirVariable();
                            do{
                                printf("\t\t\t\t\tEntre la date de paiement avec le Format jj/mm/aaaa\n");
                                gets(saisirDate);
                                datePaiement=scanDate(saisirDate);
                                verifDate(saisirDate);
                            }while(verifDate(saisirDate)==-1);
                            enregistrerPaiement(contratId,datePaiement);
                            break;
                        case 'c':
                            afficherPaiements();
                            break;
                        default:
                            printf("\t\t\t\t\tOption invalide ! Veuillez ressayer.\n");
                    }

                    break;
                case 4:
                    printf("\t\t\t\t\tAu revoir !!!\n");
                    break;
                default:
                     printf("\t\t\t\t\tChoix invalide.\n");
                    break;
            }

        }while(choix<4);
    }
}

