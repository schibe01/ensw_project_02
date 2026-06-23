#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "quiz.h"

int main(){
    Question *question = malloc(sizeof(Question));
    question -> quest = "Welches dieser Tiere ist kein Säugetier?";
    question -> ans1 = "Igel";
    question -> ans2 = "Lachs";
    question -> ans3 = "Mensch";
    question -> ans4 = "Marder";
    question -> corAns = 2;
    question -> next = NULL;

    QuestionList *list = malloc(sizeof(QuestionList));
    return 0;
}