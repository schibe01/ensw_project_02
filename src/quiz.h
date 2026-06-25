#ifndef QUIZ_H
#define QUIZ_H
#define LENGHT 1024
#define ANS_NUM 4

typedef struct Question {
    char *quest;
    char *ans[ANS_NUM];
    int corAns;
    struct Question* next;
} Question;

typedef struct {
    Question* head;
    Question* tail;
    size_t size;
    int round;
    double score;
} QuestionList;

void print_question(QuestionList* list, int idx);
void print_question_list(QuestionList* list);
Question answer_question(QuestionList* list, int idx);
void insert_question(QuestionList* list, Question* quest);
void delete_question(QuestionList* list, int idx);
Question read_question();




#endif /* QUIZ_H */