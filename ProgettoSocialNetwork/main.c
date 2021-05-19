#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
    char *username;
    char *password;
}data;

typedef struct utente
{
    data infoutente;
    struct utente * next;
}utente;

int main()
{
    utente* head = NULL;
    singup(head);
    singup(head);
    singup(head);
    singup(head);
    print_list(head);
    return 0;
}

void singup(utente *head){
    char *username = malloc(20*sizeof(char));
    char *password = malloc(80*sizeof(char));
    char *confermapassword = malloc(80*sizeof(char));
    utente * temp = head;
    data infoutente;
    printf("Inserisci il tuo nome utente:");
    fgets(username,20,stdin);
    do
    {
        printf("Inserisci la tua password:");
        fgets(password,80,stdin);
        printf("Conferma password :");
        fgets(confermapassword,80,stdin);
        if(strcmp(password, confermapassword))
        {
            printf("La password e la conferma non corrispondono!");
            system("PAUSE");
            system("CLS");
        }
    }while(strcmp(password, confermapassword));

    infoutente.username = username;
    infoutente.password = password;

    utente * u =  (utente *) malloc(sizeof(utente));
    u->infoutente = infoutente;
    u->next = NULL;
    aggiungiUtente(head,u);
}

void print_list(utente *u)
{
    while(u != NULL)
    {
        printf("Username: %s" ,u->infoutente.username);
        printf("Password: %s\n",u->infoutente.password);
        u = u->next;
    }
}

void aggiungiUtente(utente **head_ref, utente *u)
{
  /* link the old list at the end of the new node */
  u->next = *head_ref;

  /* move the head to point to the new node */
  *head_ref = u;
}

