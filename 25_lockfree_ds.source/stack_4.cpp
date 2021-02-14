#include <atomic>

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
	std::atomic<NodePtr> m_head;
public:
	void push(const T& data) {

		NodePtr newNode = new Node<T>(data); // local data

		newNode->next = m_head;

		while(
			m_head.compare_exchange_weak(
				newNode->next,
				newNode,
				std::memory_order_relaxed
			)
		);
	}
};

int main() {

	return 0;
}