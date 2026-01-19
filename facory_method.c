#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//工厂方法类
typedef struct tNoodleSoup {
	char *name
	char *noodles;
	char *sauce;
	char *broth;
	char *toppings;
	char *meat;

	int prize;

	void (*prepare)(void *self);
	void (*deliver)(void *self);
	int (*pay)(void *self);
}tNoodleSoup;

//工厂注册表信息
typedef struct {
	const char *region;
	tNoodleSoup* (*create)(void);
}tNoodleFactoryTables;

//工厂注册表
typedef struct {
	tNoodleFactoryTables *tables
	int item;
}tNoodleFactoryRegister;

tNoodleFactoryRegister *g_factory_register = NULL;

//注册表初始化
void factory_init(tNoodleFactoryTables *tables, size_t s);

//下单函数
void order(tNoodleSoup *nds);

void factory_init(tNoodleFactoryTables *tables, size_t s) {
	g_factory_register->tables = tables;
	g_factory_register->item = s;
}

void order(const char *type) {
	for (int i = 0; i < g_factory_register->item; i++) {
		if (strcmp(type, g_factory_register->tables[i].region) == 0) {
			return g_factory_register->tables[i].create();
		}
	}
}

//具体类实现
typedef struct {
	tNoodleSoup base;
}tGuangdongNdSoup;

void guangdong_prepare(tNoodleSoup* self) {
	tGuangdongNdSoup *nds = (tGuangdongNdSoup *)self;
	printf("【广东汤面】准备中:\n");
	printf("面条: %s\n", nds->base.noodles);
	printf("汤底: %s\n", nds->base.broth);
	printf("配菜: %s\n", nds->base.toppings);
	printf("主料: %s\n", nds->base.meat);
}

void guangdong_deliver(tNoodleSoup* self) {
	tGuangdongNdSoup *nds = (tGuangdongNdSoup *)self;
	printf("【揽佬唱来财】配送中 ... ...\n");
	sleep(1);
	printf("%s 已送达\n", nds->base.name);
}

int guangdong_pay(tNoodleSoup *self) {
	tGuangdongNdSoup *nds = (tGuangdongNdSoup *)self;
	printf("支付中 ... ...\n");
	printf("%s 已支付\n", nds->base.name);
}


