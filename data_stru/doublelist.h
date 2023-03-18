/**************************************
 * @Author   walnut-kernel
 * @Time     2022/03/01
 *************************************/

#ifndef __DOUBLELIST_H__
#define __DOUBLELIST_H__
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
    struct node *prior;
    struct node *next;
}node_t, *doublelist;

//初始化双链表, 双链表使用完后调用doublelist_free()释放; 成功返回头结点地址, 失败返回NULL
node_t *doublelist_init(void);

//释放除头结点之外的所有结点; dl: 双链表
void doublelist_clear(doublelist dl);

//释放整个双链表; dl: 双链表
void doublelist_destroy(doublelist dl);

//求双链表的长度; dl: 双链表; 返回双链表的长度
int32_t doublelist_length(doublelist dl);

//打印双链表中全部的结点数据; dl: 双链表
void doublelist_print(doublelist dl);

//判断双链表是否为空
bool doublelist_is_empty(doublelist dl);

//在指定结点前后插入结点; dl: 双链表, dd:待插入结点的数据域地址, da: 指定结点的数据域地址, lc: 插入位置, 前插FRONT, 后插NEXT
bool doublelist_insert_data(doublelist dl, struct data_damon *dd, struct data_damon *da, uint8_t lc);

//按位置插入结点到双链表中; dl: 双链表, dd: 待插入结点的数据域地址, lc: 插入位置, 头插HEAD, 尾插TAIL, 其它位置输入数字
bool doublelist_insert_location(doublelist dl, struct data_damon *dd, uint32_t lc);

//删除双链表中指定数据所在的结点; dl: 双链表, dd: 指定数据的地址
bool doublelist_delete_data(doublelist dl, struct data_damon *dd);

//删除双链表中指定位置的结点; dl: 双链表, i: 删除位置
bool doublelist_delete_location(doublelist dl, uint32_t i);

//更新双链表中指定的数据; dl: 双链表, da: 待更新的数据, dd: 新的数据
bool doublelist_update_data(doublelist dl, struct data_damon *da, struct data_damon *dd);

//更新双链表中指定的位置的数据; dl: 双链表, dd: 新的数据, lc: 指定的位置
bool doublelist_update_location(doublelist dl, struct data_damon *dd, uint32_t lc);

//按值查找结点; dl: 双链表, dd: 要查找的数据地址; 查到返回数据所在的结点地址, 未查到返回NULL
node_t *doublelist_search_data(doublelist dl, struct data_damon *dd);

//按位置查找结点; dl: 双链表, lc: 要查找的位置; 查到返回该位置的结点地址, 未查到返回NULL
node_t *doublelist_search_location(doublelist dl, uint32_t lc);
