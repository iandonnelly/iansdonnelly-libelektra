#include <shell.hpp>

#include <kdb>

#include <iostream>
#include <sstream>

using namespace std;
using namespace kdb;

ShellCommand::ShellCommand()
{}

int ShellCommand::execute(int, char**)
{
	KeySet current;
	Key currentKey;

	string commandline;
	string prompt = "> ";

	cout << prompt;
	while (getline(cin, commandline))
	{
		istringstream is (commandline);
		string command;

		is >> command;
		if (command == "kdbGet")
		{
			string parent;
			is >> parent;
			Key parentKey (parent, KEY_END);
			cout << "return value: " << kdb.get(current, parentKey) << endl;
		}
		else if (command == "kdbSet")
		{
			string parent;
			is >> parent;
			Key parentKey (parent, KEY_END);
			cout << "return value: " << kdb.set(current, parentKey) << endl;
		}
		else if (command == "keySetName")
		{
			string name;
			is >> name;
			currentKey.setName(name);
		}
		else if (command == "keySetMeta")
		{
			string name;
			is >> name;
			string value;
			is >> value;
			std::string tmp;
			getline (is, tmp);
			value += tmp;
			currentKey.setMeta(name, value);
			cout << "Set meta " << name << " to " << value << endl;
		}
		else if (command == "keySetString")
		{
			string value;
			is >> value;
			std::string tmp;
			getline (is, tmp);
			value += tmp;
			currentKey.setString(value);
		}
		else if (command == "ksAppendKey")
		{
			current.append(currentKey);
		}
		else if (command == "ksCut")
		{
			string parent;
			is >> parent;
			Key parentKey (parent, KEY_END);

			current.cut (parentKey);
		}
		else if (command == "ksOutput")
		{
			current.rewind();
			while (current.next())
			{
				cout << current.current().getName() << " value: " << current.current().getString() << endl;
			}
		} else {
			cout << "unknown command" << endl;
		}

		cout << prompt;
	}

	return 0;
}

ShellCommand::~ShellCommand()
{}
