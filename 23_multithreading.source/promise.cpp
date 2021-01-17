#include <future>
#include <iostream>
#include <thread>
#include <condition_variable>

#pragma promise implementation
template<typename... TArgs> using Action = std::function<void(TArgs...)>;

template<typename T> class TaskState : public std::enable_shared_from_this<TaskState<T>>
{
    static std::shared_ptr<TaskState<T>> Create()
    {
        return std::make_shared<TaskState<T>>();
    }

    bool IsComplete()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return mIsComplete;
    }
    
    const T &Wait()
    {
        std::unique_lock<std::mutex> lock(mMutex);
        while (!mIsComplete)
        {
            mCondition.wait(lock);
        }
        
        return mData;
    }
    
    void RaiseOnComplete()
    {
        // invoke completion handler on result
        if (mIsComplete)
        {
            mOnComplete(*mData);
        }

        // set completion flag to true, this is done after all handlers have been invoked
        {
            std::lock_guard<std::mutex> lock(mMutex);
            // set complete flag to true
            mIsComplete = true;
            mCondition.notify_all();
        }
    }
    
    void SetResult(const T &result)
    {
        {
            std::lock_guard<std::mutex> lock(mMutex);
            mData = result;
        }

        RaiseOnComplete();
    }
    
    void Then(Action<const T &> callback)
    {
        {
            std::lock_guard<std::mutex> lock(mMutex);
            if (!mData.has_value())
            {
                mOnComplete = callback;
            }
        }
    }
private:
    T mData;
    bool mIsComplete = false;
    std::mutex mMutex;
    std::condition_variable mCondition;
    Action<const T&> mOnComplete;
};

template<typename T> class Future
{
    using State = TaskState<T>;
    using FutureType = Future<T>;
    template<typename U> friend class Promise;
    
    virtual bool IsComplete() const
    {
        return mState->IsComplete();
    }
    
    const T &Wait() const
    {
        return mState->Wait();
    }
    
    void Then(Action<const T &> callback)
    {
        mState->Then(callback);
    }
    
private:
    std::shared_ptr<State> mState;
};

template<typename T> class Promise
{
    using State = TaskState<T>;
     using FutureType = Future<T>;
    using PromiseType = Promise<T>;
    template<typename U> friend class Future;

public:
    
    void SetResult(const T &result) const
    {
        mState->SetResult(result);
    }
    
    FutureType GetFuture() const
    {
        auto retVal = FutureType(mState);
        return retVal;
    }
    
private:
    std::shared_ptr<State> mState;
};

#pragma promise examples

void test_promise() {

    auto worker = [](int value, std::promise<int>& promise) {
        try {
            if (value == 7)
                throw std::logic_error("Ooooops");

            promise.set_value(42 + value);
        }
        catch(const std::exception& ex) {
            promise.set_exception(std::current_exception());
        }
    };

    std::promise<int> promise1;
    std::future<int> result1 = promise1.get_future();

    std::thread thread1{worker, 7, std::ref(promise1)};

    try {
        std::cout << "Waiting...." << std::endl;
        result1.wait();
        std::cout << "Result!" << std::endl;
        auto value1 = result1.get();
        std::cout << "value1 = " << value1 << std::endl;
    }
    catch(const std::exception& ex) {
        std::cout << "Exception! " << ex.what() << std::endl;
    }
    thread1.join();


    std::promise<int> promise2;
    std::future<int> result2 = promise2.get_future();

    std::thread thread2{worker, 10, std::ref(promise2)};

    auto value2 = result2.get();
    std::cout << "value2 = " << value2 << std::endl;

    thread2.join();

}


int main() {

    test_promise();

    return 0;
}
