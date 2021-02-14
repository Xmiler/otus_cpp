

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

		Node<T>* newNode = new Node<T>(data); // local data

		while(true) {
			Node<T>* oldHead = m_head;

			newNode->next = oldHead;

			// Check if something has changed
			if (m_head == oldHead) {
				m_head = newNode;
				break;
			}
		}
	}
};

int main() {

	return 0;
}