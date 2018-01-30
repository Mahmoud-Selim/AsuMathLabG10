/*
 * AdvOp.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: mohamed
 */
#include<string>
#include"string.h"
#include<iostream>
#include <stdlib.h>
#include "AdvNumbers.h"
#include<stdio.h>
#include<math.h>
#include "Mystring.h"
using namespace std;
//using namespace numbers ;
static int y=0;
string Adoperation1Num(string s)
{
	bool semiColonFlag = s[s.length() - 1] == ';' ? 1 : 0;
	int equalPos;string newString;int newstrPos;
	s = AdoperationNum(s);
	equalPos=s.find("=");
	if(equalPos!=-1)
	{
		newstrPos=s.length()-equalPos;
		newString=s.substr(equalPos+1,newstrPos);
		newString = trimm(newString);
		newString=	TokenNum(newString);
		s.replace(equalPos+1,newstrPos,newString);
	}
	else
	{
		s=TokenNum(s);
	}
	if(semiColonFlag)
		startOperation(s+';');
	else
	startOperation(s);
	return s ;
}
string AdoperationNum(string s)
{
	int TrigPos;string Trig;char text[50];double trigValue;int flagTrig=0;
	unsigned long i,j, oneBrace = 0, flag = 0, firstBracePosition;
	string manipulatedString = s;
	unsigned long sLength = s.length();
	for (i = 0; i < sLength; i++)
	{
		if(s[i] == '(')
		{
			oneBrace++;
			if(flag == 0)
				firstBracePosition = i;
			flag = 1;
		}
		if(s[i] == ')'&&flag==1)
			oneBrace--;
		if(oneBrace == 0 && flag == 1)
		{
			string subString = s.substr(firstBracePosition + 1, i - firstBracePosition - 1);
			if(subString.find('(') != size_t(-1))
			{
				string buffer = AdoperationNum(subString);
				int bufferPos=s.find(subString);
				s.replace(bufferPos,subString.length(),buffer);
			}
			else
			{
				subString = TokenNum(subString);
				s.replace(firstBracePosition, i - firstBracePosition + 1, subString);
				TrigPos=s.find(subString);
				if(s[TrigPos-3]>='a'&& s[TrigPos-3]<='z')
					{
						Trig=s.substr(TrigPos-3,3);
						if((Trig=="sin")||(Trig=="cos")||(Trig=="tan")||(Trig=="qrt")||(Trig=="log")||(Trig=="sec")||(Trig=="csc")||(Trig=="cot"));
							{
								flagTrig=0;
								char* buffer = new char[subString.length() + 1];
								strcpy(buffer, subString.c_str());
								buffer=trim(buffer);
								trigValue=atof(buffer);
								if(Trig=="sin")
									{
										trigValue=sin(trigValue);
									}
								else if (Trig =="cos")
									{
										trigValue=cos(trigValue);
									}
								else if (Trig == "tan")
									{
										trigValue=tan(trigValue);
									}
								else if(Trig=="log")
									{
										trigValue=log(trigValue);
									}

								else if (Trig=="qrt")
									{
										trigValue= sqrt(trigValue);
										flagTrig=1;
									}
								else if (Trig=="sec")
									{
										trigValue= 1/cos(trigValue);
									}
								else if (Trig=="csc")
									{
										trigValue = 1 /sin(trigValue);
									}
								else if (Trig=="cot")
									{
										trigValue =1/tan(trigValue);
									}
								if(flagTrig==0)
									{
										sprintf(text,"%lf",trigValue);
										s.replace(TrigPos-3,subString.length()+3,text);
									}
								else
									{
										sprintf(text,"%lf",trigValue);
										s.replace(TrigPos-4,subString.length()+4,text);
									}
							}
					}
			}
			sLength = s.length();
			i = 0;
			flag = 0;
		}
	}
	return s;
}


	string trimm(string  text)
	{
	int i =0;
	while(i<text.size())
	{


		if(text[i] == '(' || text[i] == ')')
		{
		    text.erase(i,1);
		}
		else
		{
		i++;
		}
	}
	return text ;
	}

	char* trim(char* text)
	{
		char* p = text + strlen(text) - 1;//pointing pointer to the end of the string
		while (*p == ' ' || *p == '\t' || *p == '\r' ||*p == '(' || *p == ')')
		{
			*p-- = '\0';
		}
		p = text; //pointing pointer to the start of the string
		while (*p == ' ' || *p == '\t' || *p == '\r' ||*p == '(' || *p == ')')
		{
			p++;
		}

		return p;
	}
	string TokenNum(string s)
	{
		int Mul ,Div,Add,Sub,pow;
	do
	{

		pow=s.find('^');
		Mul=s.find("*");
		Div=s.find("/");
		Add=s.find("+");
		Sub=s.find("-");

		if(pow!=-1)
		{
		s=powerNum(s);
		}

		if((Mul<Div||(Div==-1))&&(Mul!=-1))
		{
			s=MullNum(s);
		}
		else if((Div<Mul||Mul==-1)&&(Div!=-1))
		{
			s=DivvNum(s);

		}
		if(Mul==-1&&Div==-1)
			{

				if((Add<Sub||Sub==-1)&&(Add!=-1))
					{
						s=AdddNum(s);

					}
				else if((Sub<Add||Add==-1)&&Sub!=-1)
					{
						s=subbNum(s);
					}
			}
		if(Sub==0&&Mul==-1&&Div==-1&&Add==-1&&pow==-1) break;
	}
	while((Mul!=-1)||(Div!=-1)||(Add!=-1)||((Sub!=-1))||(pow!=-1));
		return s ;
	}
