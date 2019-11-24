#include <string>
#include <iostream>
#include <vector>
#include "Folder.h"

	bool dirnamecheck(vector<Folder> tree, vector<string> currentpath, string name)
	{
		for (size_t i = 0; i < tree.size(); i++)
		{
			if (tree[i].parentfolder == currentpath.back())
			{
				if (tree[i].name == name)
				{

					cout << "ERROR: Directory or file with that name already exists.\n";
					return false;
				}
			}
		}
		return true;
	}
	Folder mk(vector<Folder> tree, vector<string> currentpath, string name, string type)
	{
		Folder tempFolder;
		tempFolder.name = name;
		tempFolder.parentfolder = currentpath.back();
		tempFolder.type = type;
		return tempFolder;
	}

