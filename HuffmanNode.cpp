#include "HuffmanNode.h"

HuffmanNode::HuffmanNode(char c, int f)
{
    character = c;
    frequency = f;
    left_child = nullptr;
    right_child = nullptr;
}
