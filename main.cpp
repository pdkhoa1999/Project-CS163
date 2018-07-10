#include"Header.h"


int main()
{
	query q;
	wordTrie fuck;

	string query;
	fuck.add("data\\1.txt");
	cout << "Enter:";
	getline(cin,query);
	q.insert_query(query, fuck);
	//if (fuck.search(query))cout << "YES" << endl;
	//else cout << "NO" << endl;
	
	return 0;
}
