#include <iostream>
#include <set>
#include <map>
#include <string>
#include <algorithm>

template <typename Node>
class Graph
{
public:
    std::set<Node> getVertexs() const
    {
        std::set<Node> vertexs;
        for (GraphConstIter iter = graph_.begin(); iter != graph_.end(); ++iter) {
            vertexs.insert(iter->first);
        }
        return vertexs;
    }

    void addVertex(const Node& n)
    {
        if (graph_.find(n) == graph_.end()) {
            graph_[n] = std::set<Node>();
        }
    }

    void addEdge(const Node& a, const Node& b)
    {
        addEdgeInternal(a, b);
        addEdgeInternal(b, a);
    }

    std::list<std::list<Node> > findAllPaths(const Node& from, const Node& to)
    {
        std::list<Node> path;
        return findAllPathsInternal(from, to, path);
    }

    std::list<Node> findShortestPath(const Node& from, const Node& to)
    {
        std::list<std::list<Node> > paths = findAllPaths(from, to);
        std::list<Node> shortest;
        for (std::list<std::list<Node> >::iterator iter = paths.begin(); iter != paths.end(); ++iter) {
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
            std::set<Node> e;
            e.insert(b);
            graph_[a] = e;
        }
        else {
            if (graph_[a].find(b) == graph_[a].end()) {
                graph_[a].insert(b);
            }
        }
    }

    std::list<std::list<Node> > findAllPathsInternal(const Node& from, const Node& to, std::list<Node>& path)
    {
        if (graph_.find(from) == graph_.end()) {
            return std::list<Node>();
        }

        if (from == to) {
            std::list<Node> p;
            p.push_back(from);
            return p;
        }

        path.push_back(from);
        std::list<std::list<Node> > paths;
        for (std::list<Node>::iterator iter = graph_[from].begin(); iter != graph_[from].end(); ++iter) {
            if (std::find(path.begin(), path.end(), *iter) == path.end()) {
                std::list<std::list<Node> > newpaths = findAllPathsInternal(*iter, to, path);
                for (std::list<std::list<Node> >::iterator piter = newpaths.begin(); piter != newpaths.end(); ++piter) {
                    newpaths.push_back(newpath);
                }
            }
        }

        return paths;
    }

private:
    typedef std::map<Node, std::vector<Node> > InternalGraph;
    typedef InternalGraph::iterator GraphIter;
    typedef InternalGraph::const_iterator GraphConstIter;
    InternalGraph graph_;
};


void getInput(Graph& g)
{

}

int main(int argc, char* argv[])
{
    return 0;
}
