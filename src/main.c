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

// Menus
void launchMainMenu();
void printMainMenu(bool error, char errorMessage[256]);

void launchCentralineMenu();
void printCentralineMenu(bool error, char errorMessage[256]);

void launchRefsMenu();

// Core

// Routine
int main(void) {
    //
    // IN FUTURO: Carica da un file le centraline
    //

    // Avvia il menu principale, nonché il programma vero e proprio
    launchMainMenu();

    // Saluta e chiedi di premere un tasto per chiudere
    system("cls");
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
    printf("2. Riferimenti\n");

    printf("\nQ. Esci\n");

    // Eventuali errori
    if (error) {
        printf("\n[!] %s\n", errorMessage);
    }
}

// Menu visualizzazione centraline
void launchCentralineMenu() {

}

void printCentralineMenu(bool error, char errorMessage[256]) {

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