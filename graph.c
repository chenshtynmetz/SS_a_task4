#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <math.h>


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
//            pedge new_edge= NULL;
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

void insert_node_cmd(pnode *head){
    int id= -1;
    char space= '!';
    scanf("%d", &id);
    scanf("%c", &space);
    pnode *pointer;
    pnode n= search(head, id);
    pointer= &n;
    if(n != NULL){
        pedge e= n->edges;
        while (e != NULL){
            delete_edge(pointer, e->endpoint->node_num);
        }
    }
    else{
        n= *head;
        pnode temp= n;
        while (temp->next != NULL){
            temp= temp->next;
        }
        temp->next= (pnode) malloc(sizeof (node));
        if(temp->next == NULL){
            return;
        }
        temp->next->node_num= id;
        temp->next->next= NULL;
        temp->next->edges= NULL;
        *head= n;
    }
    int dest= -1;
    int w= -1;
    pnode new_node= search(head, id);
    pedge *first= &(new_node->edges);
    while (scanf("%d", &dest)){
        scanf("%c", &space);
        *first= (pedge) malloc(sizeof (edge));
        if (*first == NULL){
            return;
        }
        (*first)->endpoint= search(head, dest);
        (*first)->next= NULL;
        scanf("%d", &w);
        scanf("%c", &space);
        (*first)->weight = w;
        first= &((*first)->next);
    }
}

pnode low_n(pnode *head){
    pnode temp= *head;
    pnode min= temp;
    int maxi= (int)INFINITY;
    while (temp != NULL){
        if(temp->weight< maxi) {
            if (temp->visit == 0) {
                maxi= temp->weight;
                min = temp;
            }
        }
        temp= temp->next;
    }
    return min;
}

int shortsPath_cmd(pnode *head, int src, int dest){
//    int src= -1;
//    int dest= -1;
    int counter= 0;
//    char space= '!';
//    scanf("%d", &src);
//    scanf("%c", &space);
//    scanf("%d", &dest);
//    scanf("%c", &space);
    pnode temp= *head;
    while (temp != NULL){
        temp->visit= 0;
        temp->weight= (int)INFINITY-100;
        temp= temp->next;
        counter++;
    }
    pnode node_src= search(head, src);
    node_src->weight= 0;
    while (counter>0){
        node_src= low_n(head);
        if(node_src->node_num== dest){
            return node_src->weight;
        }
        node_src->visit= 1;
        pedge s_edge= node_src->edges;
        while (s_edge != NULL){
            if(node_src->weight + s_edge->weight < s_edge->endpoint->weight){
                s_edge->endpoint->weight= node_src->weight+s_edge->weight;
            }
            s_edge= s_edge->next;
        }
        counter--;
    }
    return 0;
}

void swap(int* a, int *b){
    int temp= *b;
    *b = *a;
    *a = temp;
}
void permotion(pnode *head, int arr[], int size, int num_of_cities, int *minpath){
    if (size==1){
        int path=0;
        for(int j=0; j<num_of_cities-1; j++){
            path+= shortsPath_cmd(head, arr[j], arr[j+1]);
        }
        if(path< *minpath){
            *minpath= path;
        }
        return;
    }
    for(int j=0; j<size; j++){
        permotion(head, arr,  size-1, num_of_cities, minpath);
        if(size % 2 == 1){
            swap(&arr[0], &arr[size-1]);
        }
        else{
            swap(&arr[j], &arr[size-1]);
        }
    }
}

void TSP_cmd(pnode *head){
    int size= -1;
    char space= '!';
    int num= -1;
    int *min= 0;
    *min = (int)INFINITY;
    scanf("%d", &size);
    scanf("%c", &space);
    int arr[size];
    for(int i=0; i<size; i++){
        scanf("%d", &num);
        scanf("%c", &space);
        arr[i]= num;
    }
    permotion(head, arr, size, size, min);
    if(*min == INFINITY){
        *min= -1;
    }
    printf("TSP shortest path: %d\n", *min);
}


int main(){
    pnode head =NULL;
    pnode *temp= &head;
    build_graph_cmd(temp);
//    char ch= 'a';
//    scanf("%c", &ch);
//    scanf("%c", &ch);
//    TSP_cmd(temp);
//    pnode t= head;
//    while (t != NULL)
//    {
//        printf("%d\n", t->node_num);
//        pedge te= t->edges;
//        while (te != NULL)
//        {
//            printf("%d\n", te->endpoint->node_num);
//            printf("%d\n", te->weight);
//            te= te->next;
//        }
//        t= t->next;
//    }

    // for(int i=0; i<4; i++){
    //     printf("%d", t->node_num);
    //     t= t->next;
    // }

    return 0;
}


