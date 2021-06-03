#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Card.h"




void Initiate_CardsDB( Card ****Cards_DB){
    int i, j;
    char types [4][10];
    strcpy( types[0], "piques"); /*piques, coeurs, carreaux, trèfles —known in English as spades, hearts, diamonds, clubs*/
    strcpy( types[1], "coeurs");
    strcpy( types[2], "carreaux");
    strcpy( types[3], "trefles");
    j= (rand()*7)%4;

    *Cards_DB = ( Card ***) malloc( 4 * sizeof( Card ** ) ); // memory allocation

    for( i=0; i<4; i++)
        (*Cards_DB)[i] = ( Card **) malloc( 13 * sizeof( Card * ) );


    for( i=0; i<13; i++ ){
       (*Cards_DB)[0][i] = new_Card( i+1, types[j]);
    }
    j++; j%=4;


    for( i=0; i<13; i++ ){
       (*Cards_DB)[1][i] = new_Card( i+1, types[j]);
    }
    j++; j%=4;

    for( i=0; i<13; i++ ){
       (*Cards_DB)[2][i] = new_Card( i+1, types[j]);
    }
    j++; j%=4;

    for( i=0; i<13; i++ ){
       (*Cards_DB)[3][i] = new_Card( i+1, types[j]);
    }

}

void Free_CardsDB(Card ****Cards_DB){
    int i, ii;
    for ( i=0; i<4; i++)
        for( ii=0; ii<13; ii++)
            free( (*Cards_DB)[i][ii] ); // freeing card object
    for( i=0; i<4; i++)
        free( (*Cards_DB)[i] ); // freeing 13 length 4 tables
    free( *Cards_DB ); // freeing 4 length table
    printf("\n  => Debuging : Cards Memory allocation Freed successfully ! \n");
}

Card * new_Card( int num, char type[10]){
    Card * card = ( Card *) malloc( sizeof(Card) );
    card->num = num;
    strcpy( card->type, type);
    return card;
}

void show_Card( Card *card){
    printf("%d-%s", card->num, card->type);
}
