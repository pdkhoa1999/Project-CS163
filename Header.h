#pragma once
#ifndef  _header_h_
#define _header_h_
#include<iostream>
#include<fstream>
#include<string>
#include <Windows.h>
#include <time.h>
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
	wordNode*children[26] = {};
};
struct wordTrie {
private:
	wordNode*root;
	void printInternal(wordNode*root, string word);//test print
	string takeWord(ifstream &fin, int &n);
	bool search(string s, wordNode * root);
	wordNode* Findword(string s, wordNode * root);

public:
	void print();//test print
	wordTrie() { 
		root = NULL;
	}
	void loadwordFile(string path);//load trie from wordfile
	void add(string path);//add a file to wordttrie
	bool search(string s)
	{
		return search(s, root);
	}
	wordNode* Findword(string s);
};
//For searching
//User will input a string -> we merge and split them into few blocks.

struct keyword_block
{
	string s;
	pathNode *wordinfo; //contain address and it's frequency
	bool isMerge = false; // For ranking higher
	bool isFactor = false; // For ranking higher .From feature 
};
//To manage each keyword_block
struct query
{
public:
	query()
	{
		n = 0;
	}
	void insert_query(string & s,wordTrie  root)
	{
		insert_queryInternal(s, root,n);
	}

private:
	keyword_block *block[34]; //maximum we get 34 keywords after split & merge & filter.
	int n;   
	void insert_queryInternal(string & s,wordTrie  root,int & n);
};
//
bool checkValidation(char x);//check if a valid char or not
void print(string input, query * q);	
#endif
