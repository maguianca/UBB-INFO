#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct Edge
{
    int flow, capacity;
    int u, v;
};

struct Vertex
{
    int h, e;
};

void preflux(vector<Edge>& edge, vector<Vertex>& ver, int s)
{
    ver[s].h = ver.size();
    for (int i = 0; i < edge.size(); i++)
    {
        if (edge[i].u == s)
        {
            edge[i].flow = edge[i].capacity;
            ver[edge[i].v].e += edge[i].flow;
            edge.push_back({ -edge[i].flow, 0, edge[i].v, s });
        }
    }
}

int overFlowVertex(vector<Vertex>& ver)
{
    for (int i = 1; i < ver.size() - 1; i++)
        if (ver[i].e > 0)
            return i;
    return -1;
}

void update(vector<Edge>& edge, int i, int flow)
{
    int u = edge[i].v, v = edge[i].u;

    for (int j = 0; j < edge.size(); j++)
    {
        if (edge[j].v == v && edge[j].u == u)
        {
            edge[j].flow -= flow;
            return;
        }
    }
    Edge e = { 0, flow, u, v };
    edge.push_back(e);
}

bool pompare(vector<Edge>& edge, vector<Vertex>& ver, int u)
{
    for (int i = 0; i < edge.size(); i++)
    {
        if (edge[i].u == u)
        {
            if (edge[i].flow == edge[i].capacity)
                continue;
            if (ver[u].h > ver[edge[i].v].h)
            {
                int flow = min(edge[i].capacity - edge[i].flow, ver[u].e);
                ver[u].e -= flow;
                ver[edge[i].v].e += flow;
                edge[i].flow += flow;
                update(edge, i, flow);
                return true;
            }
        }
    }
    return false;
}

void inaltare(vector<Edge>& edge, vector<Vertex>& ver, int u)
{
    int mh = INT_MAX;
    for (int i = 0; i < edge.size(); i++)
    {
        if (edge[i].u == u)
        {
            if (edge[i].flow == edge[i].capacity)
                continue;
            if (ver[edge[i].v].h < mh)
            {
                mh = ver[edge[i].v].h;
                ver[u].h = mh + 1;
            }
        }
    }
}

int pompare_preflux(vector<Edge>& edge, vector<Vertex>& ver, int s, int t)
{
    preflux(edge, ver, s);
    while (overFlowVertex(ver) != -1)
    {
        int u = overFlowVertex(ver);
        if (!pompare(edge, ver, u))
            inaltare(edge, ver, u);
    }
    return ver.back().e;
}

int main()
{
    int V, E, u, v, cantitatea;
    fin >> V >> E;
    vector<Edge> edge;
    vector<Vertex> ver(V);
    for (int i = 0; i < E; i++)
    {
        fin >> u >> v >> cantitatea;
        edge.push_back({ 0, cantitatea, u, v });
    }
    fout << pompare_preflux(edge, ver, 0, V - 1);
    return 0;
}