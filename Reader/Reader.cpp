#include "stdafx.h"
//It's important that these are included
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//These variables can be referenced at any point for these 2 methods
string letters("abcdefghijklmnopqrstuvwxyz");
string uppercaseLetters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

struct Book
{
public:
	string title;
	string authorFirstName;
	string authorLastName;
	int characters;
	double letterFrequency[26];
	int lineCount;
};

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

void printLetterDistribution(double distribution[26])
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

//Puts book data into a book and returns whether it was successful
bool readBookData(string filename, Book *book)
{
	ifstream stream;
	stream.open(filename);
	if (stream.fail())
	{
		stream.close();
		return false;
	}
	//TODO: read contents into book
	//You need to reference book with the -> symbol. Ex: book->authorFirstName = "Test";
	stream.close();
}

//Saves a book to CardCatalog.txt
void saveBookData(Book book)
{
	//TODO
}

//Method containing all the main code for the assignment
void analyzeBook()
{
	string input;
	cout << "What file do you want to read?" << endl;
	cin >> input;
	bool success = false;
	Book book;
	if (!readBookData(input, &book))
	{
		cout << "The file " << input << " does not exist!";
		return;
	}
	saveBookData(book);
	cout << "Do you want to see the letter distribution?";
	cin >> input;
	if (input == "Yes" || input == "yes")
	{
		printLetterDistribution(book.letterFrequency);
	}
}

int main()
{
	while (true)
	{
		analyzeBook();
		string answer;
		cout << "Would you like to process another book?" << endl;
		cin >> answer;
		if (answer == "Yes" || answer == "yes")
		{
			break;
		}
	}
}