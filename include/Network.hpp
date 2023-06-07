#ifndef __Network_HPP__
#define __Network_HPP__

#include "Graph.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#define COMMAND_DELIM ' '

using namespace std;


vector<string> tokenize(string _string, char delimeter);

class Network
{
private:
    Graph* graph;
public:
    void run();
};



#endif