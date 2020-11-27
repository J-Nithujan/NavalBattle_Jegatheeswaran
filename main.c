/****************************************
*   Title   :   NavalBattle             *
*   Author  :   Jegatheeswaran Nithujan *
*   Version :   [27-11-2020] v0.1       *
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/**Global variables**/
int gameBoard[10][10];
int choice = 0;

/**Fonctions**/
//In-game help
void showHelp() {
    printf("Aide de jeu\n===========\n"
           "Le but du jeu est de couler tous les bateaux.\n"
           "Pour ce faire il faut tirer sur une des cases du tableau en indiquant une coordonnée.\n"
           "Répéter cette opération jusqu'à ce que tous les bateaux soient coulées\n\n"
           "État des cases:\n"
           "Ratée: ~\n"
           "Touchée: X\n"
           "Coulée: O\n===========\n"
           "Retour (0)\n");
    scanf("%d", choice);
    return;
}


void gameBoardMaker() {

    for (int i = 0; i < 10; ++i) {

    }


    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%d", gameBoard[i][j]);
        }
        printf("\n");
    }
    return;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    printf("Bataille Navale\n==============\n"
           "Nouvelle partie (1)\n"
           "Aide (2)\n"
           "Quitter(3)\n"
           "==============\n");
    scanf("%d", &choice);


    switch (choice) {
        case 1:;
            printf("Work in progress\n");
            break;
        case 2:
            showHelp();
            break;
        case 3:
            system("exit");
            break;
        default:
            printf("Error");
            break;
    }


    return 0;
}
