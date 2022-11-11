#ifndef AKINATOR_UTILITIES_HPP_INCLUDED
#define AKINATOR_UTILITIES_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <malloc.h>

//typedef int stack_t;
#include "STACK/utils_stk.hpp"
#include "STACK/debug.hpp"
#include "STACK/stack.hpp"

#define MAX_STR_LEN 40


enum COMMAND {
    GUESS = 1,  //отгадывание
    DEF   = 2,  //определение
    DIFF  = 3,  //сравнение
    DUMP  = 4,  //графический дамп
    STOP  = 5,
};

struct Text
    {
    size_t amountOfElements;
    size_t amountOfStrings;
    };

struct Node 
{
    char * data;
    Node * left;// = NULL;
    Node * right;// = NULL;
};

struct Tree 
{
    Node * root = NULL;
};

struct Akinator 
    {
    Tree * tree = {};
    char * buffer = NULL;
    };

#endif