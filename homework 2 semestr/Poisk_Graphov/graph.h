#pragma once
#include <iostream>
#include <set>
#include <queue>
#include <vector>

struct Node {
    int id;
    std::set<int> adjacent_ids; 

    Node(int _id) : id(_id) {}
};

class Graph {
private:
    std::vector<Node> network_nodes; 

    int getInternalIndex(int vertex_id) const;

public:
    Graph() = default;
    Graph(const std::string& path_to_file); 

    void linkVertices(int source_id, int target_id);
    
    std::vector<std::vector<int>> extractDisjointGraphs();
    
    void exportComponents(const std::vector<std::vector<int>>& components, const std::string& base_name);
};