#ifndef LIST_STRUCT_H
#define LIST_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//可以优化
#define DISH_NAME_MAX 15
#define DISH_NUM_MAX  25
#ifdef _WIN32
#include <direct.h>		//for mkdir rmdir
#include <io.h>      	//for access
#elif __linux__
#include <dirent.h>	 //for DIR remove
#include <stdarg.h>
#include <sys/stat.h>  //for access
#include <unistd.h>	   //for mkdir rmdir
#endif

#ifdef _WIN32
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#define RMDIR(a) _rmdir((a))
#elif __linux__
//不存在返回-1 存在返回0
#define ACCESS(x) access((x),0)
//若新建文件夹的路径存在，且路径下没有同名文件夹或文件，则可成功创建一个空文件夹，并返回0，否则返回-1
#define MKDIR(a) mkdir((a),0755)
//若输入参数路径存在，且被删除文件夹是一个空文件夹，则可成功删除该空文件夹，返回0，否则返回-1
#define RMDIR(a) rmdir((a))
#endif
inline void cls() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
void Show_Main_Menu();

typedef struct ORDER {
	struct ORDER* _next;
	int			  _dish[DISH_NUM_MAX + 1];	 //记录菜的索引 // 保留一位做判断//最大是DISH_NAME_MAX
} order;					 

/*
 * tables read from text or in runtime
 */
typedef struct TABLE {
	order* _client;
	int _capacity;	//餐桌最多能容纳的人数
	int _is_full;	// 1 有人在用,0 没人用
} table;			//把数组索引当成编号
/*
 * dishes read from text or in runtime
 */

typedef struct DISH {
	char   _name[DISH_NAME_MAX + 1];  //菜名
	double _price;					  //价格
} dish;								  //把数组索引当成编号
void Show_Dish_Menu();
void initTables();
void initDishes();

//pass people's count return index (-1 means no match result ) 
//(-2 means no table can contain)
int searchTable(int num);

//大函数
void handle();//一层封装
void pay();
void save_in_list(double);
void save_inform(order*, int);
int Pass_Word();
void List_Management();
void ModifyPW();
void initPassword();
void Observe();
void run();
void Get_Rank();
void Save_Dishes_Changes();
void Save_Tables_Changes();

#endif	// LIST_STRUCT_H