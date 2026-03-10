#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

ListArray initArrayOfLists() {
    ListArray arr;

    arr.capacity = 10;
    arr.size = 0;

    arr.head_data = malloc(arr.capacity * sizeof(HeadList));

    if (arr.head_data == NULL) {
        printf("Allocation error\n");
        arr.capacity = 0;
        return arr;
    }

    // inițializare elemente
    for (int i = 0; i < arr.capacity; i++) {
        arr.head_data[i].name_list = NULL;
        arr.head_data[i].address_list = NULL;
    }

    return arr;
}

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
    printf_s(COLOR_CYAN "\n1) Add data (Firstly/Lasted/After idicated elemtent/befor indicated element) >>> 1\n");
    printf_s("2) View data >>> 2\n");
    printf_s("3) Search element from storage data >>> 3\n");
    printf_s("4) Edit data >>> 4\n");
    printf_s("5) Switch 2 elements >>> 5\n");
    printf_s("6) Sort storage data >>> 6\n");
    printf_s("7) Deleted choused element>>> 7\n");
    printf_s("8) Save data in file >>> 8\n");
    printf_s("9) Read data from file >>> 9\n");
    printf_s("10) Divide list >>> d\n");
    printf_s("11) Split list >>> s\n");
    printf_s("h) View Menu option >>> h\n");
    printf_s("c) Clean screen panel >>> c\n");
    printf_s("0) EXIT >>> 0\n" COLOR_RESET);
}

void info_add_data(){
    printf_s("1) Add item firstly of the all data >>> 1\n");
    printf_s("2) Add item lasted of the all data >>> 2\n");
    printf_s("3) Add item after indicated element of the data >>> 3\n");
    printf_s("4) Add item befor indicated element of the data >>> 4\n");
}

void menu(ListArray *arr, char option)
{
    switch (option)
    {
        case '1': {
            char option_add;

            info_add_data();
            printf("Input option >>> ");
            scanf(" %c", &option_add);

            menu_add_data(arr, option_add);   // multi-list
            break;
        }
        case '2':
            view_all_lists(arr);
            break;
        case '3': {
            char name[MAX_STRING];

            printf("Enter state name to search: ");
            scanf(" %89s", name);

            search_state_global(arr, name);
            break;
        }
        case '4': {
            view_all_lists(arr);

            int listIndex = selectList(arr);
            if (listIndex == -1)
                break;

            int stateIndex;
            printf("Enter state index: ");
            scanf("%d", &stateIndex);

            edit_state(arr->head_data[listIndex].address_list,
                       stateIndex);
            break;
        }
        case '5':{
            int listIndex = selectList(arr);
            if (listIndex == -1)
                break;

            int p1, p2;
            printf("Index value 1 : ");
            scanf("%d", &p1);

            printf("Index value 2 : ");
            scanf("%d", &p2);

            switch_states(arr->head_data[listIndex].address_list,p1-1,p2-1);
            break;
        }
        case '6': {
            view_all_lists(arr);

            int listIndex;
            printf("Select list to sort: ");
            scanf("%d", &listIndex);

            sort_states_list(arr->head_data[listIndex].address_list);

            printf("List sorted.\n");
            break;
        }
        case '7': {
            view_all_lists(arr);

            int listIndex;
            printf("Select list: ");
            scanf("%d", &listIndex);

            int stateIndex;
            printf("Enter state index: ");
            scanf("%d", &stateIndex);

            delete_state_list(&arr->head_data[listIndex].address_list,
                              stateIndex - 1);
            break;
        }
        case '8': {
            char filename[100];

            printf("Input file name >>> ");
            scanf("%99s", filename);

            save_to_file(arr, filename);
            break;
        }
        case '9': {
            printf("List of file .TXT :\n" COLOR_CYAN);
            #ifdef _WIN32
                system("dir *.txt /b");
            #elif __linux__
                system("ls *.txt /b");
            #endif
            printf(COLOR_RESET "\n");
            char filename_import[MAX_STRING];
            printf("Input file name >>> ");
            scanf(" %s", &filename_import);

            read_from_file(arr, filename_import);
            break;
        }
        case 'd': {
            view_all_lists(arr);

            int listIndex;
            printf("Select list to divide: ");
            scanf("%d", &listIndex);

            split_list_array(arr, listIndex);
            break;
        }
        case 's': {
            view_all_lists(arr);

            int i, j;
            printf("Enter first list index: ");
            scanf("%d", &i);

            printf("Enter second list index: ");
            scanf("%d", &j);

            concatenate_lists_array(arr, i, j);
            break;
        }
        case 'h':
            menu_info();
            break;
        case 'c':
            clean_screen();
            break;
        case '0':
            break;
        default:
            printf("Invalid option!\n");
            menu_info();
            break;
    }
}

