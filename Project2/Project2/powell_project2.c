//
//  main.c
//  Project2
//
//  Created by Rhys Powell on 6/7/16.
//  Copyright © 2016 Rhys Powell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define STACK_MAX 5

int *pageInput;
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
    if(S->size <STACK_MAX ){
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





int main(int argc, const char * argv[]) {
    if(argc == 1){
        printf("ERROR: No parameters, please try again.\n");
    } else {
        printf("Running tests with %s frames and %d pages.\n", argv[1], (argc-2));
        numFrames = atoi(argv[1]);
        pageInput = malloc(argc-2);
        for(int i =0; i < (argc-2); ++i){
            pageInput[i] = atoi(argv[i+2]);
            printf("slot %d has page %d\n",i,pageInput[i]);
        }
        
    }
}
