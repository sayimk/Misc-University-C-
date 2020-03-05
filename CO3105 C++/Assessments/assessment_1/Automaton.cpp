/*
 * Automaton.cpp
 * Created on: 23/10/2017
 * Author: np183
 *         Department of Informatics
 * 	   University of Leicester
 */
#include <iostream>
#include <string>
#include "Automaton.h"

using std::cout;
using std::endl;


Automaton::Automaton() 
{
	_stateArraySize =1;
	_transitionArraySize =1;
	_automatonName="";
	_stateArray = new State*[_stateArraySize];
	_transitionArray = new Transition*[_transitionArraySize];
}

Automaton::Automaton(const std::string& name)
{
	_stateArraySize =1;
	_transitionArraySize =1;
	_automatonName=name;
	_stateArray = new State*[_stateArraySize];
	_transitionArray = new Transition*[_transitionArraySize];
}

Automaton::Automaton(const Automaton& other) 
{
	_stateArraySize = (other.numberOfStates()+1);
	_transitionArraySize = (other.numberOfTransitions()+1);
	_automatonName=other.getName();
	_stateArray = new State*[_stateArraySize];
	_transitionArray = new Transition*[_transitionArraySize];



	//adding all the state
	for(int i=0; i<(other.numberOfStates()+1); i++){
		_stateArray[i]=other.customGetState(i);

	}

	for(int i=0; i<(other.numberOfTransitions()+1); i++){
		_transitionArray[i]=other.customGetTransition(i);
	}
}

Automaton::Automaton(Automaton&& other)
{


	_stateArraySize = (other.numberOfStates()+1);
	_transitionArraySize = (other.numberOfTransitions()+1);
	_automatonName=other.getName();
	_stateArray = new State*[_stateArraySize];
	_transitionArray = new Transition*[_transitionArraySize];


	//adding all the state
	for(int i=0; i<(other.numberOfStates()+1); i++){
		_stateArray[i]=other.customGetState(i);

	}

	for(int i=0; i<(other.numberOfTransitions()+1); i++){
		_transitionArray[i]=other.customGetTransition(i);
	}

	other.~Automaton();
}


//investigate why this cause dynamic array deletion to fail
Automaton::~Automaton() 
{
	if(_stateArray)
	delete [] _stateArray;

	if(_transitionArray)
	delete [] _transitionArray;
}

void Automaton::setName(const std::string& name)
{
	_automatonName = name;
}

std::string Automaton::getName() const
{
	std::string name = _automatonName;
	return name;
}

bool Automaton::addState(const std::string& stateName, State*& state)
{
	//check the automaton for the state, if exists return false

	if (_stateArraySize>1){
		for(int i =0; i<(_stateArraySize-1); i++){
			if (_stateArray[i]->getName()==stateName) //error line
				return false;
		}
	}
	//create the new state on the heap
	State *createdState = new State(stateName);

	_stateArray[(_stateArraySize-1)] = createdState;
	state = createdState;

	State** temp = new State*[(_stateArraySize+1)];

	for(int i =0; i<_stateArraySize; i++){
			temp[i]=_stateArray[i];

	}
	delete [] _stateArray;

	_stateArray = temp;

	_stateArraySize = _stateArraySize+1;

	return true;
}

bool Automaton::getState(const std::string& stateName, State*& state)
{
	for (int i=0; i< (_stateArraySize-1); i++){
		if(_stateArray[i]->getName()==stateName){
			state = _stateArray[i];
			return true;
		}
	}
	return false;
}

bool Automaton::getState(int i, State*& st)
{
	if (_stateArraySize < (i))
		return false;

	if (_stateArray[i] == nullptr)
		return false;

	st = _stateArray[i];

	return true;
}

bool Automaton::getState(int i, const State*& st) const
{
	if (_stateArraySize < (i))
		return false;

	if (_stateArray[i] == nullptr)
		return false;

	st = _stateArray[i];

	return true;
}

State* Automaton::customGetState(int location){

	if (_stateArraySize < (location))
		return nullptr;

	if (_stateArray[location] == nullptr)
		return nullptr;

	State* temp = _stateArray[location];
	return temp;
}

State* Automaton::customGetState(int location) const{

	if (_stateArraySize < (location))
		return nullptr;

	if (_stateArray[location] == nullptr)
		return nullptr;

	State* temp = _stateArray[location];
	return temp;
}

int Automaton::numberOfStates() const 
{
	int i = (_stateArraySize-1);
	return i;
}

