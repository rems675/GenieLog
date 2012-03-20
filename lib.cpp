#include <iostream>
#include <fstream>
#include <string.h>
#include "../include/lib.h"

using namespace std;

char *__strcpy(char *target, const char *source)
{
        char *orig_target = target;

        while(*source)
                *target++ = *source++;
        *target = '\0';

        return orig_target;
}

/* Supprime les zéros inutiles
 * 0001234 devient 1234
 * 00000   devient 0
 */
char* suprZeros(char *s, int size)
{
    int n = size;
    int i=0;
    
     //On supprime les zéros inutiles 
	while(s[i]=='0')
		s++;
	   
	  return s;
}

/* Retourne le chaîne s
 * 1234 -> 4321
 */
char* reverse(char *s, int size)
{
    int n = size;
    int i;

    for (i = 0; i < n / 2; ++i)
    {
        int tmp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = tmp;
    }
  
    return s;
}

/* Supprime les zéros inutiles et retourne la chaîne s */
char * transforme(char *s, int size)
{
    char * retReverse = reverse(s, size);
    char* final=suprZeros(retReverse, size);
    return final; 
    
}

/**STRING COMPARE**/
int __strcmp(char *a, int sizea, char *b, int sizeb)
{
	a=suprZeros(a, taille(a));
	b=suprZeros(b, taille(b));
	
	int i=0;
	if(taille(a)>taille(b))// we check if the number left is higher than the other
		return 1;
	if(taille(a)<taille(b)) //we check if the number left is lesser than the other
		return -1;
		
	if(taille(a)==taille(b))//we check if the number is like than the other
	{
		/* if the numbers are egal and we haven't run all the string
		 * we run through the string
		  */
		while(a[i]==b[i] && i!=taille(a)) 
		i++;
		if(a[i]>b[i]) // if a part of string are higher than te other return 1
			return 1;
		if(a[i]<b[i]) // reverse
			return -1;
	}
	return 0; // string are the same
}
/**CORE ADDITION**/
char * coreAdd(char * left, int sizeOfLeft, char * right, int sizeOfRight) {

    /* [ Determine which number is longer. ]
     * For visibility's sake, I'm aliasing "min" and "max" to the corresponding
     * values from "sizeOfLeft" and "sizeOfRight".
     * For the same reason I'm aliasing the pointers "small" and "big" to the
     * "left" and "right" array of characters.
     */
    int min = sizeOfRight; char * small = right;
    int max = sizeOfLeft;  char * big   = left;
    if (max < min) {
        max = min;        big   = small;
        min = sizeOfLeft; small = left;
    }


    /* [ Allocate space to store the result. ]
     * The result array of characters needs to have one more cell than the
     * bigger between right and left, so that's one more than "max".
     * 9 + 9 -> 18
     * 9 + 1 -> 10
     * The allocation itself needs to be nested in a try block to provide
     * exception handling when not enough space is available.
     */
    char * result;
    try {
        result = new char[max+1];
    }
    catch (...) { return NULL; } // This catches any exception and return NULL.


    /* [ Initialize. ] 
     * - Of course the carry needs to be 0 when first entering the loop.
     * - Also, we'll use "max" to address both the current value inside of "big"
     * and the current cell in the result array.
     * Because the result array has "max+1" cells, to access the right one using
     * the value of "max" we can either evaluate "max+1" each time we need it,
     * or save ourselves a considerable number of operations by adding "1" to
     * the value pointed by "result". (The same way we would move %edi by one 
     * char in assembly using "addb $1,%edi")
     * - Finally, the last cell of each array holds the "End Of String"
     * character: '\0' which value is "0". We need to set the last cell of the
     * result array with that same value for various reasons. 
     * (i.e: Use with "cout".)
     */
    char carry = 0;
    ++result;
    result[max] = 0; --min; --max;

    /* Now let's get to work people! */

    /* [ Phase 1/3 ]
     * We have to sum the values contained in the cells of the small and big
     * arrays, and store the result in the "result" array.
     * At each step we also need to add the carry.
     *
     *      Example 1:
     *      '1' + '2' = 49 + 50 =  99
     *                            -48
     *                           = 51 = '3'
     *      (Hence the - '0' below, because '0' = 48) (#1)
     *
     *      Example 2:
     *      '9' + '3' = 57 + 51 = 108
     *                            -48
     *                           = 60 = '<' --> 60 / 58 = 1 ( carry )
     *                                      --> 60 % 58 = 2 ( reminder )
     *      (Hence the '9'+1 below, because '9'-1 = 58) (#2)
     *
     * When a carry is produced, the reminder needs to be added 48 again to
     * match the character corresponding. (#3)
     * In the second example above, the reminder is 2. But the character of
     * value 2 is '2'. and '2' = 50 = 2 + 48
     */
    for (min ; min >= 0 ; --min, --max) {
        result[max] = big[max] + small[min] - '0' + carry; // (#1)
        carry       = result[max] / ('9'+1);  // (#2)
        result[max] = result[max] % ('9'+1);
        if (carry)       // (#3)
            result[max] = result[max] + '0';
    }


    /* [ Phase 2/3 ]
     * It's exactly the same principle as in phase 1, except we're done with
     * the small array, so we only need to propagate the carry on the values
     * from the big array.
     */
    for (max ; max >= 0 ; --max) {
        result[max] = big[max] + carry;
        carry       = result[max] / ('9'+1);
        result[max] = result[max] % ('9'+1);
        if (carry)
            result[max] = result[max] + '0';
        else
            while (max--)
                result[max] = big[max];
    }


    /* [ Phase 3/3 ]
     * The work is almost done.
     * The last operation may have raised a carry, in which case we need to set
     * the value of the first cell of our array with the character '1'.
     * But to access the cell of indice zero in our array, we first need to
     * switch back the pointer from one char so as to undo what was done during
     * initialization.
     */
    --result;
    if (carry)
        result[0] = '1';
    else
        result[0] = '0';


    /* [ Completion.]
     * Return the pointer on the array with the result.
     * A problem with this algorithm is the leading zero when the last
     * addition fails to raise a carry.
     */
     result=suprZeros(result, taille(result));
    return result;
}
/**ADDITON TREATMENT**/
char* add(char * left, int sizeOfLeft, char * right, int sizeOfRight)
{				
	return(coreAdd(left, sizeOfLeft, right, sizeOfRight));	
}

