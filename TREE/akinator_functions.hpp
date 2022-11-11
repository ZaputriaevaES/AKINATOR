#include "akinator_utilities.hpp"

char  ask_yes_no (char need_question);
int   ask_mode   (void);

void  tree_graph_dump (Akinator * akinator);
void  graph_dump      (FILE * file , Node * node, Node * node_son);

void  tree_preorder_dump  (FILE * file, Node * node);

void  guessing       (Akinator * akinator);
void  get_definition (Akinator * akinator, char * obj);
void  get_difference (Akinator * akinator, char * obj1, char * obj2);

void   tree_add_obj(Akinator * akinator, Node * cur_node);