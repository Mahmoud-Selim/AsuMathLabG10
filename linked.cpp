/*
 * linked.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: mohamed
 */
#include "MatLibrary.h"
#include "linked.h"



node *head = NULL;
node *current = NULL;


CMatrix * INSERT(string ID,int Nrows,int Ncolumns)
{
	node *link = new node;
	link->Matrix =new CMatrix(Nrows,Ncolumns);
	link->ID = ID;
	link->next = NULL;
	if (head == NULL)
	{
		head = link;
		return link->Matrix;
	}
	current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = link;
	return link->Matrix;
}


CMatrix* ISEXISTING (string id)
{
	if(head==NULL)
	{
		return NULL;
	}
	current = head;
	while(current != NULL)
	{
		if(current->ID == id)
		{
			return current ->Matrix;
		}
		current = current->next;
	}
	return NULL;
}


void KILLLIST(void)
{
	current = head;
	if(head != NULL)
	{
		if(head->next==NULL)//list is empty
		{
			delete head->Matrix;
			return ;
		}
		while(current->next!=NULL)
		{
			delete current->Matrix;
				current=current->next;
		}
	}
}
