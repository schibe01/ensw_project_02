#include <stdio.h>
#include <stdlib.h>
#include "quiz.h"

void insert_question(QuestionList* list, Question* quest){

    if(list->head == NULL){
        list->head = quest;
        list->tail = quest;
    }
    else{
        list->tail->next = quest;
        list->tail = quest;
        list->size++;
    }

}

void print_question(QuestionList* list, int idx){

    if(idx < 1|| idx > list->size){
        fprintf(stderr, "Error: index doesn't extist\n");
        return;
    }

    
}
