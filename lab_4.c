#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int** create_matrix(int n, int m) {
    int **T = malloc(n * sizeof(int *));
    if (!T) return NULL; // verificare alocare
    for (int i = 0; i < n; i++) {
        T[i] = malloc(m * sizeof(int));
        if (!T[i]) { // verificare alocare
            for (int j = 0; j < i; j++) free(T[j]);
            free(T);
            printf("Memory allocation failed\n");
            return NULL;
        }
    }
    printf("Memory allocated successfully for a %dx%d matrix.\n", n, m);
    return T;
}

void free_matrix(int **m, int n) {
    for (int i = 0; i < n; i++) {
        free(m[i]);
    }
    free(m);
    printf("Memory freed successfully.\n");
}

int view_array(int **T, int n, int m){
    printf(">>> Displaying the matrix:\n");
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            printf("%i ",T[i][j]);
        }
        printf("\n");
    }
}

int input_array(int **T, int n, int m){
    printf("<<< Input array elements:\n");
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            printf("T[%i][%i]=",i,j); 
            scanf("%i",&T[i][j]);
        }
    }
}

int sort_odd_columns(int **T, int n, int m) {
    printf(">>> Sorting odd columns...\n");
    for (int j = 0; j < m; j += 2) { // coloane impare
        for (int i = 0; i < n - 1; i++) {
            for (int k = 0; k < n - i - 1; k++) {
                if (T[k][j] > T[k + 1][j]) {
                    int temp = T[k][j];
                    T[k][j] = T[k + 1][j];
                    T[k + 1][j] = temp;
                }
            }
        }
    }
    printf("<<< Odd columns sorted successfully.\n");
    view_array(T, n, m);
    return 0;
}

void print_menu() {
    printf("=====================================\n");
    printf("\nMenu:\n");
    printf("1: Allocate memory for a matrix of size n x m\n");
    printf("2: Insert elements into the matrix manually\n");
    printf("3: Complete the matrix with random values\n");
    printf("4: Sort odd columns of the matrix\n");
    printf("5: Display the matrix\n");
    printf("6: Free allocated memory\n");
    printf("0: Exit the program\n");
    printf("\n");
    printf("111 Clear screen\n");
    printf("112: View menu\n");
    printf("=====================================\n");
}

void clrscr() {
    system("clear||cls");
}

bool verify_allocation(int **T) {
    if (T == NULL) {
        printf("Matrix not allocated. Please allocate memory first (choose option 1).\n");
        return false;
    }
    return true;
}

int input_random_values(int **T, int n, int m) {
    printf("<<< Filling the matrix with random values (0-100)...\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            T[i][j] = rand() % 101; // valori random intre 0 si 99
        }
    }
    printf("<<< Matrix filled with random values successfully.\n");
    view_array(T, n, m);
    return 0;
}


void main(){
    int n,m,**T = NULL;
    int option;
    bool status=true;
    print_menu();
    while (status){
        printf("--------------------------------\n");
        printf("Choose an option: ");
        scanf("%i",&option);
        switch (option)
        {
        case 1:{
            clrscr();
            printf("1. Input size of the array n x m\n");
            printf("n >>> "); scanf("%i",&n);
            printf("m >>> "); scanf("%i",&m);
            T = create_matrix(n, m);
            break;
        }
        case 2:{
            clrscr();
            printf("2. Input array elements:\n");
            if(verify_allocation(T)) {
                input_array(T,n,m);
                break;
            }
            break;
        }
        case 3:{
            clrscr();
            printf("3. Complete the matrix with random values\n");
            if (verify_allocation(T)) {
                input_random_values(T, n, m);
                break;
            }
            break;
        }
        case 4:{
            clrscr();
            printf("4. Sort odd columns of the matrix\n");
            if (verify_allocation(T)){
                sort_odd_columns(T, n, m);
                break;
            }
            break;
        }
        case 5:{
            clrscr();
            printf("5. Display the matrix\n");
            if (verify_allocation(T)){
                view_array(T,n,m);
                break;
            }
            break;
        }
        case 6:{
            printf("6. Free allocated memory\n");
            if (verify_allocation(T)){
                free_matrix(T, n);
                break;
            }
            break;
        }
        case 0:{
            if (verify_allocation(T)){
                free_matrix(T, n);
            }
            printf("Exiting the program.\n");
            status=false;
            break;}
        case 112:{
            clrscr();
            print_menu();
            break;}
        case 111:{
            clrscr();
            break;
        }
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }
}