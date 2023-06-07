#ifndef __Graph_HPP__
#define __Graph_HPP__

#include <vector>
#include <utility>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <chrono>

using namespace std;

const int INF = 1e9;

using namespace std;

int get_digits_count(int x);

class Graph
{
private:
    set<int> nodes;
    map<pair<int, int>, int> weight;
public:
    Graph(string topology);

    void add_edge(int v, int u, int w);
    void show();
    void delete_edge(int v, int u);
    void modify_edge(int v, int u, int cost);
    void link_state(int source);
    void distance_vector(int source);
};


#endif