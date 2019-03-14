/************************************************************************
GAtoolkit.h
日期:    12/3/2019
作者:	张清周
邮箱:	wdswater@gmail.com
单位:    浙江大学建筑工程学院
功能:    声明GA优化算法dll文件结构体变量及函数指针类型
*************************************************************************/

#ifndef GATOOLKIT_H
#define GATOOLKIT_H

#include <stdio.h>

typedef struct GA_Problem_t *GA_Problem;
typedef struct GA_Solution_t *GA_Solution;
typedef struct GA_Operator_t *GA_Operator;
typedef struct GA_Population_t *GA_Population;
typedef struct GA_Entry_t *GA_Entry;
typedef struct GA_Archive_t *GA_Archive;
typedef struct GA_Algorithm_t *GA_Algorithm;

typedef enum GA_Restart {
	RESTART_DEFAULT = 0,
	RESTART_RANDOM = 1,
	RESTART_RAMPED = 2,
	RESTART_ADAPTIVE = 3,
	RESTART_INVERTED = 4
} GA_Restart;

typedef enum GA_Probabilities {
	PROBABILITIES_DEFAULT = 0,
	PROBABILITIES_RECENCY = 1,
	PROBABILITIES_BOTH = 2,
	PROBABILITIES_ADAPTIVE = 3
} GA_Probabilities;

struct GA_Problem_t {
	int numberOfVariables;
	int numberOfObjectives;
	int numberOfConstraints;
	double* lowerBounds;
	double* upperBounds;
	double* epsilons;
	const char** names;
	void(*function)(double*, double*, double*);
};


struct GA_Solution_t {
	GA_Problem problem;
	double* variables;
	double* objectives;
	double* constraints;
	int operatorIndex;
};

struct GA_Operator_t {
	const char* name;
	int numberOfParents;
	int numberOfOffspring;
	int numberOfParameters;
	double selectionProbability;
	double* parameters;
	void(*function)(GA_Operator, GA_Solution*, GA_Solution*);
	GA_Operator mutation;
};

struct GA_Population_t {
	int size;
	int capacity;
	GA_Solution* members;
};

struct GA_Entry_t {
	GA_Solution solution;
	GA_Entry next;
	GA_Entry prev;
	GA_Archive archive;
};

struct GA_Archive_t {
	int size;
	GA_Entry head;
	GA_Entry tail;
	int numberOfImprovements;
	int* recencyList;
	int recencyListSize;
	int recencyListPosition;
};

struct GA_Algorithm_t {
	GA_Problem problem;
	int numberOfEvaluations;
	int numberOfOperators;
	int tournamentSize;
	int windowSize;
	int maximumWindowSize;
	int initialPopulationSize;
	int minimumPopulationSize;
	int maximumPopulationSize;
	double populationRatio;
	double selectionRatio;
	int evaluationsAtLastCheck;
	int evaluationsAtLastRestart;
	int updateInterval;
	int operationsSinceLastUpdate;
	int improvementsAtLastCheck;
	GA_Operator* operators;
	GA_Population population;
	GA_Archive archive;
	GA_Restart restartMode;
	int restartedLastCheck;
	int baseMutationIndex;
	int maxMutationIndex;
	GA_Probabilities probabilityMode;
	int numberOfRestarts;
};

#endif
