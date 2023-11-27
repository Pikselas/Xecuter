#include <thread>
#include <memory>
#include <chrono>
#include <functional>
#include <condition_variable>

class AutoThread
{
    private:
        struct shared_thread_data
        {
            bool signal_run;
            std::function<void()> task;
            std::condition_variable& notifier;
            std::function<void()> expire_callback;
            
            shared_thread_data(std::condition_variable& notifier) : signal_run(false) , notifier(notifier) {}
        };
    private:
        std::shared_ptr<shared_thread_data> shared_data;
    public:
        AutoThread(std::condition_variable& notifier , std::chrono::milliseconds timeout);
    public:
        void setTask(std::function<void()> task);
        void setExpireCallback(std::function<void()> callback);

};

AutoThread::AutoThread(std::condition_variable& notifier , std::chrono::milliseconds timeout) : shared_data(std::make_shared<shared_thread_data>(notifier))
{
    std::thread([=]()
    {
        std::mutex mtx;
        std::unique_lock<std::mutex> m_lock(mtx);
        shared_data->thread_id = std::this_thread::get_id();
        while(shared_data->notifier.wait_for(m_lock , timeout , [&](){  return shared_data->signal_run; }))
        {
            shared_data->signal_run = false;
            shared_data->task();
        }
        shared_data->expire_callback();
    }).detach();
}

void AutoThread::setTask(std::function<void()> task)
{
    shared_data->task = task;
    shared_data->signal_run = true;
}

void AutoThread::setExpireCallback(std::function<void()> callback)
{
    shared_data->expire_callback = callback;
}