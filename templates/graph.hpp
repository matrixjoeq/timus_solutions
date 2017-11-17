
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


