#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 32
#define P 4	//numero di persone per ogni cella
#define TOT 100
#define file_lista "lista_criminali.txt"
#define file_crim "lista_crimini.txt"
//i criminali in lista con numero di cella = 0 sono criminali liberati ma mantenuti nella lista

typedef struct nodo_crimini{
	char crimine[n];
	struct nodo_crimini*next;
}nodo_crimini;

typedef struct nodo_criminali{
	int id,cella,crimini;
	char nome[n],cognome[n];
	nodo_crimini*head_crimini;
	struct nodo_criminali*next;
}nodo_criminali;

typedef struct nodo_id{
	int id;
	struct nodo_id*next;
}nodo_id;

typedef struct nodo_celle{
	int num_criminali;
	nodo_id *head_id;
}nodo_celle;

void clear_buff(){
	char c;
	while((c=getchar())!='\n' && c!=EOF);
}

void crea_celle(nodo_celle**celle,int *num_celle){
	*num_celle=TOT;
	*celle=(struct nodo_celle*)malloc((*num_celle)*sizeof(struct nodo_celle));
	if(*celle==NULL){
		printf("ERRORE DI MEMORIA\n");
		exit(1);
	}
	for(int i=0;i<(*num_celle);i++){
		(*celle)[i].num_criminali=0;
		(*celle)[i].head_id=NULL;
	}
}

void inserisci_crimini(struct nodo_criminali*head,int i){
	nodo_crimini*temp;
	temp=(struct nodo_crimini*)malloc(sizeof(struct nodo_crimini));
	if(temp==NULL){
		printf("ERRORE DI MEMORIA\n");
		exit(1);
	}
	printf("Inserisci il crimine n.%d (usa max %d caratteri ed il carattere '_' per lo spazio)\n",i,n);
	scanf("%s",temp->crimine);
	clear_buff();
	temp->next=head->head_crimini;
	head->head_crimini=temp;

}

void inserisci_id(struct nodo_celle celle[],int i,int id){
	nodo_id*temp;
	temp=(struct nodo_id*)malloc(sizeof(struct nodo_id));
	if(temp==NULL){
		printf("ERRORE DI MEMORIA\n");
		exit(1);
	}
	temp->id=id;
	temp->next=celle[i].head_id;
	celle[i].head_id=temp;
	celle[i].num_criminali+=1;
}

void pop_cella(struct nodo_celle celle[],int i,int id){
	nodo_id *scorr=celle[i].head_id,*prec;
	while(scorr!=NULL){
		if(scorr->id==id)
			break;
		prec=scorr;
		scorr=scorr->next;
	}
	if(scorr==(celle[i].head_id))
		celle[i].head_id=scorr->next;
	else
		prec->next=scorr->next;

	free(scorr);
	celle[i].num_criminali-=1;
}

void inserisci_criminale(struct nodo_criminali **head,struct nodo_criminali **tail, struct nodo_celle celle[],int num_celle){
	int i,posto_trovato=0,trovato=0;
	nodo_criminali*temp,*scorr=*head;
	temp=(struct nodo_criminali*)malloc(sizeof(struct nodo_criminali));
	if(temp==NULL){
		printf("ERRORE DI MEMORIA\n");
		exit(1);
	}
	temp->next=NULL;
	temp->head_crimini=NULL;

	if(*head==NULL)
		temp->id=1;
	else
		temp->id=(*tail)->id+1;

	for(i=0;i<num_celle;i++){
		if(celle[i].num_criminali<P){
			posto_trovato=1;
			break;
		}
	}
	if(posto_trovato){
		temp->cella=i+1;
		inserisci_id(celle,i,temp->id);
	}
	else{
		printf("\nNon e' possibile inserire il criminale, non ci sono celle disponibili\n");
		free(temp);
		return;
	}

	printf("\nInserisci il nome del criminale(max %d caratteri ed il carattere '_' per lo spazio)\n",n);
	scanf("%s",temp->nome);
	clear_buff();
	printf("\nInserisci il cognome del criminale(max %d caratteri ed il carattere '_' per lo spazio)\n",n);
	scanf("%s",temp->cognome);
	clear_buff();
	printf("\nVerifica se gia'presente in lista...\n");
	while(scorr!=NULL && !trovato){
		if(!(strcmp(temp->cognome,scorr->cognome)))
			if(!(strcmp(temp->nome,scorr->nome))){
				printf("\nIl criminale e' gia'presente in lista con id:%d\n",scorr->id);
				trovato=1;
				break;
			}
		scorr=scorr->next;
	}
	if(trovato){
		pop_cella(celle,i,temp->id);
		if(scorr->cella==0){
			scorr->cella=temp->cella;
			inserisci_id(celle,i,scorr->id);
			printf("\nIl criminale %d\nE' assegnato alla cella numero %d\n",scorr->id,temp->cella);
		}
		else
			printf("\nE' in cella %d\n",scorr->cella);
		free(temp);
		return;
	}
	do{
		printf("\nInserisci quanti crimini ha commesso\n");
		scanf("%d",&temp->crimini);
		clear_buff();
		if(temp->crimini<=0)
			printf("\nHAI INSERITO UN NUMERO NON VALIDO\n");
	}while(temp->crimini<=0);
	for(i=0;i<temp->crimini;i++)
		inserisci_crimini(temp,i+1);

	printf("\nInserimento riuscito\n\nL'id del criminale e': %d\nE' assegnato alla cella numero %d\n",temp->id,temp->cella);

	if(*head==NULL){
		*tail=temp;
		*head=temp;
	}
	else{
		(*tail)->next=temp;
		*tail=temp;
	}
}

