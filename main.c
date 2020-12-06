///Oublie pas différents entête et les commms//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/**Global variables**/
char gameGrid[10][10];

int boats = 5;
int boat5[5][2] = { {'D', 5}, {'D',6}, {'D',7}, {'D',8}, {'D',9}};
int boat4[4][2] = {{'B',2}, {'B',3}, {'B',4}, {'B',5}};
int boat3_1[3][2] = {{'E',1}, {'F',1}, {'G',1}};
int boat3_2[3][2] = {{'H',3},{'H',4},{'H', 5}};
int boat2[2][2] = {{'G', 7}, {'H',7}};

int boat5Health = 4;
int boat4Health = 3;
int boat3_1Health = 2;
int boat3_2Health = 2;
int boat2Health = 1;

int choice = 0;

/**Fonctions**/

void emptyBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void showHelp()
{
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


        if (choice != 1)
        {
            printf("UTILISEZ LA TOUCHE 1 POUR LANCER UNE PARTIE\n\n");
        }

    emptyBuffer();

    } while (choice != 1);

    return;
}

void gameGridChanges(char vertical , int horizontal)
{

    switch (vertical)
    {
        case 'B':

            for (int i = 0; i < 4; ++i)
            {
                if (horizontal == boat4[i][1] && boat4Health != 0)
                {
                    printf("========\n"
                           "TOUCHÉ !\n"
                           "========\n");

                    gameGrid[(int)(vertical) - 65][horizontal - 1] = 'X';
                    --boat4Health;

                    return;

                } else if(horizontal == boat4[i][1])
                {
                    printf("=======\n"
                           "COULÉ !\n"
                           "=======\n");

                    gameGrid[1][1] = 'O';
                    gameGrid[1][2] = 'O';
                    gameGrid[1][3] = 'O';
                    gameGrid[1][4] = 'O';

                    --boats;

                    return;
                }
            }

            printf("=======\n"
                   "PLOUF !\n"
                   "=======\n");

            gameGrid[(int)(vertical) - 65][horizontal - 1] = '~';

            break;

        case 'D':

            for (int i = 0; i < 5; ++i)
            {
                if (horizontal == boat5[i][1] && boat5Health != 0)
                {
                    printf("========\n"
                           "TOUCHÉ !\n"
                           "========\n");

                    gameGrid[(int)(vertical) - 65][horizontal - 1] = 'X';
                    --boat5Health;

                    return;

                } else if(horizontal == boat5[i][1])
                {
                    printf("=======\n"
                           "COULÉ !\n"
                           "=======\n");

                    gameGrid[3][4] = 'O';
                    gameGrid[3][5] = 'O';
                    gameGrid[3][6] = 'O';
                    gameGrid[3][7] = 'O';
                    gameGrid[3][8] = 'O';

                    --boats;

                    return;
                }
            }

            printf("=======\n"
                   "PLOUF !\n"
                   "=======\n");

            gameGrid[(int)(vertical) - 65][horizontal - 1] = '~';

            break;

        case 'E':

            if (horizontal == boat3_1[0][1] && boat3_1Health != 0)
            {
                printf("========\n"
                       "TOUCHÉ !\n"
                       "========\n");

                gameGrid[(int)(vertical) - 65][horizontal - 1] = 'X';
                --boat3_1Health;

                break;

            } else if(horizontal == boat3_1[0][1])
            {
                printf("=======\n"
                       "COULÉ !\n"
                       "=======\n");

                gameGrid[4][0] = 'O';
                gameGrid[5][0] = 'O';
                gameGrid[6][0] = 'O';

                --boats;

                break;
                }

            printf("=======\n"
                   "PLOUF !\n"
                   "=======\n");

            gameGrid[(int)(vertical) - 65][horizontal - 1] = '~';

            break;

        case 'F':

            if (horizontal == boat3_1[1][1] && boat3_1Health != 0)
            {
                printf("========\n"
                       "TOUCHÉ !\n"
                       "========\n");

                gameGrid[(int)(vertical) - 65][horizontal - 1] = 'X';
                --boat3_1Health;

                break;

            } else if(horizontal == boat3_1[1][1])
            {
                printf("=======\n"
                       "COULÉ !\n"
                       "=======\n");

                gameGrid[4][0] = 'O';
                gameGrid[5][0] = 'O';
                gameGrid[6][0] = 'O';

                --boats;

                break;
            }

            printf("=======\n"
                   "PLOUF !\n"
                   "=======\n");

            gameGrid[(int)(vertical) - 65][horizontal - 1] = '~';

            break;

        case 'G':

            if (horizontal == boat3_1[2][1] && boat3_1Health != 0)
            {
                printf("=========\n"
                       "TOUCHÉ !\n"
                       "=========\n");

                gameGrid[(int)(vertical) - 65][horizontal - 1] = 'X';
                --boat3_1Health;

                break;

            } else if (horizontal == boat3_1[2][1])
            {
                printf("========\n"
                       "COULÉ !\n"
                       "========\n");

                gameGrid[4][0] = 'O';
                gameGrid[5][0] = 'O';
                gameGrid[6][0] = 'O';

                --boats;

                break;
            }

            if (horizontal == boat2[0][1] && boat2Health != 0)
            {
                printf("=========\n"
                       "TOUCHÉ !\n"
                       "=========\n");

                gameGrid[(int)(vertical) - 65][horizontal - 1] = 'X';
                --boat2Health;

                break;

            } else if (horizontal == boat2[0][1])
            {
                printf("========\n"
                       "COULÉ !\n"
                       "========\n");

                gameGrid[6][6] = 'O';
                gameGrid[7][6] = 'O';

                --boats;

                break;
            }

            printf("=======\n"
                   "PLOUF !\n"
                   "=======\n");

            gameGrid[(int)(vertical) - 65][horizontal - 1] = '~';

            break;

        case 'H':

            for (int i = 0; i < 3; ++i)
            {

                if (horizontal == boat3_2[i][1] && boat3_2Health != 0)
                {
                    printf("=========\n"
                           "TOUCHÉ !\n"
                           "=========\n");

                    gameGrid[(int)(vertical) - 65][horizontal - 1] = 'X';
                    --boat3_2Health;

                    return;

                } else if (horizontal == boat3_2[i][1])
                {
                    printf("========\n"
                           "COULÉ !\n"
                           "========\n");

                    gameGrid[7][3] = 'O';
                    gameGrid[7][4] = 'O';
                    gameGrid[7][5] = 'O';

                    --boats;

                    return;
                }
            }


            if (horizontal == boat2[1][1] && boat2Health != 0)
            {
                printf("=========\n"
                       "TOUCHÉ !\n"
                       "=========\n");

                gameGrid[(int)(vertical) - 65][horizontal - 1] = 'X';
                --boat2Health;

                break;

            } else if (horizontal == boat2[1][1])
            {
                printf("========\n"
                       "COULÉ !\n"
                       "========\n");

                gameGrid[6][6] = 'O';
                gameGrid[7][6] = 'O';

                --boats;

                break;
            }

            printf("=======\n"
                   "PLOUF !\n"
                   "=======\n");

            gameGrid[(int)(vertical) - 65][horizontal - 1] = '~';

            break;

        default:
            printf("======\n"
                   "PLOUF!\n"
                   "======\n");

            gameGrid[(int)(vertical) - 65][horizontal - 1] = '~';

    }


    return;
}


