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

#define INITIAL_MEM_SIZE 2
//Put clear, remove, list, and help here
int main() 
{
    vector *memory = malloc(INITIAL_MEM_SIZE * sizeof(vector));
    int curr_mem = INITIAL_MEM_SIZE;
    char textstr_array[10][10];
    char *seq;
    
    FILE *file_ptr;
    char *token;
    int elements = 0;
    int arg;
    int error;
    bool rewritten;
    
    //Used for returning ans and loading a csv file.
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
            free(memory);
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

        //Test Prints
        // printf("Number of args: %d\n", arg);
        // printf("%s", textstr_array[0]);
        // printf("%s\n",seq);

        //Validate vectors
        bool vector_found = false;
        bool no_search = false;
        if (seq[0] == 'v' && seq[1] == '=')
        {
            vector_found = true;
            no_search = true;
        }
        for (int i = 0; i < strlen(seq); i++)
        {
            if (no_search)
            {
                break;
            }
            if (seq[i] == 'v')
            {
                //Search Memory
                for(int j = 0; j < elements; j++)
                {
                    if(strcmp(textstr_array[i],memory[j].name) == 0)
                    vector_found = true;
                }
            }
        }
        if (!vector_found)
        {
            strcpy(seq,"ERROR");
        }





        //Case 1: Vector
        if (strcmp(seq, "v") == 0)   
        {
            printvector(*getVector(memory, textstr_array[0], curr_mem));
        }

        //Case 2: Vector = float float float
        else if (strcmp(seq, "v=fff") == 0)   
        {
            //Check mem full, then realloc
            if (elements >= curr_mem)
            {
                curr_mem *= 2;
                memory = (vector *) realloc(memory, curr_mem * sizeof(vector));
            }
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
            printvector(*getVector(memory, textstr_array[0], curr_mem));
            } 
            
        }

        //Case 3.1: Vector + Vector
        else if (strcmp(seq, "v+v") == 0)   
        {
            temp = add(getVector(memory, textstr_array[0], curr_mem), getVector(memory, textstr_array[2], curr_mem), "ans"); 
            printvector(temp);
        }

        //Case 3.2: Vector - Vector
        else if (strcmp(seq, "v-v") == 0)   
        {
            temp = sub(getVector(memory, textstr_array[0], curr_mem), getVector(memory, textstr_array[2], curr_mem), "ans "); 
            printvector(temp);
        }

        //Case 3.3: Vector . Vector
        else if (strcmp(seq, "v.v") == 0)   
        {
            printf("ans = %f", dotprod(getVector(memory, textstr_array[0], curr_mem), getVector(memory, textstr_array[2], curr_mem))); 
        }

        //Case 3.4: Vector X Vector
        else if (strcmp(seq, "vXv") == 0)   
        {
            temp = crosprod(getVector(memory, textstr_array[0], curr_mem), getVector(memory, textstr_array[2], curr_mem), "ans"); 
            printvector(temp);
        }

        //Case 4.1: Vector = Vector + Vector
        else if (strcmp(seq, "v=v+v") == 0)   
        {
            //Check mem full, then realloc
            if (elements >= curr_mem)
            {
                curr_mem *= 2;
                memory = (vector *) realloc(memory, curr_mem * sizeof(vector));
            }
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    memory[i] = add(getVector(memory, textstr_array[2], curr_mem), getVector(memory, textstr_array[4], curr_mem), textstr_array[0]);
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if(!rewritten) {
                memory[elements] = add(getVector(memory, textstr_array[2], curr_mem), getVector(memory, textstr_array[4], curr_mem), textstr_array[0]);
                elements++;
                printvector(*getVector(memory, textstr_array[0], curr_mem));
            }
        }

        //Case 4.2: Vector = Vector - Vector
        else if (strcmp(seq, "v=v-v") == 0)   
        {
            //Check mem full, then realloc
            if (elements >= curr_mem)
            {
                curr_mem *= 2;
                memory = (vector *) realloc(memory, curr_mem * sizeof(vector));
            }
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    memory[i] = sub(getVector(memory, textstr_array[2], curr_mem), getVector(memory, textstr_array[4], curr_mem), textstr_array[0]);
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if (!rewritten)
            {
                memory[elements] = sub(getVector(memory, textstr_array[2], curr_mem), getVector(memory, textstr_array[4], curr_mem), textstr_array[0]);
                elements++;
                printvector(*getVector(memory, textstr_array[0], curr_mem));
            }
        }

        //Case 4.4: Vector = Vector X Vector
        else if (strcmp(seq, "v=vXv") == 0)   
        {
            //Check mem full, then realloc
            if (elements >= curr_mem)
            {
                curr_mem *= 2;
                memory = (vector *) realloc(memory, curr_mem * sizeof(vector));
            }
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    memory[i] = crosprod(getVector(memory, textstr_array[2], curr_mem), getVector(memory, textstr_array[4], curr_mem), textstr_array[0]);
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if (!rewritten) {
            memory[elements] = crosprod(getVector(memory, textstr_array[2], curr_mem), getVector(memory, textstr_array[4], curr_mem), textstr_array[0]);
            elements++;
            printvector(*getVector(memory, textstr_array[0], curr_mem));
            }
        }

        //Case 5.1: Vector = Vector * float (Communitive)
        else if (strcmp(seq, "v=v*f") == 0)   
        {
            //Check mem full, then realloc
            if (elements >= curr_mem)
            {
                curr_mem *= 2;
                memory = (vector *) realloc(memory, curr_mem * sizeof(vector));
            }
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    memory[i] =  mult(strtof(textstr_array[4], NULL), getVector(memory, textstr_array[2], curr_mem), textstr_array[0]); 
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if (!rewritten) {
            memory[elements] = mult(strtof(textstr_array[4], NULL), getVector(memory, textstr_array[2], curr_mem), textstr_array[0]); 
            elements++;
            printvector(*getVector(memory, textstr_array[0], curr_mem));
            }
        }
        //Case 5.2
        else if (strcmp(seq, "v=f*v") == 0)   
        {
            //Check mem full, then realloc
            if (elements >= curr_mem)
            {
                curr_mem *= 2;
                memory = (vector *) realloc(memory, curr_mem * sizeof(vector));
            }
            //Check same name
            for (int i = 0; i < elements; i++) 
            {
                if (strcmp(textstr_array[0], memory[i].name) == 0) 
                {
                    memory[i] =  mult(strtof(textstr_array[2], NULL), getVector(memory, textstr_array[4], curr_mem), textstr_array[0]); 
                    printvector(memory[i]);
                    rewritten = true;
                }
            }
            if (!rewritten){
            memory[elements] = mult(strtof(textstr_array[2], NULL), getVector(memory, textstr_array[4], curr_mem), textstr_array[0]); 
            elements++;
            printvector(*getVector(memory, textstr_array[0], curr_mem));
            }
        }

        //Case 6.1: Vector * float (Comunitive)
        else if (strcmp(seq, "v*f") == 0)   
        {
            temp = mult(strtof(textstr_array[2], NULL), getVector(memory, textstr_array[0], curr_mem), "ans"); 
            printvector(temp);
        }
        //Case 6.2
        else if (strcmp(seq, "f*v") == 0)   
        {
            temp = mult(strtof(textstr_array[0], NULL), getVector(memory, textstr_array[2], curr_mem), "ans"); 
            printvector(temp);
        }
        //Case: Load
        else if(strcmp(textstr_array[0], "load") == 0 && arg == 3)
        {
            //"Call" the clear case
            free(memory);
            memory = malloc(INITIAL_MEM_SIZE * sizeof(vector));
            curr_mem = INITIAL_MEM_SIZE;
            elements = 0;

            //Store data in temp by reading .csv
            char directory[100];
            strcpy(directory, textstr_array[1]);
            file_ptr = fopen(directory, "r");
            char line[100];
            char *token_read;
            float new_x;
            float new_y;
            float new_z;
            char new_name[10];

            if (!file_ptr)
            {
                printf("Error reading file. Check if the file exists.\n");
            }
            else 
            {
                //Ignore Title
                fgets(line,99,file_ptr);
                printf("Line: %s", line);
                while(fgets(line,99,file_ptr))
                {
                    token_read = strtok(line,",");
                    strcpy(new_name,token_read);
                    printf("%s\n", new_name);

                    token_read = strtok(NULL, ",");
                    new_x = atof(token_read);
                    printf("%f\n", new_x);

                    token_read = strtok(NULL, ",");
                    new_y = atof(token_read);
                    printf("%f\n", new_y);

                    token_read = strtok(NULL, ",");
                    new_z = atof(token_read);
                    printf("%f\n", new_z);

                    //Mem Realloc
                    if (elements >= curr_mem)
                    {
                        curr_mem *= 2;
                        memory = (vector *) realloc(memory, curr_mem * sizeof(vector));
                    }
                    memory[elements] = create(new_x, new_y, new_z, new_name);
                    elements++;
                }
                fclose(file_ptr);
            }
            

        }
        
        //Case: Save
        else if(strcmp(textstr_array[0], "save") == 0 && arg == 3) 
        {

            //textstr_array[1] contains the directory/filename
            char directory[100];
            strcpy(directory, textstr_array[1]);
            strcat(directory,".csv");
            // printf("Directory: %s", directory);


            file_ptr = fopen(directory, "w");
            fprintf(file_ptr,"Name,X,Y,Z\n");
            for (int i = 0; i < elements; i++)
            {
                fprintf(file_ptr,"%s, %f, %f, %f\n", memory[i].name, memory[i].x,
                memory[i].y, memory[i].z);
            }
            fclose(file_ptr);
            
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
            printf("- Save Vector Array: save [directory].csv");
            printf("- Load Vector Array: load [directory].csv");
            printf("Note: When using load/save, put .csv at the end of the directory. Only .csv files are supported.");
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
            free(memory);
            memory = malloc(INITIAL_MEM_SIZE * sizeof(vector));
            curr_mem = INITIAL_MEM_SIZE;
            elements = 0;
        }
        //Case 0: Error/Invalid Input
        else 
        {
            printf("Invailid input. Try typing help. Make sure all vector names are valid and initialized.\n");
            printf("You must also have spaces in between each character and only using supported functions.\n");    
        }        
        free(seq);
    }
    return 0;

}
