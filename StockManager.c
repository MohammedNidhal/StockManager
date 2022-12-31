#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct produit {
  char nom[50];
  int ID,stock,prix;
} Produit;
Produit prod ;
int Rech(int IDrech)
{
   FILE*F ;
   F=fopen("Stock.txt","r");
   do
       {
       fscanf(F,"%d %s %d %d\n",&prod.ID,&prod.nom,&prod.prix,&prod.stock) ;
       fflush(stdin);
       if (prod.ID==IDrech)
       {
           fclose(F);
           return 1;
       }
       }
   while(!feof(F));
   fclose(F);
   return 0 ;
}
void Ajout()
{   int nb=1; int i;
    time_t currentTime;
    time (&currentTime);
    struct tm *myTime = localtime (&currentTime);
    do {
        FILE *F, *F2 ;
        F=fopen("Stock.txt","a");
        F2=fopen("Historique.txt","a");
        int IDajoute ;
        printf("Donner l'ID du produit : ");
        scanf("%d",&IDajoute);
        while (Rech(IDajoute)==1)
        {printf("Ce ID existe deja ");
        printf("Donner l'ID du produit : ");
        scanf("%d",&IDajoute);
        }
        prod.ID=IDajoute;
        printf("Donner le nom du produit : ");
        gets(&prod.nom);
        fflush(stdin);
        printf("Donner le stock du produit : ");
        scanf("%d",&prod.stock);
        fflush(stdin);
        printf("Donner le prix du produit : ");
        scanf("%d",&prod.prix);
        fflush(stdin);
        fprintf(F,"%d %s %d %d \n",prod.ID,prod.nom,prod.prix,prod.stock) ;
        fprintf(F2,"%i/%i/%i : Ajout de : %d %s %d %d\n",myTime->tm_mon + 1, myTime->tm_mday, myTime->tm_year + 1900,prod.ID,prod.nom,prod.prix,prod.stock);
        fclose(F);
        fclose(F2);
        printf("Pour ajouter un autre produit taper 1 sinon 0 : ");
        scanf("%d",&i);
        if (i==1){
            nb=1;
        }
        else{
            nb=0;
        }
    }while (nb==1);
    printf("\n");
    printf("Appuyez sur entrer pour revenir au menu ");
    getch();
    menu();
}
void Recherche()
{
    int IDrech ;
    printf("Donner l'ID du produit a recherche : ");
    scanf("%d",&IDrech);
    FILE *F ;
    F=fopen("Stock.txt","r");
    do
    {
        fscanf(F,"%d %s %d %d\n",&prod.ID,&prod.nom,&prod.prix,&prod.stock) ;
        if (IDrech==prod.ID)
        {
            printf("-----Information sur un produit\n");
            printf("\n");
            printf("l'ID du produit     \t:%d\n",prod.ID);
            printf("Le nom du produit\t:%s\n",prod.nom);
            printf("Le prix du produit \t:%d\n",prod.prix);
            printf("Le stock du produit\t:%d\n",prod.stock);
        }
    }
    while(!feof(F));
    fclose(F);
    printf("\n");
    printf("Appuyez sur entrer pour revenir au menu ");
    getch();
    menu();
}
void Supprimer()
{   int IDrech ;
    time_t currentTime;
    time (&currentTime);
    struct tm *myTime = localtime (&currentTime);
    printf("Donner l'ID du noveau produit : ");
    scanf("%d",&IDrech);
    fflush(stdin);
if (Rech(IDrech)==1)
{
    FILE *Fich ,*F, *F2 ;
    F=fopen("Stock.txt","r");
    Fich=fopen("Stock2.txt","w");
    F2=fopen("Historique.txt","a");
    do
       {
       fscanf(F,"%d %s %d %d\n",&prod.ID,&prod.nom,&prod.prix,&prod.stock) ;
       if (IDrech!=prod.ID)
       {
        fprintf(Fich,"%d %s %d %d\n",prod.ID,prod.nom,prod.prix,prod.stock) ;
       }
       else {
        fscanf(F2,"%i/%i/%i : Suppression de : %d %s %d %d\n",myTime->tm_mon + 1, myTime->tm_mday, myTime->tm_year + 1900,prod.ID,prod.nom,prod.prix,prod.stock);
       }
      }
    while(!feof(F));
    fclose(Fich);
    fclose(F);
    fclose(F2);
    remove("Stock.txt");
    rename("Stock2.txt","Stock.txt");
    printf("Suppression Effectuee avec success");
    }
else {
    printf("Suppression echouee \n");
}
    printf("\n");
    printf("Appuyez sur entrer pour revenir au menu ");
    getch();
    menu();
}
void Modifier(){
    FILE *F,*F2,*F3;
    int num,i;
    time_t currentTime;
    time (&currentTime);
    struct tm *myTime = localtime (&currentTime);
    printf("\n Entrez l'ID du produit a modifier : ");
    scanf("%d",&num);
    fflush(stdin);
    if (Rech(num)==1){
        fflush(stdin);
        F=fopen("Stock.txt","r");
        F2=fopen("Stock2.txt","a");
        F3=fopen("Historique.txt","a");
        while (1){
            fscanf(F,"%d %s %d %d",&prod.ID,&prod.nom,&prod.stock,&prod.prix);
            if (feof(F)){break;}
            if (num==prod.ID){
                fprintf(F3,"%i/%i/%i : Modification de : %d %s %d %d \n",myTime->tm_mon + 1, myTime->tm_mday, myTime->tm_year + 1900,prod.ID,prod.nom,prod.prix,prod.stock);
                prod.ID=num;
                printf("\n Entrez le nouveau nom : ");
                gets(prod.nom);
                printf("\n Entrez la quantité du stock : ");
                scanf("%d",&prod.stock);
                printf("\n Entrez le nouveau prix : ");
                scanf("%d",&prod.prix);
                }
            fprintf(F2,"%d %s %d %d \n",prod.ID,prod.nom,prod.stock,prod.prix);
            }
        fclose(F);
        fclose(F2);
        fclose(F3);
        remove("Stock.txt");
        rename("Stock2.txt","Stock.txt");
        printf("\n Modification reussite .");
        }
        else {
        printf("\n Modification echouée . \n");
        }
    printf("\n");
    printf("Appuyez sur entrer pour revenir au menu ");
    getch();
    menu();
}
void Historique(){
    FILE *F;
    char text[210];
    F=fopen("Historique.txt","r");
    if(feof(F)){
        printf("Aucune operation n'est faite .");
    }
    else {
        while (1){
            fgets(text,200,F);
            printf("%s \n",text);
            if (feof(F)){
                break;
                }

        }
    }

    fclose(F);
    printf("\n");
    printf("Appuyez sur entrer pour revenir au menu ");
    getch();
    menu();
}


