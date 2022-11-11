#include "tree_functions.hpp"

extern FILE * input_base;
extern FILE * file_tree;

void start_program(Akinator * akinator)
{
    akinator_ctor(akinator);

    akinator->tree->root = tree_ctor(akinator->tree->root, &(akinator->buffer));
}

void akinator_ctor(Akinator * akinator) 
{
    assert(akinator);
 
    akinator->tree = (Tree *) calloc(1, sizeof(Tree));

    struct Text text_base = {0, 0};
    akinator->buffer = createBufferWithFread(&text_base.amountOfElements, input_base, &text_base.amountOfStrings); 

    printf("%s\n", akinator->buffer);

}


Node * tree_ctor(Node * node, char ** text_buf)
{
    assert (node == NULL);
    assert (text_buf != NULL);

    if (**text_buf == '{') 
    {
        skip_while_no_char('"', text_buf);

        (*text_buf)++;

        char * obj = (char *) calloc(MAX_STR_LEN, sizeof(char));
        assert (obj != NULL);
        obj = obj_ctor(&obj, text_buf);
        node = node_ctor(node, obj);

        while(**text_buf != '{' && **text_buf != '}' && **text_buf != '\0') (*text_buf)++;

        if (**text_buf == '}' || **text_buf == '\0') return node;

        node->left = tree_ctor(node->left, text_buf);

        skip_while_no_char('{', text_buf);

        node->right = tree_ctor(node->right, text_buf);
    }

    return node;
}

Node * node_ctor(Node * node, char * obj) 
{
    assert (node == NULL);
    assert (obj != NULL);

    node = (Node *) calloc(1, sizeof(node));

    node->data = obj;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int skip_while_no_char(char c, char ** text_buf)
{
    char *start_p = *text_buf;
    char f_c = 0;
    while ((f_c = (**text_buf)) != c && (**text_buf) != '\0') (*text_buf)++;
    if(f_c == c) return 1;
    else 
    {
        *text_buf = start_p; 
        return 0;
    }
    //(*text_buf)++;
}

char * obj_ctor(char ** obj, char ** text_buf)
{
    assert(obj);
    assert(text_buf);
    
    char * point = *obj;
    for (; **text_buf != '\"' && **text_buf != '\0'; (*text_buf)++, (*obj)++) **obj = **text_buf; 
    *obj = point; 

    return point;
}



char * createBufferWithFread(size_t * elements, FILE * readFile, size_t * strNum)
{
    assert(readFile != NULL);

    *elements = fileSizeDetection(readFile);

    char * buffer = (char *)calloc(*elements, sizeof(char));

    fread(buffer, sizeof(char), *elements, readFile);

    *strNum = countNumberOfRows(buffer, *elements);

    *elements -= *strNum - 1;

    buffer = textNormalize(buffer);

    return buffer;
}

size_t fileSizeDetection(FILE * read)
{
    assert(read != NULL);

    struct stat stbuf;
    stat("input_base.txt", &stbuf);
    off_t fsize = stbuf.st_size;

    return fsize / sizeof(char) ;
}

size_t countNumberOfRows(char * BUF, size_t elements)
{
    assert(BUF != NULL);

    size_t n = 0; //количество символов новой строки
    for (size_t i = 0; i < elements; i++)
    {
        if (BUF[i] == '\n')
        {
            //BUF[i] = '\0';
            n++;
        }
    }

    n++;

    return n;
}

char * textNormalize(char * text)  
{
    assert(text);
   
    char * point = text;

    for (; *(point) != '\0'; point++)  
    { 
        if (*point == '\r')
        {    
            *point = ' ';
            point++;
            *point = ' ';
        }     
    }
    printf("\n\n");
    return text;
}



Node * tree_find_obj(Node * node, stack * search_stack, char * search_object) 
{
    assert(node);
    assert(search_stack);

    stack_push(search_stack, (size_t)node);

    if (strcmp(node->data, search_object) == 0) return node;

    if (node->left  != NULL) 
    {
        stack_push(search_stack, 1);
        if(tree_find_obj(node->left,  search_stack, search_object))
        {  
            return (Node*)search_stack->data[search_stack->size - 1];
        }
        else stack_pop(search_stack);
    }
    if (node->right != NULL) 
    {
        stack_push(search_stack, 0);
        if(tree_find_obj(node->right,  search_stack, search_object))
        {        
            return (Node*)search_stack->data[search_stack->size - 1];
        }
        else stack_pop(search_stack);
    }

    stack_pop(search_stack);

    return NULL;
}


void finish_program(Akinator * akinator)
{
    tree_dtor(akinator->tree);
}

void tree_dtor (Tree * tree)
{
    assert(tree);

    node_dtor(tree->root);
}

void node_dtor(Node * node) 
{
    assert(node);

    if (node->left != NULL) node_dtor(node->left);
    if (node->right != NULL) node_dtor(node->right);

    node->left = node->right = NULL;
    //node->data = NULL;

    free(node->data);
    free(node);

    return;
}
