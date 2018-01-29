/*
 * linked.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: mohamed
 */
#include "MatLibrary.h"
#include "linked.h"



node *head = NULL;//pointer to the first structure in list
node *current = NULL;//pointer to the current structure in list


	//Create Linked List
	CMatrix * INSERT(string ID,int Nrows,int Ncolumns)
	{
		// Allocate memory for new node;
		node *link = new node;
		link->Matrix =new CMatrix(Nrows,Ncolumns);
		link->ID = ID;
		link->next = NULL;

		// If head is empty, create new list
		if (head == NULL)
		{
			head = link;
			return link->Matrix;

		}

		current = head;

		// move to the end of the list
		while (current->next != NULL)
		{
			current = current->next;
		}

		// Insert link at the end of the list
		current->next = link;
		return link->Matrix;

	}
	/*
	 *
	 * ISEXIST Function
	 *
	 */
	CMatrix* ISEXISTING (string id)
	{
		   if(head==NULL)
		   {
		    //cout <<("Linked List is empty");
		      return NULL;
		   }

		   // start checking from the first node
		   current = head;
		   while(current != NULL)
		   {
		      if(current->ID == id)
		      {
		    	  //cout<<current->ID<<endl;
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
