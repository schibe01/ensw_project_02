#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "quiz.h"

int main(){
    srand(time(NULL));
    char* filename = "questions.txt";
    char* fileHighscore = "highscore.txt";
    QuestionList *list = malloc(sizeof(QuestionList));


    Question *question = malloc(sizeof(Question));
    question -> quest = "Welches dieser Tiere ist kein Säugetier?";
    question -> ans[0] = "Igel";
    question -> ans[1] = "Lachs";
    question -> ans[2] = "Mensch";
    question -> ans[3] = "Marder";
    question -> corAns = 1;
    question -> next = NULL;


    Score* score = malloc(sizeof(Score));
    score->name = "Lucien";
    score->surname = "Weißer";
    score->score = 0.0;

    updateHighscore(fileHighscore, score);
    

    //insert_question(list, question);
    //print_question(list, 0);


    FILE *file = fopen(filename, "r");


    //read_question_list(list, 5, filename);
    //print_question(list, 0);
    //print_question_list(list);
  
  
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list -> round = 0;
    list -> score = 0.0;


    QuestionList *falseList = malloc(sizeof(QuestionList));
    falseList->head = NULL;
    falseList->tail = NULL;
    falseList->size = 0;
    falseList->round = 0;
    falseList->score = 0.0;



    int option;
    
    printf("\nWillkommen zum Quiz!\n\n");

    while(1){
        printf("\nWaehlen Sie eine Option:\n");
        printf("1. Quiz starten\n");
        printf("2. Highscores anzeigen\n");
        printf("3. Tests durchfuehren\n");
        printf("4. Beenden\n\n");
        
        int check = scanf("%d", &option);

        while(getchar() != '\n');
        if(check != 1 || option < 1 || option > 4){
            fprintf(stderr, "Error: Wrong input\n");
            continue;
        }
        else{
            break;
        }
    }


    switch(option){
    
        case 1:
            printf("\nGeben Sie die gewuenschte Anzahl an Fragen ein (maximal 20 Fragen):\n");
            int numQuestions;
            int check = scanf("%d", &numQuestions);

            while(getchar() != '\n');
            if(check != 1 || numQuestions < 1){
                fprintf(stderr, "Error: Wrong input\n");
            } else {
                numQuestions = min(numQuestions, 20);
                printf("\nQuiz startet\n");
                read_question_list(list, numQuestions, filename);
                double finalScore = quiz(list, falseList, numQuestions) * 20/numQuestions;
                printf("\nEndpunkte: %.2f\n", finalScore);


                printf("\nWollen Sie den Highscore speichern?\n");
                printf("1: Ja\n");
                printf("2: Nein\n");
                int save;
                check = scanf("%d", &save);
                while(getchar() != '\n');

                if(check != 1 || (save != 1 && save != 2)){
                    fprintf(stderr, "Error: Wrong input\n");
                } else if(save == 1){
                    printf("Highscore wird gespeichert\n");
                    printf("\nGeben Sie Ihren Vornamen ein:\n");
                    char name[50];
                    int checkName = scanf("%49s", name);
                    
                    while(getchar() != '\n');
                    if(checkName != 1){
                        fprintf(stderr, "Error: wrong input\n");
                    }

                    printf("\nGeben Sie Ihren Nachnamen ein:\n");
                    char surname[50];
                    checkName = scanf("%49s", surname);
                    while(getchar() != '\n');
                    if(checkName != 1){
                        fprintf(stderr, "Error: wrong input\n");
                    }

                    Score* newScore = malloc(sizeof(Score));
                    newScore->name = name;
                    newScore->surname = surname;
                    newScore->score = finalScore;

                    updateHighscore(fileHighscore, newScore);
                } else {
                    printf("Highscore wird nicht gespeichert\n");
                }

                printf("\nWollen Sie die aktuelle Highscoreliste ansehen?\n");
                printf("1: Ja\n");
                printf("2: Nein\n");
                int view;
                check = scanf("%d", &view);
                while(getchar() != '\n');

                if(check != 1 || (view != 1 && view != 2)){
                    fprintf(stderr, "Error: Wrong input\n");
                } else if(view == 1){
                    printf("Highscoreliste wird angezeigt\n");
                    printHighscore(fileHighscore);
                } else {
                    printf("Highscoreliste wird nicht angezeigt\n");
                }

                printf("\nVielen Dank fuer die Teilnahme am Quiz!\n");
            }
            break;
        case 2:
            printf("Highscores anzeigen:\n");
            printHighscore(fileHighscore);
            break;
        case 3:
            while(1){
                printf("\nWelchen Test moechten Sie durchfuhren?\n");
                printf("Test 1: Neue Frage in die Liste der Fragen anfuegen und diese testen\n");
                printf("Test 2: Fragenliste bearbeiten und anzeigen\n");
                printf("Test 3: Frage in Dokument einlesen und anzeigen\n");
                printf("Test 4: Frage aus Liste loeschen\n");

                check = scanf("%d", &option);

                while(getchar() != '\n');
                if(check != 1 || option < 1 || option > 4){
                    fprintf(stderr, "Error: Wrong input\n");
                    continue;
                }
                else{
                    break;
                }
            }

            switch(option){

                case 1:
                    Question *newQuestion = malloc(sizeof(Question));

                    printf("\nGeben Sie die Frage ein (keine Umlaute)\n");
                    char newQuest[100];
                    int checkName = scanf("%99[^\n]", newQuest);
                    
                    while(getchar() != '\n');
                    if(checkName != 1){
                        fprintf(stderr, "Error: wrong input\n");
                    }


                    printf("\nGeben Sie die erste Antortmoeglichkeit ein (keine Umlaute)\n");
                    char ans0[100];
                    checkName = scanf("%99[^\n]", ans0);
                    
                    while(getchar() != '\n');
                    if(checkName != 1){
                        fprintf(stderr, "Error: wrong input\n");
                    }


                    printf("\nGeben Sie die zweite Antortmoeglichkeit ein (keine Umlaute)\n");
                    char ans1[100];
                    checkName = scanf("%99[^\n]", ans1);
                    
                    while(getchar() != '\n');
                    if(checkName != 1){
                        fprintf(stderr, "Error: wrong input\n");
                    }


                    printf("\nGeben Sie die dritte Antortmoeglichkeit ein (keine Umlaute)\n");
                    char ans2[100];
                    checkName = scanf("%99[^\n]", ans2);
                    
                    while(getchar() != '\n');
                    if(checkName != 1){
                        fprintf(stderr, "Error: wrong input\n");
                    }


                    printf("\nGeben Sie die vierte Antortmoeglichkeit ein (keine Umlaute)\n");
                    char ans3[100];
                    checkName = scanf("%99[^\n]", ans3);
                    
                    while(getchar() != '\n');
                    if(checkName != 1){
                        fprintf(stderr, "Error: wrong input\n");
                    }


                    printf("\nGeben Sie die richtige Antortmoeglichkeit ein (1-4)\n");
                    int cor;
                    int check = scanf("%d", &cor);
                    
                    while(getchar() != '\n');
                    if(check != 1){
                        fprintf(stderr, "Error: wrong input\n");
                    }


                    newQuestion -> quest = strdup(newQuest);
                    newQuestion -> ans[0] = strdup(ans0);
                    newQuestion -> ans[1] = strdup(ans1);
                    newQuestion -> ans[2] = strdup(ans2);
                    newQuestion -> ans[3] = strdup(ans3);
                    newQuestion -> corAns = cor - 1;
                    newQuestion -> next = NULL;

                    QuestionList *test1 = malloc(sizeof(QuestionList));
                    test1->head = NULL;
                    test1->tail = NULL;
                    test1->size = 0;
                    test1->score = 0.0;
                    test1->round = 0;

                    insert_question(test1, newQuestion);
                    quiz(test1, falseList, 1);
                    break;
                case 2:
                    printf("\n\nLeere Fragenliste:\n");

                    
                    QuestionList *test2 = malloc(sizeof(QuestionList));
                    test2->head = NULL;
                    test2->tail = NULL;
                    test2->size = 0;
                    test2->score = 0.0;
                    test2->round = 0;

                    print_question_list(test2);
                    
                    printf("\nGeben Sie eine Frage ein:\n");

                    Question *newQuestion2 = malloc(sizeof(Question));

                    printf("\nGeben Sie die Frage ein (keine Umlaute)\n");
                    char newQuest2[100];
                    int checkName2 = scanf("%99[^\n]", newQuest2);
                    
                    while(getchar() != '\n');
                    if(checkName2 != 1){
                        fprintf(stderr, "Error: wrong input\n");
                    }

                    newQuestion2 -> quest = strdup(newQuest2);
                    newQuestion2 -> ans[0] = NULL;
                    newQuestion2 -> ans[1] = NULL;
                    newQuestion2 -> ans[2] = NULL;
                    newQuestion2 -> ans[3] = NULL;
                    newQuestion2 -> corAns = -1;
                    newQuestion2 -> next = NULL;

                    insert_question(test2, newQuestion2);
                    print_question_list(test2);
                    break;
                case 3:
                    
                    break;
                case 4:
                    QuestionList *test4 = malloc(sizeof(QuestionList));
                    test4->head = NULL;
                    test4->tail = NULL;
                    test4->size = 0;
                    test4->score = 0.0;
                    test4->round = 0;

                    Question *newQuestion41 = malloc(sizeof(Question));
                    newQuestion41->quest = strdup("Testfrage 1");
                    newQuestion41->ans[0] = NULL;
                    newQuestion41->ans[1] = NULL;
                    newQuestion41->ans[2] = NULL;
                    newQuestion41->ans[3] = NULL;
                    newQuestion41->corAns = -1;
                    newQuestion41->next = NULL;

                    insert_question(test4, newQuestion41);


                    Question *newQuestion42 = malloc(sizeof(Question));
                    newQuestion42->quest = strdup("Testfrage 2");
                    newQuestion42->ans[0] = NULL;
                    newQuestion42->ans[1] = NULL;
                    newQuestion42->ans[2] = NULL;
                    newQuestion42->ans[3] = NULL;
                    newQuestion42->corAns = -1;
                    newQuestion42->next = NULL;

                    insert_question(test4, newQuestion42);


                    Question *newQuestion43 = malloc(sizeof(Question));
                    newQuestion43->quest = strdup("Testfrage 3");
                    newQuestion43->ans[0] = NULL;
                    newQuestion43->ans[1] = NULL;
                    newQuestion43->ans[2] = NULL;
                    newQuestion43->ans[3] = NULL;
                    newQuestion43->corAns = -1;
                    newQuestion43->next = NULL;

                    insert_question(test4, newQuestion43);

                    printf("\nFragenliste vor dem Löschen:\n");
                    print_question_list(test4);

                    printf("\nGeben Sie den Index der Frage ein, die Sie loeschen moechten (1-3):\n");
                    int delIdx;
                    int checkDel = scanf("%d", &delIdx);

                    while(getchar() != '\n');
                    if(checkDel != 1 || delIdx < 1 || delIdx > 3){
                        fprintf(stderr, "Error: wrong input\n");
                    } else {
                        delete_question(test4, delIdx - 1);
                        printf("\nFragenliste nach dem Loeschen:\n");
                        print_question_list(test4);
                    }

                    break;
                default:
                    break;
            }
            break;
        case 4:
            printf("Beenden\n");
            break;
        default:
            fprintf(stderr, "Error: Wrong input\n");
            break;
    }

    return 0;
}