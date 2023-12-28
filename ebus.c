//sous programme pour afficher les details des bus :
#include <stdio.h>

void afficher_les_details_des_bus() {
    FILE *fichier;
    char caractere;


    fichier = fopen("C:\\Users\\mayssen\\Desktop\\E-BUS\\ebus.txt", "r");


    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }



    while ((caractere = fgetc(fichier)) != EOF) {
        printf("%c", caractere);
    }


    fclose(fichier);

    return 0;
}




//fonction pour enregistrer les reservation dans une pile :
#include <stdio.h>
#include <stdlib.h>

// Définition de la structure d'un élément de la pile
struct Element {
    int donnee;
    struct Element* suivant;
};

// Définition du type Pile
typedef struct {
    struct Element* sommet;
} Pile;

// Fonction pour créer une pile vide
Pile* creerPile() {
    Pile* nouvellePile = (Pile*)malloc(sizeof(Pile));
    if (nouvellePile == NULL) {
        fprintf(stderr, "Impossible de créer la pile\n");
        exit(EXIT_FAILURE);
    }
    nouvellePile->sommet = NULL;
    return nouvellePile;
}

// Fonction enregistrer les reservations dans la pile
void empiler(Pile* pile, int valeur) {
    // Création d'un nouvel élément
    struct Element* nouvelElement = (struct Element*)malloc(sizeof(struct Element));
    if (nouvelElement == NULL) {
        fprintf(stderr, "Impossible d'allouer la mémoire pour l'élément\n");
        exit(EXIT_FAILURE);
    }
    // Affectation des données et mise à jour du pointeur suivant
    nouvelElement->donnee = valeur;
    nouvelElement->suivant = pile->sommet;
    // Mise à jour du sommet de la pile
    pile->sommet = nouvelElement;
}

// Fonction pour dépiler un élément de la pile
int depiler(Pile* pile) {
    if (pile->sommet == NULL) {
        fprintf(stderr, "Erreur : La pile est vide\n");
        exit(EXIT_FAILURE);
    }
    // Récupération de la valeur du sommet
    int valeurDepilee = pile->sommet->donnee;
    // Sauvegarde du pointeur vers l'élément à dépiler
    struct Element* elementADepiler = pile->sommet;
    // Mise à jour du sommet de la pile
    pile->sommet = pile->sommet->suivant;
    // Libération de la mémoire de l'élément dépilé
    free(elementADepiler);
    return valeurDepilee;
}

// Fonction pour afficher les reservations
void afficherPile(Pile* pile) {
    struct Element* actuel = pile->sommet;
    printf("votre reservations ");
    while (actuel != NULL) {
        printf("%d ", actuel->donnee);
        actuel = actuel->suivant;
    }
    printf("\n");
}

//sous programme pour annuler une reservation

void annuler_reservation(Pile* pile, int valeur) {
    if (pile->sommet == NULL) {
        fprintf(stderr, " Vous n'avez pas encore reserver\n");
        exit(EXIT_FAILURE);
    }

    // Si l'élément à supprimer est en haut de la pile
    if (pile->sommet->donnee == valeur) {
        struct Element* elementASupprimer = pile->sommet;
        pile->sommet = pile->sommet->suivant;
        free(elementASupprimer);
        return;
    }

    // Recherche de l'élément à supprimer dans le reste de la pile
    struct Element* precedent = pile->sommet;
    struct Element* actuel = pile->sommet->suivant;

    while (actuel != NULL && actuel->donnee != valeur) {
        precedent = actuel;
        actuel = actuel->suivant;
    }

    // Si l'élément est trouvé, le supprimer
    if (actuel != NULL) {
        precedent->suivant = actuel->suivant;
        free(actuel);
    } else {
        fprintf(stderr, "La reservaton que vous voulez l'annulez n'existe pas \n", valeur);
        exit(EXIT_FAILURE);
    }
}


//fichier
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définir une structure pour stocker les détails d'une voyage
struct DetailsBus {
    int code;
    int num_bus;
    char depart[50];
    char arrivee[50];
    int places_disponibles;
    float prix;
    char type[20];
    char heure[6];
};

// Sous-programme pour remplir un tableau avec les lignes du fichier
void remplirTableau(const char *nomFichier, struct DetailsBus tableau[], int taille) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    char ligne[256];
    int index = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL && index < taille) {

        sscanf(ligne, "%d / %d / %s / %s / %d / %f / %s / %s",
               &tableau[index].code, &tableau[index].num_bus, tableau[index].depart,
               tableau[index].arrivee, &tableau[index].places_disponibles, &tableau[index].prix,
               tableau[index].type, tableau[index].heure);

        index++;
    }

    fclose(fichier);
}
//sous programme pour ecrire dans le fichier (changer la base de donnees apres la reservation)
void ecrireDansFichier(const char *nomFichier, struct DetailsBus tableau[], int tailleTableau) {
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }


    for (int i = 0; i < tailleTableau; i++) {
        fprintf(fichier,"%d / %d / %s / %s / %d / %.2f / %s / %s\n",
                tableau[i].code, tableau[i].num_bus, tableau[i].depart, tableau[i].arrivee,
                tableau[i].places_disponibles , tableau[i].prix, tableau[i].type, tableau[i].heure);
    }

    fclose(fichier);
}






