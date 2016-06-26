/*
 Rhys Powell
 CEG4350 Summer 2016
 Project 2: Paging Algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define STACK_MAX 5
#define ARRAY_MAX 3

//int *pageInput;
int pageInput[50];
int numPages;
int numFrames;


struct Stack{
	int data[STACK_MAX];
	int size;
};

typedef struct Stack Stack;

void stackInit(Stack *S){
	S->size = 0;
	for (int i = 0; i < STACK_MAX; i++){
		S->data[i] = -1;
	}
}

int top(Stack *S){
	if(S->size == 0){
		//Stack Empty
		return 0;
	}
	return S->data[S->size-1];
}

void push(Stack *S, int val){
	if(S->size < numFrames){
		S->data[S->size++] = val;
	} else {
		for(int i = S->size-1; i > 0; i--){
			S->data[i] = S->data[i-1];
		}
		S->data[0] = val;
	}
}

int pop(Stack *S){
	if(S->size == 0){
		//Stack empty
	} else {
		int retVal = S->data[S->size-1];
		S->size--;
		return retVal;
	}
	return 0;
}

void fifo(){
	//FIFO Structure
	printf("\nStarting FIFO\n-----------------------\n");
	int faultCount = 0;
	int fifo[ARRAY_MAX] = {-1,-1,-1};
	//int fifo[numFrames];
	int isPresent = 0;
	int slotTracker = 0;
	//Loop to insert all pages
	for(int i = 0; i < numPages; ++i){
		//Search for current page in frames.
		for (int j =0; j < numFrames; ++j){
			if(fifo[j] == pageInput[i]){
				//No fault, value is already in frame.
				isPresent = 1;
			}
		}
		//if it is NOT present
		if(isPresent == 0){
			faultCount++;
			fifo[slotTracker] = pageInput[i];
			for(int j = 0; j <= slotTracker; ++j){
				printf("%d,",fifo[j]);
			}
			printf("*\n");
			if (slotTracker < numFrames - 1){
				slotTracker++;
			} else {
				slotTracker = 0;
			}
		} else {
			for(int k = 0; k < numFrames; k++){
				printf("%d,",fifo[k]);
			}
			printf("\n");
		}
		isPresent = 0;
	}
	printf("--------------------------------------\n");
	printf("FIFO: Total number of Page Faults: %d\n",faultCount);
}

void optimal(){
	printf("Starting Optimal\n---------------------\n");
	//Set up variables and stuff
	int opt[ARRAY_MAX] = {-1,-1,-1};
	
	int isPresent = 0;
	int faultCount = 0;
	int slotTracker = 0;
	int distance = 0;
	int victimTracker[ARRAY_MAX];
	
	//Loop through the pages
	for(int i = 0; i < numPages; i++){
		//Search through current pages
		for (int j = 0; j < numFrames; ++j){
			if(opt[j] == pageInput[i]){
				//No fault, value is already in frame.
				isPresent = 1;
			}
		}//End Search
		//If it is NOT present
		if(isPresent == 0){
			faultCount++;
			if(i >= numFrames){
				//This means that all frames are full
				//and we need to perform a replacement
				for(int k =0; k < numFrames; k++){ //Loops through frames
					for(int j = i; j < numPages; j++){ //loops through pages
						//Search through pages to see
						//which value is the farthest away from being used
						if(opt[k]!= pageInput[j]){
							//Increment to show how far away the value is.
							distance++;
						} else {
							break;
						}
					}
					//Array to store the values of distance for victims
					victimTracker[k] = distance;
					distance = 0;
				}
				//This will loop through the array of victims and find the
				//the slot with the highest value. This select the victim frame.
				int temp = -1;
				int tempSlot = -1;
				for(int k = 0; k < numFrames; k++){
					if(victimTracker[k] >= temp){
						//Shows the distance
						temp = victimTracker[k];
						//tracks the slot of victim
						tempSlot = k;
					}
				}
				opt[tempSlot] = pageInput[i];
				temp = -1;
				tempSlot = -1;
				for(int j = 0; j < numFrames; j++){
					printf("%d,",opt[j]);
				}
				printf("*\n");
			} else {
				//nothing in frames, load page in.
				opt[slotTracker] = pageInput[i];
				//Make sure we stay in bounds of index
				if(slotTracker + 1 == numFrames){
					slotTracker = 0;
				} else {
					slotTracker++;
				}
				for(int j = 0; j < numFrames; j++){
					printf("%d,",opt[j]);
				}
				printf("*\n");
			}
		} else {
			//Prints if no fault
			for(int j = 0; j < numFrames; j++){
				printf("%d,",opt[j]);
			}
			printf("\n");
			isPresent = 0;
		}
	}
	printf("--------------------------------------\n");
	printf("Optimal: Total number of Page Faults: %d\n",faultCount);}

void lru(){
	printf("Starting LRU\n---------------------\n");
	//Set up variables and stuff
	Stack lru;
	stackInit(&lru);
	
	int isPresent = 0;
	int faultCount = 0;
	
	//Loop through the pages
	for(int i = 0; i < numPages; i++){
		//Search through current pages
		for (int j = 0; j < numFrames; ++j){
			if(lru.data[j] == pageInput[i]){
				//No fault, value is already in frame.
				isPresent = 1;
				for(int k = 0; k < lru.size; k++){
					printf("%d,",lru.data[k]);
				}
				printf("\n");
			}
			
		}//End Search
		if(isPresent == 0){
			//is NOT present
			faultCount++;
			push(&lru,pageInput[i]);
			for(int j = 0; j < lru.size; j++){
				printf("%d,",lru.data[j]);
			}
			printf("*\n");
		}
		isPresent = 0;
	}
	printf("--------------------------------------\n");
	printf("LRU: Total number of Page Faults: %d\n",faultCount);
}


void lfu(){
	
}
void mfu(){
	
}



int main(int argc, const char * argv[]) {
	if(argc == 1){
		printf("ERROR: No parameters, please try again.\n");
		exit(0);
	} else if(argc == 2){
		printf("ERROR: Not enough parameters, please try again.\n");
		exit(0);
	} else {
		if(0!=isdigit((int)argv[1])){
			printf("ERROR: Not numeric parameters, please try again.\n");
			exit(0);
		}
		printf("Running tests with %s frames and %d pages.\n", argv[1], (argc-2));
		numFrames = atoi(argv[1]);
		numPages = (argc-2);
		printf("Page input: ");
		for(int i =0; i < (argc-2); ++i){
			if(0!=isdigit((int)argv[i+2])){
				printf("ERROR: Not numeric parameters, please try again.\n");
				exit(0);
			}
			pageInput[i] = atoi(argv[i+2]);
			printf("%d ",pageInput[i]);
		}
	}
	fifo();
	optimal();
	lru();
}
