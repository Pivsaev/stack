#include <iostream>
const int max = 1000;
template<typename T>
class TStack
{
	T arr[max];
	int top;
public:
	TStack();
	void add(T el);
	void udalit();
	int isempty();
	int isfull();
	T peek();
};

template<typename T>
TStack<T>::TStack() : top(-1) {}

template<typename T>
void TStack<T>::add(T el)
{
    if (!isfull()) {
        arr[++top] = el;
    }
}

template<typename T>
void TStack<T>::udalit()
{
    if (!isempty()) {
        top--;
    }
}

template<typename T>
int TStack<T>::isempty()
{
    return top == -1;
}

template<typename T>
int TStack<T>::isfull()
{
    return top == max - 1;
}

template<typename T>
T TStack<T>::peek()
{
    if (!isempty()) {
        return arr[top];
    }
    return T();
}
