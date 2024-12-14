#include "MinHeap.h"
#include "HuffmanNode.h"
#include <cstring>

MinHeap::MinHeap()
{
    current_size = 0;
}

void MinHeap::heapify_down(int index)
{
    int smallest = index;
    int left_child_index = 2 * index + 1;
    int right_child_index = 2 * index + 2;

    if (left_child_index < current_size && heap_array[left_child_index]->frequency < heap_array[smallest]->frequency)
    {
        smallest = left_child_index;
    }
    if (right_child_index < current_size && heap_array[right_child_index]->frequency < heap_array[smallest]->frequency)
    {
        smallest = right_child_index;
    }
    if (smallest != index)
    {
        HuffmanNode* temp = heap_array[index];
        heap_array[index] = heap_array[smallest];
        heap_array[smallest] = temp;
        heapify_down(smallest);
    }
}

void MinHeap::heapify_up(int index)
{
    int parent_index = (index - 1) / 2;
    if (index > 0 && heap_array[index]->frequency < heap_array[parent_index]->frequency)
    {
        HuffmanNode* temp = heap_array[index];
        heap_array[index] = heap_array[parent_index];
        heap_array[parent_index] = temp;
        heapify_up(parent_index);
    }
}

void MinHeap::insert_node(HuffmanNode* node)
{
    heap_array.push_back(node);
    current_size++;
    heapify_up(current_size - 1);
}

HuffmanNode* MinHeap::remove_min()
{
    if (current_size == 0)
    {
        return nullptr;
    }
    HuffmanNode* min_node = heap_array[0];
    heap_array[0] = heap_array[current_size - 1];
    heap_array.pop_back();
    current_size--;
    heapify_down(0);
    return min_node;
}

int MinHeap::get_size()
{
    return current_size;
}

HuffmanNode* build_huffman_tree(vector<char>& characters, vector<int>& frequencies)
{
    MinHeap heap;

    for (int i = 0; i < characters.size(); i++)
    {
        heap.insert_node(new HuffmanNode(characters[i], frequencies[i]));
    }

    while (heap.get_size() > 1)
    {
        HuffmanNode* left_child = heap.remove_min();
        HuffmanNode* right_child = heap.remove_min();

        HuffmanNode* parent_node = new HuffmanNode('\0', left_child->frequency + right_child->frequency);
        parent_node->left_child = left_child;
        parent_node->right_child = right_child;

        heap.insert_node(parent_node);
    }

    return heap.remove_min();
}
