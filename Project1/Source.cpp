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
bool parametercheck(vector<string> command, int parameternm =1)
{
	if (command.size() <= parameternm)
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
	else if (command[0] == "rm")
	{
		bool exists = false;
		bool haschild = false;
		int parameterindex = 1;
		int dirindex=0;
		
		 if (command[1] == "-rf")
		{
			if (!parametercheck(command,2))cout << "ERROR: Missing parameter. \n";
			else
			{
				parameterindex = 2;
			}
		}
		if (!parametercheck(command))cout << "ERROR: Missing parameter. \n";
		else {
			for (size_t i = 0; i < tree.size(); i++)
			{
				if (tree[i].name == command[parameterindex])
				{
					exists = true;	
					dirindex = i;
				}
				if (tree[i].parentfolder == command[parameterindex])
				{
					haschild = true;
					if (command[1] == "-rf")
					{
						tree.erase(tree.begin() + i);
					}
					
				}

			}
			
			if (!exists)
			{
				cout << "ERROR: Directory with that name does not exist.\n";
			}
			else if (!haschild)
			{
				tree.erase(tree.begin() + dirindex);
			}
			else if (haschild && command[1] != "-rf")
			{
				cout << "ERROR: Directory is not empty.\n";
			}
		}
	}
	else if (command[0] == "cd" )
	{
		if (!parametercheck(command))cout << "ERROR: Missing parameter. \n";
		else if(command[1]=="..")
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
	else if (command[0] == "ls")
	{
		for (size_t i = 0; i < tree.size(); i++)
		{
			if (tree[i].parentfolder == currentpath.back())
				cout << tree[i].name<<"\n";
		}
	}
	/*else if (command[0] == "cd" && command[1] != "..")
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
	}*/
	else if(command[0]!="exit")
	{
		cout << "ERROR: No such command\n";
	}
	command.clear();	
	} while (input_raw!="exit");
	return 0;
}
