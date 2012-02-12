#include <iostream>
#include "lib.h"


	char* add(char * left, int sizeOfLeft, char * right, int sizeOfRight)
	{
		int detention=0, number=0;
		char* result=NULL;
		
		bool sign=false; // false represent positif number
		if(left[0]=='-')
		sign=true;
		if(right[0]=='-')
		//call substration 
		
		if(sizeOfLeft>sizeOfRight)
			 result=new char[sizeOfLeft+2];
		if(sizeOfLeft<sizeOfRight)
			result=new char[sizeOfRight+2];
		else
		result=new char[sizeOfLeft+2];
		for(int i =sizeOfLeft-1; i<=0; i--)
		{
			number=left[i]+right[i]+detention;
			result[i]=number%10;
		}
		return result;
	}

