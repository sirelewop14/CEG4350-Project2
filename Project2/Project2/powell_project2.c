/*
 Rhys Powell
 CEG4350 Summer 2016
 Project 2: Paging Algorithms
 */

//Standard includes and define max number of frames
//for memory allocation.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_FRAMES 10

int pageInput[50];
int numPages;
int numFrames;

/**
 *  The Stack struct definition.
 */
struct Stack{
	int data[MAX_FRAMES];
	int size;
};

typedef struct Stack Stack;

/**
 *  The stackInit function simply intitializes the Stack with default values.
 *	For this project, the default value is -1 since this is not a valid page number.
 *
 *  @param S - The stack to initialize.
 */
void stackInit(Stack *S){
	S->size = 0;
	for (int i = 0; i < MAX_FRAMES; i++){
		S->data[i] = -1;
	}
}

/**
 *  The push function adds a value to the stack. The value is added to the top of the stack and 
 *  the any values that are already in the stack get pushed down one slot.
 *
 *  @param S   S is the stack on which to push the value.
 *  @param val val is the integer value to add to the top of the stack.
 */
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

/**
 *  The FIFO function runs a simulation of the First In, First Out paging algorithm
 *  and prints out the page hits, faults, and frame values as it runs.
 */
void fifo(){
	printf("Starting FIFO\n---------------------\n");
	//Set up variables and stuff
	Stack fifo;
	stackInit(&fifo);
	
	int isPresent = 0;
	int faultCount = 0;
	
	//Loop through the pages
	for(int i = 0; i < numPages; i++){
		//Search through current pages
		for (int j = 0; j < numFrames; ++j){
			if(fifo.data[j] == pageInput[i]){
				//No fault, value is already in frame.
				isPresent = 1;
				for(int k = 0; k < fifo.size; k++){
					printf("%d,", fifo.data[k]);
				}
				printf("\n");
			}
		}//End Search
		if(isPresent == 0){
			//is NOT present
			faultCount++;
			push(&fifo,pageInput[i]);
			for(int j = 0; j < fifo.size; j++){
				printf("%d,", fifo.data[j]);
			}
			printf("*\n");
		}
		isPresent = 0;
	}
	printf("--------------------------------------\n");
	printf("FIFO: Total number of Page Faults: %d\n", faultCount);
}

/**
 *  The Optimal function runs a simulation of the Optimal paging algorithm.
 *  It searches through the pages that are passed in as arguments at the programs beginning.
 *  After searching through the pages, it determines the best times to swap certain frames
 *  in and out to provide the lowest number of page faults. This algorithm is purely for testing,
 *  as a developer would need to be able to predict the future to implement this algorthim. It is
 *  "The Best Case Scenario"
 */
void optimal(){
	printf("Starting Optimal\n---------------------\n");
	//Set up variables and stuff
	int opt[MAX_FRAMES];
	
	for (int i = 0; i < MAX_FRAMES; i++){
		opt[i] = -1;
	}
	
	int isPresent = 0;
	int faultCount = 0;
	int slotTracker = 0;
	int distance = 0;
	int victimTracker[MAX_FRAMES];
	
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
					printf("%d,", opt[j]);
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
					printf("%d,", opt[j]);
				}
				printf("*\n");
			}
		} else {
			//Prints if no fault
			for(int j = 0; j < numFrames; j++){
				printf("%d,", opt[j]);
			}
			printf("\n");
			isPresent = 0;
		}
	}
	printf("--------------------------------------\n");
	printf("Optimal: Total number of Page Faults: %d\n", faultCount);}

/**
 *  The LRU function runs a simulation of the paging algorithm Least Recently Used.
 *  The function determines the page frame that was used the least recently and selects 
 *  it as the victim frame when a page fault occurs.
 */
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
				//move page hit to top of stack
				int temp = lru.data[j];
				int temp2 = lru.data[0];
				lru.data[0] = temp;
				lru.data[j] = temp2;
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
	printf("LRU: Total number of Page Faults: %d\n", faultCount);
}

/**
 *  The LFU function performs a paging simulation of the Least Frequently Used algorithm.
 *  This algorithm keeps a count of how often each page is used (Hit) after it is loaded into
 *  a frame. The algorithm then selects the frame that has the lowest hit count as the victim
 *  frame when a page fault occurs.
 */
