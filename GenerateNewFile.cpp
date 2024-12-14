#include "GenerateNewFile.h"
#include "GenerateHuffmanCodes.h"
#include "HuffmanNode.h"
#include "MinHeap.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

void GenerateNewFile::set_file_name(string parameter_file_name)
{
    file_name = parameter_file_name;
}

void GenerateNewFile::place_data_into_file(string parameter_file_name, string& full_text)
{
    out.open(parameter_file_name);
    if (out.is_open())
    {
        out << full_text;
        out.close();
    }
    else
    {
        cout << "Error opening file to write." << endl;
    }
}

void GenerateNewFile::encode(const string& input_file, const string& output_file)
{
    ifstream in(input_file);
    string user_input_string;
    if (in.is_open())
    {
        getline(in, user_input_string, '\0');
        in.close();
    }
    else
    {
        cout << "Error opening input file." << endl;
        return;
    }

    int frequency_table[256] = {0};
    for (char c : user_input_string)
    {
        frequency_table[(int)c]++;
    }

    vector<char> characters;
    vector<int> frequencies;
    for (int i = 0; i < 256; i++)
    {
        if (frequency_table[i] > 0)
        {
            characters.push_back((char)i);
            frequencies.push_back(frequency_table[i]);
        }
    }

    HuffmanNode* huffman_tree_root = build_huffman_tree(characters, frequencies);

    string code_table[256];
    for (int i = 0; i < 256; i++)
    {
        code_table[i] = "";
    }

    generate_huffman_codes(huffman_tree_root, "", code_table);

    string encoded_bits = "";
    for (char c : user_input_string)
    {
        encoded_bits += code_table[(int)c];
    }

    ofstream out(output_file, ios::binary);
    if (out.is_open())
    {
        unsigned char byte = 0;
        int bit_count = 0;

        for (char bit : encoded_bits)
        {
            byte = (byte << 1) | (bit - '0');
            bit_count++;

            if (bit_count == 8)
            {
                out.put(byte);
                byte = 0;
                bit_count = 0;
            }
        }

        if (bit_count > 0)
        {
            byte <<= (8 - bit_count);
            out.put(byte);
        }

        out.close();
    }
    else
    {
        cout << "Error opening output file." << endl;
    }

    cout << "Encoding completed and saved to " << output_file << endl;
}

void GenerateNewFile::decode(const string& input_file, HuffmanNode* huffman_tree_root, const string& output_file)
{
    ifstream in(input_file, ios::binary);
    if (!in.is_open())
    {
        cout << "Error opening input file." << endl;
        return;
    }

    string encoded_bits = "";
    unsigned char byte;
    while (in.read(reinterpret_cast<char*>(&byte), 1))
    {
        for (int i = 7; i >= 0; i--)
        {
            encoded_bits += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    in.close();

    string decoded_string = "";
    HuffmanNode* current_node = huffman_tree_root;

    for (char bit : encoded_bits)
    {
        if (bit == '0')
        {
            current_node = current_node->left_child;
        }
        else if (bit == '1')
        {
            current_node = current_node->right_child;
        }

        if (current_node->left_child == nullptr && current_node->right_child == nullptr)
        {
            decoded_string += current_node->character;
            current_node = huffman_tree_root;
        }
    }

    ofstream out(output_file);
    if (out.is_open())
    {
        out << decoded_string;
        out.close();
    }
    else
    {
        cout << "Error opening output file." << endl;
    }

    cout << "Decoding completed and saved to " << output_file << endl;
}





void GenerateNewFile::print_prefix_tree(HuffmanNode* root, string current_code)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->left_child == nullptr && root->right_child == nullptr)
    {
        cout << root->character << ": " << current_code << endl;
    }
    
    print_prefix_tree(root->left_child, current_code + "0");

    print_prefix_tree(root->right_child, current_code + "1");
}
