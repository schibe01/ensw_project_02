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

    FILE *file = fopen(filename, "r");

    QuestionList *list = malloc(sizeof(QuestionList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    read_question_list(list, 5, filename);
    print_question(list, 0);
    print_question_list(list);
    return 0;
}