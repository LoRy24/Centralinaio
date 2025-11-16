//
// Created by loren on 13/11/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "../includes/liste.h"
#include "../includes/centraline.h"
#include "../includes/impostazioni.h"
#include "../includes/utils.h"

// Area dati del programma
int totaleCentraline = 0;
ListNode* centraline = nullptr;

// Testate funzioni

/* Menus */

// Menu principale
void launchMainMenu();
void printMainMenu(bool error, char errorMessage[256]);

// Visualizzazione centraline
void launchCentralineMenu();
void printCentralineMenu(bool error, char errorMessage[256]);

// Creazione centralina
void launchCentralinaCreationMenu();

// Gestione centralina
void launchCentralinaControllingMenu(int idCentralina);
void printCentralinaControllingMenu(Centralina* centralina, bool error, char errorMessage[256]);
void printListaMisure(Centralina* centralina);

// Gestione & Selezione misura
void launchSelezioneMisura(Centralina* centralina);
void printSelezioneMisuraMenu(Centralina* centralina, bool error, char errorMessage[256]);

void launchGestioneMisura(Centralina* centralina, int idMisura);
void printGestioneMisuraMenu(Centralina* centralina, MisuraGiornaliera* misura, bool error, char errorMessage[256]);

void launchAggiornaMisura(MisuraGiornaliera* misura);

// Creazione misura
void launchCreazioneMisura(Centralina* centralina);

// Riferimenti
void launchRefsMenu();

// Core
void deleteCentralina(int id);

// Routine
int main(void) {
    //
    // IN FUTURO: Carica da un file le centraline
    //

    // Avvia il menu principale, nonché il programma vero e proprio
    launchMainMenu();

    // Pulisci
    system("cls");

    // Scrivi l'intestazione
    printProgramHeader();

    // Messaggio
    printf("Grazie per aver scelto Centralinaio.\nPremi un tasto per uscire!\n");
    _getch();

    // Ok
    return 0;
}

// Funzioni programma

// Menu principale
void launchMainMenu() {
    // Routine del programma (I/O)
    int selection;
    bool error = false;
    char errorMessage[256];
    do {
        // Scrivi il menu principale
        printMainMenu(error, errorMessage);
        error = false;
        errorMessage[0] = '\0';

        // Richiedi la selezione
        selection = _getch();

        // In base alla selezione
        switch (selection) {
            case '1': {
                launchCentralineMenu();
                break;
            }

            case '2': {
                launchCentralinaCreationMenu();
                break;
            }

            case '3': {
                break;
            }

            case '4': {
                launchRefsMenu();
                break;
            }

            case 'q': {
                break;
            }

            default: {
                error = true;
                strcpy(errorMessage, "Selezione non valida! Riprova");
                break;
            }
        }
    } while (selection != 'q');
}

void printMainMenu(const bool error, char errorMessage[256]) {
    // Pulisci lo schermo
    system("cls");

    // Scrivi l'intestazione
    printProgramHeader();

    // Dettagli
    printf("Versione v1.0.0 made with <3 by Lorenzo Rocca\n\n");

    // Opzioni
    printf("Seleziona una delle seguenti opzioni:\n\n");

    printf("1. Visualizza centraline\n");
    printf("2. Aggiungi centralina\n");
    printf("3. Statistiche\n");
    printf("4. Riferimenti\n");

    printf("\nQ. Esci\n");

    // Eventuali errori
    if (error) {
        printf("\n[!] %s\n", errorMessage);
    }
}

