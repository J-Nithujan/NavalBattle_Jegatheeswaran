/**
 * \file      main.c
 * \author    Nithujan Jegatheeswaran
 * \version   0.1
 * \date      11.12.20
 * \brief     A battleship game ??????????????????????
 *
 * \details    This game is made to be played in Windows' command prompt
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/**Global variables**/
int userInputs[10][10];
char gameGrid[10][10];

int allBoats = 5;
int boat5[5][2] = {{3, 5/*-1*/}, ///!!!!!!!!!!!!!!!!
                   {3, 6},
                   {3, 7},
                   {3, 8},
                   {3, 9}}; //D=3

int boat4[4][2] = {{1, 2},
                   {1, 3},
                   {1, 4},
                   {1, 5}}; //B=1

int boat3_1[3][2] = {{4, 1},    //E=4
                     {5, 1},    //F=5
                     {6, 1}};   //G=6

int boat3_2[3][2] = {{7, 3},
                     {7, 4},
                     {7, 5}};   //H=7

int boat2[2][2] = {{6, 7},  //G=6
                   {7, 7}}; //H=7

int boat5Health = 4;
int boat4Health = 3;
int boat3_1Health = 2;
int boat3_2Health = 2;
int boat2Health = 1;

int choice = 0;


/**Fonctions**/

/** \brief emptyBuffer - This function clears the memory used by the scanf function
 * \return
 *
 */
void emptyBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void boat5End() {
    //Fonction made to sink boat5
}

void boat4End() {

}

void boat3_1End() {

}

void boat3_2End() {

}

void boat2End() {

}

/** \brief showHelp - This function explains the game to the user
 * \return
 *
 */
void showHelp() {
    do {

        printf("===========\n"
               "Aide de jeu\n"
               "===========\n\n"
               "Le but du jeu est de couler tous les bateaux.\n"
               "Pour ce faire il faut tirer sur une des cases du tableau en indiquant une coordonnée.\n"
               "Répétez cette opération jusqu'à ce que tous les bateaux soient coulées\n\n"
               "État des cases:\n"
               "---------------\n"
               "Case inconnue: ?\n"
               "Ratée: ~\n"
               "Touchée: X\n"
               "Coulée: O\n"
               "\n=====================\n"
               "Lancer une partie (1)\n"
               "=====================\n");

        scanf("%d", &choice);


        if (choice != 1) {
            printf("UTILISEZ LA TOUCHE 1 POUR LANCER UNE PARTIE\n\n");
        }

        emptyBuffer();

    } while (choice != 1);
}

///ATTENTION GLOBALISATION DES COORDONNÉES DES BATEAU

/** \brief gameGridChanges - This function shows the result for the user's input entered in the game function
 * \return void
 *
 */
