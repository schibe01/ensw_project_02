#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "quiz.h"

#define NUM_QUEST 20

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
    
double quiz(QuestionList* list, QuestionList* falseList, int numQuestions){ 
    while(list->size != 0){
        printf("\n\nRunde %d:\n\n", list->round + 1);
        for(int i = 0; i < numQuestions && i < list->size; i++){
            print_question(list, i);
            int answer = answer_question(list, i);
            if(answer == 1){
                printf("\nScore: %.2f\n", list->score);
                printf("\n\n\n\n\n");
                //printf("Runde: %d\n\n\n\n\n", list->round + 1);
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
    
    return list->score;
}

void read_question_list(QuestionList* list, int n, const char* filename) {
    FILE *file = fopen(filename, "r");
    char Buffer[N];

    if (file == NULL){
        fprintf(stderr, "File could not be opened\n");
        return;
    }

    for (int i = 0 ; i < NUM_QUEST; i++) {

        /*if(feof(file)){ //Wie erkennt man am Besten, wann keine Fragen mehr in der Liste sind?
            fprintf(stderr, "Error: Not enough questions in recieved file\n");
            fprintf(stderr, "Maximum amount: %d\n\n", i + 1);
            fclose(file);
            return;
        }*/
        
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
        
        buffer -> corAns = Buffer[0] - '0' - 1; // Convert char to int and adjust for 0-based index

        fgets(Buffer, N, file);
        fgets(Buffer, N, file);
        insert_question(list, buffer);
    }

    QuestionList *bufferList = malloc(sizeof(QuestionList));
    bufferList->head = NULL;
    bufferList->tail = NULL;
    bufferList->size = 0;

    for(; list->size > NUM_QUEST - n; ){
        
        Question *ptr = list->head;

        int randomIndex = (rand() % list->size);

        for(int i = 0; i < randomIndex; i++){
            ptr = ptr->next;
        }

        Question *temp = malloc(sizeof(Question));
        if(!temp){
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }

        *temp = *ptr;
        temp->next = NULL;

        insert_question(bufferList, temp);
        delete_question(list, randomIndex);
    }

    *list = *bufferList;
    free(bufferList);
    

    fclose(file);
}

void updateHighscore(char* filename, Score* score) {
    Score highscore[5]; 
    FILE *file = fopen(filename, "r");
    char Buffer[N];

    if (file == NULL) {
        fprintf(stderr, "File could not be opened\n");
        return;
    }

    fgets(Buffer, N, file);
    fgets(Buffer, N, file);
    for (int i = 0 ; i < 5 ; i++) {
        fgets(Buffer, N, file);
        char c;
        int j = 3;
        int k = 0;
        char buffer[N];
        while((c = Buffer[j]) != ' ') {
            buffer[k++] = c;
            j++;
        }
        buffer[k++] = '\0';
        highscore[i].name = strdup(buffer);


        char buffer1[N];
        k = 0;
        j++;
        while((c = Buffer[j]) != ' '){
            buffer1[k++] = c;
            j++;
        }
        buffer1[k++] = '\0';
        highscore[i].surname = strdup(buffer1);

        int decimal = 1;
        j = j+3;
        highscore[i].score = 0.0;
        while((c = Buffer[j]) != '\n') {
            if (c == ' ') {
                decimal--;
            }
            if(c >= '0' && c <= '9') {
            highscore[i].score += pow(10, decimal--)*(c - '0');
            }
            j++;
        }

    }
    
    fclose(file);


    int j = 0;
    Score newHighscore[5];
    for (int i = 0 ; i < 5 ; i++) {
        if (highscore[i].score < score -> score && j == 0) {
            newHighscore[i] = *score;
            j = 1;
        } else if(j == 1) {
            newHighscore[i] = highscore[i-j];
        } else {
            newHighscore[i] = highscore[i];
        }
    }

    
    file = fopen(filename, "w");

    fputs("Highscorelist\n", file);
    fputs("\n", file);
    for (int i = 0 ; i < 5 ; i++) {
        fprintf(file, "%d. %s %s : %5.2lf\n", i+1, newHighscore[i].name, newHighscore[i].surname, newHighscore[i].score);
    }
    fclose(file);

}