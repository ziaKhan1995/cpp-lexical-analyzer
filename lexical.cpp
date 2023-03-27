
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <string.h>
#include <iomanip>
using namespace std;
#include<iostream>
using namespace std;
typedef enum
{
	IF = 1, ELSE, WHILE, DO, FOR, LEFTPARENTHESIS, RIGHTPARENTHESIS,
	ID, FLOAT, DIGIT, MINUS, MINUSMINUS, MINUSEQUAL, PLUSPLUS, PLUS,
	SINGLEAND, SINGLEOR, SINGLELINECOMMENT, NOT, TERNARYCONDITION, PLUSEQUAL,
	MULTILINECOMMENT, LOGICALOR, LOGICALAND, NOTEQUAL, EQUAL, RIGHTSHIFT,
	MODULUS, LEFTCURLYBRACE, RIGHTCURLYBRACE, LEFTSHIFT, POINTERACCESSOR,
	DIVIDE, DIVIDEEQUAL, BEGIN, END, LEFTSQUAREBRACKET, XOR, DOUBLE,
	RIGHTSQUAREBRACKET, EQUALEQUAL, MULTIPLYEQUAL, BACKSLASH, QUESTIONMARK,
	SEMICOLON, COLON, COMMA, LESS, DOT, UNDERSCORE, TILDE, HASH, DOLLAR,
	MULTIPLY, LESSEQUAL, GREATER, GREATEREQUAL, INT, STRING, CHAR
}tokentype;

struct token
{
	tokentype tkn;
	int num=0;//S.no
	string variable;//name
	token* nextToken = NULL;
}tokn, ctoken;

class LinkedList {
	private
		:
			token* head;
			token* tail;
			int lenghtOfList; //LinkedList List;
			
public:
	LinkedList();
	bool isEmpty();
	int getListLenght();
	bool search(string);
	void insert_in_table(string, tokentype);
	void traverse();
};
LinkedList symbolTable;

ifstream file;
int countIfs = 0;
int countIElse = 0;
int countIElseIf = 0;
bool flag = 0;
int sno = 0;
bool statement_list();
void ungettoken();
token gettoken();
token lexical();
bool program();
bool statement();
bool expression();
bool term();
bool factor();
bool expr();
bool orexp();
bool andexp();
bool eqexp();
bool cmpexp();
bool shiftexp();

