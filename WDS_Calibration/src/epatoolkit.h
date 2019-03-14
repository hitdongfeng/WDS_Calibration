/*
***********************************************************************
epatoolkit.h
日期:    9/3/2019
作者:	张清周
邮箱:	wdswater@gmail.com
单位:    浙江大学建筑工程学院
功能:    声明epanet API函数相关参数编码
**********************************************************************
*/

#ifndef EPATOOLKIT_H
#define EPATOOLKIT_H

/******** 节点属性 *********/
#define EN_ELEVATION			0 
#define EN_BASEDEMAND 			1
#define EN_PATTERN				2
#define EN_EMITTER				3
#define EN_INITQUAL				4
#define EN_SOURCEQUAL			5
#define EN_SOURCEPAT			6
#define EN_SOURCETYPE			7
#define EN_TANKLEVEL			8
#define EN_DEMAND				9
#define EN_HEAD					10
#define EN_PRESSURE				11
#define EN_QUALITY				12
#define EN_SOURCEMASS			13
#define EN_INITVOLUME 			14
#define EN_MIXMODEL				15
#define EN_MIXZONEVOL 			16
#define EN_TANKDIAM 			17
#define EN_MINVOLUME 			18
#define EN_VOLCURVE 			19
#define EN_MINLEVEL 			20
#define EN_MAXLEVEL 			21
#define EN_MIXFRACTION 			22
#define EN_TANK_KBULK 			23
#define EN_COORDINATEX 		    100
#define EN_COORDINATEY 		    101
#define EN_CALCULATEDDEMAND 	110
#define EN_MINIMUMPRESSURE 		120
#define EN_CRITICALPRESSURE 	121
#define EN_EMITTERTYPE 		    122
#define EN_EMITTERSTATUS        123
#define EN_EMITTEREXPONENT 		124

/******** 管段属性 *********/
#define EN_DIAMETER 			0
#define EN_LENGTH 				1
#define EN_ROUGHNESS 			2
#define EN_MINORLOSS 			3
#define EN_INITSTATUS 			4
#define EN_INITSETTING 			5
#define EN_KBULK 				6
#define EN_KWALL 				7
#define EN_FLOW 				8
#define EN_VELOCITY 			9
#define EN_HEADLOSS 			10
#define EN_STATUS 				11
#define EN_SETTING 				12
#define EN_ENERGY 				13
#define EN_VERTEXCOUNT 			100
#define EN_VERTEXX 				101
#define EN_VERTEXY 				102

/******** 水池属性 *********/
#define EN_TANKAREA 		    0
#define EN_TANKMINDEPTH 		1
#define EN_TANKMAXDEPTH 		2
#define EN_TANKINITDEPTH 		3
#define EN_TANKMINVOLUME 		4
#define EN_TANKMAXVOLUME 		5
#define EN_TANKINITVOLUME 	    6
#define EN_TANKVOLUME 		    7

/******** 系统属性 *********/
#define EN_ENERGY_COST_PATTERN 		          901
#define EN_PUMP_PATTERN 		              902
#define EN_PUMP_HEAD_CURVE 		              903
#define EN_PUMP_EFFICIENCY_CURVE 		      904
#define EN_SYSTEM_UNSTABLE 		              911
#define EN_NODES_NEGATIVE_PRESSURE_COUNT      912
#define EN_VALVES_ABNORMAL_CONDITION_COUNT 	  913
#define EN_PUMPS_ABNORMAL_CONDITION_COUNT 	  914
#define EN_SYSTEM_UNBALANCED 		          915
#define EN_NODES_DISCONNECTED_COUNT 		  916

/******** 时间属性 *********/
#define EN_DURATION 		0 
#define EN_HYDSTEP 		    1
#define EN_QUALSTEP 		2
#define EN_PATTERNSTEP 		3
#define EN_PATTERNSTART		4
#define EN_REPORTSTEP 		5
#define EN_REPORTSTART 		6
#define EN_RULESTEP 		7
#define EN_STATISTIC 		8
#define EN_PERIODS 			9

/******** 组件属性 *********/
#define EN_NODECOUNT 		0
#define EN_TANKCOUNT 		1
#define EN_LINKCOUNT 		2
#define EN_PATCOUNT 		3
#define EN_CURVECOUNT 		4
#define EN_CONTROLCOUNT		5

/******** 节点类型 *********/
#define EN_JUNCTION 		0
#define EN_RESERVOIR 		1
#define EN_TANK 		    2

/******** 管段类型 *********/
#define EN_CVPIPE			0 
#define EN_PIPE 			1
#define EN_PUMP 			2
#define EN_PRV 				3
#define EN_PSV 				4
#define EN_PBV 				5
#define EN_FCV 				6
#define EN_TCV 				7
#define EN_GPV 				8

/***** 水质分析类型 ******/
#define EN_NONE 			0 
#define EN_CHEM 			1 
#define EN_AGE 				2
#define EN_TRACE 			3

/****** 水质投加类型 *******/
#define EN_CONCEN 			0 
#define EN_MASS 	   		1 
#define EN_SETPOINT 		2
#define EN_FLOWPACED		3

/****** 流量单位 *******/
#define EN_CFS 				0 
#define EN_GPM 				1 
#define EN_MGD 				2 
#define EN_IMGD 			3
#define EN_AFD 				4
#define EN_LPS 				5
#define EN_LPM 				6
#define EN_MLD 				7
#define EN_CMH 				8
#define EN_CMD 				9

/******** 计算选项 *********/
#define EN_TRIALS 			0 
#define EN_ACCURACY 		1
#define EN_TOLERANCE 		2
#define EN_EMITEXPON 		3
#define EN_DEMANDMULT 		4

/******** 控制类型 *********/
#define EN_LOWLEVEL 		0 
#define EN_HILEVEL 			1 
#define EN_TIMER 		    2 
#define EN_TIMEOFDAY 		3

/***** 时间序列统计类型 ******/
#define EN_AVERAGE 			1 
#define EN_MINIMUM 			2
#define EN_MAXIMUM 			3
#define EN_RANGE 			4

/****** 水池混合类型 *******/
#define EN_MIX1 			0 
#define EN_MIX2 			1
#define EN_FIFO 			2
#define EN_LIFO 			3

/****** 计算结果存储标志 ******/
#define EN_NOSAVE 			0 
#define EN_SAVE 			1

/***** 流量重新初始化标志 *****/
#define EN_INITFLOW			10 

#endif
