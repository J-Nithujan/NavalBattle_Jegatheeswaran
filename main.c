/**
 * \file      main.c
 * \author    Nithujan Jegatheeswaran
 * \version   0.1
 * \date      18.12.20
 * \brief     A battleship game
 *
 * \details    The game is made to be played in Windows' command prompt and has only one grid of ships.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

/*Global Variables*/

/**\brief Grid used to check if the user already entered that coordinate*/
int userInputs[10][10] = {0};
/**\brief Grid that is shown to the user*/
char gameGrid[10][10] = {' '};

/**\brief Used when you launch a game from the menu */
bool newGame = 0;

/**\brief Updated every time a boat is sunk */
int numberOfBoats = 5;

/**\brief This grid contains all boats' positions, the order of the coordinates is /!\ VITAL /!\*/
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

/**\brief Health variables help to determine if a boat is sunk, or not, when hit*/
int boat5Health = 4;
/**\brief Health variables help to determine if a boat is sunk, or not, when hit*/
int boat4Health = 3;
/**\brief Health variables help to determine if a boat is sunk, or not, when hit*/
int boat31Health = 2;
/**\brief Health variables help to determine if a boat is sunk, or not, when hit*/
int boat32Health = 2;
/**\brief Health variables help to determine if a boat is sunk, or not, when hit*/
int boat2Health = 1;

/**\brief These indexes help to manipulate the userInput and gameGrid arrays*/
int verticalIndex = 0;
/**\brief These indexes help to manipulate the userInput and gameGrid arrays*/
int horizontalIndex = 0;

/**\brief Used to take user's input in main and help menus*/
int choice = 0;

/**\brief Used to update the player's score*/
int score = 0;

/**\brief Const used for the score*/
const int hit = 100;
/**\brief Const used for the score*/
const int missed = -50;
/**\brief Const used for the score*/
const int oldCoordinate = -75;
/**\brief Const used for the score*/
const int sink = 250;

/**\brief Graphical split line*/
const char splitLine[69] = "><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><";

/**\brief Name entered by the player*/
char playerName[20] = "";

/*Functions*/

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

/** \brief showHelp - This function ask the player for a nickname with the purpose of saving his score
 *
 *
 */
void registerPlayer(){
    bool incorrect = 1;

    do {
        printf("%s\n\nEntrez votre nom de joueur (Taille: entre 1 et 20 caractères):\n", splitLine);
        scanf("%s", &playerName);
        emptyBuffer();

        if (strlen(playerName) < 1 || strlen(playerName) > 20){                                     ///Certains symboles ne passent pas !!!!
            printf("\n/!\\ VOTRE NOM DE JOUEUR DOIT CONTENIR ENTRE 1 ET 20 CARACTÈRES /!\\\n\n");
        } else incorrect = 0;

    }while (incorrect);

    /**Player Name Test*/
    printf("\nPlayer name: %s\n", playerName);
}

/** \brief showHelp - This function displays the explanation of the game to the user and wait for a specific input
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
               "%s\nRetour au Menu principal (5)\n%s\n",        //buttons 1, 2, 3 and 4 are already used for new game, help, scores and quit in mainMenu
               splitLine, splitLine, splitLine);

        scanf("%d", &choice);

        emptyBuffer();

        if (choice != 5) {
            printf("\n/!\\ UTILISEZ LES TOUCHES AFFICHÉES POUR VOUS DÉPLACER /!\\\n");
        }

    } while (choice != 5);
}


/** \brief boatsEnd - This function changes the state of the grid when a ship is sunk: related (O)'s are replaced by (X)'s
 *
 *
 */
void boatsEnd(int boatNumber) {
    printf("###############\n"
           "TOUCHÉ, COULÉ !\n"
           "###############\n\n");

    //Every cases of this switch is linked to a specific boat: 2 is for boat 2, 31 for boat31, etc.
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
            printf("CE NAVIRE N'EXISTE PAS !!!\n");
    }
}

void boatSink(int boatNumber) {
    switch (boatNumber) {
        case 5:
            ;

        case 4:
            ;

        case 31:
            ;

        case 32:
            ;

        case 2:
            ;

        default:
            printf("\n/!\\CE BATEAU N'EXISTE PAS/!\\\n");
    }
}

/** \brief hitOrSink - This function calculates if a boat is hit or sink: in the first case it replaces the (.)'s with (O)'s, in the second case it calls the boatEnd function
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
    verticalIndex = vertical - 97;      //ASCII table: a = 97, so I need to substract this number to start the indexes from 0
    horizontalIndex = horizontal - 1;   //Array's index start from 0 unlike the game board seen by the user
    bool miss = 1;

    //This tests if the coordinates were already entered by the user
    if (userInputs[verticalIndex][horizontalIndex]) {

        userInputs[verticalIndex][horizontalIndex] = 0;

        for (int i = 0; i < 17; ++i) {
            if (boats[i][0] == verticalIndex && boats[i][1] == horizontalIndex) {   //Modify with 5,4,31,32,2 with a grid (again)
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
        printf("/!\\ COORDONNÉE DÉJÀ ENTRÉE /!\\\n\n");
        score += oldCoordinate;
    }
}

/** \brief game - This function displays the battleship game's grid and wait for the user's inputs, repeats until the user sink all the boats
 *
 *
 */
void game() {
    choice = 0;

    //Initialization of variables related to the win conditions, useful only when you start another game without closing the program
    if (newGame) {
        score = 0;

        //Initialization of the number of remaining boats
        numberOfBoats = 5;

        //Initialization of the boats' health variables
        boat5Health = 4;
        boat4Health = 3;
        boat31Health = 2;
        boat32Health = 2;
        boat2Health = 1;

        //Initialization of the game grid and the input check grid
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

        //Variables used to take user's input for the "gameGrid" array
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
               "Quitter (4)\n"                      //Button 4 is used in the mainMenu function (consistency)
               "Retour au Menu principal (5)\n"     //Button 5 is used to return to the main menu when you check the help from the main menu
               "%s\n", splitLine, splitLine);
        scanf("%d", &choice);

        emptyBuffer();

        if (choice != 3 && choice != 4) {
            printf("\n/!\\ UTILISEZ LES TOUCHES AFFICHÉES POUR VOUS DÉPLACER /!\\\n\n"
                   "%s\n\n", splitLine);
        }
    }while (choice != 4 && choice != 5);

}

/** \brief mainMenu - This function shows the main menu of the game and bring the user to the selected place
 *
 *
 */
void mainMenu() {
    do {
        choice = 0;

        printf("%s\n\n"
               " Bataille navale\n"
               "#################\n\n"
               "Nouvelle partie (1)\n"
               "Aide (2)\n"
               "Scores (3)\n"
               "Quitter(4)\n\n"
               "%s\n", splitLine, splitLine);

        scanf("%d", &choice);

        emptyBuffer();

        switch (choice) {
            case 1:
                newGame = 1;
                registerPlayer();
                game();
                break;

            case 2:
                displayHelp();
                break;

            case 3:
                /**Scores (Work In Progress)*/

            case 4:
                system("exit");
                break;

            default:
                printf("\n/!\\ UTILISEZ LES TOUCHES AFFICHÉES POUR VOUS DÉPLACER /!\\\n\n");
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
}

/** \brief main - This function is the program's entry point
 * \return an int different from 0 if abnormal termination
 *
 */
int main() {
    SetConsoleOutputCP(CP_UTF8);

    while (choice != 4){
        mainMenu();
    }

    system("pause");
    return 0;
}