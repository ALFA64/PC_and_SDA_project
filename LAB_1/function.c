#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void print_border_info(const char* text, char border){
    int len = strlen(text);
    printf("\n");
    for(int i=0; i<len+4; i++)
        printf("*");

    printf("\n* %s *\n",text);

    for(int i=0; i<len+4; i++)
        printf("*");

    printf("\n");   
}

void menu_info(){
    printf_s("\n1) Add data (Firstly/Lasted/After idicated elemtent/befor indicated element) >>> 1\n");
    printf_s("2) View data >>> 2\n");
    printf_s("3) Search element from storage data >>> 3\n");
    printf_s("4) Edit data >>> 4\n");
    printf_s("5) Switch 2 elements >>> 5\n");
    printf_s("6) Sort storage data >>> 6\n");
    printf_s("7) Deleted choused element>>> 7\n");
    printf_s("8) Save data in file >>> 8\n");
    printf_s("9) Read data from file >>> 9\n");
    printf_s("h) View Menu option >>> h\n");
    printf_s("c) Clean screen panel >>> c\n");
    printf_s("0) EXIT >>> 0\n");
}

void info_add_data(){
    printf_s("1) Add item firstly of the all data >>> 1\n");
    printf_s("2) Add item lasted of the all data >>> 2\n");
    printf_s("3) Add item after indicated element of the data >>> 3\n");
    printf_s("4) Add item befor indicated element of the data >>> 4\n");
}

void menu(StateArray *arr, char option) {
    switch (option) {
        case '1': {
            char option_add;
            info_add_data();
            printf("Input option >>>");
            scanf(" %c", &option_add);
            menu_add_data(arr, option_add);
            break;
        }
        case '2':
            view_data(arr);
            break;
        case '3': {
            char name[MAX_STRING];
            printf("Enter state name to search: ");
            scanf(" %89s", name);
            search_state(arr, name);
            break;
        }
        case '4': {
            int index;
            printf("Enter index to edit (1..%d): ", arr->size);
            scanf("%d", &index);
            edit_state(arr, index-1);
            break;
        }
        case '5': {
            int i, j;
            printf("Enter two indices to switch: ");
            scanf("%d %d", &i, &j);
            switch_states(arr, i-1, j-1);
            break;
        }
        case '6':
            sort_states(arr);
            printf("States sorted by name.\n");
            break;
        case '7': {
            int index;
            printf("Enter index to delete (1..%d): ", arr->size);
            scanf("%d", &index);
            delete_state(arr, index-1);
            break;
        }
        case '8':
            char filename_export[MAX_STRING];
            printf("Input file name >>>");
            scanf(" %s",&filename_export);
            save_to_file(arr, filename_export);
            printf("Data saved to states.txt\n");
            break;
        case '9':
            printf("List of file .TXT :\n");
            #ifdef _WIN32
                system("dir *.txt /b");
            #elif __linux__
                system("ls *.txt /b");
            #endif
            printf("\n");
            char filename_import[MAX_STRING];
            printf("Input file name >>>");
            scanf(" %s",&filename_import);
            read_from_file(arr, filename_import);
            printf("Data loaded from states.txt\n");
            break;
        case 'h':
            menu_info();
            break;
        case 'c':
            clean_screen();
            break;
        case '0':
            // handled in main loop
            break;
        default:
            printf("Invalid option!\n");
            menu_info();
            break;
    }
}


void menu_add_data(StateArray *arr, char option) {
    State s;

    // clear leftover newline before reading strings
    while (getchar() != '\n');

    readString(&s.nume, "Introdu numele tarii: ");
    readString(&s.capital, "Introdu numele capitalei: ");
    printf("Introdu suprafata (km^2) >>> ");
    scanf("%lf", &s.area);
    printf("Introdu numarul populatiei >>> ");
    scanf("%u", &s.population);
    printf("Introdu BIP >>> ");
    scanf("%lf", &s.BIP);
    while (getchar() != '\n'); // clear newline after last scanf

    int index;
    switch(option) {
        case '1': // add first
            addFirstItem(arr, s.nume, s.capital, s.area, s.population, s.BIP);
            break;
        case '2': // add last
            addNewItem(arr, s.nume, s.capital, s.area, s.population, s.BIP);
            break;
        case '3': // add after index
            printf("Enter index after which to insert: ");
            scanf("%d", &index);
            addAfterIndex(arr, index-1, s.nume, s.capital, s.area, s.population, s.BIP);
            break;
        case '4': // add before index
            printf("Enter index before which to insert: ");
            scanf("%d", &index);
            addBeforeIndex(arr, index-1, s.nume, s.capital, s.area, s.population, s.BIP);
            break;
        case '0':
            printf("Drop option\n");
            break;
        default:
            printf("Invalid add option.\n");
    }
}



