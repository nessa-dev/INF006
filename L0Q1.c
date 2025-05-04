#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TAM 1000

typedef struct {
    int x;
    int y;
    double distanceToOrigin;
} point;

double distance(point a, point b);
void ordenarPontos(point Pontos[], int qntPontos);

int main() {
    system("cls||clear");

    FILE *entrada, *saida;
    entrada = fopen("L0Q1.in", "r");
    saida = fopen("L0Q1.out", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Arquivos inexistentes.\n");
        return 1;
    }

    char linhaEntrada[TAM];
    char separador[] = "(,) ";
    char *parte;
    point origin = {0, 0, 0};

    while (fgets(linhaEntrada, TAM, entrada) != NULL) {
        // Remove a palavra "points " do início
        if (strncmp(linhaEntrada, "points ", 7) == 0) {
            memmove(linhaEntrada, linhaEntrada + 7, strlen(linhaEntrada) - 6);
        }

        point Pontos[400];
        int index = 0;
        int cont = 0;
        double soma = 0, shortcut = 0;

        fprintf(saida, "points");

        parte = strtok(linhaEntrada, separador);
        while (parte != NULL) {
            if (cont % 2 == 0) {
                Pontos[index].x = atoi(parte);
            } else {
                Pontos[index].y = atoi(parte);
                Pontos[index].distanceToOrigin = distance(Pontos[index], origin);

                if (index > 0) {
                    soma += distance(Pontos[index], Pontos[index - 1]);
                    shortcut = distance(Pontos[0], Pontos[index]);
                }

                index++;
            }
            cont++;
            parte = strtok(NULL, separador);
        }

        ordenarPontos(Pontos, index);

        for (int i = 0; i < index; i++) {
            fprintf(saida, " (%d,%d)", Pontos[i].x, Pontos[i].y);
        }

        fprintf(saida, " distance %.2f", soma);
        fprintf(saida, " shortcut %.2f\n", shortcut);
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}

double distance(point a, point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void ordenarPontos(point Pontos[], int index) {
    point aux;
    int troca = 1;
    for (int j = 0; troca; j++) {
        troca = 0;
        for (int i = 1; i < index - j; i++) {
            if (Pontos[i - 1].distanceToOrigin > Pontos[i].distanceToOrigin) {
                aux = Pontos[i];
                Pontos[i] = Pontos[i - 1];
                Pontos[i - 1] = aux;
                troca = 1;
            }
        }
    }
}
