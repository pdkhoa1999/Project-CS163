#include "Header.h"
StopWordChaining sw;
HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void wordTrie::add(string path)
{

	ifstream fin;
	fin.open(path);
	if (fin)
	{
		int count = 0;
		while (!fin.eof())
		{
			wordNode* cur = NULL;
			int n = 0;
			string word = takeWord(fin, n);

			//if (!sw.isStopWord(word)) {
				if (word[0] > 0) {
					if (root == NULL) root = new wordNode;
					cur = root;
					for (int i = 0; i < n; i++)
					{

						char x = tolower(word[i]);
						if ((x - 'a' >= 26 || x - 'a' < 0) && (x < 48 || x>57) && x != '#'&&x != '$')//if not alphabet ->break
							break;
						if (x == '#')
						{
							if (cur->children[36] == NULL)
							{
								cur->children[36] = new wordNode;
							}
							cur = cur->children[36];
						}
						else if (x == '$')
						{
							if (cur->children[37] == NULL)
							{
								cur->children[37] = new wordNode;
							}
							cur = cur->children[37];
						}
						else if (x >= 48 && x <= 57)
						{
							if (cur->children[x - 22] == NULL)
							{
								cur->children[x - 22] = new wordNode;
							}
							cur = cur->children[x - 22];
						}
						else if (x > 57)
						{
							if (cur->children[x - 'a'] == NULL)
							{
								cur->children[x - 'a'] = new wordNode;
							}
							cur = cur->children[x - 'a'];
						}
					}
					if (cur->phead == NULL)//create first data node for the word
					{
						cur->phead = new pathNode;
						cur->phead->pos[0] = count;
						cur->phead->occurance++;
						cur->phead->path = path;
						cur->phead->pnext = NULL;
						cur->n++;
					}
					else
					{
						pathNode*curpath = cur->phead;
						while (curpath->pnext != NULL && curpath->path != path)//create nodes after the first node
						{
							curpath = curpath->pnext;
						}
						if (curpath->path == path)//the file already in the data
						{
							curpath->pos[curpath->occurance] = count;
							curpath->occurance++;
						}
						else
						{
							curpath->pnext = new pathNode;//new file
							curpath = curpath->pnext;
							curpath->path = path;
							curpath->pos[0] = count;
							curpath->occurance++;
							curpath->pnext = NULL;
							cur->n++;
						}

					}

				}
			}
			count++;
		}
	//}
	fin.close();
}
string wordTrie::takeWord(ifstream &fin, int &n)
{
	string word, w;
	char x;
	fin >> x;
	while (!checkValidation(x) && fin)fin >> x;
	fin >> word;
	w += x;
	word.insert(0, w);
	n = word.length();
	for (int i = 0; i < n; i++)
	{
		if (!checkValidation(word[i]))
		{
			word.erase(i, n);
			n = i;
		}
	}
	ToLower(word);
	return word;
}
void wordTrie::printInternal(wordNode*root, string word)
{
	if (root->phead != NULL)
	{
		cout << word << "-" << root->n << "-";
		pathNode *cur = root->phead;
		while (cur != NULL)
		{
			cout << cur->path << "," << cur->occurance;
			for (int i = 0; i < cur->occurance; i++)
			{
				cout << "," << cur->pos[i];
			}
			cout << ";";
			cur = cur->pnext;
		}
		cout << endl;
	}
	for (int i = 0; i < 38; i++)
	{
		if (root->children[i] != NULL)
		{
			if (i == 37) word += '$';
			else if (i == 36) word += '#';
			else if (i >= 26 && i <= 35)word += i + 22;
			else word += 'a' + i;
			printInternal(root->children[i], word);
			word.pop_back();
		}
	}
}
void wordTrie::print()
{
	string word;
	printInternal(root, word);
}
void wordTrie::loadwordFile(string path)
{
	ifstream fin;
	fin.open(path);
	if (fin)
	{
		while (!fin.eof())
		{
			string word;
			getline(fin, word, '-');
			wordNode* cur = NULL;
			int n = word.length();
			if (root == NULL) root = new wordNode;
			cur = root;
			for (int i = 0; i < n; i++)
			{

				char x = tolower(word[i]);
				if ((x - 'a' >= 26 || x - 'a' < 0) && (x < 48 || x>57) && x != '#'&&x != '$')//if not alphabet ->break
					break;
				if (x == '#')
				{
					if (cur->children[36] == NULL)
					{
						cur->children[36] = new wordNode;
					}
					cur = cur->children[36];
				}
				else if (x == '$')
				{
					if (cur->children[37] == NULL)
					{
						cur->children[37] = new wordNode;
					}
					cur = cur->children[37];
				}
				else if (x >= 48 && x <= 57)
				{
					if (cur->children[x - 22] == NULL)
					{
						cur->children[x - 22] = new wordNode;
					}
					cur = cur->children[x - 22];
				}
				else if (x > 57) {
					if (cur->children[x - 'a'] == NULL)
					{
						cur->children[x - 'a'] = new wordNode;
					}
					cur = cur->children[x - 'a'];
				}
			}
			fin >> cur->n;
			pathNode*curpath = NULL;
			for (int i = 0; i < cur->n; i++)
			{
				int x;
				fin.ignore();
				getline(fin, path, ',');
				fin >> x;
				if (cur->phead == NULL)//create first data node for the word
				{
					cur->phead = new pathNode;
					curpath = cur->phead;
					cur->phead->occurance += x;
					for (int i = 0; i < x; i++)
					{
						fin.ignore(1);
						fin >> curpath->pos[i];

					}
					cur->phead->path = path;
					cur->phead->pnext = NULL;
				}
				else
				{
					curpath->pnext = new pathNode;
					curpath = curpath->pnext;
					curpath->occurance += x;
					for (int i = 0; i < x; i++)
					{
						fin.ignore(1);
						fin >> curpath->pos[i];

					}
					curpath->path = path;
					curpath->pnext = NULL;


				}
			}
			fin.ignore(2);
		}
	}
	fin.close();
}
void wordTrie::saveInternal(ofstream &fout, wordNode*root, string word) {

	if (fout)
	{
		if (root->phead != NULL)
		{
			fout << word << "-" << root->n << "-";
			pathNode*cur = root->phead;
			while (cur != NULL)
			{
				fout << cur->path << "," << cur->occurance;
				for (int i = 0; i < cur->occurance; i++)
				{
					fout << "," << cur->pos[i];
				}
				fout << ";";
				cur = cur->pnext;
			}
			fout << endl;
		}
		for (int i = 0; i < 38; i++)
		{
			if (root->children[i] != NULL)
			{
				if (i == 37) word += '$';
				else if (i == 36) word += '#';
				else if (i >= 26 && i <= 35)word += i + 22;
				else word += 'a' + i;
				saveInternal(fout, root->children[i], word);
				word.pop_back();
			}
		}
	}
}
void wordTrie::savewordFile()
{
	ofstream fout;
	fout.open("word.txt");
	string m;
	saveInternal(fout, root, m);
	fout.close();
}
bool wordTrie::search(string s, wordNode *root)
{
	int i = 0;
	wordNode * cur = root;
	char x;
	//function filter 
	while (checkValidation(s[i]) && i<s.length())
	{
		if (cur == NULL)return false;
		x = tolower(s[i]);
		cur = cur->children[s[i] - 'a'];
		i++;
		if (cur != NULL && i == s.length() && cur->phead != NULL)return true;
	}
	return false;
}
wordNode* wordTrie::Findword(string s)
{
	return Findword(s, root);
}
wordNode* wordTrie::Findword(string s, wordNode * root)
{
	int i = 0;
	wordNode * cur = root;
	//function filter 
	while (checkValidation(s[i]) && i<s.length())
	{ //26 -> 35
	  // 36:# 37 $ 38
		if (cur == NULL)return NULL;
		if ((s[i] >= 'A'&& s[i] <= 90) || s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] = tolower(s[i]);
			cur = cur->children[s[i] - 'a'];
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			cur = cur->children[s[i] - 22];
		}
		else if (s[i] == '#')
		{
			cur = cur->children[36];
		}
		else if (s[i] == '$')
		{
			cur = cur->children[37];
		}
		i++;
		if (cur != NULL && i == s.length() && cur->phead != NULL)return cur;
	}
	return NULL;
}
string wordTrie::ShowMakeUpString(string s)
{
	string makeup = MakeUpString(s);
	if (IsNeeded(makeup, s)) return makeup;
	else return "\0";
}
string wordTrie::ShowSplitString(string s)
{
	string splited = SplitString(s);
	if (IsNeeded(splited, s)) return splited;
	else return "\0";
}
string wordTrie::MakeUpString(string s)
{
	wordNode *cur = root;
	string result;
	int i = 0, len = s.length();
	while (cur != NULL && i<len)
	{
		if (!checkValidation(s[i]))
		{
			i++;
			continue;
		}
		int t = HashWord(s, i);
		if (cur->children[t] != NULL)
		{
			cur = cur->children[t];
			result += s[i];
		}
		i++;
	}
	if (cur->phead == NULL) return "\0";

	return result;
}
string wordTrie::SplitString(string s)
{
	wordNode *cur = root;
	string result;
	int i = 0, len = s.length();
	int flag = 0;
	while (cur != NULL && i<len)
	{
		if (!checkValidation(s[i]))
		{
			i++;
			continue;
		}
		int t = HashWord(s, i);
		if (cur->children[t] != NULL)
		{
			cur = cur->children[t];
			result += s[i];
		}
		else if (cur->phead != NULL)
		{
			// this is refresh step			
			cur = root;
			i--;
			// this is split step
			result += ",";
			flag = result.length();
		}
		else if (cur->phead == NULL)
		{
			// this is refresh step
			cur = root;
			i--;
			// clear the redundancy in process
			result.erase(flag);

		}


		i++;
	}
	// Clean the worst case
	if (cur->phead == NULL)
	{

		result.erase(flag);
	}


	return result;
}
void wordTrie::addSynonym(LinkedList synWord[50])
{
	int k;
	ifstream fin;
	string a, b;
	k = 0;
	fin.open("synonym.txt");
	if (!fin) {
		cout << "No synonym file";
		return;
	}
	while (!fin.eof())
	{

		getline(fin, a);
		int n = a.length();
		for (int i = 0; i < n; i++)
		{
			if (a[i] != ',')
			{
				b += a[i];
			}
			else
			{
				synWord[k].RunInsertWords(b);
				b = "";
			}
		}
		k++;
	}
	for (int i = 0; i < k; i++)
	{
		Node *curN = synWord[i].head;
		while (curN != NULL) {
			wordNode*cur = root;
			for (int j = 0; j < curN->s.length(); j++)
			{

				char x = tolower(curN->s[j]);
				if ((x - 'a' >= 26 || x - 'a' < 0) && (x < 48 || x>57) && x != '#'&&x != '$')//if not alphabet ->break
					break;
				if (x == '#')
				{
					if (cur->children[36] == NULL)
					{
						cur->children[36] = new wordNode;
					}
					cur = cur->children[36];
				}
				else if (x == '$')
				{
					if (cur->children[37] == NULL)
					{
						cur->children[37] = new wordNode;
					}
					cur = cur->children[37];
				}
				else if (x >= 48 && x <= 57)
				{
					if (cur->children[x - 22] == NULL)
					{
						cur->children[x - 22] = new wordNode;
					}
					cur = cur->children[x - 22];
				}
				else if (x > 57) {
					if (cur->children[x - 'a'] == NULL)
					{
						cur->children[x - 'a'] = new wordNode;
					}
					cur = cur->children[x - 'a'];
				}
			}
			cur->syn = i;
			curN = curN->next;
		}
	}
}

