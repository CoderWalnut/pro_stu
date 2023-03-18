
/**************************************
 * @Author   walnut-kernel
 * @Time     2022/02/07
 *************************************/

#ifndef __SINGLELIST_H__
#define __SINGLELIST_H__
#include "../public.h"

#define HEAD 1
#define TAIL 0

#define FRONT 0
#define NEXT  1

#endif

struct data_damon{
    int32_t rand;
};

typedef struct node{
    struct data_damon data;
    struct node *next;
}node_t, *singlelist;

//初始化单链表, 单链表使用完后调用singlelist_free()释放; 成功返回头结点地址, 失败返回NULL
node_t *singlelist_init(void);

//释放除头结点之外的所有结点; sl: 单链表
void singlelist_clear(singlelist sl);

//释放整个单链表; sl: 单链表
void singlelist_destroy(singlelist sl);

//求单链表的长度; sl: 单链表; 返回单链表的长度
int32_t singlelist_length(singlelist sl);

//打印单链表中全部的结点数据; sl: 单链表
void singlelist_print(singlelist sl);

//判断单链表是否为空
bool singlelist_is_empty(singlelist sl);

//在指定结点前后插入结点; sl: 单链表, dd:待插入结点的数据域地址, da: 指定结点的数据域地址, lc: 插入位置, 前插FRONT, 后插NEXT
bool singlelist_insert_data(singlelist sl, struct data_damon *dd, struct data_damon *da, uint8_t lc);

//按位置插入结点到单链表中; sl: 单链表, dd: 待插入结点的数据域地址, lc: 插入位置, 头插HEAD, 尾插TAIL, 其它位置输入数字
bool singlelist_insert_location(singlelist sl, struct data_damon *dd, uint32_t lc);

//删除单链表中指定数据所在的结点; sl: 单链表, dd: 指定数据的地址
bool singlelist_delete_data(singlelist sl, struct data_damon *dd);

//删除单链表中指定位置的结点; sl: 单链表, i: 删除位置
bool singlelist_delete_location(singlelist sl, uint32_t i);

//更新单链表中指定的数据; sl: 单链表, da: 待更新的数据, dd: 新的数据
bool singlelist_update_data(singlelist sl, struct data_damon *da, struct data_damon *dd);

//更新单链表中指定的位置的数据; sl: 单链表, dd: 新的数据, lc: 指定的位置
bool singlelist_update_location(singlelist sl, struct data_damon *dd, uint32_t lc);

//按值查找结点; sl: 单链表, dd: 要查找的数据地址; 查到返回数据所在的结点地址, 未查到返回NULL
node_t *singlelist_search_data(singlelist sl, struct data_damon *dd);

//按位置查找结点; sl: 单链表, lc: 要查找的位置; 查到返回该位置的结点地址, 未查到返回NULL
node_t *singlelist_search_location(singlelist sl, uint32_t lc);

//将单链表nd结点之后的结点逆置
void singlelist_reverse(node_t *nd);