#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;
class Folder {	
public:
	bool dirnamecheck(vector<Folder> tree, vector<string> currentpath, string name);
	Folder mk(vector<Folder> tree, vector<string> currentpath, string name, string type);	
	vector<string> split(string input, char charsplit);
	vector<string> FindAbsPath(vector<Folder> tree, vector<string> currentpath, string command, string type);
	string name;
	vector<string> AbsolutePath;
	string parentfolder;
	string type;
	int Parentindex;

};
