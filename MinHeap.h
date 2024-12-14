#pragma once
#include <vector>
#include <string>
#include "HuffmanNode.h"

using namespace std;

class MinHeap
{
private:
    vector<HuffmanNode*> heap_array;
    int current_size;

    void heapify_down(int index);
    void heapify_up(int index);

public:
    MinHeap();
    void insert_node(HuffmanNode* node);
    HuffmanNode* remove_min();
    int get_size();
};

HuffmanNode* build_huffman_tree(vector<char>& characters, vector<int>& frequencies);
