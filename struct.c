#include "struct.h"

#include <stdio.h>
static int	  ldish;
static int	  ltable;
static dish*  dishes;  //管理dish
static table* tables;  //管理table

static order* head = NULL;
static order* pre  = NULL;

char password[129] = "114514";

void Show_Main_Menu() {
	printf("\n*********************\n");
	printf("餐厅服务系统\n");
	printf("*********************\n");
	printf("1.点菜\n");
	printf("2.客户结账\n");
	printf("3.账目管理\n");
	printf("4.餐厅统计\n");
	printf("5.退出系统\n");
}

void Show_Dish_Menu() {
	int i;
	printf("*********欢迎选购本店菜**********\n");
	printf("菜编号\t\t\t菜名\t菜单价\n");
	for (i = 1; i < ldish; ++i)
		printf("%d\t%16s\t%.2lf\n", i, dishes[i]._name, dishes[i]._price);
}

void initTables() {
	if (ACCESS("data/tables") == -1) {
		FILE* temp = fopen("data/tables", "w");
		fprintf(temp, "3 3 3 3 3 3");
		fclose(temp);
	}
	FILE* fp = fopen("data/tables", "r");
	if (!fp) {
		printf("文件tables打开失败");
		return;
	}
	ltable = 0;
	while (fscanf(fp, "%*d") != EOF) {
		++ltable;
	}
	fseek(fp, 0, SEEK_SET);
	tables = malloc(ltable * sizeof(table));
	int cap, i = 0;
	while (fscanf(fp, "%d", &cap) != EOF) {
		tables[i]._capacity = cap;
		tables[i]._is_full	= 0;
		tables[i]._client	= NULL;
		++i;
	}
	fclose(fp);
}

void initDishes() {
	if (ACCESS("data/dishes") == -1) {
		FILE* temp = fopen("data/dishes", "w");
		fprintf(temp, "jiba 4.0\n"
					  "baji 5.0\n"
					  "xingzhe 6.0 \n"
					  "cao  7.0\n"
					  "fuck 2.0");
		fclose(temp);
	}
	FILE* fp = fopen("data/dishes", "r");
	if (!fp) {
		printf("文件dishes打开失败");
		return;
	}
	ldish = 1;	// dishes[0]不算
	while (fscanf(fp, "%*s%*lf") != EOF) {
		++ldish;
	}
	fseek(fp, 0, SEEK_SET);
	dishes = malloc(ldish * sizeof(dish));
	char   name[DISH_NAME_MAX + 1];
	double price;
	int	   i = 1;  //没有dishes[0]
	while (fscanf(fp, "%s%lf", name, &price) != EOF) {
		strcpy(dishes[i]._name, name);
		dishes[i]._price = price;
		++i;
	}
	fclose(fp);
}

int searchTable(int num) {
	int i;
	int _can_come = 0;
	for (i = 0; i < ltable; ++i) {
		if (!tables[i]._is_full && tables[i]._capacity >= num) {
			return i;
		}
		if (!_can_come && tables[i]._capacity >= num)
			_can_come = 1;
	}
	return _can_come ? -1 : -2;
}

