#include "struct.h"

int main() {
	MKDIR("data");
	initPassword();
	initDishes();
	initTables();
	run();
	return 0;
}
