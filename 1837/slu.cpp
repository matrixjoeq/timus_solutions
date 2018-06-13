/*
1837. Isenbaev's Number
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
Vladislav Isenbaev is a two-time champion of Ural, vice champion of TopCoder
Open 2009, and absolute champion of ACM ICPC 2009. In the time you will spend
reading this problem statement Vladislav would have solved a problem. Maybe,
even two…
Since Vladislav Isenbaev graduated from the Specialized Educational and
Scientific Center at Ural State University, many of the former and present
contestants at USU have known him for quite a few years. Some of them are proud
to say that they either played in the same team with him or played in the same
team with one of his teammates…
Let us define Isenbaev's number as follows. This number for Vladislav himself
is 0. For people who played in the same team with him, the number is 1. For
people who weren't his teammates but played in the same team with one or more
of his teammates, the number is 2, and so on. Your task is to automate the
process of calculating Isenbaev's numbers so that each contestant at USU would
know their proximity to the ACM ICPC champion.

[Input]
The first line contains the number of teams n (1 ≤ n ≤ 100). In each of the
following n lines you are given the names of the three members of the corres-
ponding team. The names are separated with a space. Each name is a nonempty
line consisting of English letters, and its length is at most 20 symbols. The
first letter of a name is capital and the other letters are lowercase.

[Output]
For each contestant mentioned in the input data output a line with their name
and Isenbaev's number. If the number is undefined, output “undefined” instead
of it. The contestants must be ordered lexicographically.
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <cmath>

#include <memory>
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
#include <stdexcept>

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

enum NODE_COLOR
{
    COLOR_WHITE,    // never visited
    COLOR_GREY,     // discovered
    COLOR_BLACK     // visit from current node finished
};

template <typename Node>
struct NodeHolder
{
    Node node;
    shared_ptr<NodeHolder> parent;
    NODE_COLOR color;
    int32_t distance;       // used for BFS, recording distance to source
    int32_t discover_time;  // used for DFS, recording time when this node is discovered
    int32_t finish_time;    // used for DFS, recording time when DFS from this node is finished

    NodeHolder()
        : color(COLOR_WHITE)
        , distance(-1)
        , discover_time(-1)
        , finish_time(-1)
    {}

    explicit NodeHolder(const Node& n)
        : node(n)
        , color(COLOR_WHITE)
        , distance(-1)
        , discover_time(-1)
        , finish_time(-1)
    {}

    NodeHolder(const NodeHolder& other)
        : node(other.node)
        , parent(other.parent)
        , color(other.color)
        , distance(other.distance)
        , discover_time(-1)
        , finish_time(-1)
    {}

    void reset()
    {
        parent.reset();
        color = COLOR_WHITE;
        distance = -1;
        discover_time = -1;
        finish_time = -1;
    }

    NodeHolder& operator=(const NodeHolder& other)
    {
        if (this != &other) {
            node = other.node;
            parent = other.parent;
            color = other.color;
            distance = other.distance;
            discover_time = other.discover_time;
            finish_time = other.finish_time;
        }

        return *this;
    }

    bool operator==(const NodeHolder& other) const
    {
        return (node == other.node);
    }

    bool operator<(const NodeHolder& other) const
    {
        return (node < other.node);
    }
};

template <typename Node>
class AdjacentList
{
private:
    typedef shared_ptr<NodeHolder<Node> > _Node;
    typedef set<_Node> NodeList;
    typedef typename NodeList::iterator NodeIter;
    typedef typename NodeList::const_iterator NodeConstIter;
    typedef map<_Node, NodeList> NodeListMap;
    typedef typename NodeListMap::iterator NodeMapIter;
    typedef typename NodeListMap::const_iterator NodeMapConstIter;

public:
    set<shared_ptr<NodeHolder<Node> > > getVertexs() const
    {
        NodeList vertexs;
        for (NodeMapConstIter it = list_.cbegin(); it != list_.cend(); ++it) {
            const _Node& node = it->first;
            if (node) {
                vertexs.insert(node);
            }
        }
        return vertexs;
    }

    shared_ptr<NodeHolder<Node> > addVertex(const Node& n)
    {
        for (NodeMapConstIter it = list_.cbegin(); it != list_.cend(); ++it) {
            const _Node& node = it->first;
            if (node && node->node == n) {
                return node;
            }
        }

        _Node node = make_shared<NodeHolder<Node> >(n);
        if (node) {
            list_[node] = NodeList();
        }
        return node;
    }

    void addEdge(const Node& from, const Node& to)
    {
        _Node _from = addVertex(from);
        _Node _to = addVertex(to);
        if (_from && _to) {
            list_[_from].insert(_to);
        }
    }

    void bfs(const Node& n)
    {
        resetStates();

        _Node node = convertNode(n);
        if (!node) {
            return;
        }

        node->color = COLOR_GREY;
        node->distance = 0;

        queue<_Node> q;
        q.push(node);

        while (!q.empty()) {
            _Node u = q.front();
            q.pop();

            if (!u || list_.find(u) == list_.end()) {
                continue;
            }

            for (NodeIter v = list_[u].begin(); v != list_[u].end(); ++v) {
                const _Node& _v = *v;
                if (!_v) {
                    continue;
                }

                if (_v->color == COLOR_WHITE) {
                    _v->color = COLOR_GREY;
                    _v->distance = u->distance + 1;
                    _v->parent = u;
                    q.push(_v);
                }
            }
            u->color = COLOR_BLACK;
        }
    }

    void dfs()
    {
        resetStates();

        int32_t t = 0;
        for (NodeMapIter x = list_.begin(); x != list_.end(); ++x) {
            const _Node& node = x->first;
            if (!node) {
                continue;
            }

            if (node->color == COLOR_WHITE) {
                dfsVisit(node, t);
            }
        }
    }

    void dfs(const Node& n)
    {
        resetStates();

        _Node node = convertNode(n);
        if (!node) {
            return;
        }

        int32_t t = 0;
        dfsVisit(node, t);
    }

    list<shared_ptr<NodeHolder<Node> > > topologicalSort()
    {
        dfs();
        return topological_list_;
    }

    bool hasLoop()
    {
        dfs();
        return loop_detected_;
    }

    void dump() const
    {
        for (NodeMapConstIter x = list_.cbegin(); x != list_.cend(); ++x) {
            const _Node& n = x->first;
            const NodeList l = x->second;
            if (!n) {
                continue;
            }

            cout << n->node << ": [ ";
            for (NodeConstIter y = l.cbegin(); y != l.cend(); ++y) {
                const _Node& n = *y;
                if (n) {
                    cout << n->node << " ";
                }
            }
            cout << "]\n";
        }
    }

private:
    _Node convertNode(const Node& n)
    {
        _Node _node;
        for (NodeMapIter it = list_.begin(); it != list_.end(); ++it) {
            const _Node& _n = it->first;
            if (!_n && _n->node == n) {
                _node = _n;
                break;
            }
        }
        return _node;
    }

    void resetStates()
    {
        loop_detected_ = false;
        for (NodeMapIter it = list_.begin(); it != list_.end(); ++it) {
            const _Node& _node = it->first;
            if (!_node) {
                continue;
            }

            _node->reset();
        }
    }

    void dfsVisit(const _Node& n, int32_t& t)
    {
        assert(n);

        // node n has just been discovered
        ++t;
        n->discover_time = t;
        n->color = COLOR_GREY;

        // explore edge (n, v)
        for (NodeIter x = list_[n].begin(); x != list_[n].end(); ++x) {
            const _Node& node = *x;
            if (node->color == COLOR_WHITE) {
                node->parent = n;
                dfsVisit(node, t);
            }
            else if (node->color == COLOR_GREY) {
                loop_detected_ = true;
            }
        }

        // blacken n, it is finished
        n->color = COLOR_BLACK;
        ++t;
        n->finish_time = t;

        // insert n at the front of topological list
        topological_list_.insert(topological_list_.begin(), n);
    }

private:
    NodeListMap list_;
    bool loop_detected_;
    list<_Node> topological_list_;
};

class IllegalOperation : public runtime_error
{
public:
    explicit IllegalOperation(const string& msg)
        : runtime_error(msg)
    {}
};

template <typename Node, class Impl = AdjacentList<Node> >
class Graph
{
public:
    explicit Graph(bool directed = true)
        : directed_(directed)
    {}

    set<shared_ptr<NodeHolder<Node> > > getVertexs() const
    {
        return graph_.getVertexs();
    }

    shared_ptr<NodeHolder<Node> > addVertex(const Node& n)
    {
        return graph_.addVertex(n);
    }

    void addEdge(const Node& from, const Node& to)
    {
        graph_.addEdge(from, to);
        if (!directed_) {
            graph_.addEdge(to, from);
        }
    }

    void bfs(const Node& n)
    {
        graph_.bfs(n);
    }

    void dfs()
    {
        graph_.dfs();
    }

    void dfs(const Node& n)
    {
        graph_.dfs(n);
    }

    bool hasLoop()
    {
        return graph_.hasLoop();
    }

    list<shared_ptr<NodeHolder<Node> > > topologicalSort()
    {
        if (!directed_ || graph_.hasLoop()) {
            throw IllegalOperation("Topological sort can only be used on a directed non-loop graph");
        }
        return graph_.topologicalSort();
    }

    void dump() const
    {
        graph_.dump();
    }

private:
    Impl graph_;
    bool directed_;
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

    g.dump();
}

template <typename Node>
map<Node, int> calc(const Node& champion, Graph<Node>& graph)
{
    map<Node, int> result;
    graph.bfs(champion);

    set<shared_ptr<NodeHolder<Node> > > vertexs = graph.getVertexs();
    for (auto it = vertexs.begin(); it != vertexs.end(); ++it) {
        result[(*it)->node] = (*it)->distance;
    }

    return result;
}

template <typename Node>
void showResult(const map<Node, int>& result)
{
    size_t n = result.size();
    for (typename map<Node, int>::const_iterator it = result.cbegin(); it != result.cend(); ++it) {
        cout << it->first << ' ';
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
    Graph<string> graph(false /* directed */);
    getInput(graph);
    /*
    const string champion = "Isenbaev";
    map<string, int> result = calc(champion, graph);
    showResult(result);
    */

    try {
        list<shared_ptr<NodeHolder<string> > > topological_list = graph.topologicalSort();
        for (auto it = topological_list.begin(); it != topological_list.end(); ++it) {
            cout << (*it)->node << " [ " << (*it)->discover_time << ", " << (*it)->finish_time << " ] \n";
        }
    }
    catch (const IllegalOperation& e) {
        cout << e.what() << endl;
    }

    return 0;
}

