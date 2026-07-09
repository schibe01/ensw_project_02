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


    Score* score = malloc(sizeof(score));
    score->name = "Lucien";
    score->surname = "Weißer";
    score->score = 0.0;

    updateHighscore(fileHighscore, score);
    

    //insert_question(list, question);
    //print_question(list, 0);


    FILE *file = fopen(filename, "r");

    QuestionList *list = malloc(sizeof(QuestionList));

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
        printf("3. Beenden\n\n");
        
        int check = scanf("%d", &option);

        while(getchar() != '\n');
        if(check != 1 || option < 1 || option > 3){
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
                double finalScore = quiz(list, falseList, numQuestions);
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
                } else {
                    printf("Highscoreliste wird nicht angezeigt\n");
                }

                printf("\nVielen Dank fuer die Teilnahme am Quiz!\n");
            }
            break;
        case 2:
            printf("Highscores anzeigen\n");
            break;
        case 3:
            printf("Beenden\n");
            break;
        default:
            fprintf(stderr, "Error: Wrong input\n");
            break;
    
    }
    
    return 0;
}