#include"Graph.hpp"
#include"Network.hpp"

Graph::Graph(string topology) 
{
    vector<string> tokens = tokenize(topology, ' ');
    for (auto token: tokens)
    {
        vector<string> t = tokenize(token, '-');
        int source = stoi(t[0]);
        int destination = stoi(t[1]);
        int cost = stoi(t[2]);
        if(source == destination)
        {
            cout << "Source: " << source << " and destination: " << destination << " cannot be same!" << endl;
            continue;
        }

        add_edge(source, destination, cost);
        add_edge(destination, source, cost);
        nodes.insert(source);
        nodes.insert(destination);
    }
    cout << "OK" << endl;
}



void Graph::delete_edge(int source, int destination){
    if(nodes.find(source) == nodes.end() || nodes.find(source) == nodes.end())
    {
        cout << "Invalid Node!" << endl;
        return;
    }

    if(weight.find(make_pair(destination,source)) == weight.end())
    {
        cout << "No Route To Delete!" << endl;
        return;
    }

    weight.erase(make_pair(destination,source));
    weight.erase(make_pair(source,destination));
    cout << "OK" << endl;
}

void Graph::modify_edge(int source, int destination, int cost)
{
    if(source == destination)
    {
        cout << "Source And Destination Cannot Be Same" << endl;
        return;
    }

    weight[make_pair(source,destination)]=cost;
    weight[make_pair(destination,source)]=cost;

    cout << "OK" << endl;
}

void Graph::add_edge(int source, int destination, int w)
{   
    weight[make_pair(source, destination)] = w;
    weight[make_pair(destination, source)] = w;
}

void Graph::link_state(int source)
{
    auto start_time = chrono::steady_clock::now();

    int number_of_nodes = nodes.size();

    vector<bool> mark(number_of_nodes + 1, false);
    vector<int> distance(number_of_nodes + 1, INF);
    vector<int> parent(number_of_nodes + 1, -1);

    for(int node: nodes)
    {
        if(weight.find(make_pair(source, node)) != weight.end())
        {
            distance[node] = weight[make_pair(source, node)];
            parent[node] = source;
        }
        else
        {
            distance[node] = INF;
        }
    }

    mark[source] = true;
    distance[source] = 0;

    int size = 1;
    while (size < number_of_nodes)
    {
        int mn = INF, source;
        for (auto node: nodes)
        {
            if (mark[node])
                continue;
            if (distance[node] < mn)
            {
                mn = distance[node];
                source = node;
            }
        }

        cout << "   |Iter " + to_string(size) << ":" << endl;
        cout << "Dest|";
        for (auto node: nodes)
        {
            int column = 4 - get_digits_count(node);
            for (int i = 0; i < column; i++)
                cout << " ";
            cout << node << "|";
        }
        cout << endl;
        cout << "Cost|";
        for (auto node: nodes)
        {
            int column = 4 - get_digits_count(distance[node]);
            if (distance[node] == INF)
                column = 2;
            for (int i = 0; i < column; i++)
                cout << " ";
            cout << (distance[node] == INF ? -1 : distance[node]) << "|";
        }
        cout << endl;
        for (int i = 0; i < (nodes.size() + 1) * 5; i++)
            cout << "-";
        cout << endl;

        mark[source] = true;
        size += 1;
        for (auto node: nodes)
        {
            if (mark[node])
                continue;
            if (weight.find(make_pair(source, node)) == weight.end())
                continue;
            if (distance[source] + weight[make_pair(source, node)] < distance[node])
            {
                distance[node] = distance[source] + weight[make_pair(source, node)];
                parent[node] = source;
            }
        }  
    }


    string path;
    cout<<"\nPath  [s] -> [d]         Min-Cost         Shortest Path"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for (auto node: nodes)
    {
        path="";
        if (node == source)
            continue;
        
        cout << "     " << source << "  ->  " << node << " ";
        int column = 15 - get_digits_count(node);
        for (int i = 0; i < column; i++)
        {
            cout << " ";
        }

        cout << distance[node];
        column= 15 - get_digits_count(distance[node]);
        for (int i = 0; i < column; i++)
        {
                cout << " ";
        }

        int p = node;
        while (parent[p] != -1)
        {   
            path=" -> "+to_string(p) + path;
            p = parent[p];
        }
        cout << to_string(source) << path << endl;
    }

    auto finish_time = chrono::steady_clock::now();
    auto elapsed_seconds = chrono::duration_cast<std::chrono::duration<double> >(finish_time - start_time).count();
    cout << "Elapsed: " << elapsed_seconds << endl;
}

int get_digits_count(int x)
{
    if (x == 0)
        return 1;
    int count = 0;
    while (x)
    {
        x /= 10;
        count++;
    }
    return count;
}

void Graph::show()
{
    cout << "    |";
    for (auto node: nodes)
    {
        int column = 4 - get_digits_count(node);
        for (int i = 0; i < column; i++)
            cout << " ";
        cout << node;
        cout << "|";
    }
    cout << endl;

    for (int i = 0; i < (nodes.size() + 1) * 5; i++)
        cout << "-";
    cout << endl;

    for (auto source: nodes)
    {
        for (int i = 0; i < 4 - get_digits_count(source); i++)
            cout << " ";
        cout << source << "|";

        for (auto destination: nodes)
        {
            int w, column;
            if(destination == source)
            {
                column = 3;
                w = 0;
            }
            else if (weight.find(make_pair(source, destination)) == weight.end())
            {
                column = 2;
                w = -1;
            }
            else
            {
                w = weight[make_pair(source, destination)];
                column = 4 - get_digits_count(w);
                if (w <= 0)
                    column--;
            }
            
            for (int i = 0; i < column; i++)
                cout << " ";
            cout << w << "|";
        }
        cout << endl;
    }
}

void Graph::distance_vector(int source)
{
    auto start_time = chrono::steady_clock::now(); 

    int number_of_nodes = nodes.size();

    vector<bool> mark(number_of_nodes + 1, false);
    vector<int> distance(number_of_nodes + 1, INF);
    vector<int> parent(number_of_nodes + 1, -1);

    distance[source] = 0;


    while (1)
    {
        bool updated = false;
        for (auto it = weight.begin(); it != weight.end(); it++)
        {
            int source = it->first.first, destination = it->first.second, w = it->second;
            if (distance[source] + w < distance[destination])
            {
                distance[destination] = distance[source] + w;
                parent[destination] = source;
                updated = true;
            }
        }
        if (!updated)
            break;
    }


    string path;
    int prev_p;
    cout<<"\nDest   |     NextHop    |    Dist    |    Shortest Path"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for (auto node: nodes)
    {
        path="";
        if (node == source)
            continue;
        cout <<  node ;
        int column = 15 - get_digits_count(node);
        for (int i = 0; i < column; i++)
            cout << " ";
        
        cout << "|";
        int p = node;
        while (parent[p] != -1)
        {   
            path=" -> "+to_string(p)+path;
            prev_p=p;
            p = parent[p];
        }

        cout<<prev_p;
        column= 15 - get_digits_count(prev_p);
        for (int i = 0; i < column; i++)
                cout << " ";
        cout << "|";
        cout<<distance[node];
        column= 12 - get_digits_count(distance[node]);
        for (int i = 0; i < column; i++)
                cout << " ";
        cout << "|";
        cout << to_string(source) << path << endl;
    }

    auto finish_time = chrono::steady_clock::now();
    auto elapsed_seconds = chrono::duration_cast<std::chrono::duration<double> >(finish_time - start_time).count();
    cout << "Elapsed: " << elapsed_seconds << endl;
}