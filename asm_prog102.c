/*
Program: Student math grade management program
Author: Trịnh Đỗ Duy Hưng
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STUDENT 40

int n = 0;
char stop = 1;
int option = -1;
int student_id[MAX_STUDENT];
float student_grade[MAX_STUDENT];
int max_low_index[2] = {-1, -1};

void max_and_low_index(float *, int);
int menu();
void selected(int);
void addStudents();
void showStudents();
void showHigh_lowest();
int check_exist(int);
int check_edit();
int check_valid(char *);
void edit_grade(int);

int main()
{
    while (stop)
    {
        option = menu();
        selected(option);
        option = -1;
    };
    return 0;
}
void showHigh_lowest()
{
    max_and_low_index(student_grade, n);
    if (max_low_index[0] != -1 && max_low_index[1] != -1)
    {
        printf("\n These are your data:\n ");
        printf("Student ID has highest grade: %d\n ", student_id[max_low_index[0]]);
        printf("Student ID has lowest grade: %d\n ", student_id[max_low_index[1]]);
    }
}
void showStudents()
{
    if (n == 0)
    {
        printf("You need to add students first and choose the option 3 one more time when the menu show up again!");
        addStudents();
    }
    else
    {
        printf("\n These are your class:\n ");
        printf("\n-----------------------------------");
        printf("\n|  STT  |  Student's ID  |  Grade  ");
        printf("\n|-------|----------------|---------");
        int length = sizeof(student_id) / sizeof(student_id[0]);
        for (int i = 0; i < length; i++)
        {
            if (student_id[i] == 0)
            {
                break;
            }
            char i_to_string[100] = "";
            char spaces[100] = "";
            sprintf(i_to_string, "%d", i);
            int total_header_charac = strlen("  STT  ");
            int total_to_string = strlen(i_to_string);
            int total_spaces = total_header_charac - total_to_string;
            for (int sp = 0; sp < total_spaces; sp++)
            {
                strcat(spaces, " ");
            }
            strcat(i_to_string, spaces);

            char stid_to_string[100] = "";
            char stid_spaces[100] = "";
            sprintf(stid_to_string, "%ld", student_id[i]);
            int total_headerstid_charac = strlen("  Student's ID  ");
            int total_stid_to_string = strlen(stid_to_string);
            int total_stid_spaces = total_headerstid_charac - total_stid_to_string;
            for (int sp = 0; sp < total_stid_spaces; sp++)
            {
                strcat(stid_spaces, " ");
            }
            strcat(stid_to_string, stid_spaces);

            printf("\n|%s|%s| %.2f", i_to_string, stid_to_string, student_grade[i]);
            printf("\n|-------|----------------|---------");
        }
        printf("\n");
    }
}
int check_exist(int ids)
{
    int length = sizeof(student_id) / sizeof(student_id[0]);
    for (int i = 0; i <= length; i++)
    {
        if (i > length)
        {
            return 1;
        }
        else
        {
            if (ids == student_id[i])
            {
                return 0;
            }
        }
    }
}
int check_valid(char *user_input)
{
    int i = 0;
    int check_charac = 0;
    if (user_input[0] != '\n')
    {
        for (i; user_input[i] != '\0'; i++)
        {
            if (user_input[i] >= '0' && user_input[i] <= '9')
            {
                check_charac += 1;
                break;
            }
        }
    }
    else
    {
        return -1;
    }
    if (check_charac == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int check_edit()
{
    char yes_no[3];
    printf(" If you want to edit this student's grade, please enter 1, or enter any number to cancel: ");
    fgets(yes_no, sizeof(yes_no), stdin);
    return atoi(yes_no);
}
void edit_grade(int ids)
{
    int length = sizeof(student_id) / sizeof(student_id[0]);
    int index_student;
    for (int i = 0; i <= length; i++)
    {
        if (ids == student_id[i])
        {
            index_student = i;
            break;
        }
    }
    printf("\n---------------EDIT--------------");
    printf("\n|Please enter student's grade for ID - %ld: ", ids);
    scanf("%f", &student_grade[index_student]);
    printf("\n------------END EDIT-------------\n");
}
void addStudents()
{
    printf("\n ========================== ADD DATA ==========================\n");
    printf(" Please enter the total number of students (1<n<%d): ", MAX_STUDENT);
    scanf("%d", &n);
    if (n < MAX_STUDENT && n >= 2)
    {
        printf("\n Please enter student's id and grade");
        int length = sizeof(student_id) / sizeof(student_id[0]);
        int count = 0;
        int no = 0;
        if (student_id[0] != 0)
        {
            for (int spread = 0; spread < length; spread++)
            {
                if (student_id[spread] == 0)
                {
                    break;
                }
                no += 1;
            }
        }
        while (count < n)
        {
            char student_id_input[MAX_STUDENT];
            fgets(student_id_input, sizeof(student_id_input), stdin);
            if (check_valid(student_id_input))
            {
                printf("\n Please enter student's id: ");
                fgets(student_id_input, sizeof(student_id_input), stdin);
                int check_valid_input = check_valid(student_id_input);
                if (check_valid_input == 1)
                {
                    int ids = atoi(student_id_input);
                    int check = check_exist(ids);
                    if (check)
                    {
                        student_id[no] = ids;
                        printf(" Please enter student's grade: ");
                        scanf("%f", &student_grade[no]);
                        no += 1;
                        count += 1;
                    }
                    else
                    {
                        int yes_edit;
                        yes_edit = check_edit();
                        if (yes_edit == 1)
                        {
                            edit_grade(ids);
                        }else{
                            printf(" This student id already exists, please add another. Press Enter button to continue");
                        }
                    }
                }
                else if (check_valid_input == 0)
                {
                    printf("Not valid");
                }
            }
        }
        showStudents();
        printf("\n ======================== END ADD DATA ======================== \n");
    }
    else
    {
        printf(" Your number is not valid (1<n<%d) ", MAX_STUDENT);
        addStudents();
    }
}
void selected(int option)
{
    switch (option)
    {
    case 1:
        addStudents();
        break;
    case 2:
        showStudents();
        break;
    case 3:
        showHigh_lowest();
        break;
    case 4:
        stop = 0;
        break;
    default:
        break;
    }
}
void max_and_low_index(float *a, int n)
{
    if (n == 0)
    {
        printf("You need to add students first and choose the option 3 one more time when the menu show up again!");
        addStudents();
    }
    else
    {
        int length = sizeof(student_id) / sizeof(student_id[0]);
        int i, max_i, low_i = 0;
        float max, low = a[i];
        for (i = 1; i < length; i++)
        {
            if (a[i] == 0)
            {
                break;
            }
            if (a[i] > max)
            {
                max = a[i];
                max_i = i;
            }
            if (a[i] < low)
            {
                low = a[i];
                low_i = i;
            }
        }
        max_low_index[0] = max_i;
        max_low_index[1] = low_i;
    }
}
int menu()
{
    char itemSelected[10];
    printf("\n ============== Student grade management system ===============\n");
    printf("\t Press 1: Enter your student's id and grade \n");
    printf("\t Press 2: Show all data \n");
    printf("\t Press 3: Show who has highest, and who has lowest grade \n");
    printf("\t Press 4: Exit ");
    printf("\n ==============================================================\n");
    printf("Enter your option: ");
    fgets(itemSelected, sizeof(itemSelected), stdin);
    if (check_valid(itemSelected))
    {
        int select = atoi(itemSelected);
        if (select == 0)
        {
            fgets(itemSelected, sizeof(itemSelected), stdin);
            select = atoi(itemSelected);
            return select;
        }
        else
        {
            return select;
        }
    }
    else
    {
        printf("Not valid. Enter a number not string or character, please!");
        return -1;
    }
}