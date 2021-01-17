#include <future>
#include <iostream>
#include <mutex>


int do_something_very_interesting_and_long(int i) {
    return 42 + i;
}


void motivation() {
    std::thread worker1{do_something_very_interesting_and_long, 1};
    std::thread worker2{do_something_very_interesting_and_long, 2};

    // Where are my results??
    worker1.join();
    worker2.join();
}


void test1_async() {
    std::future<int> r1 = std::async(std::launch::async, do_something_very_interesting_and_long, 1);
    
    auto r2 = std::async(std::launch::deferred, do_something_very_interesting_and_long, 2);

    auto r3 = std::async(std::launch::deferred | std::launch::async, do_something_very_interesting_and_long, 3);
    
    std::cout << "Result1 = " << r1.get() << std::endl;
    std::cout << "Result2 = " << r2.get() << std::endl;
    std::cout << "Result3 = " << r3.get() << std::endl;
}

void test2_exception() {
    auto bad_worker = []() -> int {
        throw std::logic_error("Ooooops");
        return 42;
    };

    auto result = std::async(std::launch::deferred | std::launch::async, bad_worker);

    try {
        auto value = result.get();
    }
    catch(const std::exception& ex) {
        std::cout << "Exception! " << ex.what() << std::endl;
    }
}


int main() {

    test1_async();

    test2_exception();


    return 0;
}