// Menu visualizzazione centraline
void launchCentralineMenu() {
    if (totaleCentraline == 0) {
        printCentralineMenu(false, "");
        _getch();
    }
    else {
        int selezione;
        bool error = false;
        char errorMessage[256];
        do {
            // Scrivi il menu
            printCentralineMenu(error, errorMessage);
            error = false;
            strcpy(errorMessage, "");

            // Ottieni il valore
            const int res = scanf("%d", &selezione); // NOLINT(*-err34-c)
            if (!res) {
                fflush(stdin);
                error = true;
                strcpy(errorMessage, "Valore non valido! Riprova");
                continue;
            }

            // Se la selezione non è -1
            if (selezione != 0) {
                // Vedi se la selezione è valida, altrimenti richiedi nuovamente
                if (selezione < 0 || selezione > totaleCentraline) {
                    error = true;
                    strcpy(errorMessage, "Selezione non valida! Riprova");
                    continue;
                }

                // Avvia il menu per gestirla
                launchCentralinaControllingMenu(selezione - 1);

                // Se, per esempio, viene aperta l'unica centralina e poi eliminata, bisogna tornare al menù principale
                if (totaleCentraline == 0) {
                    break;
                }
            }
        } while (selezione != 0);
    }
}

void printCentralineMenu(const bool error, char errorMessage[256]) {
    // Pulisci lo schermo
    system("cls");

    // Scrivi l'intestazione
    printProgramHeader();

    // Se sono presenti centraline, mostrale
    if (totaleCentraline == 0) {
        printf("Al momento non sono presenti centraline. Torna indietro per crearne una [PREMI UN TASTO]\n");
    }
    else {
        // Dettagli
        printf("Lista delle centraline:\n\n");

        // Lista delle centraline
        printf("ID       Nome             Coordinate                                             Misurazioni     \n");

        // Scorri ciascuna centralina per scriverne i dettagli a schermo
        const ListNode* nodoCentralina = centraline; // Const per maggior sicurezza, così non posso modificare i dati.
        int i = 1;
        while (nodoCentralina != nullptr) {
            // Estraine il puntatore alla centralina
            Centralina* centralina = nodoCentralina->value;

            // Scrivilo
            printf("%8d %16s %54s %16d\n", i, centralina->nome, centralina->coordinate, centralina->totMisurazioni);

            // Avanza
            nodoCentralina = nodoCentralina->next;
            ++i;
        }

        // Scrivi un errore se c'è
        if (error) {
            printf("\n[!] %s\n", errorMessage);
        }

        // Scrivi il prompt per selezionare la centralina
        printf("\nInserisci il valore della centralina [1-%d, 0 per tornare indietro] >> ", totaleCentraline);
    }
}

// Menu specifico per centralina selezionata
void launchCentralinaControllingMenu(const int idCentralina) {
    // Seleziona la centralina
    Centralina* centralina = get(idCentralina, centraline)->value;

    // Avvia il ciclo per la selezione
    int selezione;
    bool error = false;
    char errorMessage[256];
    do {
        // Scrivi il menu
        printCentralinaControllingMenu(centralina, error, errorMessage);
        error = false;
        strcpy(errorMessage, "");

        // Richiedi l'operazione
        selezione = _getch();

        // In base alla selezione
        switch (selezione) {
            case '1': {
                // Se non ci sono centraline, esci
                if (centralina->totMisurazioni == 0) {
                    error = true;
                    strcpy(errorMessage, "Non sono presenti misurazioni! Creane una per proseguire.");
                    break;
                }

                launchSelezioneMisura(centralina);
                break;
            }

            case '2': {
                launchCreazioneMisura(centralina);
                break;
            }

            case '3': {
                // Pulisci lo schermo
                system("cls");

                // Scrivi l'intestazione
                printProgramHeader();

                // Messaggio di conferma per l'eliminazione
                printf("Sei sicuro di voler eliminare questa centralina?\nPremi Y per confermare, qualsiasi altro tasto per tornare indietro.\n");
                const int conferma = _getch();

                // Vedi per la conferma
                if (conferma == 'y') {
                    // Elimina la centralina ed esci
                    deleteCentralina(idCentralina);
                    selezione = 'q'; // Per uscire
                }

                // Esci
                break;
            }

            default: {
                error = true;
                strcpy(errorMessage, "Selezione non valida! Riprova");
                break;
            }
        }
    } while (selezione != 'q');
}

