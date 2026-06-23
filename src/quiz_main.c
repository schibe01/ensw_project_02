#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "quiz.h"

int main(){
    Question *question = malloc(sizeof(Question));
    question -> quest = "Welches dieser Tiere ist kein Säugetier?";
    question -> ans[0] = "Igel";
    question -> ans[1] = "Lachs";
    question -> ans[2] = "Mensch";
    question -> ans[3] = "Marder";
    question -> corAns = 1;
    question -> next = NULL;

    QuestionList *list = malloc(sizeof(QuestionList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    insert_question(list, question);
    return 0;
}