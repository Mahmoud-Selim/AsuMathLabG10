/*
 * rome7.cpp
 *
 *  Created on: Jan 22, 2018
 *      Author: mohamed
 */
#include<string>
#include"string.h"
#include<iostream>
#include <stdlib.h>
#include"AdvMatrices.h"
#include<stdio.h>
#include<math.h>

using namespace std;
static int NumMatrices =0 ;
static int y=0;
string AdOperation1Mat(string s)
{
	int equalPos;string newString;int newstrPos;
	s = AdoperationMat(s);
	equalPos=s.find("=");
		if(equalPos!=-1)
		{
			newstrPos=s.length()-equalPos;
			newString=s.substr(equalPos+1,newstrPos);
			newString = trimm(newString);
			newString=TokenMat(newString);
			s.replace(equalPos+1,newstrPos,newString);
		}
		else
		{
			s=TokenMat(s);
		}
		startOperation(s);
		return s ;
}

string AdoperationMat(string s)
{
	unsigned long i,j, oneBrace = 0, flag = 0, firstBracePosition;int TrigPos;string Trig;
	int sinPos=0,cosPos=0,tanPos=0,logPos=0,sqrtPos=0;char text[50];string hash;
	int logCounter=0,logFlag=1; //dol godad
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

				string buffer = AdoperationMat(subString);
				int bufferPos=s.find(subString);
				s.replace(bufferPos,subString.length(),buffer);
			}
			else
			{

				subString = TokenMat(subString);
				s.replace(firstBracePosition, i - firstBracePosition + 1, subString);
				for(int j = 0 ; j<s.length();j++)
					{
						sinPos=s.find("sin",sinPos);
						cosPos=s.find("cos",cosPos);
						tanPos=s.find("tan",tanPos);
						logPos=s.find("log",logPos);
						sqrtPos=s.find("sqrt",sqrtPos);
						if(logPos!=-1)//men awel hena gededa
							{
								logCounter=	logPos+3;
								while(logFlag==1)
									{
										if(isdigit(s[logCounter])==0)
										{
											logFlag=0;
											if(s[logCounter]=='(')
											{
												logFlag=1;
												break;
											}
											else
											{
												NumMatrices++;
												sprintf(text,"%d",NumMatrices);
												Trig="#"+string(text)+"="+"log"+s.substr(logPos+3,logCounter-(logPos+3))+"("+subString+")";
												startOperation(Trig);
												hash = "#"+string(text);
												s.replace(logPos,logCounter-logPos+subString.length(),hash);
												logFlag=1;
												break;
											}
										}
									logCounter++;
									}
							logPos++;
						} //le7ad hna
						if(s[sinPos+3]!='('&&sinPos!=-1)
							{
								NumMatrices++;
								sprintf(text,"%d",NumMatrices);
								Trig="#"+string(text)+"="+s.substr(sinPos,3)+"("+subString+")";
								startOperation(Trig);
								hash = "#"+string(text);
								s.replace(sinPos,subString.length()+3,hash);
								sinPos++;
							}
						else if(s[cosPos+3]!='('&&cosPos!=-1)
							{
								NumMatrices++;
								sprintf(text,"%d",NumMatrices);
								Trig="#"+string(text)+"="+s.substr(cosPos,3)+"("+subString+")";
								startOperation(Trig);
								hash = "#"+string(text);
								s.replace(cosPos,subString.length()+3,hash);
								cosPos++;
							}
						else if(s[tanPos+3]!='('&&tanPos!=-1)
							{
								NumMatrices++;
								sprintf(text,"%d",NumMatrices);
								Trig="#"+string(text)+"="+s.substr(tanPos,3)+"("+subString+")";
								startOperation(Trig);
								hash = "#"+string(text);
								s.replace(tanPos,subString.length()+3,hash);
								tanPos++;
							}
						/*else if(s[logPos+3]!='('&&logPos!=-1)
							{
								NumMatrices++;
								sprintf(text,"%d",NumMatrices);
								Trig="#"+string(text)+"="+s.substr(logPos,3)+"("+subString+")";
								startOperation(Trig);
								hash = "#"+string(text);
								s.replace(logPos,subString.length()+3,hash);
								logPos++;
							}*/
						else if(s[sqrtPos+4]!='('&&sqrtPos!=-1)
							{
								NumMatrices++;
								sprintf(text,"%d",NumMatrices);
								Trig="#"+string(text)+"="+s.substr(sqrtPos,4)+"("+subString+")";
								startOperation(Trig);
								hash = "#"+string(text);
								s.replace(sqrtPos,subString.length()+4,hash);
								sqrtPos++;
							}

						if(sinPos==-1&&cosPos==-1&&tanPos==-1&&logPos==-1&&sqrtPos==-1)
							{
								sinPos=0;
								cosPos=0;
								tanPos=0;
								logPos=0;
								sqrtPos=0;
								break;
							}
						}

			}
			sLength = s.length();
			i = -1;
			flag = 0;
		}
	}
	return s;
}


	string TokenMat(string s)
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
		s=powerMat(s);
		}

		if((Mul<Div||(Div==-1))&&(Mul!=-1))
		{
			s=MullMat(s);
		}
		else if((Div<Mul||Mul==-1)&&(Div!=-1))
		{
			s=DivvMat(s);

		}
		if(Mul==-1&&Div==-1)
			{

				if((Add<Sub||Sub==-1)&&(Add!=-1))
					{
						s=AdddMat(s);

					}
				else if((Sub<Add||Add==-1)&&Sub!=-1)
					{
						s=subbMat(s);
					}
			}
		if(Sub==0&&Mul==-1&&Div==-1&&Add==-1&&pow==-1) break;
	}
	while((Mul!=-1)||(Div!=-1)||(Add!=-1)||((Sub!=-1))||(pow!=-1));

		return s ;
	}
