#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include "functions.h"

int main(){
    //start here
    printf("Genshin Mats Calculator by Maverick B-)\nRelease 14.04.2024\n\n");

    
    //error handler here
    printf("Enter the level of your chara's NA: ");
    int naStart = 1;
    checkInput(&naStart);
   
    // printf("naStart is: %d\n",naStart);

    //error handler here
    printf("Enter the level of your chara's E: ");
    int eStart = 1;
    checkInput(&eStart);

    //error handler here
    printf("Enter the level of your chara's Q: ");
    int qStart = 1;
    checkInput(&qStart);

    printf("\n\n");
    
    //error handler here
    printf("Enter the level of your desired chara's NA: ");
    int naEnd = 1;
    checkInput(&naEnd);

    printf("Enter the level of your desired chara's E: ");
    int eEnd = 1;
    checkInput(&eEnd);

    printf("Enter the level of your desired chara's Q: ");
    int qEnd = 1;
    checkInput(&qEnd);

    printf("\n");
    

   

    Booksset * naBooks = createBookSet();
    naBooks = evolve(naStart,naEnd);

    Booksset * eBooks = createBookSet();
    eBooks = evolve(eStart,eEnd);

    Booksset * qBooks = createBookSet();
    qBooks = evolve(qStart,qEnd);

    Booksset * totalBooks = createBookSet();
    totalBooks = combineBooks(naBooks, eBooks, qBooks);

    printf("\n");

    printf("So this is your plan, check if everything is in order:\n");
    printf("Normal Attack:  lvl.%2d -> %2d\n",naStart,naEnd);
    printf("Elemental Skill:lvl.%2d -> %2d\n",eStart,eEnd);
    printf("Burst Skill:    lvl.%2d -> %2d\n",qStart,qEnd);

    
    printf("\nSooo, the required books are: \n");
    printBooks(totalBooks);
    printf("\n\n");

    Booksset * ownedBooks = createBookSet();
    
    printf("Enter how many books do you have (2 star): ");
    scanf("%d",&ownedBooks->common);
    printf("Enter how many books do you have (3 star): ");
    scanf("%d",&ownedBooks->rare);
    printf("Enter how many books do you have (4 star): ");
    scanf("%d",&ownedBooks->epic);

    printf("\n\n");

    

    calculate(totalBooks,ownedBooks);


    printf("\n");

    printf("Press any key to exit...");
    getch();
    
}