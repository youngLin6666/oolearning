/* menu_item.c */
#include "menu_component.h"

// --- 私有数据 ---
typedef struct {
	MenuComponent base; // 继承机制
	char* name;
	char* description;
	Boolean vegetarian;
	double price;
} MenuItem;

void menu_item_print(MenuComponent* this) {
	MenuItem *item = (MenuItem *)this;
	printf("  %s%s, $%.2f\n    -- %s\n",
			item->name,
			item->vegetarian ? "(v)" : "",
			item->price,
			item->description);
}

void menu_item_add(MenuComponent* this, MenuComponent* c) {
	// 叶子节点不能添加子节点，属于无效操作
	fprintf(stderr, "WARNING: Cannot add to a Leaf node (MenuItem).\n");
}

const char* menu_item_get_name(MenuComponent* this) {
	return ((MenuItem*)this)->name;
}

void menu_item_destroy(MenuComponent* this) {
	MenuItem* item = (MenuItem*)this;

	printf("Debug: MenuItem(%s) destroyed.\n", item->name);

	SAFE_FREE(item->name);
	SAFE_FREE(item->description);
	SAFE_FREE(item);
}

// --- VTable ---
static MenuComponentVTable menuItemVTable = {
	.print = menu_item_print,
	.add = menu_item_add,
	.destroy = menu_item_destroy,
	.getName = menu_item_get_name
};

// --- 工厂函数 ---
MenuComponent* create_menu_item(const char* name, const char* desc, Boolean veg, double price) {
	MenuItem* item = NEW(MenuItem);
	item->base.vtable = &menuItemVTable;
	item->name = strdup(name);
	item->description = strdup(desc);
	item->vegetarian = veg;
	item->price = price;
	return (MenuComponent*)item;
}