void handle() {
	int num;
	printf("请输入来客数量:\n");
	while (scanf("%d", &num) == 0) {
		while (getchar() != '\n')
			continue;
		printf("无效字符\n");
		printf("请输入来客数量:\n");
	}
	int id = searchTable(num);
	if (id == -1) {
		printf("抱歉,现在没有%d人桌\n", num);
	}
	else if (id == -2) {
		printf("抱歉,本店没有容纳%d的餐桌!\n", num);
	}
	else {
		printf("请到%d号餐桌就坐\n", id);

		order* curr;
		if ((curr = ( order* )malloc(sizeof(order))) == NULL) {
			printf("订单创建失败\n");
			return;
		}
		// 没失败就是成功
		memset(curr->_dish, 0, (DISH_NUM_MAX + 1) * sizeof(int));
		tables[id]._client = curr;

		if (head != NULL) {
			pre->_next	= curr;
			curr->_next = NULL;
			pre			= curr;
		}
		else {
			pre = head = curr;
		}

		int i = 1, n = 0;
		do {
			Show_Dish_Menu();
			printf("请输入菜的编号,按0结束输入:");
			if (scanf("%d", &i) == 0) {
				while (getchar() != '\n')
					continue;
				printf("无效字符\n");
				continue;
			}
			if (i > ldish - 1 || i < 0) {
				printf("没有这个菜\n");
				continue;
			}
			if (i == 0) {
				break;
			}

			curr->_dish[n++] = i;	 //结尾有个-1
			if (n >= DISH_NUM_MAX) {
				printf("你点的菜已达到上限\n");
				break;
			}
		} while (1);
		tables[id]._is_full = 1;
	}
}
void pay() {
	int id;
	printf("请输入您的餐桌号\n");
	while (scanf("%d", &id) == 0) {
		while (getchar() != '\n')
			continue;
		printf("无效字符\n");
		printf("请输入您的餐桌号\n");
	}
	order* curr = tables[id]._client;
	if (curr == NULL) {
		printf("\n此餐桌未点菜!\n");
		return;
	}

	double pay = 0;
	printf("您点菜的情况如下:\n");
	printf("编号\t菜名\t价格\n");
	int index;
	int i = 0;
	while ((index = curr->_dish[i]) != 0) {
		printf("%d\t%s\t%.2lf\n", index, dishes[index]._name, dishes[index]._price);
		pay += dishes[index]._price;
		++i;
	}
	if (i != 0) {
		printf("您一共点了%d道菜\n", i);
		printf("您本次的消费额为%.2lf元\n", pay);
		double Pay;
		while (1) {
			printf("您实际的付款:\n");
			while (scanf("%lf", &Pay) == 0) {
				while (getchar() != '\n')
					continue;
				printf("无效字符\n");
				printf("您实际的付款:\n");
			}
			if (Pay < pay) {
				printf("钱不够:(\n");
				continue;
			}
			break;
		}
		printf("找您%lf\n", Pay - pay);

		printf("谢谢您的惠顾,欢迎下次光临\n");
		save_in_list(pay);
		save_inform(curr, i);
		tables[id]._is_full = 0;
	}
	order *pree = head, *j = head;
	for (; curr != j; j = j->_next)	 //与外pre无关
	{
		pree = j;
	}
	if (j == head)
		;
	else {
		order* temp = curr->_next;
		free(curr);
		pree->_next = temp;
	}
}

void save_in_list(double pay) {
	FILE*  fp;
	time_t timer;
	timer = time(NULL);
	if ((fp = fopen("data/accounts.txt", "a")) == NULL) {
		printf("操作失败\n");
		exit(1);
	}
	fprintf(fp, "%.2lf\t%s\n", pay, ctime(&timer));	 //有问题系统时间
	printf("账本保存成功\n");
	fclose(fp);
}

void save_inform(order* curr, int count) {
	FILE*  fp = fopen("data/histories.txt", "a");
	time_t timer = time(NULL);
	if (fp == NULL) {
		printf("操作失败\n");
		exit(1);
	}
	fprintf(fp, "%d\n", count);
	for (int i = 0; i < count; ++i) {
		int index = curr->_dish[i];
		fprintf(fp, "%d\t%s\t%.2lf\n", index, dishes[index]._name, dishes[index]._price);
	}
	fprintf(fp, "%s\n", ctime(&timer));
	printf("历史记录保存成功\n");
	fclose(fp);
}

int Pass_Word() {
	char currpass[129];
	int ch;//实际上是char
	do {
		while(getchar() != '\n') continue;//清除缓冲区
		printf("请输入密码\n");
		scanf("%s", currpass);
		getchar();//消耗空白符
		if (strcmp(password, currpass) == 0) {
			printf("**********************************\n");
			printf("     欢迎进入账目管理系统\n");
			printf("**********************************\n");
			return 1;
		}
		else {
			printf("密码输入有误,请重新输入\n");
			printf("是否重新输入\n");
		}
	} while ((ch = getchar()) == 'y' || ch == 'Y');
	return 0;
}

