#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "quiz.h"

int main(){
    char* filename = "questions.txt";

    Question *question = malloc(sizeof(Question));
    question -> quest = "Welches dieser Tiere ist kein Säugetier?";
    question -> ans[0] = "Igel";
    question -> ans[1] = "Lachs";
    question -> ans[2] = "Mensch";
    question -> ans[3] = "Marder";
    question -> corAns = 1;
    question -> next = NULL;
  
    read_question_list(list, 4, "question.txt");
    insert_question(list, question);
    print_question(list, 0);

    FILE *file = fopen(filename, "r");
  
    read_question_list(list, 5, filename);
    print_question(list, 0);
    print_question_list(list);
  
  
    QuestionList *list = malloc(sizeof(QuestionList));
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
    
    printf("Willkommen zum Quiz!\n\n");

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
            printf("\nGeben Sie die gewuenschte Anzahl an Fragen ein:\n");
            int numQuestions;
            int check = scanf("%d", &numQuestions);

            while(getchar() != '\n');
            if(check != 1 || numQuestions < 1 || numQuestions > list->size){
                fprintf(stderr, "Error: Wrong input\n");
            } else {
                printf("Quiz startet\n");
                quiz(list, falseList, numQuestions);
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

    printf("\nWollen Sie den Highscore speichern?\n");
    printf("1: Ja\n");
    printf("2: Nein\n");
    int save;
    int check = scanf(" %d", &save);
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
    check = scanf(" %d", &view);
    while(getchar() != '\n');

    if(check != 1 || (view != 1 && view != 2)){
        fprintf(stderr, "Error: Wrong input\n");
    } else if(view == 1){
        printf("Highscoreliste wird angezeigt\n");
    } else {
        printf("Highscoreliste wird nicht angezeigt\n");
    }

    printf("\nVielen Dank fuer die Teilnahme am Quiz!\n");

    //insert_question(list, question);
    //print_question(list, 0);





    return 0;
}