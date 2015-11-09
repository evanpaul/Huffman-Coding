# Huffman Encoding
A C program that uses Huffman encoding to compress an inputted text file.
## Usage
Compilation: `gcc -o huffman huffman.c tree.c pack.c`  
Run: `./huffman input.txt output.gz` (only the extensions are important)  
To test if it succeeded, decompress the file using gzip:
`gzip -d output.gz`
## How it works
The program analyzes the input text and counts character frequency. It then builds a tree 'upwards' i.e. builds toward the root rather than from it. Based on the tree a bit battern is then created for each character based upon whether you traverse to a left child (0) or a right child (1). This reduces the number of bits required to represent frequently occuring characters.

[Here's a quick and insightful visualization of how the algorithm works](https://www.siggraph.org/education/materials/HyperGraph/video/mpeg/mpegfaq/huffman_tutorial.html)