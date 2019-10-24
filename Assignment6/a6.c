/* Name: a6.c
 * Author: Will St. Onge
 * Description: Program that fills bins with items using the first fit approach where you put an item in a bin based on which one it can fit in first starting at the first bin on. The lists of items inside the bins are implement as linked lists with a name and weight associated with them. These linked lists are sorted in alphabetically order by name a->z. This program also includes a print function which traverses through the bin items and prints them out in a formatted fashion and a destroy function which frees up the memory of the linked list and sets the items pointer to null.
 */ 

#include <stdio.h>
#include <string.h>

#define BINS 20 // Size of bin array
#define INPUTS 18 // Number of items entered

// Linked list that contains a name and weight of the item as well as the next item in the list.
struct node
{
	char *name;
	double weight;
	struct node* next;
};

// Bin data structure that has a linked list of items and a total capacity for that bin.
struct bin
{
	double capacity;
	struct node* items;
} bins[BINS]; // Declares array for the bins to be stored in.

void firstFit(); // Algorithm for inserting a new item into a bins based on user input.
void insert(struct bin*, char*, double); // Insert the item into the list inside of bin making sure it is in alphabetical order.
void print(struct bin*, int); // Traverses and outputs all items in the list inside of the bin as well as the total weight of the items.
void destory(struct bin*); // Deallocates the list inside the bin and sets the items pointer to NULL.

int main()
{
	// Number of bins used;
	int count = 0;

	// Run the first fit algorithm
	firstFit();

	// Prints out all the bins with items in them
	for (int i = 0; i < BINS; i++)
		if ((bins + i)->items != NULL)
		{
			print(bins + i, i);
			count++;
		}

	printf("Number of bins used: %d", count);
}

// Gets user inputs for the item names and weights, then adds them to the bins based on the first fit algorithm.
void firstFit()
{
	int binCount = 0;
	char* name;
	double weight;
	struct bin* currentBin;
	char* names[] = { "Computer Organization", "Internet_Infrastructure", "The_History_Of_The_Universe", "Linux_with_Operating_Systems_Concepts", "C_Programming", "Statistics", "English_For_Dummies", "American_History_2000-","Computer_Architecture", "Hitchhiker's_Guide", "English-Minbari_Dictionary", "Zen_and_the_Art_of_Programming","The_Joy_of_Cooking", "Heart_of_Darkness", "Cincinnati_Yellow_Pages", "Artificial_Intelligence","Business_Programming:__Why?", "The_History_of_Ohio_State_Buckeyes" };
	double weights[] = { .75, .62, .27, .78, .21, .41, .55, .20, .90, .23, .42, .33, .56, .18, .98, .32, .12, .82 };

	// Loops all through all bins and reset their values to default.
	for (int i = 0; i < BINS; i++)
	{
		currentBin = bins + i;
		currentBin->capacity = 1.0;
		currentBin->items = NULL;
	}

	// Loop through all inputs
	for (int i = 0; i < INPUTS; i++)
	{
		// Get the i-th name and weight in the 'arrays'
		name = *(names + i);
		weight = *(weights + i);

		// Find the first bin that the element will fit in, then insert it into 
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
	// Allocate and initialize a new node
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->name = name;
	newNode->weight = weight;
	newNode->next = NULL;

	// Lower the left over capacity of the bin
	bin->capacity -= weight;

	// If there are no items in the bin, set the items pointer to the new node.
	if (bin->items == NULL)
		bin->items = newNode;
	// Search through the bin to see where node will fit
	else
	{
		// Temp pointer for linked list insertion
		struct node* currentNode = bin->items;
		struct node* previousNode = NULL;

		// Loop through each node to find the proper spot for the new node
		while (currentNode != NULL)
		{
			// Compare the strings to determine where the new node should be placed.
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

				// Make sure not to reference a null pointer
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
	// Temp pointers for looping through the linked list
	struct node* nextNode;
	struct node* currentNode = bin->items;

	// Loop through all items in the linked list and free the memory
	while (currentNode != NULL)
	{
		nextNode = currentNode->next;
		free(currentNode);
		currentNode = nextNode;
	}

	// Reset bin values
	bin->items = NULL;
	bin->capacity = 1.0;
}

// Traverses and outputs all items in the list inside of the bin as well as the total weight of the items. Takes a bin as an input.
void print(struct bin* bin, int num)
{
	struct node* node = bin->items;

	printf("Bin %d:\nItems in the list: [", num);

	// Print each item in the linked list
	while (node != NULL)
	{
		// Print a comma and space if it is node the last item in the list
		node->next == NULL ? printf("\"%s\"", node->name) : printf("\"%s\", ", node->name);
		node = node->next;
	}

	printf("]\nLeftover capacity of the bin is %.2f\n\n", bin->capacity);
}