#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	int f = 10, a = 1;
	for (int i = 2; i <= f; i++)
	{
		a *= i;
	}

	cout << a << endl;

	return 0;
}