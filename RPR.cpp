

#include "Results.h"
#include <iostream>
#include <limits>

int main()
{
	typedef std::numeric_limits< double > dbl;
	cout.precision(dbl::max_digits10);

	CONFIG_A();
	return 0;
}

