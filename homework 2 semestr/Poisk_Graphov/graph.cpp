#include "Graph.h"
#include <sstream>
#include <fstream>

int Graph::getInternalIndex(int vertex_id) const {
    for (size_t i = 0; i < network_nodes.size(); ++i) {
        if (network_nodes[i].id == vertex_id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void Graph::linkVertices(int source_id, int target_id) {
    int src_pos = getInternalIndex(source_id);
    if (src_pos == -1) {
        network_nodes.push_back(Node(source_id));
        src_pos = network_nodes.size() - 1;
    }

    int tgt_pos = getInternalIndex(target_id);
    if (tgt_pos == -1) {
        network_nodes.push_back(Node(target_id));
        tgt_pos = network_nodes.size() - 1;
    }

    network_nodes[src_pos].adjacent_ids.insert(target_id);
    network_nodes[tgt_pos].adjacent_ids.insert(source_id);
}

Graph::Graph(const std::string& path_to_file) {
    std::ifstream input_stream(path_to_file);
    if (!input_stream.is_open()) {
        std::cerr << "CRITICAL: Unable to open file " << path_to_file << std::endl;
        return;
    }

    std::string current_line;
    if (std::getline(input_stream, current_line)) {
    }

    while (std::getline(input_stream, current_line)) {
        if (current_line.empty()) continue;
        
        std::stringstream ss(current_line);
        std::string src_raw, tgt_raw;
        
        if (std::getline(ss, src_raw, ',') && std::getline(ss, tgt_raw)) {
            int src = std::stoi(src_raw);
            int tgt = std::stoi(tgt_raw);
            linkVertices(src, tgt);
        }
    }
    input_stream.close();
}

std::vector<std::vector<int>> Graph::extractDisjointGraphs() {
    std::vector<std::vector<int>> all_components;
    std::set<int> visited_ids;

    for (const auto& vertex : network_nodes) {
        if (visited_ids.find(vertex.id) == visited_ids.end()) {
            std::vector<int> local_component;
            std::queue<int> bfs_queue;

            bfs_queue.push(vertex.id);
            visited_ids.insert(vertex.id);

            while (!bfs_queue.empty()) {
                int current_id = bfs_queue.front();
                bfs_queue.pop();
                local_component.push_back(current_id);

                int idx = getInternalIndex(current_id);
                if (idx != -1) {
                    for (int neighbor_id : network_nodes[idx].adjacent_ids) {
                        if (visited_ids.find(neighbor_id) == visited_ids.end()) {
                            visited_ids.insert(neighbor_id);
                            bfs_queue.push(neighbor_id);
                        }
                    }
                }
            }
            all_components.push_back(local_component);
        }
    }
    return all_components;
}

void Graph::exportComponents(const std::vector<std::vector<int>>& components, const std::string& base_name) {
    for (size_t i = 0; i < components.size(); ++i) {
        std::set<int> component_filter(components[i].begin(), components[i].end());
        std::string out_name = "subgraph_" + std::to_string(i + 1) + "_" + base_name;
        
        std::ofstream output_file(out_name);
        if (!output_file.is_open()) continue;

        output_file << "Source,Target\n";

        std::ifstream source_file(base_name);
        std::string line;
        std::getline(source_file, line); 

        while (std::getline(source_file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string src_str;
            if (std::getline(ss, src_str, ',')) {
                int source_val = std::stoi(src_str);
                if (component_filter.find(source_val) != component_filter.end()) {
                    output_file << line << "\n";
                }
            }
        }
        source_file.close();
        output_file.close();
    }
}