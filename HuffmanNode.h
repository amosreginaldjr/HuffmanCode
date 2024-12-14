#pragma once

struct HuffmanNode
{
    char character;
    int frequency;
    HuffmanNode* left_child;
    HuffmanNode* right_child;

    HuffmanNode(char c, int f);
};
