#include <ostream>
#include "Base.h"

using namespace std;

template<typename S>
string to_s(const S& m) {
 	ostringstream os;
	os << m;
	return os.str();
}

int main()
{


	return 0;

};
