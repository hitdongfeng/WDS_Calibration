/************************************************************************
Function.c
����:    2/4/2019
����:	������
����:	wdswater@gmail.com
��λ:    �㽭��ѧ��������ѧԺ
����:    ���屾��Ŀ�йصĺ�����
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
#include "GAtoolkit.h"
#define EXTERN extern
#include "General.h"

void Error(const char* format, ...) 
/**--------------------------------------------------------------
**  ����: format: ��ʽ�ַ���
**  ���: ��
**  ����: ���������Ϣ
**--------------------------------------------------------------*/
{
	va_list arguments;

	va_start(arguments, format);
	vfprintf(stderr, format, arguments);
	va_end(arguments);

	exit(EXIT_FAILURE);
}

void Validate_file(FILE* fp)
/**--------------------------------------------------------------
**  ����: fp: �ļ�ָ��
**  ���: ��
**  ����: ��ʵ�ļ�ָ���Ƿ���Ч
**--------------------------------------------------------------*/
{
	if (!fp) {
		Error("unable to open file: %s\n", strerror(errno));
	}
}

void Validate_dll(HINSTANCE hdll)
/**--------------------------------------------------------------
**  ����: hdll: dll��̬��ָ��
**  ���: ��
**  ����: ��ʵdllָ���Ƿ���Ч
**--------------------------------------------------------------*/
{
	if (!hdll) {
		Error("unable to LoadLibrary.\n");
	}
}

void Validate_pointer(const void* ptr) 
/**--------------------------------------------------------------
**  ����: ptr: ��̬�������ָ��
**  ���: ��
**  ����: ��ʵ�ѷ�����ڴ��Ƿ���Ч
**--------------------------------------------------------------*/
{
	if (!ptr) {
		Error("pointer to NULL object\n");
	}
}

