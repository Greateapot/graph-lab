#pragma once

#define INF int(10E10)

#include <string>
#include <vector>
#include <functional>

struct GCity
{
    std::string name;
    std::vector<GCity *> neighbors;
    std::vector<GCity *> neighbor_of;
    std::size_t mark_DXTR = INF;

    GCity(std::string name);

    friend bool operator==(const GCity &, const GCity &);
};

struct GRoad
{
    GCity *A = nullptr, *B = nullptr; // A -> B
    std::size_t length = 0;

    GRoad(GCity *, GCity *, std::size_t);

    GRoad *contains(std::vector<GRoad *> &);

    //    GRoad *reverse();
};

class Graph
{
public:
    std::vector<GCity *> cities;
    std::vector<GRoad *> roads;
    std::vector<std::vector<int>> matrix;

    //    void gen_matrix();

    std::string solve_depth(std::size_t, std::function<void(std::string, std::size_t)>);
    void solve_width(std::size_t, void (*)(std::string));
    std::string solve_DXTR(std::size_t, void (*)(std::string, std::size_t));

private:
    void _solve_depth(GCity *, std::vector<std::string> &, std::vector<std::pair<std::string, std::size_t>> &,
                      std::string, std::size_t, std::function<void(std::string, std::size_t)>);

    void _solve_DXTR(GCity *, std::vector<std::string> &, void (*)(std::string, std::size_t));
};