string powerNum(string s)
	{
			int x=0;
			int j = 0;
			int len ,pos6;
			double value2;
			char text[100];
			char* buffer2 = new char[s.length() + 1];
			strcpy(buffer2, s.c_str());
			char* separators2 = "+*-/";
			char* lineContext2;
			char* token2 = strtok_r(buffer2, separators2, &lineContext2);
				while (token2)
					{
						x=0;
						while (token2[j] != '\0')
							{
								if (token2[j] == '^')
									{
										char * trimmed2 = trim(token2);
										string str2 = token2;
										len = str2.length();
										pos6 = s.find(token2);
										value2 = pow_string(trimmed2);
										sprintf(text, "%lf", value2);
										s.replace(pos6, len, text);
										j = 0;
										break;
									}
								j++;
							}
							j=0;
							token2 = strtok_r(NULL, separators2,&lineContext2);
					}
			return s ;
		}

string DivvNum(string s)
	{
		int x=0;
		int j = 0;
		int len ,pos6;
		double value2;
		char text[100];
		char* buffer2 = new char[s.length() + 1];
		strcpy(buffer2, s.c_str());
		char* separators2 = "+*-";
		char* lineContext2;
		char* token2 = strtok_r(buffer2, separators2, &lineContext2);
			while (token2)
				{
					x=0;
					while (token2[j] != '\0')
						{
							if (token2[j] == '/')
								{
									char * trimmed2 = trim(token2);
									string str2 = token2;
									len = str2.length();
									pos6 = s.find(token2);
									value2 = Div_string(trimmed2);
									sprintf(text, "%lf", value2);
									s.replace(pos6, len, text);
									j = 0;
									x=1;
									break;
								}

							if(x==1)break;
							j++;
						}
						j=0;
						if(x==1)break;
						token2 = strtok_r(NULL, separators2,&lineContext2);
				}
		return s ;
	}
	string  MullNum(string s)
	{
		int len,pos6;
		double value;
		char text[100];
		int i = 0;
		char* buffer = new char[s.length() + 1];
		strcpy(buffer, s.c_str());
		char* separators1 = "/+-";
		char* lineContext;
		char* token1 = strtok_r(buffer, separators1,&lineContext);
		int x=0;
			while (token1)
				{
				x=0;
					while (token1[i] != '\0')
						{
							if (token1[i] == '*')
								{
									int SinPos;
									char * trimmed = trim(token1);
									string str1 = token1;
									len = str1.length();
									pos6 =s.find(token1);
									value =  Mul_string(trimmed);
									sprintf(text, "%lf", value);
									s.replace(pos6, len, text);
									i = 0;
									x=1;
									break;
								}
							i++;
							if(x==1)break;
						}
					i=0;
					if(x==1)break;
					token1 = strtok_r(NULL, separators1,&lineContext);
				}
		return s ;
	}
	string  AdddNum(string s)
	{
		int sub = s.find("-");
		if(sub==0)y=1;
		int len,pos6;
		double value;
		char text[100];
		int i = 0;
		char* buffer = new char[s.length() + 1];
		strcpy(buffer, s.c_str());
		char* separators1 = "/*-";
		char* lineContext;
		char* token1 = strtok_r(buffer, separators1,&lineContext);
		int x=0;
			while (token1)
				{
				x=0;
					while (token1[i] != '\0')
						{
							if (token1[i] == '+')
								{
									char * trimmed = trim(token1);
									string str1 = token1;
									len = str1.length();
									pos6 =s.find(token1);
									value = Add_string(trimmed);
									sprintf(text, "%lf", value);
									s.replace(pos6, len, text);
									if(y==1)
									{
										y=0;
										s[0]=' ';
									}
									i = 0;
									x=1;
									break;
								}
							if(x==1)break;
							i++;
						}
					i=0;
					y=0;
					if(x==1)break;
					token1 = strtok_r(NULL, separators1,&lineContext);
				}
		return s ;
	}
	string  subbNum(string s)
	{
			string oldval=s;
			int len,pos6;
			double value;
			char text[100];
			int i = 0;
			char* buffer = new char[s.length() + 1];
			strcpy(buffer, s.c_str());
			char* separators1 = "/+*";
			char* lineContext;
			char* token1 = strtok_r(buffer, separators1,&lineContext);
			int x=0;
				while (token1)
					{
					x=0;
						while (token1[i] != '\0')
							{
								if (token1[i] == '-')
									{
										char * trimmed = trim(token1);
										string str1 = token1;
										len = str1.length();
										pos6 =s.find(token1);
										value = Sub_string(trimmed);
										sprintf(text, "%lf", value);
										s.replace(pos6, len, text);
										i = 0;
										x=1;
										break;
									}
								if(x==1)break;
								i++;
							}
						i=0;
						if(x==1)break;
						token1 = strtok_r(NULL, separators1,&lineContext);
					}
				if(s==oldval) s=AdddNum(s);
			return s ;
	}
	double Mul_string(char * s)
	{
		double value = 1;
		char* spearators = "*";
		char * line3 ;
		char* token = strtok_r(s, spearators,&line3);
		value *= atof(token);
		while (token)
		{
			token = strtok_r(NULL, spearators,&line3);
			if (token)
			{
				value *= atof(token);
			}
		}
		return value;
	}
	double Div_string(char * s)
	{
		double value = 1;
		char* spearators = "/";
		char *line;
		char* token = strtok_r(s, spearators,&line);
		value= atof(token);
		while (token)
		{
			token = strtok_r(NULL, spearators,&line);
			if (token)
			{
				if(atof(token) == 0)
					throw("Can't divide by zero");
				value =value/ atof(token);
			}
		}
		return value;
	}
	double Add_string(char * s)
	{
			double value = 0;
			int i = 0;
			char *line1 ;
			char* spearators = "+";
			char* token = strtok_r(s, spearators,&line1);
			value = atof(token);
			while (token)
			{
				token = strtok_r(NULL, spearators,&line1);
				if (token)
				{
					if(y==1)
							{
								value = -value + atof(token);
							}
					else
					value = value + atof(token);
				}
			}
			return value;
	}
	double Sub_string(char * s)
	{
			double value = 1;
			int i = 0;
			if (s[i] == '-') value = -1;
			char* spearators = "-";
			char *line2;
			char* token = strtok_r(s, spearators,&line2);
			value *= atof(token);
			while (token)
			{
				token = strtok_r(NULL, spearators,&line2);
				if (token)
				{
					value = value - atof(token);
				}
			}
			return value;
	}
	double pow_string(char * s)
	{
		double value = 1;
				char* spearators = "^";
				char *line;
				char* token = strtok_r(s, spearators,&line);
				value =(double) atof(token);
				while (token)
				{
					token = strtok_r(NULL, spearators,&line);
					if (token)
					{
						value =pow(value, atof(token));
					}
				}
				return value;
	}

