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

enum NODE_COLOR {
    COLOR_WHITE,
    COLOR_GREY,
    COLOR_BLACK
};

template <typename Node>
struct NodeHolder
{
    Node node;
    NODE_COLOR color;
    int32_t distance;
    //shared_ptr<NodeHolder> parent;

    NodeHolder()
        : color(COLOR_WHITE)
        , distance(-1)
        //, parent()
    {}

    explicit NodeHolder(const Node& n)
        : node(n)
        , color(COLOR_WHITE)
        , distance(-1)
        //, parent()
    {}

    NodeHolder(const NodeHolder& other)
        : node(other.node)
        , color(other.color)
        , distance(other.distance)
        //, parent(other.parent)
    {}

    NodeHolder& operator=(const NodeHolder& other)
    {
        if (this != &other) {
            node = other.node;
            color = other.color;
            distance = other.distance;
            //parent = other.parent;
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
        _Node node = reset(n);
        if (!node) return;

        queue<_Node> q;
        q.push(node);

        while (!q.empty()) {
            _Node u = q.front();
            q.pop();

            if (!u || list_.find(u) == list_.end()) continue;

            for (NodeIter v = list_[u].begin(); v != list_[u].end(); ++v) {
                const _Node& _v = *v;
                if (!_v) continue;

                if (_v->color == COLOR_WHITE) {
                    _v->color = COLOR_GREY;
                    _v->distance = u->distance + 1;
                    //_v->parent = u;
                    q.push(_v);
                }
            }
            u->color = COLOR_BLACK;
        }
    }

    void dump() const
    {
        for (NodeMapConstIter x = list_.cbegin(); x != list_.cend(); ++x) {
            const _Node& n = x->first;
            if (!n) continue;

            cout << n->node << ": [ ";
            for (NodeConstIter y = x->second.cbegin(); y != x->second.cend(); ++y) {
                if (*y) {
                    cout << (*y)->node << " ";
                }
            }
            cout << "]\n";
        }
    }

private:
    _Node reset(const Node& n)
    {
        _Node node;
        for (NodeMapIter it = list_.begin(); it != list_.end(); ++it) {
            const _Node& _node = it->first;
            if (!_node) continue;

            if (_node->node == n) {
                _node->color = COLOR_GREY;
                _node->distance = 0;
                node = _node;
            }
            else {
                _node->color = COLOR_WHITE;
                _node->distance = -1;
            }
            //_node->parent.reset();
        }
        return node;
    }

private:
    NodeListMap list_;
};

#if 0
template <typename Node>
class AdjacentMatrix
{
public:
    explicit AdjacentMatrix(uint32_t node_count = 0)
        : id_generator_(0)
        , matrix_(node_count)
    {
        if (node_count <= 0) {
            return;
        }

        for (NodeArrayIter it = matrix_.begin(); it != matrix_.end(); ++it) {
            NodeArray& node_array = *it;
            node_array.resize(node_count);
        }
    }

    void add_node(const Node& node)
    {

    }

private:
    typedef std::vector<Node> NodeArray;
    typedef std::vector<NodeArray> NodeMatrix;
    typedef std::map<uint32_t, Node> NodeIdMap;

    typedef typename NodeArray::iterator NodeArrayIter;
    typedef typename NodeMatrix::iterator NodeMatrixIter;
    typedef typename NodeIdMap::iterator NodeIdMapIter;

    uint32_t id_generator_;
    NodeIdMap id_map_;
    NodeMatrix matrix_;
};
#endif

template <typename Node, class Impl = AdjacentList<Node> >
class UndirectedGraph
{
public:
    set<shared_ptr<NodeHolder<Node> > > getVertexs() const
    {
        return graph_.getVertexs();
    }

    shared_ptr<NodeHolder<Node> > addVertex(const Node& n)
    {
        return graph_.addVertex(n);
    }

    void addEdge(const Node& x, const Node& y)
    {
        graph_.addEdge(x, y);
        graph_.addEdge(y, x);
    }

    void bfs(const Node& n)
    {
        graph_.bfs(n);
    }

    void dump() const
    {
        graph_.dump();
    }

private:
    Impl graph_;
};

template <typename Node>
void getInput(UndirectedGraph<Node>& g)
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

    //g.dump();
}

template <typename Node>
map<Node, int> calc(const Node& champion, UndirectedGraph<Node>& graph)
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
    UndirectedGraph<string> graph;
    getInput(graph);
    const string champion = "Isenbaev";
    map<string, int> result = calc(champion, graph);
    showResult(result);

    return 0;
}

