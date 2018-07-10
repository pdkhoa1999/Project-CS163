#include "Header.h"

void wordTrie::add(string path)
{
	ifstream fin;
	fin.open(path);
	if (fin)
	{
		wordNode*cur = NULL;
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
				if (x - 'a' >= 26 || x - 'a' < 0)
					break;
				if (cur->children[x - 'a'] == NULL)
				{
					cur->children[x - 'a'] = new wordNode;
				}
				cur = cur->children[x - 'a'];
			}
			if (cur->phead == NULL)
			{
				cur->phead = new pathNode;
				cur->phead->occurance++;
				cur->phead->path = path;
				cur->phead->pnext = NULL;
			}
			else
			{
				pathNode*curpath = cur->phead;
				while (curpath->pnext != NULL&&curpath->path != path)
				{
					curpath = curpath->pnext;
				}
				if (curpath->path == path)
				{
					curpath->occurance++;
				}
				else
				{
					curpath->pnext = new pathNode;
					curpath = curpath->pnext;
					curpath->path = path;
					curpath->occurance++;
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
	while (!checkValidation(x))fin >> x;
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
		cout << word << "-";
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
	while (checkValidation(s[i]) && i<s.length())
	{
		if (cur == NULL)return NULL;
		x = tolower(s[i]);
		cur = cur->children[s[i] - 'a'];
		i++;
		if (cur != NULL && i == s.length() && cur->phead != NULL)return cur;
	}
	return NULL;
}

void query::insert_queryInternal(string & s, wordTrie  root,int & n)
{
	string trial, temp = " ";
	wordNode * word_temp;
	//split into meaning words
	for (int i = 0; i < s.length(); i++)
	{
		trial += s[i];
		if (root.search(trial))
		{
			trial.insert(i, temp);
		}
	}
	temp = "\0";
	bool iscont = true;

	for (int i = 0; i < trial.length() + 1; i++)
	{
		string prev = "\0";
		word_temp = root.Findword(temp);
		//if(trial == stopword)iscont=false;
		
		if (word_temp!=NULL && trial[i]!=' ')
		{
			block[n] = new keyword_block();
			block[n]->s = temp;
			//upduate address
			block[n]->wordinfo = word_temp->phead;
			n++;
		}

		word_temp = root.Findword(prev + temp);
		if (word_temp!=NULL && prev != "\0")
		{
			block[n] = new keyword_block();
			block[n]->s = prev + temp;
			block[n]->wordinfo = word_temp->phead; //upduate address
			n++;
			block[n]->isMerge = true; //merged word
			iscont = true;
			prev = temp;
			temp = "\0";
		}
		if (trial[i] != ' ')temp += trial[i];
	}

	//Just print to test 
	for (int i = 0; i < n; i++)
	{
		cout << block[i]->s <<" " << block[i]->wordinfo->occurance<<" "<<block[i]->wordinfo->path << endl;
	}
}
