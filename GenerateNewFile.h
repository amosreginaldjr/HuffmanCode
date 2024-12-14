#pragma once
#include <string>
#include <fstream> ///////////////////////////////////////////////////
#include "HuffmanNode.h"
#include "MinHeap.h"

class GenerateNewFile
{
private:
    std::ofstream out;
    std::ifstream in;
    std::string file_name;

public:
    void set_file_name(std::string parameter_file_name);
    void place_data_into_file(std::string parameter_file_name, std::string& full_text);
    void encode(const std::string& input_file, const std::string& output_file);
    void decode(const std::string& input_file, HuffmanNode* huffman_tree_root, const std::string& output_file);
    
    void print_prefix_tree(HuffmanNode* root, string current_code);
};
