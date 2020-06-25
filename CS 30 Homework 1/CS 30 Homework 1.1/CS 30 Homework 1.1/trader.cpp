//
//  trader.cpp
//  CS 30 Homework 1.2
//
//  Created by Gregory Clark on 4/27/19.
//  Copyright © 2019 Gregory Clark. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

struct Trade{
	int day;
	string name;
	string tradeType;
	int amount;
	int moneySpent;
};

struct StockPrice{
	int day;
	int amount;
};

void loadStock(vector<Trade> &t, vector<StockPrice> &sp, const vector<string> &v) //sets all corresponding values into trade, and price change vectors
{
	vector<StockPrice> tempp;
	int count = 0, firstPipe = 0, secondPipe = 0, thirdPipe = 0; 	//create all the variables to count the number of pipes in string
	for(int i = 0; i < v.size(); i++)	//sets all corresponding values into trade, and price change vectors
	{
		//reset all values back to zero
		count = 0;		//counts the number of pipes
		firstPipe = 0;
		secondPipe = 0;
		thirdPipe = 0;
		for(int j = 0; j < v[i].size();  j++)	//loops through characters of vector
		{
			if(v[i][j] == '|')					//takes a count of all the pipes
				count++;
			if(count == 1 && firstPipe == 0)	//finds the position of the first pipe
				firstPipe = j+1;
			if(count == 2 && secondPipe == 0)	//finds the position of the second pipe
				secondPipe = j;
			if(count == 3 && thirdPipe == 0)	//finds the position of the third pipe
				thirdPipe = j;
		}
		if(count > 1)
		{
			StockPrice temp2;	//adds filler days for where the stock price doesn't change
			temp2.day = stoi(v[i].substr(0, firstPipe));
			temp2.amount = tempp[tempp.size()-1].amount;
			
			//puts all the individual values into the trade vector
			Trade temp;
			temp.day = temp2.day;
			temp.name = v[i].substr(firstPipe, secondPipe-firstPipe);
			temp.tradeType = v[i].substr(secondPipe+1, thirdPipe-(secondPipe+1));
			temp.amount = stoi(v[i].substr(thirdPipe+1));
			temp.moneySpent = (temp.amount) * (temp2.amount);
			t.push_back(temp);
		}
		else
		{
			//puts all the individual values into the price changes vectors
			StockPrice temp;
			temp.day = stoi(v[i].substr(0, firstPipe));
			temp.amount = stoi(v[i].substr(firstPipe));
			if(tempp.size() > 0)
			{
				for(int k = (int) (tempp.size()-1); k < temp.day; k++)
				{
					StockPrice temporary;
					temporary.day = tempp[k].day + 1;
					temporary.amount = tempp[k].amount;
					tempp.push_back(temporary);
				}
			}
			tempp.push_back(temp);
			sp.push_back(temp);
		}
	}
}

vector<Trade> potentialpotentialBadTraders(const vector<Trade> &t, const vector<StockPrice> &sp)	//catches all the bad traders
{
	vector<Trade> ppbt;
	bool repeat = false;
	for(int i = 1; i < sp.size(); i++)
	{
		for(int j = 0; j < t.size(); j++)
		{
			if(sp[i].day - t[j].day <= 3 && sp[i].day - t[j].day >= 0)
			{
				if(t[j].moneySpent - (t[j].amount * sp[i].amount) >= 500000 && t[j].tradeType == "SELL")	//checks for the bad traders who sell
				{
					for(int k = 0; k < ppbt.size(); k++) //checks for repeated bad traders
					{
						if(t[j].day == ppbt[k].day && t[j].name == ppbt[k].name && t[j].tradeType == ppbt[k].tradeType && t[j].amount == ppbt[k].amount)
						{
							repeat = true;
						}
					}
					if(repeat == false)
						ppbt.push_back(t[j]);
				}
				if(t[j].moneySpent - (t[j].amount * sp[i].amount) <= -500000 && t[j].tradeType == "BUY")	//checks for the bad traders who buy
				{
					for(int k = 0; k < ppbt.size(); k++) //checks for repeated bad traders
					{
						if(t[j].day == ppbt[k].day && t[j].name == ppbt[k].name && t[j].tradeType == ppbt[k].tradeType && t[j].amount == ppbt[k].amount)
						{
							repeat = true;
						}
					}
					if(repeat == false)
						ppbt.push_back(t[j]);
				}
			}
		}
	}
	return ppbt;
}

vector<string> findPotentialBadTraders(const vector<string> &v){
	vector<Trade> t;
	vector<StockPrice> sp;
	loadStock(t, sp, v);	//loads all the values from the stock trade
	vector<Trade> ppbt = potentialpotentialBadTraders(t, sp);
	vector<string> badTraders;
	for(int i = 0; i < ppbt.size(); i++)	//convert potential bad traders to a string form
	{
		string btemp = to_string (ppbt[i].day) + "|" + ppbt[i].name + "|" + ppbt[i].tradeType + "|" + to_string(ppbt[i].amount) + " is a potential bad trade";
		badTraders.push_back(btemp);
	}
	return badTraders;
}

int main() {
	
	ifstream in("input.txt");
	string str;
	
	if (!in) {
		cerr << "No input file" << endl;
		exit (0);
	}
	
	vector<string> inputVec;
	while (getline(in,str)) {
		inputVec.push_back(str);
	}
	
	vector<string> resV = findPotentialBadTraders(inputVec);
	for (const string& r : resV) {		//loops through and prints out vector
		cout << r << endl;
	}
	return 0;
}