bool Automaton::addTransition(const std::string& nameSt1, const std::string& nameSt2,
		Transition*& trans)
{
	State* tempState1;
	State* tempState2;
	State* temp;

	if(_transitionArraySize>1){
		for(int i=0; i<(_transitionArraySize-1); i++){

			_transitionArray[i]->getState1(tempState1);
			_transitionArray[i]->getState2(tempState2);

			if (tempState1->getName()==nameSt1)
				return false;

			if(tempState2->getName()==nameSt2)
				return false;
		}
	}
	//checking if states exist

	tempState1 = nullptr;
	tempState2 = nullptr;

	for(int i=0; i<(_stateArraySize-1); i++){
		if(_stateArray[i]->getName()==nameSt1)
			tempState1=_stateArray[i];
	}

	if(tempState1==nullptr)
		return false;

	for(int i=0; i<(_stateArraySize-1); i++){
		if(_stateArray[i]->getName()==nameSt2)
			tempState2=_stateArray[i];
	}

	if(tempState2==nullptr)
		return false;



	//if all checks pass, create the new state
	Transition *createdTransition = new Transition(tempState1,tempState2);
	trans=createdTransition;
	_transitionArray[(_transitionArraySize-1)]= createdTransition;


		Transition** tempArray = new Transition*[(_transitionArraySize+1)];

		for(int i =0; i<_transitionArraySize; i++){
				tempArray[i]=_transitionArray[i];
		}

		delete [] _transitionArray;

		_transitionArray = tempArray;

		_transitionArraySize = _transitionArraySize+1;


	return true;
}

bool Automaton::getTransition(const std::string& nameSt1, const std::string& nameSt2,
		Transition*& trans)
{
	// implement me
	return false;
}

bool Automaton::getTransition(int location,Transition*& trans) 
{
	if (_transitionArraySize < (location))
		return false;

	if (_transitionArray[location] == nullptr)
		return false;

	trans = _transitionArray[location];

	return true;
}

bool Automaton::getTransition(int location,const Transition*& trans) const
{
	if (_transitionArraySize < (location))
		return false;

	if (_transitionArray[location] == nullptr)
		return false;

	trans = _transitionArray[location];

	return true;
}

Transition* Automaton::customGetTransition(int location){

	if (_transitionArraySize < (location))
		return nullptr;

	if (_transitionArray[location] == nullptr)
		return nullptr;

	Transition* temp = _transitionArray[location];
	return temp;
}

Transition* Automaton::customGetTransition(int location) const{

	if (_transitionArraySize < (location))
		return nullptr;

	if (_transitionArray[location] == nullptr)
		return nullptr;

	Transition* temp = _transitionArray[location];
	return temp;
}

int Automaton::numberOfTransitions() const
{
	int i = (_transitionArraySize-1);
	return i;
}

void Automaton::print(std::ostream& stream) const
{
	stream << "Automaton(" << getName() << "):" << std::endl;
	if (numberOfStates()>0) {
		stream << "States:" << std::endl;
		for (int i=0 ; i< numberOfStates() ; i++) {
			const State* s=nullptr;
			getState(i,s);
			stream << *s << std::endl;
		}

		if (numberOfTransitions()>0) {
			stream << "Transitions:" << std::endl;
			for (int j=0 ; j<numberOfTransitions() ; j++) {
				const Transition* t=nullptr;
				getTransition(j,t);
				stream << *t << std::endl;
			}
		}
	}
}

Automaton& Automaton::operator=(const Automaton& other)
{

	_stateArraySize = (other.numberOfStates()+1);
		_transitionArraySize = (other.numberOfTransitions()+1);
		_automatonName=other.getName();
		_stateArray = new State*[_stateArraySize];
		_transitionArray = new Transition*[_transitionArraySize];



		//adding all the state
		for(int i=0; i<(other.numberOfStates()+1); i++){
			_stateArray[i]=other.customGetState(i);

		}

		for(int i=0; i<(other.numberOfTransitions()+1); i++){
			_transitionArray[i]=other.customGetTransition(i);
		}

	return *this;
}

Automaton& Automaton::operator=(Automaton&& other)
{
	_stateArraySize = (other.numberOfStates()+1);
		_transitionArraySize = (other.numberOfTransitions()+1);
		_automatonName=other.getName();
		_stateArray = new State*[_stateArraySize];
		_transitionArray = new Transition*[_transitionArraySize];



		//adding all the state
		for(int i=0; i<(other.numberOfStates()+1); i++){
			_stateArray[i]=other.customGetState(i);

		}

		for(int i=0; i<(other.numberOfTransitions()+1); i++){
			_transitionArray[i]=other.customGetTransition(i);
		}

	return *this;
}

bool Automaton::operator==(const Automaton& other) const
{

	if (other.getName()!=_automatonName)
		return false;

	if(other.numberOfStates()!=numberOfStates())
		return false;

	if(other.numberOfTransitions()!=numberOfTransitions())
		return false;

	for (int i = 0; i<other.numberOfStates(); i++){
		if(other.customGetState(i)!=_stateArray[i])
			return false;
	}

	for (int i = 0; i<other.numberOfTransitions(); i++){
		if(other.customGetTransition(i)!=_transitionArray[i])
			return false;
	}

	return true;
}

bool Automaton::operator!=(const Automaton& other) const
{
	if (other.getName()==_automatonName)
		return false;

	if(other.numberOfStates()==numberOfStates())
		return false;

	if(other.numberOfTransitions()==numberOfTransitions())
		return false;

	for (int i = 0; i<other.numberOfStates(); i++){
		if(other.customGetState(i)==_stateArray[i])
			return false;
	}

	for (int i = 0; i<other.numberOfTransitions(); i++){
		if(other.customGetTransition(i)==_transitionArray[i])
			return false;
	}

	return true;
}

std::ostream& operator<<(std::ostream& stream, const Automaton& aut)
{
	aut.print(stream);
	return stream;
}

