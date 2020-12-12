#include "struct.h"

#include <stdio.h>
#define fuck printf("fuck!");
int main() {
	// Table_Init();
	/*
	order* head = NULL;
	while (1) {
	begin:
		Show_Main_Menu();
		int choose;
		cls();

		// Load_Dish();
		do {
			printf("请选择:\n");
			fflush(stdin);	//?

		} while (scanf("%d", &choose) != 1);
		const ORDER* head = NULL;

		switch (choose) {
		case 1:
			Dish_Menu();
			return Dish_Order(head, CreateOne(search()));
			break;
		case 2:
			head = Pay(head);
			break;
		case 3:
			List_Management();
			break;
		case 4:
			Get_Rank();
			break;
		case 5:
			exit(1);
		default:
			break;
		}
	}
end:
	return 0;
*/
	// while (1) {
	// 首先初始化餐桌 菜
	// 然后展示界面
	MKDIR("data");
	initPassword();
	initDishes();
	initTables();
	run();
	return 0;
}
