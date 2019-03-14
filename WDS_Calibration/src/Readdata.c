/************************************************************************
Readdata.c
����:    9/3/2019
����:	������
����:	wdswater@gmail.com
��λ:    �㽭��ѧ��������ѧԺ
����:    ��ȡdata.txt�ļ�����
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h> 

#define EXTERN extern
#include "General.h"

char *Tok[MAXTOKS]; /* �洢ÿ���ֶ��ַ�ָ�� */
int Presensor_count; /* ѹ��������� */
int Flowsensor_count; /* ����������� */
int Demandnode_count; /* ��ˮ���ڵ���� */

/* data.txt�ֽڱ�־ */
char *SectTxt[] = {
	"[Pressure_sensor]",
	"[Flow_sensor]",
	"[Demand_node]",
	NULL
};

/* data.txt�ֽڱ�־ö�ٱ��� */
enum SectType {
	_Pressure_sensor,
	_Flow_sensor,
	_Demand_node,
	_END
};

FILE* openfile(char *f1)
/*----------------------------------------------------------------
**  ����: f1 = �ļ�ָ��
**  ���: ��
**  ����: ��
**  ����: �������ļ�
**----------------------------------------------------------------*/
{
	FILE* DataFile = fopen(f1, "r");
	Validate_file(DataFile);

	return DataFile;
}

int match(char *str, char *substr)
/*--------------------------------------------------------------
**  ����: *str    = string being searched
**       *substr = substring being searched for
**  ���: returns 1 if substr found in str, 0 if not
**  ����: sees if substr matches any part of str
**--------------------------------------------------------------*/
{
	Validate_pointer(str);
	Validate_pointer(substr);
	
	int i, j;
	int Length_str = 0;
	int Length_substr = 0;
	int Length_blanks = 0;

	/* Fail if substring is empty */
	if (!substr[0]) return(0);

	/* Skip leading blanks of str. */
	for (i = 0; str[i]; i++)
	{
		if (str[i] != ' ')
		{
			Length_blanks = i;
			break;
		}
	}

	Length_str = (int)strlen(str) - Length_blanks;
	Length_substr = (int)strlen(substr);

	if (Length_str != Length_substr)
		return 0;
	else
	{
		/* Check if substr matches remainder of str. */
		for (i = i, j = 0; substr[j]; i++, j++)
			if (!str[i] || UCHAR(str[i]) != UCHAR(substr[j]))
				return(0);
	}
	return(1);
}

int  findmatch_keyword(char *line, char *keyword[])
/**--------------------------------------------------------------
**  ����: *line  = line from input file
**       *keyword[] = list of NULL terminated keywords
**  ���: returns index of matching keyword or -1 if no match found
**  ����: determines which keyword appears on input line
**--------------------------------------------------------------*/
{
	Validate_pointer(line);
	Validate_pointer(keyword);

	int i = 0;
	while (keyword[i] != NULL)
	{
		if (match(line, keyword[i])) return(i);
		i++;
	}
	return(-1);
}

void Get_count(FILE* DataFile, int *Npresensors, int *Nflowsensors, int *Ndemandnodes)
/**--------------------------------------------------------------
**  ����: ��
**  ���: �������
**  ����: ��ȡ���㡢��ˮ���ڵ�����
**--------------------------------------------------------------*/
{
	Validate_file(DataFile);
	Validate_pointer(Npresensors);
	Validate_pointer(Ndemandnodes);
	
	char  line[MAXLINE + 1];    /* Line from input data.txt    */
	char  *tok;                 /* First token of line          */
	int   sect, newsect;        /* Input data sections          */

	/* Initialize component counts */
	int npresensors = 0;
	int nflowsensors = 0;
	int ndemandnodes = 0;
	sect = -1;

	/* Make pass through data file counting number of each component */
	while (fgets(line, MAXLINE, DataFile) != NULL)
	{
		/* Skip blank lines & those beginning with a comment */
		tok = strtok(line, SEPSTR);
		if (tok == NULL) continue;
		if (*tok == ';') continue;

		/* Check if line begins with a new section heading */
		if (*tok == '[')
		{
			newsect = findmatch_keyword(tok, SectTxt);
			if (newsect >= 0)
			{
				sect = newsect;
				if (sect == _END) break;
				continue;
			}
			else continue;
		}

		/* Add to count of current component */
		switch (sect)
		{
			case _Pressure_sensor:  npresensors++;    break;
			case _Flow_sensor:	nflowsensors++;	break;
			case _Demand_node: ndemandnodes++; break;
			default: break;
		}
	}
	*Npresensors = npresensors;
	*Nflowsensors = nflowsensors;
	*Ndemandnodes = ndemandnodes;
}

