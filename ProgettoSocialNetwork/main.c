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
    struct seguiti *seguiti;
}data;

typedef struct utente
{
    data infoutente;
    struct utente * next;
}utente;

typedef struct seguiti
{
    utente * seguito;
    struct seguiti * next;
}seguiti;

//PROTOTIPI
utente* signup(utente *head);
utente* aggiungiutente(utente *head,utente *user);
void print_list(utente *u);
utente* controlloutenza(char username[USER_LENGTH],utente* head);
utente* log_in(utente *head);
void segui_utente(utente *head,utente *utentein);
utente* elimina_utente(utente *head);
utente* init(utente *head);

//MAIN
int main()
{
    utente* head = NULL; //testa della lista degli utenti
    head = init(head);//init
    unsigned int scelta; //scelta menu
    utente* utentein;
    do
    {
        system("CLS");
        printf(" MENU \n1)Log in \n2)Sign up \n3)Delete account \n4)Per uscire\n");
        scanf("%d",&scelta);
        switch(scelta)
        {
            case 1:
                utentein = log_in(head);
                menu_login(head,utentein);
                break;
            case 2:
                head = aggiungiutente(head,signup(head));
                printf("Utenza creata!\n");
                system("PAUSE");
                break;
            case 3:
                head = elimina_utente(head);
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
//MENU DOPO LOGIN
void menu_login(utente *head,utente *utentein)
{
    int scelta;
    do
    {
        system("CLS");
        printf(" Loggato con %s \n MENU \n1)Visualizza il nome degli utenti\n2)Ricerca utente\n3)Segui utente\n4)Crea post\n5)Mostra i post di un utente\n6)Mostra i post dei seguiti\n7)Vedi l'ultimo post di ogni utente\n8)Log out\n",utentein->infoutente.username);
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
            case 3:
                segui_utente(head,utentein);
                system("Pause");
                break;
            case 4:
                crea_post(utentein);
                system("Pause");
                break;
            case 5:
                mostra_post(head);
                system("Pause");
                break;
            case 6:
                vedi_post_seguiti(utentein);
                system("Pause");
                break;
            case 7:
                stampa_ultimo_post_utenti(head);
                system("Pause");
                break;
            case 8:
                printf("Logout! Si tornerà al menu di login\n");
                system("Pause");
                break;
            default:
                printf("default");
                break;
        }
    }while(scelta != 8);
}

//FUNZIONI
utente* signup(utente *head)
{
    system("CLS");
    utente * nuovoutente = (utente*)malloc(sizeof(utente));
    char password[PASS_LENGTH];
    char confermapassword[PASS_LENGTH];
    utente* trovato;
    do
    {
        printf("Inserisci il tuo nome utente:");
        scanf("%s",nuovoutente->infoutente.username);
        trovato = controlloutenza(nuovoutente->infoutente.username,head);
        if(trovato != NULL)
        {
            system("CLS");
            printf("Utenza già esistente!\n");
        }
    }while(trovato != NULL);
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
    nuovoutente->infoutente.seguiti = (seguiti*)malloc(sizeof(seguiti));
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
utente* controlloutenza(char username[USER_LENGTH],utente* head)
{
   while(head != NULL)
    {
        if(strcmp(username,head->infoutente.username) == 0)
            return head;
        head = head->next;
    }
    return NULL;
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
utente* log_in(utente *head)
{
    char username[USER_LENGTH];
    char password[USER_LENGTH];
    utente* controllousername;
    int controllopassword;
    do
    {
        system("CLS");
        printf("Inserisci il nome utente:");
        scanf("%s",username);
        controllousername = controlloutenza(username,head);
        if(controllousername == NULL)
        {
            printf("Utenza non trovata inserire nuovo utente!\n");
        }
    }while(controllousername == NULL);

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
    return controllousername;
    system("PAUSE");
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
//CREA POST
void crea_post(utente* utenza)
{
    char post[POST_LENGTH];
    int i = 9;
    printf("Inserisci il post solo testo 400 char");
    scanf("%s",post);
    while(i>0)
    {
        strcpy(utenza->infoutente.post[i],utenza->infoutente.post[i-1]);
        i--;
    }
    strcpy(utenza->infoutente.post[0],post);
}

//STAMPA ULTIMO POST UTENTEI
void stampa_ultimo_post_utenti(utente *head)
{
    printf("ULTIMO POST DI TUTTI GLI UTENTE\n");
    while(head != NULL)
    {
        printf("%s -> %s\n" ,head->infoutente.username,head->infoutente.post[0]);
        head = head->next;
    }
}

//RICERCA UTENTE
void mostra_post(utente* head)
{
    char username[USER_LENGTH];
    int i = 0;
    printf("I post di quale utente vuoi cercare?");
    scanf("%s",username);
    printf("Post di '%s'\n",username);
    utente* utente = controlloutenza(username,head);
    if (utente == NULL)
    {
        printf("Utente non esiste");
    }else
    {
        while(i<10)
        {
            printf("Post %d -> %s\n",i+1,utente->infoutente.post[i]);
            i++;
        }
    }
}

//SEGUI UTENTE
void segui_utente(utente* head,utente* utentein)
{
    char username[USER_LENGTH];
    utente* trovato = NULL;
    seguiti* temp = (seguiti*)malloc(sizeof(seguiti));
    seguiti* app = utentein->infoutente.seguiti;
    printf("Inserisci l'utente da seguire:");
    scanf("%s",username);
    trovato = controlloutenza(username,head);
    if(trovato != NULL)
    {
        temp->seguito = trovato;
        temp->next = NULL;

        if(app == NULL)
        {
            utentein->infoutente.seguiti = temp;
        }
        else
        {
            while(app->next !=NULL)
                app = app->next;
            app->next = temp;
        }
    }else
    {
        printf("utente inesistente!");
    }
}

//VEDI ULTIMO POST DEI SEGUITI
void vedi_post_seguiti(utente* utentein)
{
    seguiti* seguiti = utentein->infoutente.seguiti;
    while(seguiti != NULL)
    {
        printf("%s -> %s\n",seguiti->seguito->infoutente.username,seguiti->seguito->infoutente.post[0]);
        seguiti = seguiti->next;
    }
}

//INIT
utente* init(utente * head)
{
    utente * u = NULL;
    char names[5][USER_LENGTH] = {
                         "octavio",
                         "roberto",
                         "gibbo",
                         "luca",
                         "arturo"
                     };
    char posts[10][POST_LENGTH] = {
                         "ciao mondo","oggi mi sento una sedia",
                         "pewpew","oggi sono felice",
                         "non c'è nulla di sbagliato","ho paura",
                         "ti ho dato i soldi","cuore",
                         "luvluv","sono morto"
                     };
    int i = 0;
    int j = 0;
    while(j<5)
    {
        u = (utente*)malloc(sizeof(utente));
        strcpy(u->infoutente.username,names[j]);
        strcpy(u->infoutente.password,"baubau");
        u->infoutente.seguiti = NULL;
        u->next = NULL;
        while(i<10)
        {
            strcpy(u->infoutente.post[i],posts[i]);
            i++;
        }
        i = 0;
        j++;
        head = aggiungiutente(head,u);
    }
    return head;
}
//ELIMINA UTENTE
utente* elimina_utente(utente* head)
{
   char username[USER_LENGTH];
   utente* temp = head;
   utente* app = head;
   printf("Inserisci l'utenza che vuoi eliminare:");
   scanf("%s",username);
   if(strcmp(username,head->infoutente.username) == 0)
   {
        head = head->next;
        free(temp);
        return head;
   }
   else
   {
    head = head->next;
    while(head != NULL)
    {
        if(strcmp(username,head->infoutente.username) == 0)
        {
            temp->next = head->next;
            free(head);
            return app;
        }
        temp = temp->next;
        head = head->next;
    }
    printf("L'utente %s non è stato trovato!",username);
   }
}
