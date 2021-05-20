#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define USER_LENGTH 16
#define PASS_LENGTH 16
#define POST_LENGTH 400

//Definizione dei tipi
typedef struct data
{
    char username[USER_LENGTH];
    char password[PASS_LENGTH];
    char post[10][POST_LENGTH];
    struct utente *seguiti;
}data;

typedef struct utente
{
    data infoutente;
    struct utente * next;
}utente;

//PROTOTIPI
utente* signup(utente *head);
utente* aggiungiutente(utente *head,utente *user);
void print_list(utente *u);
int controlloutenza(char username[USER_LENGTH],utente* head);
void log_in(utente *head);
void elimina_account(utente *head);

//MAIN
int main()
{
    utente* head = NULL; //testa della lista degli utenti
    unsigned int scelta; //scelta menu

    do
    {
        system("CLS");
        printf(" MENU \n1)Log in \n2)Sign up \n3)Delete account \n4)Per uscire\n");
        scanf("%d",&scelta);
        switch(scelta)
        {
            case 1:
                log_in(head);
                menu_login(head);
                break;
            case 2:
                head = aggiungiutente(head,signup(head));
                printf("Utenza creata!\n");
                system("PAUSE");
                break;
            case 3:
                printf("Delete account");
                break;
            case 4:
                system("PAUSE");
                break;
            default:
                printf("default");
                break;
        }
    }while(scelta !=4);
    return 0;
}

//FUNZIONI
utente* signup(utente *head)
{
    system("CLS");
    utente * nuovoutente = (utente*)malloc(sizeof(utente));
    char password[PASS_LENGTH];
    char confermapassword[PASS_LENGTH];
    int trovato;
    do
    {
        printf("Inserisci il tuo nome utente:");
        scanf("%s",nuovoutente->infoutente.username);
        trovato = controlloutenza(nuovoutente->infoutente.username,head);
        if(trovato == 0)
        {
            system("CLS");
            printf("Utenza già esistente!\n");
        }
    }while(trovato == 0);
    do
    {
        printf("Inserisci la tua password:");
        scanf("%s",password);
        printf("Conferma password :");
        scanf("%s",confermapassword);
        if(strcmp(password, confermapassword) != 0)
        {
            printf("La password e la conferma non corrispondono!\n");
            system("PAUSE");
            system("CLS");
        }
        else
        {
            strcpy(nuovoutente->infoutente.password,password);
        }
    }while(strcmp(password, confermapassword));
    strcpy(nuovoutente->infoutente.post,"");
    nuovoutente->infoutente.seguiti = NULL;
    return nuovoutente;
}
//AGGIUNGI UTENTE LISTA
utente* aggiungiutente(utente *head,utente *user)
{
    utente* temp = head;
    if(head == NULL)
    {
        return user;
    }else
    {
        while(temp->next !=NULL)
        {
            temp = temp->next;
        }
        temp->next= user;
        return head;
    }
}
//STAMPA LISTA
void stampa_utenti(utente *utente)
{
    printf("UTENTI\n");
    while(utente != NULL)
    {
        printf("%s\n" ,utente->infoutente.username);
        utente = utente->next;
    }
}
//CONTROLLO PRESENZA UTENZA
int controlloutenza(char username[USER_LENGTH],utente* head)
{
   while(head != NULL)
    {
        if(strcmp(username,head->infoutente.username) == 0)
            return 0;
        head = head->next;
    }
    return 1;
}
//CONTROLLO PASSWORD UTENZA
int controllopasswordutenza(char username[USER_LENGTH],char password[PASS_LENGTH],utente* head)
{
   while(head != NULL)
    {
        if(strcmp(username,head->infoutente.username) == 0)
        {
            if(strcmp(password,head->infoutente.password) == 0)
            {
                return 0;
            }else{
                return 1;
            }
        }
        head = head->next;
    }
    return 1;
}
//LOGIN
void log_in(utente *head)
{
    char username[USER_LENGTH];
    char password[USER_LENGTH];
    int controllousername;
    int controllopassword;
    do
    {
        system("CLS");
        printf("Inserisci il nome utente:");
        scanf("%s",username);
        controllousername = controlloutenza(username,head);
        if(controllousername !=0)
        {
            printf("Utenza non trovata inserire nuovo utente!\n");
        }
    }while(controllousername !=0);

    do
    {
        system("CLS");
        printf("Inserisci la password:");
        scanf("%s",password);
        controllopassword = controllopasswordutenza(username,password,head);
        if(controllopassword != 0)
        {
            printf("Password errata \n");
        }
    }while(controllopassword !=0);
    printf("Log in  effettuato!\n");
    system("PAUSE");
}
//ELIMINAZIONE ACCOUNT
void elimina_account(utente *head)
{

}
//MENU DOPO LOGIN
void menu_login(utente *head)
{
    int scelta;
    do
    {
        system("CLS");
        printf(" MENU \n1)Visualizza il nome degli utenti\n2)Ricerca utente\n7)Ricerca utente\n");
        scanf("%d",&scelta);
        switch(scelta)
        {
            case 1:
                stampa_utenti(head);
                system("Pause");
                break;
            case 2:
                ricerca_utente(head);
                system("Pause");
                break;
            case 7:
                printf("Logout! Si tornerà al menu di login\n");
                system("Pause");
                break;
            default:
                printf("default");
                break;
        }
    }while(scelta != 7);
}

//RICERCA UTENTE
void ricerca_utente(utente* head)
{
   char username[USER_LENGTH];
   printf("Inserisci l'utenza che vuoi cercare:");
   scanf("%s",username);
   while(head != NULL)
    {
        if(strcmp(username,head->infoutente.username) == 0)
            {
                printf("L'utente %s è stato trovato!\n",username);
                return;
            }
        head = head->next;
    }
    printf("L'utente %s non è stato trovato!",username);
}

//INIT SOCIAL NETWORD
utente* init_social(utente *head)
{

}

