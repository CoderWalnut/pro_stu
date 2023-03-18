//方法二: 在c语言的头文件中添加以下代码; 推荐使用此方法

#ifdef __cplusplus  //两个下划线
extern "C" {
#endif

#include <stdio.h>

void show();

#ifdef __cplusplus
}
#endif