void stampa_cella(struct nodo_celle celle[],int num_celle){
	int scelta;
	nodo_id *scorr;
	do{
		printf("\nInserisci il numero della cella di cui vuoi vedere i criminali (da 1 a %d)\n",num_celle);
		scanf("%d",&scelta);
		clear_buff();
		if(scelta<1 || scelta>num_celle)
			printf("\nHai inserito un numero non valido\n");
	}while(scelta<1 || scelta>num_celle);
	if(celle[scelta-1].num_criminali==0){
		printf("\nLa cella %d e' vuota\n",scelta);
		return;
	}
	printf("\nI criminali nella cella %d sono:\n",scelta);
	scorr=celle[scelta-1].head_id;
	while(scorr!=NULL){
		printf("-Criminale %d\n",scorr->id);
		scorr=scorr->next;
	}
}

void stampa_criminali(struct nodo_criminali*head){
	int scelta;
	nodo_crimini*scorr=head->head_crimini;
	do{
		printf("\nPer stampare tutti i dati inserisci 1, altrimenti 0 per gli id\n");
		scanf("%d",&scelta);
		clear_buff();
		if(scelta<0 || scelta>1)
			printf("\nHai inserito un numero non valido\n");
	}while(scelta<0 || scelta>1);
	if(scelta)
		while(head!=NULL){
			printf("\nIl criminale:%d nella cella %d\nNome:%s\nCognome:%s\nCrimini:\n",head->id,head->cella,head->nome,head->cognome);
			while(scorr!=NULL){
				printf("-%s\n",scorr->crimine);
				scorr=scorr->next;
			}
			head=head->next;
			if(head!=NULL)
				scorr=head->head_crimini;
		}
	else
		while(head!=NULL){
			printf("Criminale %d nella cella %d\n",head->id,head->cella);
			head=head->next;
		}
}

void modifica_nome(struct nodo_criminali *temp){
	printf("\nInserisci il nome del criminale n%d (max %d caratteri, usa '_' per inserire uno spazio)\n",temp->id,n);
	scanf("%s",temp->nome);
	clear_buff();
	printf("\nInserisci il cognome del criminale n%d (max %d caratteri, usa '_' per inserire uno spazio)\n",temp->id,n);
	scanf("%s",temp->cognome);
	clear_buff();
	return;
}