void lfu(){
	printf("Starting LFU\n---------------------\n");
	//Set up parallel arrays.
	int lfuVals[MAX_FRAMES];
	int lfuCounts[MAX_FRAMES];
	//Initialize the arrays with default values.
	for (int i = 0; i < MAX_FRAMES; i++){
		lfuVals[i] = -1;
		lfuCounts[i] = 0;
	}
	
	int isPresent = 0;
	int lowestSlot = -1;
	int lowestCount = 99;
	int faultCount = 0;
	
	//Loop through pages
	for(int i = 0; i < numPages; i++){
		//loop through frames for search
		for(int j = 0; j < numFrames; j++){
			if(pageInput[i] == lfuVals[j]){
				//page hit, increment counter
				isPresent = 1;
				lfuCounts[j]++;
				for(int k = 0; k < numFrames; k++){
					printf("%d,",lfuVals[k]);
				}
				printf("\n");
			}
		}
		//This makes sure that the frames are full
		if(faultCount < numFrames && isPresent == 0 ){
			lfuVals[i] = pageInput[i];
			faultCount++;
			for(int k = 0; k < numFrames; k++){
				printf("%d,",lfuVals[k]);
			}
			printf("*\n");
		//Once all the frames are full we can start looking for victims
		} else if(isPresent == 0){
			//we have to perform replacment
			faultCount++;
			for(int j = 0; j < numFrames; j++){
				//search through loaded frames to find lowest count
				if(lfuCounts[j] < lowestCount){
					lowestSlot = j;
					lowestCount = lfuCounts[j];
				}
			}
			lfuVals[lowestSlot] = pageInput[i];
			lfuCounts[lowestSlot] = 0;
			for(int k = 0; k < numFrames; k++){
				printf("%d,",lfuVals[k]);
			}
			printf("*\n");
		}
		isPresent = 0;
	}
	printf("--------------------------------------\n");
	printf("LFU: Total number of Page Faults: %d\n", faultCount);
}

/**
 *  The MFU function performs the Most Frequently Used paging algorithm simulation. The Most
 *  Frequently Used algorithm functions almost identically to the LFU function, and only differs
 *  in its selection of the victim frame. In stead of slecting the frame with the lowest hit count,
 *  it selects the frame with the highest hit count as the victim frame when a page fault occurs.
 */
void mfu(){
	printf("Starting MFU\n---------------------\n");
	//Set up parallel arrays
	int mfuVals[MAX_FRAMES];
	int mfuCounts[MAX_FRAMES];
	//Initialize the arrays with default values
	for (int i = 0; i < MAX_FRAMES; i++){
		mfuVals[i] = -1;
		mfuCounts[i] = 0;
	}
	
	int isPresent = 0;
	int highestSlot = -1;
	int highestCount = 99;
	int faultCount = 0;
	
	//Loop through pages
	for(int i = 0; i < numPages; i++){
		//loop through frames for search
		for(int j = 0; j < numFrames; j++){
			if(pageInput[i] == mfuVals[j]){
				//page hit, increment counter
				isPresent = 1;
				mfuCounts[j]++;
				for(int k = 0; k < numFrames; k++){
					printf("%d,",mfuVals[k]);
				}
				printf("\n");
			}
		}
		//Ensure the frames are full
		if(faultCount < numFrames && isPresent == 0 ){
			mfuVals[i] = pageInput[i];
			faultCount++;
			for(int k = 0; k < numFrames; k++){
				printf("%d,",mfuVals[k]);
			}
			printf("*\n");
		//Once all the frames are full we can do victim selection
		} else if(isPresent == 0){
			//we have to perform replacment
			faultCount++;
			for(int j = 0; j < numFrames; j++){
				//search through loaded frames to find highest count
				if(mfuCounts[j] > highestCount){
					highestSlot = j;
					highestCount = mfuCounts[j];
				}
			}
			mfuVals[highestSlot] = pageInput[i];
			mfuCounts[highestSlot] = 0;
			for(int k = 0; k < numFrames; k++){
				printf("%d,",mfuVals[k]);
			}
			printf("*\n");
		}
		isPresent = 0;
	}
	printf("--------------------------------------\n");
	printf("MFU: Total number of Page Faults: %d\n", faultCount);
}

/**
 *  The main function. This function is the bread and butter of the whole operation.
 *  The main function takes input from the user and processes it into frame numbers 
 *  and page values. The page values get stored into an array, and the number of frames
 *  determines the size of the stacks and arrays used for simulations of the paging 
 *  algorithms.
 *
 *  @param argc An integer value which indicates the number of arguments passed to the 
 *				program at run-time. 0 is the program itself, 1 is the number of frames,
 *				2-n are the page values.
 *  @param argv A char array that contains the values of the arguments passed to the program.
 *
 *  @return returns and int value showing how the program exited.
 */
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
	lfu();
	mfu();
}
