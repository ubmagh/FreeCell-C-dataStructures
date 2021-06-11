#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED
#include "Card.h"


// Cell = Case (fr)
typedef struct _cell{
    Card *card;
    struct _cell *next;
} Cell;





Card ** Get1D_shuffeledCards( Card ***Cards_DB ); // Shuffles randomly 'Cards_DB' Cards that is a 2D array into a 1D array
void initiate_zones( Card ***Cards_DB, Cell ***zone1, Cell ***zone2, Cell ***zone3); // initiates zone 1 with random cards from Cards_DB ; zone 2 & zone 3 are empty
void free_zones( Cell ***zone1, Cell ***zone2, Cell ***zone3);
void push_card( Cell **cardStack, Card *card);
void show_zone( Cell **zone, int zoneNumber, int zoneSize);// zoneSize = number of cols
void show_all_zones( Cell **zone1, Cell **zone2, Cell **zone3);
int does_col_existsIn_zone( int col, int zone);
Card * peek_card(Cell *cardStack); // just getting the adress of the card in the head of the stack
int check_move_possibility(Cell **zone1, Cell **zone2, Cell **zone3, int, int, int, int);
Card * pop_card( Cell **cardStack );
void move_card(Cell **zone1, Cell **zone2, Cell **zone3, int, int, int, int);


#endif // CELL_H_INCLUDED
