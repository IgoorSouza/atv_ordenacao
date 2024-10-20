#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[4];
    int vitorias = 0;
    int empates = 0;
    int derrotas = 0;
    int golsPro = 0;
    int golsContra = 0;
    int saldoGols = 0;
    int pontos = 0;
} Time;

void atualizarEstatisticas(Time *time, int golsPro, int golsContra) {
    time->golsPro += golsPro;
    time->golsContra += golsContra;
    time->saldoGols = time->golsPro - time->golsContra;

    if (golsPro > golsContra) {
        time->vitorias++;
        time->pontos += 3;
    } else if (golsPro < golsContra) {
        time->derrotas++;
    } else {
        time->empates++;
        time->pontos += 1;
    }
}

void bubbleSort(Time times[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (times[j].pontos < times[j + 1].pontos ||
               (times[j].pontos == times[j + 1].pontos && times[j].vitorias < times[j + 1].vitorias) ||
               (times[j].pontos == times[j + 1].pontos && times[j].vitorias == times[j + 1].vitorias && times[j].saldoGols < times[j + 1].saldoGols) ||
               (times[j].pontos == times[j + 1].pontos && times[j].vitorias == times[j + 1].vitorias && times[j].saldoGols == times[j + 1].saldoGols && times[j].golsPro < times[j + 1].golsPro)) {
                Time aux = times[j];
                times[j] = times[j + 1];
                times[j + 1] = aux;
            }
        }
    }
}

void selectionSort(Time times[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (times[j].pontos > times[maxIndex].pontos ||
               (times[j].pontos == times[maxIndex].pontos && times[j].vitorias > times[maxIndex].vitorias) ||
               (times[j].pontos == times[maxIndex].pontos && times[j].vitorias == times[maxIndex].vitorias && times[j].saldoGols > times[maxIndex].saldoGols) ||
               (times[j].pontos == times[maxIndex].pontos && times[j].vitorias == times[maxIndex].vitorias && times[j].saldoGols == times[maxIndex].saldoGols && times[j].golsPro > times[maxIndex].golsPro)) {
                maxIndex = j;
            }
        }

        Time tmp = times[i];
        times[i] = times[maxIndex];
        times[maxIndex] = tmp;
    }
}

void insertionSort(Time times[], int n) {
    for (int i = 1; i < n; i++) {
        Time time = times[i];
        int j = i - 1;

        while (j >= 0 && (times[j].pontos < time.pontos ||
                         (times[j].pontos == time.pontos && times[j].vitorias < time.vitorias) ||
                         (times[j].pontos == time.pontos && times[j].vitorias == time.vitorias && times[j].saldoGols < time.saldoGols) ||
                         (times[j].pontos == time.pontos && times[j].vitorias == time.vitorias && times[j].saldoGols == time.saldoGols && times[j].golsPro < time.golsPro))) {
            times[j + 1] = times[j];
            j--;
        }

        times[j + 1] = time;
    }
}

void merge(Time times[], int s, int m, int e) {
    int n1 = m - s + 1, n2 = e - m, i = 0, j = 0, k = s;

    Time time1[n1], time2[n2];

    for (int i = 0; i < n1; i++) {
        time1[i] = times[s + i];
    }

    for (int j = 0; j < n2; j++) {
        time2[j] = times[m + 1 + j];
    }

    while (i < n1 && j < n2) {
        if (time1[i].pontos > time2[j].pontos ||
           (time1[i].pontos == time2[j].pontos && time1[i].vitorias > time2[j].vitorias) ||
           (time1[i].pontos == time2[j].pontos && time1[i].vitorias == time2[j].vitorias && time1[i].saldoGols > time2[j].saldoGols) ||
           (time1[i].pontos == time2[j].pontos && time1[i].vitorias == time2[j].vitorias && time1[i].saldoGols == time2[j].saldoGols && time1[i].golsPro > time2[j].golsPro)) {
            times[k] = time1[i];
            i++;
        } else {
            times[k] = time2[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        times[k] = time1[i];
        i++;
        k++;
    }

    while (j < n2) {
        times[k] = time2[j];
        j++;
        k++;
    }
}

void mergeSort(Time times[], int s, int e) {
    if (s < e) {
        int m = s + (e - s) / 2;

        mergeSort(times, s, m);
        mergeSort(times, m + 1, e);
        merge(times, s, m, e);
    }
}

void imprimir(Time times[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Nome: %s; Pontos: %d; Vitorias: %d; Empates: %d; Derrotas: %d; Saldo de gols: %d; Gols Pro: %d; Gols contra: %d\n",
               times[i].nome, times[i].pontos, times[i].vitorias, times[i].empates, times[i].derrotas, times[i].saldoGols, times[i].golsPro, times[i].golsContra);
    }
}

int main() {
    Time times[83];
    int n = 0, escolha;
    char linha[12];

    FILE *file = fopen("dados.txt", "r");

    while (fgets(linha, sizeof(linha), file) != NULL) {
        char time1[4], time2[4];
        int gols1, gols2;

        if (sscanf(linha, "%s %dX%d %s", time1, &gols1, &gols2, time2) == 4) {
            int i;
            for (i = 0; i < n; i++) {
                if (strcmp(times[i].nome, time1) == 0) {
                    break;
                }
            }

            if (i == n) {
                strcpy(times[n].nome, time1);
                n++;
            }

            atualizarEstatisticas(&times[i], gols1, gols2);

            if (gols1 > gols2) {
                times[i].vitorias++;
            }

            for (i = 0; i < n; i++) {
                if (strcmp(times[i].nome, time2) == 0) {
                    break;
                }
            }

            if (i == n) {
                strcpy(times[n].nome, time2);
                n++;
            }

            atualizarEstatisticas(&times[i], gols2, gols1);

            if (gols2 > gols1) {
                times[i].vitorias++;
            }
        }
    }

    fclose(file);

    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Merge Sort\n");
    printf("5. Sair\n");

    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            bubbleSort(times, n);
            break;

        case 2:
            selectionSort(times, n);
            break;

        case 3:
            insertionSort(times, n);
            break;

        case 4:
            mergeSort(times, 0, n - 1);
            break;

        default:
            break;
    }

    imprimir(times, n);
    return 0;
}