void modifica_crimini(struct nodo_criminali *temp){
	int scelta,trovato=0;
	char crime[n];
	nodo_crimini *scorr,*prec;
	do{
		printf("\nInserisci 1 se devi inserire un crimine o 0 se devi cancellare un crimine\n");
		scanf("%d",&scelta);
		clear_buff();
		if(scelta<0||scelta>1)
			printf("\nHai inserito un numero non valido\n");
	}while(scelta<0||scelta>1);
	if (scelta==0){
		if(temp->head_crimini->next==NULL){
			printf("\nNon puoi cancellare l'unico crimine commesso, prima devi inserirne uno se vuoi fare una sostituzione\n");
			return;
		}
		scorr=temp->head_crimini;
		printf("\nLa lista dei crimini:\n");
		while(scorr!=NULL){
			printf("-%s\n",scorr->crimine);
			scorr=scorr->next;
		}
		scorr=temp->head_crimini;
		printf("\nInserisci il crimine da cancellare\n");
		scanf("%s",crime);
		clear_buff();
		while(scorr!=NULL){
			if(strcmp(scorr->crimine,crime)==0){
				trovato=1;
				break;
			}
			prec=scorr;
			scorr=scorr->next;
		}
		if(!trovato){
			printf("\nHai inserito un crimine non presente in lista\n");
			return;
		}
		if(scorr==temp->head_crimini)
			temp->head_crimini=scorr->next;
		else
			prec->next=scorr->next;
		free(scorr);
		temp->crimini-=1;
		printf("\nCrimine cancellato con successo\n");
		return;
	}
	scorr=(struct nodo_crimini*)malloc(sizeof(struct nodo_crimini));
	if(scorr==NULL){
		printf("ERRORE DI MEMORIA\n");
		exit(1);
	}
	printf("\nInserisci il crimine da aggiungere\n");
	scanf("%s",scorr->crimine);
	clear_buff();
	scorr->next=temp->head_crimini;
	temp->head_crimini=scorr;
	temp->crimini+=1;
	return;
}

void menu_modifica(struct nodo_criminali **head,struct nodo_criminali **tail, struct nodo_celle celle[]){
	int scelta,trovato=0;
	nodo_criminali *temp=*head;
	nodo_criminali *prec;
	nodo_crimini *temp_crimini;
	printf("\nInserisci il numero id del criminale da cercare\n");
	scanf("%d",&scelta);
	clear_buff();
	while(temp!=NULL && !trovato){
		if(temp->id==scelta){
			trovato=1;
			break;
		}
		prec=temp;
		temp=temp->next;
	}
	if(!trovato){
		printf("\nL'id inserito non corrisponde a nessun criminale in lista\n");
		return;
	}
	printf("\nL'id inserito corrisponde al criminale nella cella %d\n",temp->cella);
	printf("\nI suoi dati sono:\nNome: %s\nCognome: %s\nCrimini:\n",temp->nome,temp->cognome);
	temp_crimini=temp->head_crimini;
	while(temp_crimini!=NULL){
		printf("-%s\n",temp_crimini->crimine);
		temp_crimini=temp_crimini->next;
	}
	do{
		printf("\nScegli la funzione da fare o 0 per tornare al menu precedente\n");
		printf("1)Modifica Nome/cognome del criminale %d\n",temp->id);
		printf("2)Modifica i Crimini del criminale %d\n",temp->id);
		printf("3)Libera criminale %d\n",temp->id);
		scanf("%d",&scelta);
		clear_buff();
		switch(scelta){
			case 0:	break;
			case 1:
				modifica_nome(temp);
				break;
			case 2:
				modifica_crimini(temp);
				break;
			case 3:
				if(temp->cella==0){
					printf("\nIl criminale era gia' stato liberato precedentemente\n");
					break;
				}
				pop_cella(celle,(temp->cella)-1,temp->id);
				temp->cella=0;
				puts("\nIl criminale e' stato liberato con successo\n");
				return;
			default:
				printf("\nHai inserito un numero non valido\n");
				break;
		}
	}while(scelta!=0);
}

void alloca_criminale(struct nodo_criminali **temp){
	*temp=(struct nodo_criminali*)malloc(sizeof(struct nodo_criminali));
	if(*temp==NULL){
		printf("\nErrore di memoria\n");
		exit(1);
	}
}

void alloca_crimine(struct nodo_crimini **crimine){
	*crimine=(struct nodo_crimini*)malloc(sizeof(struct nodo_crimini));
	if(*crimine==NULL){
		printf("\nErrore di memoria\n");
		exit(1);
	}
}

