//
// Created by loren on 15/11/2025.
//

#include <stdlib.h>
#include <string.h>

#include "../includes/centraline.h"

Centralina* createCentralina(char nome[17], char coordinate[255]) {
    Centralina* centralina = malloc(sizeof(Centralina));
    strcpy(centralina->nome, nome);
    strcpy(centralina->coordinate, coordinate);
    return centralina;
}

MisuraGiornaliera* createMisura(char data[11], const double temperatura, const double umidita, const double vVento) {
    MisuraGiornaliera* misura = malloc(sizeof(MisuraGiornaliera));
    strcpy(misura->data, data);
    misura->temperatura = temperatura;
    misura->umidita = umidita;
    misura->vVento = vVento;
    return misura;
}