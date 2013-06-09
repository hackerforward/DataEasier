#ifndef _LOG_H
#define _LOG_H
#include<cstdio>
class LOG
{
public:
	//static bool verbose;
	static void DERRLOG(const char * message,char * file,int linenum)
	{
		fprintf(stderr,"[%s:%d ERROR]--%s\n",message,file,linenum);
	}
	
	static void ERRLOG(const char * message)
	{
		fprintf(stderr,"[%s:%d ERROR]--%s\n",message);
	}
	
	static void DINFOLOG(const char * message,char * file,int linenum)
	{
	//	if(verbose)
			fprintf(stdout,"[%s:%d INFO]--%s\n",message,file,linenum);
	}
	
	static void INFOLOG(const char * message)
	{
	//	if(verbose)
			fprintf(stdout,"[%s:%d INFO]--%s\n",message);
	}
};
#endif
