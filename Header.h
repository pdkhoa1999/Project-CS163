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
	int n = 0;
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
		num = 0;
	}
	void insert_query(string & s,wordTrie  root)
	{
		insert_queryInternal(s, root,num);
	}
	bool word_exist(string s)
	{
		return word_exist(s, num, block);
	}
private:
	keyword_block block[34]; //maximum we get 34 keywords after split & merge & filter.
	int num;   
	void insert_queryInternal(string & s,wordTrie  root,int & n);
	bool word_exist(string s, int n, keyword_block block[]);
};
//
bool checkValidation(char x);//check if a valid char or not
#endif
