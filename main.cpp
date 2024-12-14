#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "GenerateNewFile.h"
#include "GenerateHuffmanCodes.h"
#include "HuffmanNode.h"
#include "MinHeap.h"
using namespace std;

bool isFile(int& read_from_file_or_input);
void user_input_or_file();

int main()
{
    int file_or_input = 0;
    user_input_or_file();
    cout << "Input the corresponding int: ";
    cin >> file_or_input;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clearing input buffer

    if (file_or_input == 1)
    {
        string file_base_name = "test_file_";

        GenerateNewFile gnf;

        for (int i = 0; i < 21; i++)
        {
            string current_file_name = file_base_name + to_string(i) + ".txt";
            string encoded_file_name = "encoded_" + to_string(i) + ".bin";
            string decoded_file_name = "decoded_" + to_string(i) + ".txt";

            ifstream in(current_file_name);
            if (!in.is_open())
            {
                cout << "Error opening file: " << current_file_name << endl;
                continue;
            }
            in.close();

            
            gnf.set_file_name(current_file_name);
            gnf.encode(current_file_name, encoded_file_name);

            
            ifstream original_file(current_file_name);
            string original_content;
            getline(original_file, original_content, '\0');
            original_file.close();

            int frequency_table[256] = {0};
            for (char c : original_content)
            {
                frequency_table[(int)c]++;
            }

            vector<char> characters;
            vector<int> frequencies;
            for (int j = 0; j < 256; j++)
            {
                if (frequency_table[j] > 0)
                {
                    characters.push_back((char)j);
                    frequencies.push_back(frequency_table[j]);
                }
            }

            HuffmanNode* huffman_tree_root = build_huffman_tree(characters, frequencies);

            
            cout << "\nPrefix Tree for " << current_file_name << ":\n";
            gnf.print_prefix_tree(huffman_tree_root, "");

            
            gnf.decode(encoded_file_name, huffman_tree_root, decoded_file_name);

            cout << "File " << current_file_name << " encoded to " << encoded_file_name
                 << " and decoded to " << decoded_file_name << endl;
        }
    }
    
    else
    {
        string user_input_string;
        cout << "Enter a string: ";
        getline(cin, user_input_string);

        // Frequency table setup
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

        cout << "\nPrefix Tree:\n";
        GenerateNewFile gnf;
        gnf.print_prefix_tree(huffman_tree_root, "");

        string code_table[256];
        for (int i = 0; i < 256; i++)
        {
            code_table[i] = "";
        }

        generate_huffman_codes(huffman_tree_root, "", code_table);

        cout << "\nHuffman Codes:\n";
        for (int i = 0; i < 256; i++)
        {
            if (!code_table[i].empty())
            {
                cout << (char)i << ": " << code_table[i] << endl;
            }
        }

        string encoded_string = "";
        for (char c : user_input_string)
        {
            encoded_string += code_table[(int)c];
        }
        cout << "\nEncoded string (binary format): " << encoded_string << endl;

        string decoded_string = "";
        HuffmanNode* current_node = huffman_tree_root;
        for (char bit : encoded_string)
        {
            if (bit == '0')
                current_node = current_node->left_child;
            else if (bit == '1')
                current_node = current_node->right_child;

            if (current_node->left_child == nullptr && current_node->right_child == nullptr)
            {
                decoded_string += current_node->character;
                current_node = huffman_tree_root;
            }
        }

        cout << "Decoded string: " << decoded_string << endl;
    }

    return 0;
}

bool isFile(int& read_from_file_or_input)
{
    return (read_from_file_or_input == 1);
}

void user_input_or_file()
{
    cout << "1) File\n2) Input\n";
}