//stopword
void LinkedList::InsertWords(string s, Node *&cur)
{
	if (cur == NULL)
	{
		cur = new Node;
		cur->s = s;
		return;
	}
	else return InsertWords(s, cur->next);
}
void LinkedList::RunInsertWords(string s)
{
	InsertWords(s, head);
}
StopWordChaining::StopWordChaining()
{
	ifstream fin;

	fin.open("Stopwords.txt");
	if (!fin.good())
	{
		cout << " Stopword.txt ERROR!!";
		exit(1);
	}
	while (!fin.eof())
	{
		string s;
		getline(fin, s, '\n');
		arr[HashWord(s)].RunInsertWords(s);
	}


	fin.close();
	return;
}
int StopWordChaining::HashWord(string s)
{
	int t = s.length(), index = 0;
	for (int i = 0; i<t; i++)
	{
		index += s[i];
	}
	index = index % 419;

	return index;
}
bool StopWordChaining::isStopWord(string s)
{
	if (arr[HashWord(s)].RunFindWord(s) != NULL) return true;


	return false;
}
Node* LinkedList::FindWord(string s, Node*cur)
{
	if (cur == NULL) return NULL;
	if (StringCompare(s, cur->s))
	{
		return cur;
	}
	else return FindWord(s, cur->next);
}
Node* LinkedList::RunFindWord(string s)
{
	ToLower(s);
	return FindWord(s, head);

}
//Support
bool StringCompare(string s1, string s2)
{

	for (int i = 0; i < s1.size(); i++)
		s1[i] = toupper(s1[i]);

	for (int i = 0; i < s2.size(); i++)
		s2[i] = toupper(s2[i]);

	if (s1.compare(s2) == 0)
	{
		return true;
	}

	return false;
}
void ToLower(string & s)
{
	for (int i = 0; i < s.length(); i++) s[i] = tolower(s[i]);
	return;
}
bool checkValidation(char x)
{
	if ((x>64 && x<91) || (x>96 && x<123) || (x >= 48 && x <= 57) || x == '$' || x == '#')
		return true;
	return false;
}
int HashWord(string s, int i)
{
	if ((s[i] >= 'A'&& s[i] <= 90) || s[i] >= 'a' && s[i] <= 'z')
	{
		s[i] = tolower(s[i]);
		return s[i] - 'a';
	}
	else if (s[i] >= '0' && s[i] <= '9')
	{
		return s[i] - 22;
	}
	else if (s[i] == '#')
	{
		return 36;
	}
	else if (s[i] == '$')
	{
		return 37;
	}

	return 0;
}
bool IsNeeded(string s1, string s2)
{
	if (s2 == "")return false;
	int t = s1.length() * 100 / (s2.length());
	if (t >= 80) return true;
	else if (s1.find(",") != std::string::npos && t>70) return true;
	else return false;
}
int StringtoNumber(string s)
{
	int x = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (int(s[i]) >= 48 && int(s[i]) <= 57)
			x = x * 10 + (int(s[i]) - 48);
	}
	return x;

}
bool checkNumber(string s)
{
	for (int i = 0; i <= s.length(); i++)
	{
		if (int(s[i]) < 48 && int(s[i]) > 57)
			return false;
	}
	return true;
}
LinkedList findSynonym(wordTrie root, string a)
{
	LinkedList synWord[50],null;
	root.addSynonym(synWord);
	wordNode *cur = root.Findword(a);
	if (!cur) return null;
	int k = cur->syn;
	return synWord[k];

}
string Dictionary(std::vector<std::string> dict, string input)
{

	std::vector<std::string>::iterator it;
	std::string temp, word;
	bool done = false;


	temp = "";
	word = "";
	string str1, str2, str3;
	int i = 1;

	word += input;
	for (it = dict.begin(); it != dict.end(); ++it)
	{
		if (word == (*it).substr(0, word.length()))
		{
			if (i == 1)
				str1 = (*it);
			if (i == 2)
			{
				if (str1 != *it)
					str2 = *it;
				else
				{
					i--;
				}
			}
			if (i == 3)
			{
				if (str1 != *it && str2 != *it)
					str3 = *it;
				else i--;
			}
			i++;
			if (i > 3) break;
		}
	}
	if (i == 1) return input;

	cout << "Do you mean:" << endl;
	for (int j = 1; j < i; j++)
	{
		if (j == 1)
			cout << j << ". " << str1 << endl;
		else if (j == 2)
			cout << j << ". " << str2 << endl;
		else if (j == 3)
			cout << j << ". " << str1 << endl;
		else break;
	}
	cout << "Choose your choice:";
	string s;
	getline(cin, s);
	if (s == "1") return str1;
	else if (s == "2") return str2;
	else if (s == "3") return str3;
	else return input;
}
void LoadDictionary(std::vector<std::string> &dict)
{
	std::ifstream inf;
	ofstream fout;
	char check[100];

	inf.open("dict.txt");

	while (!inf.eof())
	{
		inf.getline(check, 100, '\n');

		dict.push_back(check);
	}
	fout.close();
	return;
}

