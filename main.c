/**
 * \file      main.c
 * \author    Nithujan Jegatheeswaran
 * \version   0.1
 * \date      13.12.20
 * \brief     A battleship game
 *
 * \details    The game is made to be played in Windows' command prompt and has only one grid of ships.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/**Global variables**/
int userInputs[10][10];
char gameGrid[10][10];

int allBoats = 5;
int boat5[5][2] = {{3, 4},
                   {3, 5},
                   {3, 6},
                   {3, 7},
                   {3, 8}}; //D=3

int boat4[4][2] = {{1, 1},
                   {1, 2},
                   {1, 3},
                   {1, 4}}; //B=1

int boat31[3][2] = {{4, 0},    //E=4
                    {5, 0},    //F=5
                    {6, 0}};   //G=6

int boat32[3][2] = {{7, 2},
                    {7, 3},
                    {7, 4}};   //H=7

int boat2[2][2] = {{6, 6},  //G=6
                   {7, 6}}; //H=7

int boat5Health = 4;
int boat4Health = 3;
int boat31Health = 2;
int boat32Health = 2;
int boat2Health = 1;

int choice = 0;

int score = 0;



/**Fonctions**/

/** \brief emptyBuffer - This function helps avoiding infinite loops in the scanf() function
 * \return void
 *
 */
void emptyBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

/** \brief showHelp - This function displays the explanation of the game to the user
 * \return void
 *
 */
void displayHelp() {
    do {

        printf("/-----------\\\n"
               " Aide de jeu\n"
               "\\-----------/\n\n"
               "Le but du jeu est de couler tous les navires cachés dans une grille.\n"
               "Pour faire cela il faut tirer sur une des cases de la grille en indiquant une coordonnée.\n"
               "Répétez cette opération jusqu'à ce que tous les navires soient coulés\n\n"
               "Score:\n"
               "------\n"
               "Raté: -50pts | Touché: 100pts | Touché-coulé: 250pts | Déjà tiré: -75pts\n\n"
               "État des cases:\n"
               "---------------\n"
               "Case inconnue: ?\n"
               "Ratée: ~\n"
               "Touchée: X\n"
               "Coulée: O\n\n"
               "=====================\n"
               "Lancer une partie (1)\n"
               "=====================\n");

        scanf("%d", &choice);


        if (choice != 1) {
            printf("\n/!\\ UTILISEZ LA TOUCHE 1 POUR LANCER UNE PARTIE /!\\\n\n");
        }

        emptyBuffer();

    } while (choice != 1);
}


/** \brief boatsEnd - This function changes the state of the grid when a ship is sunk
 * \return void
 *
 */
void boatsEnd(int boatNumber) {


    printf("###############\n"
           "TOUCHÉ, COULÉ !\n"
           "###############\n\n");

    switch (boatNumber) {
        case 2:
            for (int i = 0; i < 2; ++i) {
                gameGrid[boat2[i][0]][boat2[i][1]] = 'O';
            }
            --allBoats;
            score += 250;
            break;

        case 31:
            for (int i = 0; i < 3; ++i) {
                gameGrid[boat31[i][0]][boat31[i][1]] = 'O';
            }
            --allBoats;
            score += 250;
            break;

        case 32:
            for (int i = 0; i < 3; ++i) {
                gameGrid[boat32[i][0]][boat32[i][1]] = 'O';
            }
            --allBoats;
            score += 250;
            break;

        case 4:
            for (int i = 0; i < 4; ++i) {
                gameGrid[boat4[i][0]][boat4[i][1]] = 'O';
            }
            --allBoats;
            score += 250;
            break;

        case 5:
            for (int i = 0; i < 5; ++i) {
                gameGrid[boat5[i][0]][boat5[i][1]] = 'O';
            }
            --allBoats;
            score += 250;
            break;

        default:
            printf("Ce navire n'existe pas !!!\n");
    }
}

/** \brief gameGridChanges - This function makes the changes related to the user's input entered in the game() function
 * \return void
 *
 */