void GetFuncAddress(HINSTANCE pt, HINSTANCE pt1)
/**--------------------------------------------------------------
**  ����: pt: dll�ļ�ָ��; pt1: dll�ļ�ָ��
**  ���: ��
**  ����: ��ȡdll�ļ��ж�Ӧ�����ĵ�ַ
**--------------------------------------------------------------*/
{
	int errsum = 0;

	/******************* EPANET���API���� ************************/
	_ENopen = (ENopen_)GetProcAddress(pt, "ENopen"); if (_ENopen == NULL) errsum++;
	_ENsaveinpfile = (ENsaveinpfile_)GetProcAddress(pt, "ENsaveinpfile"); if (_ENsaveinpfile == NULL) errsum++;
	_ENclose = (ENclose_)GetProcAddress(pt, "ENclose"); if (_ENclose == NULL) errsum++;
	_ENopenH = (ENopenH_)GetProcAddress(pt, "ENopenH"); if (_ENopenH == NULL) errsum++;
	_ENinitH = (ENinitH_)GetProcAddress(pt, "ENinitH"); if (_ENinitH == NULL) errsum++;
	_ENrunH = (ENrunH_)GetProcAddress(pt, "ENrunH"); if (_ENrunH == NULL) errsum++;
	_ENnextH = (ENnextH_)GetProcAddress(pt, "ENnextH"); if (_ENnextH == NULL) errsum++;
	_ENcloseH = (ENcloseH_)GetProcAddress(pt, "ENcloseH"); if (_ENcloseH == NULL) errsum++;
	_ENgetnodeindex = (ENgetnodeindex_)GetProcAddress(pt, "ENgetnodeindex"); if (_ENgetnodeindex == NULL) errsum++;
	_ENgetnodeid = (ENgetnodeid_)GetProcAddress(pt, "ENgetnodeid"); if (_ENgetnodeid == NULL) errsum++;
	_ENgetnodevalue = (ENgetnodevalue_)GetProcAddress(pt, "ENgetnodevalue"); if (_ENgetnodevalue == NULL) errsum++;
	_ENgettankvalue = (ENgettankvalue_)GetProcAddress(pt, "ENgettankvalue"); if (_ENgettankvalue == NULL) errsum++;
	_ENsettankvalue = (ENsettankvalue_)GetProcAddress(pt, "ENsettankvalue"); if (_ENsettankvalue == NULL) errsum++;
	_ENgetlinkindex = (ENgetlinkindex_)GetProcAddress(pt, "ENgetlinkindex"); if (_ENgetlinkindex == NULL) errsum++;
	_ENgetlinkid = (ENgetlinkid_)GetProcAddress(pt, "ENgetlinkid"); if (_ENgetlinkid == NULL) errsum++;
	_ENgetlinkvalue = (ENgetlinkvalue_)GetProcAddress(pt, "ENgetlinkvalue"); if (_ENgetlinkvalue == NULL) errsum++;
	_ENsetnodevalue = (ENsetnodevalue_)GetProcAddress(pt, "ENsetnodevalue"); if (_ENsetnodevalue == NULL) errsum++;
	_ENsetlinkvalue = (ENsetlinkvalue_)GetProcAddress(pt, "ENsetlinkvalue"); if (_ENsetlinkvalue == NULL) errsum++;
	
	/******************* GA���API���� ************************/
	_GA_Random_seed = (GA_Random_seed_)GetProcAddress(pt1, "GA_Random_seed"); if (_GA_Random_seed == NULL) errsum++;
	_GA_Problem_create = (GA_Problem_create_)GetProcAddress(pt1, "GA_Problem_create"); if (_GA_Problem_create == NULL) errsum++;
	_GA_Problem_set_bounds = (GA_Problem_set_bounds_)GetProcAddress(pt1, "GA_Problem_set_bounds"); if (_GA_Problem_set_bounds == NULL) errsum++;
	_GA_Problem_set_epsilon = (GA_Problem_set_epsilon_)GetProcAddress(pt1, "GA_Problem_set_epsilon"); if (_GA_Problem_set_epsilon == NULL) errsum++;
	_GA_Algorithm_Initialize = (GA_Algorithm_Initialize_)GetProcAddress(pt1, "GA_Algorithm_Initialize"); if (_GA_Algorithm_Initialize == NULL) errsum++;
	_GA_Algorithm_get_nfe = (GA_Algorithm_get_nfe_)GetProcAddress(pt1, "GA_Algorithm_get_nfe"); if (_GA_Algorithm_get_nfe == NULL) errsum++;
	_GA_Algorithm_step = (GA_Algorithm_step_)GetProcAddress(pt1, "GA_Algorithm_step"); if (_GA_Algorithm_step == NULL) errsum++;
	_GA_Algorithm_get_result = (GA_Algorithm_get_result_)GetProcAddress(pt1, "GA_Algorithm_get_result"); if (_GA_Algorithm_get_result == NULL) errsum++;
	_GA_Algorithm_initialize_destroy = (GA_Algorithm_initialize_destroy_)GetProcAddress(pt1, "GA_Algorithm_initialize_destroy"); if (_GA_Algorithm_initialize_destroy == NULL) errsum++;
	_GA_Archive_destroy = (GA_Archive_destroy_)GetProcAddress(pt1, "GA_Archive_destroy"); if (_GA_Archive_destroy == NULL) errsum++;
	_GA_Problem_destroy = (GA_Problem_destroy_)GetProcAddress(pt1, "GA_Problem_destroy"); if (_GA_Problem_destroy == NULL) errsum++;
	_GA_Algorithm_set_initial_population_size = (GA_Algorithm_set_initial_population_size_)GetProcAddress(pt1, "GA_Algorithm_set_initial_population_size"); if (_GA_Algorithm_set_initial_population_size == NULL) errsum++;
	_GA_Algorithm_set_minimum_population_size = (GA_Algorithm_set_minimum_population_size_)GetProcAddress(pt1, "GA_Algorithm_set_minimum_population_size"); if (_GA_Algorithm_set_minimum_population_size == NULL) errsum++;
	_GA_Algorithm_destroy = (GA_Algorithm_destroy_)GetProcAddress(pt1, "GA_Algorithm_destroy"); if (_GA_Algorithm_destroy == NULL) errsum++;

	if (errsum)
		Error("Error occurred in GetFuncAddress\n");
}

