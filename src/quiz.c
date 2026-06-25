#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

}

void print_question(QuestionList* list, int idx){
    Question *ptr = list->head;
    if(idx < 0 || idx >= list->size){
        fprintf(stderr, "Error: Index doesn't exist\n");
        return;
    }

    for(; idx--; ){
        ptr = ptr->next;
    }

    printf("%s\n\n", ptr->quest);
    for(int i = 0; i < 4; i++){
        printf("Ans %d: %s\n", i + 1, ptr->ans[i]);
    }
    
}

Question answer_question(QuestionList* list, int idx){
    Question *ptr = list->head;
    Question *null = NULL;
    if(idx < 0 || idx >= list->size){
        fprintf(stderr, "Error: Index doesn't exist\n");
        return *null;
    }
    
    int ans;
    printf("\nWas ist Ihre Antwort?\n");
    int check = scanf("%d", &ans);

    if(check != 1){
        fprintf(stderr, "Error: Wrong input");
    }

    if(ans < 1 || ans > 4){
        printf("Keine gueltige Antwort\n");
        return answer_question(list, idx);
    }

    for(; idx--; ){
        ptr = ptr->next;
    }

    if(ans - 1 == ptr->corAns){
        printf("Richtige Antwort!");
        list->score += pow(2, -(list->round));
        return *null;
    }
    
    else{
        printf("Leider falsch");
        return *ptr;
    }
    
    
    
}
