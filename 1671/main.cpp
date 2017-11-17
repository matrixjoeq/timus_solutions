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

struct NullType
{
};

class Vertex
{
public:
    typedef std::map<uint32_t, uint32_t> NeighbourMap;
    typedef std::list<uint32_t> NeighbourList;

    Vertex() : id_(0) {}

    explicit Vertex(uint32_t id) : id_(id) {}

    Vertex(const Vertex& other)
     : id_(other.id_)
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
        }
    }

private:
    uint32_t id_;
    NeighbourMap neighbours_;
};

class Graph
{
public:
    typedef std::map<uint32_t, Vertex> VertexMap;

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

    void DumpVertices()
    {
        std::cout << "Graph vertices: ";
        for (typename VertexMap::iterator it = vertices_.begin();
             it != vertices_.end();
             ++it)
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

    void DumpEdges()
    {
        std::cout << "Graph edges: " << std::endl;
        for (typename VertexMap::iterator it = vertices_.begin();
             it != vertices_.end();
             ++it)
        {
            std::cout << "from: " << it->first << ", to: ";
            std::list<uint32_t> n;
            it->second.GetNeighbours(n);
            for (std::list<uint32_t>::iterator it = n.begin(); it != n.end(); ++it)
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
        for (typename VertexMap::iterator it = vertices_.begin();
             it != vertices_.end();
             ++it)
        {
            /*
            if (std::find(visited.begin(), visited.end(), it->first) != visited.end()) 
            {
                continue;
            }
            */
            if (visited[it->first]) continue;
            
            ++cc_count_;
            //std::cout << "unvisited node found: " << it->first << std::endl;
            //visited.push_back(it->first);
            visited[it->first] = true;
            visit_stack.push(it->first);

            std::list<uint32_t> neighbours;
            uint32_t vid;
            bool all_neighbours_visited;
            while (!visit_stack.empty()) 
            {
                vid = visit_stack.top();
                vertices_[vid].GetNeighbours(neighbours);
                /*
                std::cout << "neighbours of: " << vid << std::endl;
                for (std::list<uint32_t>::iterator it = neighbours.begin();
                     it != neighbours.end(); ++it)
                {
                    std::cout << *it << ' ';
                }
                std::cout << std::endl;
                */
                     
                all_neighbours_visited = true;
                for (std::list<uint32_t>::iterator it = neighbours.begin();
                     it != neighbours.end();
                     ++it)
                {
                    //if (std::find(visited.begin(), visited.end(), *it) == visited.end())
                    if (!visited[*it])
                    {
                        all_neighbours_visited = false;
                        //visited.push_back(*it);
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
    uint32_t n, m;
    get_n_m(n, m);

    Graph g;
    add_vertices(g, n);
    //g.DumpVertices();

    vector<uint32_t> edges;
    get_edges(edges, m);
    /*
    cout << "origin edges: " << endl;
    for (vector<uint32_t>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
    */

    add_edges(g, edges);
    //g.DumpEdges();

    uint32_t q;
    get_single_input(q);

    list<uint32_t> threads;
    get_inputs(threads);

    list<uint32_t>::iterator it = threads.begin();
    while (q--)
    {
        uint32_t from = edges[2 * (*it - 1)];
        uint32_t to = edges[2 * (*it - 1) + 1];
        g.RemoveEdge(from, to);
        g.RemoveEdge(to, from);
        uint32_t c = g.GetConnectedComponentCount();
        cout << c;
        if (q)
        {
            cout << ' ';
        }
        else
        {
            cout << endl;
        }
        ++it;
    }

    return 0;
}

