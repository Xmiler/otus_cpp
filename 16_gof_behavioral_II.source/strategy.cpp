// Стратегия (Strategy)

#include <iostream>
#include <mutex>
#include <stack>

#include <cassert>

namespace thread_safety_strategy {

    class IThreadSafeStrategy {
    public:
        virtual ~IThreadSafeStrategy() = default;

        virtual void lock() = 0;
        virtual void unlock() = 0;
    };

    template<typename T>
    struct Stack {
    public:
        // 1. Set the strategy
        Stack(std::unique_ptr<IThreadSafeStrategy> strategy)
            : m_threadSafetyStrategy{std::move(strategy)}
        {
            assert(m_threadSafetyStrategy);
        }

        void push(const T& value) {
            // 3. Use the strategy
            m_threadSafetyStrategy->lock();
            m_impl.push(value);
            m_threadSafetyStrategy->unlock();
        }

    private:
        std::stack<T> m_impl;
        std::mutex mMut;
        // 2. Save the strategy
        std::unique_ptr<IThreadSafeStrategy> m_threadSafetyStrategy;
    };


    class MutexThreadSafeStrategy : public IThreadSafeStrategy {
    public:
        void lock() override {
            std::cout << "MutexThreadSafeStrategy::lock()" << std::endl;
            m_mutex.lock();
        }
        void unlock() override {
            m_mutex.unlock();
            std::cout << "MutexThreadSafeStrategy::unlock()" << std::endl;
        }
    private:
        std::mutex m_mutex;
    };

    void example() {
        std::cout << "thread_safety_strategy::example:" << std::endl;

        Stack<int> stack{
            std::make_unique<MutexThreadSafeStrategy>()
        };

        stack.push(42);
        stack.push(50);

        std::cout << std::endl << std::endl;
    }

    namespace templates {

        // This is a template interface specification
        class SingleThreadStrategy {
        public:
            void lock() {
                std::cout << "SingleThreadStrategy::lock()" << std::endl;
                // do nothing here
            }

            void unlock() {
                std::cout << "SingleThreadStrategy::unlock()" << std::endl;
                // do nothing here
            }
        };

        class MutexBasedStrategy {
        public:
            void lock() {
                std::cout << "MutexBasedStrategy::lock()" << std::endl;
                m_mutex.lock();
            }

            void unlock() {
                m_mutex.unlock();
                std::cout << "MutexBasedStrategy::unlock()" << std::endl;
            }
        private:
            std::mutex m_mutex;
        };

        //                                   Set the strategy
        template<typename T, typename ThreadSafeStrategy = SingleThreadStrategy>
        class Stack {
        public:
            void push(const T& value) {
                // 3. Use the strategy
                m_threadSafetyStrategy.lock();

                m_impl.push(value);

                m_threadSafetyStrategy.unlock();
            }
        private:
            std::stack<T> m_impl;
            // 2. Save the strategy
            ThreadSafeStrategy m_threadSafetyStrategy;
        };


        void example() {
            std::cout << "thread_safety_strategy::templates::example:" << std::endl;

            Stack<int, SingleThreadStrategy> noThreadSafeStack;

            noThreadSafeStack.push(42);
            noThreadSafeStack.push(24);

            Stack<int, MutexBasedStrategy> mutexBasedStack;

            mutexBasedStack.push(42);
            mutexBasedStack.push(24);

            Stack<int, MutexThreadSafeStrategy> mutexBasedStack2;

            mutexBasedStack2.push(42);
            mutexBasedStack2.push(24);

            std::cout << std::endl << std::endl;
        }

    }

}

namespace randomize {

    class Generator {
    public:
        virtual size_t seed(size_t seed_) = 0;
    };

    class HardwareGenerator : public Generator {
    public:
        size_t seed(size_t) override {
            std::cout << "generate using mac address" << std::endl;
            return 42;
        }
    };

    class SoftwareGenerator : public Generator {
    public:
        size_t seed(size_t) override {
            std::cout << "generate using software emulator" << std::endl;
            return 0;
        }
    };

    class Shuffle {
    public:
        explicit Shuffle(std::unique_ptr<Generator> gen_) 
            : m_gen{std::move(gen_)} 
        {
            assert(m_gen);
        }

        size_t seed(size_t seed_) {
            return m_gen->seed(seed_);
        }

    private:
        std::unique_ptr<Generator> m_gen;
    };

    void example() {
        std::cout << "random::example" << std::endl;

        auto ptr = std::make_unique<Shuffle>(std::make_unique<HardwareGenerator>());
        ptr->seed(0);

        std::cout << std::endl << std::endl;
    }

}

int main(int, char *[]) {

    thread_safety_strategy::example();
    thread_safety_strategy::templates::example();

    randomize::example();

    return 0;
}
