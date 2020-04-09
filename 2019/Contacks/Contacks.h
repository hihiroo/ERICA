#ifndef CONTACKS
#define CONTACKS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{false,true} boolean;

typedef struct Info
{
    char *name;
    char *phone_number;
    char *birth;
} Info;

typedef struct Node
{
    Info *data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct list
{
    int size;
    Node *top;
    Node *bottom;
} list;

void init_list(list **a);
void make_Info(Info **d, char *name, char *birth, char *ph);
void push(list *a, Info *mid);
void pop(list *a, Node *mid);
void swap_data(list *a, Node *A1, Node *A2);
void sort(list *a);
boolean empty(list *a);
void Read_File(list *contacks_list);
void Write_File(list *a);
void Registration(list *a);
void Delete(list *a);
void ShowAll(list *a);
void FindByBirth(list *a);
int compare(Info *a, Info *b);

#endif