//programme principale :

#include<stdio.h>
#include<conio.h>

int main (){
    char nom[50], prenom[50] , email[50] , mdp[50] , y[1000]  ;
    int num, code , codesup ,nombredeplace , x , totalpoint=0 ; //, j=0 ;
    float  prixapayer ;
    char clique ;
    Pile* reservation = creerPile();
    const char *nomFichier = "C:\\Users\\mayssen\\Desktop\\E-BUS\\ebus.txt" ;
    const int tailleTableau = 18;
    struct DetailsBus tableau[tailleTableau] ;
    //struct commentaire votre_avis[20] ;


    printf("**********Bienvenue a E-bus**********\n") ;
    printf("********************************\n") ;
    printf("creer un compte : \n") ;
    printf("                               \n") ;
    printf("donner votre nom : \n") ;
    scanf(" %[^\n]" , nom ) ;
    printf("donner votre prenom : \n") ;
    scanf(" %[^\n]" , prenom) ;
    printf("donner votre numero de telephone : \n") ;
    scanf("%d" , &num) ;
    printf("donner votre adresse email : \n") ;
    scanf("%s" , email) ;
    printf("donner votre mot de passe : \n") ;
    scanf(" %[^\n]" , mdp) ;
    printf("********************************\n") ;
    printf("BIENVENUE!! \n") ;
    while (clique != 'e'){

            printf("Si vous voulez reserver un bus cliquez sur a \n") ;
            printf("Si vous voulez voir l'historique de votres reservastions cliquez sur b \n") ;
            printf("Si vous voulez affichez vos points cliquez sur c \n") ;
            printf("Si vous voulez donner votre avis a un service cliquez sur d \n") ;
            printf("Si vous voulez quitter l'application cliquez sur e \n") ;
            scanf(" %c" , &clique) ;

    //si on veut reserver un bus :
            if (clique=='a'){
                  printf ("code / num_bus / depart / arrivee / nombre_de_places_disponibles / prix / type / heure de depart\n") ;
                  afficher_les_details_des_bus() ;
                  printf("ecrivez le code de votre reservation \n") ;
                  scanf("%d" , &code) ;
                  empiler(reservation, code) ;
                  remplirTableau(nomFichier, tableau, tailleTableau);
                  for (int i=0 ; i<tailleTableau ; i++){

                      if (tableau[i].code==code){

                          x=i ;
                          break ;
                      }
                  }
                  do{

                      printf("combien de places voulez vous reserver? \n") ;
                      scanf ("%d" , &nombredeplace) ;
                      if (tableau[x].places_disponibles < nombredeplace){

                          printf("nombre de places insuffisant \n") ;
                      }


                  }while (tableau[x].places_disponibles < nombredeplace) ;



    // afficher la reservation :



                for (int i = 0; i < tailleTableau; i++) {
                    if (tableau[i].code==code){
                        tableau[i].places_disponibles = tableau[i].places_disponibles - nombredeplace ;
                        printf("VOTRE RESERVATION est Code: %d, Numero de bus: %d, Depart: %s, Arrivee: %s , Nombre de places reservees: %d, Prix: %.2f, Type: %s, Heure de depart: %s\n",
                        tableau[i].code, tableau[i].num_bus, tableau[i].depart, tableau[i].arrivee ,
                        nombredeplace  , tableau[i].prix, tableau[i].type, tableau[i].heure);
                        break ;
                    }
                }
                if (10000 < totalpoint && totalpoint < 30000){

                    prixapayer=(tableau[x].prix)*nombredeplace * 0.8  ;
                }
                else if ( 30000 <totalpoint && totalpoint < 50000){
                    prixapayer=(tableau[x].prix)*nombredeplace * 0.7  ;
                }
                else if (totalpoint >50000){
                    prixapayer=(tableau[x].prix)*nombredeplace * 0.5  ;
                }
                else{

                    prixapayer=(tableau[x].prix)*nombredeplace ;
                }

                printf("le prix a payer est :%f \n" , prixapayer) ;
                totalpoint += prixapayer *100 ;


       //modifier les details dans le fichier du fichier apres reservation
                ecrireDansFichier(nomFichier, tableau, tailleTableau) ;


                }
                else if (clique =='b'){

                    afficherPile(reservation) ;
                }
                else if (clique=='c'){
                    printf("vous avez : %d", totalpoint) ;
                    printf("points \n") ;
                }
                else if (clique=='d'){

                    afficherPile(reservation) ;
                    printf("ecrivez le code de la reservation que vous voulez la donner votre avis \n") ;
                    scanf ("%d" , &code) ;
                    printf("*Ecrivez votre avis* \n") ;
                    scanf(" %[^\n]", y);


                }


       }



}

