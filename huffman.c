#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "pack.h"
#include "tree.h"

#define LCHILD (2*i+1)
#define RCHILD (2*i+2)
#define PARENT ((i-1)/2)


void insert(struct tree*);
struct tree *delete();
void printBits(struct tree*);

int treeCount;
struct tree *heap[257];
struct tree *leaves[257];

int main(int argc, char **argv)
{
	treeCount = 0;
	FILE *fpin, *fpout;
	int c;
	int count[256];
	
	// Check arguments	
	if(argc != 3){
		printf("Usage: ./huffman [input_file] [output_file]\n");
		return 0;
	}
	
	// Open files and confirm
	fpin = fopen(argv[1], "r");
	assert(fpin != NULL);

	fpout = fopen(argv[2], "w");
	assert(fpout != NULL);
	
	// Initialize arrays
	for(int i = 0; i <= 256; i++)
		leaves[i] = NULL;
	for(int i = 0; i < 256; i++)
		count[i] = 0;
	
	// The index of count refers to an ASCII value
	// and the data refers to the # of occurences
	while((c = getc(fpin)) != EOF){
		count[c] = count[c] + 1;
	}
	
	
	struct tree *tp;
	// Create a tree for every nonzero character occurence
	for(int i = 0; i <= 255; i++){
		if(count[i] > 0){
			tp = createTree(count[i], NULL, NULL);
			leaves[i] = tp;
			insert(tp);
		}
	}
	// EOF marker
	leaves[256] = createTree(0, NULL, NULL);
	insert(leaves[256]);

	struct tree *low1, *low2, *result;
	int lowData;
	// Create Huffman Tree
	while(treeCount > 1){
		//Delete two smallest values, create new tree, reinset into priority queue
		low1 = delete();
		low2 = delete();
		lowData = getData(low1) + getData(low2);
		result = createTree(lowData, low1, low2);
		insert(result);
	}
	//Print occurences and patterns
	for(int k = 0; k < 257; k++){
		if(leaves[k] > 0){
			if(isprint(k))
				printf("'%c' : %d ", k, count[k]);
			else
				//If non-printable: print octal value
				printf("%o : %d ", k, count[k]);
			printBits(leaves[k]);
			printf("\n");
		}
	}
	pack(argv[1], argv[2], leaves);

	return 0;
}
void printBits(struct tree *tp){		
	struct tree *parent;
	struct tree *left;
	struct tree *right;

	parent = getParent(tp);

	//Recurse through tree to get pattern
	if(parent != NULL){
		left = getLeft(parent);
		right = getRight(parent);
		printBits(parent);
		if(left == tp)
			printf("0");
		if(right == tp)
			printf("1");
	}
	return;
}		

void insert(struct tree *tp)
{
	int i = treeCount++;
	while(i > 0 && getData(heap[PARENT]) > getData(tp)){
		heap[i] = heap[PARENT];
		i = PARENT;
	}
	heap[i] = tp;
	
	return;
}
struct tree *delete()
{
	int i, child;
	struct tree *min,*x;
	min = heap[0];
	x = heap[--(treeCount)];
	i = 0;
	while(LCHILD < treeCount){
		child = LCHILD;
		if(RCHILD < treeCount && getData(heap[LCHILD]) > getData(heap[RCHILD]))
			child = RCHILD;
		if(getData(x) > getData(heap[child])){
			heap[i] = heap[child];
			i = child;
		}else
			break;
	}
	heap[i] = x;
	return min;
}
