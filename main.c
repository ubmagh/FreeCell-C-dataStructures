#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#ifdef _WIN32
#define WINDOWS 1
#else
#define WINDOWS 0
#endif

#include "Card.h"
#include "Cell.h"



void clrScrn();
int menu();
void collect_move_details( int *, int *, int *, int *);


Card ***Cards_DB;

/** every single zone is an array of stacks !  Remember this !! */
Cell **Zone1 ;
Cell **Zone2 ;
Cell **Zone3 ;




int main(){
    int choice=0, restart =0;
    int DepartZone, DepartCol; // Be careful DepartCol &
    int DestZone, DestCol;  // DestCol should be expressed later with 0->n-1 ; array indexe

startGame:
    Initiate_CardsDB( &Cards_DB); // creates cards
    initiate_zones( Cards_DB, &Zone1, &Zone2, &Zone3); // fills Zone1 with random cards
    restart = 0;
    while( 1 ){

        do{
            clrScrn();
            show_all_zones( Zone1, Zone2, Zone3);
            choice = menu();
        }while( choice <1 || choice >3 );
        switch(choice){
            case 1:
                clrScrn();
                show_all_zones( Zone1, Zone2, Zone3);
                choice =0;
                collect_move_details( &DepartZone, &DepartCol, &DestZone, &DestCol );

                if( !check_move_possibility( Zone1, Zone2, Zone3, DepartZone, DepartCol, DestZone, DestCol) )
                    printf("\n\t\t => deplacement impossible !");
                else{
                    // perform move
                    move_card( Zone1, Zone2, Zone3, DepartZone, DepartCol, DestZone, DestCol);
                    printf("\n\t\t => deplacement effectue !");
                }


                printf("\n\n\t\t\tAppuyez sur une touche pour continuer ..... \n");
                getch();
                // performe move and check possibility
            break;
            case 2:
                restart = 1;
                goto exitDoor;
                break;
            case 3:
                clrScrn();
                printf("\n\n\n\n\n\n\t\t\t ..:| GooD Bye |:..\n\n\n\n\n\n\n\n\n");
                goto exitDoor;
                break;
        }
    }
exitDoor:
    free_zones( &Zone1, &Zone2, &Zone3 );
    Free_CardsDB(&Cards_DB);
    if(restart)
        goto startGame;
    return 0;
}




int menu(){
    int i;
    printf("\n\n\t-------------------------------------Menu---------------------------------------");
    printf("\n\t\t 1: Deplacer une carte  |  2: Rejouer la partie  | 3: quitter");
    printf("\n\t--------------------------------------------------------------------------------\n\t\t votre choix est -> ");
    scanf(" %d", &i);
    return i;
}


void clrScrn(){
    if(WINDOWS)
        system("cls");
    else
        system("clear");
}


void collect_move_details( int *DepartZone, int *DepartCol, int *DestZone, int *DestCol ){
    printf("\n\t-------------------------------------------------------------------------------");
    printf("\n\t\t        Saisir les coordonnees de deplacement  ");
    printf("\n\t-------------------------------------------------------------------------------");
    do{
        printf("\n\n\t\t ::::::::> la carte a deplacer se trouve dans la zone : ");
        scanf(" %d", DepartZone);
    }while( (*DepartZone)<1 || (*DepartZone)>3 );
    do{
        printf("\t\t   =========> la carte a deplacer se trouve dans la case (col) : ");
        scanf(" %d", DepartCol);
    }while( !does_col_existsIn_zone( *DepartCol, *DepartZone) );

    do{
        printf("\n\t\t ::::::::> deplacer la carte a la zone : ");
        scanf(" %d", DestZone);
    }while( (*DestZone)<1 || (*DestZone)>3 );
    do{
        printf("\t\t   =========> mettre la carte dans la case (col) : ");
        scanf(" %d", DestCol);
    }while( !does_col_existsIn_zone( *DestCol, *DestZone) );
    printf("\n\t--------------------------------------------------------------------------------\n\t\t");
}



/**
    Useful links :

    - https://www.britannica.com/topic/playing-card


*/
