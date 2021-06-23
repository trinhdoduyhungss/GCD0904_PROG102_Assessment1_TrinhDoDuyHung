/*
Program: Student math grade management program
Author: Trịnh Đỗ Duy Hưng
Solution: 1 - Get index from insertion sort to find who has highest or lowest grade
*/

#include<stdio.h>
#include <stdlib.h>
#define MAX_STUDENT 40

int n=0;
char stop = 1;
int option=-1;
int student_id[MAX_STUDENT];
float student_grade[MAX_STUDENT];
int max_low_index[2] = {-1,-1};


void max_and_low_index(float*, int);
int menu();
void selected(int);
void addStudents();
void showStudents();
void showHigh_lowest();
int check_exist(int);
int check_valid(char*);

int main(){
    while(stop){
        option = menu();
        selected(option);
        option = -1;
    };
    return 0;
}
void showHigh_lowest(){
    max_and_low_index(student_grade, n);
    if(max_low_index[0] != -1 && max_low_index[1] != -1){
        printf("\n These are your data:\n ");
        printf("Student ID has highest grade: %d\n ", student_id[max_low_index[0]]);
        printf("Student ID has lowest grade: %d\n ", student_id[max_low_index[1]]);
    }
}
void showStudents(){
    if(n == 0 || max_low_index[0] != -1 && max_low_index[1] != -1){
        printf("You need to add students first and choose the option 3 one more time when the menu show up again!");
        addStudents();
    }else{
        printf("\n These are your data:\n ");
        for(int i=0; i<n; i++){
            printf("\nSTT %d - Student's ID %ld - Grade %.2f \n", i, student_id[i], student_grade[i]);
        }
    }
}
int check_exist(int ids){
    int length = sizeof(student_id)/sizeof(student_id[0]);
    for(int i=0;i<=length;i++){
        if (i > length){
            return 1;
        }else{
            if (ids == student_id[i]){
                return 0;
            }
        }
    }
}
int check_valid(char *user_input){
    int i = 0;
    int check_charac = 0;
    if(user_input[0] != '\n'){
        for(i; user_input[i] != '\0'; i++){
            if(user_input[i] >= '0' && user_input[i] <= '9'){
               check_charac += 1;
               break;
            }
        }
    }else{
        return -1;
    }
    if(check_charac == 1){
        return 1;
    }else{
        return 0;
    }
}
void addStudents(){
    printf("\n ========================== ADD DATA ==========================\n");
    printf(" Please enter the total number of students (n<%d): ", MAX_STUDENT);
    scanf("%d",&n);
    if(n < MAX_STUDENT){
        printf("\n Please enter student's id and grade");
        int count = 0;
        while(count < n){
            char student_id_input[MAX_STUDENT];
            printf("\n Please enter student's id: ");
            fgets(student_id_input, sizeof(student_id_input), stdin);
            int check_valid_input = check_valid(student_id_input);
            if(check_valid_input==1){
                int ids = atoi(student_id_input);
                int check = check_exist(ids);
                if(check){
                    student_id[count] = ids;
                    printf(" Please enter student's grade: ");
                    scanf("%f", &student_grade[count]);
                    count += 1;
                }else{
                    printf(" This student id already exists, please add another\n");
                }
            }else if(check_valid_input == 0){
                printf("Not valid");
            }
        }
        showStudents();
        printf("\n ======================== END ADD DATA ========================\n");
    }
}
void selected(int option){
    switch (option)
    {
    case 1: addStudents();
        break;
    case 2: showStudents(); 
        break;
    case 3: showHigh_lowest();
        break;
    case 4: stop = 0;
        break;
    default:
        break;
    }
}
void max_and_low_index(float *a, int n){
        if(n == 0){
            printf("You need to add students first and choose the option 3 one more time when the menu show up again!");
            addStudents();
        }
        else{
            int i, max_i, low_i = 0;
            float max, low = a[i];
            for(i = 1; i < n; i++){
                if(a[i] > max){
                    max = a[i];
                    max_i = i;
                }
                if(a[i] < low){
                    low = a[i];
                    low_i = i;
                }
            }
            max_low_index[0] = max_i;
            max_low_index[1] = low_i;
        }
}
int menu(){
    char itemSelected[10];
    printf("\n ============== Student grade management system ===============\n");
    printf("\t 1. Enter your student's id and grade \n");
    printf("\t 2. Show all data \n");
    printf("\t 3. Show who has highest, and who has lowest grade \n");
    printf("\t 4. Exit ");
    printf("\n ==============================================================\n");
    printf("Enter your option: ");
    fgets(itemSelected, sizeof(itemSelected), stdin);
    if(check_valid(itemSelected)){
        int select = atoi(itemSelected);
        return select;
    }else{
       printf("Not valid. Enter a number not string or character, please!");
       return -1;
    }
}