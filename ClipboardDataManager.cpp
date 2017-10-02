#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <fstream>
#include <limits>
#include <conio.h>
#include <stdio.h>
#include <cstdlib> 
#include <Winuser.h>
#include <cmath>
#include <iomanip>
#include <complex>

#undef max
#pragma comment (lib, "user32.lib")

using namespace std;

char **str;					//If not made global, exception occurs
int b = 0,c = 0;			//If not made global, class "RectDesign" cannot display data

class ClipboardDataManager
{
	public:
		bool result = true;

		void intCheck()							//A method to identify whether the input is a whole number
		{
			while (!(cin >> b))
			{
				cout << "You need to input a whole number" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Please enter how many items do you want to store: ";
			}
		}

		void intCheck2()					//Another method to identify whether the input is a whole number
		{
			while (!(cin >> c))
			{
				cout << "You need to input a whole number" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter line number to copy: ";
			}
		}

		void storeInputs()				//A method to store inputs in both dynamically created memory and in a txt file
		{	
			ofstream storeFile;
			storeFile.open("storeInputs.txt", std::ofstream::out | std::ofstream::trunc); //out for output, trunc for discarding old data
			str = new char*[10];

			for (int i = 0; i < 10; i++)
			{
				str[i] = new char[255];
			}

			cout << "Please enter how many items do you want to store: ";
			intCheck();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (b <= 0 || b > 10)
			{
				do
				{
					cout << "You need to enter a value between 1 to 10" << endl;
					cout << "Please enter how many items do you want to store: ";
					intCheck();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					if (b >= 1 && b <= 10)
					{
						result = false;
					}

				} while (result);
			}

			if ( b > 0 && b < 11)
			{
				result = true;
				for (int i = 0; i < b; i++)
				{
					cout << "Enter input " << i + 1 << ": ";
					cin.getline(str[i], 255);
					if (storeFile.is_open() && strlen(str[i]) > 0 && strlen(str[i]) < 26)
					{
						storeFile << str[i] << endl;
					}
					if (storeFile.is_open() && strlen(str[i]) <= 0 ||storeFile.is_open() && strlen(str[i]) >= 26)
					{
						do
						{
							cout << "Your input must not exceed 25 characters and should have at least 1 character" << endl;
							cout << "Enter input " << i + 1 << ": ";
							cin.getline(str[i], 255);
							if(strlen(str[i]) <= 0 || strlen(str[i]) >=26)
							{
								result = true;
								//continue;
							}
							else 
							{
								storeFile << str[i] << endl;
								result = false;
							}

						} while (result);
					}

				}
				storeFile.close();		//closing the txt file after inserting data
			}
	}

	std::ifstream& readLine(std::ifstream& file, unsigned int num) //A method to loop through the specific line number in txt file
	{
		file.seekg(std::ios::beg);		//Sets the position of the next character to be extracted from the input stream
		for (int i = 0; i < num - 1; ++i) 
		{
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores all the lines until it matches the number
		}
		return file;
	}

	void copy(HWND hwnd, const std::string &s) //A Windows specific method to copy the inputs
	{
		OpenClipboard(hwnd);
		EmptyClipboard();
		HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
		if (!hg) 
		{
			CloseClipboard();
			return;
		}
		memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
		GlobalUnlock(hg);
		SetClipboardData(CF_TEXT, hg);
		CloseClipboard();
		GlobalFree(hg);
	}

	void copyInputs()  //A method that copies the inputs by reading the specific line using the readLine method and copy method
	{
		cout << "Enter 0 to exit in the following process" << endl;
		cout << endl;
		
		ifstream readFile;
		readFile.open("storeInputs.txt", std::ifstream::in); //in for reading the file
		
		do
		{ 
			cout << "Enter line number to copy: ";
			
			intCheck2();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (c > b || c < 0 )
			{
				cout << "Your input must be between 0 and " << b + 1 << endl;
			}

			else if (readFile.is_open() && c > 0)
			{
				readLine(readFile, c);
				string line;
				getline(readFile, line);		
				cout << "Your input: \"" << line << "\" is copied" << endl;
				HWND hwnd = GetDesktopWindow();
				copy(hwnd, line);
				cin.clear();
			}
			
		} while (c != 0);
		
		readFile.close();	//closing the txt file after reading the lines
	}

};

class RectDesign: public ClipboardDataManager //A specific class defined for UI design to separate design from data manipulation
{
	public:
	int k = 0, z = 0, count = 1,x = 3;
	
	void rectDesign()			//creates the rectangle box and displays data in the box
	{
		for (int j = 0; j < 31; j++)		//enables creating the rectangles in the middle
		{
			cout << " ";
		}

		for (int i = 0; i < 29; i++)		//creates 1st border and upper line		//+-----
		{
			if (i == 0)
			{
				cout << "+";
			}
			cout << "-";
		}

		cout << "+\n";						//creates 2nd border					//+------+
		if ( b > 0 && b < 11)
		{
		 for (int j = 0; j < (b*2) - 1; j++)
		 {
			for (int i = 0; i < 31; i++)
			{
				cout << " ";				//creates the space to push for left rectangle
			}

			cout << "|";					//creates left hand vertical lines

			if (j % 2 != 0)
			{
				for (int k = 0; k < 29; k++)
				{
					cout << "-";			     //creates small boxes within the rectangle
				}
			}

			if (j % 2 == 0)
			{

				for (int i = z; i <= z; i++)
				{
					cout << count << ". " <<str[k];				//displays data using the dynamically allocated memory string
					for (int i = strlen(str[k])+x ; i < 29; i++)				//creates space after "|" and given string
					{
						if (k == 8)	//If the application is going to store the 10th line then it will require 4 characters "10. "
						{
						 x = 4;
						}
						cout << " ";
					}
				}
				count++;
				k++;
				z += 2;
			}
			cout << "|\n";                         //creates right hand vertical lines
		 }
		}
		for (int i = 0; i < 31; i++)			   //creates space for third border
		{
			cout << " ";
		}

		for (int j = 0; j < 29; j++)
		{
			if (j == 0)
			{
				cout << "+";                      //creates forth border
			}
			cout << "-";                          //creates horizontal lines to complete the rectangle
		}
		cout << "+\n";							  //creates third border
	}
	
	void deleteMemory()		//A method to delete memory after user decides to stop the application
	{
		for (int i = 0; i < 10; i++)
		{
			delete[] str[i];
		}
		delete[] str;
	}
};

int main()
{
	ClipboardDataManager cp;
	RectDesign rd;
	cp.storeInputs();			//Firstly, inputs are stored
	rd.rectDesign();			//Afterwards, data is displayed	
	cp.copyInputs();			//Afterwards, data is copied from txt file
	rd.deleteMemory();			//And finally, dynamically allocated memory is deleted
	system("pause");
	return 0;
}