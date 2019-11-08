/* Name: a6.c
 * Author: Will St. Onge
 * Description: Program that fills bins with items using the first fit approach where you put an item in a bin based on which one it can fit in first starting at the first bin on. The lists of items inside the bins are implement as linked lists with a name and weight associated with them. These linked lists are sorted in alphabetically order by name a->z. This program also includes a print function which traverses through the bin items and prints them out in a formatted fashion and a destroy function which frees up the memory of the linked list and sets the items pointer to null.
 */ 

#include <stdio.h>			// For console output.
#include <string.h>			// For the strncmp fucntion so I can compare where 2 words are alphabetically.
#include <stdlib.h>			// For memory allocation/deallocation functions.

#define BINS 20 // Size of bin array.
#define INPUTS 18 // Number of items entered.

// Linked list that contains a name and weight of the item as well as the next item in the list.
struct node
{
	char *name;
	double weight;
	struct node* next;
};

// Bin data structure that has a linked list of items and a total capacity for that bin. Items acts as a head pointer.
struct bin
{
	double capacity;
	struct node* items;
};

void firstFit(struct bin*); // Algorithm for inserting a new item into a bins based on user input.
void insert(struct bin*, char*, double); // Insert the item into the list inside of bin making sure it is in alphabetical order.
void print(struct bin*, int); // Traverses and outputs all items in the list inside of the bin as well as the total weight of the items.
void destory(struct bin*); // Deallocates the list inside the bin and sets the items pointer to NULL.

int main()
{
	// Declare array of bins of size BINS.
	struct bin bins[BINS];
	// Number of bins used.
	int i = 0;

	// Run the first fit algorithm.
	firstFit(bins);

	// Prints out all the bins with items in them.
	for (i = 0; i < BINS; i++)
		if ((bins + i)->items)
			print(bins + i, i);
		else
			break;

	// Prints total number of bins used.
	printf("Number of bins used: %d", i);
}

// Gets user inputs for the item names and weights, then adds them to the bins based on the first fit algorithm.
void firstFit(struct bin *bins)
{
	// Name and weight of current item being inserted.
	char* name;
	double weight;

	// Current bin the function is looking at. Used for iteration.
	struct bin* currentBin;

	// Hardcoded names and weight of items.
	char* names[] = { "Computer Organization", "Internet_Infrastructure", "The_History_Of_The_Universe", "Linux_with_Operating_Systems_Concepts", "C_Programming", "Statistics", "English_For_Dummies", "American_History_2000-","Computer_Architecture", "Hitchhiker's_Guide", "English-Minbari_Dictionary", "Zen_and_the_Art_of_Programming","The_Joy_of_Cooking", "Heart_of_Darkness", "Cincinnati_Yellow_Pages", "Artificial_Intelligence","Business_Programming:__Why?", "The_History_of_Ohio_State_Buckeyes" };
	double weights[] = { .75, .62, .27, .78, .21, .41, .55, .20, .90, .23, .42, .33, .56, .18, .98, .32, .12, .82 };

	// Loops all through all bins and reset their values to default.
	for (int i = 0; i < BINS; i++)
	{
		currentBin = bins + i;
		currentBin->capacity = 1.0;
		currentBin->items = NULL;
	}

	// Loop through all inputs.
	for (int i = 0; i < INPUTS; i++)
	{
		// Get the i-th name and weight in the 'arrays'.
		name = *(names + i);
		weight = *(weights + i);

		// Find the first bin that the element will fit in, then insert the element into the linked list.
		for (int j = 0; j < BINS; j++)
		{
			currentBin = bins + j;
			if (weight < currentBin->capacity + .001)
			{
				insert(currentBin, name, weight);
				break;
			}
		}
	}
}

// Insert the item into the list inside of bin making sure it is in alphabetical order. Takes a bin pointer, string (character pointer), and a double as inputs.
void insert(struct bin* bin, char* name, double weight)
{
	// Allocate and initialize a new node.
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->name = name;
	newNode->weight = weight;
	newNode->next = NULL;

	// Decrease the remaining capacity of the bin.
	bin->capacity -= weight;

	// If there are no items in the bin, set the items pointer in the bin to the new node.
	if (bin->items == NULL)
		bin->items = newNode;
	// Search through the bin to see where the node will go so the linked list stays in alphabetical order.
	else
	{
		// Temp pointers for linked list insertion.
		struct node* currentNode = bin->items;
		struct node* previousNode = NULL;

		// Loop through each node to find the proper spot for the new node.
		while (currentNode != NULL)
		{
			// Compare the new nodes name and the current nodes name to determine where the new node should be placed.
			int result = strcmp(name, currentNode->name);

			// New nodes name is higher alphabetically than the current nodes name, keep looping.
			if (result > 0)
			{
				previousNode = currentNode;
				currentNode = currentNode->next;
			}
			// New node is lower alphabetically than or the same as the current nodes name, insert the item after the previous node. If the strings are the same, order doesn't matter between them.
			else
			{
				newNode->next = currentNode;

				// Make sure not to dereference a null pointer.
				if (previousNode == NULL)
					bin->items = newNode;
				else
					previousNode->next = newNode;
				return;
			}
		}
		// New nodes name is greater than all items currently in the list, throw it at the end.
		previousNode->next = newNode;
	}
}

// Free the list's memory inside the bin and sets the items pointer to NULL. Takes a bin pointer as an input.
void destory(struct bin* bin)
{
	// Temp pointers for looping through the linked list.
	struct node* nextNode, *currentNode = bin->items;

	// Loop through all items in the linked list and deallocate the memory.
	while (currentNode != NULL)
	{
		nextNode = currentNode->next;
		free(currentNode);
		currentNode = nextNode;
	}

	// Reset bin values to default.
	bin->items = NULL;
	bin->capacity = 1.0;
}

// Traverses and outputs all items in the list inside of the bin as well as the total weight of the items. Takes a bin as an input.
void print(struct bin* bin, int num)
{
	// Pointer to the linked list of items inside the bin.
	struct node* currentNode = bin->items;

	// Output the bin number and the beginning of the list.
	printf("Bin %d:\nItems in the list: [", num);

	// Print the current nodes name until the current node is null.
	while (currentNode != NULL)
	{
		// Print a comma and space if the node is not the last item in the list then go to the next node.
		currentNode->next == NULL ? printf("\"%s\"", currentNode->name) : printf("\"%s\", ", currentNode->name);
		currentNode = currentNode->next;
	}

	// Print out the remaining capacity of the bin rounded to the hundredths place.
	printf("]\nRemaining capacity of the bin is %.2f\n\n", bin->capacity);
}