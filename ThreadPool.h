#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
private:
    std::queue<std::function<void()>> tasks;
    std::atomic<size_t> tasks_in_progress = 0;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::condition_variable completion_condition;
    bool stop = false;

public:
    std::vector<std::thread> workers;

    ThreadPool(size_t num_threads) {
        for (size_t i = 0; i < num_threads; i++) {
            workers.emplace_back([this] { workerLoop(); });
        }
    }

    template<class F>
    void enqueue(F&& task) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace(std::forward<F>(task));
        }
        condition.notify_one();
    }

    void workerLoop() {
        while(true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                condition.wait(lock, [this] {
                    return stop || !tasks.empty();
                });
                if (stop && tasks.empty()) return;
                task = std::move(tasks.front());
                tasks.pop();
            }
            tasks_in_progress++;
            task();
            tasks_in_progress--;
            completion_condition.notify_one();
        }
    }

    void waitForCompletion() {
        while (tasks.size() > 0) {
            std::this_thread::yield();
        }
    }
};