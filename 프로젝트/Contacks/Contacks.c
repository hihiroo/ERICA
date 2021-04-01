#include "Contacks.h"

void init_list(list **a)
{ //리스트 초기화
    *a = (list *)malloc(sizeof(list));
    (*a)->size = 0;
    (*a)->top = NULL;
    (*a)->bottom = NULL;
}

void make_Info(Info **d, char *name, char *birth, char *ph)
{
    *d = (Info *)malloc(sizeof(Info));
    (*d)->name = name;
    (*d)->birth = birth;
    (*d)->phone_number = ph;
}

//linked list에 노드 추가
void push(list *a, Info *d)
{
    Node *k = (Node *)malloc(sizeof(Node)); //노드 생성
    k->data = d;
    k->prev = a->top; //리스트 젤 오른쪽 데이터랑 연결
    k->next = NULL;

    if (a->size == 0)
        a->bottom = k;
    else
        a->top->next = k;
    a->top = k;
    a->size += 1;
    return;
}

//linked list에서 특정 노드 삭제
void pop(list *a, Node *mid)
{
    Node *left, *right;
    left = mid->prev;  //삭제할 노드 왼쪽 노드
    right = mid->next; //오른쪽 노드

    free(mid->data->name);
    free(mid->data->birth);
    free(mid->data->phone_number);
    free(mid->data); //info 구조체 할당 해제
    free(mid);       //노드 할당 해제
    a->size--;

    if (right == NULL)
        a->top = left;
    if (left == NULL)
        a->bottom = right;

    //양옆 데이터 이어붙이기
    if (left != NULL)
        left->next = right;
    if (right != NULL)
        right->prev = left;
    return;
}

//노드 데이터 교환
void swap_data(list *a, Node *A1, Node *A2)
{
    Info *temp;
    temp = A1->data;
    A1->data = A2->data;
    A2->data = temp;
    return;
}

void sort(list *a)
{
    Node *inode = a->bottom;

    for (int i = 0; i < a->size; i++)
    {
        Node *jnode = a->bottom;
        for (int j = 0; j < a->size; j++)
        {
            if (i < j && compare(inode->data, jnode->data) > 0)
            {
                swap_data(a, inode, jnode);
            }
            jnode = jnode->next;
        }
        inode = inode->next;
    }
}

boolean empty(list *a)
{
    return a->size == 0;
}

void Read_File(list *contacks_list)
{
    FILE *contacks_file = fopen("Contacks", "r");

    while (!feof(contacks_file))
    { // 파일의 끝이 아니라면
        char *str = (char *)malloc(sizeof(char) * 50);
        fgets(str, 50, contacks_file); // 최대 50칸짜리 한줄 읽기
        if (strcmp("", str) == 0)
        {
            free(str);
            break;
        }
        char *name = (char *)malloc(sizeof(char) * 21);
        char *birth = (char *)malloc(sizeof(char) * 9);
        char *ph = (char *)malloc(sizeof(char) * 16);
        strcpy(name, strtok(str, " ")); //데이터 저장할 메모리에 자른 문자열 복사
        strcpy(ph, strtok(NULL, " "));
        strcpy(birth, strtok(NULL, "\n"));

        Info *d;
        make_Info(&d, name, birth, ph);
        push(contacks_list, d);
        sort(contacks_list);

        free(str); //읽은 문자열 메모리 해제
    }
    fclose(contacks_file);
}

void Write_File(list *a)
{
    FILE *contacks_file = fopen("Contacks", "w");

    Node *vtx = a->bottom;
    for (int i = 0; i < a->size; i++)
    {
        fprintf(contacks_file, "%s %s %s\n", vtx->data->name, vtx->data->phone_number, vtx->data->birth);
        vtx = vtx->next;
    }
    fclose(contacks_file);
}

void Registration(list *a)
{
    char *name, *birth, *ph;
    name = (char *)malloc(sizeof(char) * 21);
    ph = (char *)malloc(sizeof(char) * 16);
    birth = (char *)malloc(sizeof(char) * 9);

    printf("Name:");
    scanf("%s", name);
    printf("Phone number:");
    scanf("%s", ph);
    printf("Birth:");
    scanf("%s", birth);

    Info *d;
    make_Info(&d, name, birth, ph);
    push(a, d);
    sort(a);
    printf("count: %d\n", a->size);

    Write_File(a);
}

void Delete(list *a)
{
    if (!empty(a))
    {
        printf("Name:");
        char *target_name = (char *)malloc(sizeof(char) * 20);
        scanf("%s", target_name);

        Node *vtx = a->bottom;
        for (int i = 0; i < a->size; i++)
        {
            if (strcmp(vtx->data->name, target_name) == 0)
            {
                pop(a, vtx);
                free(target_name);
                Write_File(a);
                return;
            }
            vtx = vtx->next;
        }

        free(target_name);
    }
    printf("No record founded.\n");
    return;
}

void ShowAll(list *a)
{
    Node *vtx = a->bottom;
    for (int i = 0; i < a->size; i++)
    {
        printf("%s %s %s\n", vtx->data->name, vtx->data->phone_number, vtx->data->birth);
        vtx = vtx->next;
    }
    return;
}

void FindByBirth(list *a)
{
    printf("Birth:");
    int key;
    scanf("%d", &key);

    Node *vtx = a->bottom;
    for (int i = 0; i < a->size; i++)
    {
        //생일에서 연도 빼고 4자리를 숫자로 바꾸고
        //100으로 나눠서 몇 월인지 구함
        if (atoi(vtx->data->birth + 4) / 100 == key)
            printf("%s %s %s\n", vtx->data->name, vtx->data->phone_number, vtx->data->birth);
        vtx = vtx->next;
    }
    return;
}

int compare(Info *a, Info *b)
{
    int name = strcmp(a->name, b->name);
    if (name)
        return name;

    int ph = strcmp(a->phone_number, b->phone_number);
    if (ph)
        return ph;

    return strcmp(a->birth, b->birth);
}
