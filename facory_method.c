/**
 *
 * 工厂方法:
 * 工厂方法的create由子类去具体实现,但是生产的流程还是由工厂去决定,即生产的具体产品有具体子类定义。
 * 工厂方法如果要添加一个新的具体产品生产,则该具体产品必须实现抽象产品类的所有接口,最后把create注册到工厂中。
 *
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//抽象产品类
typedef struct tNoodleSoup {
	char name[16];
	char noodles[16];
	char sauce[16];
	char broth[16];
	char toppings[16];
	char meat[16];

	int prize;

	void (*prepare)(struct tNoodleSoup *self);
	void (*deliver)(struct tNoodleSoup *self);
	int (*pay)(struct tNoodleSoup *self);
	void (*clean)(struct tNoodleSoup *self);
}tNoodleSoup;

//工厂注册表信息
typedef struct {
	const char *region;
	tNoodleSoup* (*create)(void);
}tNoodleFactoryTables;

//工厂注册表
typedef struct {
	tNoodleFactoryTables *tables;
	int item;
}tNoodleFactoryRegister;

tNoodleFactoryRegister *g_factory_register = NULL;

//注册表初始化
void factory_init(tNoodleFactoryTables *tables, size_t s); //工厂方法

//下单函数 创建对象
tNoodleSoup* order(const char *type); //工厂方法

//吃完函数 清除对象
void eat(tNoodleSoup* self); //工厂方法,其实这个函数可以不用实现,因为工厂只需负责生产即可,其他操作均由对象自己控制

void factory_init(tNoodleFactoryTables *tables, size_t s) {
	g_factory_register = (tNoodleFactoryRegister *)malloc(sizeof(tNoodleFactoryRegister));
	g_factory_register->tables = tables;
	g_factory_register->item = s;
}

tNoodleSoup* order(const char *type) {
	tNoodleSoup* nds = NULL;
	for (int i = 0; i < g_factory_register->item; i++) {
		if (strcmp(type, g_factory_register->tables[i].region) == 0) {
			nds = g_factory_register->tables[i].create();
		}
	}

	if(nds != NULL) {
		nds->prepare(nds);
		nds->deliver(nds);
		nds->pay(nds);
	}

	return nds;
}

void eat(tNoodleSoup* self) {
	self->clean(self);
}

/* ============================================================================================= */

//具体类实现
typedef struct {
	tNoodleSoup base;
}tGuangdongNdSoup;

void guangdong_prepare(tNoodleSoup* self) {
	tGuangdongNdSoup *nds = (tGuangdongNdSoup *)self;
	printf("【广东 %s】准备中:\n", nds->base.name);
	printf("面条: %s\n", nds->base.noodles);
	printf("汤底: %s\n", nds->base.broth);
	printf("配菜: %s\n", nds->base.toppings);
	printf("主料: %s\n", nds->base.meat);
	printf("蘸料: %s\n", nds->base.sauce);
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
	printf("%s 已支付 %d元\n", nds->base.name, nds->base.prize);
}

void guangdong_clean(tNoodleSoup *nds) {
	tGuangdongNdSoup *gnds = (tGuangdongNdSoup *)nds;
	printf("%s 吃完了\n", nds->name);
	free(gnds);
}

tNoodleSoup *guangdong_create(void) {
	tGuangdongNdSoup *nds = (tGuangdongNdSoup *)malloc(sizeof(tGuangdongNdSoup));

	strcpy(nds->base.noodles, "细米粉");
	strcpy(nds->base.broth, "清汤");
	strcpy(nds->base.toppings, "西洋菜");
	strcpy(nds->base.meat, "瘦肉");
	strcpy(nds->base.sauce, "天海酱油");
	strcpy(nds->base.name, "瘦肉粉");

	nds->base.prize = 12;
	nds->base.prepare = guangdong_prepare;
	nds->base.deliver = guangdong_deliver;
	nds->base.pay = guangdong_pay;
	nds->base.clean = guangdong_clean;

	return (tNoodleSoup *)nds;
}

/* ============================================================================================= */

//具体类实现
typedef struct {
	tNoodleSoup base;
}tChangShaNdSoup;

void changsha_prepare(tNoodleSoup* self) {
	tChangShaNdSoup *nds = (tChangShaNdSoup *)self;
	printf("【长沙 %s】准备中:\n", nds->base.name);
	printf("面条: %s\n", nds->base.noodles);
	printf("汤底: %s\n", nds->base.broth);
	printf("配菜: %s\n", nds->base.toppings);
	printf("主料: %s\n", nds->base.meat);
	printf("蘸料: %s\n", nds->base.sauce);
}

void changsha_deliver(tNoodleSoup* self) {
	tGuangdongNdSoup *nds = (tGuangdongNdSoup *)self;
	printf("【长沙跳跳糖】配送中 ... ...\n");
	sleep(1);
	printf("%s 已送达\n", nds->base.name);
}

int changsha_pay(tNoodleSoup *self) {
	tGuangdongNdSoup *nds = (tGuangdongNdSoup *)self;
	printf("支付中 ... ...\n");
	printf("%s 已支付 %d元\n", nds->base.name, nds->base.prize);
}

void changsha_clean(tNoodleSoup *nds) {
	tGuangdongNdSoup *gnds = (tGuangdongNdSoup *)nds;
	printf("%s 吃完了\n", nds->name);
	free(gnds);
}

tNoodleSoup *changsha_create(void) {
	tGuangdongNdSoup *nds = (tGuangdongNdSoup *)malloc(sizeof(tGuangdongNdSoup));

	strcpy(nds->base.noodles, "拉面");
	strcpy(nds->base.broth, "辣汤");
	strcpy(nds->base.toppings, "大白菜");
	strcpy(nds->base.meat, "牛肉");
	strcpy(nds->base.sauce, "辣椒面");
	strcpy(nds->base.name, "麻辣牛肉面");

	nds->base.prize = 8;
	nds->base.prepare = changsha_prepare;
	nds->base.deliver = changsha_deliver;
	nds->base.pay = changsha_pay;
	nds->base.clean = changsha_clean;

	return (tNoodleSoup *)nds;
}

/* ============================================================================================= */

tNoodleFactoryTables tables[] = {
	{"GuangDong", guangdong_create},
	{"ChangSha", changsha_create},
};

int main(void) {
	factory_init(tables, sizeof(tables) / sizeof(tNoodleFactoryTables));
	tNoodleSoup *a = order("GuangDong");
	printf("\n\n");
	tNoodleSoup *b = order("ChangSha");

	printf("\n\n");
	eat(a);
	eat(b);

	return 0;
}

