#ifndef _BUILD_H
#define _BUILD_H

#include<vector>
#include<set>
#include<string>
#include<map>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include"Log.h"

#define FIELD_SEP "|"
#define ARR_SEP "$"
#define PR_FD(fp,str) {fprintf(fp,"%s%s",str,FIELD_SEP);}
#define PR_END(fp) {fseek(fp, -1, SEEK_CUR);fprintf(fp,"\n");}

using namespace std;


class Build
{
private:
	vector<string> chwordVec;
	vector<string> enwordVec;
	set<string> uniqChword;
	set<string> uniqEnword;
	set<string> uniqPhoneNum;
	set<string> uniqDate;
	vector<string> phonenumHead;
	long long seed;
	long long fiSeedA;
	long long fiSeedB;
	long long maxRowNum;
	long long gen_nextid();
	long long seq;
public:
	Build(string datapath,long long maxRowNum,long long seed);
	~Build();
	string gen_ChSentence(int length);
	string gen_EnSentence(int length);
	string gen_PhoneNum();
	string gen_ShortDate();
	string gen_LongDate();
	string gen_Sequence();
	string gen_IpV4Address();
	string gen_Int();
	string gen_Long();
	string gen_Float();
	string gen_Double();

	string gen_INTArray(int length);
};

#endif
