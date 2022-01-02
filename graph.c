#include <stdio.h>
#include "graph.h"
#include <stdlib.h>



// void new_node(pnode *temp){
//      *temp= (pnode)malloc(sizeof(node));
//         if(*temp == NULL){
//             return;
//         }
// }

pedge find_edge(pnode *curr){
    pnode temp= *curr;
    pedge t_e= temp->edges;
    while (t_e != NULL){
        if(t_e->endpoint->node_num == temp->node_num){
            return t_e;
        }
        t_e= t_e->next;
    }
    return NULL;
}

void delete_edge(pnode *curr, int id){
    pnode n= *curr;
    pedge ed= n->edges;
    if(ed->endpoint->node_num == id){
        pedge temp= ed;
        n->edges= ed->next;
        free(temp);
        return;
    }
    while (ed->next != NULL){
        if(ed->next->endpoint->node_num == id){
            pedge temp= ed->next;
            ed->next = ed->next->next;
            free(temp);
            return;
        }
    }
}
void delete_node(pnode *head, pnode id){
    pnode temp= *head;
    while (temp->node_num != id->node_num){
        temp= temp->next;
    }
    pedge temp_edge= temp->edges;
    while(temp_edge!=NULL){
        pedge curr= temp_edge;
        temp_edge= temp_edge->next;
        free(curr);
    }
    pnode start= *head;
    while(start != NULL){
        pnode *te= &start;
        pedge e= find_edge(te);
        if(e != NULL){
            delete_edge(te, id->node_num);
        }
        start= start->next;
    }
    free(temp);
}

void deleteGraph_cmd(pnode *head){
   pnode temp_node= *head;
   while(temp_node != NULL){
       pnode curr= temp_node;
       temp_node=temp_node->next;
       delete_node(head, curr);
       *head= temp_node;
   }
}

pnode search(pnode *head, int id){
    pnode temp= *head;
    while (temp!= NULL)
    {
        if(temp->node_num == id){
            return temp;
        }
        temp= temp->next;
    }
    return NULL;
}



void build_graph_cmd(pnode *head){
    if(*head != NULL){
        deleteGraph_cmd(head);
    }
    pnode start= *head;
    pnode new_node=NULL;
    pnode temp=NULL;
    int counter= 0;
    int id= -1;
    char space= '!';
    scanf("%d", &counter);
    scanf("%c", &space);
    start = (pnode)malloc(sizeof(node));
    if(start == NULL){
        return;
    }
    start->node_num= 0;
    start->edges= NULL;
    start->next=NULL;
    temp= start;
    for(int i= 1; i<counter;i++){
        new_node= (pnode)malloc(sizeof(node));
        if(new_node==NULL){
            return;
        }
        new_node->node_num= i;
        new_node->edges=NULL;
        new_node->next= NULL;
        temp->next=new_node;
        temp= temp->next;
    }
    *head= start;
    char ch= '!';
    while (scanf("%c", &ch))
    {
        scanf("%c", &space);
        if(ch == 'n'){
            counter--;
            scanf("%d", &id);
            scanf("%c", &space);
            pnode curr= search(head, id);
            pedge *first_edge= &(curr->edges);
            pedge new_edge= NULL;
//            pedge edge_temp= NULL;
//            edge_temp= first_edge;
            int dest = -1;
            int w= -1;
            while(scanf("%d", &dest)){
                scanf("%c", &space);
                *first_edge= (pedge) malloc(sizeof (edge));
//                new_edge= (pedge)malloc(sizeof(edge));
                if(*first_edge == NULL){
                    return;
                }
                (*first_edge)->endpoint= search(head, dest);
//                new_edge->endpoint= search(head, dest);
                (*first_edge)->next= NULL;
//                new_edge->next= NULL;
                scanf("%d", &w);
                scanf("%c", &space);
                (*first_edge)->weight= w;
                first_edge= &((*first_edge)->next);
//                new_edge->weight= w;
//                edge_temp= new_edge;
//                edge_temp= edge_temp->next;

                // first edge dont get value
                //
            }
//            curr->edges = first_edge;
            // free(curr);
            // free(edge_temp);
            // free(new_edge);
            // free(first_edge);
        }
        if(counter == 0){
            break;
        }
    }
    *head= start;
}

void shortsPath_cmd(pnode head){
    int src= -1;
    int dest= -1;
    char space= '!';
    scanf("%d", &src);
    scanf("%c", &space);
    scanf("%d", &dest);
    scanf("%c", &space);

}
//void delete_node_cmd(pnode *head, int id){// change in h fule
//    pnode start = *head;
//    pnode temp = start;
//    if (temp->node_num == id){
//        start = temp->next;
//        //free()
//
//    }
//    while (temp->next != NULL){
//
//    }
//}

int main(){
    pnode head =NULL;
    pnode *temp= &head;
    build_graph_cmd(temp);
    pnode t= head;
    while (t != NULL)
    {
        printf("%d\n", t->node_num);
        pedge te= t->edges;
        while (te != NULL)
        {
            printf("%d\n", te->endpoint->node_num);
            printf("%d\n", te->weight);
            te= te->next;
        }
        t= t->next;
    }

    // for(int i=0; i<4; i++){
    //     printf("%d", t->node_num);
    //     t= t->next;
    // }

    return 0;
}


//int main() {
//    printf("Hello, World!\n");
//
//    int a = 5;
//    int b = 3;
//    int ans;
//    ans = add(a, b);
//    printf("%d", ans);
//    return 0;
//}
