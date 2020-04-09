#include "Contacks.h"

int main()
{
    list *contacks_list;
    init_list(&contacks_list);

    Read_File(contacks_list);

    while (1)
    {
        int menu_selected;
        printf("*****Menu*****\n");
        printf("1. Registration, 2. ShowAll, 3. Delete, 4. FindByBirth, 5. Exit\n");
        printf("Enter the menu number:");
        scanf("%d", &menu_selected);

        switch (menu_selected)
        {
        case 1:
            Registration(contacks_list);
            break;

        case 2:
            ShowAll(contacks_list);
            break;

        case 3:
            Delete(contacks_list);
            break;

        case 4:
            FindByBirth(contacks_list);
            break;

        case 5:
            menu_selected = -1;
            break;
        }

        if (menu_selected == -1)
            break;
    }

    Node *vtx = contacks_list->bottom;
    for (int i = 0; !empty(contacks_list); i++)
    {
        pop(contacks_list, vtx); //모든 노드, Info구조체, 데이터 메모리 해제
        vtx = vtx->next;
    }
    free(contacks_list); // 리스트 메모리 해제
    return 0;
}