Pdata DatabaseInitial(FILE* DataFile)
/*----------------------------------------------------------------
**  Input:   data.txt �ļ�ָ��
**  Output:  ��
**  Purpose: ��ʼ���ṹ��TextData
**----------------------------------------------------------------*/
{
	Validate_file(DataFile);
	
	Pdata Textdata = (Pdata)calloc(1, sizeof(struct Data_));
	Validate_pointer(Textdata);

	Get_count(DataFile, &Textdata->NumOfPressureSensor, &Textdata->NumOfFlowSensor, &Textdata->NumOfDemandNode);

	if (Textdata->NumOfPressureSensor > 0)
	{
		Textdata->presensor = (Psensor)calloc(Textdata->NumOfPressureSensor, sizeof(struct Sensor_));
		Validate_pointer(Textdata->presensor);
	}

	if (Textdata->NumOfFlowSensor > 0)
	{
		Textdata->flowsensor = (Psensor)calloc(Textdata->NumOfFlowSensor, sizeof(struct Sensor_));
		Validate_pointer(Textdata->flowsensor);
	}

	Textdata->node = (Pcalielement)calloc(1, sizeof(struct Calielement_));
	if (Textdata->NumOfDemandNode > 0)
	{
		Textdata->node->ement = (Pelement)calloc(Textdata->NumOfDemandNode, sizeof(struct element_));
		Validate_pointer(Textdata->node->ement);
	}
		
	return Textdata;
}

void Textdata_destroy(Pdata Textdata)
/*----------------------------------------------------------------
**  ����: Textdata: data.txt���ݽṹ��ָ��;
**  ���: ��
**  ����: �ͷŽṹ��TextData�ڴ�
**----------------------------------------------------------------*/
{
	if (Textdata)
	{
		free(Textdata->presensor);
		free(Textdata->flowsensor);
		free(Textdata->node->ement);
		free(Textdata->node);
	}
	free(Textdata);
}

int  gettokens(char *s)
/*--------------------------------------------------------------
**  ����: *s = string to be tokenized
**  ���: returns number of tokens in s
**  ����: scans string for tokens, saving pointers to them
**       in module global variable Tok[]
**--------------------------------------------------------------*/
{
	Validate_pointer(s);
	int  len, m, n;
	char *c;

	/* Begin with no tokens */
	for (n = 0; n < MAXTOKS; n++) Tok[n] = NULL;
	n = 0;

	/* Truncate s at start of comment */
	c = strchr(s, ';');
	if (c) *c = '\0';
	len = (int)strlen(s);

	/* Scan s for tokens until nothing left */
	while (len > 0 && n < MAXTOKS)
	{
		m = (int)strcspn(s, SEPSTR);           /* Find token length */
		len -= m + 1;                     /* Update length of s */
		if (m == 0) s++;                  /* No token found */
		else
		{
			if (*s == '"')                /* Token begins with quote */
			{
				s++;                      /* Start token after quote */
				m = (int)strcspn(s, "\"\n\r"); /* Find end quote (or EOL) */
			}
			s[m] = '\0';                  /* Null-terminate the token */
			Tok[n] = s;                   /* Save pointer to token */
			n++;                          /* Update token count */
			s += m + 1;                   /* Begin next token */
		}
	}
	return(n);
}

int  getfloat(char *s, double *y)
/**-----------------------------------------------------------
**  ����: *s = character string
**  ���: *y = floating point number
**  ���أ�returns 1 if conversion successful, return error message if not
**  ����: converts string to floating point number
**-----------------------------------------------------------*/
{
	Validate_pointer(s);
	Validate_pointer(y);
	char *endptr;
	*y = (double)strtod(s, &endptr);
	if (*endptr > 0)
		Error("Unable to convert string to a floating number!\n");
	return(1);
}

