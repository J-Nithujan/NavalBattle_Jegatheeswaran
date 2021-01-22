/**
 * \file      main.c
 * \author    Nithujan Jegatheeswaran
 * \version   1.0
 * \date      22.01.21
 * \brief     A battleship game
 *
 * \details    The game is made to be played in Windows' command prompt and has only 3 different game grids.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

/*Global Variables*/

/**\brief Grid used to check if the user already entered that coordinate*/
int userInputs[10][10] = {0};
/**\brief Grid that is shown to the user*/
char gameGrid[10][10] = {' '};
/**\brief Grid where the boats positions are stored*/
int positions[10][10] = {0};

/**\brief Updated every time a boat is sunk */
int numberOfBoats = 5;

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


/**\brief Used to take user's input in main and help menus*/
int choice = 0;

/**\brief Used to update the player's score*/
int score = 0;

/**\brief Const used for the score*/
const int HIT = 100;
/**\brief Const used for the score*/
const int MISSED = -50;
/**\brief Const used for the score*/
const int OLDCOORDINATE = -75;
/**\brief Const used for the score*/
const int SUNK = 250;

/**\brief Graphical split line used in the game*/
const char splitLine[75] = "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ";
/**\brief Graphical split line used in the logs*/
const char logSplitLine[75] = "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n";

/**\brief Name entered by the player*/
char playerName[20] = "";

/**\brief Pointer used for the logs .txt file*/
FILE *fptrLogs; //fptr stands for filePointer
/**\brief Pointer used for the scores .txt file*/
FILE *fptrScores; //fptr stands for filePointer

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

/** \brief writeLogs - This function write the specified sentence in the file "logs.txt"
 *
 *\param log - sentence that need to be logged
 *
 */
void writeLogs(char log[200]) {

    char timeBuffer[75] = "";
    time_t timer;
    struct tm *tm_info;

    fptrLogs = fopen("data/logs.txt", "a");

    //It is to know how the program is closed, by menus there will be 2 line and by closing the window there will be 1 lines
    if (!strcmp(log, "Program launched")){
        fputs(logSplitLine, fptrLogs);
    }

    //I take the current time and date and save it with a specific format
    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(timeBuffer, 75, "%d-%m-%Y / %H:%M:%S", tm_info);
    fputs(timeBuffer, fptrLogs);

    //Used to separate date/time and logged sentences
    fputs(": ", fptrLogs);
    fputs(log, fptrLogs);
    fputs("\n", fptrLogs);

    //It is to know how the program is closed, by menus there will be 2 line and by closing the window there will be 1 lines
    if (!strcmp(log, "Program closed")){
        fputs(logSplitLine, fptrLogs);
    }

    fclose(fptrLogs);
}

/** \brief showScores - This function shows the score to the user, it is only used in the main menu
 *
 *
 */
void showScores() {
    char dataToBeRead[100] = "";
    fptrScores = fopen("data/scores.txt", "r");

    fseek(fptrScores, 0, SEEK_END);
    //I use the pointer's position to know whether the file is empty or not (if it exists)
    unsigned long length = ftell(fptrScores);
    fseek(fptrScores, 0, SEEK_SET);

    if (fptrScores == NULL) {
        printf("\n/!\\ ERREUR LORS DU CHARGEMENT DES SCORES /!\\\n\n");

        writeLogs("Scores' file not found");

    } else if (length == 0) {
        //Needed for the first player
        printf("\n/!\\ PAS DE SCORES À AFFICHER, SOYEZ LE PREMIER /!\\\n\n");

        writeLogs("Scores are displayed");

    } else {
        printf("%s\n\n"
               " Scores\n"
               "########\n\n", splitLine);

        while (fgets(dataToBeRead, 100, fptrScores) != NULL) {
            printf("%s", dataToBeRead);
        }
        printf("\n\n");

        writeLogs("Scores are displayed");
    }
    fclose(fptrScores);
}


/** \brief writeScores - This function write the player's score at the end of a game
 *
 * \param pseudo -  name entered by the player, scoreInt - The player's score at the end of the game
 *
 */
