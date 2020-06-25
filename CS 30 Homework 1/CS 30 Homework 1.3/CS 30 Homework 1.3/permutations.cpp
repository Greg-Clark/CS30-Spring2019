//
//  permutations.cpp
//  CS 30 Homework 1.2
//
//  Created by Gregory Clark on 4/27/19.
//  Copyright © 2019 Gregory Clark. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;



int loadDictionary(istream &dictfile, vector<string>& dict)
{
	string file;
	while(dictfile)
	{
		dictfile >> file;
		dict.push_back(file);
	}
	return (int) dict.size();
}

int permute(string word, vector<string>& dict, vector<string>& results)
{
	do
	{
		for(int i = 0; i < dict.size(); i++)
		{
			if(word == dict[i])
			{
				results.push_back(word);
			}
		}
	}while(next_permutation(word.begin(), word.end()));
	return (int) results.size();
}

int main()
{
	vector<string> dict;
	ifstream dictfile;
	string word;
	vector<string> results;
	int nWords;
	
	dictfile.open("words.txt");
	if (!dictfile)
	{
		cout << "File not found!" << endl;
		return (1);
	}
	
	
	
	
	nWords = loadDictionary(dictfile, dict);
	dictfile.close();
	
	cout << "Please enter a string for an anagram: ";
	cin >> word;
	
	permute(word, dict, results);
	
	for(int i = 0; i < results.size(); i++)
	{
		cout << "Matching word " << results[i] << endl;
	}
	
	if(results.size() < 1)
		cout << "No matches found" << endl;
	
	return 0;
}
