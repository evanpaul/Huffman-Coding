# Huffman Coding
A C program that uses Huffman encoding to compress an inputted text file.
## Usage
Compilation: `gcc -o huffman huffman.c tree.c pack.c`  
Run: `./huffman input.txt output.gz` (only the extensions are important)  
To test if it succeeded, decompress the file using gzip:
`gzip -d output.gz`
## How it works
Huffman coding works by analyzing the input text and counting character frequency. A tree is then built 'upwards' i.e. builds toward the root rather than from it. Based on the tree, a bit pattern is created for each character based upon whether you traverse to a left child (0) or a right child (1). This reduces the number of bits required to represent frequently occurring characters.

[Here's a quick and insightful visualization (not made by me) of how the algorithm  works](https://www.siggraph.org/education/materials/HyperGraph/video/mpeg/mpegfaq/huffman_tutorial.html)
