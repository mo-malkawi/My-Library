#pragma once
#include<iostream>
#include<fstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialCharacter = 3, Digit = 4 };


namespace input
{
	int ReadNumber(string Message)
	{
		int Number;
		cout << Message;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid Input , Please enter a number\n";
			cin >> Number;
		}

		return Number;
	}

	string ReadString(string Message)
	{
		string Input;

		cout << Message << endl;
		getline(cin, Input);

		return Input;
	}

	char ReadCharacter(string message)
	{
		char c;

		cout << message << endl;
		cin >> c;

		return c;
	}
}

namespace random
{
	int RandomNumber(int From, int To)
	{

		int RandNum = rand() % (To - From + 1) + From;
		return RandNum;

	}

	char GetRandomCharacter(enCharType CharType)
	{
		switch (CharType)
		{
		case enCharType::SmallLetter:
			return RandomNumber(97, 122);
		case enCharType::CapitalLetter:
			return RandomNumber(65, 90);
		case enCharType::SpecialCharacter:
			return RandomNumber(33, 47);
		case enCharType::Digit:
			return RandomNumber(48, 57);
		}

	}
}

namespace files
{
	void SaveVectorToFile(string FileName, vector <string> vFileContent)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::out);

		if (MyFile.is_open())
		{
			for (string Line : vFileContent)
			{
				if (Line != "")
				{
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}


	}
	void LoadDataFromFileToVector(string FileName, vector <string>& vFileContent)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vFileContent.push_back(Line);
			}
			MyFile.close();
		}


	}
	void PrintFileContent(string FileName)
	{
		fstream MyFile;

		MyFile.open(FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				cout << Line << endl;
			}

			MyFile.close();
		}
	}
	void DeleteRecordFromFile(string FileName, string Record)
	{
		vector <string> vFileContent;
		files::LoadDataFromFileToVector(FileName, vFileContent);

		for (string& Line : vFileContent)
		{
			if (Line == Record)
			{
				Line = "";
			}
		}
		files::SaveVectorToFile(FileName, vFileContent);
	}

}

namespace Chars
{
	char InvertLetterCase(char C1)
	{
		return isupper(C1) ? tolower(C1) : toupper(C1);
	}

	bool IsVowel(char Letter)
	{
		Letter = toupper(Letter);

		return (Letter == 'A' || Letter == 'E' || Letter == 'I' || Letter == 'O' || Letter == 'U');
	}
}

namespace Strings
{

	string UpperAllString(string S1)
	{

		for (int i = 0; i < S1.length(); i++)
		{
			S1[i] = toupper(S1[i]);
		}

		return S1;
	}

	string LowerAllString(string S1)
	{

		for (int i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}

		return S1;
	}

	string InvertAllStringLettersCase(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = Chars::InvertLetterCase(S1[i]);
		}

		return S1;

	}

	vector <string> SplitString(string S1, string delim)
	{
		vector <string> Splitted;

		short pos = 0;
		string sWord;

		while ((pos = S1.find(delim)) != string::npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != "")
			{
				Splitted.push_back(sWord);
			}

			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
		{
			Splitted.push_back(S1);
		}

		return Splitted;
	}

	string JoinString(vector <string> vString, string delim)
	{
		string S1 = "";

		for (string& s : vString)
		{
			S1 += s + delim;
		}

		return S1.substr(0, S1.length() - delim.length());
	}
}