void gameGridChanges(char vertical, int horizontal) {
    int trueVertical = vertical - 97;
    int trueHorizontal = horizontal -1;

    if (userInputs[vertical - 97][horizontal]) {

        userInputs[vertical - 65][horizontal] = 0;

        switch (vertical) {
            case 'B':

                for (int i = 0; i < 4; ++i) {
                    if (horizontal == boat4[i][1] && boat4Health != 0) {
                        printf("========\n"
                               "TOUCHÉ !\n"
                               "========\n\n");

                        gameGrid[(int) (vertical) - 65][horizontal - 1] = 'X';
                        --boat4Health;

                        return;

                    } else if (horizontal == boat4[i][1]) {
                        printf("===============\n"
                               "TOUCHÉ, COULÉ !\n"
                               "===============\n\n");

                        for (int j = boat4[0][1] - 1; j < boat4[3][1]; ++j) {
                            gameGrid[1][j] = '0';
                        }

                        --allBoats;

                        return;
                    }
                }

                printf("=======\n"
                       "PLOUF !\n"
                       "=======\n\n");

                gameGrid[(int) (vertical) - 65][horizontal - 1] = '~';

                break;

            case 'D':

                for (int i = 0; i < 5; ++i) {
                    if (horizontal == boat5[i][1] && boat5Health != 0) {
                        printf("========\n"
                               "TOUCHÉ !\n"
                               "========\n\n");

                        gameGrid[(int) (vertical) - 65][horizontal - 1] = 'X';
                        --boat5Health;

                        return;

                    } else if (horizontal == boat5[i][1]) {
                        printf("===============\n"
                               "TOUCHÉ, COULÉ !\n"
                               "===============\n\n");

                        /*boat5End();
                        */
                        gameGrid[3][4] = 'O';
                        gameGrid[3][5] = 'O';
                        gameGrid[3][6] = 'O';
                        gameGrid[3][7] = 'O';
                        gameGrid[3][8] = 'O';

                        --allBoats;

                        return;
                    }
                }

                printf("=======\n"
                       "PLOUF !\n"
                       "=======\n\n");

                gameGrid[(int) (vertical) - 65][horizontal - 1] = '~';

                break;

            case 'E':

                if (horizontal == boat3_1[0][1] && boat3_1Health != 0) {
                    printf("========\n"
                           "TOUCHÉ !\n"
                           "========\n\n");

                    gameGrid[(int) (vertical) - 65][horizontal - 1] = 'X';
                    --boat3_1Health;

                    break;

                } else if (horizontal == boat3_1[0][1]) {
                    printf("===============\n"
                           "TOUCHÉ, COULÉ !\n"
                           "===============\n\n");

                    for (int i = boat3_1[0][1] - 1; i < boat3_1[2][1]; ++i) {
                        gameGrid[i][0] = '0';
                    }
                    /*
                    gameGrid[4][0] = 'O';
                    gameGrid[5][0] = 'O';
                    gameGrid[6][0] = 'O';
                    */
                    --allBoats;

                    break;
                }

                printf("=======\n"
                       "PLOUF !\n"
                       "=======\n\n");

                gameGrid[(int) (vertical) - 65][horizontal - 1] = '~';

                break;

            case 'F':

                if (horizontal == boat3_1[1][1] && boat3_1Health != 0) {
                    printf("========\n"
                           "TOUCHÉ !\n"
                           "========\n\n");

                    gameGrid[(int) (vertical) - 65][horizontal - 1] = 'X';
                    --boat3_1Health;

                    break;

                } else if (horizontal == boat3_1[1][1]) {
                    printf("===============\n"
                           "TOUCHÉ, COULÉ !\n"
                           "===============\n\n");

                    for (int i = boat3_1[0][1] - 1; i < boat3_1[2][1]; ++i) {
                        gameGrid[i][0] = '0';
                    }
                    gameGrid[4][0] = 'O';
                    gameGrid[5][0] = 'O';
                    gameGrid[6][0] = 'O';

                    --allBoats;

                    break;
                }

                printf("=======\n"
                       "PLOUF !\n"
                       "=======\n\n");

                gameGrid[(int) (vertical) - 65][horizontal - 1] = '~';

                break;

            case 'G':

                if (horizontal == boat3_1[2][1] && boat3_1Health != 0) {
                    printf("=========\n"
                           "TOUCHÉ !\n"
                           "=========\n\n");

                    gameGrid[(int) (vertical) - 65][horizontal - 1] = 'X';
                    --boat3_1Health;

                    break;

                } else if (horizontal == boat3_1[2][1]) {
                    printf("===============\n"
                           "TOUCHÉ, COULÉ !\n"
                           "===============\n\n");

                    gameGrid[4][0] = 'O';
                    gameGrid[5][0] = 'O';
                    gameGrid[6][0] = 'O';

                    --allBoats;

                    break;
                }

                if (horizontal == boat2[0][1] && boat2Health != 0) {
                    printf("=========\n"
                           "TOUCHÉ !\n"
                           "=========\n\n");

                    gameGrid[(int) (vertical) - 65][horizontal - 1] = 'X';
                    --boat2Health;

                    break;

                } else if (horizontal == boat2[0][1]) {
                    printf("===============\n"
                           "TOUCHÉ, COULÉ !\n"
                           "===============\n\n");

                    gameGrid[6][6] = 'O';
                    gameGrid[7][6] = 'O';

                    --allBoats;

                    break;
                }

                printf("=======\n"
                       "PLOUF !\n"
                       "=======\n\n");

                gameGrid[(int) (vertical) - 65][horizontal - 1] = '~';

                break;

            case 'H':

                for (int i = 0; i < 3; ++i) {

                    if (horizontal == boat3_2[i][1] && boat3_2Health != 0) {
                        printf("=========\n"
                               "TOUCHÉ !\n"
                               "=========\n\n");

                        gameGrid[(int) (vertical) - 65][horizontal - 1] = 'X';
                        --boat3_2Health;

                        return;

                    } else if (horizontal == boat3_2[i][1]) {
                        printf("===============\n"
                               "TOUCHÉ, COULÉ !\n"
                               "===============\n\n");

                        gameGrid[7][3] = 'O';
                        gameGrid[7][4] = 'O';
                        gameGrid[7][5] = 'O';

                        --allBoats;

                        return;
                    }
                }


                if (horizontal == boat2[1][1] && boat2Health != 0) {
                    printf("=========\n"
                           "TOUCHÉ !\n"
                           "=========\n\n");

                    gameGrid[(int) (vertical) - 65][horizontal - 1] = 'X';
                    --boat2Health;

                    break;

                } else if (horizontal == boat2[1][1]) {
                    printf("===============\n"
                           "TOUCHÉ, COULÉ !\n"
                           "===============\n\n");

                    gameGrid[6][6] = 'O';
                    gameGrid[7][6] = 'O';

                    --allBoats;

                    break;
                }

                printf("=======\n"
                       "PLOUF !\n"
                       "=======\n\n");

                gameGrid[(int) (vertical) - 65][horizontal - 1] = '~';

                break;

            default:
                printf("======\n"
                       "PLOUF!\n"
                       "======\n\n");

                gameGrid[(int) (vertical) - 65][horizontal - 1] = '~';

        }
    } else {
        printf("====================\n"
               "CASE DÉJÀ ENTRÉE !!!\n"
               "====================\n\n");
    }
}

