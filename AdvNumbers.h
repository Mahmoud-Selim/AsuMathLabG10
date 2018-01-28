/*
 * AdvOp.h
 *
 *  Created on: Jan 21, 2018
 *      Author: mohamed
 */

#ifndef ADVOP_H_
#define ADVOP_H_
#include<string>
#include "Mystring.h"
#include"string"
#include<iostream>
#include "assistingfunctions.h"
using namespace std;

string Adoperation1Num(string s);
/**
 * @brief <Evaluates a string of operations on numbers >
 *
 * <Example:"L = (1.2 + 3.4 - 5.6)/(2.1*3.2 + 4.6) - 12.1*3.1 + (1.2 + 5.2)^(4/(3.2+5.6))>
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string AdoperationNum(string s);
/**
 * @brief <shrinks a string of operations on numbers to only 1 operations >
 *
 * <Example:"L = (1.2 + 3.4 - 5.6)/(2.1*3.2 + 4.6) - 12.1*3.1 + (1.2 + 5.2)^(4/(3.2+5.6))>
 *
 * @param <string s> <string to be shrinked>
 *
 * @return <Shrinked string>
 */
string trimm(string text);
/**
 * @brief <trim " ( ) " from input string>
 *
 * @param <string text> <string to be trimmed>
 *
 * @return <Trimmed string>
 */
string TokenNum(string s);
/**
 * @brief <Evaluates only one expression operations on numbers according to priority of operators >
 *
 * <Example:"1.2 + 3.4 * 5.6">
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string powerNum(string s);
/**
 * @brief <Parses input string to get expression contains power operator only then calls
 * pow_string to evaluate power expression >
 *
 * <Example:"1.2 ^ 3.4 * 5.6" -> " 1.2 ^ 3.4 " -> pow_string >
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string  MullNum(string s);
/**
 * @brief <Parses input string to get expression contains multiply operator only then calls
 * Mul_string to evaluate multiply expression >
 *
 * <Example:"1.2 ^ 3.4 * 5.6" -> " 3.4 * 5.6 " -> pow_string >
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string  DivvNum(string s);
/**
 * @brief <Parses input string to get expression contains Division operator only then calls
 * Div_string to evaluate division expression >
 *
 * <Example:"1.2 / 3.4 * 5.6" -> " 1.2 / 3.4 " -> Div_string >
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string  AdddNum(string s);
/**
 * @brief <Parses input string to get expression contains addition operator only then calls
 * Add_string to evaluate addition expression >
 *
 * <Example:"1.2 + 3.4 * 5.6 "-> " 1.2 + 3.4 " -> Add_string >
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string  subbNum(string s);
/**
 * @brief <Parses input string to get expression contains subtraction operator only then calls
 * Sub_string to evaluate subtraction expression >
 *
 * <Example:"1.2 - 3.4 * 5.6" -> " 1.2 - 3.4 " -> Sub_string >
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
double Mul_string(char * s);
/**
 * @brief <Parses input to get operands that will be multiplied then evaluates it>
 *
 * <Example:" 1.2 * 3.4 "
 *
 * @param <char * s>
 *
 * @return <result of multiplication>
 */
double Div_string(char * s);
/**
 * @brief <Parses input to get operands that will be Divided then evaluates it>
 *
 * <Example:" 1.2 / 3.4 "
 *
 * @param <char * s>
 *
 * @return <result of Division>
 */
double Add_string(char * s);
/**
 * @brief <Parses input to get operands that will be Added then evaluates it>
 *
 * <Example:" 1.2 + 3.4 "
 *
 * @param <char * s>
 *
 * @return <result of Addition>
 */
double Sub_string(char * s);
/**
 * @brief <Parses input to get operands that will be subtracted then evaluates it>
 *
 * <Example:" 1.2 - 3.4 "
 *
 * @param <char * s>
 *
 * @return <result of subtraction>
 */
double pow_string(char * s);
/**
 * @brief <Parses input to get operands that will be powerd then evaluates it>
 *
 * <Example:" 1.2 ^ 3.4 "
 *
 * @param <char * s>
 *
 * @return <result of powering>
 */





#endif /* ADVOP_H_ */