void gameGridChanges(char vertical, int horizontal) {
    int hit = 100;
    int missed = -50;
    int oldCoordinate = -75;

    int verticalIndex = vertical - 97;      //See the comment in the game() function
    int horizontalIndex = horizontal - 1;

    if (userInputs[verticalIndex][horizontalIndex]) {

        userInputs[verticalIndex][horizontalIndex] = 0;

        switch (verticalIndex) {
            case 1:
                for (int i = 0; i < 4; ++i) {
                    if (horizontalIndex == boat4[i][1] && boat4Health != 0) {
                        printf("########\n"
                               "TOUCHÉ !\n"
                               "########\n\n");

                        gameGrid[verticalIndex][horizontalIndex] = 'X';
                        --boat4Health;
                        score += hit;
                        return;

                    } else if (horizontalIndex == boat4[i][1]) {
                        boatsEnd(4);
                        return;
                    }
                }

                printf("#######\n"
                       "PLOUF !\n"
                       "#######\n\n");

                gameGrid[verticalIndex][horizontalIndex] = '~';
                break;

            case 3:

                for (int i = 0; i < 5; ++i) {
                    if (horizontalIndex == boat5[i][1] && boat5Health != 0) {
                        printf("########\n"
                               "TOUCHÉ !\n"
                               "########\n\n");

                        gameGrid[verticalIndex][horizontalIndex] = 'X';
                        --boat5Health;
                        score += hit;
                        return;

                    } else if (horizontalIndex == boat5[i][1]) {
                        boatsEnd(5);
                        return;
                    }
                }

                printf("#######\n"
                       "PLOUF !\n"
                       "#######\n\n");

                gameGrid[verticalIndex][horizontalIndex] = '~';
                score += missed;
                break;

            case 4:

                if (horizontalIndex == boat31[0][1] && boat31Health != 0) {
                    printf("########\n"
                           "TOUCHÉ !\n"
                           "########\n\n");

                    gameGrid[verticalIndex][horizontalIndex] = 'X';
                    --boat31Health;
                    score += hit;
                    break;

                } else if (horizontalIndex == boat31[0][1]) {
                    boatsEnd(31);
                    break;
                }

                printf("#######\n"
                       "PLOUF !\n"
                       "#######\n\n");

                gameGrid[verticalIndex][horizontalIndex] = '~';
                score += missed;
                break;

            case 5:

                if (horizontalIndex == boat31[1][1] && boat31Health != 0) {
                    printf("########\n"
                           "TOUCHÉ !\n"
                           "########\n\n");

                    gameGrid[verticalIndex][horizontalIndex] = 'X';
                    --boat31Health;
                    score += hit;
                    break;

                } else if (horizontalIndex == boat31[1][1]) {
                    boatsEnd(31);
                    break;
                }

                printf("#######\n"
                       "PLOUF !\n"
                       "#######\n\n");

                gameGrid[verticalIndex][horizontalIndex] = '~';
                score += missed;
                break;

            case 6:

                if (horizontalIndex == boat31[2][1] && boat31Health != 0) {
                    printf("########\n"
                           "TOUCHÉ !\n"
                           "########\n\n");

                    gameGrid[verticalIndex][horizontalIndex] = 'X';
                    --boat31Health;
                    score += hit;
                    break;

                } else if (horizontalIndex == boat31[2][1]) {
                    boatsEnd(31);
                    break;
                }

                if (horizontalIndex == boat2[0][1] && boat2Health != 0) {
                    printf("########\n"
                           "TOUCHÉ !\n"
                           "########\n\n");

                    gameGrid[verticalIndex][horizontalIndex] = 'X';
                    --boat2Health;
                    score += hit;
                    break;

                } else if (horizontalIndex == boat2[0][1]) {
                    boatsEnd(2);

                    break;
                }

                printf("=======\n"
                       "PLOUF !\n"
                       "=======\n\n");

                gameGrid[verticalIndex][horizontalIndex] = '~';
                score += missed;
                break;

            case 7:

                for (int i = 0; i < 3; ++i) {
                    if (horizontalIndex == boat32[i][1] && boat32Health != 0) {
                        printf("########\n"
                               "TOUCHÉ !\n"
                               "########\n\n");

                        gameGrid[verticalIndex][horizontalIndex] = 'X';
                        --boat32Health;
                        score += hit;
                        return;

                    } else if (horizontalIndex == boat32[i][1]) {
                        boatsEnd(32);
                        return;
                    }
                }

                if (horizontalIndex == boat2[1][1] && boat2Health != 0) {
                    printf("########\n"
                           "TOUCHÉ !\n"
                           "########\n\n");

                    gameGrid[verticalIndex][horizontalIndex] = 'X';
                    --boat2Health;
                    score += hit;
                    break;

                } else if (horizontalIndex == boat2[1][1]) {
                    boatsEnd(2);
                    break;
                }

                printf("#######\n"
                       "PLOUF !\n"
                       "#######\n\n");

                gameGrid[verticalIndex][horizontalIndex] = '~';
                score += missed;
                break;

            default:
                printf("######\n"
                       "PLOUF!\n"
                       "######\n\n");

                gameGrid[verticalIndex][horizontalIndex] = '~';
                score += missed;
        }
    } else {
        printf("/!\\ COORDONNÉE DÉJÀ ENTRÉE !!! /!\\\n\n");
        score += oldCoordinate;
    }
}

