#include <stdio.h>
#include "graph.h"

int main(){
    char ch= 'x';
    char space= '!';
    pnode *head= NULL;
    while(scanf("%c", &ch) != EOF){
        scanf("%c", &space);
        if(ch == 'A'){
            build_graph_cmd(head);
        }
        else if(ch == 'B'){
            insert_node_cmd(head);
        }
        else if(ch == 'D'){
            int id= -1;
            scanf("%d", &id);
            pnode n= search(head, id);
            delete_node(head, n);
        }
        else if(ch == 'S'){
            int src= -1;
            int dest= -1;
            scanf("%d", &src);
            scanf("%c", &space);
            scanf("%d", &dest);
            scanf("%c", &space);
            int path= shortsPath_cmd(head, src, dest);
            printf("Dijsktra shortest path: %d\n", path);
        }
        else if(ch == 'T'){
            TSP_cmd(head);
        }
    }
    return 0;
}