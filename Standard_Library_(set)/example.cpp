#include <iostream>
#include <sstream>
#include <set>
using namespace std;

int main()
{
	set<int> s;

	string st = "2 8 1 56 8 2 1 77";
	stringstream str;

	str << st;

	int x;
	while (str >> x)
		s.insert(x);

	for (auto y : s)
		cout << y << " ";

	cout << endl;

}