//Query
bool query::word_exist(string s)
{
	return word_exist(s, num, block);
}
void query::load_Query(string & s, wordTrie  root)
{
	load_QueryInternal(s, root, num);
}
void query::insert_Query(string s, int pos, wordTrie root)
{
	insert_QueryInternal(s, pos, root, num);
}
int query::find_Query(string s)
{
	return find_QueryInternal(s, num);
}
void query::remove_Query(int pos, int &n)
{
	remove_QueryInternal(pos, num);
}
bool query::Linearsearch(wordTrie root, int i)
{
	return LinearseachInternal(root, i);
}
void query::process_Query(string s, wordTrie  root, StopWordChaining stopword)
{
	process_QueryInternal(s, root, stopword, num);
}
void query::clear_Query()
{
	clear_QueryInternal(num);
}
void query::inrange_Feature(int i, wordTrie root, int & n)
{
	inrange_FeatureInternal(i, root, n);
}
void query::plus_Feature(int i, wordTrie root, int n)
{
	plus_FeatureInternal(i, root, n);
}
void query::and_Feature(int i, int n)
{
	and_FeatureInternal(i, n);
}
void query::or_Feature(int i, int n)
{
	or_FeatureInternal(i, n);
}
void query::minus_Feature(int i, wordTrie root, int n)
{
	minus_FeatureInternal(i, root, n);
}
void query::intitle_Feature(int i, wordTrie root, int n)
{
	intitle_FeatureInternal(i, root, n);
}
void query::file_Feature(int i, wordTrie root, int n)
{
	file_FeatureInternal(i, root, n);
}
void query::wildcard_Feature(int i, int n)
{
	wildcard_FeatureInternal(i, n);
}
void query::upduate_Address(int &i, wordTrie root, int &n)
{
	upduate_AddressInternal(i, root, n);
}
void query::match_Feature(int i, wordTrie root, int n)
{
	match_FeatureInternal(i, root, n);
}
void query::synonym_Feature(int i, wordTrie root, int &n)
{
	synonym_FeatureInternal(i, root, n);
}

