#include <stdio.h>
#include <stdlib.h>
#include "quiz.h"

void insert_question(QuestionList* list, Question* quest){

    if(list->head == NULL){
        list->head = quest;
    }
    else{
        list->tail->next = quest;
    }
    list->tail = quest;
    list->size++;

}

void print_question(QuestionList* list, int idx){
    Question *ptr = list->head;
    if(idx < 0 || idx >= list->size){
        fprintf(stderr, "Error: index doesn't exist\n");
        return;
    }

    for(; --idx; ){
        ptr = ptr->next;
    }

    printf("%s\n\n", ptr->quest);
    for(int i = 0; i < 4; i++){
        printf("Ans %d: %s\n", i, ptr->ans[i]);
    }
    
    printf("\nWas ist Ihre Antwort?\n");    
}

