#pragma once
#include <string>
#include "HuffmanNode.h"

void generate_huffman_codes(HuffmanNode* root, std::string current_code, std::string* code_table);
