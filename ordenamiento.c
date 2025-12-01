#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ===================== CREAR ARREGLO ===================== */
int* generarVector(int n) {
    int *v = malloc(sizeof(int) * n);
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        v[i] = rand() % 100 + 1;
    return v;
}

void duplicarVector(int *src, int *dst, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

/* ===================== BURBUJA ===================== */
void ordenBurbuja(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {  // pequeño cambio
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

/* ===================== QUICKSORT ===================== */
void quick(int *a, int left, int right) {
    int i = left, j = right;
    int pivot = a[(left + right) / 2];

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;

        if (i <= j) {
            int aux = a[i];
            a[i] = a[j];
            a[j] = aux;
            i++; j--;
        }
    }

    if (left < j) quick(a, left, j);
    if (i < right) quick(a, i, right);
}

/* ===================== SHELL SORT ===================== */
void shell(int *a, int n) {
    for (int salto = n / 2; salto > 0; salto /= 2) {
        for (int i = salto; i < n; i++) {
            int temp = a[i];
            int j = i;

            while (j >= salto && a[j - salto] > temp) {
                a[j] = a[j - salto];
                j -= salto;
            }

            a[j] = temp;
        }
    }
}

/* ===================== RADIX SORT ===================== */
int obtenerMax(int *a, int n) {
    int m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > m) m = a[i];
    return m;
}

void counting(int *a, int n, int exp) {
    int salida[n];
    int contador[10] = {0};

    for (int i = 0; i < n; i++)
        contador[(a[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        contador[i] += contador[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        salida[contador[(a[i] / exp) % 10] - 1] = a[i];
        contador[(a[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = salida[i];
}

void radix(int *a, int n) {
    int max = obtenerMax(a, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        counting(a, n, exp);
}

/* ===================== MAIN ===================== */
int main() {
    int n;

    printf("Ingresa el tamano del vector: ");
    scanf("%d", &n);

    int *original = generarVector(n);

    int *v1 = malloc(n * sizeof(int));
    int *v2 = malloc(n * sizeof(int));
    int *v3 = malloc(n * sizeof(int));
    int *v4 = malloc(n * sizeof(int));

    duplicarVector(original, v1, n);
    duplicarVector(original, v2, n);
    duplicarVector(original, v3, n);
    duplicarVector(original, v4, n);

    clock_t start, end;

    start = clock();
    ordenBurbuja(v1, n);
    end = clock();
    double tBurbuja = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    quick(v2, 0, n - 1);
    end = clock();
    double tQuick = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    shell(v3, n);
    end = clock();
    double tShell = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    radix(v4, n);
    end = clock();
    double tRadix = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n===== TIEMPOS DE ORDENAMIENTO =====\n");
    printf("Burbuja :   %.6f segundos\n", tBurbuja);
    printf("QuickSort : %.6f segundos\n", tQuick);
    printf("ShellSort : %.6f segundos\n", tShell);
    printf("RadixSort : %.6f segundos\n", tRadix);

    free(original);
    free(v1); free(v2); free(v3); free(v4);

    return 0;
}