/**SUBSTRACTION**/
char *sub(char * left, int sizeOfLeft, char * right, int sizeOfRight) // Grand, taille du grand, petit, taille petit
{
		right=complement(right, taille(right), taille(left));
	
		//int maxLeft=sizeOfLeft-1, min=sizeOfRight-1, carry=0, i=0, maxRight;
		int maxLeft=taille(left)-1, min=taille(right)-1, carry=0, i=0, maxRight;
		char *res;		
		//cherche le complément du tableau Right on ecrasse les donner pour mettre les données complémenter
		while(right[min-i]=='0') // on prend comme début le dernier chiffre non nul en partant de la droite
			i++;
		maxRight=min-i; // c'est notre reférence
	
		right[maxRight]= -(right[maxRight]-'0')+('9'+'1')-'0';// on cherche le complément du chiffre le plus a droite
		--maxRight; //on passe au chiffre suivant, leur sort est différent !
		
		for(int j=maxRight; j>=0; j--)
			right[j]=-(right[j]-'0')+'9';					
			
		//std::cout<<" valeur tab"<<right<<std::endl;
		//++maxRight; //on incrément pour revenir sur le dernier chiffre non nul du grand nombre

		//res=coreAdd(left, sizeOfLeft, right, sizeOfRight);
		res=coreAdd(left, taille(left), right, taille(right));
		delete [] right;
		++res;// pour suprimer le 1 en debut de chaine du au complement; sela fait partir de l'algorithme du complement.
		//int resTaille = taille(res); // recuperer la taille du resultat
		res=suprZeros(res, taille(res)); // on suprime les zero inutile du resulat.
	

		return (res);
	}


