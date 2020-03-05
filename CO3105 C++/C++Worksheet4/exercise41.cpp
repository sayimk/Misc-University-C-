/*
 * exercise41.cpp
 *
 *  Created on: 12 Oct 2017
 *      Author: sayimk
 */

#include "exercise41.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

	int main(){

		//vars
		string temp;
		string output="";
		int sequenceLength;
		int bufferSize;
		bool valid = false;
		int currentPos; //tracking current empty array field


		//repeating until valid use input
		while(!valid){

		//fetching sequence length from user
		 cout << "Enter the size of the array: '" << endl;
		 getline(cin,temp);
		 sequenceLength=atoi(temp.c_str());

		 //fetching buffer size
		 cout << "Enter the size of the buffer (k): '" << endl;
		 getline(cin,temp);
		 bufferSize=atoi(temp.c_str());

		 //validating inputs
		 if(sequenceLength <0)
			 cout<<"The information you entered is not valid. Please try again."<<endl;
		 else if (bufferSize<0)
			 cout<<"The information you entered is not valid. Please try again."<<endl;
		 else if (bufferSize>sequenceLength)
			 cout<<"The information you entered is not valid. Please try again."<<endl;
		 else valid = true;
		}

		//Creating and filling the new array
		int fibNumbs [sequenceLength];

		for (currentPos=0; currentPos<bufferSize; currentPos=currentPos+1){

			 cout << "Enter a number: '" << endl;
			 getline(cin,temp);
			 fibNumbs[currentPos]=atoi(temp.c_str());
		}


		for (int i = currentPos; i < sequenceLength; i=i+1)
			fibNumbs[i]= fibNumbs[(i-1)]+fibNumbs[(i-2)];


		//constructing output String
		for (int i=0; i<sequenceLength; i=i+1)
			output = output + to_string(fibNumbs[i]) + ",";

		cout << output << endl;

		return 0;
	}
