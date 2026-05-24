#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "Graph.h"

int main() {
    std::string test_filename = "TestGraph.txt";
    Graph test_instance(test_filename);
    std::vector<std::vector<int>> test_res = test_instance.extractDisjointGraphs();
    test_instance.exportComponents(test_res, test_filename);
    std::cout << "[SUCCESS] TestGraph.txt processed. Isolated subgraphs: " << test_res.size() << std::endl;

    std::string main_filename = "1000.csv";
    Graph main_instance(main_filename);
    std::vector<std::vector<int>> main_res = main_instance.extractDisjointGraphs();
    main_instance.exportComponents(main_res, main_filename);
    std::cout << "[SUCCESS] 1000.csv processed. Isolated subgraphs: " << main_res.size() << std::endl;

    return 0;
}