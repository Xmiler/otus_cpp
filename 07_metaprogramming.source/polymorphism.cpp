#include <iostream>
#include <list>
#include <memory>
#include <mutex>

namespace inheritance {

	struct IThreadStrategy {
		virtual void lock() = 0;
		virtual void unlock() = 0;
	};

	struct SingleThreadStrategy : public IThreadStrategy {
		void lock() override {
			// do nothing here
		}

		void unlock() override {
			// do nothing here
		}
	};

	struct MultyThreadStrategy : public IThreadStrategy {
		void lock() override {
			m_mutex.lock();
		}

		void unlock() override {
			m_mutex.unlock();
		}

	private:
		std::mutex m_mutex;
	};

	template<typename T>
	struct Stack {
	public:
		void push(const T& value) {
			m_data.push_back(value);
		}

		T pop() {
			T value = m_data.front();
			m_data.pop_front();
			return value;
		}

	private:
		std::list<T> m_data;
	};


	template<typename T>
	struct StackSingleThread : private SingleThreadStrategy {
	public:
		void push(const T& value) {
			lock();
			m_data.push_back(value);
			unlock();
		}

		T pop() {
			lock();
			T value = m_data.front();
			m_data.pop_front();
			unlock();
			return value;
		}

	private:
		std::list<T> m_data;
	};


	template<typename T>
	struct StackMultyThread : private MultyThreadStrategy {
	public:
		void push(const T& value) {
			lock();
			m_data.push_back(value);
			unlock();
		}

		T pop() {
			lock();
			T value = m_data.front();
			m_data.pop_front();
			unlock();
			return value;
		}

	private:
		std::list<T> m_data;
	};


	void example() {
		std::cout << "inheritance::example" << std::endl;

		auto testStack = [](auto& stack) {
			for (int i = 0; i < 10; ++i) {
				stack.push(i);
			}
			for (int i = 0; i < 10; ++i) {
				std::cout << stack.pop() << ' ';
			}
			std::cout << std::endl;
		};

		std::cout << "singleThreadStack test:" << std::endl;
		StackSingleThread<int> singleThreadStack;
		testStack(singleThreadStack);
		std::cout << std::endl;

		std::cout << "threadSafeStack test:" << std::endl;
		StackMultyThread<int> threadSafeStack;
		testStack(threadSafeStack);
	}

}

namespace templates {

	struct SingleThreadStrategy {
		void lock() {
			// do nothing here
		}

		void unlock() {
			// do nothing here
		}
	};

	struct MultyThreadStrategy {
		void lock() {
			m_mutex.lock();
		}

		void unlock() {
			m_mutex.unlock();
		}

	private:
		std::mutex m_mutex;
	};


	template<typename T,
		typename ThreadStrategy = SingleThreadStrategy>
	struct Stack {
	public:
		void push(const T& value) {
			m_threadStrategy.lock();

			m_data.push_back(value);

			m_threadStrategy.unlock();
		}

		T pop() {
			m_threadStrategy.lock();

			T value = m_data.front();
			m_data.pop_front();

			m_threadStrategy.unlock();
			return value;
		}

	private:
		ThreadStrategy m_threadStrategy;
		std::list<T> m_data;
	};

	// Or just Stack<T> because of default template parameter value
	template<typename T>
	using StackSingleThread = Stack<T, SingleThreadStrategy>;

	template<typename T>
	using StackMultyThread = Stack<T, MultyThreadStrategy>;

	void example() {
		std::cout << "templates::example" << std::endl;

		auto testStack = [](auto& stack) {
			for (int i = 0; i < 10; ++i) {
				stack.push(i);
			}
			for (int i = 0; i < 10; ++i) {
				std::cout << stack.pop() << ' ';
			}
			std::cout << std::endl;
		};

		std::cout << "singleThreadStack test:" << std::endl;
		
		StackSingleThread<int> singleThreadStack;
		testStack(singleThreadStack);
		std::cout << std::endl;

		std::cout << "threadSafeStack test:" << std::endl;
		StackMultyThread<int> threadSafeStack;
		testStack(threadSafeStack);
	}

}

namespace compare {

	// What if:
	// 1. We have several different strategies?
	// - Thread safety: SingleThread, MultyThread (or even TwoThreads or SingleProducerSingleConsumer)
	// - memory allocation: std::allocator, user-defined allocator, some special allocator
	// - something else
	namespace templates {
		// Templates:
		template<typename T,
			typename ThreadSafetyPolicy,
			typename Allocator
			// , typename ... somthing else
			>
		struct Stack {};

		// Looks good!
		// Stack<int, SingleThread, std::allocator/*...*/>
	}


	// inheritance
	namespace inheritance {

		struct SingleThread {};
		struct MultyThread {};
		struct UserAllocator {};
		struct SpecialAllocator {};

		struct Stack : private SingleThread, private UserAllocator /*....*/ {
		};

		struct Stack2 : private SingleThread, private SpecialAllocator /*....*/ {
		};

		struct Stack3 : private MultyThread, private SpecialAllocator /*....*/ {
		};

		// ...
		// Looks not so good

		// But!

		struct IThreadSafetyPolicy {};
		struct IAllocator {};

		template<typename T>
		struct Stack4 {
			public:
				Stack4(
					IThreadSafetyPolicy* thr_policy,
					IAllocator* allocator
					// something else
				) {}
			private:
				std::unique_ptr<IThreadSafetyPolicy> m_thr_policy;
				std::unique_ptr<IAllocator> m_allocator;
		};

		// Also good
	}
}


int main() {

	inheritance::example();

	std::cout << std::endl << std::endl;

	templates::example();

	return 0;
}