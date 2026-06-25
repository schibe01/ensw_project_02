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
    quest->next = NULL;
    list->size++;
    printf("%zd\n", list->size);

}

void print_question(QuestionList* list, int idx){
    Question *ptr = list->head;
    if(idx < 0 || idx >= list->size){
        fprintf(stderr, "Error: index doesn't exist\n");
        return;
    }

    for(; idx--; ){
        ptr = ptr->next;
    }

    printf("%s\n\n", ptr->quest);
    for(int i = 0; i < 4; i++){
        printf("Ans %d: %s\n", i, ptr->ans[i]);
    }
    
    printf("\nWas ist Ihre Antwort?\n");    
}

void delete_question(QuestionList* list, int idx){
    Question *ptr = list->head;
    if(idx < 0 || idx >= list->size){
        fprintf(stderr, "Error: index doesn't exist\n");
        return;
    }

    if (idx == 0){
        list -> head = ptr -> next;

        free(ptr);

        list -> size--;
        return;
    }

    for(; idx-- -1; ){
        ptr = ptr->next;
    }

    free(ptr -> next);

    ptr -> next = ptr -> next -> next;

    if(ptr -> next == NULL){
        list -> tail = ptr;
    }

    list -> size--;
}

void print_question_list(QuestionList* list){
    Question* ptr = list -> head -> next;
    for (int i = 0 ; i < list -> size ; i++) {
        printf("Question %d: ", i);
        if (i == 0) {
            printf("%s\n", list -> head -> quest);
        } else if (i == list -> size - 1) {
            printf("%s\n", list -> tail -> quest);
        } else {
            printf("%s\n", ptr -> quest);
            ptr = ptr -> next;
        }
    }
    printf("size: %zd\n\n", list -> size);
}

