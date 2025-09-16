#include <stdio.h>

int element_min(int T[], int n) {
    int min = T[0], k = 0;
    for (int i = 1; i < n; i++) {
        if (T[i] < min && T[i] > 0) {
            min = T[i];
            k = i;
        }
    }
    return k;
}

int count_positiv_element(int T[], int n){
	int k=0;
	for (int i = 0; i < n; i++){
		k += (T[i]>0);
	}
	return k;
}

int main() {
    int n;
    printf("Introdu dimensiunea tabloului >>> ");
    scanf("%i", &n);

    int T[11]; 
    for (int i = 0; i < n; i++) {
        printf("T[%i] = ", i);
        scanf("%i", &T[i]);
    }

    int idx = element_min(T, n);
    printf("Valoarea minima = %i, pozitia = %i\n", T[idx], idx);
	printf("Numarul de elemente pozitive >>> %i",count_positiv_element(T,n));
    return 0;
}
