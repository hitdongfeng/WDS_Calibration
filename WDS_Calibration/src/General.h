/*
***********************************************************************
General.h
日期:    9/3/2019
作者:	张清周
邮箱:	wdswater@gmail.com
单位:    浙江大学建筑工程学院
功能:    声明本项目相关的全局变量、结构体和函数。
**********************************************************************
*/

#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include "windows.h"
#include "GAtoolkit.h"
#define   MAXLINE   100        /* 数据文件每行最大字符数 */
#define   MAXTOKS   50         /* 数据文件每行最大字段数 */
#define	  MAXID		31		   /* Maximum number of characters for ID */
#define   SEPSTR    " \t\n\r"  /* 分割符 */
#define   UCHAR(x)  (((x) >= 'a' && (x) <= 'z') ? ((x)&~32) : (x)) /* 字母转大写 */
#define   ERRCODE(x) (errcode = ((errcode>100) ? (errcode) : (x))) /*Macro to evaluate function x with error checking*/

/*********** Structs *****************/
struct Sensor_
{
	char ID[MAXID]; /* 监测点ID */
	int index;		/* 监测点ID索引 */
	double value;	/* 监测点观测值 */
};
typedef struct Sensor_* Psensor;  /* 监测点结构体指针 */

struct element_
{
	char ID[MAXID];		/* 节点/管道ID */
	int IDindex;		/* 节点/管道ID索引 */
	double Inivalue;	/* 节点/管道的需水量/阻力系数初始值 */
	char groupID[MAXID];/* 节点/管道分组ID */
	int groupindex;		/* 节点/管道分组ID索引 */
};
typedef struct element_* Pelement;	/* 节点/管道结构体指针 */

struct Calielement_
{
	int NumOfGroups;	/* 节点/管道分组数量 */
	Pelement ement;		/* 节点/管道结构体数组 */
};
typedef struct Calielement_* Pcalielement; /* 校核元素结构体指针 */

struct Data_
{
	int NumOfPressureSensor; /* 压力监测点数量 */
	int NumOfFlowSensor;	/* 流量监测点数量 */
	int NumOfDemandNode;	/* 需要校核的节点数量 */
	double Totaldemand;
	Psensor presensor;		/* 压力监测点结构体指针 */
	Psensor flowsensor;		/* 流量监测点结构体指针 */
	Pcalielement node;		/* 校核元素结构体指针 */
};
typedef struct Data_* Pdata; /* 数据库结构体指针 */

struct Slist_
{
	char* Char;				/* 字符串指针 */
	struct Slist_ *next;	/* 指向下一个结构体 */
};
typedef struct Slist_* Plist; /* 单向链表结构体指针 */

/*********** Functions *****************/
void Error(const char* format, ...); /* 输出错误信息并终止程序 */
void Validate_file(FILE*);	/* 若文件指针无效，则输出错误并中止程序 */
void Validate_pointer(const void* ); /* 若指针无效，则输出错误并中止程序 */
void Validate_dll(HINSTANCE); /* 若dll指针无效，则输出错误并中止程序 */
int match(char*, char*);	/* 字符串一致性检验 */
Pdata  readdata(char *); /* 读取data.txt数据 */
void Textdata_destroy(Pdata); /* 清除Textdata结构体内存 */
void GetFuncAddress(HINSTANCE, HINSTANCE); /* 获取dll文件中对应函数的地址 */
void getindex(Pdata , char*); /* 节点/管道、分组ID对应的索引 */
void save_results(Pdata, GA_Archive, char*,double); /* 输出计算结果和校正好的模型inp文件 */

#endif