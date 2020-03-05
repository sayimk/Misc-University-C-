/*
 * userFib.cpp
 *
 *  Created on: 11 Oct 2017
 *      Author: sayimk
 */

#include "userFib.h"
#include <string>;
#include <iostream>;
#include <stdlib.h>;

using namespace std;

 int main(){

	 int userNumb;
	 int fibNumb;
	 string temp;

	 //prompt for number and fetching number
	 cout << "Enter a Number: " << endl;
	 getline(cin,temp);
	 userNumb=atoi(temp.c_str());

	 //processing the user's number
	 if(userNumb==0)
		 cout << userNumb << "'s Fibonacci number is " << 0 << endl;
	 else if (userNumb==1)
		 cout << userNumb << "'s Fibonacci number is " << 0 << endl;
	 else{
		 fibNumb=((userNumb-1)+(userNumb-2));
		 cout << userNumb << "'s Fibonacci number is " << fibNumb << endl;

	 }

	 return 0;
 }

