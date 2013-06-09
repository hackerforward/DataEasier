#include "include/build.h"


Build::Build(string data,long long maxRowNum,long long seed)
{
	seed=seed;
	string datapath=data;
	maxRowNum=maxRowNum;
	fiSeedA=maxRowNum*seed%521;
	fiSeedB=fiSeedA+1;
	seq=1L;
	phonenumHead.push_back("130");
	phonenumHead.push_back("131");
	phonenumHead.push_back("132");
	phonenumHead.push_back("133");
	phonenumHead.push_back("134");
	phonenumHead.push_back("135");
	phonenumHead.push_back("136");
	phonenumHead.push_back("137");
	phonenumHead.push_back("138");
	phonenumHead.push_back("139");
	phonenumHead.push_back("150");
	phonenumHead.push_back("151");
	phonenumHead.push_back("152");
	phonenumHead.push_back("159");
	phonenumHead.push_back("180");
	phonenumHead.push_back("182");
	phonenumHead.push_back("186");

	ifstream fin;
	fin.open((datapath+"/uniqKeyword").c_str());
	if(!fin.is_open())
	{
		LOG::ERRLOG("Opne file uniqKeyword failed");
		//exit(0);
	}
	else
	{
		string tmpline;
		while(getline(fin,tmpline))
		{
			uniqChword.insert(tmpline);
		}
		fin.close();
	}

	fin.open((datapath+"/uniqEnkeyword").c_str());
	if(!fin.is_open())
	{
		LOG::DERRLOG("Opne file uniqEnkeyword failed",__FILE__,__LINE__);
		//exit(0);
	}
	else
	{
		string tmpline;
		while(getline(fin,tmpline))
		{
			uniqEnword.insert(tmpline);
		}
		fin.close();
	}

	fin.open((datapath+"/uniqPhonenum").c_str());
	if(!fin.is_open())
	{
		LOG::DERRLOG("Opne file uniqPhonenum failed",__FILE__,__LINE__);
		//exit(0);
	}
	else
	{
		string tmpline;
		while(getline(fin,tmpline))
		{
			uniqPhoneNum.insert(tmpline);
		}
		fin.close();
	}

	fin.open((datapath+"/uniqDate").c_str());
	if(!fin.is_open())
	{
		LOG::DERRLOG("Opne file uniqDate failed",__FILE__,__LINE__);
		//exit(0);
	}
	else
	{
		string tmpline;
		while(getline(fin,tmpline))
		{
			uniqDate.insert(tmpline);
		}
		fin.close();
	}

	for(int i=0;i<10;++i)
	{
		char tchar[10];
		sprintf(tchar,"%d",i);
		string filename="keywordseg.";
		filename+=tchar;
		fin.open((datapath+"/"+filename).c_str());
		if(!fin.is_open())
		{	
			LOG::DERRLOG(("Opne file "+filename+" failed").c_str(),__FILE__,__LINE__);
			//exit(0);
		}
		else
		{
			string tmpline;
			while(getline(fin,tmpline))
			{
				chwordVec.push_back(tmpline);
			}
			fin.close();
		}
	}

	fin.open((datapath+"/vocabulary").c_str());
	if(!fin.is_open())
	{
		LOG::DERRLOG("Opne file vocabulary failed",__FILE__,__LINE__);
		//exit(0);
	}
	else
	{
		string tmpline;
		while(getline(fin,tmpline))
		{
			enwordVec.push_back(tmpline);
		}
		fin.close();
	}
}
Build::~Build()
{
	for(int i=0;i<chwordVec.size();++i)
	{
		chwordVec[i].clear();
	}
	chwordVec.clear();

	for(int i=0;i<enwordVec.size();++i)
	{
		enwordVec[i].clear();
	}
	enwordVec.clear();

	uniqChword.clear();
	uniqEnword.clear();
	uniqPhoneNum.clear();
	uniqDate.clear();
}

long long Build::gen_nextid()
{
	long long ret=(fiSeedA+fiSeedB)%maxRowNum;
	fiSeedA=fiSeedB;
	fiSeedB=ret;
	return ret; 
}

string Build::gen_ChSentence(int length)
{
	string ret="";
	int cur=gen_nextid()%chwordVec.size();
	while(ret.size()+chwordVec[cur].size()<length)
	{
		ret+=chwordVec[cur];
		cur=gen_nextid()%chwordVec.size();
	}
	return ret;
}

string Build::gen_EnSentence(int length)
{
	string ret="";
	int cur=gen_nextid()%enwordVec.size();
	while(ret.size()+enwordVec[cur].size()<length-1)
	{
		ret+=enwordVec[cur];
		ret+=" ";
		cur=gen_nextid()%enwordVec.size();
	}
	return ret;
}

string Build::gen_PhoneNum()
{
	long long id=gen_nextid();
	char tmp[20];
	sprintf(tmp,"%ld",id*13579%100000000);
	string ret=tmp;
	return phonenumHead[id%phonenumHead.size()]+ret;
}

string Build::gen_IpV4Address()
{
	long long id=gen_nextid();
	char arr[4][5];
	sprintf(arr[0],"%ld",id*2357%256);
	sprintf(arr[1],"%ld",id*3579%256);
	sprintf(arr[2],"%ld",id*5791%256);
	sprintf(arr[3],"%ld",id*7913%256);
	string ret="";
	return ret+arr[0]+"."+arr[1]+"."+arr[2]+"."+arr[3];
}

string Build::gen_Sequence()
{
	char arr[15];
	string ret="";
	sprintf(arr,"%ld",seq++);
	return ret+arr;
}

string Build::gen_LongDate()
{

	char arr[10];
	long long id=gen_nextid();
	string ret="";
	int year=2004+id%10;
	sprintf(arr,"%d",year);
	ret+=arr;
	ret+="-";

	int monh=id/10%2;
	int mont=monh>0?id%9+1:id/100%3;
	sprintf(arr,"%d",monh);
	ret+=arr;
	sprintf(arr,"%d",mont);
	ret+=arr;
	ret+="-";

	int dayh=id%1000%3;
	sprintf(arr,"%d",dayh);
	ret+=arr;
	int dayt=id%8+2;
	sprintf(arr,"%d",dayt);
	ret+=arr;
	ret+=" ";

	int hour=id%24;
	int min=id%57;
	int sec=id/17%60;

	if(hour<10)
		ret+="0";
	sprintf(arr,"%d",hour);
	ret+=arr;
	ret+=":";

	if(min<10)
		ret+="0";
	sprintf(arr,"%d",min);
	ret+=arr;
	ret+=":";

	if(sec<10)
		ret+="0";
	sprintf(arr,"%d",sec);
	ret+=arr;

	return ret;
}

string Build::gen_INTArray(int length)
{
	string ret="";
	char arr[20];
	for(int i=0;i<length-1;++i)
	{
		sprintf(arr,"%d",(int)(gen_nextid()%2147483647));
		ret+=arr;
		ret+=ARR_SEP;
	}

	sprintf(arr,"%d",(int)(gen_nextid()%2147483647));
	ret+=arr;
	return ret;
}

string Build::gen_Int()
{
	char arr[20];
	sprintf(arr,"%d",(int)(gen_nextid()%2147483647));
	string ret=arr;
	return ret;
}

string Build::gen_Long()
{
	char arr[20];
	sprintf(arr,"%ld",gen_nextid());
	string ret=arr;
	return ret;
}
string Build::gen_Float()
{
	return "0.9";
}
string Build::gen_Double()
{
	return "12.03";
}
