/*
 * 1671. Anansi's Cobweb
 * Time limit: 1.0 second
 * Memory limit: 64 MB
 *
 * [Description]
 * Usatiy-Polosatiy XIII decided to destroy Anansi's home — his cobweb. The
 * cobweb consists of N nodes, some of which are connected by threads. Let 
 * us say that two nodes belong to the same piece if it is possible to get 
 * from one node to the other by threads. Usatiy-Polosatiy has already 
 * decided which threads and in what order he would tear and now wants to 
 * know the number of pieces in cobweb after each of his actions.
 *
 * [Input]
 * The first line contains integers N and M — the number of nodes and threads
 * in the cobweb, respectively(2 ≤ N ≤ 100000; 1 ≤ M ≤ 100000). Each of the 
 * next M lines contains two different integers — the 1-based indices of nodes
 * connected by current thread. The threads are numbered from 1 to M in the 
 * order of description. Next line contains an integer Q which denotes the 
 * quantity of threads Usatiy-Polosatiy wants to tear (1 ≤ Q ≤ M). The last 
 * line contains numbers of these threads — different integers separated by 
 * spaces.
 *
 * [Output]
 * Output Q integers — the number of pieces in Anansi's cobweb after each of 
 * Usatiy-Polosatiy's action. Separate numbers with single spaces.
 */

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
    cin >> x;
}

// Get a line input from stdin
// Add the values as elements in Container
template<typename Container>
static void get_inputs(Container& c)
{
    typedef typename Container::value_type T;

    string line;
    while (getline(cin, line))
    {
        istringstream input(line);

        T x;
        while (input >> x)
        {
            c.push_back(x);
        }
    }
}

class Vertex
{
public:
    typedef std::map<uint32_t, uint32_t> NeighbourMap;
    typedef std::vector<uint32_t> NeighbourList;

    Vertex() : id_(0) {}

    explicit Vertex(uint32_t id) : id_(id) {}

    Vertex(const Vertex& other)
     : id_(other.id_), neighbours_(other.neighbours_)
    {}

    ~Vertex() {}

    void SetId(uint32_t id)
    {
        id_ = id;
    }

    uint32_t GetId() const
    {
        return id_;
    }

    int AddNeighbour(uint32_t id, uint32_t weight = 0)
    {
        //if (neighbours_.find(id) != neighbours_.end()) return -1;
        
        neighbours_[id] = weight;
        return 0;
    }

    int RemoveNeighbour(uint32_t id)
    {
        //if (neighbours_.find(id) == neighbours_.end()) return -1;
        
        neighbours_.erase(id);
        return 0;
    }

    void GetNeighbours(NeighbourList& l)
    {
        l.clear();
        l.reserve(neighbours_.size());
        for (NeighbourMap::iterator it = neighbours_.begin();
             it != neighbours_.end();
             ++it)
        {
            l.push_back(it->first);
        }
    }

    void GetNeighbours(NeighbourMap& m) const
    {
        m = neighbours_;
    }

    uint32_t GetNeighbourWeight(uint32_t id)
    {
        return neighbours_[id];
    }

    Vertex& operator=(const Vertex& other)
    {
        if (this != &other) 
        {
            id_ = other.id_;
            neighbours_ = other.neighbours_;
        }
    }

    bool operator<(const Vertex& other) const
    {
        return id_ < other.id_;
    }

    bool operator==(const Vertex& other) const
    {
        return id_ == other.id_;
    }

private:
    uint32_t id_;
    NeighbourMap neighbours_;
};

struct Edge
{
    Edge() : from(0), to(0), weight(0) {}
    Edge(uint32_t f, uint32_t t, uint32_t w) : from(f), to(t), weight(w) {}
    Edge(const Edge& other) : from(other.from), to(other.to), weight(other.weight) {}
    Edge& operator=(const Edge& other)
    {
        if (this != &other)
        {
            from = other.from;
            to = other.to;
            weight = other.weight;
        }

        return *this;
    }

    uint32_t from;
    uint32_t to;
    uint32_t weight;
};

class Graph
{
public:
    typedef std::map<uint32_t, Vertex> VertexMap;
    typedef typename VertexMap::iterator VertexIter;
    typedef std::vector<Vertex> VertexList;
    typedef std::vector<Edge> EdgeList;

    Graph() : id_gen_(0) {}
    ~Graph() {}

    inline int AddVertex()
    {
        return AddVertex(id_gen_++);
    }