/** \brief game - This function
 * \return
 *
 */
void game() {

    char selectedCoordinate[2] = "";

    do {
        int horizontalHeader[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        char verticalHeader[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

        int horizontalCoordinate = 0;
        char verticalCoordinate = '0';

        printf("%4c", ' ');

        for (int i = 0; i < 10; ++i) {
            printf("%6d", horizontalHeader[i]);
        }

        printf("\n%4c", ' ');

        for (int i = 0; i < 10; ++i) {
            printf("%3c%3c", 'v', '-');
        }

        printf("%2c\n%4c\n", 'v', '>');

        for (int i = 0; i < 10; ++i) {
            printf("%2c", verticalHeader[i]);
            printf("%2c", '|');

            for (int j = 0; j < 10; ++j) {
                printf("%6c", gameGrid[i][j]);
            }

            printf("\n%4c\n", '>');
        }

        printf("\n");

        do {
            printf("Veuillez entrer une coordonnée vertical (a-j, en minuscule!):\n");
            scanf("%c", &verticalCoordinate);

            emptyBuffer();

        } while (verticalCoordinate < 97 || verticalCoordinate > 106); //I used the ASCII table 97:a, 106:j

        do {

            printf("Veuillez entrer une coordonnée horizontale (1-10):\n");
            scanf("%d", &horizontalCoordinate);

            emptyBuffer();

        } while (horizontalCoordinate < 1 || horizontalCoordinate > 10);

        sprintf(selectedCoordinate, "%c%d", verticalCoordinate, horizontalCoordinate);
        printf("\nCase choisie: %s\n", selectedCoordinate);

        gameGridChanges(verticalCoordinate, horizontalCoordinate);

    } while (allBoats != 0);

    printf("VICTOIRE !!!\n");

}



/**Will be updated and used in v1.0*/
/** \brief mainMenu - This function shows the main menu of the game and bring the user to the selected place
 * \return void
 *
 */
/*void mainMenu()
{
    do {

        printf("===============\nBataille Navale\n===============\n"
               "Nouvelle partie (1)\n"
               "Aide (2)\n"
               "Quitter(3)\n"
               "==============\n");
        scanf("%d", &choice);

        if (choice != 1 && choice != 2 && choice != 3 )
        {
            printf("VEUILLEZ FAIRE UN CHOIX AVEC LES TOUCHES 1, 2 OU 3 !!!\n\n");
        }

        emptyBuffer();
    }while (choice != 1 && choice != 2 && choice != 3 );

    switch (choice)
    {

        case 1:
            game();
            break;

        case 2:
            showHelp();
            break;

        case 3:
            system("exit");
            break;

    }

    return;
}*/



/** \brief main - This function is the program's entry point
 * \return an int different from 0 if abnormal termination
 *
 */
int main() {
    SetConsoleOutputCP(CP_UTF8);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            gameGrid[i][j] = '?';
            userInputs[i][j] = 1;
        }
    }

    /*showHelp();*/
    game();

    system("pause");

    return 0;
}