void Afficher(){
    FILE *F;
    F=fopen("Stock.txt","r");
    printf("       ID      |       nom     |     qte     |     prix           \n");
    printf("---------------|---------------|-------------|-------------\n");
    while (1){
        fscanf(F,"%d %s %d %d",&prod.ID,&prod.nom,&prod.stock,&prod.prix);
        if (feof(F)){
            break;
            }
        printf("%d\t         %s\t       %d\t         %d \n",prod.ID,prod.nom,prod.stock,prod.prix);
        }
    fclose(F);
    printf("\n");
    printf("Appuyez sur entrer pour revenir au menu ");
    getch();
    menu();
}

void menu(){
    int j;
	system("cls");
	main:
	printf("\n======================== Application De Gestion De Stock ========================");
	printf("                                                                                          ");
	printf("                                                                                          ");
	printf("\n\t\tPress Choisir un chiffre ");
	printf("\n\t\tPress <1> Ajouter un produit");
	printf("\n\t\tPress <2> Modifier un produit existant");
	printf("\n\t\tPress <3> Supprimer un produit");
	printf("\n\t\tPress <4> Afficher la description d'un produit");
	printf("\n\t\tPress <5> Afficher le stock ");
	printf("\n\t\tPress <6> Afficher l'historique des operations ");
	printf("\n\t\tPress <7> Sortir de l'application ");

	printf("\n\n\t\tEnter your choice[1-7] : ");
	scanf("%i", &j);

	system("cls");

		switch(j)
	{
		case 1:
			Ajout();
			break;
		case 2:
			Modifier();
			break;
		case 3:
            Supprimer();
			break;
		case 4:
            Recherche();
			break;
		case 5:
			Afficher();
			break;
        case 6:
            Historique();
        case 7:
            break;
		default:
		printf("Invalid Choice! System Exit\n");
			getch();
	}
}
void wel_come(void)

{
	time_t t;
	time(&t);
	printf("                                                                                                         \n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\t\t\t\t%s",ctime(&t));


	printf("\t\t\t     ====================================\t\t\t\t\t\n");
	printf("\t\t\t\t       Bienvenue \t \t\t\t\t\t\t\n");
	printf("\t\t\t        Application De Gestion Du Stock\t \t\t\t\t\t\t\n");
	printf("\t\t\t     ====================================\t\t\t\t\t\t\n");
	printf("Appuyez sur entrer pour continuer.........\n");

	printf("--------------------------------------------------------------------------------\n");

getch();
system("cls");
}
void login(){
int a=0,i=0;
    char name[10],c=' ';
    char password[10],code[10];
    char user[10]="admin";
    char pass[10]="admin";
    do{

        printf("\n  ========================  CONNEXION   ========================  ");
        printf(" \n                        NOM:-");
        scanf("%s", &name);
        printf(" \n                        MOT DE PASSE:-");
        while(i<10){
            password[i]=getch();
            c=password[i];
            if(c==13) break;
            else printf("*");
            i++;
            }
        password[i]='\0';
        i=0;
        if(strcmp(name,"admin")==0 && strcmp(password,"admin")==0){
            printf("  \n\n\n       BIENVENUE A L'APPLICATION DE GESTION DU STOCK !!!! ");
            printf("\n\n\n\t\t\t\tAppuyez sur entrer pour continuer...");
            getch();
            break;
            }
        else{
            printf("\n        DESOLE !!!!  CONNEXION ECHOUE");
            a++;
            getch();
            }
        } while(a<=2);

    if (a>2){
        printf("\n Désolé, vous avez entré le mauvais nom d'utilisateur et mot de passe quatre fois!!!");
		getch();
		}
		system("cls");
}
main(){
    login();
    wel_come();
    menu();
}