void getIdindex(Pdata Textdata, char* Inpfile)
/**--------------------------------------------------------------
**  ����: Textdata: data.txt���ݽṹ��ָ��; Inpfile: ģ��inp�ļ�ָ��
**  ���: ��
**  ����: ��ȡ�ڵ�/�ܵ�ID��Ӧ������
**--------------------------------------------------------------*/
{
	Validate_pointer(Textdata);
	Validate_pointer(Inpfile);
	double demand;

	if (Textdata->NumOfPressureSensor > 0 
		|| Textdata->NumOfFlowSensor > 0 
		|| Textdata->NumOfDemandNode > 0)
	{
		int errcode = 0;

		ERRCODE(_ENopen(Inpfile, "report.rpt", "")); /* ��inp�ļ� */

		if (Textdata->NumOfPressureSensor > 0)
		{
			for (int i = 0; i < Textdata->NumOfPressureSensor; i++)
				ERRCODE(_ENgetnodeindex(Textdata->presensor[i].ID, &Textdata->presensor[i].index));	/* ��ȡ����ID���� */
		}

		if (Textdata->NumOfFlowSensor > 0)
		{
			for (int i = 0; i < Textdata->NumOfFlowSensor; i++)
				ERRCODE(_ENgetlinkindex(Textdata->flowsensor[i].ID, &Textdata->flowsensor[i].index));	/* ��ȡ����ID���� */
		}
		
		if (Textdata->NumOfDemandNode > 0)
		{
			for (int i = 0; i < Textdata->NumOfDemandNode; i++)
				ERRCODE(_ENgetnodeindex(Textdata->node->ement[i].ID, &Textdata->node->ement[i].IDindex));	/* ��ȡ��ˮ���ڵ�ID���� */
		}

		/* ��ȡ�ڵ�����ˮ�� */
		Textdata->Totaldemand = 0;
		for (int i = 0; i < Textdata->NumOfDemandNode; i++)
		{
			ERRCODE(_ENgetnodevalue(Textdata->node->ement[i].IDindex, EN_BASEDEMAND, &demand));
			Textdata->Totaldemand += demand;
		}
		
		ERRCODE(_ENclose());
	}
	else
		Error("Empty data file!\n");
}

int  findmatch_slist(char *line, const Plist keyword)
/**--------------------------------------------------------------
**  ����: *line  = line from input file
**       keyword = list of NULL terminated keywords
**  ���: returns index of matching keyword or -1 if no match found
**  ����: determines which keyword appears on input line
**--------------------------------------------------------------*/
{
	Validate_pointer(line);
	Validate_pointer(keyword);

	int i = 0;
	Plist p= keyword;
	while (p != NULL)
	{
		if(match(line, p->Char)) 
			return(i);
		i++;
		p = p->next;
	}
	return(-1);
}

void getGroupindex(Pdata Textdata)
/**--------------------------------------------------------------
**  ����: Textdata: data.txt���ݽṹ��ָ��
**  ���: ��
**  ����: ��ȡ�ڵ����ID��Ӧ������
**--------------------------------------------------------------*/
{
	Validate_pointer(Textdata);

	int flag, group_count = 0;
	Plist p;
	Plist pt;

	if (Textdata->NumOfDemandNode > 0)
	{
		p = (Plist)calloc(1, sizeof(struct Slist_));
		Validate_pointer(p);
		p->Char = Textdata->node->ement[0].groupID;
		p->next = NULL;
		group_count++;

		for (int i = 1; i < Textdata->NumOfDemandNode; i++)
		{
			flag = findmatch_slist(Textdata->node->ement[i].groupID, p);
			if (flag < 0)
			{
				pt = (Plist)calloc(1, sizeof(struct Slist_));
				Validate_pointer(p);
				pt->Char = Textdata->node->ement[i].groupID;
				pt->next = p;
				p = pt;
				group_count++;
			}
		}

		Textdata->node->NumOfGroups = group_count;

		for (int i = 0; i < Textdata->NumOfDemandNode; i++)
		{
			flag = findmatch_slist(Textdata->node->ement[i].groupID, p);
			if (flag >= 0)
				Textdata->node->ement[i].groupindex = flag;
			else
				Error("Undefined group ID %s.\n", Textdata->node->ement[i].groupID);
		}

		/* �ͷ������ڴ� */
		while (p!=NULL)
		{
			pt = p;
			p = p->next;
			free(pt);
		}

	}
	
}

void getindex(Pdata Textdata, char* Inpfile)
/**--------------------------------------------------------------
**  ����:  Textdata: data.txt���ݽṹ��ָ��; Inpfile: ģ��inp�ļ�ָ��
**  ���: ��
**  ����: ��ȡ�ڵ�/�ܵ�������ID��Ӧ������
**--------------------------------------------------------------*/
{
	getIdindex(Textdata, Inpfile);
	getGroupindex(Textdata);
}

