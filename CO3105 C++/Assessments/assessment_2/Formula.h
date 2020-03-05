/*
 * Formula.h
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */


#include <string>
#include <iosfwd>

#ifndef FORMULA
#define FORMULA 1

#include "Assignment.h"

// This exercise implements a more complicated hierarchy of Boolean Formulas
// The hierarchy consists of
// Formula
//   |
//   -----------------------------------------
//   |              |            |           |
//   UnaryOperator Constant Variable BinaryOperator
//   |                                       |
//   Not                                     ------
//                                           |    |
//                                           And  Or
//
// Overall, this (together with the file BoolFormula that is supplied)
// creates a utility for evaluating and manipulating Boolean Formulas.
//
// A Boolean formula is a formula composed from the constants
// "true" and "false", "variables", and operators "and", "or", and "not".
//
// For example, "(true and false)" or "(not (true or false))".
//
// You will create the main class that implements the Formula by creating
// the different types of formulas all inheriting from Formula.
// The functions that apply to these Boolean formulas are explained below.
//
// As before, you should add the virtual keyword where appropriate and then implement the functions
// where they are most appropriate.
// Formula, BinaryOperator, and UnaryOperator could be an abstract class but all other classes should be
// concrete classes.
//
// The included classes are:
// Formula - base class
// Constant - either true or false
// Variable - a Boolean variable to be given a value by an assignment
// BinaryOperator - an operator that has two operands
// UnaryOperator - an operator that has one operand
// And, Or, and Not - operators
class Formula {
public:
  Formula();
  Formula(const Formula& other) = delete;
  Formula(Formula&& other) = delete;
  virtual ~Formula();

  // Returns true if the formula is valid and false otherwise
  //
  bool valid() const;

  // Evaluates whether the formula is true or false
  // If variables appear in the formula their value should
  // be given in the parameter assignment.
  // If it is not, then the value for that variable can be
  // arbitrary
  virtual bool evaluate(const Assignment&) const;

  // prints the function to the ostream
  // The format should look like these examples:
  // (T and F)
  // (not (F or (T and F)))
  // (T and (T and (T and (X or Y))))
  //
  // T and F stand for true and false
  // X and Y are variables
  // Every or, and, and not is enclosed by parenthesis.
  // There cannot be redundant parenthesis.
  // This format is also read by the BoolFormula reader
  void print(std::ostream&) const;

  // returns the name of the class:
  // not, and, or, T/F, variable name
  std::string name() const;

  // Returns a pointer to a deep copy
  virtual Formula* copy() const;

  // Returns a copy to a formula that is the negation
  // of the given formula
  virtual Formula* negate() const;

  virtual std::string getOutString();
protected:
  std::string formulaName_;
  std::string outString_;
private:
  // Add private members
};

class Constant : public Formula {
public:
  Constant() = delete;
  Constant(bool);
  Constant(const Constant&) = delete;
  Constant(Constant&&) = delete;
  ~Constant();

  Formula* negate() const;

  bool evaluate(const Assignment&) const;

  Formula* copy() const;
protected:
  bool constantValue_;
private:
  // Add private members
};

class Variable : public Formula {
public:
  Variable() = delete;
  Variable(const Variable&) = delete;
  Variable(Variable&&) = delete;

  Variable(const std::string& name);
  ~Variable();

  Formula* negate() const;
  bool evaluate(const Assignment& assignmentValues) const;

  Formula* copy() const;

protected:
private:
  // Add private members
};

class BinaryOperator : public Formula {
public:
  BinaryOperator() = delete;
  BinaryOperator(const BinaryOperator&) = delete;
  BinaryOperator(BinaryOperator&&) = delete;

  BinaryOperator(Formula*, Formula*);

  ~BinaryOperator();

protected:
  Formula* leftValue_;
  Formula* rightValue_;
private:
  // Add private members
};

class UnaryOperator : public Formula {
public:
  UnaryOperator() = delete;
  UnaryOperator(const UnaryOperator&) = delete;
  UnaryOperator(UnaryOperator&&) = delete;

  UnaryOperator(Formula*);

  virtual ~UnaryOperator();

protected:
  Formula* operandFormulaValue_;
private:
  // Add private members
};

class And : public BinaryOperator {
public:
  And() = delete;
  And(const And&) = delete;
  And(And&&) = delete;

  And(Formula*, Formula*);

  ~And();

  Formula* negate() const;

  bool evaluate(const Assignment& assigned) const;

  Formula* copy() const;
protected:
  // Add protected members
private:
  // Add private members
};

class Or: public BinaryOperator {
public:
  Or() = delete;
  Or(const Or&) = delete;
  Or(Or&&) = delete;

  Or(Formula*, Formula*);

  ~Or();

  Formula* negate() const;
  bool evaluate(const Assignment& assigned) const;

  Formula* copy() const;
protected:
  // Add protected members
private:
  // Add private members
};

class Not : public UnaryOperator {
public:
  Not() = delete;
  Not(const Not&) = delete;
  Not(Not&&) = delete;

  Not(Formula* operand);

  ~Not();

  Formula* negate() const;
  bool evaluate(const Assignment& assigned) const;

  Formula* copy() const;
protected:
private:
  // Add private members
};
  
#endif

