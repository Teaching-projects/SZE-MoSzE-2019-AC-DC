#include <string>
#include <iostream>
#include <vector>
#include "Folder.h"

using namespace std;

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
	currentpath.push_back("~");
	do
	{
		cpath = "";
	for (size_t i = 0; i < currentpath.size(); i++)
	{
		cpath = cpath+'/'+currentpath[i];
		
	}
	cout<<cpath <<"$ ";
	do
	{
		getline(cin, input_raw);
		
	} while (input_raw=="");
	command = Folder().split(input_raw,' ');	
	if (command[0] == "mkdir")
	{
		if (!parametercheck(command))cout << "ERROR: Missing parameter. \n";
		else
		{
			if (command[1].find("/")==0)
			{
				vector<string>tempvector =Folder().FindAbsPath(tree,currentpath,command[1],"abs");
				if (!tempvector.empty())
				{
					tree.push_back(Folder().mk(tree, tempvector, Folder().split(command[1], '/').back(), "directory"));
				}
			}
			else if (command[1].find("../")==0) // TO DO
			{
								
				vector<string>tempvector = Folder().FindAbsPath(tree, currentpath, command[1], "rel");
				if (!tempvector.empty())
				{
					tree.push_back(Folder().mk(tree, tempvector, Folder().split(command[1], '/').back(), "directory"));
				}
			}
			else if (Folder().dirnamecheck(tree,currentpath,command[1]))
			{
				
				tree.push_back(Folder().mk(tree, currentpath, command[1], "directory"));
			}			
		}
		
	}
	else if (command[0] == "touch")
	{
		if (!parametercheck(command))cout << "ERROR: Missing parameter. \n";
		else
		{
			if (command[1].find("/") == 0)
			{
				vector<string>tempvector = Folder().FindAbsPath(tree, currentpath, command[1], "abs");
				if (!tempvector.empty())
				{
					tree.push_back(Folder().mk(tree, tempvector, Folder().split(command[1], '/').back(), "file"));
				}
			}
			else if (command[1].find("../") == 0) // TO DO
			{

				vector<string>tempvector = Folder().FindAbsPath(tree, currentpath, command[1], "rel");
				if (!tempvector.empty())
				{
					tree.push_back(Folder().mk(tree, tempvector, Folder().split(command[1], '/').back(), "file"));
				}
			}
			else if (Folder().dirnamecheck(tree, currentpath, command[1]))
			{

				tree.push_back(Folder().mk(tree, currentpath, command[1], "file"));
			}
		}
		/*if (!parametercheck(command))cout << "ERROR: Missing parameter. \n";
		else
		{
			if (Folder().dirnamecheck(tree, currentpath, command[1]))
			{
				tree.push_back(Folder().mk(tree, currentpath, command[1], "file"));
			}
		}*/
	}
	else if (command[0] == "rm")// -RF hibás 
	{
		bool exists = false;
		bool haschild = false;		
		int parameterindex = 1;
		int dirindex=0;
		vector<string> ABSPATH;
		
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
			if (command[parameterindex].find("/") == 0)
			{
				ABSPATH = Folder().FindAbsPath(tree, currentpath, command[parameterindex], "abs");
				if(!ABSPATH.empty()) ABSPATH.push_back(Folder().split(command[parameterindex], '/').back());				
			}
			else if (command[parameterindex].find("../") == 0)
			{
				ABSPATH = Folder().FindAbsPath(tree, currentpath, command[parameterindex], "rel");
				if (!ABSPATH.empty()) ABSPATH.push_back(Folder().split(command[parameterindex], '/').back());				
			}
			else
			{
				ABSPATH = currentpath;
				ABSPATH.push_back(command[parameterindex]);
			}			
			for (size_t i = 0; i < tree.size(); i++)
			{
				if (tree[i].AbsolutePath==ABSPATH)
				{
					exists = true;	
					dirindex = i;
				}
				
				if (tree[i].parentfolder == Folder().split(command[parameterindex], '/').back())
				{
					haschild = true;
					if (command[1] == "-rf")
					{
						tree.erase(tree.begin() + i-1);
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
			if (currentpath.back() != "~")
			{
				currentpath.pop_back();
			}
			else
			{
				cout << "ERROR: Root has no parent\n";
			}
		}
		else if (command[1].find("../") == 0)
		{			
			command[1].erase(0, 2);			
			vector<string> relpath;
			relpath = Folder().split(command[1], '/');
			relpath.insert(relpath.begin(), currentpath.begin(), currentpath.end());
			bool error = true;
			for (size_t i = 0; i < tree.size(); i++)
			{
				
				if (tree[i].AbsolutePath == relpath);
				{
					currentpath = tree[i].AbsolutePath;
					//currentpath.push_back(tree[i].name);
					error = false;
				}
			}
			if (error)
			{
				cout << "ERROR: No directory with that names exists.\n";
			}
		}
		else if (command[1].find("/") == 0)
		{			
			bool error = true;
			for (size_t i = 0; i < tree.size(); i++)
			{
				
				if(tree[i].AbsolutePath == Folder().split(command[1],'/'));
				{	
					
					currentpath = tree[i].AbsolutePath;
				//	currentpath.push_back(tree[i].name);
					error= false;					

				}				
			}
			if (command[1] == "/")
			{
				currentpath.clear();
				currentpath.push_back("~");

			}
			else if (error)
			{
				cout << "ERROR: No directory with that names exists.\n";
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
					if (tree[i].name == command[1] && tree[i].type=="directory")
					{
						currentpath.push_back(command[1]);
					}				
				}

			}
			
			if (currentpath.back() != command[1] && command[1].find("/") != 0 && command[1].find("../") != 0)
			{
				cout << "ERROR: No directory with that names exists.\n";
			}
		}
	}	
	else if (command[0] == "ls")
	{
	vector<string> tempvector;	
		for (size_t i = 0; i < tree.size(); i++)
		{
			tempvector = tree[i].AbsolutePath;
			tempvector.pop_back();
			if (tempvector == currentpath)
				cout << tree[i].name<<"\n";
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