char *mult(char* left, int sizeOfLeft, char* right, int sizeOfRight) // multiplication
{
	    char * result;
    try {
        result = new char [(sizeOfLeft+sizeOfRight)] ;
         for(int k=0; k<=(sizeOfLeft+sizeOfRight); k++)
			result[k]=0;
	
        
    }
    catch (...) { return NULL; } // This catches any exception and return NULL.
    int i=0,cr=0, j=0, tmp=0;
    
	 for ( i = 0; i < sizeOfLeft; i++ )
    {
        /* Retenue */
        int cr = 0;

        for ( j = 0; j < sizeOfRight || cr; j++ )
        {
            /* On effecue la multiplication de b par le chiffre courant de a */
            int tmp = result[i + j] + cr;

            if ( j < sizeOfRight)
            {
                tmp += ( left[ sizeOfLeft - i - 1] - '0') *
                       ( right[ sizeOfRight - j - 1] - '0');
            }

            /* Si le produit est supérieur à 10, on pose la retenue */
            cr = tmp / 10;

            if ( cr )
            {
                /* si il y a retenue on ne conserve que l'unité du produit */
                tmp %= 10;
            }

            result[i + j] = tmp;
        }
    }

    for ( i = 0; i < sizeOfLeft+sizeOfRight; i++ )
    {
        /* On récupère le caractère correspondant à la valeur de tmp */
        result[i] += '0';
    }
    
   
	  char* recup=transforme ( result, sizeOfLeft+sizeOfRight );
	    return recup; 
}

char* division(char* left, int sizeOfLeft, char* right, int sizeOfRight) // division
{
	//char * div=complement(right, taille(right), taille(left));
	//char * s;
	char * result;// contien le resultat de la division
	char * one = new char[1];// un tableau qui contien la valeur 1; pour incrémenter le quotien a chaque tours de boucle
	one[0]='1';
	
	 try
     {
        result = new char [((sizeOfLeft-sizeOfRight)+1)] ; 
     }
    catch (...) { return NULL; } // This catches any exception and return NULL

	while(__strcmp(left, taille(left), right, taille(right))!=-1)
	{		
		if(__strcmp(left, taille(left), right, taille(right))==0)
		{
			result=add(result, taille(result), one, taille(one));
			break;
		}
		else
		{
			left=sub(left, taille(left), right, taille(right));
			result=add(result, taille(result), one, taille(one));
			result=suprZeros(result, taille(result));
		}
	}
	
	
	result=suprZeros(result, taille(result));
	return result;
}

int taille(char * str) //calcul la taille
{
	int size =0;
	while(str[size++]);
	return size-1;
		
}

char * complement(char * s, int sizeOfLittle, int sizeOfBig) // fonction qui fait le complement d'un nombre
{
//	std::cout<<"chaine a completer "<<s<<"sizeBig "<<sizeOfBig<<"size Little "<<sizeOfLittle<<std::endl;
	int recop=0;
	
	//	std::cout<<sizeOfLittle<<std::endl;
	//	std::cout<<sizeOfBig<<std::endl;
		char * newTab = new char[sizeOfLittle+(sizeOfBig-sizeOfLittle)];
		int sizeOfNewTab=sizeOfLittle+(sizeOfBig-sizeOfLittle);
		recop=sizeOfNewTab-1;
	//	std::cout<<"taille new "<< sizeOfBig-sizeOfLittle<<std::endl;

		for(int t=sizeOfLittle-1; t>=0; t--)
		{
			newTab[recop]=s[t];
			recop--;
		}
		
		for(int t=recop; t>=0; t--)
			newTab[t]='0';
			
		return newTab;			
}	

