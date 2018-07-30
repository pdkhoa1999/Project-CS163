#pragma once
#ifndef  _header_h_
#define _header_h_
#include<iostream>
#include<fstream>
#include<string>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <filesystem>
#include <algorithm>
using namespace std;
//HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//Loading
struct pathNode {//contain data of a single word
	string path;
	pathNode* pnext;
	int pos[50];
	int occurance;
	pathNode() { occurance = 0; }
};
struct wordNode {//one node in the wordtrie
	pathNode*phead = NULL;
	int n;
	wordNode*children[38] = {};
	wordNode() { n = 0; }


};
struct wordTrie {
private:
	wordNode * root;
	void printInternal(wordNode*root, string word);//test print
	string takeWord(ifstream &fin, int &n);
	void saveInternal(ofstream &fout, wordNode*root, string word);
	wordNode* Findword(string s, wordNode * root);
	string MakeUpString(string s);
	string SplitString(string s);
public:
	void print();//test print
	wordTrie() { root = NULL; }
	void loadwordFile(string path);//load trie from wordfile
	void add(string path);//add a file to wordttrie
	void savewordFile();//save trie to word file
	bool search(string s, wordNode *root);
	wordNode* Findword(string s);
	string ShowMakeUpString(string s);
	string ShowSplitString(string s);
};
bool checkValidation(char x);//check if a valid char or not
							 //Stopword
							 // Stopwords for feature 
struct Node
{
	string s;
	Node *next;
	Node()
	{
		next = NULL;
	}
};
class LinkedList
{
private:
	Node * head;
	void InsertWords(string s, Node *&cur);
	Node* FindWord(string s, Node*cur);
public:
	LinkedList()
	{
		head = NULL;
	}
	void RunInsertWords(string s);
	Node* RunFindWord(string s);
};
struct StopWordChaining
{
private:
	LinkedList arr[420];

public:
	StopWordChaining();
	bool isStopWord(string s);
	int HashWord(string s);
};
//ranking
class RankingSystem
{
public:
	int occurance_in1path = 0;
	string path;
	int rankingPoint = 0;
	int inTitle = 0;
	bool is_And = false;// Feature 1
	bool is_Or1 = false;//Feature 2
	bool is_Or = false; //Feature 2
	bool is_Minus = false;// Feature 3 //done
	bool is_Intitle = false;// Feature 4 //done
	bool is_File = false;//Feature 6 //done
	bool is_Price = false;//Feature 7 //done
	bool is_Hashtags = false; //Feature 8	
	bool is_Match = false; // Feature 9 //done
	bool is_WildCard = false; // Feature 10 //done
	bool is_InRange = false; // Feature 11 //done (maybe?)
	bool is_Feature = false;
	bool morethan1 = false;
	bool key = false;
	//ranking (+1 ranking point for each standard)
	bool intitle = false;
	bool seamless = false;

	///////////// Function
	bool isAnd(string s);// Feature 1
	bool isOr(string s);//Feature 2
	bool isMinus(string s);// Feature 3
	bool isIntitle(string s);// Feature 4
	bool isFile(string s);//Feature 6
	bool isPrice(string s);//Feature 7
	bool isHashtags(string s); //Feature 8	
	bool isMatch(string s); // Feature 9
	bool isWildCard(string s); // Feature 10
	bool isInRange(string s); // Feature 11
	void isFeature(string s);
};
////////////////////////
//query
struct keyword_block
{
	string s;
	pathNode *wordinfo; //contain address and it's frequency
	RankingSystem rank;
};
//To manage each keyword_block
struct query
{
public:
	query()
	{
		for (int i = 0; i < 34; i++)
			block[i].wordinfo = NULL;
		num = 0;
		rankingNum = 0;
	}
	void load_Query(string & s, wordTrie  root);
	void insert_Query(string s, int pos, wordTrie root);
	void remove_Query(int pos, int &n);
	int  find_Query(string s); // return block position 
	bool word_exist(string s);
	bool Linearsearch(wordTrie root, int i);
	void Exactsearch(string s);
	void inrange_Feature(int i, wordTrie root, int & n);
	void plus_Feature(int i, wordTrie root, int n);
	void and_Feature(int i, int n);
	void or_Feature(int i, int n);
	void minus_Feature(int i, wordTrie root, int n);
	void intitle_Feature(int i, wordTrie root, int n);
	void file_Feature(int i, wordTrie root, int n);
	void wildcard_Feature(int i, int n);
	void match_Feature(int i, wordTrie root, int n);
	void process_Query(string s, wordTrie  root, StopWordChaining  stopword);
	void upduate_Address(int &i, wordTrie root, int &n);
	int min_location(string path);
	int max_location(string path);
	bool is_Print(string s);
	void clear_Query();
	
	//Minh - ranking
	void occur_nearword_Ranking();
	int is_Near(string path);

	//Huy
	void preRanking();
	void clear_occurance1path();
	void calculate_Occurance();
	void printOccurance_in1path();
	void processFeature();
	void calculateEachBlock();
	bool notFeature();
	bool ANDorOR();//check xem co phai feature 1/2 ko
	int posANDOR();//1:full AND 2:full OR 3:AND OR 4:OR AND
				   // Function test
	void ShowPrint();
	void Print_process(string path);
	void Print_paragraph(string s);
private:
	keyword_block block[34];
	int  num = 0;
	void upduate_AddressInternal(int &i, wordTrie root, int &n);
	void load_QueryInternal(string &, wordTrie root, int & n);
	void insert_QueryInternal(string s, int pos, wordTrie root, int & n);
	void remove_QueryInternal(int pos, int &n);
	int  find_QueryInternal(string s, int n);
	void clear_QueryInternal(int & n);
	void inrange_FeatureInternal(int i, wordTrie root, int & n);
	void and_FeatureInternal(int i, int n);
	void wildcard_FeatureInternal(int i, int n);
	void file_FeatureInternal(int i, wordTrie root, int n);
	void intitle_FeatureInternal(int i, wordTrie root, int n);
	void minus_FeatureInternal(int i, wordTrie root, int n);
	void or_FeatureInternal(int i, int n);
	void match_FeatureInternal(int i, wordTrie root, int n);
	void plus_FeatureInternal(int i, wordTrie root, int n);
	void process_QueryInternal(string s, wordTrie  root, StopWordChaining stopword, int & n);
	bool LinearseachInternal(wordTrie root, int i);
	bool word_exist(string s, int n, keyword_block * block);
	void Print_processInternal(string path, int n);
	int  min_locationInternal(string path);
	int  max_locationInternal(string path);
	bool is_PrintInternal(string s);
	void Print_paragraphInternal(string s);
	
	//Minh - ranking
	int  is_NearInternal(string path);
	void occur_nearword_RankingInternal();


	//Huy
	void preRankingInternal();
	void clear_Occurance1pathInternal();
	RankingSystem ranking[101];   // Array of path
	int  rankingNum ;
	void calculate_OccuranceInternal();
	void printOccurance_in1pathInternal();
	void rankingAndInternal();
	void calculateEachBlockInternal();
	void processFeatureInternal();
	// Function test
	void PrintToTest();
};
//
void ToLower(string & s);
bool StringCompare(string s1, string s2);
bool checkValidation(char x);//check if a valid char or not
string takeWord(ifstream &fin, int &n);
int  StringtoNumber(string s);
bool checkNumber(string s);
bool IsNeeded(string s1, string s2);
int  HashWord(string s, int i);
#endif