void Presensor_data(Pdata Textdata,int num_toks)
/*--------------------------------------------------------------
**  Input:   Textdata = data.txt���ݽṹ��ָ��;
**			 num_toks = number of Toks
**  Output:  error code
**  Purpose: processes  pressure sensor data
**  Format:
**  [Pressure_sensor]
**  ID		Observed     value
**--------------------------------------------------------------*/
{
	double x;
	if (Textdata->NumOfPressureSensor > 0)
	{
		if (num_toks != 2)
			Error("TypeError in [Pressure_sensor]\n");
		strncpy(Textdata->presensor[Presensor_count].ID, Tok[0], MAXID);
		getfloat(Tok[1], &x);
		Textdata->presensor[Presensor_count].value = x;
		Presensor_count++;
	}
}

void Flowsensor_data(Pdata Textdata, int num_toks)
/*--------------------------------------------------------------
**  Input:   Textdata = data.txt���ݽṹ��ָ��;
**			 num_toks = number of Toks
**  Output:  none
**  Purpose: processes  flow sensor data
**  Format:
**  [Flow_sensor]
**  ID		Observed	  value
**--------------------------------------------------------------*/
{
	double x;
	if (Textdata->NumOfFlowSensor > 0)
	{
		if (num_toks != 2)
			Error("TypeError in [Flow_sensor]\n");
		strncpy(Textdata->flowsensor[Flowsensor_count].ID, Tok[0], MAXID);
		getfloat(Tok[1], &x);
		Textdata->flowsensor[Flowsensor_count].value = x;
		Flowsensor_count++;
	}
}

void Demandnode_data(Pdata Textdata, int num_toks)
/*--------------------------------------------------------------
**  Input:   Textdata = data.txt���ݽṹ��ָ��;
**			 num_toks = number of Toks
**  Output:  none
**  Purpose: processes  demand node data
**  Format:
**  [Demand_node]
**  ID		Initial_demand	    Group
**--------------------------------------------------------------*/
{
	double x;
	if (Textdata->NumOfDemandNode > 0)
	{
		if (num_toks != 3)
			Error("TypeError in [Flow_sensor]\n");
		
		strncpy(Textdata->node->ement[Demandnode_count].ID, Tok[0], MAXID);
		
		getfloat(Tok[1], &x);
		Textdata->node->ement[Demandnode_count].Inivalue = x;
		
		strncpy(Textdata->node->ement[Demandnode_count].groupID, Tok[2], MAXID);

		Demandnode_count++;
	}
}

void  newline(Pdata Textdata, int sect, char *line, int num_Toks)
/**--------------------------------------------------------------
**  Input:   Textdata = pointer to Textdata
**			 sect  = current section of input file
**           *line = line read from input file
**			 num_Toks = number of Toks
**  Output:  returns error code or 0 if no error found
**  Purpose: processes a new line of data from data.txt
**--------------------------------------------------------------*/
{
	switch (sect)
	{
	case _Pressure_sensor:  Presensor_data(Textdata,num_Toks); break;
	case _Flow_sensor:		Flowsensor_data(Textdata,num_Toks); break;
	case _Demand_node: Demandnode_data(Textdata,num_Toks); break;
	}
}

Pdata  readdata(char *f1)
/*----------------------------------------------------------------
**  Input:   f1 = pointer to name of data.txt
**  Output:  none
**  Returns: error code
**  Purpose: opens data file & reads parameter data
**----------------------------------------------------------------*/
{
	int  errcode = 0;
	char line[MAXLINE + 1],     /* Line from input data file       */
		wline[MAXLINE + 1];    /* Working copy of input line      */
	int  sect, newsect;         /* Data sections                   */
	int Ntokens = 0;
	Presensor_count = 0;
	Flowsensor_count = 0;
	Demandnode_count = 0;

	/* Open input & report files */
	FILE* DataFile = openfile(f1);

	/* Initialize */
	Pdata Textdata = DatabaseInitial(DataFile);

	rewind(DataFile);  //��ָ��ָ���ļ���ͷ

	while (fgets(line, MAXLINE, DataFile) != NULL)
	{
		/* Make copy of line and scan for tokens */
		strcpy(wline, line);
		Ntokens = gettokens(wline);

		/* Skip blank lines and comments */
		if (Ntokens == 0) continue;
		if (*Tok[0] == ';') continue;

		/* Check if at start of a new input section */
		if (*Tok[0] == '[')
		{
			newsect = findmatch_keyword(Tok[0], SectTxt);
			if (newsect >= 0)
			{
				sect = newsect;
				if (sect == _END) break;
				continue;
			}
		}

		/* Otherwise process next line of input in current section */
		else
			newline(Textdata, sect, line,Ntokens);
	}   /* End of while */
	fclose(DataFile);

	return Textdata;
}