void menu_add_data(ListArray *arr, char option)
{
    int list_index = selectList(arr);

    if (list_index == -1)
        return;

    Node **head = &arr->head_data[list_index].address_list;

    State s;

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    readString(&s.nume, "Introdu numele tarii: ");
    readString(&s.capital, "Introdu numele capitalei: ");

    printf("Introdu suprafata (km^2) >>> ");
    scanf("%lf", &s.area);

    printf("Introdu numarul populatiei >>> ");
    scanf("%u", &s.population);

    printf("Introdu BIP >>> ");
    scanf("%lf", &s.BIP);

    while ((c = getchar()) != '\n' && c != EOF);

    int index;

    switch(option)
    {
        case '1':
            addFirstItem(head, s.nume, s.capital,
                         s.area, s.population, s.BIP);
            break;

        case '2':
            addNewItem(head, s.nume, s.capital,
                       s.area, s.population, s.BIP);
            break;

        case '3':
            printf("Enter index after which to insert: ");
            scanf("%d", &index);

            if (index < 1) {
                printf("Invalid index.\n");
                break;
            }

            addAfterIndex(head, index-1,
                          s.nume, s.capital,
                          s.area, s.population, s.BIP);
            break;

        case '4':
            printf("Enter index before which to insert: ");
            scanf("%d", &index);

            if (index < 1) {
                printf("Invalid index.\n");
                break;
            }

            addBeforeIndex(head, index-1,
                           s.nume, s.capital,
                           s.area, s.population, s.BIP);
            break;

        default:
            printf("Invalid option.\n");
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

void addFirstItem(Node **head,
                  const char* nume,
                  const char* capital,
                  double area,
                  unsigned int population,
                  double BIP)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode){
        printf("Memory allocation error\n");
        return;
    }

    newNode->data.nume = strdup(nume);
    newNode->data.capital = strdup(capital);
    newNode->data.area = area;
    newNode->data.population = population;
    newNode->data.BIP = BIP;

    newNode->next = *head; // leaga catre fostul inceput
    *head = newNode; //noul inceput devine acest nod
}

void addNewItem(Node **head,
                const char* nume,
                const char* capital, 
                double area,
                unsigned int population,
                double BIP)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode){
        printf("Memory allocation error\n");
        return;
    }
    
    newNode->data.nume = strdup(nume);
    newNode->data.capital = strdup(capital);
    newNode->data.area = area;
    newNode->data.population = population;
    newNode->data.BIP = BIP;

    newNode->next = NULL;
    //daca lista e goala se considera ca nodul sfarsit a nodului de inainte e NULL
    if(*head == NULL){
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

void addAfterIndex(Node **head, int index,
                   const char* nume,
                   const char* capital,
                   double area,
                   unsigned int population,
                   double BIP)
{
    if (index < 0) {
        printf("Invalid index.\n");
        return;
    }

    Node* temp = *head;
    int i = 0;

    // mergem la poziția index
    while (temp != NULL && i < index) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Index out of range.\n");
        return;
    }

    // creare nod nou
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error.\n");
        return;
    }

    newNode->data.nume = strdup(nume);
    newNode->data.capital = strdup(capital);
    newNode->data.area = area;
    newNode->data.population = population;
    newNode->data.BIP = BIP;

    //legare corecta
    newNode->next = temp->next;
    temp->next = newNode;
}

void addBeforeIndex(Node **head, int index,
                    const char* nume,
                    const char* capital,
                    double area,
                    unsigned int population,
                    double BIP)
{
    if (index < 0) {
        printf("Invalid index.\n");
        return;
    }

    // Inserare înainte de poziția 0
    if (index == 0) {
        addFirstItem(head, nume, capital, area, population, BIP);
        return;
    }

    Node *temp = *head;
    int i = 0;

    // mergem la nodul anterior poziției dorite
    while (temp != NULL && i < index - 1) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Index out of range.\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error.\n");
        return;
    }

    newNode->data.nume = strdup(nume);
    newNode->data.capital = strdup(capital);
    newNode->data.area = area;
    newNode->data.population = population;
    newNode->data.BIP = BIP;

    newNode->next = temp->next;
    temp->next = newNode;
}

