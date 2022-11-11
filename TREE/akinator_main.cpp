//#include "C:\Users\zaput\Documents\AKINATOR\TREE\tree_functions.hpp"
#include "tree_functions.hpp"
#include "akinator_functions.hpp"

FILE * input_base = fopen("input_base.txt", "r+");
FILE * file_tree  = fopen("tree_dump.txt", "w");


int main(int argc, char* argv[]) 
{
    Akinator akinator = {};

    start_program(&akinator);

    tree_preorder_dump(file_tree, akinator.tree->root);

    printf("\nHello, do you want to play akinator?[yes/no] ");

    char need_question = 0;

    while (ask_yes_no(need_question))
    {
        switch (ask_mode())
        {
            case GUESS: 
            {
                printf("Let's guess the words!\n");            
                guessing(&akinator);
                need_question = 1;
                break;
            }
            case DEF: 
            {
                printf("Enter the name of the object you want to get the definition of:\n");
                char obj[MAX_STR_LEN] = "";
                scanf("%40s", obj);//
                printf("So let's start looking:\n");
                get_definition(&akinator, obj);
                need_question = 1;
                break;
            } 

            case DIFF: 
            {
                printf("Enter two objects you want to know the difference between:\n");
                char obj1[MAX_STR_LEN] = "";
                char obj2[MAX_STR_LEN] = "";
                scanf("%40s", obj1);//
                scanf("%40s", obj2);//

                printf("So these objects differ in that:\n");

                get_difference(&akinator, obj1, obj2);
                need_question = 1;
                break;
            } 

            case DUMP: 
            {
                printf("The current database looks like this:\n");
                tree_preorder_dump(file_tree, akinator.tree->root);
                tree_graph_dump   (&akinator);
                need_question = 1;
                break;
            }

            case STOP: 
            {
                printf("goodbye, it was nice talking to you\n");
                need_question = 1;
                break;
            }
        }
    }  

    printf("GOODBYE\n");  

    fclose(input_base);
    FILE * finish_input_base = fopen("input_base.txt", "w");
    tree_preorder_dump(finish_input_base, akinator.tree->root);

    finish_program(&akinator);

    fclose(finish_input_base);

    return 0;
}