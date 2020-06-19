//
// Created by chang on 2020/6/19.
//
#include"student.h"

int menu()
{
    char n;
    do{
        system("cls");
        printf("\t\t\t|-------------------------------------------------|\n");
        printf("\t\t\t|      *****ѧ������ϵͳ*****                     |\n");
        printf("\t\t\t|-------------------------------------------------|\n");
        printf("\t\t\t|          1.ѧ���ɼ�¼��                         |\n");
        printf("\t\t\t|          2.ѧ���ɼ�����                         |\n");
        printf("\t\t\t|          3.�ɼ����޸�                           |\n");
        printf("\t\t\t|          4.ѧ���ɼ�ɾ��                         |\n");
        printf("\t\t\t|          5.�˳�����                             |\n");
        printf("\t\t\t---------------------------------------------------\n");
        printf("\t\t\t��ѡ��1-5��");
        n=_getch();
    }while(n<'0'||n>'5');
    return(n-48);
}

void login()
{
    system("CLS");
    student*current=list.head;
    while(current->next!=NULL)
        current=current->next;
    student* temp=(student*)malloc(sizeof(student));
    printf("�������ѧ����ѧ�ţ�");
    scanf("%lld",&temp->num);

    printf("�������ѧ����������");
    scanf("%s",temp->name);

    printf("�������ѧ�������䣺");
    scanf("%d",&temp->age);

    printf("�������ѧ���ĳɼ���");
    scanf("%f",&temp->score);

    list.size++;

    printf("¼����ϣ�\n");
    temp->next=NULL;
    current->next=temp;
}

void delete()
{
    system("CLS");
    if(list.size==0)
    {
        printf("\t\t\tNo students!\n");
        return;
    }
    long long a;
    printf("������Ҫɾ����ѧ��ѧ��");
    scanf("%lld",&a);
    student*current=list.head;
    while(current->next!=NULL)
    {
        if(current->next->num==a)
            break;
        current=current->next;
    }
    if(current->next==NULL)
    {
        printf("Not found!\n");
        return;
    }
    student* temp=current->next;
    current->next=current->next->next;
    free(temp);
    list.size--;

    printf("ɾ����ϣ�\n");
}

void Read()              //���ļ��е����ݶ��뵽�����С�
{
    list.size = 0;
    list.head=(student*)malloc(sizeof(student));
    list.head->next = NULL;
    student* current = (student*)malloc(sizeof(student)),*prev=NULL;
    FILE* fp;
    fp = fopen("student.txt", "rb");
    while (fread(current, sizeof(student), 1, fp) == 1)
    {
        if (list.head->next == NULL)
            list.head->next = current;
        else
            prev->next = current;
        prev = current;
        current = (student*)malloc(sizeof(student));
        list.size++;
    }
    free(current);
    fclose(fp);
}

void Save()              //�������е����ݱ��浽�ļ��С�
{
    FILE* fp;
    fp = fopen("student.txt", "wb");
    student* current=list.head->next;
    while (current != NULL)
    {
        fwrite(current, sizeof(student), 1, fp);
        current = current->next;
    }
    fclose(fp);
}

void Show()                        //չʾ�����Ϣ��
{
    if(list.size==0)
    {
        printf("No students!");
        return;
    }
    student*head=list.head->next;
    student*tail=head;
    while(tail->next!=0)
        tail=tail->next;
    char a[20];
    long long b;
    int c;
    float d;
    for (student* i = head; i != tail; i=i->next) {
        for (student* j = i->next; j != NULL; j=j->next) {
            if(i->score<j->score)
            {
                strcpy(a,i->name);
                strcpy(i->name,j->name);
                strcpy(j->name,a);

                b=i->num;
                i->num=j->num;
                j->num=b;

                c=i->age;
                i->age=j->age;
                j->age=c;

                d=i->score;
                i->score=j->score;
                j->score=d;
            }
        }
    }
    student* current=list.head->next;
    system("cls");
    if (current == NULL)
    {
        printf("\t\t\tNo student!\n");
        return;
    }
    printf("\t\t\tname\t\tage\t\tnumber\t\tscore\n");
    while (current != NULL)
    {
        printf("\t\t\t%s\t\t%d\t\t%lld\t\t%f\n", current->name, current->age,current->num,current->score);
        current = current->next;
    }
}

void change()
{
    system("CLS");
    if(list.size==0)
    {
        printf("\t\t\tNo students!\n");
        return;
    }
    long long a;
    printf("������Ҫɾ����ѧ��ѧ��");
    scanf("%lld",&a);
    student*current=list.head;
    while(current->next!=NULL)
    {
        if(current->next->num==a)
            break;
    }
    if(current->next==NULL)
    {
        printf("Not found!");
        return;
    }
    float b;
    printf("������Ҫ�޸ĵĳɼ���");
    scanf("%f",&b);
    current->next->score=b;
    printf("�޸���ϣ�\n");
}
