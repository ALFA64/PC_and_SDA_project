#include <stdio.h>
#include "header.h"

int main(){
    StateArray arr = initStateArray();
    char option = '\0';

    print_border_info(">>> Wellcome to LAB 1 - SDA <<<",'*');
    menu_info();

    while (option != '0'){
        for(int i=0;i<60;i++)
            printf("-");
        printf("\nInput menu option >>>");
        scanf(" %c",&option);
        menu(&arr, option);
    }

    print_border_info("Bye Bye , nice to working with you :) ...",'*');
    freeStateArray(&arr);
    fflush(stdin);
    printf("\nPress Enter for exit ...");
    getchar();
    return 0;
}