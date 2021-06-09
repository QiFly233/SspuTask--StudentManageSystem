#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

/***
 * 以下是配置文件
***/
char file[] = "students.dat";
struct STU
{
    char id[20];
    char name[20];
    double math;
    double cs;
    double english;
    double score;
    double aver;
};
//科目数量
int SubjectNum = 3;
long size = sizeof(struct STU);

//排序规则
int cmpid(const void *a, const void *b)
{ //学号排序
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    return strcmp(pa->id, pb->id);
}
int cmpname(const void *a, const void *b)
{ //姓名排序
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    return strcmp(pa->name, pb->name);
}
int cmpmath(const void *a, const void *b)
{ //数学排序
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    if (pa->math != pb->math)
        return pa->math - pb->math;
    else
        return strcmp(pa->id, pb->id);
}
int cmpenglish(const void *a, const void *b)
{ //英语排序
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    if (pa->english != pb->english)
        return pa->english - pb->english;
    else
        return strcmp(pa->id, pb->id);
}
int cmpcs(const void *a, const void *b)
{ //computer science排序
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    if (pa->cs != pb->cs)
        return pa->cs - pb->cs;
    else
        return strcmp(pa->id, pb->id);
}
int cmpscore(const void *a, const void *b)
{ //总分排序
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    if (pa->score != pb->score)
        return pa->score - pb->score;
    else
        return strcmp(pa->id, pb->id);
}
int cmpaver(const void *a, const void *b)
{ //平均分排序
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    if (pa->aver != pb->aver)
        return pa->aver - pb->aver;
    else
        return strcmp(pa->id, pb->id);
}

void echo()
{
    printf("学生成绩管理系统\n");
    printf("1--显示所有学生的成绩信息\n");
    printf("2--新增学生信息与总分和平均分\n");
    printf("3--根据学号查询该学生的基本信息\n");
    printf("4--根据学号修改某学生信息\n");
    printf("5--根据学号删除某学生信息\n");
    printf("6--对学生信息进行排序\n");
    printf("0--退出程序\n");
    printf("请输入编号使用功能:");
}

void pressJump()
{
    system("pause");
    system("cls");
    echo();
}

//初始化
void init()
{
    printf("正在进行初始化\n");
    //为后续性能优化做铺垫
    FILE *fp;
    if ((fp = fopen(file, "r")) == NULL)
    {
        printf("无法打开文件或不存在文件%s\n", file);
        printf("将创建新的文件%s\n", file);
        fp = fopen(file, "w");
        printf("%s文件创建成功\n", file);
    }
    fclose(fp);
}

//打开文件
FILE *openFile(char *mode)
{
    FILE *fp;
    if ((fp = fopen(file, mode)) == NULL)
    {
        printf("无法打开文件%s\n", file);
        exit(0);
    }
    return fp;
}

//显示所有学生成绩信息
void queryAllInfo()
{
    FILE *fp = openFile("r");
    struct STU CurrentSTU;
    char ch = fgetc(fp);
    if (ch == EOF)
    {
        printf("没有学生信息！\n");
    }
    else
    {
        fseek(fp, 0L, SEEK_SET);
        fread(&CurrentSTU, size, 1, fp);
        printf("   学号       名字     Math  CS English  总分  平均分\n");
        while (!feof(fp))
        {
            printf("%12s  %-7s %5.1f %5.1f %5.1f %5.1f %6.2f\n",
                   CurrentSTU.id, CurrentSTU.name, CurrentSTU.math, CurrentSTU.cs, CurrentSTU.english, CurrentSTU.score, CurrentSTU.aver);
            fread(&CurrentSTU, size, 1, fp);
        }
    }

    fclose(fp);
}

