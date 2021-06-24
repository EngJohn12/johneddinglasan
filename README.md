# johneddinglasan





 
 

24 GIUGNO
 

 
Università degli Studi di Messina
Corso: Ing. Elettronica e Informatica
Autore:  Dinglasan John Ed
Nº matricola 503403





 

PANORAMICA
Software per la gestione dei dati dei criminali
OBIETTIVI
1.	Inserire, modificare e cancellazione di un criminale;
2.	Inserire, modificare e cancellazione di un crimine per un certo crimine
-Ricerca di un criminale tramite un certo identificativo (nome,cognome,etc);
3.	Ricerca di tutti i criminali che hanno commesso un determinato crimine;
4.	Inserimento, modifica e cancellazione delle celle;
5.	inserimento di un criminale in una cella al suo arrivo in funzione della capienza della cella;
6.	Salvataggi e caricamenti dello stato del programma da file.
STRUTTURE UTILIZZATE:
La struct lista_crimini è formato da 50 caratteri compreso il carattere terminatore  “\0”  e serve per creare la lista crimini e essendo vuota al momento la lista utilizzerà un puntatore *Crì che  sarà uguale a NULL:
struct lista_crimini{
    char crimine[50];
    struct lista_crimini *next_crimini;

};

typedef struct lista_crimini* Crimini;

void crea_lista_crimini(Crimini* cri){
    *cri=NULL;
}
La struttura qui sottostante serve per registrare il criminale attraverso queste variabili nome, cognome  e crimini commessi(crime), quest’ultimo è stato definito da un tipo di variabile crimini precedentemente utilizzato per creare la lista dei crimini commessi:
typedef struct{
    char nome[20];
    char cognome[20];
    Crimini* crime;
	int numero_id;
} Criminale;



La struttura qui presente serve per creare una lista dei criminali che verranno aggiunti man mano che i criminali arriveranno alla sede gli verrà attribuito un numero identificativo:
struct lista_criminali{
    Criminale detenuto;
    struct lista_criminali *next;
};
typedef struct lista_criminali* lista_criminali;

void crea_lista_criminali(lista_criminali* detenuto){
    *detenuto=NULL;
    }

La struttura lista_detenuticella ospita un intero detenuto_id, e un puntatore next. L’intero detenuto_id servirà per riconoscere i criminali presenti nella cella confrontando il numero_id definito precedentemente nella struct Criminale:
  
struct lista_detenuticella{
	int detenuto_id;
	 struct lista_detenuticella *next;
};
typedef lista_detenuticella* lista_detenuticella;

void crea_ lista_detenuticella(lista_detenuticella* detenuticella_head){
detenuticella_head=NULL;
}

La struttura viene definita come un tipo di variabile che verrà poi successivamente utilizzato per creare la lista delle celle con il numero della cella con all’interno i criminali nel quale verrà aggiunto riconoscibile attraverso numero identificativo presente nella struct lista_detenuti_cella
typedef struct {
    int numero; //numero cella es. cella numero 1||2||3||4||...
	int posti;    
struct lista_detenuticella* n_id;
}Cella;

La struttura sottostante  serve per creare una la lista delle celle nel quale verranno ospitati i criminali durante la detenzione, infatti la struttura ospiterà il tipo di variabile cella con variabile gabbia e la Struct lista_cella sarà indicato con un puntatore Next:
struct lista_cella{
    Cella gabbia;
	struct lista_cella *next;
    };

typedef struct lista_cella* lista_cella;

void crea_lista_cella(lista_cella* cage){
    *cage=NULL;

}
FUNZIONI UTILIZZATE:
Inserimento criminale:
Questa funzione permette la registrazione di un criminale tramite l’inserimento da tastiera le credenziali personali dei criminali (nome, cognome, numero identificativo, crimine). Ogni volta che un criminale viene registrato e viene inserita all’interno di una lista tramite l’inserimento ordinate per il numero identificativo visto che il numero identificativo ad essere nullo ogni volta che viene effettuato l’inserimento del numero identificativo e viene effettuata una ricerca all’interno della lista con la quale riusciamo a vedere se il criminale attraverso il cognome e nome del criminale sia presente all’interno del sistema. Se non è presente nel sistema il programma stesso sarà ad  attribuire il numero identificativo al nuovo criminale che verrà aggiunto nella lista, se invece il criminale è già presente nella lista verrà aggiunto il nuovo crimine commesso alla lista dei crimini commessi da ciascun criminale.
Cancella criminale:
La cancellazione del criminale È un tipo di funzione nel quale ci scorre tutta la lista fino a quando non si trova il criminale da cancellare o non si arriva alla fine della lista. E’ necessario però memorizzare un puntatore l’elemento corrente ed un elemento a quello precedente per farsi che non si spezzi la lista.
Modifica criminale:
Se l’amministratore dovesse sbagliare oppure dovesse modificare i dati del criminale si andrà ad utilizzare un ciclo for richiamando i dati delle struct Criminali o struct crimini.
Inserimento cella:
Questa funzione serve a ad aggiungere il criminale all’interno di una cella di capienza due nel quale se vi sono già posti occupati restituirà un valore uno se invece non sarà occupata da nessuno oppure ci sarà posto darà un valore zero. Questa funzione verrà inserita all’interno della funzione inserimento criminale oppure all’interno della modifica criminale. 
Ricerca criminale: questa funzione serve a cercare il terminale attraverso il numero identificativo nel quale il programma scorre da tutta la lista fino a qua non si trova l’elemento oppure una si arriva alla fine della lista
Ricerca criminali crimini: questa funzione come la ricerca criminali serve per cercare i criminali attraverso il loro crimine commesso infatti scorrerà tutta la lista fino a quando non si trova si trova l’elemento oppure non si oppure non si arriva alla fine della lista nel quale si andranno a utilizzare dei puntatori che punteranno la testa della lista affinché il puntatore sia diverso da NULL e È il puntatore sia diverso dall’elemento il puntatore sarà uguale al puntatore che punta al prossimo elemento



struct lista_detenuticella{
	int detenuto_id;
	int posti;
struct lista_detenuticella *next;
};
typedef lista_detenuticella* lista_detenuticella;

void crea_ lista_detenuticella(lista_detenuticella* detenuticella_head){
detenuticella_head=NULL;
}



