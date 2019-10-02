#include <string>
#include <iostream>
#include <vector>
#include "Folder.h"
using namespace std;
vector<string> split(string input)
{
	vector<string> command;
	string temp;
	for (size_t i = 0; i < input.length() + 1; i++)
	{
		if (input[i] == ' ')
		{
			command.push_back(temp);			
			temp = "";
		}
		if (input[i] != ' ')
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
bool parametercheck(vector<string> command)
{
	if (command.size() <= 1)
	{
		return false;
		
	}
	else
		return true;
}

int main() {

	string input_raw;
	vector<string> currentpath;
	string cpath;
	string temp="";
	Folder tempFolder;
	vector<string> command;
	vector<Folder> tree;
	bool dirnamecheck=true;
	currentpath.push_back("root");
	do
	{
		cpath = "";
	for (size_t i = 0; i < currentpath.size(); i++)
	{
		cpath = cpath+'/'+currentpath[i];
		
	}
	cout<<cpath <<">";
	do
	{
		getline(cin, input_raw);
		
	} while (input_raw=="");
	command = split(input_raw);
	if (command[0] == "mkdir")
	{
		if (!parametercheck(command))cout << "ERROR: Missing parameter. \n";
		else
		{
			for (size_t i = 0; i < tree.size(); i++)
			{
				if (tree[i].parentfolder == currentpath.back())
				{
					if (tree[i].name == command[1])
					{
						dirnamecheck = false;
						cout << "ERROR: Directory with that name already exists.\n";
					}
				}
			}
			if (dirnamecheck)
			{
				tempFolder.name = command[1];
				tempFolder.parentfolder = currentpath.back();
				tree.push_back(tempFolder);
			}
			dirnamecheck = true;
		}
	}
	else if (command[0] == "cd" && command[1]=="..")
	{
		if (!parametercheck(command))cout << "ERROR: Missing parameter. \n";
		else
		{
			if (currentpath.back() != "root")
			{
				currentpath.pop_back();
			}
			else
			{
				cout << "ERROR: Root has no parent\n";
			}
		}
	}	
	else if (command[0] == "ls")
	{
		for (size_t i = 0; i < tree.size(); i++)
		{
			if (tree[i].parentfolder == currentpath.back())
				cout << tree[i].name<<"\n";
		}
	}
	else if (command[0] == "cd" && command[1] != "..")
	{
		if (!parametercheck(command))cout << "ERROR: Missing parameter. \n";
		else
		{
			if (currentpath.back() == command[1])
			{
				cout << "ERROR: " << command[1] << " directory already selected.\n";
			}
			for (size_t i = 0; i < tree.size(); i++)
			{
				if (tree[i].parentfolder == currentpath.back())
				{
					if (tree[i].name == command[1])
					{
						currentpath.push_back(command[1]);
					}
				}

			}
			if (currentpath.back() != command[1])
			{
				cout << "ERROR: No directory with that names exists.\n";
			}
		}
	}
	else if(command[0]!="exit")
	{
		cout << "ERROR: No such command\n";
	}
	command.clear();	
	} while (input_raw!="exit");
	return 0;
}
