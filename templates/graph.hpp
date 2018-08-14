
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

enum class NodeColor
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
    NodeColor color;
    int32_t distance;       // used for BFS, recording distance to source; used for shortest path upper limit estimation
    int32_t discover_time;  // used for DFS, recording time when this node is discovered
    int32_t finish_time;    // used for DFS, recording time when DFS from this node is finished

    NodeHolder()
        : color(NodeColor::COLOR_WHITE)
        , distance(n_infinity)
        , discover_time(-1)
        , finish_time(-1)
    {}

    explicit NodeHolder(const Node& n)
        : node(n)
        , color(NodeColor::COLOR_WHITE)
        , distance(n_infinity)
        , discover_time(-1)
        , finish_time(-1)
    {}

    void reset()
    {
        parent.reset();
        color = NodeColor::COLOR_WHITE;
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
    using _Node = shared_ptr<NodeHolder<Node>>;
    using _WeightedNode = WeightedNode<NodeHolder<Node>>;
    using NodeList = set<_WeightedNode>;
    using NodeListMap = map<_Node, NodeList>;

public:
    set<shared_ptr<NodeHolder<Node>>> getVertices() const
    {
        set<shared_ptr<NodeHolder<Node>>> vertices;
        for_each(list_.begin(), list_.end(), [&vertices](const pair<_Node, NodeList>& p){
            const auto& node = p.first;
            if (node) {
                vertices.insert(node);
            }
        });
        return vertices;
    }

    shared_ptr<NodeHolder<Node>> addVertex(const Node& n)
    {
        auto found = find_if(list_.begin(), list_.end(), [&n](const pair<_Node, NodeList>& p){
            const auto& node = p.first;
            return (node && node->node == n);
        });

        if (found != list_.end()) {
            return found->first;
        }

        auto node = make_shared<NodeHolder<Node>>(n);
        if (node) {
            list_[node] = NodeList();
        }
        return node;
    }

    void addEdge(const Node& from, const Node& to, int32_t weight = 1)
    {
        auto _from = addVertex(from);
        auto _to = addVertex(to);
        if (_from && _to) {
            _WeightedNode _weighted(_to, weight);
            list_[_from].insert(_weighted);
        }
    }

    /**
     * @brief BFS
     *
     * BFS(G, s)
     *   for each vertex u in G.V - {s}
     *     u.color = WHITE
     *     u.distance = infinite
     *     u.parent = NULL
     *   s.color = GREY
     *   s.distance = 0
     *   s.parent = NULL
     *   Q = {}
     *   ENQUEUE(Q, s)
     *   while Q != {}
     *     u = DEQUEUE(Q)
     *     for each v in G.Adj[u]
     *       if v.color == WHITE
     *         v.color = GREY
     *         v.distance = u.distance + weight(u, v)
     *         v.parent = u
     *         ENQUEUE(Q, v)
     *     u.color = BLACK
     */
    void bfs(const Node& source)
    {
        resetStates();

        auto s = convertNode(source);
        if (!s) {
            return;
        }

        s->color = NodeColor::COLOR_GREY;
        s->distance = 0;

        queue<_Node> q;
        q.push(s);

        while (!q.empty()) {
            auto u = q.front();
            q.pop();

            if (!u || list_.find(u) == list_.end()) {
                continue;
            }

            for_each(list_[u].begin(), list_[u].end(), [&u, &q](const _WeightedNode& w) {
                const auto& n = w.node;
                if (n && n->color == NodeColor::COLOR_WHITE) {
                    n->color = NodeColor::COLOR_GREY;
                    n->distance = u->distance + w.weight;
                    n->parent = u;
                    q.push(n);
                }
            });
            u->color = NodeColor::COLOR_BLACK;
        }
    }

    /**
     * @brief DFS
     *
     * DFS(G)
     *   for each vertex u in G.V
     *     u.color = WHITE
     *     u.parent = NULL
     *   time = 0
     *   for each vertex u in G.V
     *     if u.color == WHITE
     *       DFS-VISIT(G, u)
     */
    void dfs()
    {
        resetStates();

        int32_t t = 0;
        for_each(list_.begin(), list_.end(), [&t, this](const pair<_Node, NodeList>& p){
            const auto& node = p.first;
            if (node && node->color == NodeColor::COLOR_WHITE) {
                dfsVisit(node, t);
            }
        });
    }

    void dfs(const Node& source)
    {
        resetStates();

        auto s = convertNode(source);
        if (!s) {
            return;
        }

        int32_t t = 0;
        dfsVisit(s, t);
    }

    list<shared_ptr<NodeHolder<Node>>> topologicalSort()
    {
        dfs();
        return topological_list_;
    }

    bool hasLoop()
    {
        dfs();
        return loop_detected_;
    }

    /**
     * @brief Bellman-Ford
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
        auto s = convertNode(source);
        if (!s) {
            return false;
        }

        initializeSingleSource(s);
        for (auto i = list_.size(); i > 1; --i) {
            for_each(list_.begin(), list_.end(), [this](const pair<_Node, NodeList>& p){
                const auto& u = p.first;
                const auto& l = p.second;
                if (u) {
                    for_each(l.begin(), l.end(), [&u, this](const _WeightedNode& v){ relax(u, v); });
                }
            });
        }

        for_each(list_.begin(), list_.end(), [](const pair<_Node, NodeList>& p){
            const auto& u = p.first;
            const auto& l = p.second;
            if (u) {
                for_each(l.begin(), l.end(), [&u](const _WeightedNode& w){
                    const auto& v = w.node;
                    if (v) {
                        if ((u->distance != n_infinity) && (v->distance > (u->distance + w.weight))) {
                            return false;
                        }
                    }
                });
            }
        });

        return true;
    }

    /**
     * @brief DAG-SHORTEST-PATHS
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
        auto s = convertNode(source);
        if (!s) {
            return;
        }

        auto vertices = topologicalSort();
        initializeSingleSource(s);

        for_each(vertices.begin(), vertices.end(), [this](const _Node& u){
            if (u && list_.find(u) != list_.end()) {
                for_each(list_[u].begin(), list_[u].end(), [&u, this](const _WeightedNode& v){ relax(u, v); });
            }
        });
    }

    /**
     * @brief Dijkstra
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
        auto s = convertNode(source);
        if (!s) {
            return;
        }

        initializeSingleSource(s);

        list<_Node> q;
        for_each(list_.begin(), list_.end(), [&q](const pair<_Node, NodeList>& p){
            const _Node& u = p.first;
            if (u) {
                q.push_back(u);
            }
        });

        while (!q.empty()) {
            q.sort([](const _Node& lhs, const _Node& rhs){
                assert(lhs);
                assert(rhs);
                return (lhs->distance < rhs->distance);
            });

            const auto& u = q.front();
            assert(u);

            for_each(list_[u].begin(), list_[u].end(), [&u, this](const _WeightedNode& v){ relax(u, v); });

            q.pop_front();
        }
    }

    void dump() const
    {
        for_each(list_.begin(), list_.end(), [](const pair<_Node, NodeList>& p){
            const auto& n = p.first;
            const auto& l = p.second;
            if (n) {
                cout << n->node << ": [ ";
                for_each(l.begin(), l.end(), [](const _WeightedNode& n){
                    if (n.node) {
                        cout << (n.node)->node << " ";
                    }
                });
                cout << "]\n";
            }
        });
    }

private:
    _Node convertNode(const Node& n)
    {
        auto found = find_if(list_.begin(), list_.end(), [&n](const pair<_Node, NodeList>& p){ return (p.first && (p.first)->node == n); });
        return (found == list_.end() ? _Node() : found->first);
    }

    void resetStates()
    {
        loop_detected_ = false;
        for_each(list_.begin(), list_.end(), [](const pair<_Node, NodeList>& p){
            const _Node& n = p.first;
            if (n) {
                n->reset();
            }
        });
    }

    /**
     * @brief DFS-VISIT
     *
     * DFS-VISIT(G, u)
     *   time = time + 1            // white vertex u has just been discovered
     *   u.discover_time = time
     *   u.color = GREY
     *   for each v in G.Adj[u]     // explore edge (u, v)
     *     if v.color == WHITE
     *       v.parent = u
     *       DFS-VISIT(G, v)
     *  u.color = BLACK             // blacken u, it is finished
     *  time = time + 1
     *  u.finish_time = time
     */
    void dfsVisit(const _Node& n, int32_t& t)
    {
        if (!n || list_.find(n) == list_.end()) {
            return;
        }

        // node n has just been discovered
        ++t;
        n->discover_time = t;
        n->color = NodeColor::COLOR_GREY;

        // explore edge (n, v)
        for_each(list_[n].begin(), list_[n].end(), [&n, &t, this](const _WeightedNode& w){
            const _Node& node = w.node;
            if (node) {
                if (node->color == NodeColor::COLOR_WHITE) {
                    node->parent = n;
                    dfsVisit(node, t);
                }
                else if (node->color == NodeColor::COLOR_GREY) {
                    loop_detected_ = true;
                }
            }
        });

        // blacken n, it is finished
        n->color = NodeColor::COLOR_BLACK;
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

    /**
     * @brief RELAX operation
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

template <typename Node, class Impl = AdjacentList<Node>>
class Graph
{
public:
    explicit Graph(bool directed = true)
        : directed_(directed)
    {}

    set<shared_ptr<NodeHolder<Node>>> getVertices() const
    {
        return graph_.getVertices();
    }

    shared_ptr<NodeHolder<Node>> addVertex(const Node& n)
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

    list<shared_ptr<NodeHolder<Node>>> topologicalSort()
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