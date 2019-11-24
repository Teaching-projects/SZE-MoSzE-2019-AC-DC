#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;
class Folder {	
public:
	bool dirnamecheck(vector<Folder> tree, vector<string> currentpath, string name);
	Folder mk(vector<Folder> tree, vector<string> currentpath, string name, string type);
	string name;
	string parentfolder;
	string type;

};
