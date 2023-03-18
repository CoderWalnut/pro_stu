/**************************************
 * @AUTHOR   walnut-kernel
 * @TIME     2022/02/07
 *************************************/

#include "singlelist.h"

node_t *singlelist_init()
{
    node_t *head = (node_t *)malloc(sizeof(node_t));
    if(!head) return NULL;
    memset(head, 0, sizeof(node_t));
    return head;
}

void singlelist_clear(singlelist sl)
{
    node_t *tmp1 = sl->next;
    node_t *tmp2 = NULL;
    while(tmp1) { tmp2 = tmp1; tmp1 = tmp1->next; free(tmp2); tmp2 = NULL; }
    sl->next = NULL;
}

void singlelist_destroy(singlelist sl)
{
    node_t *tmp = sl;
    while(tmp){ sl = sl->next; free(tmp); tmp = sl; }
}

int32_t singlelist_length(singlelist sl)
{
    uint32_t len = 0;
    node_t *tmp = sl->next;
    while(tmp){ len++; tmp = tmp->next; }

    return len;
}

void singlelist_print(singlelist sl)
{
    node_t *tmp = sl->next;
    while(tmp)
    {
        printf("%d ", tmp->data.rand);
        tmp = tmp->next;
    }

    printf("\n");
}

bool singlelist_is_empty(singlelist sl)
{
    node_t *tmp = sl->next;
    if(tmp) return false;
    return true;
}

bool singlelist_insert_data(singlelist sl, struct data_damon *dd, struct data_damon *da, uint8_t lc)
{
    if(lc == NEXT)
    {
        node_t *tmp = sl->next;
        while(tmp)
        {
            if(tmp->data.rand == da->rand)
            {
                node_t *n = (node_t *)malloc(sizeof(node_t));
                memcpy(&(n->data), dd, sizeof(struct data_damon));
                n->next = tmp->next;
                tmp->next = n;

                return true;
            }

            tmp = tmp->next;
        }

        return false;
    }
    else if(lc == FRONT)
    {
        node_t *tmp = sl;
        while(tmp)
        {
            if(tmp->next->data.rand == da->rand)
            {
                node_t *n = (node_t *)malloc(sizeof(node_t));
                memcpy(&(n->data), dd, sizeof(struct data_damon));
                n->next = tmp->next;
                tmp->next = n;

                return true;
            }

            tmp = tmp->next;
        }

        return false;
    }
}

bool singlelist_insert_location(singlelist sl, struct data_damon *dd, uint32_t lc)
{
    if((lc < 1) || (lc > singlelist_length(sl) + 1))
        return false;

    node_t *tmp = sl;

    if(lc == HEAD)
    {
        node_t *n = (node_t *)malloc(sizeof(node_t));
        if(!n) return false;

        memcpy(&(n->data), dd, sizeof(struct data_damon));
        n->next = sl->next;
        sl->next = n;
        return true;
    }

    if(lc == TAIL)
    {
        node_t *n = (node_t *)malloc(sizeof(node_t));
        if(!n) return false;

        memcpy(&(n->data), dd, sizeof(struct data_damon));
        while(tmp->next) tmp = tmp->next;
        n->next = NULL;
        tmp->next = n; 
        return true;
    }

    node_t *n = (node_t *)malloc(sizeof(node_t));
    if(!n) return false;

    memcpy(&(n->data), dd, sizeof(struct data_damon));
    while((lc > 1) && tmp)
    {
        tmp = tmp->next; lc--;
    }

    if(!tmp) return false;

    n->next = tmp->next;
    tmp->next = n;

    return true;
}

bool singlelist_delete_data(singlelist sl, struct data_damon *dd)
{
    node_t *tmp = sl;
    while(tmp->next)
    {
        if(tmp->next->data.rand == dd->rand)
        {
            node_t *n = tmp->next;
            tmp->next = tmp->next->next;
            free(n);
            return true;
        }

        tmp = tmp->next;
    }

    return false;
}

bool singlelist_delete_location(singlelist sl, uint32_t i)
{
    if((i < 1) || (i > singlelist_length(sl)))
        return false;

    node_t *tmp = sl;
    while((i > 1) && tmp)
    {
        tmp = tmp->next; i--;
    }

    if(!tmp) return false;

    node_t *n = tmp->next;
    tmp->next = tmp->next->next;
    free(n);
    return true;
}

bool singlelist_update_data(singlelist sl, struct data_damon *da, struct data_damon *dd)
{
    node_t *tmp = sl->next;
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

bool singlelist_update_location(singlelist sl, struct data_damon *dd, uint32_t lc)
{
    if((lc < 1) || (lc > singlelist_length(sl)))
        return false;
    
    node_t *tmp = sl;
    while(tmp && (lc > 0))
    {
        tmp = tmp->next; lc--;
    }

    if(!tmp) return false;

    memcpy(&(tmp->data), dd, sizeof(struct data_damon));
    return true;
}

node_t *singlelist_search_data(singlelist sl, struct data_damon *dd)
{
    node_t *tmp = sl->next;
    while(tmp)
    {
        if(tmp->data.rand == dd->rand) return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

node_t *singlelist_search_location(singlelist sl, uint32_t lc)
{
    if(lc < 1 || (lc > singlelist_length(sl)))
        return NULL;

    node_t *tmp = sl;

    while(tmp && lc > 0)
    {
        tmp = tmp->next; lc--;
    }

    if(!tmp) return NULL;

    return tmp;
}

void singlelist_reverse(node_t *nd)
{
    node_t *tmp1 = nd->next;
    node_t *tmp2 = NULL;

    while(tmp1){
        
    }


}