    int AddVertex(uint32_t id)
    {
        //if (vertices_.find(id) != vertices_.end()) return -1;
            
        Vertex v(id);
        vertices_[id] = v;
        return 0;
    }

    Vertex GetVertex(uint32_t id)
    {
        return vertices_[id];
    }

    void GetVertices(VertexMap& m)
    {
        m = vertices_;
    }

    void GetVertices(VertexList& l)
    {
        for (VertexIter it = vertices_.begin(); it != vertices_.end(); ++it)
        {
            l.push_back(it->second);
        }
    }

    void DumpVertices()
    {
        std::cout << "Graph vertices: ";
        for (VertexIter it = vertices_.begin(); it != vertices_.end(); ++it)
        {
            std::cout << it->first << ' ';
        }
        std::cout << endl;
    }

    int AddEdge(uint32_t from_id, uint32_t to_id, uint32_t weight = 0)
    {
        /*
        if (vertices_.find(from_id) == vertices_.end() ||
            vertices_.find(to_id) == vertices_.end()) 
        {
            return -1;
        }
        */

        return vertices_[from_id].AddNeighbour(to_id, weight);
    }

    int RemoveEdge(uint32_t from_id, uint32_t to_id)
    {
        /*
        if (vertices_.find(from_id) == vertices_.end() ||
            vertices_.find(to_id) == vertices_.end()) 
        {
            return -1;
        }
        */

        return vertices_[from_id].RemoveNeighbour(to_id);
    }

    void GetEdges(EdgeList& l)
    {
        for (VertexIter it = vertices_.begin(); it != vertices_.end(); ++it)
        {
            Vertex::NeighbourMap m;
            it->second.GetNeighbours(m);
            for (Vertex::NeighbourMap::iterator nit = m.begin(); nit != m.end(); ++nit)
            {
                uint32_t from = it->second.GetId();
                uint32_t to = nit->first;
                uint32_t weight = nit->second;
                Edge e(from, to, weight);
                l.push_back(e); 
            }
        }
    }

