#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void read_question_list(QuestionList* list, int n, const char* filename) {
    FILE *file = fopen(filename, "r");
    char Buffer[N];

    if (file == NULL){
        fprintf(stderr, "File could not be open\n");
        return;
    }

    for (int i = 0 ; i < n ; i++) {
        Question *buffer = malloc(sizeof(Question));

        if (!buffer) {
            fprintf(stderr, "Memory allocation failed\n");
            fclose(file);
            return;
        }

        fgets(Buffer, N, file);
        buffer -> quest = strdup(Buffer);
        fgets(Buffer, N, file);
        for (int j = 0 ; j < 4 ; j++) {
            fgets(Buffer, N, file);
            buffer -> ans[j] = strdup(Buffer);
        }
        fgets(Buffer, N, file);
        fgets(Buffer, N, file);
        
        buffer -> corAns = Buffer[0] - '0';

        fgets(Buffer, N, file);
        fgets(Buffer, N, file);
        insert_question(list, buffer);
    }

    fclose(file);
}