void writeScore(char pseudo[], int scoreInt) {
    char scoreChar[5] = "";
    unsigned int scoreLength = 0;

    fptrScores = fopen("data/scores.txt", "a");

    if (fptrScores == NULL) {
        printf("\n/!\\ ERREUR LORS DE L'ENREGISTREMENT DES SCORES /!\\\n\n");

        writeLogs("'scores.txt' file not found");
        return;
    } else {
        sprintf(scoreChar, "%d", scoreInt);
        fputs(scoreChar, fptrScores);

        //Space between the scores and the ???????????????????
        scoreLength = strlen(scoreChar);
        char space[5] = "";
        while (8 - scoreLength >0) {
            strcat(space, " ");
            scoreLength++;
        }
        fputs(space, fptrScores);

        fputs(pseudo, fptrScores);
        fputs("\n", fptrScores);

        printf("\nScore sauvegardé\n");
        writeLogs("Score saved");
    }
    fclose(fptrScores);
}

/** \brief registerPlayer - This function ask the player to enter a pseudo and check if it is correct according to the specified rules
 *
 *
 */
void registerPlayer() {
    bool incorrect = 1;
    char logPlayerName[35] = "Entered player name = ";

    do {
        printf("%s\n\nEntrez votre nom de joueur:\n"
               "(Il peut contenir entre 1 et 20 lettres et/ou chiffres sans accents)\n",
               splitLine);
        gets(playerName);

        if (strlen(playerName) < 1 || strlen(playerName) > 20) {
            printf("\n/!\\ ENTREZ ENTRE 1 À 20 CARACTÈRES /!\\\n\n");
            incorrect = 1;

            writeLogs("Player name's rule not followed (Length)");

        } else incorrect = 0;

        for (int i = 0; i < strlen(playerName); ++i) {
            //The numbers 0-9 are represented, in the ASCII table, by numbers going from 48 to 57, letters A-Z by 65-90 and a-z by 97-122
            if ((playerName[i] < 48 || playerName[i] > 57) && (playerName[i] < 65 || playerName[i] > 90) &&
                (playerName[i] < 97 || playerName[i] > 122)) {
                printf("\n/!\\ UTILISEZ DES CHIFFRES ET/OU DES LETTRES SANS ACCENTS /!\\\n\n");

                writeLogs("Player name's rule not followed (Special characters)");

                incorrect = 1;
                break;
            }
        }

    } while (incorrect);

    printf("\nEntered player name: %s\n", playerName);

    strcat(logPlayerName, playerName);
    writeLogs(logPlayerName);
}

/** \brief showHelp - This function displays the explanation of the game to the user and wait for a specific input
 *
 *
 */
void displayHelp() {
    choice = 0;

    writeLogs("Game's help is displayed");

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
            printf("\n/!\\ UTILISEZ LES TOUCHES AFFICHÉES POUR VOUS DÉPLACER /!\\\n\n");

            writeLogs("Wrong command used in the help menu");
        }
    } while (choice != 5);

    writeLogs("Help menu closed");
}

/** \brief boatsEnd - This function changes the state of the grid when a ship is sunk: related (O)'s are replaced by (X)'s
 *
 *\param boatNumber - boat that was sunk
 *
 */
void boatsEnd(int boatNumber) {
    printf("###############\n"
           "TOUCHÉ, COULÉ !\n"
           "###############\n\n");

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (positions[i][j] == boatNumber) {
                gameGrid[i][j] = 'X';
            }
        }
    }

    numberOfBoats--;
    score += SUNK;

    writeLogs("Boat sunk");
}

/** \brief hitOrSink - This function calculates if a boat is hit or sunk: in the first case it replaces the (.)'s with (O)'s, in the second case it calls the boatEnd function
 *
 * \param
 *
 */
