/**
 * \file      main.c
 * \author    Nithujan Jegatheeswaran
 * \version   0.1
 * \date      16.12.20
 * \brief     A battleship game
 *
 * \details    The game is made to be played in Windows' command prompt and has only one grid of ships.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

/**Global variables**/
int userInputs[10][10] = {0};
char gameGrid[10][10] = {' '};

bool newGame = 0;

int numberOfBoats = 5;

//This grid contains all boats' positions, the order of the coordinates is /!\ VITAL /!\

const int boats[17][2] = {{3, 4},     //3 = D, the five coordinates from the beginning are boat5's locations
                          {3, 5},
                          {3, 6},
                          {3, 7},
                          {3, 8},
                          {1, 1},     //1 = B, the 4 coordinates from this line (included) are boat4's locations
                          {1, 2},
                          {1, 3},
                          {1, 4},
                          {4, 0},     //4 = E, the 3 coordinates from this line (included) are boat31's locations
                          {5, 0},     //5 = F
                          {6, 0},     //6 = G
                          {7, 2},     //7 = H, the 3 coordinates from this line (included) are boat32's locations
                          {7, 3},
                          {7, 4},
                          {6, 6},     //6 = G, the last 2 coordinates are related to boat2
                          {7, 6}};

//Health variables help to determine if a boat is sunk, or not, when hit
int boat5Health = 4;
int boat4Health = 3;
int boat31Health = 2;
int boat32Health = 2;
int boat2Health = 1;

//These indexes help to manipulate arrays
int verticalIndex = 0;
int horizontalIndex = 0;

int choice = 0;

int score = 0;

const int hit = 100;
const int missed = -50;
const int oldCoordinate = -75;
const int sink = 250;

//Graphical split line
const char splitLine[69] = "><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><";

/**Fonctions**/

/** \brief emptyBuffer - This function helps avoiding infinite loops in the scanf() function
 *
 *
 */
void emptyBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

/** \brief showHelp - This function displays the explanation of the game to the user
 *
 *
 */
void displayHelp() {
    choice = 0;

    do {
        printf("%s\n\n"
               " Aide de jeu\n"
               "#############\n\n"
               "Le but du jeu est de couler tous les navires cachés dans une grille.\n"
               "Pour faire cela il faut tirer sur une des cases de la grille en indiquant une coordonnée.\n"
               "Répétez cette opération jusqu'à ce que tous les navires soient coulés\n\n"
               "Score:\n"
               "------\n"
               "Raté: -50pts | Touché: 100pts | Touché-coulé: 250pts | Déjà tiré: -75pts\n\n"
               "État des cases:\n"
               "---------------\n"
               "Case inconnue: (.)\n"
               "Ratée: (~)\n"
               "Touchée: (O)\n"
               "Coulée: (X)\n"
               "Conseil: pour un meilleur confort visuel, jouez avec la fenêtre en pleine écran\n\n"
               "%s\nRetour au Menu principal (4)\n%s\n",
               splitLine, splitLine, splitLine);

        scanf("%d", &choice);

        emptyBuffer();

        if (choice != 4) {
            printf("\n/!\\ UTILISEZ LES TOUCHES AFFICHÉES POUR VOUS DÉPLACER /!\\\n");
        }

    } while (choice != 4);
}


/** \brief boatsEnd - This function changes the state of the grid when a ship is sunk: related (O)'s are replaced by (X)'s
 *
 *
 */
void boatsEnd(int boatNumber) {
    printf("###############\n"
           "TOUCHÉ, COULÉ !\n"
           "###############\n\n");

    //Every cases of this switch is linked to a specific boat
    switch (boatNumber) {
        case 2:
            for (int i = 15; i < 17; ++i) {
                gameGrid[boats[i][0]][boats[i][1]] = 'X';
            }
            --numberOfBoats;
            score += sink;
            break;

        case 32:
            for (int i = 12; i < 15; ++i) {
                gameGrid[boats[i][0]][boats[i][1]] = 'X';
            }
            --numberOfBoats;
            score += sink;
            break;

        case 31:
            for (int i = 9; i < 12; ++i) {
                gameGrid[boats[i][0]][boats[i][1]] = 'X';
            }
            --numberOfBoats;
            score += sink;
            break;

        case 4:
            for (int i = 5; i < 9; ++i) {
                gameGrid[boats[i][0]][boats[i][1]] = 'X';
            }
            --numberOfBoats;
            score += sink;
            break;

        case 5:
            for (int i = 0; i < 5; ++i) {
                gameGrid[boats[i][0]][boats[i][1]] = 'X';
            }
            --numberOfBoats;
            score += 250;
            break;

            //
        default:
            printf("Ce navire n'existe pas !!!\n");
    }
}

/** \brief hitOrSink - This function calculates if a boat is hit or sink: in the first case it replaces the (.)'s with (O)'s, in the second case it calls the hitOrSink function
 *
 *
 */
