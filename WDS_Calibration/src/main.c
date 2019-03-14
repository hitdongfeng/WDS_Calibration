/************************************************************************
Main.c
日期:    2/4/2019
作者:	张清周
邮箱:	wdswater@gmail.com
单位:    浙江大学建筑工程学院
功能:    本项目运行主函数。
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

char* inpfile;	/* 管网模型.inp文件指针 */
Pdata Textdata; /* data.txt文件数据结构体指针 */
double Pressure_factor, Flow_factor; /* 压力、流量转换因子(目标函数无量纲化) */
HINSTANCE epadll, gadll; /* dll指针 */
int Population_Initi_Size, Maximum_Generations; /* 初始种群数量、最大迭代代数 */
double Totaldemand;	/* 校核时刻系统总需水量 */

void ObjectiveFunction(double* vars, double* objs, double* consts)
/**--------------------------------------------------------------
**  输入: *vars: 决策变量数组指针
**  输出: *objs: 目标函数值; *consts: 约束值
**  功能: 计算目标函数
**--------------------------------------------------------------*/
{
	int errcode = 0;/* 错误编码 */
	long t, tstep;  /* t: 当前时刻; tstep: 计算时间步长 */
	int index; /* 分组索引 */
	double demand, adjustdemand,pressure,flow; 
	double sumerror = 0.0; /* 累计误差 */

	double netdemand=0;

	ERRCODE(_ENopen(inpfile, "report.rpt", "")); /* 打开inp文件 */

	/* 设置节点需水量调整值 */
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

	ERRCODE(_ENopenH());	/* 打开水力模型求解器 */
	ERRCODE(_ENinitH(0));	/* 初始化水力模型求解器 */
	do
	{
		ERRCODE(_ENrunH(&t));
		if (t / 3600 == 0) /* 单时段 */
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
	ERRCODE(_ENcloseH()); /* 关闭水力模型求解器 */

	/* 还原节点需水量值 */
	for (int i = 0; i < Textdata->NumOfDemandNode; i++)
		ERRCODE(_ENsetnodevalue(Textdata->node->ement[i].IDindex, EN_BASEDEMAND, Textdata->node->ement[i].Inivalue));
	ERRCODE(_ENclose()); /* 关闭模型，释放内存 */
	
	objs[0] = sumerror;
}

int main(int argc, char* argv[])
{
	inpfile = "hz.inp";			 /* 管网模型.inp文件指针 */
	Pressure_factor = 1.0;		 /* 压力转换因子(目标函数无量纲化) */
	Flow_factor = 10.0;			 /* 流量转换因子(目标函数无量纲化) */
	Population_Initi_Size = 100; /* 初始化种群大小 */
	Maximum_Generations = 1000;  /* 最大迭代代数 */
	Totaldemand = 2656;		     /* 校核时刻实际总需水量 */

	epadll = LoadLibrary("EPANETx64PDD.dll"); Validate_dll(epadll); /* 加载EPANET动态链接库 */
	gadll = LoadLibrary("GA.dll"); Validate_dll(gadll); /* 加载GA算法动态链接库 */
	GetFuncAddress(epadll,gadll); /* 获取API接口函数地址 */

	Textdata = readdata("data.txt"); /* 读取data.txt数据 */
	getindex(Textdata, inpfile);	 /* 获取监测点节点/管道ID索引 */

	/* 创建供水管网节点需水量校核模型 */
	GA_Problem problem = _GA_Problem_create(Textdata->node->NumOfGroups, 1, 0, ObjectiveFunction);

	/* 设置决策变量取值上限、下限 */
	for (int i = 0; i < Textdata->node->NumOfGroups; i++)
		_GA_Problem_set_bounds(problem, i, -0.15, 0.15);
	_GA_Problem_set_epsilon(problem, 0, 0.01); /* 设置目标函数网格大小 */

	/* 初始化GA算法，将相关参数设为默认值 */
	GA_Algorithm algorithm = _GA_Algorithm_Initialize(problem);
	_GA_Algorithm_set_initial_population_size(algorithm, Population_Initi_Size); /* 设置初始种群大小 */
	_GA_Random_seed(200);

	/* GA算法主循环过程 */
	while (_GA_Algorithm_get_nfe(algorithm) < Maximum_Generations) {

		if (_GA_Algorithm_get_nfe(algorithm) % 10 == 0)
			printf("Complited %d / %d \n", _GA_Algorithm_get_nfe(algorithm), Maximum_Generations);
		_GA_Algorithm_step(algorithm);
	}

	/* 存储最优计算结果 */
	GA_Archive result = _GA_Algorithm_get_result(algorithm);
	
	/* 输出最优计算结果 */
	save_results(Textdata, result, inpfile, Totaldemand);


	/* 释放内存,卸载动态链接库 */
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