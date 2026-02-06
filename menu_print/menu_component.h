/* menu_component.h */
#ifndef MENU_COMPONENT_H
#define MENU_COMPONENT_H

#include "common.h"

// 前向声明
typedef struct MenuComponent MenuComponent;

// 组件操作虚函数表 (VTable)
typedef struct {
	// 核心业务：打印自身信息
	// 组合模式的关键：Composite 会递归调用子节点的 print
	void (*print)(MenuComponent* this);

	// 结构管理：添加子节点
	// Leaf 节点调用此方法通常会报错或忽略
	void (*add)(MenuComponent* this, MenuComponent* component);

	// 资源管理：递归销毁
	void (*destroy)(MenuComponent* this);

	// Getter 接口 (可选，视业务需要)
	const char* (*getName)(MenuComponent* this);
} MenuComponentVTable;

// 统一的组件结构体
struct MenuComponent {
	MenuComponentVTable* vtable;
	// 子类通过强转指针访问私有数据
};

#endif
