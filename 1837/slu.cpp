/*
 * [Description]
 *
 * [Input]
 *
 * [Output]
 *
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <cmath>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

// Get a single input from stdin
template<typename T>
static void get_single_input(T& x)
{
    string line;
    getline(cin, line);
    istringstream input(line);
    input >> x;
}

// Get a line input from stdin
// Add the values as elements in Container
template<typename Container>
static void get_inputs(Container& c)
{
    typedef typename Container::value_type T;

    string line;
    while (getline(cin, line)) {
        istringstream input(line);

        T x;
        while (input >> x) {
            c.push_back(x);
        }
    }
}

template <typename Node>
class Graph
{
public:
    typedef set<Node> Vertexs;
    typedef list<Node> Path;
    typedef list<Path> Paths;

    typedef typename Vertexs::iterator VertexsIter;
    typedef typename Vertexs::const_iterator VertexsConstIter;

    typedef typename Paths::iterator PathsIter;
    typedef typename Paths::const_iterator PathsConstIter;

    typedef typename Path::iterator PathIter;
    typedef typename Path::const_iterator PathConstIter;

public:
    Vertexs getVertexs() const
    {
        Vertexs vertexs;
        for (GraphConstIter iter = graph_.cbegin(); iter != graph_.cend(); ++iter) {
            vertexs.insert(iter->first);
        }
        return vertexs;
    }

    void addVertex(const Node& n)
    {
        if (graph_.find(n) == graph_.end()) {
            graph_[n] = Vertexs();
        }
    }

    void addEdge(const Node& a, const Node& b)
    {
        addEdgeInternal(a, b);
        addEdgeInternal(b, a);
    }

    Paths findAllPaths(const Node& from, const Node& to)
    {
        Path path;
        return findAllPathsInternal(from, to, path);
    }

    Path findShortestPath(const Node& from, const Node& to)
    {
        Paths paths = findAllPaths(from, to);
        Path shortest;
        for (PathsIter iter = paths.begin(); iter != paths.end(); ++iter) {
            if (shortest.empty()) {
                shortest = *iter;
            }
            else {
                if (iter->size() < shortest.size()) {
                    shortest = *iter;
                }
            }
        }

        return shortest;
    }

private:
    void addEdgeInternal(const Node& a, const Node& b)
    {
        if (graph_.find(a) == graph_.end()) {
            Vertexs e;
            e.insert(b);
            graph_[a] = e;
        }
        else {
            if (graph_[a].find(b) == graph_[a].end()) {
                graph_[a].insert(b);
            }
        }
    }

    Paths findAllPathsInternal(const Node& from, const Node& to, Path& path)
    {
        if (graph_.find(from) == graph_.end()) {
            return Paths();
        }

        if (from == to) {
            Paths p;
            p.push_back(path);
            return p;
        }

        path.push_back(from);
        Paths paths;
        for (VertexsIter iter = graph_[from].begin(); iter != graph_[from].end(); ++iter) {
            if (find(path.begin(), path.end(), *iter) == path.end()) {
                Paths newpaths = findAllPathsInternal(*iter, to, path);
                for (PathsIter piter = newpaths.begin(); piter != newpaths.end(); ++piter) {
                    newpaths.push_back(*piter);
                }
            }
        }

        return paths;
    }

private:
    typedef map<Node, set<Node> > InternalGraph;

    typedef typename InternalGraph::iterator GraphIter;
    typedef typename InternalGraph::const_iterator GraphConstIter;

private:
    InternalGraph graph_;
};

template <typename Node>
void getInput(Graph<Node>& g)
{
    int n = 0;
    get_single_input(n);
    //cout << "n = " << n << endl;

    if (n <= 0) {
        return;
    }

    while (n-- > 0) {
        string line;
        getline(cin, line);
        //cout << "get line = " << line << endl;

        vector<string> members;
        string name;

        istringstream input(line);
        while (input >> name) {
            //cout << "get name = " << name << endl;
            members.push_back(name);
        }

        assert(members.size() == 3);
        g.addEdge(members[0], members[1]);
        g.addEdge(members[0], members[2]);
        g.addEdge(members[1], members[2]);
    }
}


template <typename Node>
map<Node, int> calc(const Node& champion, Graph<Node>& graph)
{
    map<Node, int> result;
    typename Graph<Node>::Vertexs vertexs = graph.getVertexs();
    for (typename Graph<Node>::VertexsIter it = vertexs.begin(); it != vertexs.end(); ++it) {
        typename Graph<Node>::Path shortest = graph.findShortestPath(champion, *it);
        if (shortest.size() == 0) {
            result[*it] = -1;
        }
        else {
            result[*it] = shortest.size() - 1;
        }
    }
    return result;
}


template <typename Node>
void showResult(const map<Node, int>& result)
{
    size_t n = result.size();
    for (typename map<Node, int>::const_iterator it = result.cbegin(); it != result.cend(); ++it) {
        cout << it->first;
        if (it->second == -1) {
            cout << "undefined";
        }
        else {
            cout << it->second;
        }

        if (n > 1) {
            cout << endl;
        }

        --n;
    }
}

int main(int argc, char* argv[])
{
    Graph<string> graph;
    getInput(graph);
    const string champion = "Isenbaev";
    map<string, int> result = calc(champion, graph);
    showResult(result);

    return 0;
}