//新增学生信息并计算总分和平均分
void addNewInfo()
{
    FILE *fp = openFile("ab+");
    struct STU NewStu;
    struct STU CurrentStu;
    int isQuery = 0;
    printf("请输入学号：");
    scanf("%s", &NewStu.id);
    while (!feof(fp))
    {
        fread(&CurrentStu, size, 1, fp);
        if (strcmp(CurrentStu.id, NewStu.id) == 0)
            isQuery = 1;
    }
    if (isQuery)
    {
        printf("该学号已存在\n");
        return;
    }
    printf("请输入名字：");
    scanf("%s", &NewStu.name);
    printf("请输入math分数：");
    scanf("%lf", &NewStu.math);
    printf("请输入computer science分数：");
    scanf("%lf", &NewStu.cs);
    printf("请输入english分数：");
    scanf("%lf", &NewStu.english);
    NewStu.score = NewStu.math + NewStu.cs + NewStu.english;
    NewStu.score = (double)NewStu.score;
    NewStu.aver = NewStu.score / SubjectNum;
    fwrite(&NewStu, size, 1, fp);
    printf("写入成功\n");
    fclose(fp);
}

//根据学号查询信息
void queryIdInfo()
{
    FILE *fp = openFile("r");
    struct STU CurrentSTU;
    int flag = 0;
    char m[20];
    printf("请输入学号：\n");
    scanf("%s", m);

    while (!feof(fp))
    {
        fread(&CurrentSTU, size, 1, fp);
        if (strcmp(CurrentSTU.id, m) == 0)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        printf("未找到该学生信息!\n");
        return;
    }
    else
    {
        printf("学号: %s\n", CurrentSTU.id);
        printf("姓名: %s\n", CurrentSTU.name);
        printf("Math: %.1lf\n", CurrentSTU.math);
        printf("Computer Science: %.1lf\n", CurrentSTU.cs);
        printf("English: %.1lf\n", CurrentSTU.english);
        printf("总分: %.1lf\n", CurrentSTU.score);
        printf("平均分: %.1lf\n", CurrentSTU.aver);
    }
    fclose(fp);
}

//修改信息
void updateInfo()
{
    int flag, fflag = 0; //flag 是否更改 sflag 是否修改科目 fflag 是否找到对象
    char nid[20], nname[20];
    double nscore, naver;
    STU stu;
    FILE *fp = fopen(file, "r+");
    printf("请输入学号：");
    scanf("%s", &nid);
    while (fread(&stu, size, 1, fp) == 1) //遍历文件 寻找对象
    {
        if (strcmp(stu.id, nid) == 0) //找到对象进行修改
        {
            printf("该学号信息如下\n");
            printf("   学号       名字     Math  CS English  总分  平均分\n");
            printf("%12s  %-7s %5.1f %5.1f %5.1f %5.1f %6.2f\n",
                   stu.id, stu.name, stu.math, stu.cs, stu.english, stu.score, stu.aver);
            flag = 0;  //初始化
            fflag = 1; //找到对象
            printf("是否修改学号\n是------1(除0以外的任何数)\t否------0\n");
            scanf("%d", &flag);
            if (flag)
            {
                printf("请输入修改后学号：");
                scanf("%s", &nid);
                strcpy(stu.id, nid);
            }
            printf("是否修改姓名\n是------1(除0以外的任何数)\t否------0\n");
            scanf("%d", &flag);
            if (flag)
            {
                printf("请输入修改后姓名：");
                scanf("%s", &nname);
                strcpy(stu.name, nname);
            }
            printf("是否修改分数\n是------1(除0以外的任何数)\t否------0\n");
            scanf("%d", &flag);
            if (flag)
            {
                int sflag;
                double nmath, ncs, nenglish;
                printf("是否修改math分数\n是------1(除0以外的任何数)\t否------0\n");
                scanf("%d", &sflag);
                if (sflag)
                {
                    printf("请输入修改后分数：");
                    scanf("%lf", &nmath);
                    stu.math = nmath;
                }
                printf("是否修改computer science分数\n是------1(除0以外的任何数)\t否------0\n");
                scanf("%d", &sflag);
                if (sflag)
                {
                    printf("请输入修改后分数：");
                    scanf("%lf", &ncs);
                    stu.cs = ncs;
                }
                printf("是否修改english分数\n是------1(除0以外的任何数)\t否------0\n");
                scanf("%d", &sflag);
                if (sflag)
                {
                    printf("请输入修改后分数：");
                    scanf("%lf", &nenglish);
                    stu.english = nenglish;
                }
                stu.score = stu.math + stu.cs + stu.english;
                stu.aver = stu.score / SubjectNum;
            }
            fseek(fp, -size, SEEK_CUR);
            fwrite(&stu, size, 1, fp);
            goto out;
        }
    }
out:
    if (!fflag)
        printf("没有此人!\n");
    else
        printf("修改成功!\n");
    fclose(fp);
}