void query::match_FeatureInternal(int i, wordTrie root, int n)
{
	block[0].s.erase(0, 1);
	block[n - 1].s.erase(block[n - 1].s.length() - 1);
	for (int i = 0; i < n; i++)
	{
		wordNode * temp1;
		temp1 = root.Findword(block[i].s);
		if (temp1 != NULL)
			block[i].wordinfo = temp1->phead;
		else
			block[i].wordinfo = NULL;
		block[i].rank.is_Match = true;
		block[i].rank.is_Feature = true;
	}
	cout << "Match Feature" << endl;
	//	for (int i = 0; i < n; i++)
	//	cout << block[i].s << endl;
}
void query::upduate_AddressInternal(int &i, wordTrie root, int &n)
{
	/*if (i >= 0) {
	wordNode * temp1;
	temp1 = root.Findword(block[i].s);
	if (temp1 == NULL) {
	remove_Query(i, n);
	i--;
	}
	else block[i].wordinfo = temp1->phead;
	}*/
	if (i >= 0) {
		wordNode * temp1;
		temp1 = root.Findword(block[i].s);


		if (temp1 == NULL)
		{
			if (!Linearsearch(root, i))
			{
				remove_Query(i, n);
				i--;
			}
			else
			{
				n = num;
				temp1 = root.Findword(block[i].s);
				block[i].wordinfo = temp1->phead;
			}
		}
		else block[i].wordinfo = temp1->phead;
	}
}
void query::wildcard_FeatureInternal(int i, int n)
{
	//cout << "Wilcard Feature" << endl;
	//remove_Query(i, n);
	for (int j = 0; j < n; j++) {
		block[j].rank.is_WildCard = true;
		block[j].rank.is_Feature = true;
	}
}
void query::file_FeatureInternal(int i, wordTrie root, int n)
{
	block[i].s.erase(0, 9);
	string temp = block[i].s;
	remove_Query(i, n);
	insert_Query(temp, i, root);
	block[i].rank.is_File = true;
	block[i].rank.is_Feature = true;
	cout << "Filetype Feature " << endl;
}
void query::intitle_FeatureInternal(int i, wordTrie root, int n)
{
	block[i].s.erase(0, 8);
	string temp = block[i].s;
	remove_Query(i, n);
	insert_Query(temp, i, root);
	for (int j = i; j < n; j++)
	{
		block[i].rank.is_Intitle = true;
		block[i].rank.is_Feature = true;
	}
}
void query::minus_FeatureInternal(int i, wordTrie root, int n)
{
	block[i].s.erase(block[i].s.begin(), block[i].s.begin() + 1);
	string temp = block[i].s;
	remove_Query(i, n);
	insert_Query(temp, i, root);
	block[i].rank.is_Minus = true;
	block[i].rank.is_Feature = true;
}
void query::or_FeatureInternal(int i, int n)
{
	block[i].rank.is_Or = true;
	block[i].rank.is_Feature = true;
	remove_Query(i, n);
}
void query::and_FeatureInternal(int i, int n)
{
	block[i].rank.is_And = true;
	block[i].rank.is_Feature = true;
	remove_Query(i, n);
}
void query::plus_FeatureInternal(int i, wordTrie root, int n)
{
	block[i].s.erase(0, 1);
	string temp = block[i].s;
	remove_Query(i, n);
	insert_Query(temp, i, root);
	block[i].rank.is_And = true;
	block[i].rank.is_Feature = true;
}
void query::synonym_FeatureInternal(int i, wordTrie root, int &n)
{
	block[i].s.erase(0, 1);
	string temp = block[i].s;
	remove_Query(i, n);
	insert_Query(temp, i, root);
	block[i ].rank.is_Set = true;
	block[i ].rank.is_Feature = true;
	LinkedList syn=findSynonym(root, block[i].s);
	Node *cur = syn.head;
	while (cur)
	{
		if (StringCompare(block[i].s, cur->s)) cur = cur->next;
			insert_Query(cur->s, i + 1, root);
			n++;
			block[i+1].rank.is_Set = true;
			block[i+1].rank.is_Feature = true;
		cur = cur->next;
	}

}
void query::inrange_FeatureInternal(int i, wordTrie root, int & n)
{
	string temp;
	int j = 0;
	block[i].rank.is_InRange = true;
	block[i].rank.is_Feature = true;
	for (j; j < block[i].s.length() + 1; j++)
	{
		if (block[i].s[j] == '.') {
			insert_Query(temp, i + 1, root);
			temp.clear();
			break;
		}
		else
			temp += block[i].s[j];
	}
	for (j; j < block[i].s.length(); j++)
	{
		if (block[i].s[j] == '.')continue;
		else temp += block[i].s[j];
	}
	remove_Query(i, n);
	insert_Query(temp, i, root);
}
void query::load_QueryInternal(string & s, wordTrie root, int & n)
{
	string temp;
	for (int i = 0; i < s.length() + 1; i++)
	{
		if (n >= 34)
		{
			cout << "OUT OF RANGE !!!" << endl;
			return;
		}
		if (s[i] == ' ' || i == s.length())
		{
			block[n].s = temp;
			wordNode * temp1 = root.Findword(block[n].s);
			if (temp1 != NULL)block[n].wordinfo = temp1->phead; //else remove_Query(n);
			n++;
			temp.clear();
		}
		else
			temp += s[i];
	}
}
void query::clear_QueryInternal(int & n)
{
	for (int i = 0; i < n; i++)
	{
		block[i].s = "";
		block[i].rank.is_And = false;
		block[i].rank.is_Feature = false;
		block[i].rank.is_File = false;
		block[i].rank.is_Hashtags = false;
		block[i].rank.is_InRange = false;
		block[i].rank.is_Intitle = false;
		block[i].rank.is_Match = false;
		block[i].rank.is_Minus = false;
		block[i].rank.is_Price = false;
		block[i].rank.is_Or = false;
		block[i].rank.is_WildCard = false;
	}
	n = 0;
}
void query::insert_QueryInternal(string s, int pos, wordTrie root, int & n)
{
	n++;
	int temp;
	for (int i = n; i > pos; i--)
	{
		block[i].s = block[i - 1].s;
	}
	wordNode * temp1 = root.Findword(block[n].s);
	if (temp1 != NULL)block[n].wordinfo = temp1->phead;
	block[pos].s = s;
}
int query::find_QueryInternal(string s, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (s == block[i].s)
			return i;
	}
	return -1;
}
void query::remove_QueryInternal(int pos, int &n)
{
	for (int i = pos; i < n; ++i)
	{
		block[i].s = block[i + 1].s;
		block[i].wordinfo = block[i + 1].wordinfo;
	}
	n--;
}
bool query::word_exist(string s, int n, keyword_block * block)
{
	for (int i = 0; i < n; i++)
		if (StringCompare(block[i].s,s))return true;
	return false;
}
bool query::LinearseachInternal(wordTrie root, int i)
{
	string linear = root.ShowMakeUpString(block[i].s);
	if (linear == "\0")
	{
		linear = root.ShowSplitString(block[i].s);
		if (linear == "\0") return false;
		else
		{
			int count = 0;
			for (int i = 0; i < linear.length(); i++)
				if (linear[i] == ',')
				{
					count++;
					linear[i] = ' ';
				}
			int run = 0;
			remove_Query(i, num);
			for (int j = 0; j <= count; j++)
			{
				string x;
				while (linear[run] != ' ' && run<linear.length())
				{
					x += linear[run];
					run++;
				}
				run++;
				insert_Query(x, i, root);
				i++;
			}
			return true;

		}


	}
	else
	{
		remove_Query(i, num);
		insert_Query(linear, i, root);
		return true;
	}

	return false;
}
void query::process_QueryInternal(string s, wordTrie  root, StopWordChaining stopword, int &n)
{
	bool isFeature = false;
	load_Query(s, root);
	if (block[0].rank.isMatch(block[0].s))
	{
		match_Feature(0, root, n);
	}
	else {
		for (int i = 0; i < n; i++)
		{
			if (block[i].rank.is_And || block[i].rank.is_Or)
				continue;
			isFeature = false;
			if (block[i].rank.isInRange(block[i].s))
			{
				isFeature = true;
				inrange_Feature(i, root, n);
			}
			if (block[i].rank.isAnd(block[i].s))
			{
				isFeature = true;
				and_Feature(i, n);
				//i--;
			}
			if (block[i].s[0] == '+')
			{
				isFeature = true;
				plus_Feature(i, root, n);
			}
			if (block[i].rank.isOr(block[i].s))
			{
				isFeature = true;
				or_Feature(i, n);
				//i--;
			}
			if (block[i].rank.isMinus(block[i].s))
			{
				isFeature = true;
				minus_Feature(i, root, n);
			}
			if (block[i].rank.isIntitle(block[i].s))
			{
				isFeature = true;
				intitle_Feature(i, root, n);
			}
			if (block[i].rank.isFile(block[i].s))
			{
				isFeature = true;
				file_Feature(i, root, n);
				continue;
			}
			if (block[i].rank.isPrice(block[i].s))
			{
				isFeature = true;
				block[i].rank.is_Price = true;
				block[i].rank.is_Feature = true;
			}
			if (block[i].rank.isHashtags(block[i].s))
			{
				isFeature = true;
				block[i].rank.is_Hashtags;
			}
			if (block[i].rank.isWildCard(block[i].s))
			{
				isFeature = true;
				wildcard_Feature(i, n);
				break;
			}
			if (block[i].rank.isSet(block[i].s))
			{
				synonym_Feature(i, root, n);
			}
			upduate_Address(i, root, n);
		}
	}
}
void query::PrintToTest()
{
	if (num == 0)cout << "Not Found !!!" << endl;
	else {
		for (int i = 0; i < num; i++)
		{
			cout << block[i].s << endl;
			while (block[i].wordinfo != NULL)
			{
				cout << block[i].wordinfo->path << " " << block[i].wordinfo->occurance << endl;
				block[i].wordinfo = block[i].wordinfo->pnext;
			}
		}
	}
	return;
}
void query::ShowPrint()
{
	PrintToTest();
	return;
}
//Query	 -->    Print process
void query::Print_process(string path,bool isWildcard)
{
	Print_processInternal(path, num,isWildcard);
}
int  query::min_location(string path)
{
	return min_locationInternal(path);
}
int  query::max_location(string path)
{
	return max_locationInternal(path);
}
bool query::is_Print(string s)
{
	return is_PrintInternal(s);
}
void query::Print_paragraph(string s,bool isWildcard)
{
	Print_paragraphInternal(s,isWildcard);
}
void query::Print_processInternal(string path, int n,bool isWildcard)
{
	if (n >= 34)
	{
		return;
	}
	ifstream fin;
	string temp;
	fin.open(path);
	bool firsttime = true;
	bool iscont = false;
	int count = 0;
	while (!fin.eof())
	{
		if (count == 3)break;
		getline(fin, temp, '\n');
		if (is_Print(temp)) {
			Print_paragraph(temp,isWildcard);
			if (firsttime)cout << endl;
			firsttime = false;
			iscont = false;
			count++;
		}
		else
			if (!firsttime && !iscont) {
				cout << "...";
				iscont = true;
			}
	}
	cout << endl;
	fin.close();
}
void query::Print_paragraphInternal(string s, bool isWildcard)
{
	string temp;
	if (isWildcard)
	{
		bool wildcard = false;
		for (int i = 0; i < s.length() + 1; i++)
		{
			temp += s[i];
			if (word_exist(temp))
			{
				SetConsoleTextAttribute(hConsole, 12);
				cout << temp;
				temp.clear();
				SetConsoleTextAttribute(hConsole, 7);
				wildcard = true;
			}
			else
				if (s[i] == ' ' || s[i] == '.')
				{
					if (wildcard && temp!=" ")
					{
						SetConsoleTextAttribute(hConsole, 12);
						cout << temp;
						temp.clear();
						SetConsoleTextAttribute(hConsole, 7);
						wildcard = false;
					}
					else {
						SetConsoleTextAttribute(hConsole, 7);
						cout << temp;
						temp.clear();
					}
				}
		}
	}
	else {
		for (int i = 0; i < s.length() + 1; i++)
		{
			temp += s[i];
			if (word_exist(temp))
			{
				SetConsoleTextAttribute(hConsole, 12);
				cout << temp;
				temp.clear();
				SetConsoleTextAttribute(hConsole, 7);
			}
			else
				if (s[i] == ' ' || s[i] == '.')
				{
					SetConsoleTextAttribute(hConsole, 7);
					cout << temp;
					temp.clear();
				}
		}
	}
}
bool query::is_PrintInternal(string s)
{
	string temp;
	for (int i = 0; i < s.length() + 1; i++)
	{
		s[i] = tolower(s[i]);
		temp += s[i];
		if (s[i] == ' ')
		{
			temp.clear();
		}
		if (word_exist(temp))return true;
	}
	return false;
}
int query::max_locationInternal(string path)
{
	int max = 0;
	for (int i = 0; i < num; i++)
	{
		pathNode * temp = block[i].wordinfo;
		while (temp != NULL)
		{
			if (StringCompare(path, temp->path))
			{
				if (max < temp->occurance)
					max = temp->occurance;
				break;   //just for reducing time running
			}
			temp = temp->pnext;
		}
	}
	return max;
}
int query::min_locationInternal(string path)
{
	int min = INT_MAX;
	for (int i = 0; i < num; i++)
	{
		pathNode * temp = block[i].wordinfo;
		while (temp != NULL)
		{
			if (StringCompare(path, temp->path))
			{
				if (min < temp->occurance)
					min = temp->occurance;
				break;   //just for reducing time running
			}
			temp = temp->pnext;
		}
	}
	return min;
}
//Minh --> Ranking process
int query::is_Near(string path)
{
	return is_NearInternal(path);
}
int query::is_NearInternal(string path)
{
	int count = 0,max = 0;
	string s,temp;
	ifstream fin;
	if (path == "")return -1;
	fin.open(path);
	while (!fin.eof())
	{
		getline(fin, s, '\.');
		for (int i = 0; i < s.length() + 1; i++)
		{
			s[i] = tolower(s[i]);
			temp += s[i];
			if (s[i] == ' ')
			{
				temp.clear();
			}
			if (StringCompare(temp,block[count].s) && block[count].s!="")
				count++;
		}
		if (count > max)max = count;   // re-init max value
		count = 0;
	}
	fin.close();
	return max;
}
void query::occur_nearword_Ranking()
{
	occur_nearword_RankingInternal();
}
void query::occur_nearword_RankingInternal()
{
	int temp;
	int *arr = new int[rankingNum];
	for (int i = 0; i < rankingNum; i++)
	{
		arr[i] = is_Near(ranking[i].path);
	}
	//sort descending 
	for(int i = 0; i<rankingNum; i++)
	{
		for (int j = i + 1; j<rankingNum; j++)
		{
			if (arr[i]<arr[j])
			{
				swap(arr[i], arr[j]);
				swap(ranking[i], ranking[j]);
			}
		}
	}
	//re-sort with occurance for same arr value
	for (int i = 0; i < 5; i++)
	{
		for (int j = i; j < 5; j++)
		{
			if (arr[i] == arr[j])
			{
				if (ranking[i].occurance_in1path > ranking[j].occurance_in1path)
				{
					swap(arr[i], arr[j]);
					swap(ranking[i], ranking[j]);
				}
			}
		}
	}
	delete[] arr;
}
void query::idensity_Ranking()
{
	idensity_RankingInternal();
}
void query::idensity_RankingInternal()
{
	int n = rankingNum;
	int index = 1;
	int count = 0;
	while (n != 0)
	{
		for (int i = 0; i < num; i++)
		{
			//find common path
			while (block[i].wordinfo != NULL)
			{
				count = 0;
				for (int j = i + 1; j < num; j++)
				{
					//check path of this block
					if (is_Commonpath(j, block[i].wordinfo->path))
						count++;
				}
				if (count == n)
				{
					ranking[index].path = block[i].wordinfo->path;
					index++;
				}
				block[i].wordinfo=block[i].wordinfo->pnext;
			}
		}
		n--;
	}
}
bool query::is_Commonpath(int pos,string path)
{
	return is_CommonpathInternal(pos,path);
}
bool query::is_CommonpathInternal(int pos,string path)
{
	while (block[pos].wordinfo != NULL)
	{
		if (StringCompare(path, block[pos].wordinfo->path))return true;
		block[pos].wordinfo = block[pos].wordinfo->pnext;
	}
	return false;
}

