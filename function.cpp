#include "Header.h"
StopWordChaining sw;
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

			if (!sw.isStopWord(word)) {
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
	}
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
		else if(s[i]>='0' && s[i]<='9')
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
	int t = s1.length() * 100 / (s2.length());
	if (t >= 80) return true;
	else if (s1.find(",") != std::string::npos && t>70) return true;
	else return false;
}
//Query
bool query::word_exist(string s)
{
	return word_exist(s, num, block);
}
void query::load_Query(string & s,wordTrie  root)
{
	load_QueryInternal(s,root,num);
}
void query::insert_Query(string s, int pos,wordTrie root)
{
	insert_QueryInternal(s,pos,root,num);
}
int query::find_Query(string s)
{
	return find_QueryInternal(s, num);
}														 
void query::remove_Query(int pos,int &n)
{
	remove_QueryInternal(pos,n);
}
bool query::Linearsearch(wordTrie root,int i)
{
	return LinearseachInternal(root, i);
}										 
void query::process_Query(string s, wordTrie  root, StopWordChaining stopword)
{
	process_QueryInternal(s,root,stopword,num);
}
void query::clear_Query()
{
	clear_QueryInternal(num);
}
void query::inrange_Feature(int i,wordTrie root, int & n)
{
	inrange_FeatureInternal(i,root, n);
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
void query::wildcard_Feature(int i,int n)
{
	wildcard_FeatureInternal(i,n);
}
void query::upduate_Address(int &i, wordTrie root, int &n)
{
	upduate_AddressInternal(i, root, n);
}
void query::match_Feature(int i, wordTrie root, int n)
{
	match_FeatureInternal(i, root, n);
}

void query::match_FeatureInternal(int i, wordTrie root, int n)
{
	block[0].s.erase(0,1);
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
	cout << "Wilcard Feature" << endl;
	block[i].wordinfo = NULL;
	for (int j = 0; j < n; j++) {
		block[i].rank.is_WildCard = true;
	}
}
void query::file_FeatureInternal(int i, wordTrie root, int n)
{
	block[i].s.erase(0, 8);
	string temp = block[i].s;
	remove_Query(i, n);
	insert_Query(temp, i, root);
	block[i].rank.is_File = true;
	cout << "Filetype Feature " << endl;
}
void query::intitle_FeatureInternal(int i, wordTrie root, int n)
{
	block[i].s.erase(0, 8);
	string temp = block[i].s;
	remove_Query(i, n);
	insert_Query(temp, i, root);
	block[i].rank.is_Intitle = true;
}
void query::minus_FeatureInternal(int i, wordTrie root, int n)
{
	block[i].s.erase(block[i].s.begin(), block[i].s.begin() + 1);
	string temp = block[i].s;
	remove_Query(i, n);
	insert_Query(temp, i, root);
	block[i].rank.is_Minus = true;
}
void query::or_FeatureInternal(int i, int n)
{
	if (i > 1)block[i - 1].rank.is_Or = true;
	block[i + 1].rank.is_Or = true;
	remove_Query(i, n);
}
void query::and_FeatureInternal(int i, int n)
{
	if (i > 1)block[i - 1].rank.is_And = true;
	block[i + 1].rank.is_And = true;
	remove_Query(i, n);
}
void query::plus_FeatureInternal(int i, wordTrie root, int n)
{
	block[i].s.erase(0, 1);
	string temp = block[i].s;
	remove_Query(i, n);
	insert_Query(temp, i, root);
	block[i].rank.is_And = true;
}
void query::inrange_FeatureInternal(int i,wordTrie root, int & n)
{
	string temp;
	int j = 0;
	block[i].rank.is_InRange = true;
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
void query::load_QueryInternal(string & s,wordTrie root,int & n)
{
	string temp;
	for (int i = 0; i < s.length() + 1; i++)
	{
		if (s[i] == ' ' || i == s.length())
		{
			block[n].s = temp;
			wordNode * temp1= root.Findword(block[n].s);
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
		block[i].s = "";
	n = 0;
}
void query::insert_QueryInternal(string s,int pos,wordTrie root,int & n)
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
		if (block[i].s == s)return true;
	return false;
}
bool query::LinearseachInternal(wordTrie root,int i)
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
void query::process_QueryInternal(string s, wordTrie  root, StopWordChaining stopword,int &n)
{	
	bool isFeature=false;
	load_Query(s,root);
	if (block[0].rank.isMatch(block[0].s))
	{
		match_Feature(0, root, n);
	}
	else {
		for (int i = 0; i < n; i++)
		{
			isFeature = false;
			if (stopword.isStopWord(block[i].s))
			{
				remove_Query(i, n);
				i--;
				continue;
			}
			if (block[i].rank.isInRange(block[i].s))
			{
				isFeature = true;
				inrange_Feature(i, root, n);
			}
			if (block[i].rank.isAnd(block[i].s))
			{
				isFeature = true;
				and_Feature(i, n);
				i--;
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
				i--;
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
			/*if (!isFeature)
			{
				Linearsearch(root, i, n);
			}*/
			upduate_Address(i, root, n);
		}
	}
}
void query:: PrintToTest()
{
	if (num == 0)cout << "Not Found !!!" << endl;
	else {
		for (int i = 0; i < num; i++)
		{
			cout << block[i].s << endl;
			while (block[i].wordinfo != NULL)
			{
				cout << block[i].wordinfo->path << " " << block[i].wordinfo->occurance << endl;
				block[i].wordinfo=block[i].wordinfo->pnext;
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

//Ranking system
// Feature 1
bool RankingSystem::isAnd(string s)
{
	if (StringCompare(s, "and") || StringCompare(s,"AND")) return true;
	else return false;

}
//Feature 2
bool RankingSystem::isOr(string s)
{
	if (StringCompare(s, "or")) return true;
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
	if (s.find("intitle") != std::string::npos) return true;
	else return false;

}
//Feature 6
bool RankingSystem::isFile(string s)
{
	if (s.find(".txt") != std::string::npos || s.find(":txt") != std::string::npos) return true;
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
	if (s[0]=='"' || s[s.length()]=='"')return true;
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
