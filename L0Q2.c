//INTEGRANTES: JOÃO EVERTON DE ALMEIDA DOS SANTOS e VANESSA DA CONCEIÇÃO DOS SANTOS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define TAM_MAX 512
#define QTD_MAX 100

typedef struct {
    float x, y;
} Ponto;

int main() {
    char linha[TAM_MAX];

    while (fgets(linha, sizeof(linha), stdin)) {
        char palavras[QTD_MAX][50];
        int inteiros[QTD_MAX], qt_inteiros = 0;
        float reais[QTD_MAX];
        int qt_reais = 0;
        int qt_palavras = 0;
        Ponto pontos[QTD_MAX];
        int qt_pontos = 0;

        char *token = strtok(linha, " \n");

        while (token) {
            float x, y;
            if (token[0] == '(' && token[strlen(token)-1] == ')' && sscanf(token, "(%f,%f)", &x, &y) == 2) {
                pontos[qt_pontos].x = x;
                pontos[qt_pontos].y = y;
                qt_pontos++;
            } 
            else{
                int i = 0, tem_ponto = 0, eh_num = 1;

                if (token[0] == '-' || token[0] == '+') i++;
                for (; token[i]; i++) {
                    if (token[i] == '.') {
                        if (tem_ponto) {
                            eh_num = 0;
                            break;
                        }
                        tem_ponto = 1; 
                    }
                    else if (!isdigit(token[i])) {
                        eh_num = 0;
                        break;
                    }
             }

                if (eh_num) {
                    if (tem_ponto){
                        reais[qt_reais++] = atof(token);
                    } else { 
                        inteiros[qt_inteiros++] = atoi(token);
                    }
                } else{
                    strcpy(palavras[qt_palavras++], token);
                }
            }
            token = strtok(NULL, " \n");
        }

        for (int i = 0; i < qt_inteiros - 1; i++){
            for (int j = i + 1; j < qt_inteiros; j++){
                if (inteiros[i] > inteiros[j]) {
                    int aux = inteiros[i]; inteiros[i] = inteiros[j]; inteiros[j] = aux;
                }
            }
}
        for (int i = 0; i < qt_reais - 1; i++){
            for (int j = i + 1; j < qt_reais; j++){
                if (reais[i] > reais[j]) {
                    float aux = reais[i]; reais[i] = reais[j]; reais[j] = aux;
                }
            }
        }

        for (int i = 0; i < qt_palavras - 1; i++){
            for (int j = i + 1; j < qt_palavras; j++){
                if (strcmp(palavras[i], palavras[j]) > 0) {
                    char aux[50];
                    strcpy(aux, palavras[i]);
                    strcpy(palavras[i], palavras[j]);
                    strcpy(palavras[j], aux);
                }
            }
        }

        for (int i = 0; i < qt_pontos - 1; i++){
            for (int j = i + 1; j < qt_pontos; j++) {
                float d1 = sqrt(pontos[i].x * pontos[i].x + pontos[i].y * pontos[i].y);
                float d2 = sqrt(pontos[j].x * pontos[j].x + pontos[j].y * pontos[j].y);
                if (d1 > d2) {
                    Ponto aux = pontos[i]; pontos[i] = pontos[j]; pontos[j] = aux;
                }
            }
        }
        printf("str:");
        for (int i = 0; i < qt_palavras; i++) {
            printf(" %s", palavras[i]);
        }

        printf(" int:");
        for (int i = 0; i < qt_inteiros; i++){
            printf(" %d", inteiros[i]);
        }

        printf(" float:");
        for (int i = 0; i < qt_reais; i++){
            printf(" %g", reais[i]);
        }

        printf(" p:");
        for (int i = 0; i < qt_pontos; i++){
            printf(" (%.1f,%.1f)", pontos[i].x, pontos[i].y); }

        printf("\n");
    }
    return 0;
}