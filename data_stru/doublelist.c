/**************************************
 * @Author   walnut-kernel
 * @Time     2022/03/01
 *************************************/

#include "doublelist.h"

node_t *doublelist_init(void)
{
    node_t *head = (node_t *)malloc(sizeof(node_t));
    if(!head) return NULL;
    memset(head, 0, sizeof(node_t));
    return head;
}

void doublelist_clear(doublelist dl)
{
    node_t *tmp = dl->next;
    while(tmp)
    {
        memset(&(tmp->data), 0, sizeof(struct data_damon));
        tmp = tmp->next;
    }
}

void doublelist_destroy(doublelist dl)
{
    node_t *tmp = dl;
    while(tmp)
    {
        dl = dl->next; free(tmp); tmp = dl;
    }
}

int32_t doublelist_length(doublelist dl)
{
    node_t *tmp = dl->next;
    uint32_t len = 0;

    while(tmp){ len++; tmp = tmp->next; }

    return len;
}

void doublelist_print(doublelist dl)
{
    node_t *tmp = dl->next;

    while(tmp)
    {
        printf("%d ", tmp->data.rand);
        tmp = tmp->next;
    }

    printf("\n");
}

bool doublelist_is_empty(doublelist dl)
{
    node_t *tmp = dl->next;
    if(tmp) return false;
    return true;
}

bool doublelist_insert_data(doublelist dl, struct data_damon *dd, struct data_damon *da, uint8_t lc)
{
    if(lc == FRONT)
    {
        node_t *tmp = dl->next;
        while(tmp)
        {
            if(tmp->data.rand == da->rand)
            {
                node_t *n = (node_t *)malloc(sizeof(node_t));
                if(!n) return false;
                memcpy(&(n->data), dd, sizeof(struct data_damon));
                n->next = tmp;
                n->prior = tmp->prior;
                tmp->prior->next = n;
                tmp->prior = n;

                return true;
            }

            tmp = tmp->next;
        }

        return false;
    }
    else if(lc == NEXT)
    {
        node_t *tmp = dl->next;
        while(tmp)
        {
            if(tmp->data.rand = da->rand)
            {
                node_t *n = (node_t *)malloc(sizeof(node_t));
                if(!n) return false;
                memcpy(&(n->data), dd, sizeof(struct data_damon));
                n->next = tmp->next;
                n->prior = tmp;
                tmp->next->prior = n;
                tmp->next = n;

                return true;
            }

            tmp = tmp->next;
        }

        return false;
    }
}

bool doublelist_insert_location(doublelist dl, struct data_damon *dd, uint32_t lc)
{
    if((lc < 1) || (lc > doublelist_length(dl) + 1)) return false;

    node_t *tmp = dl;

    if(lc == HEAD)
    {
        node_t *n = (node_t *)malloc(sizeof(node_t));
        if(!n) return false;
        memcpy(&(n->data), dd, sizeof(struct data_damon));
        n->next = tmp->next;
        n->prior = tmp;
        tmp->next->prior = n;
        tmp->next = n;

        return true;
    }

    if(lc == TAIL)
    {
        while(tmp->next) { tmp = tmp->next; }
        node_t *n = (node_t *)malloc(sizeof(node_t));
        if(!n) return false;
        n->next = NULL;
        n->prior = tmp;
        tmp->next = n;

        return true;
    }

    while(tmp && (lc > 0)) { tmp = tmp->next; lc--; }

    if(!tmp) return false;

    node_t *n = (node_t *)malloc(sizeof(node_t));
    if(!n) return false;
    memcpy(&(n->data), dd, sizeof(struct data_damon));
    n->next = tmp;
    n->prior = tmp->prior;
    tmp->prior->next = n;
    tmp->prior = n;

    return true;
}

bool doublelist_delete_data(doublelist dl, struct data_damon *dd)
{
    node_t *tmp = dl->next;
    while(tmp)
    {
        if(tmp->data.rand == dd->rand)
        {
            tmp->prior->next = tmp->next;
            tmp->next->prior = tmp->prior;
            free(tmp);
            return true;
        }

        tmp = tmp->next;
    }

    return false;
}

bool doublelist_delete_location(doublelist dl, uint32_t i)
{
    if((i < 1) || (i > doublelist_length(dl)))
        return false;

    node_t *tmp = dl;
    while(tmp && (i > 0))
    {
        tmp = tmp->next; i--;
    }

    if(!tmp) return false;

    tmp->next->prior = tmp->prior;
    tmp->prior->next = tmp->next;
    free(tmp);
    return true;
}

bool doublelist_update_data(doublelist dl, struct data_damon *da, struct data_damon *dd)
{
    node_t *tmp = dl->next;
    while(tmp)
    {
        if(tmp->data.rand == da->rand)
        {
            memcpy(&(tmp->data), dd, sizeof(struct data_damon));
            return true;
        }

        tmp = tmp->next;
    }

    return false;
}

bool doublelist_update_location(doublelist dl, struct data_damon *dd, uint32_t lc)
{
    if((lc < 1) || (lc > doublelist_length(dl)))
        return false;
    
    node_t *tmp = dl;
    while(tmp && (lc > 0))
    {
        tmp =tmp->next; lc--;
    }

    if(!tmp) return false;

    memcpy(&(tmp->data), dd, sizeof(struct data_damon));

    return true;
}

node_t *doublelist_search_data(doublelist dl, struct data_damon *dd)
{
    node_t *tmp = dl->next;

    while(tmp)
    {
        if(tmp->data.rand == dd->rand)
            return tmp;
        
        tmp = tmp->next;
    }

    return NULL;
}

node_t *doublelist_search_location(doublelist dl, uint32_t lc)
{
    if((lc < 1) || (lc > doublelist_length(dl)))
        return NULL;
    
    node_t *tmp = dl;
    while(tmp && (lc > 0))
    {
        tmp = tmp->next; lc--;
    }

    if(!tmp) return NULL;

    return tmp;
}