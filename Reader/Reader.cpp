#include "stdafx.h"
//It's important that these are included
#include <string>
#include <iostream>
#include <cctype>
#include <fstream>
using namespace std;

int distributionCount[26];
string letters = "abcdefghijklmnopqrstuvwxyz";
string uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

// Add to distribution total
void getLetterDistribution(string text)
{
	//First get the count of each letter
	for (int i = 0; i < text.length(); i++)
	{
		for (int j = 0; j < letters.length(); j++)
		{
			//Include both uppercase and lowercase characters for each letter
			if (text[i] == letters[j] || text[i] == uppercaseLetters[j])
			{
				distributionCount[j]++;
				break;
			}
		}
	}
}

// Calculate values in letterFrequency
Book calcLetterDistribution(Book bookStruct)
{
	bookStruct.characters = 0;
	for (int i = 0; i < sizeof(distributionCount); i++)
	{
		bookStruct.characters += distributionCount[i];
	}
	for (int i = 0; i < sizeof(distributionCount); i++)
	{
		bookStruct.letterFrequency[i] = (double)100 * ((double)distributionCount[i] / (double)bookStruct.characters);
	}
	return bookStruct;
}

//Prints letter distribution
void printLetterDistribution(double distribution[26])
{
	for (int i = 0; i < letters.length(); i++)
	{
		cout << letters[i] << ": " << distribution[i] << "%" << endl;
	}
}


//Puts book data into a book and returns whether it was successful
Book readBookData(string filename)
{
	Book book;
	ifstream stream;
	stream.open(filename);
	while(stream.fail())
	{
		cout << "The file " << filename << " does not exist. Enter a valid filename:" << endl;
		cin >> filename;
		stream.open(filename);
	}
	// Reads the metadata into the Book struct
	getline(stream, book.title);
	string fullName;
	getline(stream, fullName);
	bool space = false;
	for (int i = 0; i < fullName.length(); i++)
	{
		if (isalpha(fullName[i]) && !space)
		{
			book.authorFirstName += fullName[i];
		}
		else
		{
			book.authorLastName += fullName[i];
			space = true;
		}
	}

	string line;
	// Skip "Contents:" header
	while (true)
	{
		getline(stream, line);
		if (line == "Contents:" || line == "Contents: ")
		{
			break;
		}
	}

	// Save letter distrubution
	for (int i = 0; i < sizeof(distributionCount); i++)
	{
		distributionCount[i] = 0;
	}
	while (true)
	{
		getline(stream, line);
		if (stream.fail())
		{
			break;
		}
		getLetterDistribution(line);
		book.lineCount++;
	}
	book = calcLetterDistribution(book);

	stream.close();
	return book;
}

// Saves a book to CardCatalog.txt
void saveBookData(Book book)
{
	ofstream write;
	write.open("CardCatalog.txt", ios::ate);
	write << "Title: " << book.title << endl << endl;
	write << "Full Author: " << book.authorFirstName << " " << book.authorLastName << endl << endl;
	write << "Author First Name: " << book.authorFirstName << endl << endl;
	write << "Author Last Name: " << book.authorLastName << endl << endl;
	write << "Character Count: " << book.characters << endl << endl;
	write << "Line Count: " << book.lineCount << endl << endl;
	write << "Character Frequency: " << endl;
	for (int i = 0; i < letters.length(); i++)
	{
		write << letters[i] << ": " << book.letterFrequency[i] << "%" << endl;
	}

	write.close();
}

//Method containing all the main code for the assignment
void analyzeBook()
{
	string input;
	cout << "What file do you want to read?" << endl;
	cin >> input;
	bool success = false;
	Book book = readBookData(input);
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
		if (!(answer == "Yes" || answer == "yes"))
		{
			break;
		}
	}
}