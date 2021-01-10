/*              STACK.HPP
        Ben Zech        10/22/2020
        All work below was written by Benjamin Zech. Do not steal
*/

// Private data used for Stack
// 
//	std::vector<T> theStack;
//
//	<vector> has lots of functions. Refer to them at:
/*
	https://www.cplusplus.com/reference/vector/vector/?kw=vector	
*/

template <typename T>
Stack<T>::Stack()
// zero-arguement constructor
{
	// nothing apparently
}

template <typename T>
Stack<T>::~Stack()
// destructor
{
	theStack.clear();
}

template <typename T>
Stack<T>::Stack(const Stack<T>& rhs)
// copy constructor
{
	theStack = rhs.theStack;
}

template <typename T>
Stack<T>::Stack(Stack<T> && rhs)
// move constructor
{
	theStack = std::move(rhs.theStack);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack <T>& rhs)
// copy assignment operator=
{
	theStack = rhs.theStack;
	return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> && rhs)
// move assignment operator=
{	
	theStack = std::move(rhs.theStack);
	return *this;
}

template <typename T>
bool Stack<T>::empty() const
// returns true if the Stack contains no elements, and false otherwise.
{
	return theStack.empty();
}

template <typename T>
void Stack<T>::clear()
// delete all elements from the stack
{
	theStack.clear();	
}

template <typename T>
void Stack<T>::push(const T& x)
// adds x to the Stack. copy version
{
	theStack.push_back(x);
}

template <typename T>
void Stack<T>::push(T && x)
// adds x to the Stack. move version
{
	theStack.push_back(std::move(x));
}

template <typename T>
void Stack<T>::pop()
// removes and discards the most recently added element of the Stack
{
	theStack.pop_back();
}

template <typename T>
T& Stack<T>::top()
// returns a reference to the most recently added element of the Stack
{
	if (size() == 0)
		return dummy;
	else
		return theStack.back();
}

template <typename T>
const T& Stack<T>::top() const
// accessor that returns the most recently added element of the Stack
{
	if (size() == 0)
		return dummy;
	else
		return theStack.back();
}

template <typename T>
int Stack<T>::size() const
// returns the number of elements stored in the Stack
{
	return theStack.size();
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
// print elements of the Stack to ostream os, with ofc as the delimeter
// NOTE: print should print elements in opposite order of the Stack (oldest element first, newest element last)
{
	if ( empty() )
		os << "The stack is empty";
	else
 	{
		typename std::vector<T>::const_iterator itr = theStack.begin();
		
		os << *itr;

		while (itr != --(theStack.end()) )
		{
			os << ofc;
			itr++;
			os << *itr;
		}
	}
}

// non member functions

template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a)
// invokes the print() method to print the Stack<T> a in the specified ostream
{
	a.print(os);
	return os;
}
        
template <typename T>
bool operator==(const Stack<T>& S1, const Stack<T>& S2)
// returns true if the two stacks have the same elements, in the same order. false otherwise
{
	return (S1.theStack == S2.theStack);
}
        
template <typename T>
bool operator!=(const Stack<T>& S1, const Stack<T>& S2)
// returns opposite of operator==()
{
	if (S1 == S2)
		return false;
	else
		return true;
}

template <typename T>
bool operator <=(const Stack<T>& a, const Stack<T>& b)
// returns true if every element in Stack a is smaller than or equal to the corresponding element of Stack b
//Note: that this means a cannot have more elements that b. if so, return false
{
	return (a.theStack <= b.theStack);
}
