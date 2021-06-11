#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Card.h"

char spades[10] = "piques";
char hearts[10] = "coeurs";
char diamonds[10] = "carreaux";
char clubs[10] = "trefles";


void Initiate_CardsDB( Card ****Cards_DB){
    int i, j;
    char types [4][10];
    strcpy( types[0], spades); /*piques, coeurs, carreaux, trèfles —known in English as spades, hearts, diamonds, clubs*/
    strcpy( types[1], hearts);
    strcpy( types[2], diamonds);
    strcpy( types[3], clubs);
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
}

Card * new_Card( int num, char type[10]){
    Card * card = ( Card *) malloc( sizeof(Card) );
    card->num = num;
    strcpy( card->type, type);
    return card;
}

void show_Card( Card *card){
    switch(card->num){
        case 13:
            printf("K"); break;
        case 12:
            printf("Q"); break;
        case 11:
            printf("J"); break;
        case 1:
            printf("A"); break;
        default:
            printf("%d",card->num);
    }
    printf("-%s", card->type);
}

int cards_match_2to1( Card *c1, Card *c2){
    if( strcmp( c1->type, c2->type) )
        return 0;
    if( strcmp( c1->type, spades) || strcmp( c1->type, clubs) )
        return ( (int) ( strcmp(c2->type, hearts) || strcmp( c2->type, diamonds) ) );
    if( strcmp( c1->type, hearts) || strcmp( c1->type, diamonds) )
        return ( (int) ( strcmp(c2->type, spades) || strcmp( c2->type, clubs) ) );
    return 0;
}
