/**************************************
 * @Author   walnut-kernel
 * @Time     2022/03/03
 *************************************/

#ifndef __CIRCLELIST_H__
#define __CIRCLELIST_H__
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
}node_t, *circlelist;

//初始化循环链表, 循环链表使用完后调用circlelist_free()释放; 成功返回头结点地址, 失败返回NULL
node_t *circlelist_init(void);

//释放除头结点之外的所有结点; cl: 循环链表
void circlelist_clear(circlelist cl);

//释放整个循环链表; cl: 循环链表
void circlelist_destroy(circlelist cl);

//求循环链表的长度; cl: 循环链表; 返回循环链表的长度
int32_t circlelist_length(circlelist cl);

//打印循环链表中全部的结点数据; cl: 循环链表
void circlelist_print(circlelist cl);

//判断循环链表是否为空
bool circlelist_is_empty(circlelist cl);

//在指定结点前后插入结点; cl: 循环链表, dd:待插入结点的数据域地址, da: 指定结点的数据域地址, lc: 插入位置, 前插FRONT, 后插NEXT
bool circlelist_insert_data(circlelist cl, struct data_damon *dd, struct data_damon *da, uint8_t lc);

//按位置插入结点到循环链表中; cl: 循环链表, dd: 待插入结点的数据域地址, lc: 插入位置, 头插HEAD, 尾插TAIL, 其它位置输入数字
bool circlelist_insert_location(circlelist cl, struct data_damon *dd, uint32_t lc);

//删除循环链表中指定数据所在的结点; cl: 循环链表, dd: 指定数据的地址
bool circlelist_delete_data(circlelist cl, struct data_damon *dd);

//删除循环链表中指定位置的结点; cl: 循环链表, i: 删除位置
bool circlelist_delete_location(circlelist cl, uint32_t i);

//更新循环链表中指定的数据; cl: 循环链表, da: 待更新的数据, dd: 新的数据
bool circlelist_update_data(circlelist cl, struct data_damon *da, struct data_damon *dd);

//更新循环链表中指定的位置的数据; cl: 循环链表, dd: 新的数据, lc: 指定的位置
bool circlelist_update_location(circlelist cl, struct data_damon *dd, uint32_t lc);

//按值查找结点; cl: 循环链表, dd: 要查找的数据地址; 查到返回数据所在的结点地址, 未查到返回NULL
node_t *circlelist_search_data(circlelist cl, struct data_damon *dd);

//按位置查找结点; cl: 循环链表, lc: 要查找的位置; 查到返回该位置的结点地址, 未查到返回NULL
node_t *circlelist_search_location(circlelist cl, uint32_t lc);
