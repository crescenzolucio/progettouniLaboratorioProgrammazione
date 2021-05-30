#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_LENGTH 16
#define PASS_LENGTH 16
#define POST_LENGTH 400

//Definizione dei tipi strutturati
typedef struct data
{
    char username[USER_LENGTH];
    char password[PASS_LENGTH];
    char post[10][POST_LENGTH];
    struct seguiti *seguiti;
}data;//data contenente le informazioni sull'utente

typedef struct utente
{
    data infoutente;
    struct utente * next;
}utente;//utente

typedef struct seguiti
{
    utente * seguito;
    struct seguiti * next;
}seguiti;//seguiti

//Prototipi delle funzioni
void menu_login(utente *head,utente *utentein);     //Menu dopo aver effettuato il login
utente* sign_up(utente *head);                       //Funzione di login
utente* aggiungi_utente(utente *head,utente *user);  //Viene aggiunto un nuovo utente
void stampa_utenti(utente *utente);                 //Mostra il nome di tutti gli utenti
utente* controllo_utenza(char username[USER_LENGTH],utente* head);                                //Controlla se l'utenza esiste e la resistuisce come output
int controllo_password_utenza(char username[USER_LENGTH],char password[PASS_LENGTH],utente* head); //Verifico se la password inserita sia giusta
utente* log_in(utente *head);                       //Log in con username e password
void ricerca_utente(utente* head);                  //Controllo se un utente è presente
void crea_post(utente* utenza);                     //Crea un nuovo post
void stampa_ultimo_post_utenti(utente *head);       //Stampa l'ultimo post di tutti gli utenti
void mostra_post(utente* head);                     //Mostra gli ultimi 10 post di un utente inserito se esistente
void segui_utente(utente* head,utente* utentein);   //Inserisce il nome di un nuovo utente da seguire
void vedi_post_seguiti(utente* utentein);           //Mostra l'ultimo post di ogni utente seguito
utente* init(utente * head);                        //Inizializza il social con 5 account con 10 post ciascuno
utente* elimina_utente(utente* head);               //Elimina un utente
void elimina_seguito(utente* head,char username[USER_LENGTH]); //Elimina i seguiti prima di eliminare l'utenza
int controllo_seguiti(char username[USER_LENGTH],seguiti* head); //Controllo se ho già inserito l'utente che sto inserendo

//Main
int main()
{
    utente* head = NULL; //Testa della lista degli utenti
    head = init(head);   //Inizializzazione
    unsigned int scelta; //Scelta menu
    utente* utentein;
    do
    {
        system("CLS");
        printf("MENU \n1)Log in \n2)Sign up \n3)Elimina utenza \n4)Per uscire\n");
        scanf("%d",&scelta);
        switch(scelta)
        {
            case 1://Login
                utentein = log_in(head);
                menu_login(head,utentein);
                break;
            case 2://sign_up
                head = aggiungi_utente(head,sign_up(head));
                printf("Utenza creata!\n");
                system("PAUSE");
                break;
            case 3://Elimina
                head = elimina_utente(head);

                system("PAUSE");
                break;
            case 4://Uscire
                system("PAUSE");
                break;
            default:
                printf("Scelta errata!\n");
                system("Pause");
                break;
        }
    }while(scelta !=4);
    return 0;
}

//Menu dopo il login
void menu_login(utente *head,utente *utentein)
{
    int scelta;
    do
    {
        system("CLS");
        printf("Log in con %s \nMENU \n1)Visualizza il nome degli utenti\n2)Ricerca utente\n3)Segui utente\n4)Crea post\n5)Mostra i post di un utente\n6)Mostra l'ultimo post dei seguiti\n7)Vedi l'ultimo post di ogni utente\n8)Log out\n",utentein->infoutente.username);
        scanf("%d",&scelta);
        switch(scelta)
        {
            case 1:
                stampa_utenti(head);//1)Visualizza il nome degli utenti
                system("Pause");
                break;
            case 2:
                ricerca_utente(head);//2)Ricerca utente
                system("Pause");
                break;
            case 3:
                segui_utente(head,utentein);//3)Segui utente
                system("Pause");
                break;
            case 4:
                crea_post(utentein);//4)Crea post
                system("Pause");
                break;
            case 5:
                mostra_post(head);//5)Mostra i post di un utente
                system("Pause");
                break;
            case 6:
                vedi_post_seguiti(utentein);//6)Mostra l'ultimo post dei seguiti
                system("Pause");
                break;
            case 7:
                stampa_ultimo_post_utenti(head);//7)Vedi l'ultimo post di ogni utente
                system("Pause");
                break;
            case 8:
                printf("Logout! Si tornera al menu di login\n");//8)Log out
                system("Pause");
                break;
            default:
                printf("Scelta errata!\n");
                system("Pause");
                break;
        }
    }while(scelta != 8);
}

