/*
 * 2250_proj_4.cpp
 *
 *  Created on: Apr 13, 2021
 *      Author: Kayla
 */

#include <iostream>
#include <string>
#include <new>

using namespace std;

class DelimiterStack {
	private:
		//struct for node of stack
		struct DelimiterNode{
			//stores delimiter character
			char character = ' ';
			//stores line number of delimiter
			int lineNum = 0;
			//stores character position of delimiter in current line
			int charCount = 0;
			//pointer to next node
			DelimiterNode *next;
		};

		//pointer to head of stack
		DelimiterNode *head;
		//node counter
		int nodeNum;

	public:
		//constructor
		DelimiterStack();
		//destructor
		~DelimiterStack();
		//stack operations
		void push(char, int, int);
		void popDelimiter(char&, int&, int&);
		bool isEmpty();
		void displayStack();
};

//function to compare left and right delimiters
void compareDelim(char, int, int, char, int, int);

int main()
{
	//creates delimiterStack instance
	DelimiterStack myStack;
	//string to hold user input
	string currentLine = "";
	int lineNum = 0;

	//holds values for popped delimiter
	char popdel = ' ';
	int pos1 = 0;
	int line1 = 0;

	//prompts user for input
	cout 	<< "Program will flag mismatched or missing delimiters in input strings.\n"
			<< "Please input strings. Type 'DONE' when finished.\n";

	do {
		//increment line number
		lineNum++;

		//takes user input and stores into currentLine var
		getline(cin, currentLine);
		int len = currentLine.length();

		//process input text and locate delimiter characters
		for (int i = 0; i < len; i++)
		{
			try
			{
				//tests for left delimiter; if found, pushes the stack
				if (currentLine[i] == '[' || currentLine[i] == '{' || currentLine[i] == '(')
				{
					myStack.push(currentLine[i], (i + 1), lineNum);
				}
				//tests for right delimiter; if found, pops the stack
				if (currentLine[i] == ']' || currentLine[i] == '}' || currentLine[i] == ')')
				{
					myStack.popDelimiter(popdel, pos1, line1);
					//compare popped left delimiter to right delimiter
					compareDelim(popdel, line1, pos1, currentLine[i], lineNum, i);
				}
			}
			catch (int ex)
			{
				cout 	<< "Missing delimiter: " << currentLine[i] << " found at line "
						<< lineNum << ", char " << i+1 << " has no left delimiter.\n";
			}
		}

	} while (currentLine != "DONE");

	//displays leftover delimiters in the stack
	myStack.displayStack();

	cout << endl << "Ending program...";


	return 0;
}

DelimiterStack::DelimiterStack()
{
	//initialize head ptr to null
	head = nullptr;
	//initialize number of nodes to 0
	nodeNum = 0;
}

DelimiterStack::~DelimiterStack()
{
	//pointers to top of stack and next node in stack
	DelimiterNode *topNode = head;
	DelimiterNode *nextNode;

	//traverse list and delete each node
	while (topNode != nullptr)
	{
		//sets next node
		nextNode = topNode->next;

		//delete the top node
		delete topNode;

		//update top of the stack to the next delimiter node
		topNode = nextNode;
	}
}

void DelimiterStack::push(char delim, int pos, int line)
{
	try
	{
		//create new delimiter node
		DelimiterNode *newNode = new DelimiterNode;
		//store delimiter character, position, and line number in node
		newNode->character = delim;
		newNode->charCount = pos;
		newNode->lineNum = line;
		//increment number of nodes
		nodeNum++;

		//check if stack is empty; if so set the new delimiter node as top of stack
		if (isEmpty())
		{
			head = newNode;

			//set newNode's pointer to null since it is also the end of the stack
			newNode->next = nullptr;
		}
		//if stack is not empty, insert new delimiter node at top of stack
		else
		{
			//delimiter node's pointer now points to previous top of stack
			newNode->next = head;
			//sets top of stack to the new delimiter node
			head = newNode;
		}
	}
	//catch bad_alloc object in case of insufficient memory
	catch (bad_alloc& ba)
	{
		cout << "Insufficient memory \n";
	}
}

void DelimiterStack::popDelimiter(char &delim, int &pos, int &line)
{
	//if stack is empty, throws a empty stack exception???
	if (isEmpty())
		throw 99;
	else
	{
		//decrement number of nodes
		nodeNum--;

		//stores values of popped node into reference variables
		delim = head->character;
		pos = head->charCount;
		line = head->lineNum;

		//temp delimiter node, to be deleted after updating top of stack
		DelimiterNode * temp = head;

		//update the top of the delimiter node stack
		head = head->next;

		//delete the temp node
		delete temp;
	}
}

bool DelimiterStack::isEmpty()
{
	//checks if head pointer for stack is null and if so returns true
	if (head == nullptr)
		return true;
	//returns false if head pointer for stack is NOT null
	else
		return false;
}

void DelimiterStack::displayStack()
{
	while (!isEmpty())
	{
		//displays the unmatched delimiter at the top of the stack
		cout 	<< "Left delimiter " << head->character << " at line " << head->lineNum
				<< ", char " << head->charCount << " has no right delimiter.\n";

		//moves the top of the stack to the next node in the stack then deletes the placeholder node
		DelimiterNode *temp = head;
		head = head->next;
		delete temp;
	}
}

void compareDelim(char delim1, int line1, int pos1, char delim2, int line2, int pos2)
{
	try
	{
		//initializes the exception string that will be thrown if the delimiters do not match
		string exceptionStr = "Mismatched delimiter: ";
		//if the delimiters match, exits function without throwing exception
		if (delim1 == '(' && delim2 == ')')
			return;
		else if (delim1 == '{' && delim2 == '}')
			return;
		else if (delim1 == '[' && delim2 == ']')
			return;
		else
		{
			//fills in the information about the delimiter, position, etc. for the exception
			//string
			exceptionStr += delim1;
			exceptionStr += " found at line " + to_string(line1) + ", char " + to_string(pos1)
			+ " does not match ";
			exceptionStr += delim2;
			exceptionStr += " found at line " + to_string(line2) + ", char " + to_string(pos2 + 1) + ".\n";
			throw exceptionStr;
		}
	}
	//catches and displays the exception string in the case of a mismatched delimiter
	catch (string &exStr)
	{
		cout << exStr;
	}

}
