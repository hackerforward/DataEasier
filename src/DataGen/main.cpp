#include"include/Log.h"
#include"include/build.h"
#include"include/TableInfo.h"
#include<map>
#include<set>
#include<vector>
#include<string>

using namespace std;
string useage="";
//useage="./DataGen <-c metadatafile> [options]\n"+\
"\t\t-c metadatafile: metadata of table\n"+\
"\t\t-s num: rownum of generated data file,valid value is 1,10,100,1000,\n"+\
"\t\t\t\t10000,100000  real row is num*10000, default value 1\n"+\
"\t\t-S seed: seed default value 1"+\
"\t\t-p part: number of partion,range from 1 to 10,default value 1\n";

int rownum=10000;
int seed=1;
int part=1;

int getDataType(string dataTypeStr);
void parseMeta(TableFileInfo *tbi,string fin);
int getFieldLen(string tmp);
string gen(Build build,int len,int datatype);
vector<string> split(string& str,const char c);
int main(int argc,char ** argv)
{
	if(argc < 0)
	{
		LOG::ERRLOG(useage.c_str());
		return 0;
	}

	string metadatafile="./juntable";
	ifstream fin;
	fin.open(metadatafile.c_str());
	if(!fin.is_open())
	{
		LOG::ERRLOG(("open "+metadatafile+" failed").c_str());
		return 0;
	}
	TableFileInfo *tbi=new TableFileInfo();
	parseMeta(tbi,metadatafile);

	string datapath="../../Data";
	Build build(datapath,rownum,seed);
	//ofstream fout;
	string dataFileName=tbi->getTableName()+".tbl";
	FILE*fout;
	fout=fopen(dataFileName.c_str(),"w");
	if(fout==NULL)
	{
		LOG::ERRLOG(("open "+metadatafile+" failed").c_str());
		exit(0);
	}
	
	for(int i=0;i<rownum;++i)
	{
		for(int j=0;j<tbi->getColNum();++j)
		{
			string st=gen(build,tbi->getFieldLen(j),tbi->getDataType(j));
			PR_FD(fout,st.c_str());
		}
		PR_END(fout);
	}
	
	fclose(fout);
	LOG::INFOLOG("Generating complete!!!");
	return 0;
}
string gen(Build build,int len,int datatype)
{
	string ret="";
	switch(datatype)
	{
		case INTEGER:
			ret=build.gen_Int();
			break;
		case LONG:
			ret=build.gen_Long();
			break;
		case DATE:
			ret=build.gen_LongDate();
			break;
		case FLOAT:
			ret=build.gen_Float();
			break;
		case DOUBLE:
			ret=build.gen_Double();
		case STRING:
		case ENSTRING:
			ret=build.gen_EnSentence(len);
			break;
		case CHSTRING:
			ret=build.gen_ChSentence(len);
			break;
		case SEQUENCE:
			ret=build.gen_Sequence();
			break;
		case PHONENUM:
			ret=build.gen_PhoneNum();
			break;
		case IPADDRESS:
			ret=build.gen_IpV4Address();
			break;
		case ARRAYINT:

		case ARRAYLONG:

		case ARRAYSTRING:
			ret=build.gen_INTArray(len);
		default:
			break;
	}
	return ret;
}
void parseMeta(TableFileInfo *tfi,string metadatafile)
{
	
	ifstream fin;
	fin.open(metadatafile.c_str());
	string tmpstr;
	vector<string> tmpvec;
	string colName;
	int dataType;
	int fieldLen;
	while(getline(fin,tmpstr))
	{
		if(tmpstr==""||tmpstr.find("##")==0||
			tmpstr.find("(")==0||tmpstr.find(")")==0)
			continue;
		tmpvec=split(tmpstr,' ');
		tfi->setTableName(tmpvec[1]);
		while(getline(fin,tmpstr))
		{
			if(tmpstr==""||tmpstr.find("##")==0||
				tmpstr.find("(")==0||tmpstr.find(")")==0)
				continue;
			tmpvec.clear();
			tmpvec=split(tmpstr,' ');
			colName=tmpvec[0];
			dataType=getDataType(tmpvec[1]);
			if(dataType<0)
			{
				LOG::ERRLOG(("Unknow data type"+tmpvec[1]).c_str());
				exit(0);
			}
			fieldLen=getFieldLen(tmpvec[1]);
			tfi->addColInfo(colName,dataType,fieldLen);
		}
	}
	tmpvec.clear();
	fin.close();
}

int getFieldLen(string tmp)
{
	int is=tmp.find("(");
	int ie=tmp.find(")");
	return is>=0?atoi(tmp.substr(is+1,ie).c_str()):0;
}
vector<string> split(string& str,const char c)
{
    char *cstr, *p;
    vector<string> res;
    cstr = new char[str.size()+1];
    strcpy(cstr,str.c_str());
    p = strtok(cstr,&c);
    while(p!=NULL)
    {
        res.push_back(p);
        p = strtok(NULL,&c);
    }
    return res;
}

int getDataType(string dataTypeStr)
{
	if (dataTypeStr.find("ENSTRING")!=string::npos)
		return ENSTRING;
	else if(dataTypeStr.find("CHSTRING")!=string::npos)
		return CHSTRING;
	else if(dataTypeStr.find("ARRAYSTRING")!=string::npos)
		return ARRAYSTRING;
	else if(dataTypeStr.find("ARRAYLONG")!=string::npos)
		return ARRAYLONG;
	else if(dataTypeStr.find("ARRAYINT")!=string::npos)
		return ARRAYINT;
	else if(dataTypeStr.find("IPADDRESS")!=string::npos)
		return IPADDRESS;
	else if(dataTypeStr.find("PHONENUM")!=string::npos)
		return PHONENUM;
	else if(dataTypeStr.find("SEQUENCE")!=string::npos)
		return SEQUENCE;
	else if(dataTypeStr.find("CHAR")!=string::npos||
			dataTypeStr.find("STRING")!=string::npos)
		return STRING; 
	else if(dataTypeStr.find("DECIMAL")!=string::npos||
			dataTypeStr.find("DOUBLE")!=string::npos)
		return DOUBLE; 
	else if(dataTypeStr.find("FLOAT")!=string::npos)
		return FLOAT;
	else if(dataTypeStr.find("DATE")!=string::npos)
		return DATE; 
	else if(dataTypeStr.find("LONG")!=string::npos)
		return LONG;
	else if(dataTypeStr.find("INTEGER")!=string::npos)
		return INTEGER; 
	else
		return -1;
}
