#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    ListArray arr = initArrayOfLists();
    char option = '\0';

    print_border_info(">>> Welcome to LAB 2 - SDA <<<", '*');
    menu_info();

    while (option != '0')
    {
        for (int i = 0; i < 60; i++)
            printf("-");

        printf("\nInput menu option >>> ");
        scanf(" %c", &option);

        menu(&arr, option);
    }

    print_border_info("Bye Bye , nice to working with you :) ...", '*');

    free_all(&arr);

    printf("\nPress Enter for exit ...");
    getchar();

    return 0;
}
