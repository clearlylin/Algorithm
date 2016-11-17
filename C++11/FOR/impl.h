#include <stdexcept>
#include "iterator.h"

namespace FOR {
template <class T>
class impl {

public:
	using value_type = T;
	using reference = const value_type&;
	using const_reference = const value_type&;
	using iterator = const FOR::iterator<value_type>;
	using const_iterator = const FOR::iterator<value_type>;
	using size_type = typename FOR::iterator<value_type>::size_type;

private:
	const value_type begin_;
	const value_type end_;
	const value_type step_;
	const size_type max_count_;

	size_type get_adjusted_count(void) const
	{
		if (step_ > 0 && begin_ >= end_)
			throw std::logic_error("greater than begin value");
		else if (step_ < 0 && begin_ <= end_)
			throw std::logic_error("less than begin value");

		size_type x = static_cast<size_type>((end_ - begin_) / step_);
		if (begin_ + (step_ * x) != end_)
			++x;
		return x;
	}

public:
	impl(value_type begin_val, value_type end_val, value_type step_val)
		:begin_(begin_val)
		,end_(end_val)
		,step_(step_val)
		,max_count_(get_adjusted_count())
	{}

	size_type size(void) const
	{
		return max_count_;
	}

	const_iterator begin(void) const
	{
		return {0, begin_, step_};
	}

	const_iterator end(void) const
	{
		return {max_count_, begin_, step_};
	}
};


template<class T>
impl<T> range(T end)
{
	return {{}, end, 1};
}

template<class T>
impl<T> range(T begin, T end)
{
	return {begin, end , 1};
}

template<class T, class U>
auto range(T begin, T end, U step) -> impl<decltype(begin + end)>
{
	using rt = impl<decltype(begin + end)>;
	return rt(begin, end, step);
}

} // FOR
