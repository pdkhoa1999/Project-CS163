#include"Header.h"


int main()
{

	clock_t start = clock();
	query q;
	StopWordChaining stopword;
	wordTrie fuck;
	string s = "$";
	cout << StringtoNumber(s) << endl;
	/*string path = "data\\";
	for (auto & p : std::experimental::filesystem::directory_iterator(path)) {
	string p2 = p.path().string();
	//	cout << p2 << endl;
	fuck.add(p2);
	}
	fuck.savewordFile();*/


	fuck.loadwordFile("word.txt");
	string query;
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
	while (query != "0")
	{
		cout << "Enter:";
		getline(cin, query);
		clock_t begin = clock();
		q.process_Query(query, fuck, stopword);
		cout << endl;
		//q.calculate_Occurance();		
		q.processFeature();
		q.preRanking();
		q.printOccurance_in1path();
		//q.print_top5();
		q.clear_Query();
		q.clear_occurance1path();
		clock_t end = clock();
		cout << "Time run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
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
