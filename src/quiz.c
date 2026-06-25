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
    printf("Size: %zd\n", list->size);

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

    printf("\n%s\n\n", ptr->quest);
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

        if(list -> head == NULL){
            list -> tail = NULL;
        }

        free(ptr);

        list -> size--;
        return;
    }

    for(; idx-- -1; ){
        ptr = ptr->next;
    }

    Question *temp = ptr -> next;
    
    ptr -> next = temp -> next;

    free(temp);    

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

int answer_question(QuestionList* list, int idx){
    Question *ptr = list->head;
    Question *null = NULL;
    if(idx < 0 || idx >= list->size){
        fprintf(stderr, "Error: Index doesn't exist\n");
        return -1; //Was soll hier passieren?
    }
    
    int ans;
    printf("\nWas ist Ihre Antwort?\n");
    int check = scanf("%d", &ans);

    while(getchar() != '\n');

    if(check != 1 || ans < 1 || ans > 4){
        printf("Keine gueltige Antwort\n");
        return answer_question(list, idx);
    }

    for(; idx--; ){
        ptr = ptr->next;
    }

    if(ans - 1 == ptr->corAns){
        printf("Richtige Antwort!\n\n");
        list->score += pow(2, -(list->round));
        return 1;       //Richtige Antwort
    }
    
    else{
        printf("Leider falsch\n\n");
        return 0;       //Falsche Antwort
    }
}
    
void quiz(QuestionList* list, QuestionList* falseList, int numQuestions){
    
    while(list->size != 0){
        for(int i = 0; i < numQuestions && i < list->size; i++){
            print_question(list, i);
            int answer = answer_question(list, i);
            if(answer == 1){
                printf("\nScore: %.2f\n", list->score);
                printf("Runde: %d\n", list->round);
            }
            else if(answer == 0){

                Question *ptr = list->head;
                for(int j = i; j--; ){
                    ptr = ptr->next;
                }

                Question *failed = malloc(sizeof(Question));
                *failed = *ptr;
                failed->next = NULL;
                insert_question(falseList, failed);
            }

        }
        

        falseList->round = ++list->round;

        falseList->score = list->score;

        *list = *falseList;

        falseList->head = NULL;
        falseList->tail = NULL;
        falseList->size = 0;
        falseList->round = 0;
        falseList->score = 0.0;



        
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
        Question* buffer = NULL;
        buffer -> quest = fgets(Buffer, N, file);
        fgets(Buffer, N, file);
        for (int j = 0 ; j < 4 ; j++) {
            buffer -> ans[j] = fgets(Buffer, N, file);
        }
        fgets(Buffer, N, file);
        buffer -> corAns = (int) getc(file);
        fgets(Buffer, N, file);
        insert_question(list, buffer);       
    }

}