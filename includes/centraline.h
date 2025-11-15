//
// Created by loren on 13/11/2025.
//

#ifndef CENTRALINAIO_CENTRALINE_H
#define CENTRALINAIO_CENTRALINE_H

#include "liste.h"

typedef struct centralina_s {
    char nome[17];
    char coordinate[255];
    ListNode* misureGiornaliere;
} Centralina;

typedef struct misura_s {
    char data[11]; // Formato: 00/00/0000 con terminatore riga
    double temperatura;
    double umidita;
    double vVento;
} MisuraGiornaliera;

// Funzioni
Centralina* createCentralina(char nome[17], char coordinate[255]);
MisuraGiornaliera* createMisura(char data[11], double temperatura, double umidita, double vVento);

#endif //CENTRALINAIO_CENTRALINE_H