int findListIndex(ListArray *arr, const char *name) {
    for (int i = 0; i < arr->size; i++) {
        if (strcmp(arr->head_data[i].name_list, name) == 0)
            return i;
    }
    return -1;
}

int createNewList(ListArray *arr, const char *name) {

    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->head_data = realloc(arr->head_data,
                                 arr->capacity * sizeof(HeadList));

        if (!arr->head_data) {
            printf("Reallocation error\n");
            return -1;
        }
    }

    arr->head_data[arr->size].name_list = strdup(name);
    arr->head_data[arr->size].address_list = NULL;

    arr->size++;

    return arr->size - 1; // indexul noii liste
}

int selectList(ListArray *arr) {

    char name[MAX_STRING];

    printf("Introdu denumirea listei: ");
    scanf("%89s", name);

    int index = findListIndex(arr, name);

    if (index == -1) {
        char opt;
        printf("Lista nu exista. Creezi lista noua? (y/n): ");
        scanf(" %c", &opt);

        if (opt == 'y' || opt == 'Y') {
            index = createNewList(arr, name);
            printf("Lista creata.\n");
        } else {
            return -1;
        }
    }

    return index;
}

void view_all_lists(ListArray *arr)
{
    if (arr->size == 0) {
        printf("Nu exista liste.\n");
        return;
    }

    for (int i = 0; i < arr->size; i++) {
        printf("\n====================================\n");
        printf("Lista %d: %s\n", i, arr->head_data[i].name_list);
        printf("====================================\n");

        view_data(arr->head_data[i].address_list);

        printf("\n====================================\n");
        printf("Length list >>> %i\n",list_length(arr->head_data[i].address_list));

        Node *last = last_node(arr->head_data[i].address_list);

        if(last)
            printf("Address of last element >>> %p",(void*)last);
        else
            printf("Address of last element >>> %p",NULL);
        printf("\n====================================\n");
    }
}

void view_selected_list(ListArray *arr)
{
    int index = selectList(arr);

    if (index == -1)
        return;

    printf("\nLista: %s\n", arr->head_data[index].name_list);
    view_data(arr->head_data[index].address_list);
}

void view_data(Node *head) {
    if (head == NULL) {
        printf("Lista este goala.\n");
        return;
    }

    Node *temp = head;
    int index = 1;

    // Header
    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-20s | %-10s | %-12s | %-10s | %-14s | %-14s |",
           "ID", "Country", "Capital", "Area", "Population", "BIP",
           "Current Addr", "Next Addr");
    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");
    // Parcurgere lista
    while (temp != NULL) {

        printf("| %-3d | %-20s | %-20s | %-10.2lf | %-12u | %-10.2lf | %-14p | %-14p |\n",
               index++,
               temp->data.nume,
               temp->data.capital,
               temp->data.area,
               temp->data.population,
               temp->data.BIP,
               (void*)temp,
               (void*)temp->next);

        temp = temp->next;
    }

    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Lungime lista: %d\n", index - 1);
}

void search_state_global(ListArray *arr, const char *state_name)
{
    if (arr->size == 0) {
        printf("Nu exista liste.\n");
        return;
    }

    int found = 0;

    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-15s | %-3s | %-20s | %-20s | %-10s | %-12s | %-10s | %-14p |\n",
           "Lista", "ID", "Country", "Capital", "Area", "Population", "BIP", "Current Addr");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < arr->size; i++) {

        Node *temp = arr->head_data[i].address_list;
        int index = 1;

        while (temp != NULL) {

            if (strcmp(temp->data.nume, state_name) == 0) {

                printf("| %-15s | %-3d | %-20s | %-20s | %-10.2lf | %-12u | %-10.2lf |\n",
                       arr->head_data[i].name_list,
                       index,
                       temp->data.nume,
                       temp->data.capital,
                       temp->data.area,
                       temp->data.population,
                       temp->data.BIP,
                       (void*)temp
                );

                found = 1;
            }

            temp = temp->next;
            index++;
        }
    }

    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");

    if (!found) {
        printf("Statul '%s' nu a fost gasit in nicio lista.\n", state_name);
    }
}

void search_in_selected_list(ListArray *arr)
{
    int index = selectList(arr);

    if (index == -1)
        return;

    char name[MAX_STRING];

    printf("Enter state name to search: ");
    scanf("%89s", name);

    search_state(arr->head_data[index].address_list, name);
}

