#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

/***
 * �����������ļ�
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
//��Ŀ����
int SubjectNum = 3;
long size = sizeof(struct STU);

//�������
int cmpid(const void *a, const void *b)
{ //ѧ������
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    return strcmp(pa->id, pb->id);
}
int cmpname(const void *a, const void *b)
{ //��������
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    return strcmp(pa->name, pb->name);
}
int cmpmath(const void *a, const void *b)
{ //��ѧ����
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    if (pa->math != pb->math)
        return pa->math - pb->math;
    else
        return strcmp(pa->id, pb->id);
}
int cmpenglish(const void *a, const void *b)
{ //Ӣ������
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    if (pa->english != pb->english)
        return pa->english - pb->english;
    else
        return strcmp(pa->id, pb->id);
}
int cmpcs(const void *a, const void *b)
{ //computer science����
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    if (pa->cs != pb->cs)
        return pa->cs - pb->cs;
    else
        return strcmp(pa->id, pb->id);
}
int cmpscore(const void *a, const void *b)
{ //�ܷ�����
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    if (pa->score != pb->score)
        return pa->score - pb->score;
    else
        return strcmp(pa->id, pb->id);
}
int cmpaver(const void *a, const void *b)
{ //ƽ��������
    STU *pa = (STU *)a;
    STU *pb = (STU *)b;
    if (pa->aver != pb->aver)
        return pa->aver - pb->aver;
    else
        return strcmp(pa->id, pb->id);
}

void echo()
{
    printf("ѧ���ɼ�����ϵͳ\n");
    printf("1--��ʾ����ѧ���ĳɼ���Ϣ\n");
    printf("2--����ѧ����Ϣ���ֺܷ�ƽ����\n");
    printf("3--����ѧ�Ų�ѯ��ѧ���Ļ�����Ϣ\n");
    printf("4--����ѧ���޸�ĳѧ����Ϣ\n");
    printf("5--����ѧ��ɾ��ĳѧ����Ϣ\n");
    printf("6--��ѧ����Ϣ��������\n");
    printf("0--�˳�����\n");
    printf("��������ʹ�ù���:");
}

void pressJump()
{
    system("pause");
    system("cls");
    echo();
}

//��ʼ��
void init()
{
    printf("���ڽ��г�ʼ��\n");
    //Ϊ���������Ż����̵�
    FILE *fp;
    if ((fp = fopen(file, "r")) == NULL)
    {
        printf("�޷����ļ��򲻴����ļ�%s\n", file);
        printf("�������µ��ļ�%s\n", file);
        fp = fopen(file, "w");
        printf("%s�ļ������ɹ�\n", file);
    }
    fclose(fp);
}

//���ļ�
FILE *openFile(char *mode)
{
    FILE *fp;
    if ((fp = fopen(file, mode)) == NULL)
    {
        printf("�޷����ļ�%s\n", file);
        exit(0);
    }
    return fp;
}

//��ʾ����ѧ���ɼ���Ϣ
void queryAllInfo()
{
    FILE *fp = openFile("r");
    struct STU CurrentSTU;
    char ch = fgetc(fp);
    if (ch == EOF)
    {
        printf("û��ѧ����Ϣ��\n");
    }
    else
    {
        fseek(fp, 0L, SEEK_SET);
        fread(&CurrentSTU, size, 1, fp);
        printf("   ѧ��       ����     Math  CS English  �ܷ�  ƽ����\n");
        while (!feof(fp))
        {
            printf("%12s  %-7s %5.1f %5.1f %5.1f %5.1f %6.2f\n",
                   CurrentSTU.id, CurrentSTU.name, CurrentSTU.math, CurrentSTU.cs, CurrentSTU.english, CurrentSTU.score, CurrentSTU.aver);
            fread(&CurrentSTU, size, 1, fp);
        }
    }

    fclose(fp);
}

//����ѧ����Ϣ�������ֺܷ�ƽ����
void addNewInfo()
{
    FILE *fp = openFile("ab+");
    struct STU NewStu;
    struct STU CurrentStu;
    int isQuery = 0;
    printf("������ѧ�ţ�");
    scanf("%s", &NewStu.id);
    while (!feof(fp))
    {
        fread(&CurrentStu, size, 1, fp);
        if (strcmp(CurrentStu.id, NewStu.id) == 0)
            isQuery = 1;
    }
    if (isQuery)
    {
        printf("��ѧ���Ѵ���\n");
        return;
    }
    printf("���������֣�");
    scanf("%s", &NewStu.name);
    printf("������math������");
    scanf("%lf", &NewStu.math);
    printf("������computer science������");
    scanf("%lf", &NewStu.cs);
    printf("������english������");
    scanf("%lf", &NewStu.english);
    NewStu.score = NewStu.math + NewStu.cs + NewStu.english;
    NewStu.score = (double)NewStu.score;
    NewStu.aver = NewStu.score / SubjectNum;
    fwrite(&NewStu, size, 1, fp);
    printf("д��ɹ�\n");
    fclose(fp);
}

//����ѧ�Ų�ѯ��Ϣ
void queryIdInfo()
{
    FILE *fp = openFile("r");
    struct STU CurrentSTU;
    int flag = 0;
    char m[20];
    printf("������ѧ�ţ�\n");
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
        printf("δ�ҵ���ѧ����Ϣ!\n");
        return;
    }
    else
    {
        printf("ѧ��: %s\n", CurrentSTU.id);
        printf("����: %s\n", CurrentSTU.name);
        printf("Math: %.1lf\n", CurrentSTU.math);
        printf("Computer Science: %.1lf\n", CurrentSTU.cs);
        printf("English: %.1lf\n", CurrentSTU.english);
        printf("�ܷ�: %.1lf\n", CurrentSTU.score);
        printf("ƽ����: %.1lf\n", CurrentSTU.aver);
    }
    fclose(fp);
}

//�޸���Ϣ
void updateInfo()
{
    int flag, fflag = 0; //flag �Ƿ���� sflag �Ƿ��޸Ŀ�Ŀ fflag �Ƿ��ҵ�����
    char nid[20], nname[20];
    double nscore, naver;
    STU stu;
    FILE *fp = fopen(file, "r+");
    printf("������ѧ�ţ�");
    scanf("%s", &nid);
    while (fread(&stu, size, 1, fp) == 1) //�����ļ� Ѱ�Ҷ���
    {
        if (strcmp(stu.id, nid) == 0) //�ҵ���������޸�
        {
            printf("��ѧ����Ϣ����\n");
            printf("   ѧ��       ����     Math  CS English  �ܷ�  ƽ����\n");
            printf("%12s  %-7s %5.1f %5.1f %5.1f %5.1f %6.2f\n",
                   stu.id, stu.name, stu.math, stu.cs, stu.english, stu.score, stu.aver);
            flag = 0;  //��ʼ��
            fflag = 1; //�ҵ�����
            printf("�Ƿ��޸�ѧ��\n��------1(��0������κ���)\t��------0\n");
            scanf("%d", &flag);
            if (flag)
            {
                printf("�������޸ĺ�ѧ�ţ�");
                scanf("%s", &nid);
                strcpy(stu.id, nid);
            }
            printf("�Ƿ��޸�����\n��------1(��0������κ���)\t��------0\n");
            scanf("%d", &flag);
            if (flag)
            {
                printf("�������޸ĺ�������");
                scanf("%s", &nname);
                strcpy(stu.name, nname);
            }
            printf("�Ƿ��޸ķ���\n��------1(��0������κ���)\t��------0\n");
            scanf("%d", &flag);
            if (flag)
            {
                int sflag;
                double nmath, ncs, nenglish;
                printf("�Ƿ��޸�math����\n��------1(��0������κ���)\t��------0\n");
                scanf("%d", &sflag);
                if (sflag)
                {
                    printf("�������޸ĺ������");
                    scanf("%lf", &nmath);
                    stu.math = nmath;
                }
                printf("�Ƿ��޸�computer science����\n��------1(��0������κ���)\t��------0\n");
                scanf("%d", &sflag);
                if (sflag)
                {
                    printf("�������޸ĺ������");
                    scanf("%lf", &ncs);
                    stu.cs = ncs;
                }
                printf("�Ƿ��޸�english����\n��------1(��0������κ���)\t��------0\n");
                scanf("%d", &sflag);
                if (sflag)
                {
                    printf("�������޸ĺ������");
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
        printf("û�д���!\n");
    else
        printf("�޸ĳɹ�!\n");
    fclose(fp);
}

//ɾ����Ϣ
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
        printf("�޷����ļ�\n");
        exit(0);
        return;
    }
    printf("ѧ��ѧ�ţ�");
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
        printf("����ɾ���ɹ�\n");
    }
    else
    {
        printf("δ�ҵ���ѧ����Ϣ!\n");
    }
}

//����
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
    printf("��ѡ���������\n1.��ѧ������\n2.����������\n3.��Math��������\n4.��English��������\n5.��computer science��������\n6.���ܷ�����\n7.��ƽ��������\n");
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
        printf("�Ƿ����룡\n");
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
            printf("�������\n");
            pressJump();
        }
        scanf("%d", &n);
    }
}