void readString(char** dest, const char* prompt){
    char buffer[MAX_STRING];
    printf("%s",prompt);

    if(fgets(buffer, sizeof(buffer), stdin) != NULL){
        size_t len = strlen(buffer);
        if(len>0 && buffer[len-1] == '\n')
            buffer[len-1]='\0';

        *dest = malloc(strlen(buffer)+1);
        if(*dest!=NULL){
            strcpy(*dest,buffer);
        }
    }
}

void clean_screen(){
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

StateArray initStateArray(){
    StateArray arr;

    arr.capacity = 10;
    arr.size = 0;

    arr.data = malloc(arr.capacity*sizeof(State));

    if (arr.data == NULL){
        printf("Allocation error\n");
        arr.capacity = 0;
    }

    return arr;
}

void addFirstItem(StateArray *arr,
                  const char* nume,
                  const char* capital,
                  double area,
                  unsigned int population,
                  double BIP)
{
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        State* temp = realloc(arr->data, arr->capacity * sizeof(State));
        if (!temp) { printf("Realloc error\n"); return; }
        arr->data = temp;
    }

    // Shift elements right
    for (int i = arr->size; i > 0; i--) {
        arr->data[i] = arr->data[i-1];
    }

    State* s = &arr->data[0];
    s->nume = strdup(nume);
    s->capital = strdup(capital);
    s->area = area;
    s->population = population;
    s->BIP = BIP;

    arr->size++;
}


void addNewItem(StateArray* arr,
                const char* nume,
                const char* capital, 
                double area,
                unsigned int population,
                double BIP)
{
    if(arr->size == arr->capacity){
        arr->capacity *= 2;
        State* temp = realloc(arr->data, arr->capacity * sizeof(State));

        if(temp == NULL){
            printf("Realloc error\n");
            return;
        }

        arr->data = temp;
    }

    State* s = &arr->data[arr->size];
    s->nume = strdup(nume);
    s->capital = strdup(capital);
    s->area = area;
    s->population = population;
    s->BIP = BIP;

    arr->size++;
}

void addAfterIndex(StateArray *arr, int index,
                   const char* nume,
                   const char* capital,
                   double area,
                   unsigned int population,
                   double BIP)
{
    if (index < 0 || index >= arr->size) {
        printf("Invalid index.\n");
        return;
    }

    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        State* temp = realloc(arr->data, arr->capacity * sizeof(State));
        if (!temp) { printf("Realloc error\n"); return; }
        arr->data = temp;
    }

    // Shift elements right
    for (int i = arr->size; i > index+1; i--) {
        arr->data[i] = arr->data[i-1];
    }

    State* s = &arr->data[index+1];
    s->nume = strdup(nume);
    s->capital = strdup(capital);
    s->area = area;
    s->population = population;
    s->BIP = BIP;

    arr->size++;
}

void addBeforeIndex(StateArray *arr, int index,
                    const char* nume,
                    const char* capital,
                    double area,
                    unsigned int population,
                    double BIP)
{
    if (index < 0 || index >= arr->size) {
        printf("Invalid index.\n");
        return;
    }

    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        State* temp = realloc(arr->data, arr->capacity * sizeof(State));
        if (!temp) { printf("Realloc error\n"); return; }
        arr->data = temp;
    }

    // Shift elements right
    for (int i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i-1];
    }

    State* s = &arr->data[index];
    s->nume = strdup(nume);
    s->capital = strdup(capital);
    s->area = area;
    s->population = population;
    s->BIP = BIP;

    arr->size++;
}