void hitOrSink(int vertical, int horizontal) {
    switch (positions[vertical][horizontal]) {
        case 5:
            if (boat5Health) {
                printf("########\n"
                       "TOUCHÉ !\n"
                       "########\n\n");

                gameGrid[vertical][horizontal] = 'O';
                score += HIT;
                boat5Health--;

                writeLogs("Boat 5 hit");

            } else {
                boatsEnd(5);
            }
            break;
        case 4:
            if (boat4Health) {
                printf("########\n"
                       "TOUCHÉ !\n"
                       "########\n\n");

                gameGrid[vertical][horizontal] = 'O';
                score += HIT;
                boat4Health--;

                writeLogs("Boat 4 hit");

            } else {
                boatsEnd(4);
            }
            break;
        case 31:
            if (boat31Health) {
                printf("########\n"
                       "TOUCHÉ !\n"
                       "########\n\n");

                gameGrid[vertical][horizontal] = 'O';
                score += HIT;
                boat31Health--;

                writeLogs("Boat 31 hit");

            } else {
                boatsEnd(31);
            }
            break;
        case 32:
            if (boat32Health) {
                printf("########\n"
                       "TOUCHÉ !\n"
                       "########\n\n");

                gameGrid[vertical][horizontal] = 'O';
                score += HIT;
                boat32Health--;

                writeLogs("Boat 32 hit");

            } else {
                boatsEnd(32);
            }
            break;
        case 2:
            if (boat2Health) {
                printf("########\n"
                       "TOUCHÉ !\n"
                       "########\n\n");

                gameGrid[vertical][horizontal] = 'O';
                score += HIT;
                boat2Health--;

                writeLogs("Boat 2 hit");

            } else {
                boatsEnd(2);
            }
            break;
        default:
            printf("\n/!\\ FATAL ERROR /!\\\n\n");
            writeLogs("Error in function hitOrSink");
    }
}

/** \brief hitOrMiss - This function calculates if a boat is hit or not, or if the coordinates were already entered
 *
 *\param vertical - vertical coordinate entered by the player, horizontal - horizontal coordinate entered by the player
 *
 */
void hitOrMiss(char vertical, int horizontal) {
    int verticalIndex =
            vertical - 97;      //ASCII table: a = 97, so I need to substract this number to start the indexes from 0
    int horizontalIndex = horizontal - 1;   //Array's index start from 0 unlike the game board seen by the user

    //This tests if the coordinates were already entered by the user
    if (userInputs[verticalIndex][horizontalIndex]) {
        userInputs[verticalIndex][horizontalIndex] = 0;

        //This tests if it is a miss or a hit
        if (positions[verticalIndex][horizontalIndex] != 0) {
            hitOrSink(verticalIndex, horizontalIndex);

            return;
        } else {
            printf("######\n"
                   "PLOUF!\n"
                   "######\n\n");

            gameGrid[verticalIndex][horizontalIndex] = '~';
            score += MISSED;

            writeLogs("Missed shot");
        }
    } else {
        printf("/!\\ COORDONNÉE DÉJÀ ENTRÉE /!\\\n\n");
        score += OLDCOORDINATE;

        writeLogs("Coordinates were already entered");
    }
}

/** \brief game - This function displays the battleship game's grid and wait for the user's inputs, repeats until the user sink all the boats
 *
 *
 */
