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
		num = 0;
	}
	void insert_query(string & s,wordTrie  root,StopWordChaining stopword)
	{
		insert_queryInternal(s, root,num,stopword);
	}
	bool word_exist(string s)
	{
		return word_exist(s, num, block);
	}
private:
	keyword_block block[34]; //maximum we get 34 keywords after split & merge & filter.
	int num=0;   
	void insert_queryInternal(string & s,wordTrie  root,int & n,StopWordChaining stopword);
	bool word_exist(string s, int n, keyword_block * block);
};
//

class RankingSystem
{
private:
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


public:
	void isFeature(string s);
};
//
void ToLower(string & s);
bool StringCompare(string s1, string s2);
bool checkValidation(char x);//check if a valid char or not
#endif