/**
 * \fn bool lib.cpp (char*)
 * \brief Fonction qui permet de charger un fichier avec une opération.
 *
 * \return true si corectement déroulée - sinon false
 */
 //HERE FOR YOU !
bool fileLoad(char * file)
{
	char numberOne[2048];
	char numberTwo[2048];
	char sign[2];
	sign[1]='\0';
	int pos;
  
	ifstream f;

    f.open(file, fstream::in); // It opens the file
    if (!f || !f.good())
    {
        cout << "could not open file !\n";
        return false;
    }

    if (f.fail())
    {
        std::cout << "failed to append to file!\n";
        return false;
    }
    
    f.seekg (0, ios::beg); // We place ourselves at the beginning of the file
	f.getline(numberOne,2048, ':'); // is recovered in a table the first number to the separator

    // It is just after the first separator
	f.get(sign[0]); // It recovers the sign of the operation in the variable sign
	
	f.get(numberTwo[0]); // e advance in the file, it recovers the second separator into the first box of the second table to move forward in the file

	f.getline(numberTwo,2048);// The second number is recovered! So we crashed the first character is the separator.

	f.close(); // Close the file.
	
	char* ret = operationLoad(numberOne, sign, numberTwo); // calls the function of the operation taitement
	bool val = writeFile(ret); // calls the functions of writing in an output file
    
}
/**
 * \fn bool lib.cpp (char*)
 * \brief Fonction qui permet d'ecrire le resultat dans un fichier
 *
 * \return true si corectement déroulée - sinon false
 */
