#include"Header.h"


int main()
{

	clock_t start = clock();
	query q;
	StopWordChaining stopword;
	wordTrie fuck;
	string path = "data\\";
	for (auto & p : std::experimental::filesystem::directory_iterator(path)) {
		string p2 = p.path().string();
	//	cout << p2 << endl;
		fuck.add(p2);
	}
	fuck.savewordFile();
	string query;
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
	while (query != "0")
	{
		cout << "Enter:";
		getline(cin, query);
		q.process_Query(q, query, fuck, stopword);
		//if (stopword.isStopWord(query)) cout << "good!";
		//else cout << "fail!";
		/*cout << "Position to add:";
		string s1;
		int n;
		cin >> n;
		cout << "String to add:";
		cin.ignore();
		getline(cin, s1, '\n');	
		q.insert_Query(s1, n);
		q.ShowPrint();
		cout << endl;
		cout << "String to remove:";
		string s;
		getline(cin, s,'\n');
		q.remove_Query(s);*/
		q.ShowPrint();
		cout << endl;
	}

	/*while (query != "0") {
		q.insert_query(query, fuck,stopword);
		cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
		cout << "Enter:";
		getline(cin, query);
	}*/
	
	//if (fuck.search(query))cout << "YES" << endl;
	//else cout << "NO" << endl;
	clock_t finish = clock();
	cout << finish - start << endl;
	return 0;
}