void game()
{
    int horizontalHeader[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    char verticalHeader[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    do {
        int horizontalCoordinate = 0;
        char verticalCoordinate = '0';

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
                printf("%6c", gameGrid[i][j]);
            }

            printf("\n%4c\n", '>');
        }

        /*printf("========\nAide (2)\n========\n");*/ /**Will be used in v1.0 (unsure)*/

        do {
            printf("Veuillez entrer une coordonnée vertical (A-J, en majuscule!):\n");
            scanf("%c", &verticalCoordinate);

            emptyBuffer();

        } while (verticalCoordinate < 65 || verticalCoordinate > 90); //Use of the ASCII table 65 : A , 90 : Z

        do {

            printf("Veuillez entrer une coordonnée horizontale (1-10):\n");
            scanf("%d", &horizontalCoordinate);

            emptyBuffer();

        } while (horizontalCoordinate < 1 || horizontalCoordinate > 10);
        ///What happen if you enter the same position twice ???///
        printf("Case choisie: %c%d\n", verticalCoordinate, horizontalCoordinate);

        gameGridChanges(verticalCoordinate, horizontalCoordinate);

    } while (boats != 0);

    printf("VICTOIRE !!!\n");

    return;
}



/**Will be used in v1.0*/
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




int main()
{
    SetConsoleOutputCP(CP_UTF8);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            gameGrid[i][j] = '?';
        }
    }

    showHelp();
    game();

    system("pause");

    return 0;
}