    void DumpEdges()
    {
        std::cout << "Graph edges: " << std::endl;
        for (VertexIter it = vertices_.begin(); it != vertices_.end(); ++it)
        {
            std::cout << "from: " << it->first << ", to: ";
            Vertex::NeighbourList neighbours;
            it->second.GetNeighbours(neighbours);
            for (Vertex::NeighbourList::iterator it = neighbours.begin();
                 it != neighbours.end();
                 ++it)
            {
                std::cout << *it << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void DFS()
    {
        cc_count_ = 0;
        std::vector<bool> visited(vertices_.size() + 1, false);
        std::stack<uint32_t> visit_stack;
        for (VertexIter it = vertices_.begin(); it != vertices_.end(); ++it)
        {
            if (visited[it->first]) continue;
            
            ++cc_count_;
            visited[it->first] = true;
            visit_stack.push(it->first);

            Vertex::NeighbourList neighbours;
            uint32_t vid;
            bool all_neighbours_visited;
            while (!visit_stack.empty()) 
            {
                vid = visit_stack.top();
                vertices_[vid].GetNeighbours(neighbours);
                    
                all_neighbours_visited = true;
                for (Vertex::NeighbourList::iterator it = neighbours.begin();
                     it != neighbours.end();
                     ++it)
                {
                    if (!visited[*it])
                    {
                        all_neighbours_visited = false;
                        visited[*it] = true;
                        visit_stack.push(*it);
                        break;
                    }
                }

                if (all_neighbours_visited)
                {
                    visit_stack.pop();
                }
            }
        }
    }

    uint32_t GetConnectedComponentCount()
    {
        DFS();
        return cc_count_;
    }

private:
    uint32_t id_gen_;
    VertexMap vertices_;
    uint32_t cc_count_; // Connected Component Count
};


template<typename Rank, typename Parent>
class DisjointSet
{
public:
    DisjointSet(Rank r, Parent p) : rank_(r), parent_(p) {}
    ~DisjointSet() {}

    DisjointSet(const DisjointSet& other)
      : rank_(other.rank_),
        parent_(other.parent_)
    {}

    template<typename Element>
    void MakeSet(Element x)
    {
        parent_[x] = x;
        typedef typename Rank::value_type::second_type R;
        rank_[x] = R();
    }

    template<typename Element>
    void LinkSet(Element x, Element y)
    {
        if (x == y) return;

        if (rank_[x] > rank_[y])
        {
            parent_[y] = x;
        }
        else if (rank_[y] > rank_[x])
        {
            parent_[x] = y;
        }
        else
        {
            parent_[y] = x;
            ++rank_[x];
        }
    }

    template<typename Element>
    void UnionSet(Element x, Element y)
    {
        LinkSet(FindSet(x), FindSet(y));
    }

    template<typename Element>
    Element FindSet(Element x)
    {
        typedef std::list<Element> ElementList;

        ElementList l;
        while (!(parent_[x] == x))
        {
            l.push_back(x);
            x = parent_[x];
        }

        for (typename ElementList::iterator it = l.begin();
             it != l.end();
             ++it)
        {
            parent_[*it] = x;
        }

        return x;
    }

    template<typename ElementIterator>
    std::size_t CountSet(ElementIterator first, ElementIterator last)
    {
        std::size_t count = 0;
        for (; first != last; ++first)
        {
            if (parent_[*first] == *first)
            {
                ++count;
            }
        }

        return count;
    }

private:
    Rank rank_;
    Parent parent_;
};

static void get_n_m(uint32_t& n, uint32_t& m)
{
    string line;
    getline(cin, line);
    istringstream input(line);
    input >> n;
    input >> m;
}

static void add_vertices(Graph& g, uint32_t n)
{
    do
    {
        g.AddVertex(n--);
    }
    while (n);
}

template<typename Seq>
static void get_edges(Seq& edges, uint32_t m)
{
    typedef typename Seq::value_type ValueType;

    edges.reserve(m * 2);
    while (m--)
    {
        string line = "";
        getline(cin, line);
        istringstream input(line);
        ValueType u, v;
        input >> u;
        input >> v;
        edges.push_back(u);
        edges.push_back(v);
    }
}

template<typename Seq>
static void add_edges(Graph& g, Seq& edges)
{
    size_t m = edges.size();
    typename Seq::iterator from = edges.begin();
    typename Seq::iterator to = from + 1;
    while (m)
    {
        //cout << "Add edge from " << *from << " to " << *to << endl;
        g.AddEdge(*from, *to);
        g.AddEdge(*to, *from);
        from += 2;
        to += 2;
        m -= 2;
    }
}

int main()
{
    // setup the graph
    uint32_t n, m;
    get_n_m(n, m);

    Graph g;
    add_vertices(g, n);
    //g.DumpVertices();

    vector<uint32_t> edges;
    get_edges(edges, m);
    
    add_edges(g, edges);
    //g.DumpEdges();

    uint32_t q;
    get_single_input(q);

    list<uint32_t> threads;
    get_inputs(threads);

    // jump to last state
    for (list<uint32_t>::iterator it = threads.begin();
         it != threads.end();
         ++it)
    {
        uint32_t from = edges[2 * (*it - 1)];
        uint32_t to = edges[2 * (*it - 1) + 1];
        g.RemoveEdge(from, to);
        g.RemoveEdge(to, from);
    }
    
    // setup the disjoint set with last state
    typedef std::map<Vertex, uint32_t> Rank;
    typedef std::map<Vertex, Vertex> Parent;
    Rank r;
    Parent p;
    DisjointSet<Rank, Parent> dset(r, p);
    Graph::VertexList vertices;
    g.GetVertices(vertices);
    for (Graph::VertexList::iterator it = vertices.begin();
         it != vertices.end(); 
         ++it)
    {
        dset.MakeSet(*it);
    }

    Graph::EdgeList graph_edges;
    g.GetEdges(graph_edges);
    for (Graph::EdgeList::iterator it = graph_edges.begin();
         it != graph_edges.end();
         ++it)
    {
        dset.UnionSet(g.GetVertex(it->from), g.GetVertex(it->to));
    }

    // calculate the connected component in reverse order
    stack<size_t> pieces;
    size_t c = dset.CountSet(vertices.begin(), vertices.end());
    pieces.push(c);
    for (list<uint32_t>::reverse_iterator it = threads.rbegin();
         it != threads.rend();
         ++it)
    {
        uint32_t from = edges[2 * (*it - 1)];
        uint32_t to = edges[2 * (*it - 1) + 1];
        dset.UnionSet(g.GetVertex(from), g.GetVertex(to));
        c = dset.CountSet(vertices.begin(), vertices.end());
        pieces.push(c);
    }

    // first one is not needed
    pieces.pop();
    while (!pieces.empty())
    {
        size_t piece = pieces.top();
        pieces.pop();
        cout << piece;
        if (!pieces.empty())
            cout << ' ';
        else
            cout << endl;
    }

    return 0;
}

