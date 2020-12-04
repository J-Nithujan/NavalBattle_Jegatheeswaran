///Oublie pas différents entête et les commms//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/**Global variables**/
char gameBoard[10][10];
int horizontalHeader[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
char verticalHeader[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
char boatsPosition[10][10] = ;
char fiveLengthBoat[5] = {};
char fourLengthBoats[4][2] = {};
char threeLengthBoats[3][2] = {};
char twoLengthBoat[2] = {};
int choice = 0; /*???*/

/**Fonctions**/

//In-game help
void showHelp()
{
    do
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

        scanf("%d", choice);

        if (choice != 0)
        {
            printf("UTILISEZ LA TOUCHE 0 (ZÉRO) POUR REVENIR AU JEU\n\n");
        }
    } while (choice =! 0);

    return;
}


void game()
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

    printf("========\nAide (2)\n========");

    return;
}

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




int main()
{
    SetConsoleOutputCP(CP_UTF8);

    game();


    return 0;
}
