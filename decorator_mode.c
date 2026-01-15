#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//装饰者和被装饰者的共同基类
typedef struct Beverage {
	char *description;
	const char* (*getDescription)(struct Beverage* self);
	int (*cost)(struct Beverage* self);
	void (*destory)(struct Beverage* self);
} Beverage;

//被装饰者的具体类
typedef struct DarkRoast {
	Beverage bvg;
} DarkRoast;

const char* darkRoast_getDescription(Beverage* self) {
	return (const char*)(self->description);
}

int darkRoast_cost(Beverage* self) {
	return 12;
}

void darkRoast_destory(Beverage* self) {
	free(self->description);
	free(self);
}

Beverage* darkRoast_create(void) {
	DarkRoast *dr = (DarkRoast *)malloc(sizeof(DarkRoast));
	if(dr == NULL) {
		return NULL;
	}

	dr->bvg.description = malloc(16);
	if(!dr->bvg.description) {
		free(dr);
		return NULL;
	}

	strcpy(dr->bvg.description, "DarkRoast");
	dr->bvg.getDescription = darkRoast_getDescription;
	dr->bvg.cost = darkRoast_cost;
	dr->bvg.destory = darkRoast_destory;

	return (Beverage*)dr; //强转为基类,实现多态
}

//装饰者基类,需要继承被装饰者和装饰者的共同基类,并且使用指针引用具体的被装饰者
typedef struct CondimentDecorator {
	Beverage bvg;
	Beverage *concrete_bvg;
}CondimentDecorator;

//具体装饰类
typedef struct Milk {
	CondimentDecorator milk_dct;
}Milk;

const char* milk_getDescription(Beverage* self) {
	return (const char*)(self->description);
}

int milk_cost(Beverage* self) {
	Milk *m = (Milk *)self;

	return (m->milk_dct.concrete_bvg->cost(m->milk_dct.concrete_bvg) + 3);
}

void milk_destory(Beverage* self) {
	Milk *m = (Milk*)(self);
	m->milk_dct.concrete_bvg->destory(m->milk_dct.concrete_bvg);
	free(m->milk_dct.bvg.description);
	free(m);
}

Beverage* milk_create(Beverage* con_bvg) {
	if(con_bvg == NULL) {
		return NULL;
	}

	Milk *m = (Milk*)malloc(sizeof(Milk));
	if(!m) {
		return NULL;
	}

	int len = strlen(con_bvg->getDescription(con_bvg)) + 8;
	m->milk_dct.bvg.description = malloc(len);
	if(!(m->milk_dct.bvg.description)) {
		free(m);
		return NULL;
	}

	snprintf(m->milk_dct.bvg.description, len - 1, "milk %s", con_bvg->getDescription(con_bvg));
	m->milk_dct.bvg.getDescription = milk_getDescription;
	m->milk_dct.bvg.cost= milk_cost;
	m->milk_dct.bvg.destory= milk_destory;

	m->milk_dct.concrete_bvg = con_bvg;

	return (Beverage*)m;
}

//具体装饰类
typedef struct Whip {
	CondimentDecorator whip_dct;
}Whip;

const char* whip_getDescription(Beverage* self) {
	return (const char*)(self->description);
}

int whip_cost(Beverage* self) {
	Whip *m = (Whip *)self;

	return (m->whip_dct.concrete_bvg->cost(m->whip_dct.concrete_bvg) + 3);
}

void whip_destory(Beverage* self) {
	Whip *m = (Whip*)(self);
	m->whip_dct.concrete_bvg->destory(m->whip_dct.concrete_bvg);
	free(m->whip_dct.bvg.description);
	free(m);
}

Beverage* whip_create(Beverage* con_bvg) {
	if(con_bvg == NULL) {
		return NULL;
	}

	Whip *m = (Whip*)malloc(sizeof(Whip));
	if(!m) {
		return NULL;
	}

	int len = strlen(con_bvg->getDescription(con_bvg)) + 8;
	m->whip_dct.bvg.description = malloc(len);
	if(!(m->whip_dct.bvg.description)) {
		free(m);
		return NULL;
	}

	snprintf(m->whip_dct.bvg.description, len - 1, "whip %s", con_bvg->getDescription(con_bvg));
	m->whip_dct.bvg.getDescription = whip_getDescription;
	m->whip_dct.bvg.cost= whip_cost;
	m->whip_dct.bvg.destory= whip_destory;

	m->whip_dct.concrete_bvg = con_bvg;

	return (Beverage*)m;
}

int main() {
	Beverage *darkroast = darkRoast_create();
	printf("%s : %d$\n", darkroast->getDescription(darkroast), darkroast->cost(darkroast));

	darkroast = milk_create(darkroast);
	printf("%s : %d$\n", darkroast->getDescription(darkroast), darkroast->cost(darkroast));

	darkroast = whip_create(darkroast);
	printf("%s : %d$\n", darkroast->getDescription(darkroast), darkroast->cost(darkroast));

	darkroast->destory(darkroast);
	return 0;
}

