#include <Windows.h>

#include <signal.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <sstream>

using namespace std;

vector<int> split(string line, string delimeter);
wstring ToWSTR(string st);

LPCWSTR ToLPCWSTR(string st);

