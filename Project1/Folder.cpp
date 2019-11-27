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
	vector<string> Folder::split(string input, char charsplit)
	{
		vector<string> command;
		string temp;
		for (size_t i = 0; i < input.length() + 1; i++)
		{
			if (input[i] == charsplit)
			{
				command.push_back(temp);
				temp = "";
			}
			if (input[i] != charsplit)
			{
				temp = temp + input[i];

			}
			if (i == input.length() - 1)
			{

				command.push_back(temp);
				temp = "";


			}

		}
		return command;

	}
	vector<string> Folder::FindAbsPath(vector<Folder> tree, vector<string> currentpath, string command, string type)
	{
		command.erase(0, 1);
		vector < string> tempvector;
		if (type == "rel")
		{			
			command.erase(0, 2);
			tempvector = Folder().split(command, '/');
			tempvector.insert(tempvector.begin(), currentpath.begin(), currentpath.end());				
		}
		if (type == "abs")
		{			
			tempvector = Folder().split(command, '/');
			tempvector.insert(tempvector.begin(), "~");
			
		}
		tempvector.pop_back();		
		bool error = true;
		if (Folder().dirnamecheck(tree, currentpath, Folder().split(command, '/').back()))
		{
			for (size_t i = 0; i < tree.size(); i++)
			{
				if (tree[i].AbsolutePath == tempvector)
				{
					return tempvector;
					error = false;
				}
				
			}
			if (error)
			{
				cout << "ERROR: Path does not exist.\n";
				return {};

			}
		}
	}
