#include <cstdlib>
#include "Alloc.h"

int main()
{
	char* data[20];
	for (auto i = 0; i < 20; ++i) {
		data[i] = new char[64];
	}
	for (auto i = 0; i < 20; ++i) {
		delete []data[i];
	}

	return 0;
}