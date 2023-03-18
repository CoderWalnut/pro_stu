/**************************************
 * @Author   walnut-kernel
 * @Time     2022/03/03
 *************************************/

#include "circlelist.h"

node_t *circlelist_init(void)
{
    node_t *head = (node_t *)malloc(sizeof(node_t));
    if(!head) return NULL;

    memset(head, 0, sizeof(node_t));
    head->next = head;
    return head;
}

void circlelist_clear(circlelist cl)
{
    node_t *tmp = cl->next;
    while(tmp)
    {
        memset(&(tmp->data), 0, sizeof(struct data_damon));
        tmp = tmp->next;
    }
}

