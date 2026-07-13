#ifndef QUIZ_H
#define QUIZ_H
#define N 1024
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

typedef struct Score{
    char* name;
    char* surname;
    double score;
} Score;

void print_question(QuestionList* list, int idx);
void print_question_list(QuestionList* list);
int answer_question(QuestionList* list, int idx);
void insert_question(QuestionList* list, Question* quest);
void delete_question(QuestionList* list, int idx);
void read_question_list(QuestionList* list, int n, const char* filename);
Question read_question();
double quiz(QuestionList* list, QuestionList* falseList, int numQuestions);
void updateHighscore(char* filename, Score* score);
void printHighscore(char* filename);
void write_question(char* filename, Question* Question);



#endif /* QUIZ_H */