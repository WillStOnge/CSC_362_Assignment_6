/* Name: a6.c
 * Author: Will St. Onge
 * Description: 
 */ 

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// LinkedList data structure that contains a name and weight of the item as well as the next item in the list.
struct item
{
	char* name;
	int weight;
	struct item* next;
};

// Bin data structure that has a list of items and a total capacity. Used in an array to have multiple bins for storing items
struct bin
{
	int totalWeight;
	struct item* items;
} bins[20];

void insert(struct bin*, struct item*); // Insert the item into the list inside of bin making sure it is in alphabetical order.
void traverse(struct bin*); // Traverses and outputs all items in the list inside of the bin.
void destory(struct bin*); // Deallocates the list inside the bin and sets the items pointer to NULL.

// Entry point for the program
int main()
{
	
}

// Gets user inputs for the item names and weights, then adds them to the bins based on the first fit algorithm.
void firstFit(struct bin *bins[20])
{

}

// Insert the item into the list inside of bin making sure it is in alphabetical order.
void insert(struct bin* bin, struct item* item)
{

}

// Traverses and outputs all items in the list inside of the bin.
void traverse(struct bin* bin)
{

}

// Deallocates the list inside the bin and sets the items pointer to NULL.
void destory(struct bin* bin)
{

}