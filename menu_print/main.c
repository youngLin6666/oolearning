/* main.c */
#include "menu_component.h"

// 外部工厂函数声明
MenuComponent* create_menu(const char* name, const char* desc);
MenuComponent* create_menu_item(const char* name, const char* desc, Boolean veg, double price);

int main() {
	// 1. 创建组件
	MenuComponent* allMenus = create_menu("ALL MENUS", "All menus combined");

	MenuComponent* pancakeHouse = create_menu("PANCAKE HOUSE MENU", "Breakfast");
	MenuComponent* dinerMenu = create_menu("DINER MENU", "Lunch");
	MenuComponent* cafeMenu = create_menu("CAFE MENU", "Dinner");
	MenuComponent* dessertMenu = create_menu("DESSERT MENU", "Dessert of course!");
	MenuComponent* wineMenu = create_menu("WINE MENU", "Graciuous wine");

	// 2. 组装树形结构 (组合模式)
	allMenus->vtable->add(allMenus, pancakeHouse);
	allMenus->vtable->add(allMenus, dinerMenu);
	allMenus->vtable->add(allMenus, cafeMenu);

	// 填充煎饼屋
	pancakeHouse->vtable->add(pancakeHouse, 
		create_menu_item("K&B's Pancake Breakfast", "Pancakes with scrambled eggs", TRUE, 2.99));

	// 填充餐厅 (包含子菜单)
	dinerMenu->vtable->add(dinerMenu, 
		create_menu_item("BLT", "Bacon with lettuce & tomato", FALSE, 2.99));
	dinerMenu->vtable->add(dinerMenu, dessertMenu); // 组合嵌套
	dinerMenu->vtable->add(dinerMenu, wineMenu);

	// 填充甜点
	dessertMenu->vtable->add(dessertMenu, 
		create_menu_item("Apple Pie", "Apple pie with a flakey crust", TRUE, 1.59));

	// 填充酒单
	wineMenu->vtable->add(wineMenu,
		create_menu_item("Red Wine 1980s", "50-year-old red wine from Nansha, Guangzhou.", TRUE, 50.99));

	// 填充咖啡厅
	cafeMenu->vtable->add(cafeMenu, 
		create_menu_item("Veggie Burger", "Veggie burger on a bun", TRUE, 3.99));

	// 3. 业务执行
	// 只需要调用根节点的 print，内部自动处理递归
	printf(">>> START PRINTING MENUS <<<\n");
	allMenus->vtable->print(allMenus);

	// 4. 资源释放
	// 一键销毁整个树
	printf("\n>>> CLEANING UP <<<\n");
	allMenus->vtable->destroy(allMenus);

	return 0;
}