void hitOrSink(int vertical, int horizontal) {
    for (int i = 0; i < 5; ++i) {
        if ((vertical == boats[i][0]) && (horizontal == boats[i][1]) && (boat5Health != 0)) {
            printf("########\n"
                   "TOUCHÉ !\n"
                   "########\n\n");

            gameGrid[vertical][horizontal] = 'O';
            --boat5Health;
            score += hit;
            return;

        } else if ((vertical == boats[i][0]) && (horizontal == boats[i][1])) {
            boatsEnd(5);
        }
    }

    for (int i = 5; i < 9; ++i) {
        if ((vertical == boats[i][0]) && (horizontal == boats[i][1]) && (boat4Health != 0)) {
            printf("########\n"
                   "TOUCHÉ !\n"
                   "########\n\n");

            gameGrid[vertical][horizontal] = 'O';
            --boat4Health;
            score += hit;
            return;

        } else if ((vertical == boats[i][0]) && (horizontal == boats[i][1])) {
            boatsEnd(4);
        }
    }

    for (int i = 9; i < 12; ++i) {
        if ((vertical == boats[i][0]) && (horizontal == boats[i][1]) && (boat31Health != 0)) {
            printf("########\n"
                   "TOUCHÉ !\n"
                   "########\n\n");

            gameGrid[vertical][horizontal] = 'O';
            --boat31Health;
            score += hit;
            return;

        } else if ((vertical == boats[i][0]) && (horizontal == boats[i][1])) {
            boatsEnd(31);
        }
    }

    for (int i = 12; i < 15; ++i) {
        if ((vertical == boats[i][0]) && (horizontal == boats[i][1]) && (boat32Health != 0)) {
            printf("########\n"
                   "TOUCHÉ !\n"
                   "########\n\n");

            gameGrid[vertical][horizontal] = 'O';
            --boat32Health;
            score += hit;
            return;

        } else if ((vertical == boats[i][0]) && (horizontal == boats[i][1])) {
            boatsEnd(32);
        }
    }

    for (int i = 15; i < 17; ++i) {
        if ((vertical == boats[i][0]) && (horizontal == boats[i][1]) && (boat2Health != 0)) {
            printf("########\n"
                   "TOUCHÉ !\n"
                   "########\n\n");

            gameGrid[vertical][horizontal] = 'O';
            --boat2Health;
            score += hit;
            return;

        } else if ((vertical == boats[i][0]) && (horizontal == boats[i][1])) {
            boatsEnd(2);
        }
    }
}

/** \brief hitOrMiss - This function calculates if a boat is hit or not, or if the coordinates were already entered
 *
 *
 */
void hitOrMiss(char vertical, int horizontal) {
    verticalIndex = vertical - 97;      //ASCII table: a = 97 by
    horizontalIndex = horizontal - 1;   //Array's index start from 0 unlike the game board seen by the user
    bool miss = 1;

    //This tests if the coordinates were already entered by the user
    if (userInputs[verticalIndex][horizontalIndex]) {

        userInputs[verticalIndex][horizontalIndex] = 0;

        for (int i = 0; i < 17; ++i) {
            if (boats[i][0] == verticalIndex && boats[i][1] == horizontalIndex) {
                hitOrSink(verticalIndex, horizontalIndex);
                miss = 0;
            }
        }

        if (miss) {
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
 *
 *
 */
void game() {
    choice = 0;

    //Initialization of the game grid and the input check grid, once per game
    if (newGame) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                gameGrid[i][j] = '.';
                userInputs[i][j] = 1;
            }
        }
        newGame = 0;
    }

    do {
        //Initialization of the grid's headers
        int horizontalHeader[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        char verticalHeader[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

        //Variables used to take user's input for the game grid
        int horizontalCoordinate = 0;
        char verticalCoordinate = '0';

        printf("%s\n\n%4c", splitLine,' ');

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

            //If an uppercase letter is entered it is changed to a lowercase one, ASCII table: a is 97 and A is 65 --> 97 - 65 = 32
            if (verticalCoordinate >= 65 && verticalCoordinate <= 74) {
                verticalCoordinate = verticalCoordinate + 32;
            }

            emptyBuffer();

            //ASCII table: a = 97 and j = 106
        } while (verticalCoordinate < 97 || verticalCoordinate > 106);


        do {
            printf("Veuillez entrer une coordonnée horizontale (1-10):\n");
            scanf("%d", &horizontalCoordinate);

            emptyBuffer();

        } while ((horizontalCoordinate < 1 || horizontalCoordinate > 10));


        printf("\nCase choisie: %c%d\n\n", verticalCoordinate, horizontalCoordinate);

        hitOrMiss(verticalCoordinate, horizontalCoordinate);

    } while (numberOfBoats != 0);

    printf("############\n"
           "VICTOIRE !!!\n"
           "############\n\n"
           "Score : %d\n", score);

    do {
        printf("%s\n"
               "Quitter (3)\n"                      //button 3 is used in the mainMenu function (consistency)
               "Retour au Menu principal (4)\n"     //buttons 1, 2 and 3 are already used for new game, help and quit in mainMenu
               "%s\n", splitLine, splitLine);
        scanf("%d", &choice);

        emptyBuffer();

        if (choice != 3 && choice != 4) {
            printf("\n/!\\ UTILISEZ LES TOUCHES AFFICHÉES POUR VOUS DÉPLACER /!\\\n"
                   "%s\n\n", splitLine);
        }
    }while (choice != 3 && choice != 4);

}


/*Will be updated and used in v1.0*/
/** \brief mainMenu - This function shows the main menu of the game and bring the user to the selected place
 *
 *
 */
void mainMenu() {
    do {
        choice = 0;

        printf("%s\n\n"
               " Batialle navale\n"
               "#################\n\n"
               "Nouvelle partie (1)\n"
               "Aide (2)\n"
               "Quitter(3)\n\n"
               "%s\n", splitLine, splitLine);

        scanf("%d", &choice);

        emptyBuffer();

        switch (choice) {
            case 1:
                newGame = 1;
                game();
                break;

            case 2:
                displayHelp();
                break;

            case 3:
                system("exit");
                break;

            default:
                printf("\nVEUILLEZ FAIRE UN CHOIX AVEC LES TOUCHES 1, 2 OU 3 !!!\n");;
        }
    } while (choice != 1 && choice != 2 && choice != 3);
}

/** \brief main - This function is the program's entry point
 * \return an int different from 0 if abnormal termination
 *
 */
int main() {
    SetConsoleOutputCP(CP_UTF8);

    while (choice != 3){
        mainMenu();
    }

    system("pause");
    return 0;
}