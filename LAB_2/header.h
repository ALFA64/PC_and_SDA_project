#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define MAX_STRING 90
#define COLOR_BLUE    "\033[34m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"

typedef struct {
    char* nume;
    char* capital;
    double area;
    unsigned int population;
    double BIP;
} State;

typedef struct Node{
    State data;
    struct Node *next;
}Node;

typedef struct{
    char *name_list;
    Node *address_list;
}HeadList;

typedef struct{
    HeadList *head_data;
    int size;
    int capacity;
}ListArray;

ListArray initArrayOfLists();
void print_border_info(const char* text, char border);
void menu_info();
void info_add_data();
void menu(ListArray *arr, char option);
void menu_add_data(ListArray *arr, char option);
void readString(char** dest, const char* prompt);
void clean_screen();
void addFirstItem(Node **head,
                  const char* nume,
                  const char* capital,
                  double area,
                  unsigned int population,
                  double BIP);
void addNewItem(Node **head,
                const char* nume,
                const char* capital, 
                double area,
                unsigned int population,
                double BIP);
void addAfterIndex(Node **head, int index,
                   const char* nume,
                   const char* capital,
                   double area,
                   unsigned int population,
                   double BIP);
void addBeforeIndex(Node **head, int index,
                    const char* nume,
                    const char* capital,
                    double area,
                    unsigned int population,
                    double BIP);
int findListIndex(ListArray *arr, const char *name);
int createNewList(ListArray *arr, const char *name);
int selectList(ListArray *arr);
void view_all_lists(ListArray *arr);
void view_selected_list(ListArray *arr);
void view_data(Node *head);
void search_state_global(ListArray *arr, const char *state_name);
void search_in_selected_list(ListArray *arr);
void search_state(Node *head, const char *name);
void edit_state(Node *head, int index);
void switch_states(Node *head, int i, int j);
void sort_states_list(Node *head);
void delete_state_list(Node **head, int index);
void save_to_file(ListArray *arr, const char *filename);
void read_from_file(ListArray *arr, const char *filename);
void split_list_array(ListArray *arr, int list_index);
void concatenate_lists_array(ListArray *arr,
                             int index1,
                             int index2);
void free_list(Node* head);
void free_all(ListArray *arr);
int list_length(Node *head);
Node* last_node(Node *head);
int list_length(Node *head);

#endif

