/* menu.c */
#include "menu_component.h"

// --- 链表节点 ---
typedef struct Node {
	MenuComponent* item;
	struct Node* next;
} Node;

// --- Menu 私有数据 ---
typedef struct {
	MenuComponent base;
	char* name;
	char* description;

	// 内部数据结构：单向链表
	Node* head;
	Node* tail;
} Menu;

// --- 方法实现 ---

void menu_add(MenuComponent* this, MenuComponent* component) {
	Menu* menu = (Menu*)this;
	Node* newNode = NEW(Node);
	newNode->item = component;
	newNode->next = NULL;

	if (menu->head == NULL) {
		menu->head = newNode;
		menu->tail = newNode;
	} else {
		menu->tail->next = newNode;
		menu->tail = newNode; // 更新尾指针
	}
}

// 组合模式的核心：递归打印
void menu_print(MenuComponent* this) {
	Menu* menu = (Menu*)this;

	printf("\n%s, %s\n---------------------\n", menu->name, menu->description);

	Node* current = menu->head;
	while (current != NULL) {
		// 多态调用：current->item 可能是 MenuItem 也可能是另一个 Menu
		current->item->vtable->print(current->item);
		current = current->next;
	}
}

const char* menu_get_name(MenuComponent* this) {
	return ((Menu*)this)->name;
}

void menu_destroy(MenuComponent* this) {
	Menu* menu = (Menu*)this;
	Node* current = menu->head;

	// 递归销毁链表中的所有子节点
	while (current != NULL) {
		Node* nextNode = current->next;
		// 调用子节点的 destroy (递归)
		current->item->vtable->destroy(current->item);
		SAFE_FREE(current); // 释放链表节点本身
		current = nextNode;
	}

	printf("Debug: Menu(%s) destroyed.\n", menu->name);

	SAFE_FREE(menu->name);
	SAFE_FREE(menu->description);
	SAFE_FREE(menu);
}

// --- VTable ---
static MenuComponentVTable menuVTable = {
	.print = menu_print,
	.add = menu_add,
	.destroy = menu_destroy,
	.getName = menu_get_name
};

// --- 工厂函数 ---
MenuComponent* create_menu(const char* name, const char* desc) {
	Menu* menu = NEW(Menu);
	menu->base.vtable = &menuVTable;
	menu->name = strdup(name);
	menu->description = strdup(desc);
	menu->head = NULL;
	menu->tail = NULL;
	return (MenuComponent*)menu;
}

