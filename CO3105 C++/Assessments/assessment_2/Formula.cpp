/*
 * Formula.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */
#include <string>
#include <iostream>
#include"Formula.h"

using std::ostream;
using std::string;

Formula::Formula(){}

Formula::~Formula(){}

bool Formula::valid() const
{
	if (this==nullptr)
	return false;

	return true;
}

bool Formula::evaluate(const Assignment&) const
{
	return false;
}

void Formula::print(ostream& stream) const{
	stream << outString_;
}

string Formula::name() const
{
	return formulaName_;
}

std::string Formula::getOutString(){
	return outString_;
}

Formula* Formula::copy() const
{
	return nullptr;
}

Formula* Formula::negate() const
{
	return nullptr;
}

Constant::Constant(bool value)
{
	constantValue_ = value;


	if (value)
		formulaName_ = "T";
	else formulaName_="F";

	outString_ = formulaName_;
}

Constant::~Constant(){
	formulaName_ = "";
}

Formula* Constant::negate() const
{
	bool temp = constantValue_;
	Formula* negatedConst = new Not(new Constant(temp));

	return negatedConst;
}

bool Constant::evaluate(const Assignment&) const{
	if (constantValue_)
		return true;
	else return false;
}

Formula* Constant::copy() const
{
	Formula* constCopy = new Constant(constantValue_);
	return constCopy;
}

Variable::Variable(const string& name)
{
	formulaName_=name;
	outString_ = name;

}

Variable::~Variable(){
	formulaName_="";
}

Formula* Variable::negate() const{
	std::string tempVariable = formulaName_;
	Formula* negatedVar = new Not(new Variable(tempVariable));

	return negatedVar;
}

bool Variable::evaluate(const Assignment& assignmentValues) const{
	bool variableBool = false;
	variableBool =assignmentValues.operator ()(formulaName_);

	return variableBool;
}

Formula* Variable::copy() const
{
	Formula* VarCopy = new Variable(formulaName_);
	return VarCopy;
}

BinaryOperator::BinaryOperator(Formula* left, Formula* right) 
{
	leftValue_ = left;
	rightValue_ = right;
}

BinaryOperator::~BinaryOperator()
{
	leftValue_ = nullptr;
	rightValue_=nullptr;
}

UnaryOperator::UnaryOperator(Formula* operand)
{
	operandFormulaValue_ = operand;
}

UnaryOperator::~UnaryOperator()
{
	operandFormulaValue_ = nullptr;
}

And::And(Formula* left,Formula* right)
  : BinaryOperator(left,right){
	formulaName_= "and";
	outString_ = "("+left->getOutString()+" and "+right->getOutString()+")";
}

And::~And(){
	formulaName_="";
}

bool And::evaluate(const Assignment& assigned) const{
	if (leftValue_->evaluate(assigned) && (rightValue_->evaluate(assigned)))
		return true;
	else return false;

}

Formula* And::negate() const{
	Formula* tempLeft = leftValue_;
	Formula* tempRight = rightValue_;
	Formula* negatedAnd = new Not(new And(tempLeft,tempRight));

	return negatedAnd;
}

Formula* And::copy() const
{
	Formula* AndCopy = new And(leftValue_, rightValue_);
	return AndCopy;
}
Or::Or(Formula* left, Formula* right)
  : BinaryOperator(left,right){
	formulaName_= "or";
	outString_ = "("+left->getOutString()+" or "+right->getOutString()+")";


}

Or::~Or(){
	formulaName_="";
}

Formula* Or::negate() const{
	Formula* tempLeft = leftValue_;
	Formula* tempRight = rightValue_;
	Formula* negatedAnd = new Not(new Or(tempLeft,tempRight));

	return negatedAnd;
}

bool Or::evaluate(const Assignment& assigned) const{
	if (leftValue_->evaluate(assigned) || (rightValue_->evaluate(assigned)))
		return true;
	else return false;

}

Formula* Or::copy() const
{
	Formula* OrCopy = new Or(leftValue_, rightValue_);
	return OrCopy;
}

Not::Not(Formula* operand)
  : UnaryOperator(operand){

	formulaName_ = "not";
	outString_ = "(not "+ operandFormulaValue_->getOutString() +")";
}

Formula* Not::negate() const{
	Formula* tempOperand = operandFormulaValue_;
	Formula* negatedNot = new Not(new Not (tempOperand));

	return negatedNot;
}

Not::~Not()
{
	formulaName_="";
}

bool Not::evaluate(const Assignment& assigned) const{
	if (operandFormulaValue_->evaluate(assigned))
		return false;
	else return true;

}

Formula* Not::copy() const
{
	Formula* NotCopy = new Not(operandFormulaValue_);
	return NotCopy;
}