void search_state(Node *head, const char *name)
{
    if (!head) {
        printf("Lista este goala.\n");
        return;
    }
    printf("\n---------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-20s | %-10s | %-12s | %-10s |\n",
           "ID", "Country", "Capital", "Area", "Population", "BIP");
    printf("---------------------------------------------------------------------------------------------\n");

    Node *temp = head;
    int index = 1;

    while (temp != NULL) {

        if (strcmp(temp->data.nume, name) == 0) {
            printf("| %-3d | %-20s | %-20s | %-10.2lf | %-12u | %-10.2lf |\n",
                   index,
                   temp->data.nume,
                   temp->data.capital,
                   temp->data.area,
                   temp->data.population,
                   temp->data.BIP);
            printf("---------------------------------------------------------------------------------------------\n");
            return;
        }

        temp = temp->next;
        index++;
    }
    printf("---------------------------------------------------------------------------------------------\n");
    printf("State '%s' not found.\n", name);
}

void edit_state(Node *head, int index)
{
    if (head == NULL) {
        printf("Lista este goala.\n");
        return;
    }

    Node *temp = head;
    int current = 1;

    // mergem la poziția dorită
    while (temp != NULL && current < index) {
        temp = temp->next;
        current++;
    }

    if (temp == NULL) {
        printf("Index invalid.\n");
        return;
    }

    int option;

    do {
        printf("\nEditing state: %s\n", temp->data.nume);
        printf("1. Modifica nume\n");
        printf("2. Modifica capitala\n");
        printf("3. Modifica suprafata\n");
        printf("4. Modifica populatia\n");
        printf("5. Modifica BIP\n");
        printf("6. Modifica toate campurile\n");
        printf("0. Iesire\n");
        printf("Optiune: ");
        scanf("%d", &option);

        while (getchar() != '\n');

        switch(option) {

            case 1:
                free(temp->data.nume);
                readString(&temp->data.nume, "Nume nou: ");
                break;

            case 2:
                free(temp->data.capital);
                readString(&temp->data.capital, "Capitala noua: ");
                break;

            case 3:
                printf("Suprafata noua: ");
                scanf("%lf", &temp->data.area);
                break;

            case 4:
                printf("Populatie noua: ");
                scanf("%u", &temp->data.population);
                break;

            case 5:
                printf("BIP nou: ");
                scanf("%lf", &temp->data.BIP);
                break;

            case 6:
                free(temp->data.nume);
                free(temp->data.capital);

                readString(&temp->data.nume, "Nume nou: ");
                readString(&temp->data.capital, "Capitala noua: ");

                printf("Suprafata noua: ");
                scanf("%lf", &temp->data.area);

                printf("Populatie noua: ");
                scanf("%u", &temp->data.population);

                printf("BIP nou: ");
                scanf("%lf", &temp->data.BIP);
                break;

            case 0:
                printf("Iesire editare.\n");
                break;

            default:
                printf("Optiune invalida.\n");
        }

    } while(option != 0);

    while (getchar() != '\n');
}

void switch_states(Node *head, int i, int j)
{
    if (!head) return;

    Node *node1 = NULL, *node2 = NULL;
    Node *temp = head;
    int index = 0;

    while (temp) {
        if (index == i) node1 = temp;
        if (index == j) node2 = temp;
        temp = temp->next;
        index++;
    }

    int len = list_length(head);

    if (!node1 || !node2 || i >= len || j >= len) {
        printf(COLOR_RED "Invalid indices.\n" COLOR_RESET);
        return;
    }

    State aux = node1->data;
    node1->data = node2->data;
    node2->data = aux;

    printf(COLOR_GREEN "Succsessfull swap process\n" COLOR_RESET);
}

void sort_states_list(Node *head)
{
    if (!head) return;

    int swapped;
    Node *ptr1;
    Node *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {

            if (strcmp(ptr1->data.nume,
                       ptr1->next->data.nume) > 0) {

                State temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;

                swapped = 1;
            }

            ptr1 = ptr1->next;
        }

        lptr = ptr1;

    } while (swapped);
}

void delete_state_list(Node **head, int index)
{
    if (!*head) {
        printf("Lista este goala.\n");
        return;
    }

    Node *temp = *head;

    // ștergere primul nod
    if (index == 0) {
        *head = temp->next;

        free(temp->data.nume);
        free(temp->data.capital);
        free(temp);

        return;
    }

    Node *prev = NULL;
    int current = 0;

    while (temp && current < index) {
        prev = temp;
        temp = temp->next;
        current++;
    }

    if (!temp) {
        printf("Invalid index.\n");
        return;
    }

    prev->next = temp->next;

    free(temp->data.nume);
    free(temp->data.capital);
    free(temp);
}

