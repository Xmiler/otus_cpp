#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <future>
#include <queue>

namespace logging {
    struct LoggingMutex {
    public:
        void lock() {
            m_mutex.lock();
            std::cout << "mutex locked by thread_id: " << std::this_thread::get_id() << std::endl;
        }

        void unlock() {
            std::cout << "mutex unlocked by thread_id: " << std::this_thread::get_id() << std::endl;
            m_mutex.unlock();
        }
    private:
        std::mutex m_mutex;
    };

    LoggingMutex loggingMutex;
    std::condition_variable_any condition;
    bool startFlag = false;

    void folower() {
        std::unique_lock<LoggingMutex> lck{loggingMutex};
        while(!startFlag) condition.wait(lck);
        std::cout << "Folower wake up! threadId = " << std::this_thread::get_id() << std::endl;
    }

    void leader() {
        std::cout << "Leader - prepare command..." << std::endl;
        std::lock_guard<LoggingMutex> guard{loggingMutex};
        startFlag = true;
        condition.notify_all();
    }

    void test_leader_folowers() {
        const std::size_t folowersCount = 10;
        std::vector<std::thread> folowersThr;

        for (std::size_t i = 0; i < folowersCount; ++i) {
            folowersThr.emplace_back( folower );
        };

        std::thread leaderThr{leader};

        for (auto& thr : folowersThr)
            thr.join();
        leaderThr.join();
    }
}

namespace real {
    std::atomic<bool> finished{false};
    std::mutex conditionMutex;
    std::condition_variable condition;

    std::vector<int> data;

    void consumer() {
        std::unique_lock<std::mutex> lck{conditionMutex};
        while(!finished) {
            while(data.empty() && !finished) 
                condition.wait(lck);

            std::cout << "Consumer - next data to proceed!\n";
            for (auto& v : data)
                std::cout << v << ' ';
            std::cout << std::endl;

            data.clear();
        }

        std::cout << "Consumer - finished!" << std::endl;
    }

    void producer() {
        const int step = 5;
        int counter = 0;
        while(!finished) {
            {
                std::lock_guard<std::mutex> guard{conditionMutex};
                std::cout << "Producer - generate data" << std::endl;
                for (int i = 0; i < step; ++i)
                    data.emplace_back(++counter);
                condition.notify_one();
            }
            
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        condition.notify_one();

        std::cout << "Producer - finished!" << std::endl;
    }

    void test_condition() {

        std::thread consumerThread{consumer};
        std::thread producerThread{producer};

        std::this_thread::sleep_for(std::chrono::seconds(10));

        finished = true;
        producerThread.join();
        consumerThread.join();

    }

}

class SingleThreadExecutor
{
public:
    virtual ~SingleThreadExecutor()
    {
        if(mIsDisposed)
        {
            return;
        }

        if (mFuture.valid())
        {
            NotifyUpdate();
            mFuture.get();
        }
    }

    void Add(std::function<void(void)> func)
    {
        {
            std::lock_guard<std::mutex> lock(mStdAsyncMutex);
            if (!mFuture.valid())
            {
                mFuture = std::async(std::launch::async, &SingleThreadExecutor::Update, this);
            }
        }

        {
            std::lock_guard<std::mutex> lock(mQueueMutex);

            mActionsQueue.push(func);
        }
    }
    
    void NotifyUpdate()
    {
        {
            std::lock_guard<std::mutex> lock(mUpdateWaitMutex);
            mUpdateNotified = true;
        }

        mUpdateWait.notify_one();
    }

private:
    std::queue<std::function<void()>> mActionsQueue;
    std::atomic<bool> mIsDisposed {false};
    std::mutex mStdAsyncMutex;
    std::mutex mQueueMutex;
    std::mutex mUpdateWaitMutex;
    std::future<void> mFuture;

    std::condition_variable mUpdateWait;
    bool mUpdateNotified = false;

    void Update();
};

void SingleThreadExecutor::Update()
{
    while (!mIsDisposed)
    {
        std::function<void(void)> functionToInvoke;
        bool shouldWait;

        {
            std::lock_guard<std::mutex> lock(mQueueMutex);
            if (mActionsQueue.size() > 0)
            {
                functionToInvoke = mActionsQueue.front();
                mActionsQueue.pop();
            }
            shouldWait = mActionsQueue.empty();
        }

        if (functionToInvoke)
        {
            if (mIsDisposed)
            {
                break;
            }

            try{
                functionToInvoke();
            }
            catch(...)
            {
                std::cout<<"Error while invoking action in SingleThreadExecutor"<<std::endl;
            }
        }

        if (shouldWait)
        {
            // Blocking thread until condition variable notified outside
            std::unique_lock<std::mutex> updateLock(mUpdateWaitMutex);
            while(!mUpdateNotified){
                mUpdateWait.wait(updateLock);
                mUpdateNotified = false;
            }
        }
    }

    std::lock_guard<std::mutex> lock(mQueueMutex);
    while (mActionsQueue.size() > 0)
    {
        try{
            mActionsQueue.front()();
        }
        catch(...)
        {
            std::cout<<"Error while invoking remaining actions in SingleThreadExecutor"<<std::endl;
        }
        mActionsQueue.pop();
    }
};

int main() {

    std::cout << "Leader-folowers example" << std::endl;
    logging::test_leader_folowers();

    std::cout << std::endl << std::endl << std::endl;

    std::cout << "Producer-consumer example" << std::endl;
    real::test_condition();

    return 0;
}
