/************************************************************************
dllfuns.h
日期:    2/4/2019
作者:	张清周
邮箱:	wdswater@gmail.com
单位:    浙江大学建筑工程学院
功能:    声明dll文件函数指针类型，赋给函数指针的函数应该和函数指针所指的函数原型一致。
*************************************************************************/

#ifndef DLLFUNS_H
#define DLLFUNS_H

#include "GAtoolkit.h"

/************* 定义EPANET API函数指针类型 ***************/
typedef int(*ENopen_)(char *, char *, char *);
typedef int(*ENsaveinpfile_)(char *);
typedef int(*ENclose_)(void);
typedef int(*ENopenH_)(void);
typedef int(*ENinitH_)(int);
typedef int(*ENrunH_)(long *);
typedef int(*ENnextH_)(long *);
typedef int(*ENcloseH_)(void);
typedef int(*ENgetnodeindex_)(char *, int *);
typedef int(*ENgetnodeid_)(int, char *);
typedef int(*ENgetnodevalue_)(int, int, double *);
typedef int(*ENgettankvalue_)(int index, int code, double *value);
typedef int(*ENsettankvalue_)(int index, int code, double value);
typedef int(*ENgetlinkindex_)(char *, int *);
typedef int(*ENgetlinkid_)(int, char *);
typedef int(*ENgetlinkvalue_)(int, int, double *);
typedef int(*ENsetnodevalue_)(int, int, double);
typedef int(*ENsetlinkvalue_)(int, int, double);

/************* 定义GA API函数指针类型 ***************/
typedef void(*GA_Random_seed_)(unsigned long);
typedef GA_Problem(*GA_Problem_create_)(int, int, int, void(*function)(double*, double*, double*));
typedef void(*GA_Problem_set_bounds_)(GA_Problem, int, double, double);
typedef void(*GA_Problem_set_epsilon_)(GA_Problem, int, double);
typedef GA_Algorithm(*GA_Algorithm_Initialize_)(GA_Problem);
typedef int(*GA_Algorithm_get_nfe_)(GA_Algorithm);
typedef void(*GA_Algorithm_step_)(GA_Algorithm);
typedef GA_Archive(*GA_Algorithm_get_result_)(GA_Algorithm);
typedef void(*GA_Algorithm_initialize_destroy_)(GA_Algorithm);
typedef void(*GA_Archive_destroy_)(GA_Archive);
typedef void(*GA_Problem_destroy_)(GA_Problem);
typedef void(*GA_Algorithm_set_initial_population_size_)(GA_Algorithm, int);
typedef void(*GA_Algorithm_set_minimum_population_size_)(GA_Algorithm, int); 
typedef void(*GA_Algorithm_destroy_)(GA_Algorithm);

/************* 定义EPANET API函数别名***************/
ENopen_ _ENopen;
ENsaveinpfile_ _ENsaveinpfile;
ENclose_ _ENclose;
ENopenH_ _ENopenH;
ENinitH_ _ENinitH;
ENrunH_ _ENrunH;
ENnextH_ _ENnextH;
ENcloseH_ _ENcloseH;
ENgetnodeindex_ _ENgetnodeindex;
ENgetnodeid_ _ENgetnodeid;
ENgetnodevalue_ _ENgetnodevalue;
ENgettankvalue_ _ENgettankvalue;
ENsettankvalue_ _ENsettankvalue;
ENgetlinkindex_ _ENgetlinkindex;
ENgetlinkid_ _ENgetlinkid;
ENgetlinkvalue_ _ENgetlinkvalue;
ENsetnodevalue_ _ENsetnodevalue;
ENsetlinkvalue_ _ENsetlinkvalue;

/************* 定义GA API函数别名***************/
GA_Random_seed_ _GA_Random_seed;
GA_Problem_create_ _GA_Problem_create;
GA_Problem_set_bounds_ _GA_Problem_set_bounds;
GA_Problem_set_epsilon_ _GA_Problem_set_epsilon;
GA_Algorithm_Initialize_ _GA_Algorithm_Initialize;
GA_Algorithm_get_nfe_ _GA_Algorithm_get_nfe;
GA_Algorithm_step_ _GA_Algorithm_step;
GA_Algorithm_get_result_ _GA_Algorithm_get_result;
GA_Algorithm_initialize_destroy_ _GA_Algorithm_initialize_destroy;
GA_Archive_destroy_ _GA_Archive_destroy;
GA_Problem_destroy_ _GA_Problem_destroy;
GA_Algorithm_set_initial_population_size_ _GA_Algorithm_set_initial_population_size;
GA_Algorithm_set_minimum_population_size_ _GA_Algorithm_set_minimum_population_size;
GA_Algorithm_destroy_ _GA_Algorithm_destroy;

#endif
