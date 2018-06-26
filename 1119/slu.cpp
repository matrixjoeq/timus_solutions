/*
1119. Metro
Time limit: 0.5 second
Memory limit: 64 MB

[Description]
Many of SKB Kontur programmers like to get to work by Metro because the main
office is situated quite close the station Uralmash. So, since a sedentary
life requires active exercises off-duty, many of the staff — Nikifor among
them — walk from their homes to Metro stations on foot.
Nikifor lives in a part of our city where streets form a grid of residential
quarters. All the quarters are squares with side 100 meters. A Metro entrance
is situated at one of the crossroads. Nikifor starts his way from another
crossroad which is south and west of the Metro entrance. Naturally, Nikifor,
starting from his home, walks along the streets leading either to the north or
to the east. On his way he may cross some quarters diagonally from their south-
western corners to the north-eastern ones. Thus, some of the routes are shorter
than others. Nikifor wonders, how long is the shortest route.
You are to write a program that will calculate the length of the shortest route
from the south-western corner of the grid to the north-eastern one.

[Input]
There are two integers in the first line: N and M (0 < N,M ≤ 1000) — west-east
and south-north sizes of the grid. Nikifor starts his way from a crossroad which
is situated south-west of the quarter with coordinates (1, 1). A Metro station
is situated north-east of the quarter with coordinates (N, M). The second input
line contains a number K (0 ≤ K ≤ 100) which is a number of quarters that can
be crossed diagonally. Then K lines with pairs of numbers separated with a space
follow — these are the coordinates of those quarters.

[Output]
Your program is to output a length of the shortest route from Nikifor's home to
the Metro station in meters, rounded to the integer amount of meters.
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cmath>

#include <limits>
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

// Get a single line input from stdin
// Add the values as elements in Container
template <typename Container>
static void get_single_line(Container& c)
{
    typedef typename Container::value_type T;

    string line;
    getline(cin, line);
    istringstream input(line);
    T x;
    while (input >> x) {
        c.push_back(x);
    }
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

static const double __INFINITY__ = numeric_limits<double>::max();

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
    double distance;       // used for BFS, recording distance to source; used for shortest path upper limit estimation
    int32_t discover_time;  // used for DFS, recording time when this node is discovered
    int32_t finish_time;    // used for DFS, recording time when DFS from this node is finished

    NodeHolder()
        : color(COLOR_WHITE)
        , distance(__INFINITY__)
        , discover_time(-1)
        , finish_time(-1)
    {}

    explicit NodeHolder(const Node& n)
        : node(n)
        , color(COLOR_WHITE)
        , distance(__INFINITY__)
        , discover_time(-1)
        , finish_time(-1)
    {}

    void reset()
    {
        parent.reset();
        color = COLOR_WHITE;
        distance = __INFINITY__;
        discover_time = -1;
        finish_time = -1;
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

template <class NodeHolder>
struct WeightedNode
{
    shared_ptr<NodeHolder> node;
    double weight;

    WeightedNode()
        : node()
        , weight(1.0f)
    {}

    explicit WeightedNode(shared_ptr<NodeHolder> n, double w = 1.0f)
        : node(n)
        , weight(w)
    {}

    bool operator==(const WeightedNode& other) const
    {
        return (node == other.node && weight = other.weight);
    }

    bool operator<(const WeightedNode& other) const
    {
        if (!node && !(other.node)) {
            return (weight < other.weight);
        }
        else if (!node && other.node) {
            return true;
        }
        else if (node && !(other.node)) {
            return false;
        }
        else {
            return (*node < *(other.node));
        }
    }
};

template <typename Node>
class AdjacentList
{
private:
    typedef shared_ptr<NodeHolder<Node> > _Node;
    typedef WeightedNode<NodeHolder<Node> > _WeightedNode;
    typedef set<_WeightedNode> NodeList;
    typedef typename NodeList::iterator NodeIter;
    typedef typename NodeList::const_iterator NodeConstIter;
    typedef map<_Node, NodeList> NodeListMap;
    typedef typename NodeListMap::iterator NodeMapIter;
    typedef typename NodeListMap::const_iterator NodeMapConstIter;

private:
    template <typename _Node>
    struct NodeLess
    {
        bool operator()(const _Node& lhs, const _Node& rhs) const
        {
            assert(lhs);
            assert(rhs);
            return (lhs->distance < rhs->distance);
        }
    };

public:
    set<shared_ptr<NodeHolder<Node> > > getVertices() const
    {
        set<shared_ptr<NodeHolder<Node> > > vertices;
        for (NodeMapConstIter it = list_.cbegin(); it != list_.cend(); ++it) {
            const _Node& node = it->first;
            if (node) {
                vertices.insert(node);
            }
        }
        return vertices;
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

    void addEdge(const Node& from, const Node& to, double weight = 1.0f)
    {
        _Node _from = addVertex(from);
        _Node _to = addVertex(to);
        if (_from && _to) {
            _WeightedNode _weighted(_to, weight);
            list_[_from].insert(_weighted);
        }
    }

    void bfs(const Node& source)
    {
        resetStates();

        _Node s = convertNode(source);
        if (!s) {
            return;
        }

        s->color = COLOR_GREY;
        s->distance = 0.0f;

        queue<_Node> q;
        q.push(s);

        while (!q.empty()) {
            _Node u = q.front();
            q.pop();

            if (!u || list_.find(u) == list_.end()) {
                continue;
            }

            for (NodeIter v = list_[u].begin(); v != list_[u].end(); ++v) {
                const _WeightedNode& _v = *v;
                const _Node& n = _v.node;
                if (!n) {
                    continue;
                }

                if (n->color == COLOR_WHITE) {
                    n->color = COLOR_GREY;
                    n->distance = u->distance + _v.weight;
                    n->parent = u;
                    q.push(n);
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

    void dfs(const Node& source)
    {
        resetStates();

        _Node s = convertNode(source);
        if (!s) {
            return;
        }

        int32_t t = 0;
        dfsVisit(s, t);
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

    /* @brief Bellman-Ford
     *
     * BELLMAN-FORD(G, w, s)
     *   INITIALIZE-SINGLE-SOURCE(G, s)
     *   for i = 1 to |G.V| - 1
     *     for each edge(u, v) in G.E
     *       RELAX(u, v, w)
     *   for each edge(u, v) in G.E
     *     if v.d > u.d + w(u, v)
     *       return FALSE
     *   return TRUE
     */
    bool bellmanFord(const Node& source)
    {
        _Node s = convertNode(source);
        if (!s) {
            return false;
        }

        initializeSingleSource(s);
        for (typename NodeListMap::size_type i = 1; i < list_.size(); ++i) {
            for (NodeMapIter x = list_.begin(); x != list_.end(); ++x) {
                const _Node& u = x->first;
                if (!u) {
                    continue;
                }

                for (NodeIter y = x->second.begin(); y != x->second.end(); ++y) {
                    const _WeightedNode& v = *y;
                    relax(u, v);
                }
            }
        }

        for (NodeMapIter x = list_.begin(); x != list_.end(); ++x) {
            const _Node& u = x->first;
            if (!u) {
                continue;
            }

            for (NodeIter y = x->second.begin(); y != x->second.end(); ++y) {
                const _WeightedNode& v = *y;
                const _Node& _v = v.node;
                if (!_v) {
                    continue;
                }

                if ((u->distance != __INFINITY__) && (_v->distance > (u->distance + v.weight))) {
                    return false;
                }
            }
        }

        return true;
    }

    /* @brief DAG-SHORTEST-PATHS
     *
     * DAG-SHORTEST-PATHS(G, w, s)
     *   topologically sort the vertices of G
     *   INITIALIZE-SINGLE-SOURCE(G, s)
     *   for each vertex u, taken in topologically sorted order
     *     for each vertex v in G.Adj[u]
     *       RELAX(u, v, w)
     */
    void dagShortestPaths(const Node& source)
    {
        _Node s = convertNode(source);
        if (!s) {
            return;
        }

        list<_Node> vertices = topologicalSort();
        initializeSingleSource(s);
        for (typename list<_Node>::iterator x = vertices.begin(); x != vertices.end(); ++x) {
            const _Node& u = *x;
            if (!u || list_.find(u) == list_.end()) {
                continue;
            }

            for (NodeIter y = list_[u].begin(); y != list_[u].end(); ++y) {
                const _WeightedNode& v = *y;
                relax(u, v);
            }
        }
    }

    /* @brief Dijkstra
     *
     * DIJKSTRA(G, w, s)
     *   INITIALIZE-SINGLE-SOURCE(G, s)
     *   S = {}
     *   Q = G.V
     *   while Q != {}
     *     u = EXTRACT-MIN(Q)
     *     S = S U {u}
     *     for each vertex v in G.Adj[u]
     *       RELAX(u, v, w)
     */
    void dijkstra(const Node& source)
    {
        _Node s = convertNode(source);
        if (!s) {
            return;
        }

        initializeSingleSource(s);
        list<_Node> q;
        for (NodeMapIter x = list_.begin(); x != list_.end(); ++x) {
            const _Node& u = x->first;
            if (!u) {
                continue;
            }

            q.push_back(u);
        }

        NodeLess<_Node> compare;
        while (!q.empty()) {
            q.sort(compare);
            const _Node& u = q.front();
            assert(u);
            for (NodeIter x = list_[u].begin(); x != list_[u].end(); ++x) {
                const _WeightedNode& v = *x;
                relax(u, v);
            }
            q.pop_front();
        }
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
                const _WeightedNode& n = *y;
                if (n.node) {
                    cout << (n.node)->node << " ";
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
            if (_n && _n->node == n) {
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
        if (!n || list_.find(n) == list_.end()) {
            return;
        }

        // node n has just been discovered
        ++t;
        n->discover_time = t;
        n->color = COLOR_GREY;

        // explore edge (n, v)
        for (NodeIter x = list_[n].begin(); x != list_[n].end(); ++x) {
            const _WeightedNode& weighted_node = *x;
            const _Node& node = weighted_node.node;
            if (!node) {
                continue;
            }

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

    void initializeSingleSource(const _Node& source)
    {
        resetStates();
        if (source) {
            source->distance = 0.0;
        }
    }

    /* @brief RELAX operation
     *
     * RELAX(u, v, w)
     *   if v.d > u.d + w(u, v)
     *     v.d = u.d + w(u, v)
     *     v.p = u
     */
    void relax(const _Node& u, const _WeightedNode& v)
    {
        if (!u || !(v.node) || list_.find(u) == list_.end()) {
            return;
        }

        if ((v.weight == __INFINITY__) || (u->distance == __INFINITY__)) {
            // w = w(u, v), (u, v) must in G.E
            // AND
            // v.d can never be greater than infinity
            return;
        }

        // TODO: what if u.d + w > __INFINITY__
        if ((v.node)->distance > (u->distance + v.weight)) {
            (v.node)->distance = u->distance + v.weight;
            (v.node)->parent = u;
        }
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

    set<shared_ptr<NodeHolder<Node> > > getVertices() const
    {
        return graph_.getVertices();
    }

    shared_ptr<NodeHolder<Node> > addVertex(const Node& n)
    {
        return graph_.addVertex(n);
    }

    void addEdge(const Node& from, const Node& to, double weight = 1.0f)
    {
        graph_.addEdge(from, to, weight);
        if (!directed_) {
            graph_.addEdge(to, from, weight);
        }
    }

    void bfs(const Node& source)
    {
        graph_.bfs(source);
    }

    void dfs()
    {
        graph_.dfs();
    }

    void dfs(const Node& source)
    {
        graph_.dfs(source);
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

    bool bellmanFord(const Node& source)
    {
        return graph_.bellmanFord(source);
    }

    void dagShortestPaths(const Node& source)
    {
        return graph_.dagShortestPaths(source);
    }

    void dijkstra(const Node& source)
    {
        return graph_.dijkstra(source);
    }

    void dump() const
    {
        graph_.dump();
    }

private:
    Impl graph_;
    bool directed_;
};

struct Point
{
    uint32_t x;
    uint32_t y;

    Point() : x(0), y(0) {}
    Point(uint32_t pos_x, uint32_t pos_y) : x(pos_x), y(pos_y) {}

    bool operator==(const Point& other) const
    {
        return (x == other.x && y == other.y);
    }

    bool operator<(const Point& other) const
    {
        return (x < other.x || y < other.y);
    }

    friend ostream& operator<<(ostream& os, const Point& p);
};

ostream& operator<< (ostream& os, const Point& p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

template <typename Graph>
void getInput(Graph& g, uint32_t& n, uint32_t& m)
{
    vector<uint32_t> dimension;
    get_single_line(dimension);
    assert(dimension.size() == 2);

    n = dimension[0];
    m = dimension[1];
    assert(n > 0 && n <= 1000);
    assert(m > 0 && m <= 1000);
    //cout << "n = " << n << ", m = " << m << endl;

    // Add horizontal edges
    for (uint32_t _n = 0; _n < n; ++_n) {
        for (uint32_t _m = 0; _m <= m; ++_m) {
            Point u(_n, _m);
            Point v(_n + 1, _m);
            g.addEdge(u, v);
        }
    }

    // Add vertical edges
    for (uint32_t _m = 0; _m < m; ++_m) {
        for (uint32_t _n = 0; _n <= n; ++_n) {
            Point u(_n, _m);
            Point v(_n, _m + 1);
            g.addEdge(u, v);
        }
    }

    int32_t k = 0;
    get_single_input(k);
    assert(k >= 0 && k <= 100);

    const double w = sqrt(pow(1, 2) + pow(1, 2));
    while (k-- > 0) {
        string line;
        getline(cin, line);
        //cout << "get line = " << line << endl;

        istringstream input(line);
        uint32_t x = 0, y = 0;
        input >> x;
        input >> y;
        assert(x > 0 && x <= n && y > 0 && y <= m);
        Point u(x - 1, y - 1);
        Point v(x, y);
        g.addEdge(u, v, w);
    }

    //g.dump();
}

template <typename Node>
uint32_t calc(Graph<Node>& graph, uint32_t n, uint32_t m)
{
    uint32_t result = 0;
    Point origin(0, 0);
    graph.dijkstra(origin);

    Point destination(n, m);
    set<shared_ptr<NodeHolder<Node> > > vertices = graph.getVertices();
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        NodeHolder<Node>& node = *(*it);
        if (node.node == destination) {
            result = static_cast<uint32_t>(round(node.distance * 100.0f));
            break;
        }
    }

    return result;
}

int main(int argc, char* argv[])
{
    uint32_t n = 0, m = 0;
    Graph<Point> graph;
    getInput(graph, n, m);
    uint32_t r = calc(graph, n, m);
    cout << r;
    return 0;
}