void view_data(StateArray *arr) {
    if (arr->size == 0) {
        printf("\nNo states stored yet.\n");
        return;
    }

    // Print header
    printf("\n---------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-20s | %-10s | %-12s | %-10s |\n",
           "ID", "Country", "Capital", "Area", "Population", "BIP");
    printf("---------------------------------------------------------------------------------------------\n");

    // Print rows
    for (int i = 0; i < arr->size; i++) {
        printf("| %-3d | %-20s | %-20s | %-10.2lf | %-12u | %-10.2lf |\n",
               i+1,
               arr->data[i].nume,
               arr->data[i].capital,
               arr->data[i].area,
               arr->data[i].population,
               arr->data[i].BIP);
    }

    printf("---------------------------------------------------------------------------------------------\n");
}


void search_state(StateArray *arr, const char *name) {
    printf("\n---------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-20s | %-10s | %-12s | %-10s |\n",
           "ID", "Country", "Capital", "Area", "Population", "BIP");
    printf("---------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < arr->size; i++) {
        if (strcmp(arr->data[i].nume, name) == 0) {
            printf("| %-3d | %-20s | %-20s | %-10.2lf | %-12u | %-10.2lf |\n",
               i+1,
               arr->data[i].nume,
               arr->data[i].capital,
               arr->data[i].area,
               arr->data[i].population,
               arr->data[i].BIP);
            return;
        }
    }
    printf("---------------------------------------------------------------------------------------------\n");
    printf("State '%s' not found.\n", name);
}

void edit_state(StateArray *arr, int index) {
    if (index < 0 || index >= arr->size) {
        printf("Invalid index.\n");
        return;
    }

    State *s = &arr->data[index];
    printf("Editing state %s...\n", s->nume);

    while (getchar() != '\n');

    free(s->nume);
    free(s->capital);

    readString(&s->nume, "New name: ");
    readString(&s->capital, "New capital: ");

    printf("New area: ");
    scanf("%lf", &s->area);
    printf("New population: ");
    scanf("%u", &s->population);
    printf("New BIP: ");
    scanf("%lf", &s->BIP);

    // Clear newline after last scanf
    while (getchar() != '\n');
}


void switch_states(StateArray *arr, int i, int j) {
    if (i < 0 || j < 0 || i >= arr->size || j >= arr->size) {
        printf("Invalid indices.\n");
        return;
    }
    State temp = arr->data[i];
    arr->data[i] = arr->data[j];
    arr->data[j] = temp;
}

int compare_states(const void *a, const void *b) {
    const State *s1 = (const State*)a;
    const State *s2 = (const State*)b;
    return strcmp(s1->nume, s2->nume);
}

void sort_states(StateArray *arr) {
    qsort(arr->data, arr->size, sizeof(State), compare_states);
}

void delete_state(StateArray *arr, int index) {
    if (index < 0 || index >= arr->size) {
        printf("Invalid index.\n");
        return;
    }
    free(arr->data[index].nume);
    free(arr->data[index].capital);
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i+1];
    }
    arr->size--;
}

void save_to_file(StateArray *arr, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) { printf("Error opening file.\n"); return; }
    for (int i = 0; i < arr->size; i++) {
        fprintf(f, "%s;%s;%.2lf;%u;%.2lf\n",
                arr->data[i].nume,
                arr->data[i].capital,
                arr->data[i].area,
                arr->data[i].population,
                arr->data[i].BIP);
    }
    fclose(f);
}

void read_from_file(StateArray *arr, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) { printf("Error opening file.\n"); return; }
    char nume[MAX_STRING], capital[MAX_STRING];
    double area, BIP;
    unsigned int population;
    while (fscanf(f, "%89[^;];%89[^;];%lf;%u;%lf\n", nume, capital, &area, &population, &BIP) == 5) {
        addNewItem(arr, nume, capital, area, population, BIP);
    }
    fclose(f);
}


void freeStateArray(StateArray* arr){
    for(int i=0; i<arr->size;i++){
        free(arr->data[i].nume);
        free(arr->data[i].capital);
    }

    free(arr->data);
}