/* 
* Filename: main.c
* Description: Launches the program to simulate a vector calculator. Many operations are supported as well as
* vector-specfic operations.
* Date: 10/10/25
* Compile Info: make
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

#define MEM_SIZE 10
//Put clear, remove, list, and help here
int main() 
{
    vector memory[MEM_SIZE];
    char textstr_array[10][10];
    char *seq;
    
    char *token;
    int elements = 0;
    int arg;
    int error;
    bool rewritten;
    
    vector temp;
    printf("Welcome to the Vector Calculator!\n");
    printf("Valid inputs have spaces after each word/character (including the last char)\n");
    printf("Add, Subtract, Scalar Mult, Dot Product, Cross Product, and Declaration are all availiable functions.");

    while (1)
    {
        printf("\n> ");
        arg = 0;
        error = 0;
        rewritten = false;
        char userinput[50];

        //Receive input
        fgets(userinput, 50, stdin);
        
        //Copy userinput for future use
        char userinputcpy[50];
        strcpy(userinputcpy, userinput);
        if (strcmp(userinput, "quit\n") == 0)     //quit, with enter key
        {
            return 0;
        }
        token = strtok(userinput, " ");
        //Get all text between spaces
        while(token != NULL) 
        {
            strcpy(textstr_array[arg], token);
            token = strtok(NULL, " ");
            arg++;
            
        }
        //Find the sequence
        seq = sequence(textstr_array, arg);
        //Remove excess enter from console input
        seq[strlen(seq) - 1] = '\0';


        //Case 1: Vector
        if (strcmp(seq, "v") == 0)   
        {
            printvector(*getVector(memory, textstr_array[0]));
        }

        //Case 2: Vector = float float float
        else if (strcmp(seq, "v=fff") == 0)   
        {
            //Check mem full
            if (elements < 10)
            {
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    
                    memory[i] = create(strtof(textstr_array[2], NULL), strtof(textstr_array[3], NULL), strtof(textstr_array[4], NULL), textstr_array[0]);
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if (!rewritten)
            {
            memory[elements] = create(strtof(textstr_array[2], NULL), strtof(textstr_array[3], NULL), strtof(textstr_array[4], NULL), textstr_array[0]);
            elements++;
            printvector(*getVector(memory, textstr_array[0]));
            } 
            }
            else
            {
                printf("Memory Full.");
            }
        }

        //Case 3.1: Vector + Vector
        else if (strcmp(seq, "v+v") == 0)   
        {
            temp = add(getVector(memory, textstr_array[0]), getVector(memory, textstr_array[2]), "ans"); 
            printvector(temp);
        }

        //Case 3.2: Vector - Vector
        else if (strcmp(seq, "v-v") == 0)   
        {
            temp = sub(getVector(memory, textstr_array[0]), getVector(memory, textstr_array[2]), "ans "); 
            printvector(temp);
        }

        //Case 3.3: Vector . Vector
        else if (strcmp(seq, "v.v") == 0)   
        {
            printf("ans = %f", dotprod(getVector(memory, textstr_array[0]), getVector(memory, textstr_array[2]))); 
        }

        //Case 3.4: Vector X Vector
        else if (strcmp(seq, "vXv") == 0)   
        {
            temp = crosprod(getVector(memory, textstr_array[0]), getVector(memory, textstr_array[2]), "ans"); 
            printvector(temp);
        }

        //Case 4.1: Vector = Vector + Vector
        else if (strcmp(seq, "v=v+v") == 0)   
        {
            //Check mem full
            if (elements < 10)
            {
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    memory[i] = add(getVector(memory, textstr_array[2]), getVector(memory, textstr_array[4]), textstr_array[0]);
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if(!rewritten) {
                memory[elements] = add(getVector(memory, textstr_array[2]), getVector(memory, textstr_array[4]), textstr_array[0]);
                elements++;
                printvector(*getVector(memory, textstr_array[0]));
            }
            }
            else 
            {
                printf("Memory Full.");
            }
        }

        //Case 4.2: Vector = Vector - Vector
        else if (strcmp(seq, "v=v-v") == 0)   
        {
            //Check mem full
            if (elements < 10)
            {
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    memory[i] = sub(getVector(memory, textstr_array[2]), getVector(memory, textstr_array[4]), textstr_array[0]);
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if (!rewritten)
            {
                memory[elements] = sub(getVector(memory, textstr_array[2]), getVector(memory, textstr_array[4]), textstr_array[0]);
                elements++;
                printvector(*getVector(memory, textstr_array[0]));
            }
            }
            else 
            {
                printf("Memory Full.");
            }
        }

        //Case 4.4: Vector = Vector X Vector
        else if (strcmp(seq, "v=vXv") == 0)   
        {
            //Check mem full
            if (elements < 10)
            {
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    memory[i] = crosprod(getVector(memory, textstr_array[2]), getVector(memory, textstr_array[4]), textstr_array[0]);
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if (!rewritten) {
            memory[elements] = crosprod(getVector(memory, textstr_array[2]), getVector(memory, textstr_array[4]), textstr_array[0]);
            elements++;
            printvector(*getVector(memory, textstr_array[0]));
            }
            }
            else 
            {
                printf("Memory Full.");
            }
        }

        //Case 5.1: Vector = Vector * float (Communitive)
        else if (strcmp(seq, "v=v*f") == 0)   
        {
            //Check mem full
            if (elements < 10)
            {
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    memory[i] =  mult(strtof(textstr_array[4], NULL), getVector(memory, textstr_array[2]), textstr_array[0]); 
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if (!rewritten) {
            memory[elements] = mult(strtof(textstr_array[4], NULL), getVector(memory, textstr_array[2]), textstr_array[0]); 
            elements++;
            printvector(*getVector(memory, textstr_array[0]));
            }
            }
            else
            {
                printf("Memory Full.");
            }
        }
        //Case 5.2
        else if (strcmp(seq, "v=f*v") == 0)   
        {
            //Check mem full
            if (elements < 10)
            {
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    memory[i] =  mult(strtof(textstr_array[2], NULL), getVector(memory, textstr_array[4]), textstr_array[0]); 
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if (!rewritten){
            memory[elements] = mult(strtof(textstr_array[2], NULL), getVector(memory, textstr_array[4]), textstr_array[0]); 
            elements++;
            printvector(*getVector(memory, textstr_array[0]));
            }
        }
            else
            {
                printf("Memory Full");
            }
        }

        //Case 6.1: Vector * float (Comunitive)
        else if (strcmp(seq, "v*f") == 0)   
        {
            temp = mult(strtof(textstr_array[2], NULL), getVector(memory, textstr_array[0]), "ans"); 
            printvector(temp);
        }
        //Case 6.2
        else if (strcmp(seq, "f*v") == 0)   
        {
            temp = mult(strtof(textstr_array[0], NULL), getVector(memory, textstr_array[2]), "ans"); 
            printvector(temp);
        }
        //Case: help
        else if (strcmp(userinputcpy, "help\n") == 0)     //Help case
        {
            printf("\nBelow is a list of supported functions. Make sure to include spaces in between each argument, even after the last one.\n");
            printf("- Assignment: Vector = Num Num Num\n");
            printf("- Addition: Vector + Vector (with assignment functionality)\n");
            printf("- Subtraction: Vector - Vector (with assignment functionality)\n");
            printf("- Scalar Multiplication: Vector * Num (communitive with assignment functionality)\n");
            printf("- Dot Product: Vector . Vector\n");
            printf("- Cross Product: Vector X Vector (with assignment functionality)\n");
        }
        //Case: list
        else if (strcmp(userinputcpy, "list\n") == 0)     //list case
        {
            for (int i = 0; i < elements; i++)
            {
                printvector(memory[i]);
                printf("\n");
            }
        }
        //Case: clear
        else if (strcmp(userinputcpy, "clear\n") == 0)     //list case
        {
            memset(memory, 0, sizeof(memory));
            elements = 0;
        }
        //Case 0: Error/Invalid Input
        else 
        {
            printf("Invailid input. Try typing help. Also make sure to have spaces in between each character \nand only using supported functions.\n");
        }        
        free(seq);
    }
    return 0;

}