//删除信息
void deleteInfo()
{
    FILE *fp = openFile("r");
    struct STU CurrentSTU[10000];
    char s[20];
    int i = 0, n = 0, flag = 0;
    while (!feof(fp))
    {
        fread(&CurrentSTU[i], sizeof(STU), 1, fp);
        i++;
        n = n + 1;
    }
    fclose(fp);
    if ((fp = fopen(file, "w")) == NULL)
    {
        printf("无法打开文件\n");
        exit(0);
        return;
    }
    printf("学生学号：");
    scanf("%s", s);
    for (i = 0; i < n - 1; i++)
        if ((strcmp(CurrentSTU[i].id, s) != 0))
        {
            fwrite(&CurrentSTU[i], size, 1, fp);
        }
        else
        {
            flag = 1;
        }
    fclose(fp);
    if (flag == 1)
    {
        printf("数据删除成功\n");
    }
    else
    {
        printf("未找到该学生信息!\n");
    }
}

//排序
void sortInfo()
{
    FILE *fp = openFile("ab+");
    int people = 0, choice;
    struct STU allstu[10000];
    while (!feof(fp))
    {
        fread(&allstu[people], size, 1, fp);
        people++;
    }
    people--;
    fclose(fp);
    printf("请选择排序规则：\n1.按学号排序\n2.按姓名排序\n3.按Math分数排序\n4.按English分数排序\n5.按computer science分数排序\n6.按总分排序\n7.按平均分排序\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        qsort(allstu, people, sizeof(allstu[0]), cmpid);
        break;
    case 2:
        qsort(allstu, people, sizeof(allstu[0]), cmpname);
        break;
    case 3:
        qsort(allstu, people, sizeof(allstu[0]), cmpmath);
        break;
    case 4:
        qsort(allstu, people, sizeof(allstu[0]), cmpenglish);
        break;
    case 5:
        qsort(allstu, people, sizeof(allstu[0]), cmpcs);
        break;
    case 6:
        qsort(allstu, people, sizeof(allstu[0]), cmpscore);
        break;
    case 7:
        qsort(allstu, people, sizeof(allstu[0]), cmpaver);
        break;
    default:
        printf("非法输入！\n");
        break;
    }
    int i = 0;
    fp = openFile("r+");
    fseek(fp, 0, SEEK_SET);
    while (!feof(fp))
    {
        fwrite(&allstu[i], size, 1, fp);
        i++;
        if (i == people)
            break;
    }
    fclose(fp);
}

int main()
{
    init();
    echo();
    int n = 0;
    scanf("%d", &n);
    while (n != 0)
    {
        switch (n)
        {
        case 1:
            queryAllInfo();
            pressJump();
            break;
        case 2:
            addNewInfo();
            pressJump();
            break;
        case 3:
            queryIdInfo();
            pressJump();
            break;
        case 4:
            updateInfo();
            pressJump();
            break;
        case 5:
            deleteInfo();
            pressJump();
            break;
        case 6:
            sortInfo();
            pressJump();
            break;
        default:
            printf("输入错误！\n");
            pressJump();
        }
        scanf("%d", &n);
    }
}
