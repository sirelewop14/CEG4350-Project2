/*
 Rhys Powell
 CEG4350 Summer 2016
 Project 2: Paging Algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#define STACK_MAX 5

int *pageInput;
int numPages;
int numFrames;
int *stackSize;

struct Stack{
    int data[STACK_MAX];
    int size;
};

typedef struct Stack Stack;

void stackInit(Stack *S){
    S->size = 0;
}

int top(Stack *S){
    if(S->size == 0){
        //Stack Empty
        return 0;
    }
    return S->data[S->size-1];
}

void push(Stack *S, int val){
    if(S->size < STACK_MAX){
        S->data[S->size++] = val;
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
    int faultCount = 0;
    
    int fifo[numFrames];
    
    int isPresent = 0;
    int slotTracker = 0;

    
    //Loop to insert all pages
    for(int i = 0; i < numPages; ++i){
        //Search for current page in frames.
        for (int j =0; j < numFrames; ++j){
            if(fifo[j] == pageInput[j]){
                //No fault, value is already in frame.
                isPresent = 1;
            }
        }
        //if it is NOT present
        if(isPresent == 0){
            faultCount++;
            fifo[slotTracker] = pageInput[i];
            for(int j = 0; j < slotTracker; ++j){
                printf("%d",fifo[slotTracker]);
            }
            if (slotTracker < numFrames){
                slotTracker++;
            } else {
                slotTracker = 0;
            }
        }
    }
}





int main(int argc, const char * argv[]) {
    if(argc == 1){
        printf("ERROR: No parameters, please try again.\n");
    } else {
        printf("Running tests with %s frames and %d pages.\n", argv[1], (argc-2));
        numFrames = atoi(argv[1]);
        pageInput = malloc(argc-2);
        numPages = (argc-2);
        for(int i =0; i < (argc-2); ++i){
            pageInput[i] = atoi(argv[i+2]);
           // printf("slot %d has page %d\n",i,pageInput[i]);
        }
        
    }
    fifo();
}
