#pragma once
using namespace std;

template<typename T>
class Node
{
public:
	Node<T>* next;
	Node<T>* previous;
	T value;

	Node(T value) {
		this->value = value;
		next = nullptr;
		previous = nullptr;
	}
	~Node() {}
};
