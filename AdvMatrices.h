/*
 * rome7.h
 *
 *  Created on: Jan 22, 2018
 *      Author: mohamed
 */

#ifndef ROME7_H_
#define ROME7_H_
#include "assistingfunctions.h"
#include "Mystring.h"
#include <fstream>
#include "assistingfunctions.h"
#include "Mystring.h"
#include <fstream>
#include<iostream>
#include "AdvNumbers.h"
using namespace std;
string AdoperationMat(string s);
/**
 * @brief <Evaluates a string of operations on Matrices >
 *
 * <Example:"Y = C^3 * sin(1./D) ">
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string AdOperation1Mat(string s);
string trimm(string text);
/**
 * @brief <shrinks a string of operations on Matrices to only 1 operation >
 *
 * <Example:"Y = C^3 * sin(1./D)">
 *
 * @param <string s> <string to be shrinked>
 *
 * @return <Shrinked string>
 */
string TokenMat(string s);
/**
 * @brief <Evaluates only one expression operations on Matrices according to priority of operators >
 *
 * <Example:"C + B * A">
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string powerMat(string s);
/**
 * @brief <Parses input string to get expression contains power operator only then calls>
 *
 * <Example:"A ^ B * C" -> " A ^ B "
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string  MullMat(string s);
/**
 * @brief <Parses input string to get expression contains Multiply operator only then calls>
 *
 * <Example:"A ^ B * C" -> " B * C "
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string  DivvMat(string s);
/**
 * @brief <Parses input string to get expression contains Divide operator only then calls>
 *
 * <Example:"A / B * C" -> " A / B "
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string  AdddMat(string s);
/**
 * @brief <Parses input string to get expression contains Add operator only then calls>
 *
 * <Example:"A / B + C" -> " A / B "
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */
string  subbMat(string s);
/**
 * @brief <Parses input string to get expression contains power operator only then calls>
 *
 * <Example:"A - B + C" -> " A - B "
 *
 * @param <string s> <string to be evaluated>
 *
 * @return <evaluated string>
 */





#endif /* ROME7_H_ */
