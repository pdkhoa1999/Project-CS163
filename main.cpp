#include"Header.h"


int main()
{

	clock_t start = clock();
	query q;
	wordTrie fuck;
	string path = "data\\";
	for (auto & p : std::experimental::filesystem::directory_iterator(path)) {
		string p2 = p.path().string();
		cout << p2 << endl;
		fuck.add(p2);
	}
	fuck.savewordFile();
	string query;
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
	cout << "Enter:";
	getline(cin,query);
	q.insert_query(query, fuck);
	if (fuck.search(query))cout << "YES" << endl;
	else cout << "NO" << endl;
	clock_t finish = clock();
	cout << finish - start << endl;
	return 0;
}