//Huy
int query::posANDOR()
{
	if (block[1].rank.is_And&&block[2].rank.is_Or)
		return 3;
	if (block[1].rank.is_Or&&block[2].rank.is_And)
		return 4;
	int countAND = 0;
	int countOR = 0;
	for (int i = 0; i < num; i++)
	{
		if (block[i].rank.is_And)
			countAND++;
		if (block[i].rank.is_Or)
			countOR++;
	}
	if (countAND == num - 1)
		return 1;
	else if (countOR == num - 1)
		return 2;
}
void query::calculate_Occurance()
{
	calculate_OccuranceInternal();
	return;
}
void query::calculate_OccuranceInternal()
{
	for (int i = 0; i < num; i++)
	{
		pathNode *temp = block[i].wordinfo;
		while (block[i].wordinfo != NULL)
		{
			int t = (int(block[i].wordinfo->path.at(16)) - 48) * 10 + int((block[i].wordinfo->path.at(17) - 48));
			if (block[i].wordinfo->path.at(18) == '0')
				t = 100;
			ranking[t].occurance_in1path += block[i].wordinfo->occurance;
			ranking[t].path = block[i].wordinfo->path;
			block[i].wordinfo = block[i].wordinfo->pnext;
		}
		block[i].wordinfo = temp;
	}
}
void query::printOccurance_in1path()
{
	printOccurance_in1pathInternal();
}
bool query::notFeature()
{
	for (int i = 0; i < num; i++)
	{
		if (block[i].rank.is_Feature)
			return false;
	}
	return true;
}
void query::clear_occurance1path()
{
	clear_Occurance1pathInternal();
}
void query::processFeature(StopWordChaining stopword)
{
	processFeatureInternal(stopword);
}
void query::preRankingInternal()
{
	RankingSystem tg;
	for (int i = 1; i < 101; i++)
	{
		for (int j = 100; j >i; j--)
		{
			if (ranking[j - 1].occurance_in1path < ranking[j].occurance_in1path)
			{
				tg = ranking[j - 1];
				ranking[j - 1] = ranking[j];
				ranking[j] = tg;
			}
		}
	}
	for (int i = 1; i <= 100; i++)
	{
		if (ranking[i].path != "")
			rankingNum++;
	}
	idensity_Ranking();
	//occur_nearword_Ranking();
	for (int i = 1; i < rankingNum; i++)
	{
		for (int j = 1; j < i; j++)
		{
			if (!ranking[j].is_Feature && ranking[i].is_Feature)
				swap(ranking[j], ranking[i]);
		}
	}
}
void query::preRanking()
{
	preRankingInternal();
}
void query::printOccurance_in1pathInternal()
{
	if (block[0].s == "0")
	{
		cout << "END!" << endl;
		return;
	}
	if (notFeature())
	{
		for (int i = 1; i <= 5; i++)
		{
			if (ranking[i].path != "")
			{
				cout << ranking[i].path << endl;
				cout << "/////////////////////////////////////////////////" << endl;
				Print_process(ranking[i].path,block[0].rank.is_WildCard);
				cout << "/////////////////////////////////////////////////" << endl;
				//cout << " occurance:" << ranking[i].occurance_in1path << endl;
			}
		}
	}
	else if (ANDorOR())
	{
		if (posANDOR() == 2)
		{
			for (int i = 1; i <= 100; i++)
			{
				if (ranking[i].path != "" || ranking[i].is_Or)
				{
					cout << ranking[i].path << endl;
					Print_process(ranking[i].path,block[0].rank.is_WildCard);
					//cout << " occurance:" << ranking[i].occurance_in1path << endl;
				}
			}
		}
		else if (posANDOR() == 1)
		{
			for (int i = 1; i <= 100; i++)
			{
				if (ranking[i].is_And)
				{
					cout << ranking[i].path << endl;
					Print_process(ranking[i].path,block[0].rank.is_WildCard);
					//cout << " occurance:" << ranking[i].occurance_in1path << endl;
				}
			}
		}
		else if (posANDOR() == 3)
		{
			for (int i = 1; i <= 100; i++)
			{
				if (ranking[i].is_And || ranking[i].is_Or)
				{
					cout << ranking[i].path << endl;
					Print_process(ranking[i].path,block[0].rank.is_WildCard);
					//cout << " occurance:" << ranking[i].occurance_in1path << endl;
				}
			}
		}
		else if (posANDOR() == 4)
		{
			for (int i = 1; i <= 100; i++)
			{
				if ((ranking[i].path != "" && !ranking[i].is_Or) || (ranking[i].is_And&&ranking[i].is_Or))
				{
					cout << ranking[i].path << endl;
					Print_process(ranking[i].path,block[0].rank.is_WildCard);
					//cout << " occurance:" << ranking[i].occurance_in1path << endl;
				}
			}
		}
	}
	else if (!notFeature())
	{
		for (int i = 1; i <= 5; i++)
		{
			if (ranking[i].path != "")
			{
				cout << ranking[i].path << endl;
				cout << "/////////////////////////////////////////////////" << endl;
				Print_process(ranking[i].path,block[0].rank.is_WildCard);
				cout << "/////////////////////////////////////////////////" << endl;
				//cout << " occurance:" << ranking[i].occurance_in1path << endl;
			}
		}
	}
}
bool query::ANDorOR()
{
	int count = 0;
	for (int i = 0; i < num; i++)
	{
		if (block[i].rank.is_And || block[i].rank.is_Or)
			count++;
	}
	if (count == 0)
		return false;
	if (count == num - 1)
		return true;
	else return false;
}
void query::clear_Occurance1pathInternal()
{
	for (int i = 1; i <= rankingNum; i++)
	{
		ranking[i].occurance_in1path = 0;
		ranking[i].path = "";
		ranking[i].is_Feature = false;
		ranking[i].is_Minus = false;
		ranking[i].is_File = false;
		ranking[i].is_And = false;
		ranking[i].is_Hashtags = false;
		ranking[i].is_Intitle = false;
		ranking[i].is_Or = false;
		ranking[i].is_WildCard = false;
		ranking[i].is_Match = false;
		ranking[i].is_InRange = false;
		ranking[i].is_Price = false;
		ranking[i].rankingPoint = 0;
		ranking[i].inTitle = 0;
		rankingNum = 0;
	}
}
void query::processFeatureInternal(StopWordChaining stopword)
{
	/*Feature 9 (done)*/ if (block[0].rank.is_Match)
	{
		pathNode *temp = block[0].wordinfo;
		//int t = num;
		while (block[0].wordinfo != NULL)
		{
			int t = (int(block[0].wordinfo->path.at(16)) - 48) * 10 + int((block[0].wordinfo->path.at(17) - 48));
			if (block[0].wordinfo->path.at(18) == '0')
				t = 100;
			if (!stopword.isStopWord(block[0].s))
				ranking[t].occurance_in1path += block[0].wordinfo->occurance;
			ranking[t].rankingPoint++;
			ranking[t].path = block[0].wordinfo->path;
			block[0].wordinfo = block[0].wordinfo->pnext;
		}
		block[0].wordinfo = temp;
		for (int i = 1; i <= 100; i++)
		{
			if (ranking[i].path != "")
			{
				ifstream fin;
				fin.open(ranking[i].path);
				while (!fin.eof())
				{
					string word;
					fin >> word;
					if (block[0].s == word)
					{
						int count = 1;
						for (int j = 1; j < num; j++)
						{
							fin >> word;
							if (word == block[j].s)
								count++;
						}
						if (count == num)
						{
							ranking[i].is_Match = true;
							ranking[i].is_Feature = true;
							continue;
						}
					}
				}
				fin.close();
			}
		}

	}
	/*Feature 10 (done)*/	for (int i = 0; i < num; i++)
	{
		if (block[i].rank.is_WildCard)
		{
			if (i == 0)
			{
				pathNode *temp = block[1].wordinfo;
				//int t = num;
				while (block[1].wordinfo != NULL)
				{
					int t = (int(block[1].wordinfo->path.at(16)) - 48) * 10 + int((block[1].wordinfo->path.at(17) - 48));
					if (block[1].wordinfo->path.at(18) == '0')
						t = 100;
					if (!stopword.isStopWord(block[1].s))
						ranking[t].occurance_in1path += block[1].wordinfo->occurance;
					ranking[t].path = block[1].wordinfo->path;
					ranking[t].rankingPoint++;
					block[1].wordinfo = block[1].wordinfo->pnext;
				}
				block[1].wordinfo = temp;
				for (int i = 1; i <= 100; i++)
				{
					if (ranking[i].path != "")
					{
						ifstream fin;
						fin.open(ranking[i].path);
						while (!fin.eof())
						{
							string word;
							string temp;
							fin >> word;
							if (block[1].s == word)
							{
								if (num == 2)
								{
									ranking[i].is_WildCard = true;
									ranking[i].is_Feature = true;
									continue;
								}
								int count = 2;
								for (int j = 2; j < num; j++)
								{
									fin >> word;
									if (word == block[j].s)
										count++;
								}
								if (count == num)
								{
									ranking[i].is_WildCard = true;
									ranking[i].is_Feature = true;
									continue;
								}
							}
						}
						fin.close();
					}
				}
			}
			else if (i > 0)
			{
				pathNode *temp = block[0].wordinfo;
				//int t = num;
				while (block[0].wordinfo != NULL)
				{
					int t = (int(block[0].wordinfo->path.at(16)) - 48) * 10 + int((block[0].wordinfo->path.at(17) - 48));
					if (block[0].wordinfo->path.at(18) == '0')
						t = 100;
					if (!stopword.isStopWord(block[0].s))
						ranking[t].occurance_in1path += block[0].wordinfo->occurance;
					ranking[t].path = block[0].wordinfo->path;
					block[0].wordinfo = block[0].wordinfo->pnext;
				}
				block[0].wordinfo = temp;
				for (int i = 1; i <= 100; i++)
				{
					if (ranking[i].path != "")
					{
						ifstream fin;
						fin.open(ranking[i].path);
						while (!fin.eof())
						{
							string word;
							string temp;
							fin >> word;
							if (block[0].s == word)
							{
								int count = 1;
								for (int j = 1; j < num; j++)
								{
									if (block[j].s == "*")
									{
										fin >> word;
										count++;
									}
									else
									{
										fin >> word;
										if (word == block[j].s)
											count++;
									}
								}
								if (count == num)
								{
									ranking[i].rankingPoint++;
									ranking[i].is_WildCard = true;
									ranking[i].is_Feature = true;
									continue;
								}
							}
						}
						fin.close();
					}
				}
			}

		}
	}
	/*normal search + (AND and OR)*/ for (int i = 0; i < num; i++)
	{
		if (block[i].s != "*" && !block[i].rank.is_Feature)
		{
			pathNode *temp = block[i].wordinfo;
			while (block[i].wordinfo != NULL)
			{
				int t = (int(block[i].wordinfo->path.at(16)) - 48) * 10 + int((block[i].wordinfo->path.at(17) - 48));
				if (block[i].wordinfo->path.at(18) == '0')
					t = 100;
				if (!stopword.isStopWord(block[i].s))
					ranking[t].occurance_in1path += block[i].wordinfo->occurance;
				ranking[t].path = block[i].wordinfo->path;
				//ranking[t].is_Feature = false;
				ranking[t].rankingPoint++;
				block[i].wordinfo = block[i].wordinfo->pnext;
			}
			block[i].wordinfo = temp;
		}
		/*Feature 1*/ if ((block[i].s != "*"&&block[i].rank.is_And))
		{
			pathNode *temp = block[i].wordinfo;
			while (block[i].wordinfo != NULL)
			{
				int t = (int(block[i].wordinfo->path.at(16)) - 48) * 10 + int((block[i].wordinfo->path.at(17) - 48));
				if (block[i].wordinfo->path.at(18) == '0')
					t = 100;
				pathNode *temp2 = block[i].wordinfo;
				while (block[i - 1].wordinfo != NULL)
				{
					if (ranking[t].path != ""&&ranking[t].path == block[i - 1].wordinfo->path)
					{
						if (!stopword.isStopWord(block[i].s))
							ranking[t].occurance_in1path += block[i].wordinfo->occurance;
						ranking[t].is_And = true;
						ranking[t].is_Feature = true;
						ranking[t].rankingPoint++;
					}
					block[i - 1].wordinfo = block[i - 1].wordinfo->pnext;
				}
				block[i - 1].wordinfo = temp2;
				block[i].wordinfo = block[i].wordinfo->pnext;
			}
			block[i].wordinfo = temp;
		}
		/*Feature 2*/ if (block[i].s != "*"&&block[i].rank.is_Or)
		{
			pathNode *temp = block[i].wordinfo;
			while (block[i].wordinfo != NULL)
			{
				int t = (int(block[i].wordinfo->path.at(16)) - 48) * 10 + int((block[i].wordinfo->path.at(17) - 48));
				if (block[i].wordinfo->path.at(18) == '0')
					t = 100;
				if (ranking[t].path == "")
				{
					if (!stopword.isStopWord(block[i].s))
						ranking[t].occurance_in1path += block[i].wordinfo->occurance;
					ranking[t].is_Or = true;
					ranking[t].is_Feature = true;
					ranking[t].path = block[i].wordinfo->path;
					ranking[t].rankingPoint++;
				}
				block[i].wordinfo = block[i].wordinfo->pnext;
			}
			block[i].wordinfo = temp;
		}

	}
	for (int i = 0; i < num; i++)
	{
		if (!block[i].rank.is_Feature)
			continue;
		if (block[i].rank.is_Feature)
		{
			pathNode *temp = block[i].wordinfo;
			/*Feature 3 (done)*/ if (block[i].rank.is_Minus)
			{
				while (block[i].wordinfo != NULL)
				{
					for (int j = 1; j <= 100; j++)
					{
						if (ranking[j].path == block[i].wordinfo->path)
						{
							ranking[j].path = "";
						}
					}
					block[i].wordinfo = block[i].wordinfo->pnext;
				}
				block[i].wordinfo = temp;
			}
			/*Feature 4 (done)*/ if (block[i].rank.is_Intitle)
			{
				if (i>0)
				{
					for (int j = 1; j <= 100; j++)
					{
						if (ranking[j].path != "")
						{
							ifstream fin;
							string title;
							fin.open(ranking[j].path);
							getline(fin, title);
							string word;
							for (int z = 0; z < title.length() + 1; z++)
							{
								if (title[z] == ' ' || z == title.length())
								{
									ToLower(word);
									ToLower(block[i].s);
									if (word == block[i].s)
									{
										ranking[j].is_Intitle = true;
										ranking[j].is_Feature = true;
										word.clear();
									}
									else word.clear();
								}
								else
									word += title[z];
							}
							fin.close();
						}
					}
				}
				else
				{
					pathNode *temp = block[i].wordinfo;
					while (block[i].wordinfo != NULL)
					{
						int t = (int(block[i].wordinfo->path.at(16)) - 48) * 10 + int((block[i].wordinfo->path.at(17) - 48));
						if (block[i].wordinfo->path.at(18) == '0')
							t = 100;
						if (!stopword.isStopWord(block[i].s))
							ranking[t].occurance_in1path += block[i].wordinfo->occurance;
						ranking[t].path = block[i].wordinfo->path;
						//ranking[t].is_Feature = false;
						ranking[t].rankingPoint++;
						block[i].wordinfo = block[i].wordinfo->pnext;
					}
					block[i].wordinfo = temp;
					for (int j = 1; j <= 100; j++)
						if (ranking[j].path != "")
						{
							ifstream fin;
							string title;
							fin.open(ranking[j].path);
							getline(fin, title);
							string word;
							for (int z = 0; z < title.length() + 1; z++)
							{
								if (title[z] == ' ' || z == title.length())
								{
									ToLower(word);
									ToLower(block[i].s);
									if (word == block[i].s)
									{
										ranking[j].is_Intitle = true;
										ranking[j].is_Feature = true;
										word.clear();
									}
									else word.clear();
								}
								else
									word += title[z];
							}
							fin.close();
						}
				}
			}
			/*Feature 6 done)*/ if (block[i].rank.is_File)
			{
				if (i>0)
				{
					for (int j = 1; j <= 100; j++)
					{
						if (ranking[j].path != ""&&ranking[j].path.substr(19, 3) == block[i].s)
						{
							ranking[j].is_File = true;
							ranking[j].is_Feature = true;
							ranking[j].rankingPoint++;
						}
					}
				}
				else
				{
					ifstream fin;
					fin.open("address.txt");
					while (!fin.eof())
					{
						for (int i = 1; i < 101; i++)
						{
							string address;
							fin >> address;
							ranking[i].path = address;
						}
					}
					for (int j = 1; j <= 100; j++)
					{
						if (ranking[j].path != ""&&ranking[j].path.substr(19, 3) == block[i].s)
						{
							ranking[j].is_File = true;
							ranking[j].is_Feature = true;
							ranking[j].rankingPoint++;
						}
					}

				}
			}
			/*Feature 7 (done)*/ if (block[i].rank.is_Price)
			{
				for (int j = 1; j <= 100; j++)
				{
					pathNode *temp = block[i].wordinfo;
					while (block[i].wordinfo != NULL)
					{
						int t = (int(block[i].wordinfo->path.at(16)) - 48) * 10 + int((block[i].wordinfo->path.at(17) - 48));
						if (block[i].wordinfo->path.at(18) == '0')
							t = 100;
						if (ranking[t].path != "")
						{
							ranking[t].is_Price = true;
							ranking[t].is_Feature = true;
						}
						if (!stopword.isStopWord(block[i].s))
							ranking[t].occurance_in1path += block[i].wordinfo->occurance;
						ranking[t].path = block[i].wordinfo->path;
						ranking[t].rankingPoint++;
						block[i].wordinfo = block[i].wordinfo->pnext;
					}
					block[i].wordinfo = temp;
				}
			}
			/*Feature 11 (not yet)*/if (block[i].rank.is_InRange)
			{
				int high = StringtoNumber(block[i].s);
				int low = StringtoNumber(block[i + 1].s);
				for (int j = 1; j <= 100; j++)
				{
					if (ranking[j].path != "")
					{
						ifstream fin;
						fin.open(ranking[j].path);
						while (!fin.eof())
						{
							string word;
							fin >> word;
							//if (checkNumber(word))
							//{
							if (StringtoNumber(word) >= low&&StringtoNumber(word) <= high)
							{
								ranking[j].is_InRange = true;
								ranking[j].is_Feature = true;
							}
							//}
						}
						fin.close();
					}
				}
			}
			/*Feature 12*/ if (block[i].rank.is_Set)
			{
				pathNode *temp = block[i].wordinfo;
				while (block[i].wordinfo != NULL)
				{
					int t = (int(block[i].wordinfo->path.at(16)) - 48) * 10 + int((block[i].wordinfo->path.at(17) - 48));
					if (block[i].wordinfo->path.at(18) == '0')
						t = 100;
					if (!stopword.isStopWord(block[i].s))
						ranking[t].occurance_in1path += block[i].wordinfo->occurance;
					ranking[t].path = block[i].wordinfo->path;
					ranking[t].is_Feature = true;
					ranking[t].rankingPoint++;
					block[i].wordinfo = block[i].wordinfo->pnext;
				}
				block[i].wordinfo = temp;
			}
		}
	}
}