//Log in
utente* log_in(utente *head)
{
    char username[USER_LENGTH];
    char password[USER_LENGTH];
    utente* ctrlusername; //controllo per verifica dell'utenza
    int ctrlpassword;
    do
    {
        //Verifico se l'utenza è presente
        system("CLS");
        printf("Inserisci il nome utente:");
        scanf("%s",username);
        ctrlusername = controllo_utenza(username,head);
        if(ctrlusername == NULL)
        {
            printf("Utenza non trovata inserire nuovo utente!\n");
            system("PAUSE");
        }
    }while(ctrlusername == NULL);

    do
    {
        //Verifico se la password inserita sia giusta e ripeto finchè non viene inserita quella esatta
        printf("Inserisci la password:");
        scanf("%s",password);
        ctrlpassword = controllo_password_utenza(username,password,head);
        if(ctrlpassword != 0)
        {
            printf("Password errata \n");
            system("PAUSE");
        }
    }while(ctrlpassword !=0);

    printf("Log in  effettuato!\n");
    return ctrlusername;
    system("PAUSE");
}

//Registrazione utenza
utente* sign_up(utente *head)
{
    utente * nuovoutente = (utente*)malloc(sizeof(utente));
    int i = 0;
    char password[PASS_LENGTH];
    char confermapassword[PASS_LENGTH];
    utente* trovato;
    //Verifico se la nuova utenza è gia presente
    do
    {
        system("CLS");
        printf("Inserisci il tuo nome utente(MAX 15):");
        scanf("%s",nuovoutente->infoutente.username);
        trovato = controllo_utenza(nuovoutente->infoutente.username,head);
        if(trovato != NULL)
        {
            printf("Utenza gia' esistente!\n");
            system("PAUSE");
        }
    }while(trovato != NULL);
    //Verifico se la password e la conferma siano uguali e l'aggiungo alla nuova utenza
    do
    {
        printf("Inserisci la tua password(MAX 15):");
        scanf("%s",password);
        printf("Conferma password (MAX 15):");
        scanf("%s",confermapassword);
        if(strcmp(password, confermapassword) != 0) //strcmp compara due stringhe se restituisce 0 sono uguali
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

    while(i<10)  //Popolo i post ed i seguiti per evitare problemi di segmentaion fault
        {
            strcpy(nuovoutente->infoutente.post[i],"");
            i++;
        }
    nuovoutente->infoutente.seguiti = NULL;
    nuovoutente->next = NULL;
    return nuovoutente; //restituisco la nuova utenza
}

//Aggiunge un nuovo utente alla lista degli utenti
utente* aggiungi_utente(utente *head,utente *user)
{
    //scorro la lista fino alla coda per poi inserire la nuova utenza
    utente* temp = head;
    if(head == NULL) //in caso la lista sia vuota restituisco la nuova utenza
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

//Visualizza il nome di tutti gli utenti
void stampa_utenti(utente *utente)
{
    //scorro la lista per stampare il nome di tutti gli utenti
    printf("UTENTI\n");
    while(utente != NULL)
    {
        printf("%s\n" ,utente->infoutente.username);
        utente = utente->next;
    }
}

//Verifica dell'esistenza di un utenza
utente* controllo_utenza(char username[USER_LENGTH],utente* head)
{
   //Controllo se esiste un utenza e la restituisco
   while(head != NULL)
    {
        if(strcmp(username,head->infoutente.username) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

//Verifica della presenza nei seguiti
int controllo_seguiti(char username[USER_LENGTH],seguiti* head)
{
   //Controllo se un seguito è gia presente nella lista seguiti di un utente
   while(head != NULL)
    {
        if(strcmp(username,head->seguito->infoutente.username) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

//Verifica password
int controllo_password_utenza(char username[USER_LENGTH],char password[PASS_LENGTH],utente* head)
{
   //Controllo la password dell'utenza
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

//Verifica l'esistenza di un utenza
void ricerca_utente(utente* head)
{
   //Semplice funzione che ricerca un utenza e stampa l'avvenuta ricerca o meno
   char username[USER_LENGTH];
   printf("Inserisci l'utenza che vuoi cercare:");
   scanf("%s",username);
   while(head != NULL)
    {
        if(strcmp(username,head->infoutente.username) == 0)
            {
                printf("L'utente %s e' stato trovato!\n",username);
                return;
            }
        head = head->next;
    }
    printf("L'utente %s non e' stato trovato!\n",username);
}

//Crea un post
void crea_post(utente* utenza)
{
    //Creo un post per l'utenza loggata
    char post[POST_LENGTH];
    int i = 9;
    int j;
    printf("Inserisci il post solo testo (MAX 400): ");
    fgetc(stdin);//Usato per il corretto funzionamento di fgets
    fgets(post,sizeof(post),stdin);

    for(j=0;j<=POST_LENGTH;j++) //scorro per eliminare \n inserito alla fine del fgets
    {
        if( post[j] == '\n')
        {
            post[j] = '\0';
            break;
        }
    }
    //Sposto i vecchi post di una posizione a causa dei 10 post massimi
    while(i>0)
    {
        strcpy(utenza->infoutente.post[i],utenza->infoutente.post[i-1]);
        i--;
    }
    strcpy(utenza->infoutente.post[0],post); //inserisco l'ultimo post nella posizione 0
}

//Stampa l'ultimo post di tutti gli utenti FUNZIONE AGGIUNTIVA
void stampa_ultimo_post_utenti(utente *head)
{
    //Stampo l'ultimo post di ogni utente
    printf("ULTIMO POST DI TUTTI GLI UTENTE\n");
    while(head != NULL)
    {
        //il post in posizione 0 è l'ultimo inserito
        if(strcmp(head->infoutente.post[0],"") != 0)
        {
            printf("%s -> %s\n" ,head->infoutente.username,head->infoutente.post[0]);
        }else
        {
            printf("%s -> %s\n" ,head->infoutente.username,"NO POST");
        }
        head = head->next;
    }
}

//Mostra i post di un utente inserito
void mostra_post(utente* head)
{
    char username[USER_LENGTH];
    int i = 0;
    printf("I post di quale utente vuoi cercare?"); //inserisco l'utente da cercare
    scanf("%s",username);
    printf("Post di '%s'\n",username);
    utente* utente = controllo_utenza(username,head); //trovo l'utente
    if (utente == NULL)//in caso sia NULL non esiste
    {
        printf("Utente non esiste");
    }else
    {
        while(i<10)//mostro tutti i post
        {
            if(strcmp(utente->infoutente.post[i],"") != 0) //mostro solo i post non vuoti
                printf("Post %d -> %s\n",i+1,utente->infoutente.post[i]);
            i++;
        }
    }
}

//Segue un utente
void segui_utente(utente* head,utente* utentein)
{
    char username[USER_LENGTH];
    int controlloseguito; //controllo per la verifica della presenza del seguito
    utente* trovato = NULL;
    seguiti* temp = (seguiti*)malloc(sizeof(seguiti));
    seguiti* app = utentein->infoutente.seguiti;
    printf("Inserisci l'utente da seguire:");
    scanf("%s",username);
    trovato = controllo_utenza(username,head);//verifico se l'utenza da seguire esista
    controlloseguito = controllo_seguiti(username,utentein->infoutente.seguiti);//controllo se è gia presente
    if(controlloseguito == 0)
    {
        if(trovato != NULL)
        {
            temp->seguito = trovato;
            temp->next = NULL;

            if(app == NULL) //se non ci sono seguiti
            {
                utentein->infoutente.seguiti = temp;
            }
            else
            {   //seguo la lista fino all'ultimo ed aggiungo il nuovo in coda
                while(app->next !=NULL)
                    app = app->next;
                app->next = temp;
            }
            printf("L'utente %s e' stato aggiunto ai seguiti!\n",username);
        }else
        {
            printf("L'utente %s e' inesistente!\n",username);
        }
    }else
    {
        printf("L'utente %s e' gia' presente tra i seguiti!\n",username);
    }
}

//Stampo l'ultimo post di ogni seguito
void vedi_post_seguiti(utente* utentein)
{
    //Scorro i seguiti e stampo l'ultimo post
    seguiti* seguiti = utentein->infoutente.seguiti;
    if(seguiti == NULL)
    {
        printf("Non ci sono seguiti!\n");
    }
    else
    {
        while(seguiti != NULL)
        {
            printf("%s -> %s\n",seguiti->seguito->infoutente.username,seguiti->seguito->infoutente.post[0]);//l'ultimo post è quello in posizione 0
            seguiti = seguiti->next;
        }
    }
}

//Inizializzazione
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
                         "non c'è nulla di sbagliato","wuii",
                         "ti ho dato i soldi","cuore",
                         "ho finito il progetto","sono vivo"
                     };
    int i = 0;
    int j = 0;
    while(j<5) //5 utenze
    {
        u = (utente*)malloc(sizeof(utente));
        strcpy(u->infoutente.username,names[j]);
        strcpy(u->infoutente.password,"baubau"); //setto a tutti la password "baubau"
        u->infoutente.seguiti = NULL;
        u->next = NULL;
        while(i<10) //inserisco i post
        {
            strcpy(u->infoutente.post[i],posts[i]);
            i++;
        }
        i = 0;
        j++;
        head = aggiungi_utente(head,u); //aggiungo l'utente alla lista
    }
    return head;
}

//Elimina un utenza
utente* elimina_utente(utente* head)
{
   char username[USER_LENGTH];
   char password[USER_LENGTH];
   utente* ctrlusername; //controllo per verifica dell'utenza
   int ctrlpassword = 0;
   char scelta = ' ';
   utente* temp = head;
   utente* app = head;

   //CONTROLLO UTENZA
    do
    {
        //Verifico se l'utenza è presente
        system("CLS");
        printf("Inserisci il nome utente:");
        scanf("%s",username);
        ctrlusername = controllo_utenza(username,head);
        if(ctrlusername == NULL)
        {
            printf("Utenza non trovata inserire nuovo utente!\n");
            system("PAUSE");
        }
    }while(ctrlusername == NULL);
    do
    {
        //Verifico se la password inserita sia giusta e ripeto finchè non viene inserita quella esatta
        printf("Inserisci la password:");
        scanf("%s",password);
        ctrlpassword = controllo_password_utenza(username,password,head);
        if(ctrlpassword != 0)
        {
            printf("Password errata \n");
            system("PAUSE");
        }
    }while(ctrlpassword !=0);
    system("CLS");
    printf("Vuoi eliminare la tua utenza?[Y/N]");//conferma eliminazione
    scanf(" %c",&scelta);

   //ELIMINAZIONE
   if(scelta == 'Y' || scelta == 'y'){
       elimina_seguito(head,username); //elimino prima tutti i seguiti
       if(strcmp(username,head->infoutente.username) == 0) //se è il primo della lista
       {
            head = head->next;
            free(head->infoutente.post);//elimino post
            free(temp);//elimino l'intera utenza
            return head;
       }
       else//se è oltre il primo
       {
        head = head->next;
        while(head != NULL)
        {
            if(strcmp(username,head->infoutente.username) == 0)//applico la stessa logica
            {
                temp->next = head->next;
                free(head->infoutente.post);
                free(head);
                return app;
            }
            temp = temp->next;
            head = head->next;
        }
       }
    }else
    {
        printf("Eliminazione annullata!\n",username);//in caso si utente non trovato
    }
}

//Elimina utente eliminato dai seguiti
void elimina_seguito(utente* head,char username[USER_LENGTH])
{
    seguiti* segui = NULL;
    seguiti* temp = NULL;
    while(head != NULL) //scorro la lista
    {
        if(head->infoutente.seguiti != NULL) //verifico che l'utenza abbia dei seguiti
        {
            segui = head->infoutente.seguiti; //salvo il corrente
            temp = head->infoutente.seguiti->next; //salvo il prossimo seguito

            if(strcmp(segui->seguito->infoutente.username,username) == 0) //se è il primo
            {
                free(head->infoutente.seguiti);
                head->infoutente.seguiti = temp;
            }
            else //in alternativa controllo gli altri
            {
                temp = segui;
                segui = segui->next;
                while(segui != NULL)
                {
                    if(strcmp(username,segui->seguito->infoutente.username) == 0)//applico la stessa logica e tengo traccia del seguito precedente a quello che verrà eliminato
                    {
                        temp->next = segui->next;
                        free(segui);
                        segui = temp->next;
                    }else
                    {
                        segui = segui->next;
                        temp = temp->next;
                    }
                }
            }
        }
        head = head->next;//passo alla prossima utenza
    }
}
