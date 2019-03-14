/************************************************************************
Main.c
����:    2/4/2019
����:	������
����:	wdswater@gmail.com
��λ:    �㽭��ѧ��������ѧԺ
����:    ����Ŀ������������
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <windows.h>
#include "epatoolkit.h"
#include "dllfuns.h"
#include "General.h"

char* inpfile;	/* ����ģ��.inp�ļ�ָ�� */
Pdata Textdata; /* data.txt�ļ����ݽṹ��ָ�� */
double Pressure_factor, Flow_factor; /* ѹ��������ת������(Ŀ�꺯�������ٻ�) */
HINSTANCE epadll, gadll; /* dllָ�� */
int Population_Initi_Size, Maximum_Generations; /* ��ʼ��Ⱥ���������������� */
double Totaldemand;	/* У��ʱ��ϵͳ����ˮ�� */

void ObjectiveFunction(double* vars, double* objs, double* consts)
/**--------------------------------------------------------------
**  ����: *vars: ���߱�������ָ��
**  ���: *objs: Ŀ�꺯��ֵ; *consts: Լ��ֵ
**  ����: ����Ŀ�꺯��
**--------------------------------------------------------------*/
{
	int errcode = 0;/* ������� */
	long t, tstep;  /* t: ��ǰʱ��; tstep: ����ʱ�䲽�� */
	int index; /* �������� */
	double demand, adjustdemand,pressure,flow; 
	double sumerror = 0.0; /* �ۼ���� */

	double netdemand=0;

	ERRCODE(_ENopen(inpfile, "report.rpt", "")); /* ��inp�ļ� */

	/* ���ýڵ���ˮ������ֵ */
	for (int i = 0; i < Textdata->NumOfDemandNode; i++)
	{
		adjustdemand = Textdata->node->ement[i].Inivalue*(Totaldemand / Textdata->Totaldemand);
		index = Textdata->node->ement[i].groupindex;
		adjustdemand *= (1 + vars[index]);
		ERRCODE(_ENsetnodevalue(Textdata->node->ement[i].IDindex, EN_BASEDEMAND, adjustdemand));
		netdemand += adjustdemand;
	}
	if (netdemand- Totaldemand)
	{
		for (int i = 0; i < Textdata->NumOfDemandNode; i++)
		{
			ERRCODE(_ENgetnodevalue(Textdata->node->ement[i].IDindex, EN_BASEDEMAND, &demand));
			if(demand > (netdemand - Totaldemand) / Textdata->NumOfDemandNode)
				ERRCODE(_ENsetnodevalue(Textdata->node->ement[i].IDindex, EN_BASEDEMAND, demand - (netdemand - Totaldemand) / Textdata->NumOfDemandNode));
		}

	}

	ERRCODE(_ENopenH());	/* ��ˮ��ģ������� */
	ERRCODE(_ENinitH(0));	/* ��ʼ��ˮ��ģ������� */
	do
	{
		ERRCODE(_ENrunH(&t));
		if (t / 3600 == 0) /* ��ʱ�� */
		{
			for (int j = 0; j < Textdata->NumOfPressureSensor; j++)
			{
				ERRCODE(_ENgetnodevalue(Textdata->presensor[j].index, EN_PRESSURE, &pressure));
				sumerror += (Textdata->presensor[j].value - pressure)*(Textdata->presensor[j].value - pressure) / (Pressure_factor*Pressure_factor);
			}

			for (int j = 0; j < Textdata->NumOfFlowSensor; j++)
			{
				ERRCODE(_ENgetlinkvalue(Textdata->flowsensor[j].index, EN_FLOW, &flow));
				sumerror += (Textdata->flowsensor[j].value - flow)*(Textdata->flowsensor[j].value - flow) / (Flow_factor*Flow_factor);
			}
		}
		ERRCODE(_ENnextH(&tstep));
	} while (tstep > 0);
	ERRCODE(_ENcloseH()); /* �ر�ˮ��ģ������� */

	/* ��ԭ�ڵ���ˮ��ֵ */
	for (int i = 0; i < Textdata->NumOfDemandNode; i++)
		ERRCODE(_ENsetnodevalue(Textdata->node->ement[i].IDindex, EN_BASEDEMAND, Textdata->node->ement[i].Inivalue));
	ERRCODE(_ENclose()); /* �ر�ģ�ͣ��ͷ��ڴ� */
	
	objs[0] = sumerror;
}

int main(int argc, char* argv[])
{
	inpfile = "hz.inp";			 /* ����ģ��.inp�ļ�ָ�� */
	Pressure_factor = 1.0;		 /* ѹ��ת������(Ŀ�꺯�������ٻ�) */
	Flow_factor = 10.0;			 /* ����ת������(Ŀ�꺯�������ٻ�) */
	Population_Initi_Size = 100; /* ��ʼ����Ⱥ��С */
	Maximum_Generations = 1000;  /* ���������� */
	Totaldemand = 2656;		     /* У��ʱ��ʵ������ˮ�� */

	epadll = LoadLibrary("EPANETx64PDD.dll"); Validate_dll(epadll); /* ����EPANET��̬���ӿ� */
	gadll = LoadLibrary("GA.dll"); Validate_dll(gadll); /* ����GA�㷨��̬���ӿ� */
	GetFuncAddress(epadll,gadll); /* ��ȡAPI�ӿں�����ַ */

	Textdata = readdata("data.txt"); /* ��ȡdata.txt���� */
	getindex(Textdata, inpfile);	 /* ��ȡ����ڵ�/�ܵ�ID���� */

	/* ������ˮ�����ڵ���ˮ��У��ģ�� */
	GA_Problem problem = _GA_Problem_create(Textdata->node->NumOfGroups, 1, 0, ObjectiveFunction);

	/* ���þ��߱���ȡֵ���ޡ����� */
	for (int i = 0; i < Textdata->node->NumOfGroups; i++)
		_GA_Problem_set_bounds(problem, i, -0.15, 0.15);
	_GA_Problem_set_epsilon(problem, 0, 0.01); /* ����Ŀ�꺯�������С */

	/* ��ʼ��GA�㷨������ز�����ΪĬ��ֵ */
	GA_Algorithm algorithm = _GA_Algorithm_Initialize(problem);
	_GA_Algorithm_set_initial_population_size(algorithm, Population_Initi_Size); /* ���ó�ʼ��Ⱥ��С */
	_GA_Random_seed(200);

	/* GA�㷨��ѭ������ */
	while (_GA_Algorithm_get_nfe(algorithm) < Maximum_Generations) {

		if (_GA_Algorithm_get_nfe(algorithm) % 10 == 0)
			printf("Complited %d / %d \n", _GA_Algorithm_get_nfe(algorithm), Maximum_Generations);
		_GA_Algorithm_step(algorithm);
	}

	/* �洢���ż����� */
	GA_Archive result = _GA_Algorithm_get_result(algorithm);
	
	/* ������ż����� */
	save_results(Textdata, result, inpfile, Totaldemand);


	/* �ͷ��ڴ�,ж�ض�̬���ӿ� */
	Textdata_destroy(Textdata);
	_GA_Algorithm_initialize_destroy(algorithm);
	_GA_Archive_destroy(result);
	_GA_Problem_destroy(problem);
	FreeLibrary(epadll);
	FreeLibrary(gadll);

	printf("successful!\n");
	getchar();
	return 0;
}