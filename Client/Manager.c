#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#include "defines.h"

void clear_stdin(){
    int a;
    while((a = getchar()) != '\n' && a != EOF){}
}

static void Aggiungi_Specie_di_Pianta(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[8];

	char Pianta[6];
	char Nome_comune[45];
	char Nome_latino[45];
	char posizione[8];
	char options[4] ={'1','2'};
	char p;
	signed char esotica;
	int quantita;
	double Costo;
	char Fornitore[16];


	printf("\nCodice Pianta: ");
	getInput(6, Pianta, false);
	printf("Nome Comune: ");
	getInput(45, Nome_comune, false);
	printf("Nome Latino: ");
	getInput(45, Nome_latino, false);
	printf("Posizione Pianta\n");
	printf("\t1) interno\n");
	printf("\t2) esterno\n");
	p = multiChoice("Seleziona Posizione", options, 2);
	switch(p) {
		case '1':
			strcpy(posizione, "interno");
			break;
		case '2':
			strcpy(posizione, "esterno");
			break;
	
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
	}

	printf("La Pianta è esotica?\n");
	p = multiChoice("1)No \t2)Si", options, 2);
	switch(p) {
		case '1':
			esotica=0;
			break;
		case '2':
			esotica=1;
			break;
	
		default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
	}
    
	printf("Quantità disponibile: ");
	scanf("%d", &quantita);
    clear_stdin();
	printf("Costo Pianta: ");
	scanf("%lf", &Costo);
    clear_stdin();
	printf("Indicare il codice del Fornitore: ");
	getInput(17, Fornitore, false);


	if(!setup_prepared_stmt(&prepared_stmt, "call aggiungere_specie_pianta(?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile inzializzare lo statement\n", false);
	}
    

        // Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = Pianta;
	param[0].buffer_length = strlen(Pianta);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[1].buffer = Nome_comune;
	param[1].buffer_length = strlen(Nome_comune);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[2].buffer = Nome_latino;
	param[2].buffer_length = strlen(Nome_latino);

	param[3].buffer_type =MYSQL_TYPE_VAR_STRING ;  //IN
	param[3].buffer = posizione;
	param[3].buffer_length = strlen(posizione); 

	param[4].buffer_type = MYSQL_TYPE_TINY;  //IN
	param[4].buffer = &esotica;
	param[4].buffer_length = sizeof(esotica);

	param[5].buffer_type = MYSQL_TYPE_LONG;  //IN
	param[5].buffer = &quantita;
	param[5].buffer_length = sizeof(quantita);

	param[6].buffer_type = MYSQL_TYPE_DOUBLE;  //IN
	param[6].buffer = &Costo;
	param[6].buffer_length = sizeof(Costo);

	param[7].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[7].buffer = Fornitore;
	param[7].buffer_length = strlen(Fornitore);


	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for user insertion\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "errore durante l'inseriemento");
	} else {
		printf("Pianta inserita correttamente\n");
	}

	mysql_stmt_close(prepared_stmt);

}