void printCentralinaControllingMenu(Centralina* centralina, const bool error, char errorMessage[256]) {
    // Pulisci lo schermo
    system("cls");

    // Scrivi l'intestazione
    printProgramHeader();

    // Scrivi le info
    printf("Stai gestendo la centralina '%s'\n", centralina->nome);
    printf("Coordinate: %s\n", centralina->coordinate);
    printf("Totale misurazioni effettuate: %d\n\n", centralina->totMisurazioni);

    // Operazioni eseguibili
    printf("Scegli una delle seguenti operazioni:\n\n");
    printf("1. Gestisci misurazioni\n");
    printf("2. Aggiungi misure\n");
    printf("3. Elimina centralina\n\n");

    printf("Q. Torna indietro\n");

    // Eventuali errori
    if (error) {
        printf("\n[!] %s\n", errorMessage);
    }
}

void printListaMisure(Centralina* centralina) {
    // Messaggio e intestazione
    printf("Misurazioni raccolte in una tabella:\n\n");
    printf("ID       Data           Temperatura (C)  Umidita' (%%)     Vel. Vento (Km/h)  \n"); // 8 14 16 16 18

    // Per ogni misura scrivine i dati
    const ListNode* nodoMisura = centralina->misureGiornaliere;
    int i = 1;
    while (nodoMisura != nullptr) {
        MisuraGiornaliera* misura = nodoMisura->value;
        printf("%8d %14s %16.2f %14.2f %% %18.2f\n", i, misura->data, misura->temperatura, misura->umidita, misura->vVento);
        nodoMisura = nodoMisura->next;
        ++i;
    }

    // Spazio
    printf("\n");
}

// Selezione misure

void launchSelezioneMisura(Centralina* centralina) {
    // Richiedi la misura da gestire
    int selezione;
    bool error = false;
    char errorMessage[256];
    do {
        // Scrivi il menu
        printSelezioneMisuraMenu(centralina, error, errorMessage);
        error = false;
        strcpy(errorMessage, "");

        // Ottieni il valore
        const int res = scanf("%d", &selezione); // NOLINT(*-err34-c)
        if (!res) {
            fflush(stdin);
            error = true;
            strcpy(errorMessage, "Valore non valido! Riprova");
            continue;
        }

        // Se la selezione non è -1
        if (selezione != 0) {
            // Vedi se la selezione è valida, altrimenti richiedi nuovamente
            if (selezione < 0 || selezione > centralina->totMisurazioni) {
                error = true;
                strcpy(errorMessage, "Selezione non valida! Riprova");
                continue;
            }

            // Gestisci la misura
            launchGestioneMisura(centralina, selezione - 1);

            // Se non ci sono più misure, torna endre
            if (centralina->totMisurazioni == 0) {
                break;
            }
        }
    } while (selezione != 0);
}

void printSelezioneMisuraMenu(Centralina *centralina, bool error, char errorMessage[256]) {
    // Scrivi il form
    system("cls");
    printProgramHeader();
    printListaMisure(centralina);

    // Se c'è un errore
    if (error) {
        printf("\n[!] %s\n", errorMessage);
    }

    // Richiesta per la misura
    printf("Inserisci ID della misura da selezionare [1-%d, 0 per uscire] >> ", centralina->totMisurazioni);
}

// Gestione misure

