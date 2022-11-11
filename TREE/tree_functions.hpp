#include "akinator_utilities.hpp"

void   start_program (Akinator * akinator);
void   akinator_ctor(Akinator * akinator);

Node * tree_ctor (Node * node, char ** text_buf);
Node * node_ctor(Node * node, char * obj);
int    skip_while_no_char(char c, char ** text_buf);
char * obj_ctor(char ** obj, char ** text_buf);


char * createBufferWithFread (size_t * elements, FILE * readFile, size_t * strNum);
size_t fileSizeDetection     (FILE * read);
size_t countNumberOfRows     (char * BUF, size_t elements);
char * textNormalize         (char * text);


Node * tree_find_obj(Node * node, stack * stack, char * search_object);


void  finish_program(Akinator * akinatore);
void  tree_dtor (Tree * tree);
void  node_dtor(Node * node);