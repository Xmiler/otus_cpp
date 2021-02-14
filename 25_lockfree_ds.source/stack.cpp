#include <atomic>
#include <iostream>

template <typename T>
struct Node {
	explicit Node(const T& d) 
		: data(d), next(nullptr) {

	}

	T data;
	Node* next;
};


template <typename T>
class Stack {
	using NodePtr = Node<T>*;
	std::atomic<NodePtr> m_head{nullptr};
public:
	void push(const T& data) {

		NodePtr newNode = new Node<T>(data); // local data

		newNode->next = m_head.load(std::memory_order_relaxed);

		while(
			!m_head.compare_exchange_weak(
				newNode->next,
				newNode,
				std::memory_order_release,
				std::memory_order_relaxed
			)
		);
		std::cout << "Head now is: " << m_head.load()->data << std::endl;
		if (m_head.load()->next)
			std::cout << "And next is: " << m_head.load()->next->data << std::endl;
	}

	// Ooopppps
	bool pop(T& result) {
		NodePtr prevHead = m_head.load();
		if (!prevHead) // not atomic; while ??
			return false;
		while (!m_head.compare_exchange_weak(prevHead, prevHead->next));
		result = prevHead->data;
		delete prevHead;
		return true;
	}
};

int main() {

	Stack<int> values;

	int stub = 142;
	values.pop(stub);
	std::cout << stub << std::endl;

	values.push(0);
	values.push(1);
	values.push(2);
	values.push(3);

	int value = 0;
	values.pop(value);
	std::cout << value << std::endl;

	values.pop(value);
	std::cout << value << std::endl;

	values.pop(value);
	std::cout << value << std::endl;

	values.pop(value);
	std::cout << value << std::endl;

	return 0;
}