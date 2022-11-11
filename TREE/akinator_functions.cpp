#include "akinator_functions.hpp"
#include "tree_functions.hpp"

int dump_counter = 1;

char ask_yes_no(char need_question) 
{
    char answer[MAX_STR_LEN];
    char not_correct_answer = true;
    char ret_val = false;

    if(need_question)
        printf("\nWant try again?[yes/no]\n");

    while(not_correct_answer) 
    {
        scanf("%40s", answer);

        if (strncmp(answer, "yes", 3) == 0) 
        {
            not_correct_answer = false;
            ret_val = 1;
        } 
        else if (strncmp(answer, "no", 2) == 0) 
        {
                not_correct_answer = false;
                ret_val = 0;
        } 
        else 
        {
            printf("unknown answer\n");
        }

    }

    return ret_val;
}

int  ask_mode(void) 
{
    char answer[MAX_STR_LEN];
    printf("Which mode do you want to choose?\n"
            "available modes:\n"
            "\t[1]Guess\n"
            "\t[2]Def\n"
            "\t[3]Diff\n"
            "\t[4]Dump\n"
            "\t[5]Stop\n"
        );

    scanf("%40s", answer);

    if(strcmp(answer, "stop") == 0) 
    {
        return STOP;
    }
    
    if(strcmp(answer, "dump") == 0) 
    {
        return DUMP;
    }
    
    if(strcmp(answer, "diff") == 0) 
    {
        return DIFF;
    }

    if(strcmp(answer, "def") == 0) 
    {
        return DEF;
    }

    if(strcmp(answer, "guess") == 0) 
    {
        return GUESS;
    } 

    else
        printf("no such mode\n");
}


void tree_graph_dump(Akinator * akinator) 
{
    assert(akinator);
    assert(akinator->tree);
    assert(akinator->tree->root);

    FILE * file  = fopen("tree.dot", "w");

    Node * root = akinator->tree->root;

    fprintf(file ,"digraph TREE{\n");

    graph_dump(file , root, root->left);
    graph_dump(file , root, root->right);

    fprintf(file ,"}\n");
    fclose(file );

    char cmd_string[100] = "";
    sprintf (cmd_string, "dot tree.dot -Tpng -o output%d.png", dump_counter);
    //system (cmd_string); 

    dump_counter++;
}

void graph_dump(FILE * file , Node * node, Node * node_son) 
{
    if (node_son == NULL) return;

    if (node != NULL) 
    {
        fprintf   (file , "\t%s -> %s\n", node->data, node_son->data);
        graph_dump(file , node_son, node_son->left);
        graph_dump(file , node_son, node_son->right);
    }
    else printf("empty tree\n");
}

void tree_preorder_dump (FILE * file, Node * node)
{
    assert(file != NULL);

    if (node == NULL) return;

    if (node->left == NULL && node->right == NULL) 
    {
        fprintf(file, "{\"%s\"}\n", node->data);
    } 
    else 
    {
        fprintf(file, "{\"%s\"\n", node->data);

        if (node->left) tree_preorder_dump(file, node->left);

        if (node->right) 
        {
            tree_preorder_dump(file, node->right);
            fprintf(file, "}\n");
        }
    }

}


void guessing(Akinator * akinator) 
{
    Node * cur_node = akinator->tree->root;
    
    while(cur_node->left != NULL) 
    {
        printf("it is %s?[yes/no]\n", cur_node->data);

        char answer =  ask_yes_no(0);

        if(answer)
            cur_node = cur_node->left;
        else
            cur_node = cur_node->right;
    }

    printf("Is it %s ?\n", cur_node->data);

    char answer = ask_yes_no(0);
    if (answer) 
    {
        printf("Great, I won again\n");
    } 
    else 
    {
        tree_add_obj(akinator,  cur_node);
    }
}

void get_definition(Akinator * akinator, char * obj)
{
    assert(akinator);
    assert(akinator->tree);
    assert(obj);

    stack search_stack = {};
    stack_ctor(search_stack, 20);
    Node * find_node = tree_find_obj(akinator->tree->root, &search_stack, obj);

    Node * nd = NULL;

    printf("%s is ", find_node->data);

    for(int i = 0; i < search_stack.size - 1; i += 2)
    {
        nd = (Node *)search_stack.data[i];

        if(search_stack.data[i+1] == 1)
            printf("%s ", nd->data);
        else
            printf("no %s ", nd->data);
    }

    printf("\n");
}

void get_difference(Akinator * akinator, char * obj1, char * obj2)
{
    assert(akinator);
    assert(akinator->tree);
    assert(obj1);   
    assert(obj2);  

    stack search_stack1 = {};
    stack_ctor(search_stack1, 20);
    Node * find_node1 = tree_find_obj(akinator->tree->root, &search_stack1, obj1);

    stack search_stack2 = {};
    stack_ctor(search_stack2, 20);
    Node * find_node2 = tree_find_obj(akinator->tree->root, &search_stack2, obj2);

    Node * nd1 = NULL;
    Node * nd2 = NULL;

    char  all_matches = 1;
    printf("%s and %s similar in that:  ", find_node1->data, find_node2->data);

    for(int i = 0; (i < search_stack1.size - 1) && all_matches; i += 2)
    {
        nd1 = (Node *)search_stack1.data[i];
        nd2 = (Node *)search_stack2.data[i];

        if(all_matches && (search_stack1.data[i+1] == search_stack2.data[i+1]))
        {
            if(search_stack1.data[i+1] == 1)
                printf("%s ", nd1->data);
            else
                printf("no %s ", nd1->data);    
        }

        else
        {
            all_matches = 0;
            printf("\nbut differ in that:  ");

            printf("%s is ", ((Node *)search_stack1.data[search_stack1.size - 1])->data);
            if(search_stack1.data[i+1] == 1)
                printf("%s ", nd1->data);
            else
                printf("no %s ", nd1->data);   

            
            printf("%s is ", ((Node *)search_stack2.data[search_stack2.size - 1])->data);
            if(search_stack2.data[i+1] == 1)
                printf("%s ", nd2->data);
            else
                printf("no %s ", nd2->data);   
        }

    }        
}


void tree_add_obj(Akinator * akinator,  Node * cur_node)
{
    assert(akinator);
    assert(akinator->tree);
    assert(cur_node);

    char * old_obj = cur_node->data;

    printf("Ok this time you win\nPlease tell me what kind of object it was?\n");
    char * obj = (char *) calloc(MAX_STR_LEN, sizeof(char));
    scanf("%40s", obj);

    char * question = (char*) calloc(MAX_STR_LEN, sizeof(char));
    printf("What is the difference?\n");
    scanf("%40s", question);

    cur_node->data = question;

    cur_node->left = (Node *) calloc(1, sizeof(cur_node));
    cur_node->left->data = obj;
    cur_node->left->left = NULL;
    cur_node->left->right = NULL;

    cur_node->right = (Node *) calloc(1, sizeof(cur_node));
    cur_node->right->data = old_obj;
    cur_node->right->left = NULL;
    cur_node->right->right = NULL;
}