int main()
{
	file.open("input.txt");
	if (file.good())
	{
		if (program())
			cout << "Successful\n";
		else
			cout << "Unsuccessful\n";
	}
	else
		cout << "File not Found\n";
	file.close();
	symbolTable.traverse();
	return 0;
}
void ungettoken()
{
	flag = 1;
}
token gettoken()
{
	if (flag == 0)
	{
		ctoken = lexical(); return ctoken;
	}
	else
	{
		flag = 0;
		return ctoken;
	}
}
token lexical()
{
	char ch;
	string st = "";
	while (!file.eof())
	{
		file.get(ch);
		if (ch == ' ' || ch == '\n')
			continue;
		if (ch == '(')
		{
			tokn.tkn = LEFTPARENTHESIS;
			tokn.variable = "LEFTPARENTHESIS";
			return tokn;
		}
		else if (ch == ')')
		{
			tokn.tkn = RIGHTPARENTHESIS;
			tokn.variable = "RIGHTPARENTHESIS";
			return tokn;
		}
		else if (ch == '[')
		{
			tokn.tkn = LEFTSQUAREBRACKET;
			tokn.variable = "LEFTSQUAREBRACKET";
			return tokn;
		}
		else if (ch == ']')
		{
			tokn.tkn = RIGHTSQUAREBRACKET;
			tokn.variable = "RIGHTSQUAREBRACKET";
			return tokn;
		}
		else if (ch == '{')
		{
			tokn.tkn = LEFTCURLYBRACE;
			tokn.variable = "LEFTCURLYBRACE";
			return tokn;
		}
		else if (ch == '}')
		{
			tokn.tkn = RIGHTCURLYBRACE;
			tokn.variable = "RIGHTCURLYBRACE";
			return tokn;
		}
		else if (ch == ';')
		{
			tokn.tkn = SEMICOLON;
			tokn.variable = "SEMICOLON";
			return tokn;
		}
		else if (ch == ':') {
			tokn.tkn = COLON;
			tokn.variable = "COLON";
			return tokn;
		}
		else if (ch == ',')
		{
			tokn.tkn = COMMA;
			tokn.variable = "COMMA";
			return tokn;
		}
		else if (ch == '%')
		{
			tokn.tkn = MODULUS;
			tokn.variable = "MODULUS";
			return tokn;
		}
		else if (ch == '|')
		{
			file.get(ch);
			if (ch == '|')
			{
				tokn.tkn = LOGICALOR;
				tokn.variable = "LOGICALOR";
				return tokn;
			}
			//else
			file.unget();
			tokn.tkn = SINGLEOR;
			tokn.variable = "OR";
			return tokn;
		}
		else if (ch == '&')
		{
			file.get(ch);
			if (ch == '&')
			{
				tokn.tkn = LOGICALAND;
				tokn.variable = "LOGICALAND";
				return tokn;
			}
			else
			{
				file.unget();
				tokn.tkn = SINGLEAND;
				tokn.variable = "AND";
				return tokn;
			}

		}
		else if (ch == '!')
		{
			file.get(ch);
			if (ch == '=')
			{
				tokn.tkn = NOTEQUAL;
				tokn.variable = "NOTEQUAL";
				return tokn;
			}
			else
			{
				file.unget();
				tokn.tkn = NOT;
				tokn.variable = "NOT";
				return tokn;
			}
		}
		else if (ch == '/')
		{
			file.get(ch);
			if (ch == '/')
			{
				tokn.tkn = SINGLELINECOMMENT;
				tokn.variable = "SINGLELINECOMMENT";
				do {
					file.get(ch);
				} while (ch != '\n');
				return tokn;
			}
			else if (ch == '*')
			{
				tokn.tkn = MULTILINECOMMENT;
				tokn.variable = "MULTILINECOMMENT";
				while (1)
				{
					file.get(ch);
					if (ch == '*')
					{
						file.get(ch);
						if (ch == '/')
						{
							return tokn;
						}
					}
				}
			}
			else
			{
				file.unget();
				tokn.tkn = DIVIDE;
				tokn.variable = "DIVIDE";
				return tokn;
			}
		}
		else if (ch == '*')
		{
			if (ch == '=')
			{
				tokn.tkn = MULTIPLYEQUAL;
				tokn.variable = "MULTIPLYEQUAL";
				return tokn;
			}
			else
			{
				file.unget();
				tokn.tkn = MULTIPLY;
				tokn.variable = "MULTI";
				return tokn;
			}
		}
		else if (ch == '+')
		{
			file.get(ch);
			if (ch == '=')
			{
				tokn.tkn = PLUSEQUAL;
				tokn.variable = "PLUSEQUAL";
				return tokn;
			}
			else if (ch == '+')
			{
				tokn.tkn = PLUSPLUS;
				tokn.variable = "PLUSPLUS";
				return tokn;
			}
			else {
				file.unget();
				tokn.tkn = PLUS;
				tokn.variable = "PLUS";
				return tokn;
			}
		}
		else if (ch == '-')
		{
			file.get(ch);
			if (ch == '=')
			{
				tokn.tkn = MINUSEQUAL;
				tokn.variable = "MINUSEQUAL";
				return tokn;
			}
			else if (ch == '-')
			{
				tokn.tkn = MINUSMINUS;
				tokn.variable = "MINUSMINUS";
				return tokn;
			}
			else
			{
				file.unget();
				tokn.tkn = MINUS;
				tokn.variable = "MINUS";
				return tokn;
			}
		}
		else if (ch == '=')
		{
			file.get(ch);
			if (ch == '=')
			{
				tokn.tkn = EQUALEQUAL;
				tokn.variable = "EQUALEQUAL";
				return tokn;
			}
			else
			{
				file.unget();
				tokn.tkn = EQUAL;
				tokn.variable = "EQUAL";
				return tokn;
			}
		}
		else if (ch == '<')
		{
			file.get(ch);
			if (ch == '=')
			{
				tokn.tkn = LESSEQUAL;
				tokn.variable = "LESSEQUAL";
				return tokn;
			}
			else if (ch == '<')
			{
				tokn.tkn = LEFTSHIFT;
				tokn.variable = "LEFTSHIFT";
				return tokn;
			}
			else
			{
				file.unget();
				tokn.tkn = LESS;
				tokn.variable = "LESS";
				return tokn;
			}
		}
		else if (ch == '>')
		{
			file.get(ch);
			if (ch == '=')
			{
				tokn.tkn = GREATEREQUAL;
				tokn.variable = "GREATEREQUAL";
				return tokn;
			}
			else if (ch == '>')
			{
				tokn.tkn = RIGHTSHIFT;
				tokn.variable = "RIGHTSHIFT";
				return tokn;
			}
			else
			{
				file.unget();
				tokn.tkn = GREATER;
				tokn.variable = "Greater";
				return tokn;
			}
		}
		else if (ch == '.')
		{
			tokn.tkn = DOT;
			tokn.variable = "Dot";
			return tokn;
		}
		else if (isdigit(ch))
		{
			string b = "";
			do
			{
				b += ch;
				file.get(ch);
			} while (isdigit(ch));
			file.unget();
			tokn.tkn = DIGIT;
			tokn.variable = "NULL";
			return tokn;
		}
		else if (isalpha(ch) || ch == '_')
		{
			st = "";
			do
			{
				st += ch;
				file.get(ch);
			} while ((isalpha(ch) || ch == '_') && st != "END");
			if (st != "END")
			{
				file.unget();
			}
			char v;
			if (st == "int")
			{
				string b = "";
				do
				{
					file.get(ch);
					v = ch;
				} while (v != '=');
				file.get(ch);
				do
				{
					b += ch;
					file.get(ch);
				} while (isdigit(ch));
				tokn.tkn = INT;
				tokn.variable = "NULL";
				return tokn;
			}
			else if (st == "string")
			{
				string b = "", v1, x;
				do
				{
					file.get(ch);
					v1 = ch;
				} while (v1 != "="); file.get(ch);
				do
				{
					b += ch;
					file.get(ch);
					x = ch;
				} while (x != "'");
				tokn.tkn = STRING;
				tokn.variable = "NULL";
				return tokn;
			}
			else if (st == "for")
			{
				tokn.tkn = FOR;
				tokn.variable = "NULL";
				return tokn;
			}
			else if (st == "while")
			{
				tokn.tkn = WHILE;
				tokn.variable = "NULL";
				return tokn;
			}
			else if (st == "BEGIN")
			{
				tokn.tkn = BEGIN;
				tokn.variable = "NULL";
				return tokn;
			}
			else if (st == "END")
			{
				tokn.tkn = END;
				tokn.variable = "NULL";
				return tokn;
			}
			else if (st == "do")
			{
				tokn.tkn = DO;
				tokn.variable = "NULL";
				return tokn;
			}
			else if (st == "if")
			{
				tokn.tkn = IF;
				tokn.variable = "NULL";
				return tokn;
			}
			else if (st == "else")
			{
				tokn.tkn = ELSE;
				tokn.variable = "NULL";
				return tokn;
			}
			else if (st == "float")
			{
				tokn.tkn = FLOAT;
				tokn.variable = "NULL";
				return tokn;
			}
			else if (st == "double")
			{
				tokn.tkn = DOUBLE;
				tokn.variable = "NULL";
				return tokn;
			}
			else //insert into symbol table
			{
				tokn.tkn = ID;
				tokn.variable = "VARIABLE";
				symbolTable.insert_in_table(st, tokn.tkn);
				return tokn;
			}
		}
	}
	return tokn;
}
bool program()
{
	tokn = gettoken();
	if (tokn.tkn == BEGIN)
	{
		if (statement_list())
		{
			tokn = gettoken();
			if (tokn.tkn == END)
				return true;
		}
	}
	return false;
}
bool statement_list()
{
	if (statement())
	{
		do
		{
			tokn = gettoken();
			if (tokn.tkn == IF || tokn.tkn == DO || tokn.tkn == ID)
			{
				ungettoken();
				return false;
			}
			else
			{
				ungettoken();
				break;
			}
		} while (true);
		return true;
	}
	return false;
}
bool statement()
{
	tokn = gettoken();
	if (tokn.tkn == ID)
	{
		tokn = gettoken();
		if (tokn.tkn == EQUAL || tokn.tkn == NOTEQUAL || tokn.tkn == PLUSEQUAL || tokn.tkn == MINUSEQUAL)
		{
			if (orexp())
			{
				tokn = gettoken();
				if (tokn.tkn == SEMICOLON)
					return true;
			}
		}
	}
	else if (tokn.tkn == IF)
	{
	L1:
		tokn = gettoken();
		if (tokn.tkn == LEFTPARENTHESIS)
		{
			if (expr())
			{
				tokn = gettoken();
				if (tokn.tkn == RIGHTPARENTHESIS)
				{
					tokn = gettoken();
					if (tokn.tkn == LEFTCURLYBRACE)
					{
						if (statement_list())
						{
							tokn = gettoken();
							if (tokn.tkn == RIGHTCURLYBRACE)
							{
								tokn = gettoken();
								if (tokn.tkn == ELSE)
								{
									tokn = gettoken();
									if (tokn.tkn == LEFTCURLYBRACE)
									{
										if (statement_list())
										{
											tokn = gettoken();
											if (tokn.tkn == RIGHTCURLYBRACE)
												return true;
										}
									}
									else if (tokn.tkn == IF)
									{
										goto L1;
									}
								}
								else
									return true;
							}
						}
					}
				}
			}
		}
		return false;
	}
	else if (tokn.tkn == WHILE)
	{
		tokn = gettoken();
		if (tokn.tkn == LEFTPARENTHESIS)
		{
			if (expr())
			{
				tokn = gettoken();
				if (tokn.tkn == RIGHTPARENTHESIS)
				{
					tokn = gettoken();
					if (tokn.tkn == LEFTCURLYBRACE)
					{
						if (statement_list())
						{
							tokn = gettoken();
							if (tokn.tkn == RIGHTCURLYBRACE)
								return true;
						}
					}
				}
			}
		}
		return false;

	}
	else if (tokn.tkn == DO)
	{
		tokn = gettoken();
		if (tokn.tkn == LEFTCURLYBRACE)
		{
			if (statement_list())
			{
				tokn = gettoken();
				if (tokn.tkn == RIGHTCURLYBRACE)
				{
					tokn = gettoken();
					if (tokn.tkn == WHILE)
					{
						tokn = gettoken();
						if (tokn.tkn == LEFTPARENTHESIS)
						{
							if (expr())
							{
								tokn = gettoken();
								if (tokn.tkn == RIGHTPARENTHESIS)
								{
									tokn = gettoken();
									if (tokn.tkn == SEMICOLON)
										return true;
								}
							}
						}
					}
				}
			}
		}
		return false;
	}
	
}