void carica_dati(struct nodo_criminali **head,struct nodo_criminali **tail, struct nodo_celle celle[]){
	int i,ciclo=1;
	nodo_criminali *temp=NULL;
	nodo_crimini *crimine=NULL;
	FILE *p_criminali=NULL, *p_crimini=NULL;
	p_criminali=fopen(file_lista,"r");
	p_crimini=fopen(file_crim,"r");
	if(p_crimini==NULL || p_criminali==NULL){
		printf("\nNon sono stati trovati i file da cui caricare i dati\n");
		return;
	}
	while(ciclo){
		alloca_criminale(&temp);
		temp->head_crimini=NULL;
		temp->next=NULL;
		if((fscanf(p_criminali,"%s %s %d %d %d\n",temp->nome,temp->cognome,&temp->id,&temp->cella,&temp->crimini))==EOF)
			break;
		inserisci_id(celle,(temp->cella)-1,temp->id);
		for(i=0;i<temp->crimini;i++){
			alloca_crimine(&crimine);
			fscanf(p_crimini,"%s\n",crimine->crimine);
			crimine->next=temp->head_crimini;
			temp->head_crimini=crimine;
		}
		if(*head==NULL)
			*head=temp;
		else
			(*tail)->next=temp;
		*tail=temp;
	}
	fclose(p_criminali);
	fclose(p_crimini);
	printf("\nCaricamento eseguito con successo\n");
}

void salva_dati(struct nodo_criminali *head){
	int scelta;
	FILE *p_criminali=NULL, *p_crimini=NULL;
	p_criminali=fopen(file_lista,"w");
	p_crimini=fopen(file_crim,"w");
	if(p_crimini==NULL || p_criminali==NULL){
		printf("\nNon e'possibile salvare i dati per errore di memoria\n");
		return;
	}
	while(head!=NULL){
		fprintf(p_criminali,"%s %s %d %d %d\n",head->nome,head->cognome,head->id,head->cella,head->crimini);
		while(head->head_crimini!=NULL){
			fprintf(p_crimini,"%s\n",head->head_crimini->crimine);
			head->head_crimini=head->head_crimini->next;
		}
		head=head->next;
	}
	fclose(p_criminali);
	fclose(p_crimini);
	printf("\nSalvataggio eseguito con successo\n");
}

void menu(){
	int scelta,num_celle;
	nodo_criminali *head_criminali=NULL,*tail_criminali=NULL;
	nodo_celle *celle=NULL;
	printf("MENU\n");
	printf("\nInizializzazione delle celle (%d)\n",TOT);
	crea_celle(&celle,&num_celle);
	do{
		printf("\nInserisci 1 per caricare i dati precedenti altrimenti 0\n");
		scanf("%d",&scelta);
		clear_buff();
		if(scelta<0 || scelta>1)
			printf("\nHai inserito un numero non valido\n");
	}while(scelta<0 || scelta>1);
	if(scelta)
		carica_dati(&head_criminali,&tail_criminali,celle);
	do{
		printf("\nSCEGLI LA FUNZIONE DA FARE o 0 PER USCIRE (***I CRIMINALI CON CELLA ASSEGNATO 0 SONO I CRIMINALI LIBERATI***)\n");
		printf("1)Inserisci criminale\n");
		printf("2)Stampa criminali di una cella (solo id)\n");
		printf("3)Stampa tutti i criminali (tutti i dati o solo gli id)\n");
		printf("4)Cerca criminale (MODIFCA DATI / LIBERA CRIMINALE)\n");
		scanf("%d",&scelta);
		clear_buff();
		switch(scelta){
			case 0: break;
			case 1:
				inserisci_criminale(&head_criminali,&tail_criminali,celle,num_celle);
				break;
			case 2:
				if(head_criminali==NULL){
					printf("\nNon ci sono criminali in lista\n");
					break;
				}
				stampa_cella(celle,num_celle);
				break;
			case 3: if(head_criminali==NULL){
					printf("\nNon ci sono criminali in lista\n");
					break;
				}
				stampa_criminali(head_criminali);
				break;
			case 4:
				if(head_criminali==NULL){
					printf("\nNon ci sono criminali in lista\n");
					break;
				}
				menu_modifica(&head_criminali,&tail_criminali,celle);
				break;
			default:
				printf("\nHAI INSERITO UN NUMERO NON VALIDO\n");
				break;
		}
	}while(scelta!=0);
	do{
		printf("\nPer salvare i dati inserisci 1, altrimenti 0\n");
		scanf("%d",&scelta);
		if(scelta<0 || scelta>1)
			printf("\nHai inserito un numero non valido\n");
	}while(scelta<0 || scelta>1);
	if(scelta)
		salva_dati(head_criminali);
}

int main(){
	menu();
}
