

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
	Node<T> * m_head;
public:
	void push(const T& data) {

		// 1.
		Node<T>* newNode = new Node<T>(data); // local data

		// 2.
		newNode->next = m_head;	// common data reading

		// 3.
		m_head = newNode; // common data modification
	}
};

int main() {

	return 0;
}