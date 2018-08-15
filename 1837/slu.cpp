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

// Get a line input from stdin
// Add the values as elements in Container
template<typename Container>
static void get_inputs(Container& c)
{
    using T = typename Container::value_type;

    string line;
    while (getline(cin, line)) {
        istringstream input(line);

        T x;
        while (input >> x) {
            c.push_back(x);
        }
    }
}

static const int32_t k_infinity = numeric_limits<int32_t>::max();

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
        , distance(k_infinity)
        , discover_time(-1)
        , finish_time(-1)
    {}

    explicit NodeHolder(const Node& n)
        : node(n)
        , color(NodeColor::COLOR_WHITE)
        , distance(k_infinity)
        , discover_time(-1)
        , finish_time(-1)
    {}

    void reset()
    {
        parent.reset();
        color = NodeColor::COLOR_WHITE;
        distance = k_infinity;
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

template <class NodeHolder, typename Weight = int32_t>
struct WeightedNode
{
    shared_ptr<NodeHolder> node;
    Weight weight;

    WeightedNode()
        : node()
        , weight(static_cast<Weight>(1))
    {}

    explicit WeightedNode(shared_ptr<NodeHolder> n, Weight w = static_cast<Weight>(1))
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

template <typename Node, typename Weight = int32_t>
class AdjacentList
{
private:
    using _Node = shared_ptr<NodeHolder<Node>>;
    using _WeightedNode = WeightedNode<NodeHolder<Node>>;
    using WeightedNodeList = set<_WeightedNode>;
    using WeightedAdjacentList = map<_Node, WeightedNodeList>;
    using WeightedRow = pair<_Node, WeightedNodeList>;

private:
    static inline auto rowHead(const WeightedRow& row) -> decltype(row.first)
    {
        return row.first;
    }

    static inline auto rowTail(const WeightedRow& row) -> decltype(row.second)
    {
        return row.second;
    }

public:
    set<shared_ptr<NodeHolder<Node>>> getVertices() const
    {
        set<shared_ptr<NodeHolder<Node>>> vertices;
        for_each(adj_list_.begin(), adj_list_.end(), [&vertices](const WeightedRow& row){
            const auto& node = rowHead(row);
            if (node) {
                vertices.insert(node);
            }
        });
        return vertices;
    }

    shared_ptr<NodeHolder<Node>> addVertex(const Node& n)
    {
        auto found = find_if(adj_list_.begin(), adj_list_.end(), [&n](const WeightedRow& row){
            const auto& node = rowHead(row);
            return (node && node->node == n);
        });

        if (found != adj_list_.end()) {
            return found->first;
        }

        auto node = make_shared<NodeHolder<Node>>(n);
        if (node) {
            adj_list_[node] = WeightedNodeList();
        }

        return node;
    }

    void addEdge(const Node& from, const Node& to, Weight weight = static_cast<Weight>(1))
    {
        auto _from = addVertex(from);
        auto _to = addVertex(to);
        if (_from && _to) {
            _WeightedNode _weighted(_to, weight);
            adj_list_[_from].insert(_weighted);
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
            const auto& u = q.front();

            if (!u || adj_list_.find(u) == adj_list_.end()) {
                q.pop();
                continue;
            }

            for_each(adj_list_[u].begin(), adj_list_[u].end(), [&u, &q](const _WeightedNode& w) {
                const auto& n = w.node;
                if (n && n->color == NodeColor::COLOR_WHITE) {
                    n->color = NodeColor::COLOR_GREY;
                    n->distance = u->distance + w.weight;
                    n->parent = u;
                    q.push(n);
                }
            });
            u->color = NodeColor::COLOR_BLACK;
            q.pop();
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
        for_each(adj_list_.begin(), adj_list_.end(), [&t, this](const WeightedRow& row){
            const auto& node = rowHead(row);
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
        for (auto i = adj_list_.size(); i > 1; --i) {
            for_each(adj_list_.begin(), adj_list_.end(), [this](const WeightedRow& row){
                const auto& u = rowHead(row);
                const auto& l = rowTail(row);
                if (u) {
                    for_each(l.begin(), l.end(), [&u, this](const _WeightedNode& v){ relax(u, v); });
                }
            });
        }

        for_each(adj_list_.begin(), adj_list_.end(), [](const WeightedRow& row){
            const auto& u = rowHead(row);
            const auto& l = rowTail(row);
            if (u) {
                for_each(l.begin(), l.end(), [&u](const _WeightedNode& w){
                    const auto& v = w.node;
                    if (v) {
                        if ((u->distance != k_infinity) && (v->distance > (u->distance + w.weight))) {
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
            if (u && adj_list_.find(u) != adj_list_.end()) {
                for_each(adj_list_[u].begin(), adj_list_[u].end(), [&u, this](const _WeightedNode& v){ relax(u, v); });
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

        auto node_greater = [](const _Node& lhs, const _Node& rhs){
            assert(lhs && rhs);
            return (lhs->distance > rhs->distance);
        };

        priority_queue<_Node, vector<_Node>, decltype(node_greater)> q(node_greater);
        for_each(adj_list_.begin(), adj_list_.end(), [&q](const WeightedRow& row){
            const _Node& u = rowHead(row);
            if (u) {
                q.push(u);
            }
        });

        while (!q.empty()) {
            const auto& u = q.top();
            assert(u);

            for_each(adj_list_[u].begin(), adj_list_[u].end(), [&u, this](const _WeightedNode& v){ relax(u, v); });

            q.pop();
        }
    }

    void dump() const
    {
        for_each(adj_list_.begin(), adj_list_.end(), [](const WeightedRow& row){
            const auto& n = rowHead(row);
            const auto& l = rowTail(row);
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
        auto found = find_if(adj_list_.begin(), adj_list_.end(), [&n](const WeightedRow& row){
            const auto& node = rowHead(row);
            return (node && node->node == n);
        });
        return (found == adj_list_.end() ? _Node() : found->first);
    }

    void resetStates()
    {
        loop_detected_ = false;
        for_each(adj_list_.begin(), adj_list_.end(), [](const WeightedRow& row){
            const auto& n = rowHead(row);
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
        if (!n || adj_list_.find(n) == adj_list_.end()) {
            return;
        }

        // node n has just been discovered
        ++t;
        n->discover_time = t;
        n->color = NodeColor::COLOR_GREY;

        // explore edge (n, v)
        for_each(adj_list_[n].begin(), adj_list_[n].end(), [&n, &t, this](const _WeightedNode& w){
            const auto& node = w.node;
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
        if (!u || !(v.node) || adj_list_.find(u) == adj_list_.end()) {
            return;
        }

        if ((v.weight == k_infinity) || (u->distance == k_infinity)) {
            // w = w(u, v), (u, v) must in G.E
            // AND
            // v.d can never be greater than infinity
            return;
        }

        // TODO: what if u.d + w > k_infinity
        if ((v.node)->distance > (u->distance + v.weight)) {
            (v.node)->distance = u->distance + v.weight;
            (v.node)->parent = u;
        }
    }

private:
    WeightedAdjacentList adj_list_;
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

    //g.dump();
}

template <typename Node>
map<Node, int> calc(const Node& champion, Graph<Node>& graph)
{
    map<Node, int> result;

    // Method 1: BFS
    // |----------|---------|---------|------------|
    // | Compiler | Version | Time(s) | Memory(KB) |
    // |----------|---------|---------|------------|
    // | Clang++  | 4.0.1   | 0.046   | 588        |
    // | G++      | 7.1     | 0.046   | 608        |
    // | VC++     | 2017    | 0.078   | 492        |
    // |----------|---------|---------|------------|
    //graph.bfs(champion);

    // Method 2: Bellman-Ford
    // |----------|---------|---------|------------|
    // | Compiler | Version | Time(s) | Memory(KB) |
    // |----------|---------|---------|------------|
    // | Clang++  | 4.0.1   | 0.093   | 584        |
    // | G++      | 7.1     | 0.078   | 608        |
    // | VC++     | 2017    | 0.109   | 512        |
    // |----------|---------|---------|------------|
    // Whether detect loop or not, does not affect the performance
    //graph.bellmanFord(champion);

    // Method 3: Dijkstra
    // |----------|---------|---------|------------|
    // | Compiler | Version | Time(s) | Memory(KB) |
    // |----------|---------|---------|------------|
    // | Clang++  | 4.0.1   | 0.062   | 592        |
    // | G++      | 7.1     | 0.062   | 620        |
    // | VC++     | 2017    | 0.078   | 492        |
    // |----------|---------|---------|------------|
    graph.dijkstra(champion);

    // Method 4: DAG shortest path
    // CANNOT use DAG, since it is not a directed non-circle graph in this case
    //graph.dagShortestPaths(champion);

    // Compiler Performance: Clang++ > G++ > VC++
    // Algorithem performance: BFS > Dijkstra > Bellman-Ford

    using Vertex = shared_ptr<NodeHolder<Node>>;
    set<Vertex> vertices = graph.getVertices();
    for_each(vertices.begin(), vertices.end(), [&result](const Vertex& v){ result[v->node] = v->distance; });

    return result;
}

template <typename Node>
void showResult(const map<Node, int>& result)
{
    auto n = result.size();

    for_each(result.begin(), result.end(), [&n](const pair<Node, int>& p){
        cout << p.first << ' ';
        if (p.second == k_infinity) {
            cout << "undefined";
        }
        else {
            cout << p.second;
        }

        if (n > 1) {
            cout << endl;
        }

        --n;
    });
}

int main(int argc, char* argv[])
{
    Graph<string> graph(false /* directed */);

    getInput(graph);

    const string champion = "Isenbaev";
    auto result = calc(champion, graph);

    showResult(result);

    return 0;
}

