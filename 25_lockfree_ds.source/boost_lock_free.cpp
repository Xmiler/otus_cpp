#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/stack.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/lockfree/policies.hpp>
#include <thread>
#include <iostream>

void spsc_queue_test() {
    std::cout << "\nspsc_queue_test\n";

    // boost::lockfree::spsc_queue<int> queue{100};
    boost::lockfree::spsc_queue<
        int,
        boost::lockfree::capacity<100>
    > queue;
    int sum = 0;

    auto produce = [&queue]() {
        for (int i = 1; i <= 100; ++i)
          queue.push(i);
    };

    auto consume = [&queue, &sum]() {
        int i;
        while (queue.pop(i))
            sum += i;
    };

    std::thread t1{produce};
    std::thread t2{consume};
    t1.join();
    t2.join();

    std::cout << sum << std::endl;
}



void queue_test() {
    std::cout << "\nqueue_test\n";

    boost::lockfree::queue<int> queue{100};
    std::atomic<int> sum{0};

    auto produce = [&queue]() {
        for (int i = 1; i <= 100; ++i)
          queue.push(i);
    };

    auto consume = [&queue, &sum]() {
        int i;
        while (queue.pop(i))
            sum += i;
    };

    std::thread t1{produce};
    std::thread t2{consume};
    std::thread t3{consume};
    t1.join();
    t2.join();
    t3.join();

    std::cout << sum << std::endl;
}


void stack_test() {
    std::cout << "\nstack_test\n";

    boost::lockfree::stack<int> stack{100};
    std::atomic<int> sum{0};

    auto produce = [&stack]() {
        for (int i = 1; i <= 100; ++i)
          stack.push(i);
    };

    auto consume = [&stack, &sum]() {
        int i;
        while (stack.pop(i))
            sum += i;
    };

    std::thread t1{produce};
    std::thread t2{consume};
    std::thread t3{consume};
    t1.join();
    t2.join();
    t3.join();

    std::cout << sum << std::endl;

}


int main()
{
    spsc_queue_test();
    queue_test();
    stack_test();

    return 0;
}