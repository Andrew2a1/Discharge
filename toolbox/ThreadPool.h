#if !defined(THREAD_POOL_H)
#define THREAD_POOL_H

#include <mutex>
#include <thread>
#include <future>

#include <vector>
#include <list>

class function_wrapper
{
    struct impl_base
    {
        virtual void call() = 0;
        virtual ~impl_base() {}
    };

    std::unique_ptr<impl_base> impl;

    template <typename F>
    struct impl_type : impl_base
    {
        F f;
        impl_type(F &&f_) : f(std::move(f_)) {}
        void call() { f(); }
    };

public:
    template <typename F>
    function_wrapper(F &&f) : impl(new impl_type<F>(std::move(f)))
    {
    }

    function_wrapper() : impl(new impl_type<std::function<void()>>([]() {}))
    {
    }

    void call()
    {
        impl->call();
    }

    function_wrapper(function_wrapper &&other) : impl(std::move(other.impl))
    {
    }

    function_wrapper &operator=(function_wrapper &&other)
    {
        impl = std::move(other.impl);
        return *this;
    }

    function_wrapper(const function_wrapper &) = delete;
    function_wrapper(function_wrapper &) = delete;
    function_wrapper &operator=(const function_wrapper &) = delete;
};

class ThreadPool
{
private:
    std::vector<std::thread> threads;
    std::list<function_wrapper> tasks;

    std::condition_variable taskReady;
    std::atomic<bool> endWork;
    std::mutex taskMutex;

public:
    ThreadPool(int concurrency = 0)
    {
        endWork = false;

        if (concurrency == 0)
        {
            const int hc = std::thread::hardware_concurrency();
            concurrency = hc > 0 ? hc - 1 : 1;
        }

        for (int i = 0; i < concurrency; ++i)
            threads.emplace_back(worker, this);
    }

    ~ThreadPool()
    {
        endWork = true;
        taskReady.notify_all();

        for (unsigned i = 0; i < threads.size(); ++i)
            threads[i].join();
    }

    unsigned threadCount() const {
        return threads.size();
    }

    template <typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type>
    submit(FunctionType func)
    {
        typedef typename std::result_of<FunctionType()>::type result_type;
        std::packaged_task<result_type()> task(std::move(func));
        auto future = task.get_future();

        taskMutex.lock();
        tasks.push_back(std::move(task));
        taskMutex.unlock();

        taskReady.notify_one();
        return future;
    }

private:
    void worker()
    {
        while (!endWork)
        {
            std::unique_lock<std::mutex> guard(taskMutex);
            taskReady.wait(guard, [&]() { return !tasks.empty() || endWork; });

            if (!tasks.empty() && !endWork)
            {
                function_wrapper task = std::move(tasks.front());
                tasks.pop_front();

                guard.unlock();
                task.call();
            }
        }
    }
};

#endif // THREAD_POOL_H