string powerMat(string s)
	{
			int x=0;
			int j = 0;
			int len ,pos6,powPos;
			string value2,hash;
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
										char * trimmed = trim(token2);
										string str1 = token2;
										len = str1.length();
										pos6 =s.find(token2);
										powPos=str1.find("^",j+1);
										if(powPos!=-1)
											{
												NumMatrices++;
												sprintf(text,"%d",NumMatrices);
												string str2 =str1.substr(0,powPos);
												int	len1=str2.length();
												int	pos7=str1.find(str2);
												value2= "#"+string(text)+"="+str2;
												createAndEvaluate(value2);
												hash="#"+string(text);
												str1.replace(pos7,len1,hash);
												s.replace(pos6,len,str1);
											}
										else
											{
												len = str1.length();
												pos6 =s.find(token2);
												NumMatrices++;
												sprintf(text,"%d",NumMatrices);
												value2 ="#"+string(text)+"="+string(trimmed);
												createAndEvaluate(value2);
												hash="#"+string(text);
												s.replace(pos6, len, hash);
											}
										j = 0;
										x=1;
										break;
									}
								j++;
							}
							j=0;
							token2 = strtok_r(NULL, separators2,&lineContext2);
					}
			return s ;
		}

string DivvMat(string s)
	{
		int x=0;
		int j = 0;
		int len ,pos6,DivPos;
		string value2,hash;
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
								char * trimmed = trim(token2);
								string str1 = token2;
								len = str1.length();
								pos6 =s.find(token2);
								DivPos=str1.find("/",j+1);
								if(DivPos>1)
									{
										NumMatrices++;
										sprintf(text,"%d",NumMatrices);
										string str2 =str1.substr(0,DivPos);
										int	len1=str2.length();
										int	pos7=str1.find(str2);
										value2= "#"+string(text)+"="+str2;
										createAndEvaluate(value2);
										hash="#"+string(text);
										str1.replace(pos7,len1,hash);
										s.replace(pos6,len,str1);

									}
								else
									{
										len = str1.length();
										pos6 =s.find(token2);
										NumMatrices++;
										sprintf(text,"%d",NumMatrices);
										value2 ="#"+string(text)+"="+string(trimmed);
										createAndEvaluate(value2);
										hash="#"+string(text);
										s.replace(pos6, len, hash);
									}
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
	string  MullMat(string s)
	{
		int len,pos6,MullPos;
		string value,hash;
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

									char * trimmed = trim(token1);
									string str1 = token1;
									len = str1.length();
									pos6 =s.find(token1);
									MullPos=str1.find("*",i+1);
									if(MullPos>1)
									{
										NumMatrices++;
										sprintf(text,"%d",NumMatrices);
										string str2 =str1.substr(0,MullPos);
										int	len1=str2.length();
										int	pos7=str1.find(str2);
										value= "#"+string(text)+"="+str2;
										createAndEvaluate(value);
										hash="#"+string(text);
										str1.replace(pos7,len1,hash);
										s.replace(pos6,len,str1);

									}
									else
									{
										len = str1.length();
										pos6 =s.find(token1);
										NumMatrices++;
										sprintf(text,"%d",NumMatrices);
										value ="#"+string(text)+"="+string(trimmed);
										createAndEvaluate(value);
										hash="#"+string(text);
										s.replace(pos6, len, hash);
									}
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
	string  AdddMat(string s)
	{
		int sub = s.find("-");
		if(sub==0)y=1;
		int len,pos6,AddPos;
		string value;
		string hash;
		char text[100];
		int i = 0;
		char* buffer = new char[s.length() + 1];
		strcpy(buffer, s.c_str());
		char* separators1 = "/*-";
		char* lineContext;
		char* token1 = strtok_r(buffer, separators1,&lineContext);
		char * trimmed = trim(token1);
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
								AddPos=str1.find("+",i+1);
								if(AddPos>1)
									{
										NumMatrices++;
										sprintf(text,"%d",NumMatrices);
										string str2 =str1.substr(0,AddPos);
										int	len1=str2.length();
										int	pos7=str1.find(str2);
										value="#"+ string(text)+"="+str2;
										createAndEvaluate(value);
										hash ="#"+string(text);
										str1.replace(pos7,len1,hash);
										s.replace(pos6,len,str1);

									}
								else
									{
										len = str1.length();
										pos6 =s.find(token1);
										NumMatrices++;
										sprintf(text,"%d",NumMatrices);
										value ="#"+string(text)+"="+string(trimmed);
										createAndEvaluate(value);
										hash ="#"+string(text);
										s.replace(pos6, len, hash);
									}
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
					if(x==1)break;
					token1 = strtok_r(NULL, separators1,&lineContext);
				}
		return s ;
	}
	string  subbMat(string s)
	{
			string oldval=s;
			int len,pos6,SubPos;
			string value; string hash;
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
									SubPos=str1.find("-",i+1);
								if(SubPos>1)
									{
									NumMatrices++;
									sprintf(text,"%d",NumMatrices);
									string str2 =str1.substr(0,SubPos);
									int	len1=str2.length();
									int	pos7=str1.find(str2);
									value="#"+ string(text)+"="+str2;
									createAndEvaluate(value);
									hash ="#"+string(text);
									str1.replace(pos7,len1,hash);
									s.replace(pos6,len,str1);

									}
								else
									{
									len = str1.length();
									pos6 =s.find(token1);
									NumMatrices++;
									sprintf(text,"%d",NumMatrices);
									value = "#"+string(text)+"="+string(trimmed);
									createAndEvaluate(value);
									hash="#"+string(text);
									s.replace(pos6, len, hash);
									}
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
				if(s==oldval) s=AdddMat(s);
			return s ;
	}