void save_results(Pdata Textdata, GA_Archive result, char*inpfile,double Totaldemand)
/**--------------------------------------------------------------
**  ����:  Textdata: data.txt���ݽṹ��ָ��; result: ���Ž�ṹ��ָ��
**		  inpfile: ģ��inp�ļ�ָ��; Totaldemand: У��ʱ��ϵͳ����ˮ��
**  ���: ��
**  ����: �������Ž⣬������У����Ĺ���ģ��inp�ļ�
**--------------------------------------------------------------*/
{
	Validate_pointer(Textdata);
	Validate_pointer(result);
	
	int errcode = 0;/* ������� */
	int index;
	double demand,adjustdemand;
	double netdemand = 0;

	GA_Entry entry = result->head;
	GA_Solution solution = entry->solution;
	FILE* fp = fopen("results.txt", "w");
	ERRCODE(_ENopen(inpfile, "report.rpt", "")); /* ��inp�ļ� */
	double* x = (double*)calloc(solution->problem->numberOfVariables, sizeof(double));

	while (entry)
	{
		solution = entry->solution;
		
		for (int i = 0; i < solution->problem->numberOfVariables; i++)
		{
			//fprintf(fp, "GroupIndex[%d]: %.4f\n", i, solution->variables[i]);
			x[i] = solution->variables[i];
		}	

		for (int i = 0; i < solution->problem->numberOfObjectives; i++)
			fprintf(fp, "Objective value: %.4f\n", solution->objectives[i]);

		entry = entry->next;
	}
	fprintf(fp, "\n******Calibrated demand*****\n");
	fprintf(fp, "ID	 CalibratedValue\n");
	/* ���ýڵ���ˮ������ֵ */
	for (int i = 0; i < Textdata->NumOfDemandNode; i++)
	{
		adjustdemand = Textdata->node->ement[i].Inivalue*(Totaldemand / Textdata->Totaldemand);
		index = Textdata->node->ement[i].groupindex;
		adjustdemand *= (1 + x[index]);
		ERRCODE(_ENsetnodevalue(Textdata->node->ement[i].IDindex, EN_BASEDEMAND, adjustdemand));
		netdemand += adjustdemand;

	}
	if (netdemand - Totaldemand)
	{
		for (int i = 0; i < Textdata->NumOfDemandNode; i++)
		{
			ERRCODE(_ENgetnodevalue(Textdata->node->ement[i].IDindex, EN_BASEDEMAND, &demand));
			if (demand > (netdemand - Totaldemand) / Textdata->NumOfDemandNode)
				ERRCODE(_ENsetnodevalue(Textdata->node->ement[i].IDindex, EN_BASEDEMAND, demand - (netdemand - Totaldemand) / Textdata->NumOfDemandNode));
			fprintf(fp, "%s    %.4f\n", Textdata->node->ement[i].ID, demand - (netdemand - Totaldemand) / Textdata->NumOfDemandNode);
		}

	}
	ERRCODE(_ENsaveinpfile("Calibrationed.inp"));

	/* ������Ž��Ӧ�ļ���۲�ֵ�����ֵ */
	long t, tstep;  /* t: ��ǰʱ��; tstep: ����ʱ�䲽�� */
	double pressure, flow; /* */
	ERRCODE(_ENopenH());	/* ��ˮ��ģ������� */
	ERRCODE(_ENinitH(0));	/* ��ʼ��ˮ��ģ������� */
	do
	{
		ERRCODE(_ENrunH(&t));
		if (t / 3600 == 0) /* ��ʱ�� */
		{
			fprintf(fp, "\n**********Pressure********\n");
			fprintf(fp, "Objvalue	Calvalue	error\n");
			for (int j = 0; j < Textdata->NumOfPressureSensor; j++)
			{
				ERRCODE(_ENgetnodevalue(Textdata->presensor[j].index, EN_PRESSURE, &pressure));
				fprintf(fp, "%.2f	%.2f	%0.2f\n", Textdata->presensor[j].value, pressure, Textdata->presensor[j].value-pressure);
			}

			fprintf(fp, "\n***************Flow*************\n");
			fprintf(fp, "Objvalue	Calvalue	Error(%%)\n");
			for (int j = 0; j < Textdata->NumOfFlowSensor; j++)
			{
				ERRCODE(_ENgetlinkvalue(Textdata->flowsensor[j].index, EN_FLOW, &flow));
				fprintf(fp, "%.2f	%.2f	%.2f%%\n", Textdata->flowsensor[j].value, flow, 100*(Textdata->flowsensor[j].value-flow)/ Textdata->flowsensor[j].value);
			}
		}
		ERRCODE(_ENnextH(&tstep));
	} while (tstep > 0);
	ERRCODE(_ENcloseH()); /* �ر�ˮ��ģ������� */

	ERRCODE(_ENclose()); /* �ر�ģ�ͣ��ͷ��ڴ� */
	fclose(fp);
	free(x);

	if (errcode)
		Error("Error in the process of save results!\n");
}

