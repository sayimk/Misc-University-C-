/*
 * BankAccount.cpp
 *
 *  Created on: Nov 12, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */

#include <iostream>
#include "BankAccount.h"


using std::string;
using std::ostream;


Account::Account(std::string name)
{
	accountName = name;
	accountBalance = 0;
}

Account::Account(std::string name, float balance)
{
	accountName = name;

	if(balance >0)
	accountBalance = balance;
	else
		accountBalance = 0;

}

Account::~Account()
{
	 // Implement me
}


float Account::balance() const
{

	return accountBalance;
}

bool Account::deposit(float val)
{

	 if (val<0)
		 return false;

	 accountBalance = accountBalance+val;

	return true;
}

bool Account::withdraw(float val)
{
	 if (val<0)
		 return false;

	 if(val>accountBalance)
		 return false;

	 if ((accountBalance-val)<0)
		 return false;

	 accountBalance = accountBalance - val;

	 return true;
}

void Account::day(){}

void Account::month(){}

string Account::name() const {

	return accountName;
}

ostream& operator<<(ostream& o, const Account& a)
{
	o << a.toString();
	return o;
}


CurrentAccount::CurrentAccount(std::string name, float overdraft, float interest, float fee)
: Account(name)
{
	accountType = "Current Account";
	 this->overdraft = overdraft;
	 this->interest = interest;
	 this->fee = fee;
	 balance();
}

CurrentAccount::CurrentAccount(std::string name, float balance, float overdraft, float interest, float fee)
: Account(name,balance)
{
	accountType = "Current Account";
	 this->overdraft = overdraft;
	 this->interest = interest;
	 this->fee = fee;
}


// Destructor
CurrentAccount::~CurrentAccount()
{
	 // Implement me
}

string CurrentAccount::type() const
{
	return "Current Account";
}


bool CurrentAccount::withdraw(float val)
{
	 if (val<0)
		 return false;

	 if(val>(accountBalance+overdraft))
		 return false;

	 if ((accountBalance-val)<(0-overdraft))
		 return false;

	 accountBalance = accountBalance - val;

	 return true;
}

void CurrentAccount::day()
{
	if (accountBalance <0){
		accountBalance = accountBalance - interest;
	}

	accountBalance = accountBalance - 25;
}

void CurrentAccount::month()
{
	 accountBalance = accountBalance - fee;

}

string CurrentAccount::toString() const
{
	 string output = type()+" of "+accountName;

	 output = output +" (" +  std::to_string(accountBalance)+") ";
	 output = output + " (" + std::to_string(fee) +","+std::to_string(overdraft)+")";

	return output;
}

SavingsAccount::SavingsAccount(std::string name, float interest)
: Account(name)
{
	 this->savingsInterest = interest;
}

SavingsAccount::SavingsAccount(std::string name, float balance, float interest)
: Account(name,balance)
{
	 this->savingsInterest = interest;
}

SavingsAccount::~SavingsAccount()
{
}

string SavingsAccount::type() const
{
	return "Saving Account";
}

void SavingsAccount::month()
{
	 accountBalance = accountBalance + savingsInterest;
}

string SavingsAccount::toString() const
{
	string savingsOutput = type() +" of "+name();
	savingsOutput = savingsOutput +" (" +  std::to_string(balance())+") ";
	savingsOutput = savingsOutput + "(" +std::to_string(savingsInterest) +"%)";
	return savingsOutput;
}

StockAccount::StockAccount(std::string name)
: Account(name)
{
	size = 1;
	stockList = new string[size]();
	stockAmount = new float[size]();
	stockValues = new float[size]();


}

StockAccount::StockAccount(std::string name, float balance)
: Account(name,balance)
{
	size = 1;
	stockList = new string[size]();
	stockAmount = new float[size]();
	stockValues = new float[size]();


}

StockAccount::~StockAccount()
{
	if (stockList)
		delete [] stockList;

	if (stockAmount)
		delete [] stockAmount;

	if (stockValues)
		delete [] stockValues;
}

bool StockAccount::buy (const std::string stock, float amount, float value)
{
	 if (stock == "")
		 return false;

	 if (amount < 1)
		 return false;

	 if (value < 1)
		 return false;

	 int totalCost = amount*value;

	 if (totalCost>accountBalance)
		 return false;

	 accountBalance = accountBalance-totalCost;

	int location = -1;

	for (int i=0; i <size; i++){
		if (stockList[i]==stock)
			location = i;
		}

	if (location!=-1){

		stockAmount[location] = stockAmount[location]+amount;
		stockValues[location] = value;


	}else{
	 stockList[(size-1)]= stock;
	 stockAmount[(size-1)] = amount;
	 stockValues[(size-1)] = value;

	 string *tempList = new string[(size+1)];
	 float *tempAmount = new float[(size+1)];
	 float *tempValue = new float[(size+1)];

	 for (int i=0; i<size; i++){
		 tempList[i]=stockList[i];
		 tempAmount[i] = stockAmount[i];
		 tempValue[i] = stockValues[i];
	 }

	 size = size+1;

	 if (stockList)
		 delete [] stockList;

	 if (stockAmount)
		 delete [] stockAmount;

	 if (stockValues)
		 delete [] stockValues;

	 stockList = tempList;
	 stockAmount = tempAmount;
	 stockValues = tempValue;

	}

	 return true;
}

bool StockAccount::sell(const std::string stock, float amount)
{
	 if (stock == "")
		 return false;


	 if (amount < 1)
		 return false;


	int location = -1;

	for (int i=0; i <size; i++){
		if (stockList[i]==stock)
			location = i;
	}

	if (location==-1)
		return false;

	if(stockAmount[location]<amount)
		return false;

	int revenue = (stockValues[location]* amount);

	accountBalance = accountBalance+revenue;
	stockAmount[location] = stockAmount[location]-amount;

	return true;
}

bool StockAccount::update(const std::string stock, float value)
{
	 if (stock == "")
		 return false;

	 bool found = false;
	 int location;

	 for (int i = 0; i <size; i++){
		 if (stockList[i]==stock){
			 found = true;
			 location = i;
		 }
	 }

	 if (!found)
		 return false;

	 stockValues[location] = value;

	return true;
}

string StockAccount::type() const
{
	return "Stock Account";
}

string StockAccount::toString() const
{
	 string stockOutput = type() + " of " +name();

	stockOutput = stockOutput +" (" +  std::to_string(balance())+")";

	 string item;


	 for (int i = 0; i < size; i++){
		 if (stockAmount[i]>0){
			 item = " ("+stockList[i]+","+std::to_string(stockAmount[i])+","+std::to_string(stockValues[i])+")";

			 if (i != (size-1))
				 item = item + ",";

			 stockOutput = stockOutput + item;
		 }

	 }



	return stockOutput;
}

/*
 * BankAccount.h
 *
 *  Created on: Nov 12, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */
