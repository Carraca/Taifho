#include <string>
#include <iosfwd>
#include <sstream>

class timer {
public:
	timer(){
		min=sec=0;
	}

	void inc(){
		if(++sec >= 60){
			sec=0;
			++min;
		}
	}

	void reset(){
		min=sec=0;
	}

	std::string get(){
		std::stringstream ss;
		if(min<10) ss<<"0";
		ss << min << ":";
		if(sec<10) ss<<"0";
		ss << sec;
		return ss.str();
	}

	int get_sec_int(){
		return sec;
	}

	void set(int t){
		sec = t;
	}

	void dec(){
		--sec;
	}

	bool is_zero(){
		return sec==0;
	}

	int min, sec;
};