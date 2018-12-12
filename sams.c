#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define clean_screen() printf("\033[2J")                               //清屏
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

int main(void)
{
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