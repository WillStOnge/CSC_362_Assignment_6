/* Name: a6.c
 * Author: Will St. Onge
 * Description: 
 */ 

#define _CRT_SECURE_NO_WARNINGS

// Size of bin array
#define BINS 20
#define INPUTS 8

#include <stdio.h>
#include <string.h>

// LinkedList data structure that contains a name and weight of the item as well as the next item in the list.
struct node
{
	char name[40];
	double weight;
	struct node* next;
};

// Bin data structure that has a list of items and a total capacity. Used in an array to have multiple bins for storing items
struct bin
{
	double capacity;
	struct node* items;
} bins[BINS];

void firstFit(); // Algorithm for inserting a new item into a bins based on user input.
void insert(struct bin*, char*, int); // Insert the item into the list inside of bin making sure it is in alphabetical order.
void traverse(struct bin*); // Traverses and outputs all items in the list inside of the bin.
void destory(struct bin*); // Deallocates the list inside the bin and sets the items pointer to NULL.

// Entry point for the program
int main()
{
	struct node nodes[10];
	struct node node = { "test1", 1.0, &node};
	bins->items = nodes;

	firstFit();
}

// Gets user inputs for the item names and weights, then adds them to the bins based on the first fit algorithm.
void firstFit()
{
	int binCount = 0;
	char* name;
	double weight;
	struct bin* currentBin;
	char* names[] = { "Vase", "Bowling ball", "Book", "Umbrella", "Gold medal", "Speaker 1", "Walkman", "Speaker 2" };
	double weights[] = { .5, .9, .3, .4, .7, .4, .2, .4 };

	// Initialize all the bins in the bin array. Set linked list pointer to NULL and capacity to 1.
	for (int i = 0; i < BINS; i++)
	{
		currentBin = bins + i;
		currentBin->capacity = 1.0;
		currentBin->items = NULL;
	}

	for (int i = 0; i < INPUTS; i++)
	{
		name = names[i];
		weight = weights[i];

		for (int j = 0; j < BINS; j++)
		{
			currentBin = bins + j;
			if (weight < currentBin->capacity + .001)
				insert(currentBin, name, weight);
		}
	}
}

// Insert the item into the list inside of bin making sure it is in alphabetical order.
void insert(struct bin* bin, char* name, int weight)
{
	// Make a new node
	struct node newNode = {name, weight, NULL};

	if (bin->items == NULL)
		bin->items = &newNode;
	else
	{
		// Search through the bin to see where node will fit
	}

	bin->capacity -= weight;
}

// Traverses and outputs all items in the list inside of the bin.
void traverse(struct bin* bin)
{

}

// Deallocates the list inside the bin and sets the items pointer to NULL.
void destory(struct bin* bin)
{
	free(bin->items);
}