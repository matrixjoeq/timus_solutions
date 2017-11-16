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
    while (getline(cin, line)) {
        istringstream input(line);

        T x;
        while (input >> x) {
            c.push_back(x);
        }
    }
}

struct NullType
{
};

template<typename Payload>
class Vertex
{
public:
    typedef std::map<uint32_t, uint32_t> NeighbourMap;
    typedef std::list<uint32_t> NeighbourList;

    explicit Vertex(uint32_t id) : id_(id) {}

    Vertex(const Vertex& other)
     : id_(other.id_),
       payload_(other.payload_)
    {}

    ~Vertex() {}

    uint32_t GetId() const
    {
        return id_;
    }

    void SetPayload(Payload& payload)
    {
        payload_ = payload;
    }

    Payload GetPayload() const
    {
        return payload_;
    }

    int AddNeighbour(uint32_t id, uint32_t weight = 0)
    {
        if (neighbours_.find(id) == neighbours_.end()) {
            neighbours_[id] = weight;
            return 0;
        }

        return -1;
    }

    int RemoveNeighbour(uint32_t id)
    {
        if (neighbours_.find(id) != neighbours_.end()) {
            neighbours_.erase(id);
            return 0;
        }

        return -1;
    }

    void GetNeighbours(NeighbourList& l) const
    {
        l.clear();
        for (NeighbourMap::iterator it = neighbours_.begin(); it != neighbours_.end(); ++it) {
            l.push_back(it->first);
        }
    }

    void GetNeighbours(NeighbourMap& m) const
    {
        m = neighbours_;
    }

    uint32_t GetNeighbourWeight(uint32_t id) const
    {
        if (neighbours_.find(id) != neighbours_.end()) {
            return neighbours_[id];
        }

        return 0;
    }

    Vertex& operator=(const Vertex& other)
    {
        if (this != &other) {
            id_ = other.id_;
            payload_ = other.payload_;
        }
    }

private:
    uint32_t id_;
    Payload payload_;
    NeighbourMap neighbours_;
};

template<typename Payload>
class Graph
{
public:
    typedef std::map<uint32_t id, Vertex<Payload> > VertexMap;

    Graph() : id_gen_(0) {}
    ~Graph() {}

    inline int AddVertex(Payload& payload)
    {
        return AddVertex(id_gen_++, payload);
    }

    int AddVertex(uint32_t id, Payload& payload)
    {
        if (vertices_.find(id) == vertices_.end()) {
            Vertex<Payload> v(id);
            v.SetPayload(payload);
            vertices_[id] = v;
            return 0;
        }

        return -1;
    }

    Vertex<Payload> GetVertex(uint32_t id)
    {
        return vertices_[id];
    }

    void GetVertices(VertexMap& m)
    {
        m = vertices_;
    }

    int AddEdge(uint32_t from_id, uint32_t to_id, uint32_t weight = 0)
    {
        if (vertices_.find(from_id) == vertices_.end() ||
            vertices_.find(to_id) == vertices_.end()) {
            return -1;
        }

        return vertices_[from_id].AddNeighbour(to_id, weight);
    }

    int RemoveEdge(uint32_t from_id, uint32_t to_id)
    {
        if (vertices_.find(from_id) == vertices_.end() ||
            vertices_.find(to_id) == vertices_.end()) {
            return -1;
        }

        return vertices_[from_id].RemoveNeighbour(to_id);
    }

    void DFS()
    {
        cc_count_ = 0;
        std::list<uint32_t> visited;
        std::stack<uint32_t> visit_stack;
        for (VertexMap::iterator it = vertices_.begin(); it != vertices_.end(); ++it) {
            if (std::find(visited.begin(), visited.end(), it->first) != visited.end()) {
                continue;
            }
            
            ++cc_count_;
            visited.push_back(it->first);
            visit_stack.push(it->first);

            while (!visti_stack.empty()) {
                std::list<uint32_t> neighbours;
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

int main()
{
    return 0;
}

