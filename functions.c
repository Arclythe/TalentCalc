#include "functions.h"

void checkInput(int * absNum){
    int32_t numToBeCheck;
    while(1){
        scanf("%d",&numToBeCheck);
        if(numToBeCheck < 1 || numToBeCheck > 10){
            printf("Oops! %d is an invalid Number... Try again :)\n",numToBeCheck);
        } else {
            *absNum = numToBeCheck;
            return;
        }
    }
    
}

void printBooks(Booksset * books){
    printf("**: %d\n",books->common);
    printf("***: %d\n",books->rare);
    printf("****: %d\n",books->epic);
}

Booksset * createBookSet(){
    Booksset * pBook = NULL;
    pBook = (Booksset*) malloc (sizeof(Booksset));

    pBook->common = 0;
    pBook->rare = 0;
    pBook->epic = 0;

    return pBook;
}

Booksset * combineBooks(Booksset * bs1, Booksset * bs2, Booksset * bs3){
    Booksset * result = createBookSet();
    result->common = bs1->common + bs2->common + bs3->common;
    result->rare = bs1->rare + bs2->rare + bs3->rare;
    result->epic = bs1->epic + bs2->epic + bs3->epic;

    free(bs1);
    free(bs2);
    free(bs3);

    return result;

}

static void analyzeLvl(uint8_t level, Booksset * inputSet){
    switch(level){
        case 1:
            break;
        case 2:
            inputSet->common += 3;
            break;
        case 3:
            inputSet->rare += 2;
            break;
        case 4:
            inputSet->rare += 4;
            break;
        case 5:
            inputSet->rare += 6;
            break;
        case 6:
            inputSet->rare += 9;
            break;
        case 7:
            inputSet->epic += 4;
            break;
        case 8:
            inputSet->epic += 6;
            break;
        case 9:
            inputSet->epic += 12;
            break;
        case 10:
            inputSet->epic += 16;
            break;
        default:
            break;
    } 
}

Booksset * evolve(uint8_t from, uint8_t till){
    Booksset * currentSet = createBookSet();

    for(int i = from+1; i <= till; i++){
        analyzeLvl(i, currentSet);
    }
    return currentSet;
}

void subtract(Booksset * totalBooks, Booksset * ownedBooks){
    totalBooks->common -= ownedBooks->common;
    totalBooks->rare -= ownedBooks->rare;
    totalBooks->epic -= ownedBooks->epic;
}


static uint16_t convertTillLowerLim(uint16_t * lowerGrade, uint16_t * higherGrade, uint16_t lowGradeLimit){
    uint16_t conversionCount = 0;
    while(1){
        if(*lowerGrade < 3 || *lowerGrade - 3 < lowGradeLimit){
            return conversionCount;
        }
        *lowerGrade -=3;
        *higherGrade +=1;
        conversionCount++;
    }
    return conversionCount;
}

static uint16_t convertTillUpperLim(uint16_t * lowerGrade, uint16_t * higherGrade, uint16_t highGradeLimit){
    uint16_t conversionCount = 0;
    while(1){
        if(*lowerGrade < 3 || *higherGrade >= highGradeLimit){
            return conversionCount;
        }
        *lowerGrade -=3;
        *higherGrade +=1;
        conversionCount++;
    }
    return conversionCount;
}

static bool prognose(Booksset * demandedBooks, Booksset * ownedBooks, uint16_t * silversToMake, uint16_t * goldsToMake){
    *silversToMake = convertTillLowerLim(&ownedBooks->common, &ownedBooks->rare, demandedBooks->common);
    *goldsToMake = convertTillUpperLim(&ownedBooks->rare, &ownedBooks->epic, demandedBooks->epic);

    bool bronzeEnough = ownedBooks->common >= demandedBooks->common;
    bool goldEnough = ownedBooks->epic >= demandedBooks->epic;
    bool silverEnough = ownedBooks->rare >= demandedBooks->rare;

    if(goldEnough && silverEnough && bronzeEnough){
        return true;
    }
    
    return false;
}

void calculate(Booksset * demandedBooks, Booksset * ownedBooks){

    uint16_t silversToMake = 0;
    uint16_t goldsToMake = 0;

    bool result = prognose(demandedBooks, ownedBooks, &silversToMake, &goldsToMake);
    
    bool bronzeEnough = ownedBooks->common >= demandedBooks->common;
    bool goldEnough = ownedBooks->epic >= demandedBooks->epic;
    bool silverEnough = ownedBooks->rare >= demandedBooks->rare;
    

    if(result){
        printf("Congratulations! No need farm more!\n\n");
        if(silversToMake != 0){
            printf("You'd need to convert bronze->silver books %d times\n",silversToMake);
        }
        if(goldsToMake != 0){
            printf("You'd need to make silver->gold books %d times\n",goldsToMake);
        }
        printf("\n");
        printf("After that you'd have the following books remaining:\n");
        printf("2 Star Book: %d\n",ownedBooks->common - demandedBooks->common);
        printf("3 Star Book: %d\n",ownedBooks->rare - demandedBooks->rare);
        printf("4 Star Book: %d\n",ownedBooks->epic - demandedBooks->epic);
        
    } else {
        printf("alright, assuming you're converting all ** into *** first, then converting *** to ****,\ntill your **** book reached %d:\n\n",demandedBooks->epic);

        if(!bronzeEnough){
            printf("You'll need %d more of ** books left\n",demandedBooks->common - ownedBooks->common);
        }
        if(!silverEnough){
            printf("You'll need %d more of *** books left\n",demandedBooks->rare - ownedBooks->rare);
        }
        if(!goldEnough){
            printf("You'll need %d more of **** books left\n",demandedBooks->epic - ownedBooks->epic);
        }
       

        printf("\n");

        uint16_t dummyS = 0;
        uint16_t dummyG = 0;

        int i = 0;

        while(!prognose(demandedBooks,ownedBooks,&dummyS,&dummyG)){
            i++;
            ownedBooks->common += 2;
            ownedBooks->rare += 2;            
        }
        printf("At your worst luck, you'd need to farm the domain %d times. (Assuming using 20 resin per collect)\n",i);
        printf("or, equivalent of %d resins\n",i*20);
    }
}


