//Oublie pas conventions et commms

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/**Global variables**/
char gameBoard[10][10];
int horizontalHeader[21] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
char verticalHeader[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
int choice = 0; /*???*/

/**Fonctions**/

void mainMenu()
{
    printf("Bataille Navale\n===============\n"
           "Nouvelle partie (1)\n"
           "Aide (2)\n"
           "Quitter(3)\n"
           "==============\n");
    return;
}

//In-game help
void showHelp()
{
    printf("===========\nAide de jeu\n===========\n"
           "Le but du jeu est de couler tous les bateaux.\n"
           "Pour ce faire il faut tirer sur une des cases du tableau en indiquant une coordonnée.\n"
           "Répétez cette opération jusqu'à ce que tous les bateaux soient coulées\n\n"
           "État des cases:\n"
           "Case inconnue: ?\n"
           "Ratée: ~\n"
           "Touchée: X\n"
           "Coulée: O\n===========\n"
           "Retour (0)\n"
           "===========\n");
    return;
}


void gameBoardPrint()
{
    printf("%4c", ' ');

    for (int i = 0; i < 10; ++i)
    {
        printf("%6d", horizontalHeader[i]);
    }

    printf("\n%4c", ' ');

    for (int i = 0; i < 10; ++i)
    {
        printf("%3c%3c", 'v', '-');
    }

    printf("%2c\n%4c\n", 'v', '>');

    for (int i = 0; i < 10; ++i)
    {
        printf("%2c", verticalHeader[i]);
        printf("%2c", '|');

        for (int j = 0; j < 10; ++j)
        {
            gameBoard[i][j] = '?';
            printf("%6c", gameBoard[i][j]);
        }

        printf("\n%4c\n", '>');
    }

    return;
}

void menuInput(int input)
{
    switch (input)
    {
        case 1:
            gameBoardPrint();
            break;

        case 2:
            showHelp();
            break;

        case 3:
            system("exit");
            break;
    }

    return;
}

void helpInput(int position, int input)
{

}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    mainMenu();
    scanf("%d", &choice);
    menuInput(choice);

    return 0;
}
