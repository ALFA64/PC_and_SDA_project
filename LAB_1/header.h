#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define MAX_STRING 90

typedef struct {
    char* nume;
    char* capital;
    double area;
    unsigned int population;
    double BIP;
} State;

typedef struct {
    State* data;
    int size;
    int capacity;
} StateArray;

// Core functions used in main.c
void print_border_info(const char* text, char border);
void menu_info();
void info_add_data();
void menu(StateArray *arr, char option);
void menu_add_data(StateArray *arr, char option);
void readString(char** dest, const char* prompt);
void clean_screen(void);
StateArray initStateArray();
void freeStateArray(StateArray* arr);

// CRUD operations
void addFirstItem(StateArray *arr, const char* nume, const char* capital,
                  double area, unsigned int population, double BIP);
void addNewItem(StateArray* arr, const char* nume, const char* capital,
                double area, unsigned int population, double BIP);
void addAfterIndex(StateArray *arr, int index, const char* nume, const char* capital,
                   double area, unsigned int population, double BIP);
void addBeforeIndex(StateArray *arr, int index, const char* nume, const char* capital,
                    double area, unsigned int population, double BIP);

void view_data(StateArray *arr);
void search_state(StateArray *arr, const char *name);
void edit_state(StateArray *arr, int index);
void switch_states(StateArray *arr, int i, int j);
void sort_states(StateArray *arr);
void delete_state(StateArray *arr, int index);

void save_to_file(StateArray *arr, const char *filename);
void read_from_file(StateArray *arr, const char *filename);

#endif
