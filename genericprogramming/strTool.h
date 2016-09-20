##ifndef STRTOOL
#define STRTOOL

#include <vector>
#include <string>

namespace strTool{
	using std::vector;
	using std::string;

	string& trim(string& str) {
		unsigned i = 0;
		for (; i < str.size(); ++i)
			if (str[i] != ' ')
				break;
		str.erase(0, i);

		for (i = str.size() - 1; i >= 0; --i)
			if (str[i] != ' ')
				break;

		str.erase(i + 1);

		return str;
	}

	template<typename T>
	void split(const string& str, vector<T>& result, const string&  sep) {
		throw "unsupported type"
	}

	template<>
	void split<string>(const string& str, vector<string>& result, const string&  sep) {
		int len = str.size();
		if (len == 0)
			return;

		string t;
		string::size_type begin = str.find_first_not_of(sep);
		string::size_type end = 0;
		while (begin != string::npos) {
			end = str.find(sep, begin);
			if (end != string::npos) {
				t = str.substr(begin, end - begin);
				begin = end + sep.length();
			}
			else {
				t = str.substr(begin);
				begin = end;
			}
			if (!t.empty()) {
				result.push_back(t);
				t.clear();
			}
		}
	}

	//节省了提取过程
	//增加了存储消耗，和拷贝操作
	template<>
	void split<int>(const string& str, vector<int>& result, const string&  sep) {	
		vector<string> v;
		split<string>(str, v, sep);
		for (auto x : v)
			result.push_back(std::stoi(x));
	}

	template<>
	void split<float>(const string& str, vector<float>& result, const string&  sep) {
		vector<string> v;
		split<string>(str, v, sep);
		for (auto x : v)
			result.push_back(std::stof(x));
	}

}

#endif