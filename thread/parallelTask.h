#ifndef PARALLEL_TASK_H
#define PARALLEL_TASK_H

#include <future>
#include <functional>

template<typename T>
class Task;

template<typename R, typename... Args>
class Task<R(Args...)> {
	std::function<R(Args...)> m_func;

public:
	typename R return_type;
	Task(std::function<R(Args...)>&& f):m_func(std::move(f)) {
	}

	Task(std::function<R(Args...)>& f):m_func(f) {
	}

	~Task() {
	}

	void wait() {
		std::async(m_func).wait();
	}

	template<typename... Args>
	R get(Args&&... args) {
		return std::async(m_func, std::forward<Args>(args)...).get();
	}

	std::shared_future<R> Run() {
		return std::async(m_func);
	}

	template<typename F>
	auto Then(F&& f)->Task<typename std::result_of<F(R)>::type(Args...)> {
		typedef typename std::result_of<F(R)>::type  returnType;
		auto func = std::move(m_func);
		return Task<returnType(Args...)>([func, &f])(Args&&... args) {
			//std::future<R> 
		}
	}
};

#endif // PARALLEL_TASK_H
