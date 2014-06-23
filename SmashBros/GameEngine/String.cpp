#define _CRT_SECURE_NO_WARNINGS

#include "String.h"
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include "Console.h"
#include "stdio.h"
#include <math.h>

namespace GameEngine
{
	bool String::asBool(const String&str)
	{
		bool onlyNums = true;
		bool hasNum = false;
		bool hasDecimal = false;

		for(int i=0; i<str.length(); i++)
		{
			char c = str.charAt(i);
			if(!(c>='0' && c<='9'))
			{
				if(c=='.')
				{
					if(onlyNums && hasDecimal)
					{
						Console::WriteLine((String)"Error: invalid String in function String::asBool(\"" + str + "\")");
						return false;
					}
					else if(onlyNums)
					{
						hasDecimal = true;
					}
				}
				else if(hasNum)
				{
					Console::WriteLine((String)"Error: invalid String in function String::asBool(\"" + str + "\")");
					return false;
				}
				else
				{
					onlyNums = false;
				}
			}
			else
			{
				hasNum = true;
			}
		}

		if(onlyNums)
		{
			if(hasDecimal)
			{
				double d = asDouble(str);
				if(d>=1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				long l = asLong(str);
				if(l>=1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else if(hasNum)
		{
			Console::WriteLine((String)"Error: invalid String in function String::asBool(\"" + str + "\")");
			return false;
		}
		else
		{
			if(str.equals("true") || str.equals("TRUE") || str.equals("on") || str.equals("ON") || str.equals("yes") || str.equals("YES"))
			{
				return true;
			}
			else if(str.equals("false") || str.equals("FALSE") || str.equals("off") || str.equals("OFF") || str.equals("no") || str.equals("NO"))
			{
				return false;
			}
			else
			{
				Console::WriteLine((String)"Error: invalid String in function String::asBool(\"" + str + "\")");
				return false;
			}
		}
	}

	int String::asInt(const String&str)
	{
		for(int i=0; i<str.length(); i++)
		{
			char c = str.charAt(i);
			if(!((c>='0' && c<='9') || (c=='-' && i==0)))
			{
				Console::WriteLine((String)"Error: invalid String in function String::asInt(\"" + str + "\")");
				return 0;
			}
		}

		int mult = 1;
		int startIndex = 0;
		if(str.charAt(0)=='-')
		{
			mult = -1;
			startIndex = 1;
		}

		int counter = 0;
		int totalVal = 0;

		for(int i=(str.length()-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += (value*(int)pow((float)10,counter));
			}
			counter++;
		}

		return totalVal*mult;
	}

	long String::asLong(const String&str)
	{
		for(int i=0; i<str.length(); i++)
		{
			char c = str.charAt(i);
			if(!((c>='0' && c<='9') || (c=='-' && i==0)))
			{
				Console::WriteLine((String)"Error: invalid String in function String::asLong(\"" + str + "\")");
				return 0;
			}
		}

		int mult = 1;
		int startIndex = 0;
		if(str.charAt(0)=='-')
		{
			mult = -1;
			startIndex = 1;
		}

		int counter = 0;
		long totalVal = 0;

		for(int i=(str.length()-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += ((long)value*(long)pow((long double)10,(int)counter));
			}
			counter++;
		}

		return totalVal*mult;
	}

	float String::asFloat(const String&str)
	{
		bool hasDecimal = false;
		int decimalIndex = str.length();

		for(int i=0; i<str.length(); i++)
		{
			char c = str.charAt(i);
			if(!((c>='0' && c<='9') || (c=='-' && i==0)))
			{
				if(c=='.')
				{
					if(hasDecimal)
					{
						Console::WriteLine((String)"Error: invalid String in function String::asFloat(\"" + str + "\")");
						return 0;
					}
					else
					{
						hasDecimal = true;
						decimalIndex = i;
					}
				}
				Console::WriteLine((String)"Error: invalid String in function String::asFloat(\"" + str + "\")");
				return 0;
			}
		}

		int mult = 1;
		int startIndex = 0;
		if(str.charAt(0)=='-')
		{
			mult = -1;
			startIndex = 1;
		}

		int counter = -1;
		float totalVal = 0;

		for(int i=(decimalIndex+1); i<str.length(); i++)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			totalVal += (float)(value*pow((float)10,counter));
			counter--;
		}

		counter = 0;

		for(int i=(decimalIndex-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += (float)(value*(int)pow((float)10,counter));
			}
			counter++;
		}

		return totalVal*mult;
	}

	double String::asDouble(const String&str)
	{
		bool hasDecimal = false;
		int decimalIndex = str.length();

		for(int i=0; i<str.length(); i++)
		{
			char c = str.charAt(i);
			if(!((c>='0' && c<='9') || (c=='-' && i==0)))
			{
				if(c=='.')
				{
					if(hasDecimal)
					{
						Console::WriteLine((String)"Error: invalid String in function String::asDouble(\"" + str + "\")");
						return 0;
					}
					else
					{
						hasDecimal = true;
						decimalIndex = i;
					}
				}
				else
				{
					Console::WriteLine((String)"Error: invalid String in function String::asDouble(\"" + str + "\")");
					return 0;
				}
			}
		}

		int mult = 1;
		int startIndex = 0;
		if(str.charAt(0)=='-')
		{
			mult = -1;
			startIndex = 1;
		}

		int counter = -1;
		double totalVal = 0;

		for(int i=(decimalIndex+1); i<str.length(); i++)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			totalVal += (double)(value*pow((double)10,counter));
			counter--;
		}

		counter = 0;

		for(int i=(decimalIndex-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += (value*(double)pow((double)10,counter));
			}
			counter++;
		}

		return totalVal*mult;
	}

	std::string String::intToString(const int num) const
	{
		std::stringstream ss;
		ss << num;
		std::string s(ss.str());
		return s;
	}

	std::string String::uintToString(const unsigned int num) const
	{
		std::stringstream ss;
		ss << num;
		std::string s(ss.str());
		return s;
	}

	std::string String::floatToString(const float num) const
	{
		/*std::stringstream ss;
		ss.precision(20);
		ss << num;
		std::string s(ss.str());
		return s;*/
		char buffer[20];
		sprintf(buffer, "%g", (double)num);
		return std::string(buffer);
	}

	std::string String::doubleToString(const double num) const
	{
		/*std::stringstream ss;
		ss.precision(20);
		ss << num;
		std::string s(ss.str());
		return s;*/
		char buffer[20];
		sprintf(buffer, "%g", (double)num);
		return std::string(buffer);
	}

	std::string String::longToString(const long num) const
	{
		std::stringstream ss;
		ss << num;
		std::string s(ss.str());
		return s;
	}

	String::String()
	{
		total = 0;
		characters = (char*)calloc(1,1);
		characters[0] = '\0';
	}

	String::String(const String& str)
	{
		total = str.length();
		characters = (char*)calloc(total+1,1);
		for(int i=0; i<total; i++)
		{
			characters[i] = str.characters[i];
		}

		characters[total] = '\0';
	}

	String::String(const std::string&str)
	{
		total = str.length();
		characters = (char*)calloc(total+1,1);
		for(int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(const char*str)
	{
		total = strlen(str);
		characters = (char*)calloc(total+1,1);
		for(int i=0; i<total; i++)
		{
			characters[i] = str[i];
		}

		characters[total] = '\0';
	}

	String::String(const wchar_t*str)
	{
		int len = wcslen(str);
		total = len;
		characters = (char*)calloc(total+1,1);

		wcstombs(characters,str,total+1);

		characters[total] = '\0';
	}

	String::String(const std::wstring&str)
	{
		int len = str.length();
		total = len;
		characters = (char*)calloc(total+1,1);

		wcstombs(characters,str.c_str(),total+1);

		characters[total] = '\0';
	}

	String::String(const char c)
	{
		total = 1;
		characters = (char*)calloc(total+1,1);

		characters[0] = c;
		characters[1] = '\0';
	}

	String::String(const unsigned char num)
	{
		std::string str = intToString((int)num);
		total = str.length();
		characters = (char*)calloc(total+1,1);

		for(int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(const bool b)
	{
		if(b)
		{
			characters = (char*)calloc(4+1,1);
			characters[0] = 't';
			characters[1] = 'r';
			characters[2] = 'u';
			characters[3] = 'e';
			characters[4] = '\0';
			total = 4;
		}
		else
		{
			characters = (char*)calloc(5+1,1);
			characters[0] = 'f';
			characters[1] = 'a';
			characters[2] = 'l';
			characters[3] = 's';
			characters[4] = 'e';
			characters[5] = '\0';
			total = 5;
		}
	}

	String::String(const int num)
	{
		std::string str = intToString(num);
		total = str.length();
		characters = (char*)calloc(total+1,1);

		for(int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(const unsigned int num)
	{
		std::string str = uintToString(num);
		total = str.length();
		characters = (char*)calloc(total+1,1);

		for(int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(const float num)
	{
		std::string str = floatToString(num);
		total = str.length();
		characters = (char*)calloc(total+1,1);

		for(int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(const double num)
	{
		std::string str = doubleToString(num);
		total = str.length();
		characters = (char*)calloc(total+1,1);

		for(int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(const long num)
	{
		std::string str = longToString(num);
		total = str.length();
		characters = (char*)calloc(total+1,1);

		for(int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::~String()
	{
		free(characters);
		characters = NULL;
	}

	String::operator char*()
	{
		return characters;
	}

	String::operator const char*()
	{
		return characters;
	}

	String::operator std::string()
	{
		return std::string(characters);
	}

	String::operator std::wstring()
	{
		wchar_t*str = new wchar_t[total+1];
		mbstowcs(str,characters,total+1);
		std::wstring newStr(str);
		delete[] str;
		return newStr;
	}

	String::operator char*() const
	{
		return characters;
	}

	String::operator const char*() const
	{
		return characters;
	}

	String::operator std::string() const
	{
		return std::string(characters);
	}

	String::operator std::wstring() const
	{
		wchar_t*str = new wchar_t[total+1];
		mbstowcs(str,characters,total+1);
		std::wstring newStr(str);
		delete[] str;
		return newStr;
	}

	String String::operator+(const String& str) const
	{
		String newStr;
		int total2 = total + str.length();
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.characters[counter];
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const std::string& str) const
	{
		String newStr;
		int total2 = total + str.length();
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const char*str) const
	{
		String newStr;
		int total2 = total + strlen(str);
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str[counter];
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const wchar_t*str) const
	{
		String newStr;
		String str2(str);
		int total2 = total + str2.length();
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str2.characters[counter];
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const std::wstring& str) const
	{
		String newStr;
		String str2(str);
		int total2 = total + str2.length();
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str2.characters[counter];
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const bool b) const
	{
		String newStr = characters;
		if(b)
		{
			newStr += "true";
		}
		else
		{
			newStr += "false";
		}
		return newStr;
	}

	String String::operator+(const char c) const
	{
		String newStr;
		int total2 = total+1;
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		newStr.characters[total] = c;
		newStr.characters[total+1] = '\0';
		return newStr;
	}

	String String::operator+(const unsigned char num) const
	{
		String newStr;
		std::string str = intToString((int)num);
		int total2 = total + str.length();
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const int num) const
	{
		String newStr;
		std::string str = intToString(num);
		int total2 = total + str.length();
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const unsigned int num) const
	{
		String newStr;
		std::string str = uintToString(num);
		int total2 = total + str.length();
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const long num) const
	{
		String newStr;
		std::string str = longToString(num);
		int total2 = total + str.length();
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const float num) const
	{
		String newStr;
		std::string str = floatToString(num);
		int total2 = total + str.length();
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const double num) const
	{
		String newStr;
		std::string str = doubleToString(num);
		int total2 = total + str.length();
		newStr.characters = (char*)realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String& String::operator+=(const String& str)
	{
		int total2 = total + str.length();
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str.characters[counter];
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const std::string& str)
	{
		int total2 = total + str.length();
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const char*str)
	{
		int total2 = total + strlen(str);
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str[counter];
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const wchar_t*str)
	{
		String str2(str);
		int total2 = total + str2.length();
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str2.characters[counter];
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const std::wstring str)
	{
		String str2(str);
		int total2 = total + str2.length();
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str2.characters[counter];
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const bool b)
	{
		if(b)
		{
			characters = (char*)realloc(characters, total+5);
			characters[total]   = 't';
			characters[total+1] = 'r';
			characters[total+2] = 'u';
			characters[total+3] = 'e';
			characters[total+4] = '\0';
			total += 4;
		}
		else
		{
			characters = (char*)realloc(characters, total+6);
			characters[total]   = 'f';
			characters[total+1] = 'a';
			characters[total+2] = 'l';
			characters[total+3] = 's';
			characters[total+4] = 'e';
			characters[total+5] = '\0';
			total += 5;
		}
		return *this;
	}

	String& String::operator+=(const char c)
	{
		int total2 = total+1;
		characters = (char*)realloc(characters, total2+1);
		characters[total]=c;
		characters[total2]='\0';
		total = total2;
		return *this;
	}

	String& String::operator+=(const unsigned char num)
	{
		std::string str2 = intToString((int)num);
		int total2 = total + str2.length();
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const int num)
	{
		std::string str2 = intToString(num);
		int total2 = total + str2.length();
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const unsigned int num)
	{
		std::string str2 = uintToString(num);
		int total2 = total + str2.length();
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const long num)
	{
		std::string str2 = longToString(num);
		int total2 = total + str2.length();
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const float num)
	{
		std::string str2 = floatToString(num);
		int total2 = total + str2.length();
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const double num)
	{
		std::string str2 = doubleToString(num);
		int total2 = total + str2.length();
		characters = (char*)realloc(characters, total2+1);
		int counter = 0;
		for(int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const String& str)
	{
		int total2 = str.length();
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str.characters[i];
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const std::string& str)
	{
		int total2 = str.length();
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const char*str)
	{
		int total2 = strlen(str);
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str[i];
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const wchar_t*str)
	{
		String str2(str);
		int total2 = str2.length();
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str2.characters[i];
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const std::wstring& str)
	{
		String str2(str);
		int total2 = str2.length();
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str2.characters[i];
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const bool b)
	{
		if(b)
		{
			characters = (char*)realloc(characters, 5);
			characters[0] = 't';
			characters[1] = 'r';
			characters[2] = 'u';
			characters[3] = 'e';
			characters[4] = '\0';
			total = 4;
		}
		else
		{
			characters = (char*)realloc(characters, 6);
			characters[0] = 'f';
			characters[1] = 'a';
			characters[2] = 'l';
			characters[3] = 's';
			characters[4] = 'e';
			characters[5] = '\0';
			total = 5;
		}
		return *this;
	}

	String& String::operator=(const char c)
	{
		int total2 = 1;
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		characters[0] = c;
		characters[1] = '\0';
		return *this;
	}

	String& String::operator=(const unsigned char num)
	{
		std::string str2 = intToString((int)num);
		int total2 = str2.length();
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const int num)
	{
		std::string str2 = intToString(num);
		int total2 = str2.length();
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const unsigned int num)
	{
		std::string str2 = uintToString(num);
		int total2 = str2.length();
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const long num)
	{
		std::string str2 = longToString(num);
		int total2 = str2.length();
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const float num)
	{
		std::string str2 = floatToString(num);
		int total2 = str2.length();
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const double num)
	{
		std::string str2 = doubleToString(num);
		int total2 = str2.length();
		characters = (char*)realloc(characters, total2+1);
		total = total2;
		for(int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	bool String::operator==(String& cmp)
	{
		return equals(cmp);
	}

	bool String::operator==(const char*cmp)
	{
		return equals(cmp);
	}

	std::ostream& operator<<(std::ostream& stream, const String& str)
	{
		return stream << str.characters << "";
	}

	bool String::equals(const String& cmp) const
	{
		if(cmp.length()==length())
		{
			for(int i=(total-1); i>=0; i--)
			{
				if((int)characters[i] != (int)cmp.characters[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	bool String::equals(const char*cmp) const
	{
		if(cmp!=NULL)
		{
			int cmpLength = strlen(cmp);
			if(cmpLength==length())
			{
				for(int i=0; i<total; i++)
				{
					if(characters[i] != cmp[i])
					{
						return false;
					}
				}
				return true;
			}
			return false;
		}
		return false;
	}

	void String::clear()
	{
		characters = (char*)realloc(characters, 1);
		characters[0] = '\0';
		total = 0;
	}

	int String::length() const
	{
		return total;
	}

	char String::charAt(int index) const
	{
		return characters[index];
	}

	String String::substring(int beginIndex) const
	{
		String str;
		str.characters = (char*)realloc(str.characters, (total-beginIndex)+1);
		int counter = 0;
		for(int i=beginIndex; i<total; i++)
		{
			str.characters[counter] = characters[i];
			counter++;
		}
		str.characters[counter] = '\0';
		str.total = counter;
		return str;
	}

	String String::substring(int beginIndex, int endIndex) const
	{
		String str;
		str.characters = (char*)realloc(str.characters, (endIndex-beginIndex)+1);
		int counter = 0;
		for(int i=beginIndex; i<endIndex; i++)
		{
			str.characters[counter] = characters[i];
			counter++;
		}
		str.characters[counter] = '\0';
		str.total = counter;
		return str;
	}

	String String::trim() const
	{
		int i=0;

		int startIndex = 0;

		bool hitLetter = false;

		while(!hitLetter && i<total)
		{
			char c = charAt(i);

			if(c!=' ')
			{
				startIndex = i;
				hitLetter = true;
			}

			i++;
		}

		if(!hitLetter)
		{
			return String("");
		}
		
		hitLetter = false;
		i = total-1;

		int endIndex = 0;

		while(!hitLetter && i>=0)
		{
			char c = charAt(i);

			if(c!=' ')
			{
				endIndex = i+1;
				hitLetter = true;
			}

			i--;
		}

		return substring(startIndex, endIndex);
	}

	int String::indexOf(String str) const
	{
		int length = str.length();
		if(str.length()>0 && total >= length)
		{
			std::vector<int> indexes = std::vector<int>();
			int indexTotal = 0;

			char c = str.charAt(0);

			for(int i=0; i<total; i++)
			{
				if((int)characters[i]==(int)c)
				{
					indexTotal++;
					indexes.resize(indexTotal);
					indexes[indexTotal-1] = i;
				}
			}

			if(indexTotal>0)
			{
				int endOfThis = total - 1;
				for(int i=0; i<indexTotal; i++)
				{
					int end = indexes[i] + length;
					if(end>endOfThis)
					{
						return -1;
					}
					else
					{
						bool correct = true;
						int counter = 0;
						for(int j=indexes[i]; j<end; j++)
						{
							if((int)characters[j]==(int)str.characters[counter])
							{
								counter++;
							}
							else
							{
								correct = false;
								j = end;
							}
						}

						if(correct)
						{
							return indexes[i];
						}
					}
				}
			}
			return -1;
		}
		return -1;
	}
}