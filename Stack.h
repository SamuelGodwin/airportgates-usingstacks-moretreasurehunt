#ifndef STACK_H
#define STACK_H

#include "vector.h"
using pep::vector;
#include <string>
using std::string;

class Stack {

protected:
	vector<double> stack;
public:

	bool empty(){
		if (stack.size() ==0) {
			return true;
		}
		return false;
	}

	double pop() {
		// removes and returns the top element off the stack
		double temp = stack[stack.size() - 1];
		stack.pop_back();

		return temp;
	}

	void push(const double & input) {
		// takes a double and pushes it onto the stack
		stack.push_back(input);
	}
};

// outside of the Stack class
double evaluate(string text) { // string contains mathematical expression in RPN.
	vector<string> tokens;
	Stack stack;
	while(text.length() > 0){
		if(text.length() > 1){
			string::size_type position = text.find_first_of(' ');
			tokens.push_back(text.substr(0, position));
			text.erase(0, position+1);
			}else if(text.length() == 1){
			tokens.push_back(text);
			text = "";
			}
	}
	while(tokens.size() != 0) {
		if (tokens[0] == "+") {
			// pop two numbers a and b off stack
			double a = stack.pop();
			double b = stack.pop();
			// push (b + a) onto stack
			stack.push(b+a);
		}
		else if (tokens[0] == "-") {
			// pop two numbers a and b off stack
			double a = stack.pop();
			double b = stack.pop();
			// push (b - a) onto stack
			stack.push(b-a);
		}
		else if (tokens[0] == "*") {
			// pop two numbers a and b off stack
			double a = stack.pop();
			double b = stack.pop();
			// push (b * a) onto stack
			stack.push(b*a);
		}
		else if (tokens[0] == "/") {
			// pop two numbers a and b off stack
			double a = stack.pop();
			double b = stack.pop();
			// push (b / a) onto stack
			stack.push(b/a);
		}
		// casting string to a double
		else {stack.push(std::stod(tokens[0]));}
		// the token is a number: push onto stack
		tokens.erase(tokens.begin());
	}
	// after all tokens, answer is on top of stack
	// return answer
	return stack.pop();
}
// Do not write anything below this line
#endif
