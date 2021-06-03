#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

typedef struct {
    //char color;   // B : black, R : red
    int num;       // 1-13
    char type[10];   // "spades" (fr: pique), "hearts"(fr: coeur), "diamonds"(fr: carreaux)[ maxlength = 8 + 1 ('\0') ], "clubs"(fr: trefle)
} Card;

void Initiate_CardsDB( Card ****Cards_DB); // Fills Cards DB Table, with play cards // memory allocation
void Free_CardsDB( Card ****Cards_DB); // Frees dynamically allocated memory
Card * new_Card( int num, char type[9]); // creates Card
void show_Card( Card *card);



#endif // CARD_H_INCLUDED
