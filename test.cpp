#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str = "We think in generalities, but we live in details.";
	string str2 = str.substr(3,5);
	cout << str2 << endl;
	return 0;
}
