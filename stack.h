/*		STACK.H
	Ben Zech	Assignment 3
	Bob Myers	Due: Thursday, October 22nd 11:59pm
*/

#include <iostream>
#include <vector>
#include <string>

namespace cop4530 {


template <typename T>
class Stack;
template <typename T>
	bool operator== (const Stack<T>& S1, const Stack<T>& S2);	// returns true if the two stacks have the same elements, in the same order. false otherwise

template <typename T>
	bool operator!=(const Stack<T>& S1, const Stack<T>& S2);	// returns opposite of operator==()

template <typename T>
	bool operator <=(const Stack<T>& a, const Stack<T>& b);	// returns true if every element in Stack a is smaller than or equal to the corresponding element of Stack b


template <typename T>
	class Stack {

		friend bool operator==<T> (const Stack<T>& S1, const Stack<T>& S2);	// returns true if the two stacks have the same elements, in the same order. false otherwise
	
		friend bool operator!=<T>(const Stack<T>& S1, const Stack<T>& S2);	// returns opposite of operator==()

		friend bool operator <=<T>(const Stack<T>& a, const Stack<T>& b);	// returns true if every element in Stack a is smaller than or equal to the corresponding element of Stack b
										//Note: that this means a cannot have more elements that b. if so, return false

	public:
		Stack();	// zero-arguement constructor
		~Stack();	// destructor
		Stack(const Stack<T>&);	// copy constructor
		Stack(Stack<T> &&);	// move constructor
		Stack<T>& operator=(const Stack <T>&);	// copy assignment operator=
		Stack<T>& operator=(Stack<T> &&);	// move assignment operator=
		bool empty() const;	// returns true if the Stack contains no elements, and false otherwise.
		void clear();	// delete all elements from the stack
		void push(const T& x);	// adds x to the Stack. copy version
		void push(T && x);	// adds x to the Stack. move version
		void pop();	// removes and discards the most recently added element of the Stack
		T& top();	// returns a reference to the most recently added element of the Stack
		const T& top() const;	// accessor that returns the most recently added element of the Stack
		int size() const;	// returns the number of elements stored in the Stack
		void print(std::ostream& os, char ofc = ' ') const;	// print elements of the Stack to ostream os, with ofc as the delimeter
		// NOTE: print should print elements in opposite order of the Stack (oldest element first, newest element last)
		
	private:
		std::vector<T> theStack;
		static T dummy;
	};

template <typename T>
T Stack<T>::dummy;	// initialize dummy

	// non member functions
	
	template <typename T>
		std::ostream& operator<<(std::ostream& os, const Stack<T>& a);	//  invokes the print() method to print the Stack<T> a in the specified ostream


#include "stack.hpp"

} // end of namespace 4530
