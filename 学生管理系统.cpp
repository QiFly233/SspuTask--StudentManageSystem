#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<string.h>
#include<conio.h>
#include <windows.h>

/***
 * �����������ļ�
***/
char file[] = "students.dat";
struct STU
{
    char id[20];
    char name[20];
    double score;
};
long size = sizeof(struct STU);

void echo(){
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


void pressJump(){
    system("pause");
    system("cls");
    echo();
}

//��ʼ��
void init(){
    printf("���ڽ��г�ʼ��\n");
    //Ϊ���������Ż����̵� ����
    Sleep(1000);
    FILE *fp;
    if((fp = fopen(file,"r")) == NULL){
        printf("�޷����ļ��򲻴����ļ�%s\n",file);
        printf("�������µ��ļ�%s\n",file);
        fp = fopen(file, "w");
        printf("%s�ļ������ɹ�\n",file);
    }
    fclose(fp);
}

//���ļ�
FILE *openFile(char *mode){
    FILE *fp;
    if((fp = fopen(file,mode)) == NULL){
        printf("�޷����ļ�%s\n",file);
        exit(0);
    }
    return fp;
}

//��ʾ����ѧ���ɼ���Ϣ
void queryAllInfo(){
    FILE *fp = openFile("r");
    struct STU CurrentSTU;
    char ch = fgetc(fp);
    if(ch == EOF){
        printf("û��ѧ����Ϣ��\n");
    }
    else{
        fseek(fp, 0L, SEEK_SET);
        fread(&CurrentSTU, size, 1, fp);
        printf("   ѧ��      ����     ����\n");
        while(!feof(fp)){ 
            printf("%6s %-11s%7.1f\n",
            CurrentSTU.id, CurrentSTU.name, CurrentSTU.score);
            fread(&CurrentSTU, size, 1, fp);
        }
    }

    fclose(fp);
}

//����ѧ����Ϣ�������ֺܷ�ƽ����
void addNewInfo(){
    FILE *fp = openFile("ab+");
    struct STU NewStu;
    printf("������ѧ�ţ�");
    scanf("%s",&NewStu.id);
    printf("���������֣�");
    scanf("%s",&NewStu.name);
    printf("�����������");
    scanf("%lf",&NewStu.score);
    NewStu.score = (double)NewStu.score;
    fwrite(&NewStu, size, 1, fp);
    printf("д��ɹ�");
    fclose(fp);
}

//����ѧ�Ų�ѯ��Ϣ
void queryIdInfo(){
    printf("TEST");
}

//�޸���Ϣ
void updateInfo(){
;
}
//ɾ����Ϣ
void deleteInfo(){
;
}


//����
void sortInfo(){
;
}




int main(){

    init();

    echo();

    int n = 0;
    scanf("%d",&n);

    while(n != 0){
        switch(n){
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
        }
        scanf("%d",&n);
    }
}