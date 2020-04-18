#include <Windows.h>
#include "Utils.h"


vector<int> split(string line, string delimeter)
{
	vector<int> tokens;
	size_t last = 0; size_t next = 0;
	while ((next = line.find(delimeter, last)) != string::npos)
	{
		int currentvValue;
		std::istringstream(line.substr(last, next - last)) >> currentvValue;
		tokens.push_back(currentvValue);
		last = next + 1;
	}

	int lastValue;
	std::istringstream(line.substr(last)) >> lastValue;
	tokens.push_back(lastValue);

	return tokens;
}

/*
char * string to wchar_t* string.
*/
wstring ToWSTR(string st)
{
	const char* str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring wstr(wcstring);

	// delete wcstring   // << can I ? 
	return wstr;
}

/*
	Convert char* string to wchar_t* string.
*/
LPCWSTR ToLPCWSTR(string st)
{
	const char* str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring* w = new wstring(wcstring);

	// delete wcstring   // << can I ? 
	return w->c_str();
}