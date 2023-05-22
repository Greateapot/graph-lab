#include "graph.h"

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <exception>
#include <functional>

using namespace std;

GCity::GCity(string name) : name(name){};

bool operator==(const GCity &a, const GCity &b)
{
    return a.name == b.name;
}

GRoad::GRoad(GCity *A, GCity *B, size_t length) : A(A), B(B), length(length){};

GRoad *GRoad::contains(vector<GRoad *> &roads)
{
    GRoad *r = nullptr;
    for (auto it = roads.begin(); r == nullptr && it != roads.end(); it++)
        if (A == (*it)->A && B == (*it)->B)
            r = *it;
    return r;
}

//GRoad *GRoad::reverse()
//{
//    return new GRoad(B, A, length);
//}

//void Graph::gen_matrix()
//{
//    for (auto m : matrix)
//        m.clear();
//    matrix.clear();

//    for (int i = 0; i < (int)cities.size(); i++)
//    {
//        vector<int> m;
//        for (int j = 0; j < (int)cities.size(); j++)
//        {
//            GRoad *r = GRoad(cities[i], cities[j], 0).contains(roads);
//            m.push_back(r == nullptr ? -1 : r->length);
//        }
//        matrix.push_back(m);
//    }
//}

string Graph::solve_depth(size_t index, function<void(string, size_t)> cb)
{
    vector<string> visited;
    vector<pair<string, size_t>> results;
    _solve_depth(cities[index], visited, results, cities[index]->name, 0, cb);

    string output = "";
     for (pair<string, size_t> &p : results)
         output += p.first + " : " + to_string(p.second) + '\n';
    return output;
}

void Graph::solve_width(size_t index, void(*cb)(string))
{
    vector<string> visited;
    queue<GCity *> q;

    GCity *c = cities[index];
    visited.push_back(c->name);

    while (c != nullptr)
    {
        for (GCity *neighbor : c->neighbors)
            if (find(visited.begin(), visited.end(), neighbor->name) == visited.end())
            {
                visited.push_back(neighbor->name);
                q.push(neighbor);
            }
        cb(c->name);
        if (!q.empty())
        {
            c = q.front();
            q.pop();
        }
        else
            c = nullptr;
    }
}

string Graph::solve_DXTR(size_t index, void(*cb)(string, size_t))
{
    for (GCity *c : cities)
        c->mark_DXTR = INF;

    vector<string> visited;
    GCity *city = cities[index];
    city->mark_DXTR = 0;

    _solve_DXTR(city, visited, cb);

    string output = "";
     for (GCity *c : cities)
         output += c->name + " : " + to_string(c->mark_DXTR) + '\n';
    return output;
}

void Graph::_solve_depth(GCity *city, vector<string> &visited, vector<pair<string, size_t>> &results, string message, size_t road_length, function<void(string, size_t)> cb)
{
    visited.push_back(city->name);
    cb(city->name, road_length);

    for (GCity *neighbor : city->neighbors)
        if (find(visited.begin(), visited.end(), neighbor->name) == visited.end())
        {
            string m = message + " -> " + neighbor->name;
            GRoad *pr = GRoad(city, neighbor, 0).contains(roads);
            size_t rl = road_length + (pr != nullptr ? pr->length : 0);
            _solve_depth(neighbor, visited, results, m, rl, cb);
        }

    visited.pop_back();
    if (road_length > 0)
        results.push_back(pair<string, size_t>(message, road_length));
}

void Graph::_solve_DXTR(GCity *city, vector<string> &visited, void(*cb)(std::string, std::size_t))
{
    visited.push_back(city->name);
    cb(city->name, city->mark_DXTR);

    GCity *min = nullptr;
    size_t ml = INF;

    for (GCity *neighbor : city->neighbors)
        if (find(visited.begin(), visited.end(), neighbor->name) == visited.end())
        {
            size_t length = GRoad(city, neighbor, 0).contains(roads)->length;
            if (city->mark_DXTR + length < neighbor->mark_DXTR)
                neighbor->mark_DXTR = city->mark_DXTR + length;
            if (length < ml)
            {
                ml = length;
                min = neighbor;
            }
        }

    if (min != nullptr)
        _solve_DXTR(min, visited, cb);
}
