#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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



    // set all stacks of zone 2 and zone 3 to NULL => they are empty initially
    for( i=0; i<8; i++)
        (*zone1)[i] = NULL;
    for( i=0; i<4; i++){
        (*zone2)[i] = NULL;
        (*zone3)[i] = NULL;
    }

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
    printf("\n\t\t ====> Les cartes de la zone %d : ", zoneNumber);
    for( i=0; i<zoneSize; i++ ){
        tmp=NULL;
        tmp = zone[i];
        printf("\n Col %d:   ", i+1);
        if(tmp!=NULL){
            while( tmp!=NULL && tmp->next!=NULL ){
                show_Card( tmp->card);
                printf("  <|  ");
                tmp=tmp->next;
            }
            show_Card( tmp->card);
        }
        printf(" ||");
    }
    printf("\n");
}

void show_all_zones( Cell **zone1, Cell **zone2, Cell **zone3){
    show_zone( zone3, 3, 4);
    show_zone( zone2, 2, 4);
    show_zone( zone1, 1, 8);
}


int does_col_existsIn_zone( int col, int zone){
    switch(zone){
    case 1:
        return ( (int) (col>0 && col<9) );
    case 2:
        return ( (int) (col>0 && col<5) );
    case 3:
        return ( (int) (col>0 && col<5) );
    default:
        return 0;
    }
}

Card * peek_card(Cell *cardStack){
    if( cardStack==NULL || cardStack->card==NULL)
        return NULL;
    return cardStack->card;
}


int check_move_possibility(Cell **zone1, Cell **zone2, Cell **zone3, int DepartZone, int DepartCol, int DestZone, int DestCol){

    Card * DepartCard=NULL, *DestCard=NULL;
    Cell ** DepZone=NULL, **DesZone=NULL;

    if( DepartZone == 1 )
        DepZone = zone1;
    else
        if( DepartZone==2 )
            DepZone = zone2;
        else
            return 0; // it is not allowed to take cards from zone3

    if( DestZone == 1 )
        DesZone = zone1;
    else
        if( DestZone==2 )
            DesZone = zone2;
        else
            DesZone = zone3;

    DepartCard = peek_card( DepZone[DepartCol-1] );
    DestCard = peek_card( DesZone[DestCol-1] );


    if( DestZone==2  ){
        if(DestCard!=NULL)
            return 0;
    }
    else{
        if( DestZone == 3){
            if( DestCard!=NULL && DepartCard->num!=1 )
                return 0;
            if(DestCard!=NULL)
            if( ( DestCard->num != (DepartCard->num-1) ) || !strcmp( DestCard->type, DepartCard->type)  )
                return 0;
        }
        else{
            if( DestCard->num != (DepartCard->num+1) )
            return 0;

            if( !cards_match_2to1( DestCard, DepartCard) )
                return 0;
        }
    }
    return 1;
}

Card * pop_card( Cell **cardStack ){
    Card *node =NULL;
    Cell * dest = (*cardStack);
    if(cardStack!=NULL){
        node = (*cardStack)->card;
        (*cardStack) = (*cardStack)->next;
        free(dest);
    }
    else
    (*cardStack) = NULL;
    return node;
}


void move_card(Cell **zone1, Cell **zone2, Cell **zone3, int DepartZone, int DepartCol, int DestZone, int DestCol){
    Card * card =NULL;

    // pick the card
    if( DepartZone == 1 )
        card = pop_card( &(zone1[DepartCol-1]) );
    else if( DepartZone==2 )
        card = pop_card( &(zone2[DepartCol-1]) );
    else return;

    // put the card
    if( DestZone==1 )
        push_card( &(zone1[DestCol-1]), card);
    else if( DestZone==2 )
        push_card( &(zone2[DestCol-1]), card);
    else
        push_card( &(zone3[DestCol-1]), card);
}
