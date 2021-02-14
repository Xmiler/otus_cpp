#include <atomic>
#include <iostream>
#include <vector>
#include <thread>

void test_array() {

    const int maxSize = 100500;
    std::atomic<int> indexToWork{-1};
    std::vector<int> data;
    data.reserve(maxSize);

    auto worker = [&indexToWork, &data, &maxSize] () {
        while (true) {
            // oh my cache!
            int localIndex = indexToWork.fetch_add(1);

            // no more data to work
            if (localIndex >= maxSize)
                break;
            
            int localData = data[localIndex];

            // do something with localData

            // Save a result
            // False sharing (ложное разделение)
            data[localIndex] = 42;
        }
        std::cout << "Thread " << std::this_thread::get_id() << " finished!" << std::endl;
    };

    int threadCount = 10;
    std::vector<std::thread> threads;
    for (int i = 0; i < threadCount; ++i)
        threads.emplace_back(worker);

    for (auto& thr : threads)
        thr.join();

    std::cout << "Finished!" << std::endl;
}

int main() {
    test_array();
    return 0;
}