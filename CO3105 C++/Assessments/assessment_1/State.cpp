#include <string>
#include <sstream>
#include <iostream>
//#include <cstdlib>
#include "State.h"

using std::string;
using std::ostream;
using std::endl;
using std::cout;


State::State()
{
	TransSize=1;
	LabelSize=1;
	_stringArray=new string[LabelSize];
	_stringArray[0]="";
	_transitionArray=new Transition*[TransSize];
	_stateName="";



}  

State::State(const string& name) {
	TransSize=1;
	LabelSize=1;

	_stringArray=new std::string[LabelSize];
	_transitionArray=new Transition*[TransSize];
	_stringArray[0]="";
	_stateName = name;
}

State::State(const State& other) {

	TransSize=(other.numberOfTransitions()+1);
		LabelSize=(other.numberOfLabels()+1);
		_stringArray=new std::string[LabelSize];
		_transitionArray=new Transition*[TransSize];

		_stateName= other.getName();
		_copy(other);

}

void State::_copy(const State& other){

	TransSize=(other.numberOfTransitions()+1);
	LabelSize=(other.numberOfLabels()+1);
	_stringArray=new std::string[LabelSize];
	_transitionArray=new Transition*[TransSize];

	_stateName= other.getName();
	string stringHolder;



	for (int i =0; i<other.numberOfTransitions(); i++){
		_transitionArray[i]=other.customGetTransition(i);

	}



	for (int i=0; i<other.numberOfLabels(); i++){
		other.getLabel(i, stringHolder);
		_stringArray[i]=stringHolder;
	}
}




State::State(State&& other) {

	TransSize=(other.numberOfTransitions()+1);
	LabelSize=(other.numberOfLabels()+1);

	_stringArray=new std::string[LabelSize];
	_transitionArray=new Transition*[TransSize];
	Transition* tranHolder;
	string stringHolder;

	//copying transitions
	for (int i =0; i<other.numberOfTransitions(); i++){
		other.getTransition(i, tranHolder);
		_transitionArray[i]=tranHolder;
	}

	//copying labels
	for (int i=0; i<other.numberOfLabels(); i++){
		other.getLabel(i, stringHolder);
		_stringArray[i]=stringHolder;
	}

	_stateName=other.getName();

	other.~State();
}

State::~State()
{
	delete [] _stringArray;
	delete [] _transitionArray;
}

void State::setName(const string& name) 
{
	_stateName=name;
}

string State::getName() const 
{
  return _stateName;
}

bool State::addTransition(Transition* trans) 
{
	//checking if trans pointer is null
	if(trans==nullptr)
		return false;

	//assigning temp local states and checking if state 1 is this state
	State* transTest1;
	State* transTest2;

	trans->getState1(transTest1);
	trans->getState2(transTest2);

	if(transTest1!=this)
		return false;

	//checking if transitions exist by comparing memory location of state2
	//from trans and stored transitions
	if(TransSize>1){
		for (int i=0; i<(TransSize-1); i++){
			State* test2;
			Transition* transTest=_transitionArray[0];
			transTest->getState1(test2);

			if(test2==transTest2)
				return false;
		}
	}

	//adding *value to the array of pointers
	_transitionArray[(TransSize-1)]=trans;

	//increase size of array using newTransArray
	Transition** newTransArray=new Transition*[(TransSize+1)];

	for (int i=0; i<TransSize; i++){
		newTransArray[i]=_transitionArray[i];
	}

	delete [] _transitionArray;
	_transitionArray=newTransArray;


	TransSize=TransSize+1;
	return true;
}

bool State::getTransition(const string& targetStateName, Transition*& result)
{
	State* stateTemp;
	Transition* transTemp;

	for(int i=0; i<(TransSize-1); i++){
		transTemp=_transitionArray[i];
		transTemp->getState2(stateTemp);

		if(stateTemp->getName()==targetStateName){
			result = _transitionArray[i];
			return true;
		}
	}

  return false;
}

bool State::getTransition(const string& targetStateName, const Transition*& result) const
{
	State* stateTemp;
	Transition* transTemp;

	for(int i=0; i<(TransSize-1); i++){
		transTemp=_transitionArray[i];
		transTemp->getState2(stateTemp);

		if(stateTemp->getName()==targetStateName){
			result = _transitionArray[i];
			return true;
		}
	}

  return false;
}
bool State::getTransition(int location, Transition*& result)
{

	if (location>TransSize)
		return false;

	if (_transitionArray[location]==0)
		return false;

	result=_transitionArray[location];

    return true;
}

Transition* State::customGetTransition(int location) const{

	if (location>TransSize)
		return nullptr;

	if (_transitionArray[location]==0)
		return nullptr;

	Transition* output = _transitionArray[location];

	return output;
}

Transition* State::customGetTransition(int location){

	if (location>TransSize)
		return nullptr;

	if (_transitionArray[location]==0)
		return nullptr;

	Transition* output = _transitionArray[location];

	return output;
}

bool State::getTransition(int location, const Transition*& result) const
{
	if (location>TransSize)
		return false;

	if (_transitionArray[location]==0)
		return false;

	result=_transitionArray[location];

    return true;
}

int State::numberOfTransitions() const 
{

	return (TransSize-1);
}

bool State::addLabel(const string& label) 
{

	for (int i=0; i<(LabelSize-1);i++){
		if (_stringArray[i]==label)
			return false;
	}

	_stringArray[(LabelSize-1)]=label;

	string *newStringArray = new string[(LabelSize+1)];

	for (int i=0; i<LabelSize; i++){
		newStringArray[i]=_stringArray[i];
	}

	delete [] _stringArray;
	_stringArray=newStringArray;

	_stringArray[LabelSize]="";
	LabelSize=LabelSize+1;

  return true;
}

int State::numberOfLabels() const
{

	return (LabelSize-1);
}

bool State::getLabel(int location, string& label) const
{
	if(location>LabelSize)
		return false;

	if (_stringArray[location]=="")
		return false;

	label=_stringArray[location];

    return true;
}

State& State::operator=(const State& other)
{

	if (&other != this){
		delete [] _stringArray;
		delete [] _transitionArray;
	}

	_copy(other);

	return *this;
}

State& State::operator=(State&& other)
{
	if (&other != this){
		delete [] _stringArray;
		delete [] _transitionArray;
	}

	_copy(other);

	return *this;
}



bool State::operator==(const State& other) const {

	string temp;

	if (_stateName!=other.getName())
		return false;

	if (other.numberOfLabels()!=numberOfLabels())
		return false;

	if (other.numberOfTransitions()!=numberOfTransitions())
		return false;

	for(int i=0; i<numberOfTransitions(); i++){
		if(other.customGetTransition(i)!=_transitionArray[i])
			return false;
	}

	for(int i=0; i<numberOfLabels(); i++){
		other.getLabel(i, temp);
		if(temp!=_stringArray[i])
			return false;
	}

    return true;
}

void State::print(ostream& stream) const
{
  bool first = true;
  stream << getName() << "(";
 
  for (int i=0 ; i<this->numberOfLabels() ; i++) {
    if (first) {
      first = false;
    }
    else {
      stream << ",";
    }
    string s;
    getLabel(i,s);
    stream << s;
  }
  stream << ")";
}

ostream& operator<< (ostream& stream, const State& st) 
{
  st.print(stream);
  return stream;
}

