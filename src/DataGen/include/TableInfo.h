#ifndef _DATATYPE_H
#define _DATATYPE_H


#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;

enum DATATYPE
{
	INTEGER=0,
	LONG=1,
	DATE=2,
	FLOAT=3,
	DOUBLE=4,
	STRING=5,
	SEQUENCE=6,
	PHONENUM=7,
	IPADDRESS=8,
	ARRAYINT=9,
	ARRAYLONG=10,
	ARRAYSTRING=11,
	CHSTRING=12,
	ENSTRING=13
};



class TableFileInfo
{
public:
	string tableName;
	vector<string> colName;
	vector<int> colDataType;
	vector<int> fieldLen;

public:
	TableFileInfo(){}

	TableFileInfo(string itableName)
	{
		tableName=itableName;
	}

	~TableFileInfo()
	{
		colName.clear();
		colDataType.clear();
		fieldLen.clear();
	}
	void setTableName(string &table)
	{
		tableName=table;
	}
	void addColInfo(string &icolName,int idataType,
			int ifieldLen)
	{
		colName.push_back(icolName);
		colDataType.push_back(idataType);
		fieldLen.push_back(ifieldLen);
	}

	string getTableName()
	{
		return tableName;
	}

	int getColNum()
	{
		return colName.size();
	}

	string getColName(int curPos)
	{
		return colName[curPos];
	}

	int getDataType(int curPos)
	{
		return colDataType[curPos];
	}
	int getFieldLen(int curPos)
	{
		return fieldLen[curPos];
	}
};

#endif
