/* 
* Filename: vector.h
* Author: Jaden Hipe
* Description: Declares the struct for a vector, as well as the operation of vectors.
* Date: 10/10/25 
*/

#ifndef VECTOR_H
#define VECTOR_H //Guards(???)

typedef struct
{
    char name[10];
    float x;
    float y;
    float z;
} vector;

vector create(float a, float b, float c, char name[]);

vector add(vector *a, vector *b, char name[]);

vector sub(vector *a, vector *b, char name[]);

vector mult(float i, vector *b, char name[]);

float dotprod(vector *a, vector *b);

vector crosprod(vector *a, vector *b, char name[]);

vector *getVector(vector mem[10], char name[]);

void printvector(vector v);

int isFloat(char str[]);

char *sequence(char string[][10], int args);

#endif
