#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<string.h>
#include<conio.h>
#include <windows.h>

/***
 * 以下是配置文件
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
    printf("学生成绩管理系统\n");
    printf("1--显示所有学生的成绩信息\n");
    printf("2--新增学生信息与总分和平均分\n");
    printf("3--根据学号查询改学生的基本信息\n");
    printf("4--根据学号修改某学生信息\n");
    printf("5--根据学号删除某学生信息\n");
    printf("6--对学生信息进行排序\n");
    printf("0--退出程序\n");
    printf("请输入编号使用功能:");
}


void pressJump(){
    system("pause");
    system("cls");
    echo();
}

//初始化
void init(){
    printf("正在进行初始化\n");
    //为后续性能优化做铺垫 嘻嘻
    Sleep(1000);
    FILE *fp;
    if((fp = fopen(file,"r")) == NULL){
        printf("无法打开文件或不存在文件%s\n",file);
        printf("将创建新的文件%s\n",file);
        fp = fopen(file, "w");
        printf("%s文件创建成功\n",file);
    }
    fclose(fp);
}

//打开文件
FILE *openFile(char *mode){
    FILE *fp;
    if((fp = fopen(file,mode)) == NULL){
        printf("无法打开文件%s\n",file);
        exit(0);
    }
    return fp;
}

//显示所有学生成绩信息
void queryAllInfo(){
    FILE *fp = openFile("r");
    struct STU CurrentSTU;
    char ch = fgetc(fp);
    if(ch == EOF){
        printf("没有学生信息！\n");
    }
    else{
        fseek(fp, 0L, SEEK_SET);
        fread(&CurrentSTU, size, 1, fp);
        printf("   学号      名字     分数\n");
        while(!feof(fp)){ 
            printf("%6s %-11s%7.1f\n",
            CurrentSTU.id, CurrentSTU.name, CurrentSTU.score);
            fread(&CurrentSTU, size, 1, fp);
        }
    }

    fclose(fp);
}

//新增学生信息并计算总分和平均分
void addNewInfo(){
    FILE *fp = openFile("ab+");
    struct STU NewStu;
    printf("请输入学号：");
    scanf("%s",&NewStu.id);
    printf("请输入名字：");
    scanf("%s",&NewStu.name);
    printf("请输入分数：");
    scanf("%lf",&NewStu.score);
    NewStu.score = (double)NewStu.score;
    fwrite(&NewStu, size, 1, fp);
    printf("写入成功");
    fclose(fp);
}

//根据学号查询信息
void queryIdInfo(){
    printf("TEST");
}

//修改信息
void updateInfo(){
;
}
//删除信息
void deleteInfo(){
;
}


//排序
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