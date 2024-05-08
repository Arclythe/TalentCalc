#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include "functions.h"

#define clrscr() printf("\e[1;1H\e[2J")

int main(){

    while(1){
        //start here
        printf("Genshin Weapon Mats Calculator by Maverick\n\n");

        Booksset * ist = createBookSet();
        //error handler here
        printf("Enter the how many ** mats do you have: ");
        scanf("%d",&ist->common);

        //error handler here
        printf("Enter the how many *** mats do you have: ");
        scanf("%d",&ist->rare);

        //error handler here
        printf("Enter the how many **** mats do you have: ");
         scanf("%d",&ist->epic);

        printf("\n\n");
        
        Booksset * soll = createBookSet();
        //error handler here
        printf("Enter the level of your desired **: ");
        scanf("%d",&soll->common);

        printf("Enter the level of your desired ***: ");
        scanf("%d",&soll->rare);

        printf("Enter the level of your desired ****: ");
        scanf("%d",&soll->epic);


        printf("\n");
    
      

        printf("\n\n");

        calculate(soll,ist);

        printf("\n\n\n\n\n");

        //resets memory
        free(soll);
        free(ist);


        printf("Press any key to restart...");
        getch();

        

        
        clrscr();

    }
}