/** \brief game - This function displays the battleship game's grid and wait for the user's inputs, repeats until the user sink all the boats
 * \return void
 *
 */
void game() {
    do {
        int horizontalHeader[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        char verticalHeader[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

        int horizontalCoordinate = 0;
        char verticalCoordinate = '0';

        printf("%4c", ' ');

        for (int i = 0; i < 10; ++i) {
            printf("%4d", horizontalHeader[i]);
        }

        printf("\n%4c", ' ');

        for (int i = 0; i < 10; ++i) {
            printf("%2c%2c", '-', 'v');
        }

        printf("%2c\n%4c\n", '-', '|');

        for (int i = 0; i < 10; ++i) {
            printf("%2c", verticalHeader[i]);
            printf("%2c", '>');

            for (int j = 0; j < 10; ++j) {
                printf("%4c", gameGrid[i][j]);
            }

            printf("\n%4c\n", '|');
        }

        printf("\nScore: %d\n\n", score);

        do {
            printf("Veuillez entrer une coordonnée vertical (a-j):\n");
            scanf("%c", &verticalCoordinate);

            if (verticalCoordinate >= 65 && verticalCoordinate <= 74) {
                verticalCoordinate = verticalCoordinate + 32;           //ASCII table: a:97, j:106 and A:65, J:74 ==> 65 + 32 = 97
            }

            emptyBuffer();

        } while (verticalCoordinate < 97 || verticalCoordinate > 106);  //See previous comment

        do {

            printf("Veuillez entrer une coordonnée horizontale (1-10):\n");
            scanf("%d", &horizontalCoordinate);

            emptyBuffer();

        } while (horizontalCoordinate < 1 || horizontalCoordinate > 10);

        printf("\nCase choisie: %c%d\n\n", verticalCoordinate, horizontalCoordinate);

        gameGridChanges(verticalCoordinate, horizontalCoordinate);

    } while (allBoats != 0);

    printf("############\n"
           "VICTOIRE !!!\n"
           "############\n\n"
           "Score : %d\n", score);

}



/**Will be updated and used in v1.0*/
/** \brief mainMenu - This function shows the main menu of the game and bring the user to the selected place
 * \return void
 *
 */
void mainMenu()
{
    do {

        printf("<------------->\n"
               "Bataille Navale\n"
               "<------------->\n"
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
            displayHelp();
            break;

        case 3:
            system("exit");
            break;

    }
}



/** \brief main - This function is the program's entry point
 * \return an int different from 0 if abnormal termination
 *
 */
int main() {
    SetConsoleOutputCP(CP_UTF8);

    //Initialization of the game grid and the input check grid
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            gameGrid[i][j] = '-';
            userInputs[i][j] = 1;
        }
    }

    displayHelp();
    game();

    system("pause");

    return 0;
}

