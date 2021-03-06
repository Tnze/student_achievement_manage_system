/*
    author: Tnze
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

//清屏
#ifdef _MSC_VER
#include <windows.h>
#define clean_screen() windows("cls")
#else
#define clean_screen() printf("\033[2J")               
#endif

#define clean_input_buff() while ((c = getchar()) != EOF && c != '\n') //清输入缓冲区

//读一个数字
int read_num()
{
    int num = -1;
    scanf("%d", &num);
    return num;
}

//输入记录模式
void uurujilu(void)
{
    clean_screen();
    printf("Please input student record: (line for each)\n"
           "format: [Name] [ID] [Engl] [Math] [Clag]\n"
           "Type a space at the end of line for finish input\n");
    FILE *data = fopen("./data", "at"); //open data file
    char name[32];
    int id, engl, math, clag;
    while (scanf("%s %d %d %d %d", name, &id, &engl, &math, &clag) != EOF)
    {
        if (!strcmp(name, "end"))
            break;
        fprintf(data, "%s %d %d %d %d\n", name, id, engl, math, clag);
        if (getchar() != '\n')
            break;
    }
    fclose(data); //close file
}

//查询记录
void iaxpjilu()
{
    for (;;)
    {
        clean_screen();
        printf(
            "Please type the function you need: [1-3]\n"
            "   [1]Search student by Name or ID\n"
            "   [2]Print max score students\n"
            "   [3]Print non-pass students\n"
            "   [4]Back\n");

        FILE *data;
        char name[32];
        int id, engl, math, clag;

        switch (read_num())
        {
        case 1: //search by key words
            printf("Input key-words: \n");
            char key_words[32];
            scanf("%s", key_words);
            data = fopen("./data", "rt"); //open data file
            while (EOF != fscanf(data, "%s %d %d %d %d", name, &id, &engl, &math, &clag))
                if (strstr(name, key_words) != NULL || atoi(key_words) == id)
                    printf("Name: %s, ID: %d, Engl: %d, Math: %d, Clag: %d\n", name, id, engl, math, clag);

            fclose(data); //close file
            break;
        case 2:                           //find max score
            data = fopen("./data", "rt"); //open data file
            int maxscore = 0;
            while (EOF != fscanf(data, "%s %d %d %d %d", name, &id, &engl, &math, &clag))
                if (engl + math + clag > maxscore)
                    maxscore = engl + math + clag;

            rewind(data); //back to hand
            while (EOF != fscanf(data, "%s %d %d %d %d", name, &id, &engl, &math, &clag))
                if (engl + math + clag == maxscore)
                    printf("Name: %s, ID: %d, Engl: %d, Math: %d, Clag: %d\n", name, id, engl, math, clag);
            fclose(data); //close file
            break;
        case 3:
            printf("Input key-words: \n");
            data = fopen("./data", "rt"); //open data file
            while (EOF != fscanf(data, "%s %d %d %d %d", name, &id, &engl, &math, &clag))
                if (engl < 60 || math < 60 || clag < 60)
                    printf("Name: %s, ID: %d, Engl: %d, Math: %d, Clag: %d\n", name, id, engl, math, clag);

            fclose(data); //close file
            break;
        case 4:
            return;
        default:
            continue;
        }
        char c;
        clean_input_buff();
        getchar();
    }
}

//输出记录模式
void uuiujilu()
{
    FILE *data;
    char name[32];
    int id, engl, math, clag;
    data = fopen("./data", "rt"); //open data file

    while (EOF != fscanf(data, "%s %d %d %d %d", name, &id, &engl, &math, &clag))
        printf("Name: %s, ID: %d, Engl: %d, Math: %d, Clag: %d\n", name, id, engl, math, clag);

    fclose(data); //close file

    char c; //pause
    clean_input_buff();
    getchar();
}

//统计模式
void tsji()
{
    FILE *data;
    char name[32];
    int id, engl, math, clag;

    int max_engl = 0, max_math = 0, max_clag = 0;
    int bjg_engl = 0, bjg_math = 0, bjg_clag = 0;

    data = fopen("./data", "rt"); //open data file

    while (EOF != fscanf(data, "%s %d %d %d %d", name, &id, &engl, &math, &clag))
    {
        if (engl > max_engl)
            max_engl = engl;
        if (math > max_math)
            max_math = math;
        if (clag > max_clag)
            max_clag = clag;

        if (engl < 60)
            bjg_engl++;
        if (math < 60)
            bjg_math++;
        if (clag < 60)
            bjg_clag++;
    }

    fclose(data); //close file

    printf("max score:\n"
           "    English:    %d\n"
           "    Math:       %d\n"
           "    C lang:     %d\n",
           max_engl, max_math, max_clag);
    printf("\n\n"); //hrhh
    printf("disqualify count:\n"
           "    English:    %d\n"
           "    Math:       %d\n"
           "    C lang:     %d\n",
           bjg_engl, bjg_math, bjg_clag);

    char c; //pause
    clean_input_buff();
    getchar();
}

typedef struct
{
    char Name[32];
    int ID;
    int engl, math, clag;
} Student;

//选定一个学生
int choice_student(Student students[], int len)
{
    printf("Input search key-words: \n");
    char key_words[32];
    scanf("%s", key_words);
    getchar(); //吸收\n
    for (int i = 0; i < len; i++)
        if (strstr(students[i].Name, key_words) != NULL || atoi(key_words) == students[i].ID)
        {
            printf("Name: %s, ID: %d, Engl: %d, Math: %d, Clag: %d\n"
                   "If this student is which you wanna choice, type 'y': \n",
                   students[i].Name, students[i].ID, students[i].engl, students[i].math, students[i].clag);

            if (getchar() == 'y')
                return i;
        }
    return -1;
}

//从文件读取学生信息
int load_students(Student students[])
{
    FILE *data;
    char name[32];
    int id, engl, math, clag;
    data = fopen("./data", "rt"); //open data file

    int i = 0;
    while (EOF != fscanf(data, "%s %d %d %d %d", name, &id, &engl, &math, &clag))
    {
        strcpy(students[i].Name, name);
        students[i].ID = id;
        students[i].engl = engl;
        students[i].math = math;
        students[i].clag = clag;
        i++;
    }

    fclose(data); //close file
    return i;
}

//写入更改到文件
void write_data_file(Student students[], int len)
{
    FILE *data;
    char name[32];
    int id, engl, math, clag;
    data = fopen("./data", "wt"); //open data file

    for (int i = 0; i < len; i++)
    {
        if (strcmp(students[i].Name, "removed"))
            fprintf(data, "%s %d %d %d %d\n",
                    students[i].Name,
                    students[i].ID,
                    students[i].engl,
                    students[i].math,
                    students[i].clag);
    }

    fclose(data); //close file
}

int if_more_than(Student *s1, Student *s2)
{
    int sa1 = (s1->engl + s1->math + s1->clag);
    int sa2 = (s2->engl + s2->math + s2->clag);
    if (sa1 == sa2)
        return s1->ID > s2->ID;
    else
        return sa1 > sa2;
}

int if_less_than(Student *s1, Student *s2)
{
    int sa1 = (s1->engl + s1->math + s1->clag);
    int sa2 = (s2->engl + s2->math + s2->clag);
    if (sa1 == sa2)
        return s1->ID < s2->ID;
    else
        return sa1 < sa2;
}

//冒泡排序
void bubble(Student array[], int len)
{
    for (int j = 0; j < len; j++)
    {
        int count = 0;
        for (int i = 1; i < len - j; i++)
        {
            if (if_more_than(&array[i - 1], &array[i]))
            {
                // swap(array + i - 1, array + i);

                Student t = array[i - 1];
                array[i - 1] = array[i];
                array[i] = t;

                count++;
            }
        }
        if (!count)
            break;
    }
}

//快速排序
void quickSort(Student array[], int len)
{
    int i = 0;
    int j = len - 1;
    int flag = 0;
    Student *key = &array[0];
    while (i != j)
    {
        while (j > i)
        {
            if (flag ? if_more_than(&array[i], key) : if_less_than(&array[j], key))
            {
                // swap(array + i, array + j);
                Student t = array[j];
                array[j] = array[i];
                array[i] = t;
                break;
            }
            flag ? i++ : j--;
        }
        flag = !flag;
    }
    if (i > 1)
        quickSort(array, i);
    if (i < len - 2)
        quickSort(array + i + 1, len - 1 - i);
}

void print_student(Student *s)
{
    printf("Name: %s, ID: %d, Engl: %d, Math: %d, Clag: %d\n", s->Name, s->ID, s->engl, s->math, s->clag);
}

void change_information(Student *s)
{
    print_student(s);
    printf(
        "Please select which information you wanna change: [1-6]\n"
        "   [1]Name\n"
        "   [2]ID\n"
        "   [3]English score\n"
        "   [4]Math score\n"
        "   [5]C language score\n"
        "   [6]cancel\n");
    switch (read_num())
    {
    case 1:
        printf("Old name is %s, please input new name: ", s->Name);
        scanf("%s", s->Name);
        break;
    case 2:
        printf("Old ID is %d, please input new ID: ", s->ID);
        scanf("%d", &s->ID);
        break;
    case 3:
        printf("Old English score is %d, please input new English score: ", s->engl);
        scanf("%d", &s->engl);
        break;
    case 4:
        printf("Old math score is %d, please input new math score: ", s->math);
        scanf("%d", &s->math);
        break;
    case 5:
        printf("Old C language score is %d, please input new C language score: ", s->clag);
        scanf("%d", &s->clag);
        break;
    case 6:
        return;
    }
}

double solve_average_score(Student *s)
{
    return (s->engl + s->math + s->clag) / 3.0;
}

//更新记录模式
void ggxnjilu_mode()
{
    Student students[2048];
    int len = load_students(students);

    for (;;)
    {
        clean_screen();
        printf(
            "Please type the function you need: [1-5]\n"
            "   [1]Change one's information\n"
            "   [2]Sort\n"
            "   [3]Solve one's average score\n"
            "   [4]Remove student\n"
            "   [5]Save and back\n");

        switch (read_num())
        {
        case 1: //Change one's information
            change_information(&students[choice_student(students, len)]);
            break;
        case 2:
            quickSort(students, len);
            // bubble(students, len);
            break;
        case 3:
            printf("Average score: %.2lf", solve_average_score(&students[choice_student(students, len)]));
            break;
        case 5:
            strcpy(students[choice_student(students, len)].Name, "removed");
            printf("Remove successed! \n");
            write_data_file(students, len);
            return;
        }
        char c;
        clean_input_buff();
        getchar();
    }
}

int main(void)
{
    //create file if not exist
    FILE *f;
    if ((f = fopen("./data", "r")) == NULL)
        fclose(fopen("./data", "w"));
    else
        fclose(f);
    //read cmd
    for (;;)
    {
        clean_screen();
        printf(
            "Please type the mode you need: [1-6]\n"
            "   [1]Input mode\n"
            "   [2]Search mode\n"
            "   [3]Update mode\n"
            "   [4]Count mode\n"
            "   [5]Output mode\n"
            "   [6]Exit\n");
        switch (read_num())
        {
        case 1:
            uurujilu();
            break;
        case 2:
            iaxpjilu();
            break;
        case 3:
            ggxnjilu_mode();
            break;
        case 4:
            tsji();
            break;
        case 5:
            uuiujilu();
            break;
        case 6: //Exit
            clean_screen();
            printf("Thanks for use!\n");
            return 0;
        }
    }
}
