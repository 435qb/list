#ifndef LIST_STRUCT_H
#define LIST_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//可以优化
#define DISH_NAME_MAX 15
#define DISH_NUM_MAX  25
#define N 100  // 一单最多多少菜
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
	int           _count;
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
int MaxCapacity();// return tables max capacity
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
/*
| 函数原型                            | 功能说明                                                 |
| :---------------------------------- | :------------------------------------------------------- |
| void Table_Init(void)               | 餐桌信息初始化                                           |
| void Load_Dish(void)                | 从文件中读取菜谱                                         |
| void Dish_Menu(void)                | 打印菜单                                                 |
| void Display(int)                   | 打印菜信息，参数为菜的编号                               |
| int search(void)                    | 查找匹配型号的餐桌，返回餐桌号                           |
| ORDER *CreateOne(int)               | 创建一个客户节点，参数为餐桌编号，返回订单节点指针       |
| ORDER *Dish_Order(ORDER *，ORDER *) | 点菜，参数分别为订单头指针和客户节点指针，返回订单头指针 |
| void Save_Inform(ORDER *，int)      | 消费历史记录，参数分别为客户节点指针和点菜的总数         |
| void saveInList(float)              | 将客户消费金额存入账目，参数为消费额                     |
| ORDER *Payment(ORDER *)             | 客户结账，参数为订单头指针，返回订单头指针               |
| int Pass_Word(void)                 | 密码验证，返回密码验证的结果1或 0                        |
| void ModifyPW()                     | 修改账目密码                                             |
| void List_Management(void)          | 账本管理                                                 |
| void Observe(void)                  | 查看账目                                                 |
| void ListMenu(void)                 | 账目管理菜单                                             |
| void Main_Menu(void)                | 显示系统菜单                                             |
| void Menu_select(void)              | 完成系统各项功能                                         |
| void Get_Rank(void)                 | 对菜进行统计排名                                         |


void Load_Table();	//餐桌信息初始化
void Load_Dish();	//从文件中读取菜谱
void Dish_Menu();	//打印菜单

void   Display(int);	//打印菜信息，参数为菜的编号                               |
void   search();		//查找匹配型号的餐桌,返回餐桌编号                          |
ORDER* CreateOne(int);	// 创建一个客户节点，参数为餐桌编号，返回订单节点指针 |
ORDER* Dish_Order(ORDER*,
				  ORDER*);	//| 点菜，参数分别为订单头指针和客户节点指针，返回订单头指针 |
void   Save_Inform(ORDER*,
				   int);   //   | 消费历史记录，参数分别为客户节点指针和点菜的总数 |
void   saveInList(float);  //          | 将客户消费金额存入账目，参数为消费额 |
ORDER* Pay(ORDER*);		   //         | 客户结账，参数为订单头指针，返回订单头指针 |
int	   Pass_Word();		   //             | 密码验证，返回密码验证的结果1或 0 |
void   ModifyPW();		   //            | 修改账目密码 |
void   List_Management();  //        | 账本管理 |
void   Observe();		   //             | 查看账目 |
void   ListMenu();		   //             | 账目管理菜单 |
void   Show_Main_Menu();   //           | 显示系统菜单 |
// void Menu_select();     //           | 完成系统各项功能 |
void Get_Rank();  //            | 对菜进行统计排名 |
*/
#endif	// LIST_STRUCT_H
// telegram
// everyday
// instant messaging, video calling
// provide bot to do everything you want and api which is easy to use
// api ( Application programming interface)
// stikers and channels
// Bots are Telegram accounts operated by programs. They can respond to messages or mentions, 
// can be invited into groups and can be integrated into other programs
// Channels are a form of one-way messaging where 
// admins are able to post messages but other users are not.
// Stickers are cloud-based, high-resolution images intended to provide more expressive emoji
// Secret chats
// every chat is on the cloud and never be deleted
// unless the group's administrator or you decide to delete it
// 