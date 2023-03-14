#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#include "defines.h"

void clear(){
    int a;
    while((a = getchar()) != '\n' && a != EOF){}
}

static void Aggiungi_pianta(MYSQL *conn, int ordine);
//1
static void Add_cPrivato(MYSQL *conn){
    MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[7];

	char codice[16];
    char nome[45];
    char fatturazione[45];
	char spedizione[45];
    char residenza[45];
    char tipo[6];
    char options[4] ={'1','2', '3'};
	char p;
    char valore[45];

	printf("\nInserisci Codice Fiscale Cliente: ");
	getInput(16, codice, false);
	printf("\nInserisci Nome Cliente: ");
	getInput(45, nome, false);
    printf("\nInserisci indirizzo fatturazione: ");
	getInput(45, fatturazione, false);
	printf("\nInserisci indirizzo spedizione: ");
	getInput(45, spedizione, false);
    printf("\nInserisci indirizzo residenza: ");
	getInput(45, residenza, false);
    printf("Seleziona Contatto\n");
	printf("\t1) email\n");
	printf("\t2) telefono\n");
    printf("\t3) cellulare\n");
	p = multiChoice("Seleziona Posizione", options, 3);
	switch(p) {
		case '1':
			strcpy(tipo, "email");
			break;
		case '2':
			strcpy(tipo, "tel");
			break;
        case '3':
            strcpy(tipo, "cel");
            break;
        default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
	}

	printf("\nInserisci Contatto: ");
	getInput(45, valore, false);
    

	if(!setup_prepared_stmt(&prepared_stmt, "call Aggiungi_cliente_privato(?, ?,?,?,?,?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = codice;
	param[0].buffer_length = strlen(codice);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[1].buffer = nome;
	param[1].buffer_length = strlen(nome);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[2].buffer = fatturazione;
	param[2].buffer_length = strlen(fatturazione);

	param[3].buffer_type =MYSQL_TYPE_VAR_STRING ;  //IN
	param[3].buffer = spedizione;
	param[3].buffer_length = strlen(spedizione); 

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[4].buffer = residenza;
	param[4].buffer_length = strlen(residenza);

	param[5].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[5].buffer = tipo;
	param[5].buffer_length = strlen(tipo);

	param[6].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[6].buffer = valore;
	param[6].buffer_length = strlen(valore);
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante l'inserimento.");
	} else {
		printf("-------------Cliente aggiunto con successo-------------\n");
	}

	mysql_stmt_close(prepared_stmt);

} 
//2
static void Add_cRivendita(MYSQL *conn){
    
 MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[9];

	char codice[16];
    char nome[45];
    char fatturazione[45];
	char spedizione[45];
    char residenza[45];
    char tipo[6];
    char options[4] ={'1','2', '3'};
	char p;
    char valore[45];
    char nome_referente[45];
    char cognome_referente[45];

	printf("\nInserisci Partita IVA Cliente: ");
	getInput(16, codice, false);
	printf("\nInserisci Nome Rivendita: ");
	getInput(45, nome, false);
    printf("\nInserisci indirizzo fatturazione: ");
	getInput(45, fatturazione, false);
	printf("\nInserisci indirizzo spedizione: ");
	getInput(45, spedizione, false);
    printf("\nInserisci indirizzo residenza: ");
	getInput(45, residenza, false);
    printf("Seleziona Contatto\n");
	printf("\t1) email\n");
	printf("\t2) telefono\n");
    printf("\t3) cellulare\n");
	p = multiChoice("Seleziona Posizione", options, 3);
	switch(p) {
		case '1':
			strcpy(tipo, "email");
			break;
		case '2':
			strcpy(tipo, "tel");
			break;
        case '3':
            strcpy(tipo, "cel");
            break;
        default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
	}

	printf("\nInserisci Contatto: ");
	getInput(45, valore, false);
    printf("\nInserisci Nome Referente della Rivendita: ");
	getInput(45, nome_referente, false);
    printf("\nInserisci Cognome Referente della Rivendita: ");
	getInput(45, cognome_referente, false);
    

	if(!setup_prepared_stmt(&prepared_stmt, "call Aggiungi_cliente_rivendita(?,?,?,?,?,?,?,?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = codice;
	param[0].buffer_length = strlen(codice);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[1].buffer = nome;
	param[1].buffer_length = strlen(nome);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[2].buffer = fatturazione;
	param[2].buffer_length = strlen(fatturazione);

	param[3].buffer_type =MYSQL_TYPE_VAR_STRING ;  //IN
	param[3].buffer = spedizione;
	param[3].buffer_length = strlen(spedizione); 

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[4].buffer = residenza;
	param[4].buffer_length = strlen(residenza);

	param[5].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[5].buffer = tipo;
	param[5].buffer_length = strlen(tipo);

	param[6].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[6].buffer = valore;
	param[6].buffer_length = strlen(valore);
    
    param[7].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[7].buffer = nome_referente;
	param[7].buffer_length = strlen(nome_referente);

	param[8].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[8].buffer = cognome_referente;
	param[8].buffer_length = strlen(cognome_referente);
    
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante l'inserimento.");
	} else {
		printf("-------------Cliente aggiunto con successo-------------\n");
	}

	mysql_stmt_close(prepared_stmt);

} 
//3
static void Add_contatti(MYSQL *conn){
    MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];
    
    char cliente[45];
    char tipo[6];
    char options[4] ={'1','2', '3'};
	char p;
    char valore[45];
    
    printf("\nInserisci Codice del Cliente: ");
	getInput(45, cliente, false);
    printf("Seleziona Contatto\n");
	printf("\t1) email\n");
	printf("\t2) telefono\n");
    printf("\t3) cellulare\n");
	p = multiChoice("Seleziona Posizione", options, 3);
	switch(p) {
		case '1':
			strcpy(tipo, "email");
			break;
		case '2':
			strcpy(tipo, "tel");
			break;
        case '3':
            strcpy(tipo, "cel");
            break;
        default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
	}

	printf("\nInserisci Contatto: ");
	getInput(45, valore, false);
    
    if(!setup_prepared_stmt(&prepared_stmt, "call aggiungi_contatto(?,?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = cliente;
	param[0].buffer_length = strlen(cliente);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[1].buffer = tipo;
	param[1].buffer_length = strlen(tipo);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[2].buffer = valore;
	param[2].buffer_length = strlen(valore);

    
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante l'inserimento.");
	} else {
		printf("-------------Contatto aggiunto con successo-------------\n");
	}

	mysql_stmt_close(prepared_stmt);


}
//4
static void scegli_Contatto(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	char cliente[16];
	char valore[45];

	printf("Inserisci Cliente: ");
	getInput(16, cliente, false);
	printf("Inserisci Contatto Preferito:");
	getInput(45, valore, false);

	if(!setup_prepared_stmt(&prepared_stmt, "call scegli_contatto_preferito(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = cliente;
	param[0].buffer_length = strlen(cliente);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[1].buffer = valore;
	param[1].buffer_length = strlen(valore);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante l'aggiornamento del contatto preferito.");
	} else {
		printf("-------------Contatto preferito aggiornato con successo-------------\n");
	}

	mysql_stmt_close(prepared_stmt);

}
//5
static void Add_ordine(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	int ordine;
	char cliente[17];

	printf("\nInserisci num. Ordine: ");
	scanf("%d", &ordine);
    clear();
	printf("Inserisci Cliente: ");
	getInput(17, cliente, false);
    clear();

	if(!setup_prepared_stmt(&prepared_stmt, "call Aggiungi_ordine(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;  //IN
	param[0].buffer = &ordine;
	param[0].buffer_length = sizeof(ordine);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[1].buffer = cliente;
	param[1].buffer_length = strlen(cliente);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante l'inserimento dell'ordine.");
	}else{
        printf("-------------Ordine Registrato-------------\n");
        int i=0;
        int loop;
        printf("Quante piante si vogliono inserire: ");
        scanf("%d", &loop);
        while(loop>i){
        
        Aggiungi_pianta(conn, ordine);

        i++;
        }
    }

}
//6
static void Aggiungi_pianta(MYSQL *conn, int ordine){
    MYSQL_STMT *prepared_stmt;
        MYSQL_BIND param[3];
        char pianta[6];
        int quantita;
  
        printf("\nInsersci codice Pianta: " );
        scanf("%s", pianta);
        clear();
        printf("Inserisci quantità acquistata: ");
        scanf("%d", &quantita);
        clear();
        if(!setup_prepared_stmt(&prepared_stmt, "call agg_piante_ordine(?,?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize insertion statement\n", false);
        }

        memset(param, 0, sizeof(param));

        param[0].buffer_type = MYSQL_TYPE_LONG;  //IN
        param[0].buffer = &ordine;
        param[0].buffer_length = sizeof(ordine);

        param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
        param[1].buffer = pianta;
        param[1].buffer_length = strlen(pianta);

        param[2].buffer_type = MYSQL_TYPE_LONG;  //IN 
        param[2].buffer = &quantita;
        param[2].buffer_length = sizeof(quantita);

    
        if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
            finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
        }

        // Run procedure
        if (mysql_stmt_execute(prepared_stmt) != 0) {
            print_stmt_error (prepared_stmt, "Errore durante l'inserimento.");
        } else {
            printf("-------------Pianta aggiunta con successo-------------\n");
        }

        mysql_stmt_close(prepared_stmt);
    

}
//7
static void Aggiungi_pianta_pacco(MYSQL *conn, int pacco){
    MYSQL_STMT *prepared_stmt;
        MYSQL_BIND param[3];
        char pianta[6];
        
  
        printf("\nInsersci codice Pianta: " );
        scanf("%s", pianta);
        clear();
        if(!setup_prepared_stmt(&prepared_stmt, "call Aggiungi_piante_a_pacco(?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize insertion statement\n", false);
        }

        memset(param, 0, sizeof(param));

        param[0].buffer_type = MYSQL_TYPE_LONG;  //IN
        param[0].buffer = &pacco;
        param[0].buffer_length = sizeof(pacco);

        param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
        param[1].buffer = pianta;
        param[1].buffer_length = strlen(pianta);


    
        if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
            finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
        }

        // Run procedure
        if (mysql_stmt_execute(prepared_stmt) != 0) {
            print_stmt_error (prepared_stmt, "Errore durante l'inserimento.");
        } else {
            printf("-------------Pianta aggiunta con successo-------------\n");
        }

        mysql_stmt_close(prepared_stmt);
}
//8
static void Add_pacco(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	int ordine;
	int pacco;

	printf("\nInserisci num. Ordine: ");
	scanf("%d", &ordine);
    clear();
	printf("Inserisci numero Pacco: ");
	scanf("%d", &pacco);
    clear();

	if(!setup_prepared_stmt(&prepared_stmt, "call Aggiungi_pacco(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;  //IN
	param[0].buffer = &ordine;
	param[0].buffer_length = sizeof(ordine);

	param[1].buffer_type = MYSQL_TYPE_LONG;  //IN
	param[1].buffer = &pacco;
	param[1].buffer_length = sizeof(pacco);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante la creazione del pacco.");
	}else{
        printf("-------------Pacco creato con successo-------------\n");
        int i=0;
        int loop;
        printf("Quante specie di piante si vogliono inserire nel pacco %d: ", pacco);
        scanf("%d", &loop);
        while(loop>i){
        
        Aggiungi_pianta_pacco(conn, pacco);

        i++;
        }
    }

}

//9
static void V_ordine(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	int ordine;

	printf("Inserisci num. Ordine: ");
	scanf("%d", &ordine);

	if(!setup_prepared_stmt(&prepared_stmt, "call Visualizza_ordine(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;  //IN
	param[0].buffer = &ordine;
	param[0].buffer_length = sizeof(ordine);



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante la visualizzazione dell'ordine.");
	} else {
		dump_result_set(conn, prepared_stmt, "-------------Visualizza informazioni ordine-------------");
	}
    mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
} 
//10
static void V_Ordini_Cliente(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	char cliente[16];

	
	printf("\nInserisci codice Cliente: ");
	getInput(16, cliente, false);

	if(!setup_prepared_stmt(&prepared_stmt, "call Visualizza_ordini_cliente(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = cliente;
	param[0].buffer_length = strlen(cliente);



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante la visualizzazione degli ordini del cliente.");
	} else {
		dump_result_set(conn, prepared_stmt, "-------------Visualizza Ordini di un Cliente-------------");
	}
    mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);
} 
//11
static void V_pianta(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	char pianta[6];


	printf("\nInserisci Pianta: ");
	getInput(6, pianta, false);


	if(!setup_prepared_stmt(&prepared_stmt, "call Visualizza_Pianta(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = pianta;
	param[0].buffer_length = strlen(pianta);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante la visualizzazione delle informazioni della pianta.");
	} else {
        dump_result_set(conn, prepared_stmt, "-------------Visualizza Pianta-------------");
    }
    mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);


}
//12
static void V_colorazione(MYSQL *conn){

	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	char pianta[6];


	printf("\nInserisci Pianta: ");
	getInput(6, pianta, false);


	if(!setup_prepared_stmt(&prepared_stmt, "call Visualizzare_Colorazioni(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = pianta;
	param[0].buffer_length = strlen(pianta);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante la visualizzazione dei colori.");
	} else {
		
        dump_result_set(conn, prepared_stmt, "-------------Visualizza Colorazioni della pianta-------------");
    }
    mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);	

}
//13
static void V_prezzi(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];
 

	char pianta[6];


	printf("\nInserisci Pianta:");
	getInput(6, pianta, false);


	if(!setup_prepared_stmt(&prepared_stmt, "call Visualizzare_Storico_Prezzo(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = pianta;
	param[0].buffer_length = strlen(pianta);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante la visualizzazione dello storico dei prezzi della pianta.");
	} else{
        dump_result_set(conn, prepared_stmt, "-------------Storico Prezzo Pianta-------------");
    }
    
    mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

}
//14
static void V_piante_inserire(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	int ordine;

	printf("Inserisci num. Ordine: ");
	scanf("%d", &ordine);

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizzare_piante_inserire_pacco(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;  //IN
	param[0].buffer = &ordine;
	param[0].buffer_length = sizeof(ordine);



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante la visualizzazione delle piante da inserire nel pacco.");
	} else {
        dump_result_set(conn, prepared_stmt, "-------------Piante da Inserire nel Pacco-------------");
	}
    mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

}
//15
static void V_piante_inserite(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	int Pacco;

	printf("Inserisci num. Pacco: ");
	scanf("%d", &Pacco);

	if(!setup_prepared_stmt(&prepared_stmt, "call Visualizzare_piante_Pacco(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;  //IN
	param[0].buffer = &Pacco;
	param[0].buffer_length = sizeof(Pacco);



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante la visualizzazione delle piante inserite nel pacco.");
	} else {
		dump_result_set(conn, prepared_stmt, "-------------Piante inserite nel Pacco-------------");
	}
    mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

}
//16
static void V_costo_ordine(MYSQL *conn){
     
    MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	int ordine;

	printf("Inserisci num. Ordine: ");
	scanf("%d", &ordine);

	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_totale_ordine(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;  //IN
	param[0].buffer = &ordine;
	param[0].buffer_length = sizeof(ordine);



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante la visualizzazione delle costo totale dell'ordine.");
	} else {
		dump_result_set(conn, prepared_stmt, "-------------Costo Totale Ordine-------------");
	}
    mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

}


void run_as_operatore(MYSQL *conn){
    
    char options[17]={'1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g', 'h'};
	char op;
    int ordine, pacco;
    int i, loop;
	
	printf("Passo al ruolo di Operatore...\n");

	if(!parse_config("users/operatore.json", &conf)) {
		fprintf(stderr, "Impossibile caricare info Operatore\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, "root", "root1234", "mydb")) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}

	while(true) {
       
		printf("*** Cosa desidera fare ? ***\n\n");
		printf("1) Aggiungi Cliente Privato\n");
		printf("2) Modifica Cliente Rivendita\n");
        printf("3) Aggiungi Contatti\n");
		printf("4) Scegli Contatto Preferito del Cliente\n");
		printf("5) Aggiungi Ordine\n");
        printf("6) Aggiungere Piante ad Ordine\n");
        printf("7) Aggiungi Pacco\n");
        printf("8) Inserisci Piante in un Pacco\n");
		printf("9) Visualizza Ordine\n");
        printf("a) Visualizza Ordini Cliente\n");
		printf("b) Visualizza Pianta\n");
		printf("c) Visualizza Colorazione delle Pianta\n");
        printf("d) Visualizzare Storico Prezzi di Pianta\n");
		printf("e) Visualizzare Piante da inserire nel Pacco\n");
		printf("f) Visualizza Piante del Pacco\n");
        printf("g) Visualizza Costo Totale Ordine\n");
		printf("h) Esci\n");

        op=multiChoice("select option", options, 17);
        
		switch(op) {
        
			case '1':
				Add_cPrivato(conn);
				break;
			case '2':
				Add_cRivendita(conn);
				break;
            case '3':
				Add_contatti(conn);
				break;
			case '4':
				scegli_Contatto(conn);
				break;
			case '5':
				Add_ordine(conn);
				break;
            case '6':
               
                printf("Inserire numero dell'ordine: ");
                scanf("%d", &ordine);
                i=0;
                printf("Quante piante si vogliono inserire: ");
                scanf("%d", &loop);
                while(loop>i){
        
                    Aggiungi_pianta(conn, ordine);

                i++;
                }
               
                break;
            case '7':
                Add_pacco(conn);
				break;
            case '8':
                printf("Inserire numero del Pacco: ");
                scanf("%d", &pacco);
                i=0;
                int loop;
                printf("Quante specie di piante si vogliono inserire nel pacco %d: ", pacco);
                scanf("%d", &loop);
                while(loop>i){
                    Aggiungi_pianta_pacco(conn, pacco);
                    i++;
                }
                break;
                
			case '9':
				V_ordine(conn);
				break;
            case 'a':
				V_Ordini_Cliente(conn);
				break;
			case 'b':
				V_pianta(conn);
				break;
			case 'c':
				V_colorazione(conn);
				break;
            case 'd':
				V_prezzi(conn);
				break;
			case 'e':
				V_piante_inserire(conn);
				break;
			case 'f':
				V_piante_inserite(conn);
				break;
            case 'g':
                V_costo_ordine(conn);
                break;
			case 'h':
				return;
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

	}
}