bool expression()
{
	do
	{
		if (!term())
			return false;
		tokn = gettoken();
	} while (tokn.tkn == PLUS || tokn.tkn == MINUS);
	ungettoken();
	return true;
}
bool term()
{
	do
	{
		if (!factor())
			return false;
		tokn = gettoken();
	} while (tokn.tkn == MULTIPLY || tokn.tkn == DIVIDE || tokn.tkn == MODULUS);
	ungettoken();
	return true;
}
bool factor()
{
	tokn = gettoken();
	if (tokn.tkn == ID)
		return true;
	else if (tokn.tkn == DIGIT)
		return true;
	else if (tokn.tkn == LEFTPARENTHESIS)
	{
		if (expression())
		{
			tokn = gettoken();
			if (tokn.tkn == RIGHTPARENTHESIS)
				return true;
			else
				ungettoken();
		}
		else
			ungettoken();
	}
	ungettoken();
	return true;
}
bool expr()
{
	if (orexp())
	{
		tokn = gettoken();
		if (tokn.tkn == GREATER || tokn.tkn == LESS || tokn.tkn == GREATEREQUAL || tokn.tkn == LESSEQUAL || tokn.tkn == EQUALEQUAL || tokn.tkn == NOTEQUAL)
		{
			if (orexp())
				return true;
			else
				return false;
		}
		ungettoken();
		return true;
	}
	return false;
}
bool orexp()
{
	do
	{
		if (!andexp())
			return false;
		tokn = gettoken();
	} while (tokn.tkn == LOGICALOR);
	ungettoken();
	return true;
}
bool andexp()
{
	do
	{
		if (!eqexp())
			return false;
		tokn = gettoken();
	} while (tokn.tkn == LOGICALAND);
	ungettoken();
	return true;
}
bool eqexp()
{
	do
	{
		if (!cmpexp())
			return false;
		tokn = gettoken();
	} while (tokn.tkn == EQUALEQUAL || tokn.tkn == NOTEQUAL);
	ungettoken();
	return true;
}
bool cmpexp()
{
	do
	{
		if (!shiftexp())
			return false;
		tokn = gettoken();
	} while (tokn.tkn == LESS || tokn.tkn == LESSEQUAL || tokn.tkn == GREATER || tokn.tkn == GREATEREQUAL);
	ungettoken();
	return true;
}
bool shiftexp()
{
	do
	{
		if (!expression())
			return false;
		tokn = gettoken();
	} while (tokn.tkn == RIGHTSHIFT || tokn.tkn == LEFTSHIFT);
	ungettoken();
	return true;
}
//table functions
LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
	lenghtOfList = 0;
}
bool LinkedList::isEmpty()
{
	if (head == NULL)
		return true;
	else
		return false;
}
int LinkedList::getListLenght()
{
	return this->lenghtOfList;
}
bool LinkedList::search(string variable) {
	token* current = head; // Initialize current
	while (current != NULL)
	{
		if (current->variable == variable)
			return true;
		current = current->nextToken;
	}
	return false;
}
void LinkedList::insert_in_table(string variableName, tokentype tkn)
{
	if (search(variableName))
		return;
	sno++;
	token* temp, * p;
	temp = new token;
	temp->tkn = tkn;
	temp->variable = variableName;
	temp->nextToken = NULL;
	temp->num = sno;
	if (head == NULL)
	{
		head = temp;
		head->nextToken = 0;
		tail = temp;
		return;
	}
	p = head;
	while (p->nextToken != NULL)
	{
		p = p->nextToken;
	}
	temp->nextToken = 0;
	p->nextToken = temp;
	++lenghtOfList;
}
void LinkedList::traverse() {
	if (head == NULL) {
		cout << "List is empty\n";
		return;
	}
	token* temp = head;
	cout << "::::::::::::Symbol Table::::::::::::\nS.no  | ID | token \n";
	while (temp != NULL) {
		cout << temp->num << "     |";
		cout << temp->variable << "   |";
		cout << temp->tkn << " ";
		temp = temp->nextToken;
		cout << endl;
	}
}


