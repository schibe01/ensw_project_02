#ifndef QUIZ_H
#define QUIZ_H
#define LENGHT 1024;

typedef struct Question {
    char *quest;
    char *ans1;
    char *ans2;
    char *ans3;
    char *ans4;
    int corAns;
    struct Question* next;
} Question;

typedef struct {
    Question* head;
    size_t size;
    int round;
    double score;
} QuestionList;

void print_question(QuestionList* list, int idx);
Question answer_question(QuestionList* list, int idx);
void insert_question(QuestionList* list, Question quest);
void delete_question(QuestionList* list, int idx);
Question read_question();




#endif /* QUIZ_H */