bool writeFile(char * result)
{
	
	char fileExit[50];
	cout<<" >> Enter name of relatif path of the ouput file  ";  
	cin>>fileExit;
	
	ofstream f;
    f.open(fileExit, ios::app);
   if(f)    // All is OK
   {
		 f<<result;
		 f.close();
   }
	else
	{
		cerr << " ERROR: Can not open file " << endl;
		return false;
	}
	 return true;

}
char* operationLoad(char * left,char * sign, char * right) // charger une opération depuis	
{
	    int memory=-2; //taille des chiffre a gauche et a droite de l'oppérande
		bool zeroLelf=false, zeroRight=false; // false represent positif number
		char * res;
		int i=0;

		std::cout<<left << sign << right<<std::endl;
		
		//traintement des 0
		if(left[0]=='-')
		{
			i=1;
			while(left[i++]=='0')
				zeroLelf=true;

		}
		else
		{
			i=0;
			while(left[i++]=='0')
				zeroLelf=true;

		}
		
		i=0;
		while(right[i++]=='0')
				zeroRight=true;

		
		
		
		if(sign[0]=='+')
		{
			if(left[0]=='-')
			{
				
				if(zeroLelf)
				{
					cout<<"=  "<< right<<endl;
					return NULL;
				}
				if(zeroRight)
				{
					cout<<"=  "<< left<<endl;
					return NULL;
				}
				
					
				char*saveLeft=left;
				++saveLeft;
				memory = __strcmp(saveLeft, taille(saveLeft), right, taille(right));
				switch(memory)
				{
					case 0:
						 cout<<" = 0 "<<endl;
					break;

					case 1: // le chiffre gauche est plus grand
					res=sub(saveLeft,taille(saveLeft), right, taille(right));
						 cout<<" = - " <<res<<endl;
						 return res;
					break;
						case -1: // le chiffre gauche est plus petit
					res=sub(right, taille(right), left, taille(left));//( grand, petit )
						cout<<" =  " <<res<<endl;
						 return res;
					break;
				}		 
				 
			}
			else
			{
				if(zeroLelf)
				{
					cout<<"=  "<< right<<endl;
					return NULL;
				}
				if(zeroRight)
				{
					cout<<"=  "<< left<<endl;
					return NULL;
				}
				res=add(left,taille(left), right, taille(right));
				cout<<" = " <<res<<endl;
				 return res;
			}

		}
		if(sign[0]=='-')
		{
			if(left[0]=='-')
			{
				if(zeroLelf)
				{
					cout<<"= - "<< right<<endl;
					return NULL;
				}
				if(zeroRight)
				{
					cout<<"=  "<< left<<endl;
					return NULL;
				}
				char*saveLeft=left;
				++saveLeft;
				res=add(saveLeft,taille(saveLeft), right, taille(right));
				cout<<" = - " <<res<<endl;
				 return res;
				
			}
			else
			{
				if(zeroLelf)
				{
					cout<<"= - "<< right<<endl;
					return NULL;
				}
				if(zeroRight)
				{
					cout<<"=  "<< left<<endl;
					return NULL;
				}
				memory = __strcmp(left, taille(left), right, taille(right));
				switch(memory)
				{
					case 0:
						std::cout<<"identique"<<std::endl;
						 cout<<" = 0 "<<endl;
					break;

					case -1: // le chiffre gauche est plus petit
					
						res=sub(left, taille(left), right, taille(right)); //apeler soustraction( grand, comp(petit) )

						cout<<" = - " <<res<<endl;
						 return res;
					break;
					
					case 1:
						//apeler sosutarction (grand, petit)
						res=sub(left,taille(left), right, taille(right));
						cout<<" =  " <<res<<endl;
						 return res;
					
					break;
				}

			}
		}
		
		if(sign[0]=='x')
		{
			if(left[0]=='-')
			{
				if(zeroLelf)
				{
					cout<<"=  "<< right<<endl;
					return NULL;
				}
				if(zeroRight)
				{
					cout<<"=  "<< left<<endl;
					return NULL;
				}
				
				char*saveLeft=left;
				++saveLeft;
				res=mult(saveLeft, taille(saveLeft), right, taille(right));
				cout<<" = - "<<res<<endl;
				 return res;
				
			}
			else
			{
				if(zeroLelf)
				{
					cout<<"=  0"<<endl;
					return NULL;
				}
				if(zeroRight)
				{
					cout<<"=  0"<<endl;
					return NULL;
				}
				
				res=mult(left, taille(left), right, taille(right));
				cout<<" =  "<<res<<endl;
				 return res;
			}
		}
		
	if(sign[0]=='/')
		{
			if(left[0]=='-')
			{
				if(zeroLelf)
				{
					cout<<"= 0 "<<endl;
					return NULL;
				}
				if(zeroRight)
				{
					cout<<"=  ERREUR division par zero interdite "<<endl;
					return NULL;
				}
				
				memory = __strcmp(left+1, taille(left)-1, right, taille(right));
				switch(memory)
				{
					case 0:
						 cout<<" = 1 "<<endl;
					break;

					case -1: // le chiffre gauche est plus petit
						cout<<" = 0 " <<endl;
					break;
					case 1:
						char*saveLeft=left;
						++saveLeft;
						//apeler division (grand, petit)
						res=division(saveLeft, taille(saveLeft), right, taille(right));
						cout<<" = - " <<res<<endl;
						 return res;
					break;
				}
			}
			else
			{
				if(zeroLelf)
				{
					cout<<"= 0 "<<endl;
					return NULL;
				}
				if(zeroRight)
				{
					cout<<"=  ERRREUR division par zero interdite"<<endl;
					return NULL;
				}
				
				memory = __strcmp(left, taille(left) , right, taille(right));
				switch(memory)
				{
					case 0:
						 cout<<" = 1 "<<endl;
					break;

					case -1: // le chiffre gauche est plus petit
						cout<<" = 0 " <<endl;
					break;
					case 1:
						//apeler division (grand, petit)
						res=division(left, taille(left), right, taille(right));
						cout<<" =  " <<res<<endl;
						 return res;
					break;
				}
			}
				
		}
}
