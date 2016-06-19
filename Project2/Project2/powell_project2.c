//
//  main.c
//  Project2
//
//  Created by Rhys Powell on 6/7/16.
//  Copyright © 2016 Rhys Powell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int *pageInput;
int numFrames;

struct Stack{
    int data[50];
    int size;
};
typedef struct Stack Stack;







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
