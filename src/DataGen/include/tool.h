#ifndef _TOOL_H
#define _TOOL_H
#include<stdlib.h>
#include<stdio.h>


int atoi (char s[])
{
	int i,n,sign;
	for(i=0;isspace(s[i]);i++);
		
	sign=(s[i]=='-')?-1:1;

	if(s[i]=='+'||s[i]=='-')
 		i++;
 	for(n=0;isdigit(s[i]);i++)
       n=10*n+(s[i]-'0');

	return sign *n;
}

char * itoa(int val)
{
	char *temp=(char *)malloc(20);
	sprintf(temp,"%d",val);
	return temp;
}

char * ltoa(long long val)
{
	char *temp=(char *)malloc(30);
	sprintf(temp,"%ld",val);
	return temp;
}
#endif
