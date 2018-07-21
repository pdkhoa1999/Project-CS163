#pragma once
#ifndef  _header_h_
#define _header_h_
#include<iostream>
#include<fstream>
#include<string>
#include <Windows.h>
#include <time.h>
#include <filesystem>
using namespace std;
//HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//Loading
struct pathNode {//contain data of a single word
	//inverted index using Linked List
	string path;
	pathNode* pnext;    
	int occurance;
	pathNode() { occurance = 0; }
};
struct wordNode {//one node in the wordtrie
	pathNode*phead = NULL;  //pathHead;
	int n = 0;    //number of file
	wordNode*children[26] = {};
	wordNode()
	{
		n = 0;
	}
};
struct wordTrie {
private:
	wordNode*root;
	void printInternal(wordNode*root, string word);//test print
	string takeWord(ifstream &fin, int &n);
	bool search(string s, wordNode * root);
	wordNode* Findword(string s, wordNode * root);
	void saveInternal(ofstream &fout, wordNode*root, string word);
public:
	wordTrie() {
		root = NULL;
	}

	void print();//test print
	void loadwordFile(string path);//load trie from wordfile
	void add(string path);//add a file to wordttrie
	void savewordFile();//save trie to word file

	bool search(string s)
	{
		return search(s, root);
	}
	wordNode* Findword(string s);
};
//For searching
//User will input a string -> we merge and split them into few blocks.

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
	void RuncreateChaining();
	bool isStopWord(string s);
	int HashWord(string s);
};
//ranking
class RankingSystem
{
public:
	bool is_Merge;
	bool is_And;// Feature 1
	bool is_Or;//Feature 2
	bool is_Minus;// Feature 3
	bool is_Intitle;// Feature 4
	bool is_File;//Feature 6
	bool is_Price;//Feature 7
	bool is_Hashtags; //Feature 8	
	bool is_Match; // Feature 9(uncompleted!!)
	bool is_WildCard; // Feature 10
	bool is_InRange; // Feature 11
///////////// Function
	bool isAnd(string s);// Feature 1
	bool isOr(string s);//Feature 2
	bool isMinus(string s);// Feature 3
	bool isIntitle(string s);// Feature 4
	bool isFile(string s);//Feature 6
	bool isPrice(string s);//Feature 7
	bool isHashtags(string s); //Feature 8	
	bool isMatch(string s); // Feature 9(uncompleted!!)
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
	int isFeature = 0; // from 1 to  12 kind of feature , if 0 , it's not
	RankingSystem rank;		
};
//To manage each keyword_block
struct query
{
public:
	query()
	{
		num = 0;
	}
	void load_Query(string & s,wordTrie  root);
	void insert_Query(string s,int pos);
	void remove_Query(int pos);
	int  find_Query(string s); // return block position 
	bool word_exist(string s);
	void Linearsearch(wordTrie root,int pos);
	void Exactsearch(string s);
	void process_Query(query q,string s,wordTrie  root, StopWordChaining * stopword);
	// Function test
	void ShowPrint();
private:
	keyword_block block[34];
	int  num=0;  
	void load_QueryInternal(string & s,wordTrie root,int & n);
	void insert_QueryInternal(string s,int pos,int & n);
	void remove_QueryInternal(int pos,int &n);
	int  find_QueryInternal(string s, int n);
	void process_QueryInternal(query q,string s, wordTrie  root, StopWordChaining * stopword,int & n);
	void LinearseachInternal(wordTrie root,int pos, int &n);
	bool word_exist(string s, int n, keyword_block * block);
	// Function test
	void PrintToTest();
};
//
void ToLower(string & s);
bool StringCompare(string s1, string s2);
bool checkValidation(char x);//check if a valid char or not
#endif
