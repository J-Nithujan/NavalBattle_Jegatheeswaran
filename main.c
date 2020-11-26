/****************************************
*   Title   :   NavalBattle   *
*   Author  :   Jegatheeswaran Nithujan      *
*   Version :   [26-11-2020]            *
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/**Global variables**/
char board[10][10];

/**Fonctions**/
//In-game help
void help(){
    printf("Aide de jeu\n===========\n\n"
           "Le but du jeu est de couler tous les bateaux.\n"
           "Pour ce faire il faut tirer sur une des cases du tableau en indiquant une coordonnée.\n"
           "Répéter cette opération jusqu'à ce que tous les bateaux soient coulées\n\n"
           "État des cases:\n"
           "Ratée: ~\n"
           "Touchée: X\n"
           "Coulée: O\n===========\n"
           "Quitter (0)\n");
    return;
}
/*
int mainMenu(){
    int choice = 0;
    printf("Bataille Naval\n==============\n\n"
           "Nouvelle partie (1)\n"
           "Aide (2)\n===========\n"
           "Quitter(0)\n");
    scanf("%d", &choice);
    return choice; //A TESTER
}
 */

int gameBoard(){

    return board;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);



    return 0;
}
