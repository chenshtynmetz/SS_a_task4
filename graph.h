#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int visit;
    int weight;
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
int shortsPath_cmd(pnode *head, int src, int dest);
void TSP_cmd(pnode *head);
pedge find_edge(pnode *curr);
void delete_edge(pnode *curr, int id);
void delete_node(pnode *head, pnode id);
pnode search(pnode *head, int id);
void insert_node_cmd(pnode *head);
pnode low_n(pnode *head);
void swap(int* a, int *b);
void permotion(pnode *head, int arr[], int size, int num_of_cities, int *minpath);
void TSP_cmd(pnode *head);

#endif
