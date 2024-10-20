#include <iostream>
#include <string.h>

void troca(char v[][100], int a, int b) {
    char aux[100];
    strcpy(aux, v[a]);
    strcpy(v[a], v[b]);
    strcpy(v[b], aux);
}

void bubbleSort(char v[][100], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool houveTroca = false;
        for (int j = 0; j < (n - 1) - i; j++) {
            if (strcmp(v[j], v[j + 1]) > 0) {
                troca(v, j, j + 1);
                houveTroca = true;
            }
        }

        if (!houveTroca) return;
    }
}

void selectionSort(char v[][100], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menorIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(v[j], v[menorIndex]) < 0) {
                menorIndex = j;
            }
        }

        troca(v, i, menorIndex);
    }
}

void insertionSort(char v[][100], int n) {
    for (int i = 1; i < n; i++) {
        char aux[100];
        int j = i - 1;

        strcpy(aux, v[i]);

        while (j >= 0 && strcmp(aux, v[j]) < 0) {
            strcpy(v[j + 1], v[j]);
            j--;
        }

        strcpy(v[j + 1], aux);
    }
}

void merge(char v[][100], int s, int m, int e) {
    char tmp[1000][100];
    int i = s, j = m + 1, k = 0;

    while (i <= m && j <= e) {
        if (strcmp(v[i], v[j]) < 0) {
            strcpy(tmp[k++], v[i++]);
        } else {
            strcpy(tmp[k++], v[j++]);
        }
    }

    while (i <= m) {
        strcpy(tmp[k++], v[i++]);
    }

    while (j <= e) {
        strcpy(tmp[k++], v[j++]);
    }

    for (i = s, k = 0; i <= e; i++, k++) {
        strcpy(v[i], tmp[k]);
    }
}

void mergeSort(char v[][100], int s, int e) {
    if (s < e) {
        int m = (s + e) / 2;

        mergeSort(v, s, m);
        mergeSort(v, m + 1, e);
        merge(v, s, m, e);
    }
}

void imprimirVetor(char v[][100], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", v[i]);
    }

    printf("\n");
}

int main() {
    int escolha;
    char nomes[1000][100];
    int count = 0;

    FILE *file = fopen("nomes2.txt", "r");

    while (fgets(nomes[count], sizeof(nomes[count]), file) != NULL) {
        count++;
    }

    fclose(file);

    do {
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Sair\n");

        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                bubbleSort(nomes, count);
                imprimirVetor(nomes, count);
                break;

            case 2:
                selectionSort(nomes, count);
                imprimirVetor(nomes, count);
                break;

            case 3:
                insertionSort(nomes, count);
                imprimirVetor(nomes, count);
                break;

            case 4:
               mergeSort(nomes, 0, count - 1);
               imprimirVetor(nomes, count);
               break;

            default:
                break;
        }
    } while (escolha != 5);

    return 0;
}
