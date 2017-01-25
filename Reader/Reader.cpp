#include "stdafx.h"
//It's important that these are included
#include <string>
#include <iostream>
using namespace std;

//These variables can be referenced at any point for these 2 methods
string letters("abcdefghijklmnopqrstuvwxyz");
string uppercaseLetters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

double* getLetterDistribution(string text)
{
	double* distribution = new double[26]();
	int totalLetters = 0;
	if(text.length() > 0) //Prevents a divide by zero error
	{
		//First get the count of each letter
		for (int i = 0; i < text.length(); i++)
		{
			for (int j = 0; j < letters.length(); j++)
			{
				//Include both uppercase and lowercase characters for each letter
				if (text[i] == letters[j] || text[i] == uppercaseLetters[j])
				{
					distribution[j]++;
					totalLetters++;
					break;
				}
			}
		}
		//Turn the count into a percentage
		for (int i = 0; i < letters.length(); i++)
		{
			distribution[i] *= (double)100 / totalLetters;
		}
	}
	return distribution;
}

void printLetterDistribution(double* distribution)
{
	for (int i = 0; i < letters.length(); i++)
	{
		cout << letters[i] << " - " << distribution[i] << "%" << endl;
	}
}

int getLineCount(string text)
{
	int count = 1;
	for (int c = 0; c < text.length(); c++)
	{
		if (text[c] == '\n')
		{
			count++;
		}
	}
	return count;
}

//For testing. Do not include in the actual assignment.
int main()
{
	string text = "This is a test. I love tests. Tests are the best thing.";
	double* distribution = getLetterDistribution(text);
	cout << "Lines: " << getLineCount(text) << endl;
	printLetterDistribution(distribution);
}