void save_to_file(ListArray *arr, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < arr->size; i++) {

        fprintf(f, "#LIST %s\n", arr->head_data[i].name_list);

        Node *temp = arr->head_data[i].address_list;

        while (temp) {
            fprintf(f, "%s;%s;%.2lf;%u;%.2lf\n",
                    temp->data.nume,
                    temp->data.capital,
                    temp->data.area,
                    temp->data.population,
                    temp->data.BIP);

            temp = temp->next;
        }

        fprintf(f, "\n"); // spațiu între liste
    }

    fclose(f);
    printf("Date salvate cu succes.\n");
}

void read_from_file(ListArray *arr, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Error opening file.\n");
        return;
    }

    arr->size = 0;  // resetăm sistemul

    char line[256];
    int currentIndex = -1;

    while (fgets(line, sizeof(line), f)) {

        if (strncmp(line, "#LIST", 5) == 0) {

            char listName[100];
            sscanf(line, "#LIST %99[^\n]", listName);

            createNewList(arr, listName);   // funcția ta de creare listă
            currentIndex = arr->size - 1;

            continue;
        }

        if (line[0] == '\n')
            continue;

        char nume[100], capital[100];
        double area, BIP;
        unsigned int population;

        if (sscanf(line, "%99[^;];%99[^;];%lf;%u;%lf",
                   nume, capital,
                   &area, &population, &BIP) == 5)
        {
            addNewItem(
                &arr->head_data[currentIndex].address_list,
                nume, capital, area, population, BIP
            );
        }
    }

    fclose(f);
    printf("Date incarcate cu succes.\n");
}

void split_list_array(ListArray *arr, int list_index)
{
    if (list_index < 0 || list_index >= arr->size) {
        printf("Invalid list index.\n");
        return;
    }

    Node *source = arr->head_data[list_index].address_list;

    if (!source) {
        printf("Lista este goala.\n");
        return;
    }

    char name1[100], name2[100];

    printf("Introdu numele primei liste: ");
    scanf("%99s", name1);

    printf("Introdu numele celei de-a doua liste: ");
    scanf("%99s", name2);

    // --- SPLIT ---
    Node *slow = source;
    Node *fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    Node *secondHalf = slow->next;
    slow->next = NULL;

    // Prima listă primește nume nou
    free(arr->head_data[list_index].name_list);
    arr->head_data[list_index].name_list = strdup(name1);

    // Creăm listă nouă
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->head_data = realloc(arr->head_data,
                                 arr->capacity * sizeof(HeadList));
    }

    arr->head_data[arr->size].name_list = strdup(name2);
    arr->head_data[arr->size].address_list = secondHalf;

    arr->size++;

    printf("Lista a fost divizata.\n");
}

void concatenate_lists_array(ListArray *arr,
                             int index1,
                             int index2)
{
    if (index1 < 0 || index2 < 0 ||
        index1 >= arr->size || index2 >= arr->size ||
        index1 == index2)
    {
        printf("Index invalid.\n");
        return;
    }

    Node *list1 = arr->head_data[index1].address_list;
    Node *list2 = arr->head_data[index2].address_list;

    if (!list2) {
        printf("Second list is empty.\n");
        return;
    }

    if (!list1) {
        arr->head_data[index1].address_list = list2;
    }
    else {
        Node *temp = list1;
        while (temp->next)
            temp = temp->next;

        temp->next = list2;
    }

    // redenumire lista
    char newName[MAX_STRING];
    printf("Enter new name for concatenated list: ");
    scanf("%s", newName);

    free(arr->head_data[index1].name_list);
    arr->head_data[index1].name_list = strdup(newName);

    free(arr->head_data[index2].name_list);

    for (int i = index2; i < arr->size - 1; i++)
        arr->head_data[i] = arr->head_data[i + 1];

    arr->size--;

    printf("Lists concatenated successfully.\n");
}

void free_list(Node* head)
{
    Node* temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;

        free(temp->data.nume);
        free(temp->data.capital);
        free(temp);
    }
}

void free_all(ListArray *arr)
{
    for (int i = 0; i < arr->size; i++) {
        free_list(arr->head_data[i].address_list);
        free(arr->head_data[i].name_list);
    }

    free(arr->head_data);
}

int list_length(Node *head)
{
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

Node* last_node(Node *head)
{
    if(!head) return NULL;

    while(head->next)
        head = head->next;

    return head;
}