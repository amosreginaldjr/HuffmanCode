#include "GenerateHuffmanCodes.h"
#include "HuffmanNode.h"

void generate_huffman_codes(HuffmanNode* root, std::string current_code, std::string* code_table)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->character != '\0')
    {
        code_table[(int)root->character] = current_code;
    }

    generate_huffman_codes(root->left_child, current_code + "0", code_table);
    generate_huffman_codes(root->right_child, current_code + "1", code_table);
}