void game() {
    choice = 0;
    char coordinates[3] = "";
    int tempVertical = 0;

    //fptr stands for filePointer
    FILE *fptrChosenGrid = NULL;

    srand((unsigned) time(NULL));
    //Generation of a random number between 1 and 3
    int randomNumber = (rand() % 3) + 1;

    switch (randomNumber) {
        case 1:
            fptrChosenGrid = fopen("data/grids/grid1.txt", "r");

            writeLogs("File grid1 opened");
            break;
        case 2:
            fptrChosenGrid = fopen("data/grids/grid2.txt", "r");
            writeLogs("File grid2 opened");
            break;
        case 3:
            fptrChosenGrid = fopen("data/grids/grid3.txt", "r");
            writeLogs("File grid3 opened");
            break;
        default:
            printf("/!\\ ERREUR INATTENDUE /!\\\n\n");
            writeLogs("Random number out of range for the game grid's selection");
    }

    if (fptrChosenGrid == NULL) {
        printf("\n/!\\ ERREUR LORS DU CHARGEMENT DE LA GRILLE DE JEU /!\\\n\n");

        writeLogs("No game grid found");
        return;

    } else {

        int data = 0;
        int count1 = 0;
        int count2 = 0;

        while (fscanf(fptrChosenGrid, "%d", &data) != EOF) {
            positions[count1][count2] = data;
            count2++;

            //This "if" helps working with the "positions" table
            if (count2 == 10) {
                count2 = 0;
                count1++;
            }
        }

        fclose(fptrChosenGrid);

        printf("\n/!\\ CHARGEMENT DE LA GRILLE RÉUSSI /!\\\n\n");
        writeLogs("Game grid fully loaded");
    }

    //Initialization of the score variable
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

    do {
        //Initialized in the do...while because I use a strcat with this string variable
        char coordinatesLog[30] = "Selected coordinates: ";

        //Initialization of the grid's headers
        int horizontalHeader[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        char verticalHeader[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

        //Variables used to take user's input for the "gameGrid" array
        int horizontalCoordinate = 0;
        char verticalCoordinate = '0';

        printf("%s\n\n%4c", splitLine, ' ');

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
                writeLogs("Uppercase letter entered for vertical coordinate");
            }


            if (verticalCoordinate < 97 || verticalCoordinate > 106) {
                //Error message for the player
                printf("\n/!\\ UTILISEZ LES LETTRES ALLANT DE 'A' à 'j' /!\\\n\n");
                writeLogs("Wrong command used (vertical coordinate)");
            }

            emptyBuffer();

            //ASCII table: a = 97 and j = 106
        } while (verticalCoordinate < 97 || verticalCoordinate > 106);

        coordinates[0] = verticalCoordinate;

        do {
            printf("Veuillez entrer une coordonnée horizontale (1-10):\n");
            scanf("%d", &horizontalCoordinate);

            if (horizontalCoordinate < 1 || horizontalCoordinate > 10) {
                //Error message for the player
                printf("\n /!\\ UTILISEZ LES TOUCHES ALLANT DE 1 À 10 /!\\\n\n");
                writeLogs("Wrong command used (horizontal coordinate)");
            }

            emptyBuffer();

        } while (horizontalCoordinate < 1 || horizontalCoordinate > 10);

        //48 is the ASCII value for 0
        tempVertical = horizontalCoordinate + 48;
        coordinates[1] = (char)tempVertical;

        printf("\nCase choisie: %s\n\n", coordinates);

        strcat(coordinatesLog,coordinates);
        writeLogs(coordinatesLog);

        hitOrMiss(verticalCoordinate, horizontalCoordinate);
    } while (numberOfBoats != 0);

    printf("############\n"
           "VICTOIRE !!!\n"
           "############\n\n"
           "Score : %d\n", score);

    writeLogs("Game won");
    writeScore(playerName, score);

    do {
        printf("%s\n"
               "Quitter (4)\n"                      //Button 4 is used in the mainMenu function (consistency)
               "Retour au Menu principal (5)\n"     //Button 5 is used to return to the main menu when you check the help from the main menu
               "%s\n", splitLine, splitLine);
        scanf("%d", &choice);

        emptyBuffer();

        if (choice != 4 && choice != 5) {
            //Error message for the player
            printf("\n/!\\ UTILISEZ LES TOUCHES AFFICHÉES POUR VOUS DÉPLACER /!\\\n\n"
                   "%s\n\n", splitLine);

            writeLogs("Wrong command used in the ''after win'' menu");
        }
    } while (choice != 4 && choice != 5);

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

        writeLogs("Main menu is displayed");

        emptyBuffer();

        switch (choice) {
            case 1:
                registerPlayer();
                game();
                break;
            case 2:
                displayHelp();
                break;
            case 3:
                showScores();
                break;
            case 4:
                system("exit");
                break;
            default:
                //Error message for the player
                writeLogs("Wrong command used in the main menu");
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

    writeLogs("Program launched");

    while (choice != 4) {
        mainMenu();
    }

    writeLogs("Program closed");
    system("pause");

    return 0;
}

