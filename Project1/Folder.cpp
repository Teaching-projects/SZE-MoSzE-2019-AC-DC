#include <string>
#include <iostream>
#include <vector>
#include "Folder.h"

	bool Folder::dirnamecheck(vector<Folder> tree, vector<string> currentpath, string name)
	{	
		currentpath.push_back(name);
		for (size_t i = 0; i < tree.size(); i++)
		{
			if (tree[i].AbsolutePath == currentpath)
			{	

					cout << "ERROR: Directory or file with that name already exists.\n";
					return false;			
			}
		}
		return true;
	}
	Folder Folder::mk(vector<Folder> tree, vector<string> currentpath, string name, string type )
	{
		Folder tempFolder;
		tempFolder.name = name;		
		tempFolder.parentfolder = currentpath.back();
		tempFolder.type = type;
		tempFolder.AbsolutePath = currentpath;		
		tempFolder.AbsolutePath.push_back(name);
		return tempFolder;
	}

