/*
***********************************************************************
General.h
����:    9/3/2019
����:	������
����:	wdswater@gmail.com
��λ:    �㽭��ѧ��������ѧԺ
����:    ��������Ŀ��ص�ȫ�ֱ������ṹ��ͺ�����
**********************************************************************
*/

#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include "windows.h"
#include "GAtoolkit.h"
#define   MAXLINE   100        /* �����ļ�ÿ������ַ��� */
#define   MAXTOKS   50         /* �����ļ�ÿ������ֶ��� */
#define	  MAXID		31		   /* Maximum number of characters for ID */
#define   SEPSTR    " \t\n\r"  /* �ָ�� */
#define   UCHAR(x)  (((x) >= 'a' && (x) <= 'z') ? ((x)&~32) : (x)) /* ��ĸת��д */
#define   ERRCODE(x) (errcode = ((errcode>100) ? (errcode) : (x))) /*Macro to evaluate function x with error checking*/

/*********** Structs *****************/
struct Sensor_
{
	char ID[MAXID]; /* ����ID */
	int index;		/* ����ID���� */
	double value;	/* ����۲�ֵ */
};
typedef struct Sensor_* Psensor;  /* ����ṹ��ָ�� */

struct element_
{
	char ID[MAXID];		/* �ڵ�/�ܵ�ID */
	int IDindex;		/* �ڵ�/�ܵ�ID���� */
	double Inivalue;	/* �ڵ�/�ܵ�����ˮ��/����ϵ����ʼֵ */
	char groupID[MAXID];/* �ڵ�/�ܵ�����ID */
	int groupindex;		/* �ڵ�/�ܵ�����ID���� */
};
typedef struct element_* Pelement;	/* �ڵ�/�ܵ��ṹ��ָ�� */

struct Calielement_
{
	int NumOfGroups;	/* �ڵ�/�ܵ��������� */
	Pelement ement;		/* �ڵ�/�ܵ��ṹ������ */
};
typedef struct Calielement_* Pcalielement; /* У��Ԫ�ؽṹ��ָ�� */

struct Data_
{
	int NumOfPressureSensor; /* ѹ���������� */
	int NumOfFlowSensor;	/* ������������ */
	int NumOfDemandNode;	/* ��ҪУ�˵Ľڵ����� */
	double Totaldemand;
	Psensor presensor;		/* ѹ������ṹ��ָ�� */
	Psensor flowsensor;		/* ��������ṹ��ָ�� */
	Pcalielement node;		/* У��Ԫ�ؽṹ��ָ�� */
};
typedef struct Data_* Pdata; /* ���ݿ�ṹ��ָ�� */

struct Slist_
{
	char* Char;				/* �ַ���ָ�� */
	struct Slist_ *next;	/* ָ����һ���ṹ�� */
};
typedef struct Slist_* Plist; /* ��������ṹ��ָ�� */

/*********** Functions *****************/
void Error(const char* format, ...); /* ���������Ϣ����ֹ���� */
void Validate_file(FILE*);	/* ���ļ�ָ����Ч�������������ֹ���� */
void Validate_pointer(const void* ); /* ��ָ����Ч�������������ֹ���� */
void Validate_dll(HINSTANCE); /* ��dllָ����Ч�������������ֹ���� */
int match(char*, char*);	/* �ַ���һ���Լ��� */
Pdata  readdata(char *); /* ��ȡdata.txt���� */
void Textdata_destroy(Pdata); /* ���Textdata�ṹ���ڴ� */
void GetFuncAddress(HINSTANCE, HINSTANCE); /* ��ȡdll�ļ��ж�Ӧ�����ĵ�ַ */
void getindex(Pdata , char*); /* �ڵ�/�ܵ�������ID��Ӧ������ */
void save_results(Pdata, GA_Archive, char*,double); /* �����������У���õ�ģ��inp�ļ� */

#endif