void List_Management() {

	FILE* fp = fopen("data/accounts.txt", "r");
	if (fp == NULL) {
		printf("操作失败\n");
		exit(1);
	}
	if (Pass_Word()) {
		do {
			int choice;
			printf("1.修改密码\n");
			printf("2.查看账目\n");
			printf("3.返回\n");
			printf("请选择:\n");

			if (scanf("%d", &choice) == 0) {
				while (getchar() != '\n') continue;
				printf("无效字符\n");
				continue;
			}
			switch (choice) {
			case 1:
				ModifyPW();
				break;
			case 2:
				Observe();
				break;
			case 3:
				return;
			default:
				printf("没有该功能项\n");
			}
		} while (1);
	}
}
void initPassword() {
	if (ACCESS("data/password.txt") == -1) {
		FILE* temp = fopen("data/password.txt", "w");
		if (temp == NULL) {
			printf("文件打开失败\n");
			exit(1);
		}
		printf("请设置你的密码或留空以使用初始密码114514\n");
		int ch;//实际上是char
		if ((ch = getchar()) == '\n') {
			fprintf(temp, "114514");
		}
		else {
			password[0] = (char)ch;
			scanf("%s", password + 1);	// password[0]是getchar()里的
			fprintf(temp, "%s", password);
		}
		fclose(temp);
		return;
	}
	FILE* fp;
	if ((fp = fopen("data/password.txt", "r")) == NULL) {
		printf("文件打开失败\n");
		exit(1);
	}
	fscanf(fp, "%s", password);
	fclose(fp);
}
void ModifyPW() {
	char currpass[129], nextpass[129];
	do {
		printf("请输入新的密码\n");
		scanf("%s", currpass);
		printf("请再次输入密码\n");
		scanf("%s", nextpass);
		if (strcmp(currpass, nextpass) != 0) {
			printf("两次密码不一致，请重试\n");
			continue;
		}
		break;
	} while (1);
	FILE* fp = fopen("data/password.txt", "w");
	if (fp == NULL) {
		printf("文件打开失败\n");
		exit(1);
	}
	strcpy(password, currpass);
	fprintf(fp, "%s", currpass);
	fclose(fp);

	printf("密码修改成功\n");
}

void Observe() {
	FILE*  fp = fopen("data/accounts.txt", "r");
	if (fp == NULL) {
		printf("操作失败\n");
		exit(1);
	}
	printf("消费金额\t消费时间\n");
	size_t num = 100;
	char*  arr = malloc(num * sizeof(char));
	while (!feof(fp)) {
		getline(&arr, &num, fp);
		printf("%s", arr);
	}
	free(arr);
	fclose(fp);
}
void run(){
	do {
		Show_Main_Menu();
		int choose;
		while (scanf("%d", &choose) == 0) {
			while (getchar() != '\n') continue;
			printf("无效字符!请再次输入\n");
		}
		switch (choose) {
		case 1:
			handle();
			break;
		case 2:
			pay();
			break;
		case 3:
			List_Management();
			break;
		case 4:
			Get_Rank();
			break;
		case 5:
			exit(0);
		default:
			printf("无此选项\n");
		}
	} while (1);
}

void Get_Rank(void) {
	FILE* fp = fopen("data/histories.txt", "r");
	if(fp == NULL){
		printf("还没有历史记录\n");
		return;
	}
	int count[ldish];
	memset(count, 0, sizeof(int) * ldish);
	while (!feof(fp)) {
		int n;
		fscanf(fp, "%d\n", &n);
		for (int i = 0; i != n; ++i) {
			int id;
			fscanf(fp, "%d%*s%*s", &id);
			++count[id];
		}
		fscanf(fp, "%*s%*s%*s%*s%*s\n");
	}
	fclose(fp);
	printf("菜的受欢迎程度如下：\n");

	for (int i = 1; i < ldish; ++i) {
		printf("%d号菜%s: %d\n", i, dishes[i]._name, count[i]);
	}
	char temp[DISH_NAME_MAX + 1];
	for (int i = 1; i < ldish; ++i) {
		for (int j = 1; j < ldish - i; ++j) {
			if (count[j] < count[j + 1]) {
				int t = count[j];
				double d = dishes[j]._price;
				strcpy(temp, dishes[j]._name);
				
				count[j] = count[j + 1];
				dishes[j]._price = dishes[j + 1]._price;
				strcpy(dishes[j]._name, dishes[j + 1]._name);

				count[j + 1] = t;
				dishes[j + 1]._price = d;
				strcpy(dishes[j + 1]._name, temp);
			}
		}
	}
	//保存更改
	Save_Dishes_Changes();
	printf("\n比较受顾客欢迎的四个菜是：\n");
	printf("%s\n", dishes[1]._name);
	printf("%s\n", dishes[2]._name);
	printf("%s\n", dishes[3]._name);
	printf("%s\n", dishes[4]._name);
}
void Save_Dishes_Changes() {
	FILE *fp = fopen("data/dishes", "w");
	if (fp == NULL){
		printf("fatal error\n");
		exit(1);
	}
	for (int i = 1; i < ldish; ++i)
	{
		fprintf(fp,"%s %.2lf\n", dishes[i]._name,dishes[i]._price);
	}
	fclose(fp);
}
void Save_Tables_Changes(){
	FILE *fp = fopen("data/tables", "w");
	if (fp == NULL)
	{
		printf("fatal error\n");
		exit(1);
	}
	for (int i = 0; i < ltable; ++i)
	{
		fprintf(fp,"%d", tables[i]._capacity);
	}
}
