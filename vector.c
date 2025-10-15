/* 
* Filename: vector.c
* Author: Jaden Hipe
* Description: Defines the operations for vectors. It includes addition, subtraction, scalar mult.,
* dot product, cross product.
* Date: 10/10/25
* Compile Info: make 
*/
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

vector create(float x, float y, float z, char vector_name[])
{
    vector new_vector;
    new_vector.x = x;
    new_vector.y = y;
    new_vector.z = z;
    strcpy(new_vector.name, vector_name);

    return new_vector;
}
vector add(vector *first, vector *second, char vector_name[]) 
{
    float new_x = first->x + second->x;
    float new_y = first->y + second->y;
    float new_z = first->z + second->z;

    return create(new_x,new_y,new_z, vector_name);
}


vector sub(vector *first , vector *second, char vector_name[])
{
    float new_x = first->x - second->x;
    float new_y = first->y - second->y;
    float new_z = first->z - second->z;

    return create(new_x,new_y,new_z, vector_name);
}

vector mult(float scalar, vector *v, char vector_name[])
{
    float new_x = v->x * scalar;
    float new_y = v->y * scalar;
    float new_z = v->z * scalar;

    return create(new_x,new_y,new_z, vector_name);
}

float dotprod(vector *first, vector *second)
{
    return (first->x * second->x) + (first->y * second->y) + (first->z * second->z); 
}

vector crosprod(vector *first, vector *second, char vector_name[])
{
    float new_x = (first->y * second->z) - (first->z * second->y);
    float new_y = (first->z * second->x) - (first->x * second->z);
    float new_z = (first->x * second->y) - (first->y * second->x);

    return create(new_x,new_y,new_z, vector_name);
}

vector *getVector(vector mem[10], char name[])
{
    for(int i = 0; i < 10; i++)
    {
        if(strcmp(mem[i].name, name) == 0) 
        {
            return &mem[i];
        }
    }
    return NULL;        //If not found, return NULL
}

void printvector(vector v)
{
        printf("%s = %f %f %f",v.name, v.x, v.y, v.z);
}

int isFloat(char str[]) 
{
    //strof() - returns the number and can give back a pointer to a char that was not a number after reading possible the number.
    char *endchar;
    float fl = strtof(str, &endchar);

    //If the end char is the null operator and input != output, then it is a float
    if (*endchar == '\0' && endchar != str) 
    {
        return 1;
    }
    //Otherwise return false
    return 0; 
}

char *sequence(char str[][10], int args)
{
    //THE SOLUTION
    char *seq = malloc(16); // enough space for short sequences
    seq[0] = '\0';          // initialize as empty string
    for (int i = 0; i < args; i++)
        {
            //Check if its a float
            if(isFloat(str[i])) 
            {
                strcat(seq, "f");
            }
            //Check which operand it is
            else if(strcmp(str[i], "+") == 0)
            {
                strcat(seq, "+");
            }
            else if(strcmp(str[i], "-") == 0)
            {
                strcat(seq, "-");
            }
            else if(strcmp(str[i], "=") == 0)
            {
                strcat(seq, "=");
            }
            else if(strcmp(str[i], "*") == 0)
            {
                strcat(seq, "*");
            }
            else if(strcmp(str[i], ".") == 0)
            {
                strcat(seq, ".");
            }
            else if(strcmp(str[i], "X") == 0)
            {
                strcat(seq, "X");
            }
            //Otherwise it might be a varname
            else
            {
                    strcat(seq, "v");
            }
        }
        return seq;
}