static void Aggiungi_Colore (MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	char colorazione[20];
	char pianta[7];

	printf("\nInserisci Pianta: ");
	getInput(6, pianta, false);
	printf("Inserisci colorazione: ");
	getInput(20, colorazione, false);

	if(!setup_prepared_stmt(&prepared_stmt, "call Aggiungi_colore_pianta(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = colorazione;
	param[0].buffer_length = strlen(colorazione);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[1].buffer = pianta;
	param[1].buffer_length = strlen(pianta);



	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante l'inserimento colorazione.");
	} else {
		printf("Colorazione aggiunta con successo.\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void Modifica_Prezzo (MYSQL *conn){

	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	char pianta[6];
	double Prezzo;

	printf("\nInserisci Pianta: ");
	getInput(6, pianta, false);
	printf("Inserisci Prezzo nuovo: ");
	scanf("%lf", &Prezzo);
    clear_stdin();
    
	if(!setup_prepared_stmt(&prepared_stmt, "call Modificare_prezzo_pianta(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = pianta;
	param[0].buffer_length = strlen(pianta);

	param[1].buffer_type = MYSQL_TYPE_DOUBLE;  //IN
	param[1].buffer = &Prezzo;
	param[1].buffer_length = sizeof(Prezzo);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante l'aggiornamento del prezzo.");
	} else {
		printf("Prezzo modificato con successo.\n");
	}

	mysql_stmt_close(prepared_stmt);


}

static void crea_utente (MYSQL *conn){
    MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[3];

	char username[45];
	char password[32];
    char tipo[10];
    char options[4] ={'1','2'};
	char p;

	printf("\nInserisci Username: ");
	getInput(45, username, false);
	printf("Inserisci Password: ");
	getInput(32, password, false);
    printf("Seleziona Ruolo: \n");
    printf("\t1) Manager\n");
	printf("\t2) Operatore\n");
	p = multiChoice("Seleziona Ruolo:", options, 2);
	switch(p) {
		case '1':
			strcpy(tipo, "Manager");
			break;
		case '2':
			strcpy(tipo, "operatore");
			break;
        default:
			fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
			abort();
	}

	if(!setup_prepared_stmt(&prepared_stmt, "call crea_utente(?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize student insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = username;
	param[0].buffer_length = strlen(username);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[1].buffer = password;
	param[1].buffer_length = strlen(password);
    
    param[2].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[2].buffer =tipo;
	param[2].buffer_length = strlen(tipo);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante la creazione dell'utente.");
	} else {
		printf("Utente creato con successo.\n");
	}

	mysql_stmt_close(prepared_stmt);

}

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

static void V_Fornitori(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[1];

	char pianta[6];


	printf("\nInserisci Pianta: ");
	getInput(6, pianta, false);


	if(!setup_prepared_stmt(&prepared_stmt, "call visualizza_fornitori_pianta(?)", conn)) {
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
		print_stmt_error (prepared_stmt, "Errore durante la visualizzazione dei Fornitori.");
	} else {
		dump_result_set(conn, prepared_stmt, "-------------Visualizza Fornitori Pianta-------------");
	}
    mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

}

static void Aggiorna_Giacenza(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	char pianta[6];
	int giacenza;

	printf("\nInserisci Pianta: ");
	getInput(6, pianta, false);
	printf("Inserisci la quantità da aggiungere: ");
	scanf("%d", &giacenza);

	if(!setup_prepared_stmt(&prepared_stmt, "call Aggiornare_Giacenze(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[0].buffer = pianta;
	param[0].buffer_length = strlen(pianta);

	param[1].buffer_type = MYSQL_TYPE_LONG;  //IN
	param[1].buffer = &giacenza;
	param[1].buffer_length = sizeof(giacenza);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante l'aggiornamento della Giacenza.");
	} else {
		printf("-------------Giacenza aggiornata-------------.\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void Aggiungi_fornitore_specie(MYSQL *conn){
    MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	char pianta[6];
	int Fornitore;

	printf("\nInserisci Pianta: ");
	getInput(6, pianta, false);
	printf("Inserisci codice Fornitore: ");
    scanf("%d", &Fornitore);
    clear_stdin();
    
	if(!setup_prepared_stmt(&prepared_stmt, "call aggiungi_fornitore_specie(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize insertion statement\n", false);
	}

	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_LONG;  //IN
	param[0].buffer = &Fornitore;
	param[0].buffer_length = sizeof(Fornitore);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;  //IN
	param[1].buffer = pianta;
	param[1].buffer_length = strlen(pianta);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Impossibile associare i parametri.\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "Errore durante l'aggiunta del fornitore.");
	} else {
		printf("-------------Fornitore aggiunto alla specie-------------.\n");
	}
   
	mysql_stmt_close(prepared_stmt);
}

void run_as_manager(MYSQL *conn){
	char options[12] = {'1','2','3','4','5','6','7','8','9','a','b','e'};
	char op;
	
	printf("------------>Passo al ruolo di Manager...\n");

	if(!parse_config("users/Manager.json", &conf)) {
		fprintf(stderr, "Impossibile caricare info Manager\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, "root", "root1234", "mydb")) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}

	while(true) {
	
		printf("----- Cosa desidera fare ? -----\n\n");
		printf("1) Aggiungi Specie di Pianta\n");
		printf("2) Aggiungi Colore a Pianta\n");
		printf("3) Modifica Prezzo di una Pianta\n");
        printf("4) Aggiungi un nuovo utente\n");
        printf("5) Aggiorna Giacenze Magazzino\n");
		printf("6) Visualizza storico dei prezzi\n");
		printf("7) Visualizza fornitori di una specie\n");
        printf("8) Visualizza Specie\n");
        printf("9) Visualizza Colorazioni di una Specie\n");
        printf("a) Visualizza Totale dell'ordine\n");
        printf("b) Aggiungi Fornitore a Pianta\n");
		printf("e) Esci\n\n");

		op = multiChoice("Seleziona un opzione", options, 12);

		switch(op) {

			case '1':
				Aggiungi_Specie_di_Pianta(conn);
				break;
			case '2':
				Aggiungi_Colore(conn);
				break;
			case '3':
				Modifica_Prezzo(conn);
				break;
            case '4':
                crea_utente(conn);
                break;
			case '5':
                Aggiorna_Giacenza(conn);
				break;
            case '6':
				V_prezzi(conn);
				break;
			case '7':
				V_Fornitori(conn);
				break;
			case '8':
				V_pianta(conn);
				break;
            case '9':
                V_colorazione(conn);
                break;
			case 'a':
				V_costo_ordine(conn);
                break;
            case 'b':
                Aggiungi_fornitore_specie(conn);
                break;
            case'e':
                return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}


	}
}

