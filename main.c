#include <stdio.h>
#include <stdlib.h>

#include "Card.h"
#include "Cell.h"

Card ***Cards_DB;

/** every single zone is an array of stacks !  Remember this !! */
Cell **Zone1 ;
Cell **Zone2 ;
Cell **Zone3 ;

int main(){
    Initiate_CardsDB( &Cards_DB); // creates cards
    initiate_zones( Cards_DB, &Zone1, &Zone2, &Zone3); // fills Zone1 with random cards

    printf("\n\n ");


    show_zone( Zone1, 1, 8);

    printf("\n\n ");



    free_zones( &Zone1, &Zone2, &Zone3 );
    Free_CardsDB(&Cards_DB);
    return 0;
}


/**
    Useful links :

    - https://www.britannica.com/topic/playing-card


*/
