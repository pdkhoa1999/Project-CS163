#pragma once
#ifndef  _header_h_
#define _header_h_
#include<iostream>
#include<fstream>
#include<string>
#include <Windows.h>
#include <time.h>
using namespace std;

//Loading
struct pathNode {//contain data of a single word
	//inverted index using Linked List
	string path;
	pathNode* pnext;
	int occurance;
	pathNode() { occurance = 0; }
};
struct wordNode {//one node in the wordtrie
	pathNode*phead = NULL;
	wordNode*children[26] = {};
};
struct wordTrie {
private:
	wordNode*root;
	void printInternal(wordNode*root, string word);//test print
	string takeWord(ifstream &fin, int &n);
	bool search(string s, wordNode * root);

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
};
//For searching
//User will input a string -> we merge and split them into few blocks.

struct keyword_block
{
	string s;
	bool iscont = false;
};
//To manage each keyword_block
struct query
{
	keyword_block block[34]; //maximum we get 34 words
};

//
bool checkValidation(char x);//check if a valid char or not



#endif