void launchGestioneMisura(Centralina* centralina, int idMisura) {
    // Ottieni la misura
    MisuraGiornaliera* misura = get(idMisura, centralina->misureGiornaliere)->value;

    // Input e output
    int selezione;
    bool error = false;
    char errorMessage[256];
    do {
        // Scrivi il menu
        printGestioneMisuraMenu(centralina, misura, error, errorMessage);
        error = false;
        strcpy(errorMessage, "");

        // Ottieni la selezione
        selezione = _getch();

        // In base alla selezione
        switch (selezione) {
            case '1': { // Modifica
                launchAggiornaMisura(misura);
                break;
            }

            case '2': { // Elimina
                // Pulisci lo schermo
                system("cls");

                // Scrivi l'intestazione
                printProgramHeader();

                // Messaggio di conferma per l'eliminazione
                printf("Sei sicuro di voler eliminare questa misura?\nPremi Y per confermare, qualsiasi altro tasto per tornare indietro.\n");

                const int conferma = _getch();

                // Vedi per la conferma
                if (conferma == 'y') {
                    // Elimina la centralina ed esci
                    remove_from_list(&centralina->misureGiornaliere, idMisura);
                    centralina->totMisurazioni--;
                    selezione = 'q'; // Per uscire
                }

                // Continua
                break;
            }

            case 'q': {
                break;
            }

            default: {
                error = true;
                strcpy(errorMessage, "Selezione non valida! Riprova");
                break;
            }
        }
    } while (selezione != 'q');
}

void printGestioneMisuraMenu(Centralina* centralina, MisuraGiornaliera* misura, bool error, char errorMessage[256]) {
    // Scrivi il form
    system("cls");
    printProgramHeader();

    // Scrivi l'intestazione
    printf("Gestione della misura in data %s per la centralina '%s'\n\n", misura->data, centralina->nome);

    // Misure
    printf("Valori della misurazione:\n");
    printf("Temperatura: %f gradi C\n", misura->temperatura);
    printf("Umidita': %f %%\n", misura->umidita);
    printf("Velocita' del vento: %f Km/h\n\n", misura->vVento);

    // Operazioni
    printf("Scegli una delle seguenti operazioni:\n\n");
    printf("1. Modifica valori\n");
    printf("2. Elimina misurazione\n\n");

    printf("Q. Torna indietro\n");

    // Se c'è un errore
    if (error) {
        printf("\n[!] %s\n", errorMessage);
    }
}

void launchAggiornaMisura(MisuraGiornaliera* misura) {
    // Pulisci lo schermo
    system("cls");

    // Scrivi l'intestazione
    printProgramHeader();

    // Chiedi la data
    printf("Si desidera modificare la data inserita? Premi Y per modificare, qualunque altro per saltare\n");
    int scelta = _getch();
    if (scelta == 'y') {
        char data[11];
        printf("Inserisci la nuova data della misurazione (dd/mm/yyyy) >> ");
        scanf("%10s", data);
        strcpy(misura->data, data);
    }
    else {
        printf("Saltato.\n");
    }

    // Chiedi la temperatura
    printf("\nSi desidera modificare la temperatura rilevata? Premi Y per modificare, qualunque altro per saltare\n");
    scelta = _getch();
    if (scelta == 'y') {
        double temperatura = 0.0;
        printf("Inserisci la nuova temperatura rilevata >> ");
        while (!scanf("%lf", &temperatura)) printf("Valore invalido! Riprova >> "); // NOLINT(*-err34-c)
        misura->temperatura = temperatura;
    }
    else {
        printf("Saltato.\n");
    }

    // Chiedi l'umidità
    printf("\nSi desidera modificare l'umidita' rilevata? Premi Y per modificare, qualunque altro per saltare\n");
    scelta = _getch();
    if (scelta == 'y') {
        double umidita = 0.0;
        printf("Inserisci la nuova umidita' rilevata >> ");
        while (!scanf("%lf", &umidita) || umidita < 0 || umidita > 100) printf("Valore invalido! Riprova >> "); // NOLINT(*-err34-c)
        misura->umidita = umidita;
    }
    else {
        printf("Saltato.\n");
    }

    // Chiedi la velocità del vento
    printf("\nSi desidera modificare la velocita' del vento rilevata? Premi Y per modificare, qualunque altro per saltare\n");
    scelta = _getch();
    if (scelta == 'y') {
        double vVento = 0.0;
        printf("Inserisci la nuova velocita' del vento rilevata >> ");
        while (!scanf("%lf", &vVento)) printf("Valore invalido! Riprova >> "); // NOLINT(*-err34-c)
        misura->vVento = vVento;
    }
    else {
        printf("Saltato.\n");
    }

    // Notifica l'aggiornamento
    printf("\nValori aggiornati! Premi un tasto per continuare\n");
    _getch();
}

