#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include <string>
#include "stack.h"

using namespace std;
using namespace cop4530;

bool strIsInt(string str);
bool strIsFloat(string str);
bool strIsVariable(string str);
bool strIsOperator(string str);
int opPres (string str);

int main()
{
	
	// Part 1: Convert infix arithmetic expressions into postfix arithmetic expressions

	Stack<string> postfixStack;	// postfix stack of tokens, as strings
	Stack<string> pfStack;		// copy of ^
	Stack<string> operators;	// temporarily holds the operators before being added to the postfix stack
	Stack<string> eval;		// used when evaluation of postfix
	string inStr;
	string token;
	bool errors;
	bool containsFloat;
	bool containsVar;

	getline(cin, inStr);

while(inStr != "exit")
{
	stringstream ss(inStr);

	postfixStack.clear();
	pfStack.clear();
	operators.clear();
	eval.clear();
	errors = false;
	containsFloat = false;
	containsVar = false;

	while (ss >> token)
	{
		if ( strIsFloat(token) )
			containsFloat = true;	// will help with the evaluation
		if ( strIsVariable(token) )
			containsVar = true;	// ^ ditto
		
		if ( strIsInt(token) || strIsFloat(token) || strIsVariable(token) )
			postfixStack.push(token);
		else if ( token == "(" )
			operators.push(token);
		else if ( strIsOperator(token) )
		{
			while ( !operators.empty() && operators.top() != "(" && ( opPres(operators.top()) >= opPres(token) ) )
			{
				postfixStack.push(operators.top());
				operators.pop();
			}
			operators.push(token);
		}
		else if ( token == ")" )
		{
			while ( operators.top() != "(" && !operators.empty())
			{
				postfixStack.push(operators.top());
				operators.pop();
			}
			if (operators.top() != "(")
				errors = true;
			else
				operators.pop();	// removes the (
		}
	}
	
	if ( token == "(" )
		errors = true;	// this means last thing from input was an opening paranthesis

	while (!operators.empty())
	{
		postfixStack.push(operators.top());
		operators.pop();
	}
	

	// Part 2: Convert postfix to an evaluation

	int IntEval = 0;
	float FloatEval = 0;
	Stack<string> temp = postfixStack;

	while (!temp.empty())
	{
		pfStack.push(temp.top());
		temp.pop();
	}

	float f1,f2;
	int n1,n2;
	
	
	if (!containsVar)
	{
		if (!containsFloat)
		{
			while (!pfStack.empty())
			{
				token = pfStack.top();
				pfStack.pop();

				if ( strIsInt(token) )
					eval.push(token);
				else			// operands
				{
					if (eval.size() <= 1)
						errors = true;
					else
					{
						n1 = stoi(eval.top());
						eval.pop();
						
						n2 = stoi(eval.top());
						eval.pop();
						
						if (token == "+")
							eval.push(to_string(n2 + n1));
						if (token == "-")
							eval.push(to_string(n2 - n1));
						if (token == "*")
							eval.push(to_string(n2 * n1));
						if (token == "/")
							eval.push(to_string(n2 / n1));
					}
				}
			}
			if (eval.size() == 1)
				IntEval = stoi(eval.top());
			else
				errors = true;
		}
		else
		{
			while (!pfStack.empty())
			{
				token = pfStack.top();
				pfStack.pop();
				
				if ( strIsInt(token) || strIsFloat(token) )
					eval.push(token);
				else			// operands
				{
					if (eval.size() <= 1)
						errors = true;
					else
					{
						f1 = stof(eval.top());
						eval.pop();
						
						f2 = stof(eval.top());
						eval.pop();
						
						if (token == "+")
							eval.push(to_string(f2 + f1));
						if (token == "-")
							eval.push(to_string(f2 - f1));
						if (token == "*")
							eval.push(to_string(f2 * f1));
						if (token == "/")
							eval.push(to_string(f2 / f1));
					}
				}
			}
			if (eval.size() == 1)
				FloatEval = stof(eval.top());
			else
				errors = true;

		}
	}

	
	if (!errors)
	{
		cout << "Postfix: " << postfixStack << endl;
		cout << "Evaluation: ";
		if (containsVar)
			cout << postfixStack << endl;
		else if (containsFloat)
			cout << FloatEval << endl;
		else
			cout << IntEval << endl;
	}
	else
		cout << "Errors were found. Postfix and evaluation not calculated" << endl;


	getline(cin, inStr);	// do not delete
}
}


// below are helper functions to determine type of token

bool strIsInt(string str)
{
	return (isdigit(str.front()) != 0 && str.find('.') == -1);
}

bool strIsFloat(string str)
{
	return (isdigit(str.front()) != 0 && str.find('.') != -1);
}

bool strIsVariable(string str)
{
	return (isalpha(str.front()) != 0);
}

bool strIsOperator(string str)
{
	return (str.front() == '+' || str.front() == '-' || str.front() == '*' || str.front() == '/');
}

int opPres (string str)
{
	if (str == "+" || str == "-")
		return 2;		// these values are arbitrary. i didnt do 1 and 0 or 1 and 2 cause i wasnt sure
					// if this would confuse the computer because i know 1 is used as true for true/false statements
	if (str == "*" || str == "/")
		return 3;
}