//History
void query::SaveToHistory(std::vector<std::string> &dict)
{
	History(dict);
	return;
}
void query::History(std::vector<std::string> &dict)
{
	if (num == 0) return;
	string sentence;
	for (int i = 0; i < num; i++)
	{
		sentence += block[i].s + " ";

	}
	ofstream fout;
	fout.open("dict.txt", ios::app);
	fout << endl;
	fout << sentence;
	fout.close();
	dict.push_back(sentence);
	return;
}

//Ranking system
// Feature 1
bool RankingSystem::isAnd(string s)
{
	if (StringCompare(s, "AND")) return true;
	else return false;

}
//Feature 2
bool RankingSystem::isOr(string s)
{
	if (StringCompare(s, "OR")) return true;
	else return false;

}
// Feature 3
bool RankingSystem::isMinus(string s)
{
	if (s.find("-") != std::string::npos) return true;
	else return false;
}
// Feature 4
bool RankingSystem::isIntitle(string s)
{
	if (s.find("intitle:") != std::string::npos) return true;
	else return false;

}
//Feature 6
bool RankingSystem::isFile(string s)
{
	if (s.find("filetype:") != std::string::npos) return true;
	else return false;
}
//Feature 7
bool RankingSystem::isPrice(string s)
{
	if (s.find("$") != std::string::npos) return true;
	else return false;
}
//Feature 8
bool RankingSystem::isHashtags(string s)
{
	if (s.find("#") != std::string::npos) return true;
	else return false;
}
// Feature 9
bool RankingSystem::isMatch(string s)
{
	if (s.find("\"") != std::string::npos)return true;
	return false;
}
// Feature 10
bool RankingSystem::isWildCard(string s)
{
	if (s.find("*") != std::string::npos) return true;
	else return false;
}
// Feature 11
bool RankingSystem::isInRange(string s)
{
	if (s.find("..") != std::string::npos) return true;
	else return false;
}
// Feature 12
bool RankingSystem::isSet(string s)
{
	if (s.find("~") != std::string::npos) return true;
	else return false;
}

void RankingSystem::isFeature(string s)
{
	ToLower(s);
	if (isAnd(s))
	{
		cout << "And\n";
	}
	if (isOr(s))
	{
		cout << "Or\n";
	}
	if (isMinus(s))
	{
		cout << "Minus\n";
	}
	if (isIntitle(s))
	{
		cout << "Intitle\n";
	}
	if (isFile(s))
	{
		cout << "File\n";
	}
	if (isPrice(s))
	{
		cout << "Price\n";
	}
	if (isHashtags(s))
	{
		cout << "Hashtags\n";
	}
	if (isMatch(s))
	{
		cout << "Match\n";
	}
	if (isWildCard(s))
	{
		cout << "Wildcard\n";
	}
	if (isInRange(s))
	{
		cout << "In range\n";
	}
	return;
}

//////////////////////////////////////////////////
