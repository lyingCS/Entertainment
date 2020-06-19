//
// Created by chang on 2020/6/19.
//

#ifndef MANAGEMENT_STUDENT_H
#define MANAGEMENT_STUDENT_H
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>


typedef struct student
{
    long long num;
    char name[20];
    int age;
    float score;
    struct student *next;
}student;

struct list
{
    student *head;
    int size;
}list;

int menu();
void login();
void delete();
void Read();                      //把文件中的数据读入到链表中。
void Save();                       //把链表中的数据保存到文件中。
void Show();
void change();
#endif //MANAGEMENT_STUDENT_H
