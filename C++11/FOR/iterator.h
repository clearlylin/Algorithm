namespace FOR {

template<class T>
class iterator {
public:
	using value_type = T;
	using size_type = size_t;

private:
	size_type cursor_;
	const value_type step_;
	value_type value_;

public:
	iterator(size_type start, value_type begin, value_type step)
		:cursor_(start)
		,step_(step)
		,value_(begin)
	{
		value_ += (step_ * cursor_);
	}

	value_type operator*() const
	{
		return value_;
	}

	bool operator!=(const iterator& rhs) const
	{
		return (cursor_ != rhs.cursor_);
	}

	iterator& operator++(void)
	{
		value_ += step_;
		++cursor_;
		return (*this);
	}
};

}
