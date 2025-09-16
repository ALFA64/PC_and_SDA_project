#include <stdio.h>
#include <stdlib.h>

int view_array(int T[11][11], int n, int m){
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            printf("%i ",T[i][j]);
        }
        printf("\n");
    }
}

int input_array(int T[11][11], int n, int m){
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            printf("T[%i][%i]=",i,j); 
            scanf("%i",&T[i][j]);
        }
    }
}

int* maxim_local(int T[11][11], int n, int m, int *count) {
    int *max_list = NULL;
    int k = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int max = T[i][j];
            if (i > 0     && T[i-1][j] > max) max = T[i-1][j];
            if (i < n-1   && T[i+1][j] > max) max = T[i+1][j];
            if (j > 0     && T[i][j-1] > max) max = T[i][j-1];
            if (j < m-1   && T[i][j+1] > max) max = T[i][j+1];

            if (max == T[i][j]) {          // e maxim local
                int *tmp = realloc(max_list, (k + 1) * sizeof(int));
                if (!tmp) {                 // verificare alocare
                    free(max_list);
                    *count = 0;
                    return NULL;
                }
                max_list = tmp;
                max_list[k++] = T[i][j];
            }
        }
    }
    *count = k;
    return max_list;   // apelantul va face free()
}


void main(){
    int n,m,count;
    int T[11][11];
    printf("Introdu dimensiunea tabloului n x m <= 10 \n");
    printf("n = ");scanf("%i",&n);
    printf("m = ");scanf("%i",&m);
    input_array(T,n,m);
    view_array(T,n,m);
    int *maxim_local_values = maxim_local(T, n, m, &count);
    printf("Numar de maxime locale: %i\n", count);
    printf("Lista de Maxime local >>> ");
    for (int i = 0; i < count; i++) {
        printf("%i ", maxim_local_values[i]);
    }
    free(maxim_local_values);
}