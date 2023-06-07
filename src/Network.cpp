#include "Network.hpp"

void Network::run()
{
    string command, arg;
    vector<string> args;
    stringstream commandStream;

    while(getline(cin, command))
    {
        commandStream = stringstream(command);
        getline(commandStream,command,COMMAND_DELIM);
        getline(commandStream,arg);

        if(command == "topology")
        {
            graph = new Graph(arg);
        }
        else if(command == "lsrp"){
            args = tokenize(arg,'-');
            graph->link_state(stoi(arg));
        }
        else if(command == "dvrp")
        {
            args = tokenize(arg,'-');
            graph->distance_vector(stoi(arg));
        }
        else if(command == "show")
        {
            graph->show();
        }
        else if(command == "modify")
        {
            args = tokenize(arg,'-');
            graph->modify_edge(stoi(args[0]),stoi(args[1]),stoi(args[2]));
        }
        else if(command == "remove")
        {
            args = tokenize(arg,'-');
            graph->delete_edge(stoi(args[0]),stoi(args[1]));
        }
        else
        {
            cout << "Error: Unknown Command" << endl;
        }
    }
}

vector<string> tokenize(string _string, char delimeter)
{
    string currentToken = "";
    vector<string> tokens;
    for (int i = 0; i < _string.size(); i++)
    {
        if (_string[i] == delimeter)
        {
            tokens.push_back(currentToken);
            currentToken = "";
        }
        else
        currentToken += _string[i];
    }
    tokens.push_back(currentToken);
    return tokens;
}
