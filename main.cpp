#include"Header.h"


int main()
{

	std::vector<std::string> dict;
	LoadDictionary(dict);
	clock_t start = clock();
	query q;
	StopWordChaining stopword;
	wordTrie fuck;
	string s = "$";
	cout << StringtoNumber(s) << endl;

	fuck.loadwordFile("word.txt");
	string query;
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
	while (query != "0")
	{
		cout << "Enter:";
		getline(cin, query);
		query = Dictionary(dict, query);
		clock_t begin = clock();
		q.process_Query(query, fuck, stopword);
		//q.ShowPrint();
		cout << endl;
		//q.calculate_Occurance();		
		q.processFeature(stopword);
		q.preRanking();
		q.printOccurance_in1path();
		q.SaveToHistory(dict);
		q.clear_Query();
		q.clear_occurance1path();
		clock_t end = clock();
		cout << "Time run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
	}
	clock_t finish = clock();
	cout << finish - start << endl;
	return 0;
}
