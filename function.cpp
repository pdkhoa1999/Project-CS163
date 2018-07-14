#include "Header.h"
void wordTrie::add(string path)
{
	ifstream fin;
	fin.open(path);
	if (fin)
	{
		while (!fin.eof())
		{
			wordNode* cur = NULL;
			int n = 0;
			string word = takeWord(fin, n);

			if (root == NULL) root = new wordNode;
			cur = root;
			for (int i = 0; i < n; i++)
			{

				char x = tolower(word[i]);
				if (x - 'a' >= 26 || x - 'a' < 0)//if not alphabet ->break
					break;
				if (cur->children[x - 'a'] == NULL)
				{
					cur->children[x - 'a'] = new wordNode;
				}
				cur = cur->children[x - 'a'];
			}
			if (cur->phead == NULL)//create first data node for the word
			{
				cur->phead = new pathNode;
				cur->phead->occurance++;
				cur->phead->path = path;
				cur->phead->pnext = NULL;
				cur->n++;
			}
			else
			{
				pathNode*curpath = cur->phead;
				while (curpath->pnext != NULL&&curpath->path != path)//create nodes after the first node
				{
					curpath = curpath->pnext;
				}
				if (curpath->path == path)//the file already in the data
				{
					curpath->occurance++;
				}
				else
				{
					curpath->pnext = new pathNode;//new file
					curpath = curpath->pnext;
					curpath->path = path;
					curpath->occurance++;
					curpath->pnext = NULL;
					cur->n++;
				}

			}

		}
	}
	fin.close();
}
bool checkValidation(char x)
{
	if ((x>64 && x<91) || (x>96 && x<123))
		return true;
	return false;
}
string wordTrie::takeWord(ifstream &fin, int &n)
{
	string word, word2, word3;
	char x;
	fin >> x;
	while (!checkValidation(x) && fin)fin >> x;
	word += x;
	getline(fin, word2, ' ');
	word3 = word + word2;
	n = word3.length();

	return word3;
}

void wordTrie::printInternal(wordNode*root, string word)
{
	if (root->phead != NULL)
	{
		cout << word << "-" << root->n << "-";
		pathNode *cur = root->phead;
		while (cur != NULL)
		{
			cout << cur->path << "," << cur->occurance << ";";
			cur = cur->pnext;
		}
		cout << endl;
	}
	for (int i = 0; i < 26; i++)
	{
		if (root->children[i] != NULL)
		{
			word += 'a' + i;
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
				if (x - 'a' >= 26 || x - 'a' < 0)//if not alphabet ->break
					break;
				if (cur->children[x - 'a'] == NULL)
				{
					cur->children[x - 'a'] = new wordNode;
				}
				cur = cur->children[x - 'a'];
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
					cur->phead->path = path;
					cur->phead->pnext = NULL;
				}
				else
				{
					curpath->pnext = new pathNode;
					curpath = curpath->pnext;
					curpath->occurance += x;
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
				fout << cur->path << "," << cur->occurance << ";";
				cur = cur->pnext;
			}
			fout << endl;
		}
		for (int i = 0; i < 26; i++)
		{
			if (root->children[i] != NULL)
			{
				word += 'a' + i;
				saveInternal(fout, root->children[i], word);
				word.pop_back();
			}
		}
	}
}
void wordTrie::savewordFile()
{
	ofstream fout;
	fout.open("wordFile.txt");
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
			if (cur!=NULL && i == s.length() && cur->phead != NULL)return true;
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
	char x;
	//function filter 
	while (checkValidation(s[i]) && i<s.length()+1)
	{
		if (cur == NULL)return NULL;
		x = tolower(s[i]);
		cur = cur->children[s[i] - 'a'];
		i++;
		if (cur != NULL && i == s.length() && cur->phead != NULL)return cur;
	}
	return NULL;	
}

void query::insert_queryInternal(string & s, wordTrie root,int & n,StopWordChaining stopword)
{
	string temp,ismeaning,prev="\0";
	bool isconnected = false;
	ismeaning.clear();
	wordNode *word_temp = NULL;
	for (int i = 0; i < s.length() + 1; i++)
	{

		if ((s[i] == ' ' || i == s.length()))
		{
			if (stopword.isStopWord(temp))
			{
				prev.clear();
				temp.clear();
			}
			else {
				word_temp = root.Findword(temp);
				if (!stopword.isStopWord(temp) && word_temp != NULL)
				{
					block[n].s = temp;
					block[n].wordinfo = word_temp->phead;
					n++;
				}
				for (int j = 0; j < temp.length() + 1; j++)
				{

					ismeaning += temp[j];
					if (prev != "\0" && ismeaning != "") {
						word_temp = root.Findword(prev + ismeaning);
						if (!stopword.isStopWord(prev + ismeaning) && word_temp != NULL && !word_exist(prev + ismeaning) && prev + ismeaning != "")
						{
							block[n].s = prev + ismeaning;
							block[n].wordinfo = word_temp->phead;
							if (!root.search(ismeaning) && !stopword.isStopWord(ismeaning) && !word_exist(ismeaning)) {
								block[n].isMerge = true;
							}
							else
								block[n].isAnd = true;
							prev += ismeaning;
							ismeaning.clear();
							n++;
						}
					}
					word_temp = root.Findword(ismeaning);
					if (!stopword.isStopWord(ismeaning) && word_temp != NULL && !word_exist(ismeaning) && ismeaning != "")
					{
						block[n].s = ismeaning;
						block[n].wordinfo = word_temp->phead;
						block[n].isAnd = true;
						prev = ismeaning;
						ismeaning.clear();
						n++;
					}

				}
			}
			ismeaning.clear();
			temp.clear();
		}
		else
			temp += s[i];
	}

	//Just print to test 
	for (int i = 0; i < n; i++)
	{
		cout << block[i].s <<" " << block[i].wordinfo->occurance<<" "<<block[i].wordinfo->path << endl;
	}
}
bool query::word_exist(string s, int n, keyword_block * block)
{
	for (int i = 0; i < n; i++)
		if (block[i].s == s)return true;
	return false;
}

//Stopword
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
void StopWordChaining::RuncreateChaining()
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
	for (int i = 0; i < s.length(); i++) tolower(s[i]);
	return;
}


// Feature 1
bool RankingSystem::isAnd(string s)
{
	if (StringCompare(s, "and") || s.find("+") != std::string::npos) return true;
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
