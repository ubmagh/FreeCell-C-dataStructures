#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Cell.h"



Card ** Get1D_shuffeledCards( Card ***Cards_DB){
    int i=0; // to travel the 'Shuffled' returned array
    int x, y; // abscissa & ordinate ; used to travel the Cards_DB vertically and horizontally
    Card *tmp = NULL;
    time_t t;
    srand( (unsigned) time(&t) );
    x = ( rand() * 14 ) %13; // randomly choosing starting card in the DB table
    y = ( rand() * 5 ) %4;
    Card **Shuffled = (Card **) malloc( 52 * sizeof(Card *) );
    while(i<52){    // taking cards diagonally and inserting them into shuffled array
        Shuffled[i] = Cards_DB[y][x];
        x++; x%=13; // moving
        y++; y%=4;  // diagonally
        i++;
    }
    // more shuffling
    for( i=0; i<52; i++){
        x = ( rand() * 47 )%52; // choosing two table cells
        y = ( rand() * 59 )%52; //  randomly to switch them
        tmp = Shuffled[x];
        Shuffled[x] = Shuffled[y];
        Shuffled[y] = tmp;
    }
    return Shuffled;
}

/*
    push random cards from Cards_DB inside ZONE 1 ; 4x 7Cards & 4x 6Cards
    while zone2 & zone 3 are empty
*/
void initiate_zones( Card ***Cards_DB, Cell ***zone1, Cell ***zone2, Cell ***zone3){

    int i,j,ii;
    Card ** Shuffled_Cards = Get1D_shuffeledCards( Cards_DB ); // returns array of all cards(52) shuffled

    *zone1 = (Cell **) malloc( 8 * sizeof( Cell* ) );
    *zone2 = (Cell **) malloc( 4 * sizeof( Cell* ) );
    *zone3 = (Cell **) malloc( 4 * sizeof( Cell* ) );

    printf("\n  => Debuging : Preparing zones ! \n");

    // set all stacks of zone 2 and zone 3 to NULL => they are empty initially
    for( i=0; i<8; i++)
        (*zone1)[i] = NULL;
    for( i=0; i<4; i++){
        (*zone2)[i] = NULL;
        (*zone3)[i] = NULL;
    }
    printf("\n  => Debuging : Pushing into ZOne1 ! \n");
    // push randomized cards into zone1 8 stacks
    j=0;
    for(i=0; i<4; i++) // cols 1 to 4 have 7 cards
        for( ; j<(7*(i+1)); j++) // pushing 7 cards
            push_card( &( (*zone1)[i] ), Shuffled_Cards[j]);
    // j in this line of execution has the value 7*4 +1 =29 => means 28 cards are inserted, the rest is 6 * 4 = 24
    //and i has the value : 4 means 5the case in zone 1, that will contain 6 cards (also cases 6,7,8)
    for ( ; i<8; i++){
        ii=0;
        while( ii<=5 ){
            push_card( &( (*zone1)[i] ), Shuffled_Cards[j+ii]);
            ii++;
        }
        j +=ii;
    }


    // zone1 should be initialised now


}


void free_zones( Cell ***zone1, Cell ***zone2, Cell ***zone3){
    /** ## TODO : Free Cells stacks   */
    // freeing stacks // Cells objects
    int i;
    Cell *tmp=NULL, *dest=NULL;
    for( i=0; i<8; i++){ /// Deallocating Zone 1
        if( ((*zone1)[i]) != NULL ){
            tmp = ( (*zone1)[i] );
            while(tmp!=NULL){
                dest = tmp;
                tmp = tmp->next;
                free( dest );
            }
        }
    }
    for( i=0; i<4; i++){ /// Deallocating Zone 2
        if( (*zone2)[i] != NULL ){
            tmp = ( (*zone2)[i] ) ;
            while(tmp!=NULL){
                dest = tmp;
                tmp = tmp->next;
                free( dest );
            }
        }
    }

    for( i=0; i<4; i++){ /// Deallocating Zone 3
        if( (*zone3)[i] != NULL ){
            tmp = ( (*zone3)[i] ) ;
            while(tmp!=NULL){
                dest = tmp;
                tmp = tmp->next;
                free( dest );
            }
        }
    }

    free( *zone1 );
    free( *zone2 );
    free( *zone3 );
    printf("\n  => Debuging : Zones Memory allocation Freed successfully ! \n");
}


void push_card( Cell **cardStack, Card *card){
    Cell * node = (Cell *) malloc( sizeof(Cell) );
    node->card = card;
    node->next = (*cardStack);
    *cardStack = node;
}

void show_zone( Cell **zone, int zoneNumber, int zoneSize){ // zoneSize = number of cols
    int i;
    Cell *tmp=NULL;
    printf("\n\n\t\t ====> Les cartes de la zone %d : \n", zoneNumber);
    for( i=0; i<zoneSize; i++ ){
        tmp=NULL;
        tmp = zone[i];
        printf("\n Col %d:   ", i+1);
        while( tmp!=NULL && tmp->next!=NULL ){
            show_Card( tmp->card);
            printf(" <-| ");
            tmp=tmp->next;
        }
        show_Card( tmp->card);
        printf(" ||");
    }
}