// Creazione misura

void launchCreazioneMisura(Centralina* centralina) {
    // Pulisci lo schermo
    system("cls");

    // Scrivi l'intestazione
    printProgramHeader();

    // Chiedi la data
    char data[11];
    printf("Inserisci la data della misurazione (dd/mm/yyyy) >> ");
    scanf("%10s", data);

    // Chiedi la temperatura
    double temperatura = 0.0;
    printf("Inserisci la temperatura rilevata >> ");
    while (!scanf("%lf", &temperatura)) printf("Valore invalido! Riprova >> "); // NOLINT(*-err34-c)

    // Chiedi l'umidità
    double umidita = 0.0;
    printf("Inserisci l'umidita' rilevata >> ");
    while (!scanf("%lf", &umidita) || umidita < 0 || umidita > 100) printf("Valore invalido! Riprova >> "); // NOLINT(*-err34-c)

    // Chiedi la velocità del vento
    double vVento = 0.0;
    printf("Inserisci la velocita' del vento rilevata >> ");
    while (!scanf("%lf", &vVento)) printf("Valore invalido! Riprova >> "); // NOLINT(*-err34-c)

    // Crea la misura
    MisuraGiornaliera* misura = createMisura(data, temperatura, umidita, vVento);
    ListNode* nodoMisura = create_list(misura);

    // Inseriscila nella centralina
    if (centralina->totMisurazioni == 0) {
        centralina->misureGiornaliere = nodoMisura;
        centralina->totMisurazioni++;
    }
    else {
        insert_bottom(centralina->misureGiornaliere, nodoMisura);
        centralina->totMisurazioni++;
    }
}

// Creazione centralina
void launchCentralinaCreationMenu() {
    // Pulisci lo schermo
    system("cls");

    // Scrivi l'intestazione
    printProgramHeader();

    // Dettagli
    printf("Form per l'aggiunta della centralina N.%d\n\n", totaleCentraline + 1);

    /* RICHIESTE */

    // Nome
    char nome[17];
    printf("Inserisci il nome della centralina (NO SPAZI) >> ");
    scanf("%16s", nome);
    fflush(stdin);

    // Coordinate
    char coordinate[256];
    printf("Inserisci le coordinate della centralina (NO SPAZI) >> ");
    scanf("%255s", coordinate);
    fflush(stdin);

    // Crea la centralina
    Centralina* centralina = createCentralina(nome, coordinate);
    ListNode* nodoCentralina = create_list(centralina);

    // Se non ci sono elementi, impostalo come nodo di partenza
    if (totaleCentraline == 0) {
        centraline = nodoCentralina;
    }
    else {
        insert_bottom(centraline, nodoCentralina);
    }

    // Incrementa il contatore
    totaleCentraline++;

    // Comunica la creazione e richiedi per tornare indietro
    printf("\nCentralina creata! Premi un tasto per tornare indietro");
    _getch();
}

// Riferimenti
void launchRefsMenu() {
    // Pulisci lo schermo
    system("cls");

    // Scrivi l'intestazione
    printProgramHeader();

    // Scrivi i dettagli
    printf("Centralinaio v1.0.0 e' un software scritto da Lorenzo Rocca per un compito scolastico. Esso simula\n");
    printf("in maniera quasi completa un sistema di gestione di un complesso di centraline per effettuare\n");
    printf("misurazioni delle condizioni meteorologiche.\n\n");

    printf("Per maggiori dettagli sul codice sorgente visita:\n");
    printf("https://github.com/LoRy24/Centralinaio\n");

    // Info per uscire
    printf("\nPremi qualsiasi tasto per tornare indietro\n");
    _getch();
}

/* Gestione */

void deleteCentralina(const int id) {
    Centralina* centralina = get(id, centraline)->value;
    clear_list(&centralina->misureGiornaliere);
    remove_from_list(&centraline, id);
    totaleCentraline--;
}
