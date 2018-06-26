
#ifndef __graph_hpp_
#define __graph_hpp_

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

static const int32_t n_infinity = numeric_limits<int32_t>::max();

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
    int32_t distance;       // used for BFS, recording distance to source; used for shortest path upper limit estimation
    int32_t discover_time;  // used for DFS, recording time when this node is discovered
    int32_t finish_time;    // used for DFS, recording time when DFS from this node is finished

    NodeHolder()
        : color(COLOR_WHITE)
        , distance(n_infinity)
        , discover_time(-1)
        , finish_time(-1)
    {}

    explicit NodeHolder(const Node& n)
        : node(n)
        , color(COLOR_WHITE)
        , distance(n_infinity)
        , discover_time(-1)
        , finish_time(-1)
    {}

    void reset()
    {
        parent.reset();
        color = COLOR_WHITE;
        distance = n_infinity;
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
    int32_t weight;

    WeightedNode()
        : node()
        , weight(1)
    {}

    explicit WeightedNode(shared_ptr<NodeHolder> n, int32_t w = 1)
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

    void addEdge(const Node& from, const Node& to, int32_t weight = 1)
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
        s->distance = 0;

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

                if ((u->distance != n_infinity) && (_v->distance > (u->distance + v.weight))) {
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
            source->distance = 0;
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

        if ((v.weight == n_infinity) || (u->distance == n_infinity)) {
            // w = w(u, v), (u, v) must in G.E
            // AND
            // v.d can never be greater than infinity
            return;
        }

        // TODO: what if u.d + w > n_infinity
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

    void addEdge(const Node& from, const Node& to, int32_t weight = 1)
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

#endif // __graph_hpp__