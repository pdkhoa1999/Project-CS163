#include<iostream>
using namespace std;
#include"Header.h"


int main()
{
	wordTrie fuck;
	string query;
	fuck.add("data\\1.txt");
	//fuck.print();
	cout << "Enter:";
	cin >> query;
	if (fuck.search(query))cout << "YES" << endl;
	else cout << "NO" << endl;
	//system("pause");
	return 0;
}
