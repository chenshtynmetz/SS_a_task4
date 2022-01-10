#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <math.h>

#define INFINI 1000000
static int min = INFINI;
// pedge find_edge(pnode *curr, int dest){
//     pnode temp= *curr;
//     pedge t_e= temp->edges;
//     while (t_e != NULL){
//         if(t_e->endpoint->node_num == dest){
//             return t_e;
//         }
//         t_e= t_e->next;
//     }
//     return NULL;
// }

// void findANDdelete_edge(pnode curr, int dest){
//     pnode temp= curr;
//     pedge t_e= temp->edges;
//     while (t_e->next != NULL){
//         if(t_e->next->endpoint->node_num == dest){
//             pedge temp=t_e->next;
//             t_e->next=t_e->next->next;
//             free(temp);
//         }
//         t_e= t_e->next;
//     }
// }

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
    *curr = n;
}

void delete_node_cmd(pnode *head){
    // printf("node delete");
    pnode temp = *head;
    pnode* this_head = NULL;
    pnode prev = NULL;
    int id = -1;
    // char space = '!';
    scanf("%d", &id);
    // scanf("%c", &space);
    if(temp->node_num == id){
        this_head = head;
    }
    while (temp != NULL)
    {
        if(temp->next != NULL && temp->next->node_num == id){
            prev = temp;
        }
        if(temp->next != NULL && temp->edges != NULL && temp->edges->endpoint->node_num == id){
            pedge t_e = temp->edges;
            temp->edges = temp->edges->next;
            free(t_e);
            temp = temp->next;
            continue;
        }
        pedge  t_e = temp->edges;
        if(t_e != NULL){
            while (t_e->next != NULL)
            {
                if(t_e->next->endpoint->node_num == id){
                    pedge curr_e = t_e->next;
                    t_e->next = curr_e->next;
                    free(curr_e);
                }
                else{
                    t_e = t_e->next;
                }
            }
            
        }
        temp = temp->next;
    }
    if (this_head != NULL){
        pedge curr_e = (*this_head)->edges;
        while (curr_e != NULL)
        {
            pedge f_edge = curr_e;
            curr_e = curr_e->next;
            free(f_edge);
        }
        pnode t_n = *this_head;
        *this_head = t_n->next;
        free(t_n);
    }
    else if(prev != NULL){
        pnode f_node = prev->next;
        pedge t_e = f_node->edges;
        while(t_e != NULL){
            pedge curr_e = t_e;
            t_e = t_e->next;
            free(curr_e);
        }
        prev->next = f_node->next;
        free(f_node);
    }
}


void deleteGraph_cmd(pnode *head){
    pnode temp_node= *head;
    while (temp_node != NULL)
    {
    //    pnode *pointer = &temp_node;
        pedge temp_edge = temp_node->edges;
        while(temp_edge != NULL){
            pedge curr_e = temp_edge;
            temp_edge = temp_edge->next;
            free(curr_e);
        // int des = temp_edge->endpoint->node_num;
        // delete_edge(pointer, des);
        // temp_edge = temp_node->edges;
        }
        pnode curr_n = temp_node;
        temp_node = temp_node->next;
        free(curr_n);
    }   
//    while(temp_node != NULL){
//        pnode curr= temp_node;
//        temp_node=temp_node->next;
//        free(curr);
//        *head= temp_node;
//    }
    *head = NULL;
    // printf("the graph delet");
}

pnode search(pnode *head, int id){
    pnode n= *head;
    pnode temp = n;
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
    // char space= '!';
    scanf("%d", &counter);
    // scanf("%c", &space);
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
        // scanf("%c", &space);
        if(ch == 'n'){
            counter--;
            scanf("%d", &id);
            // scanf("%c", &space);
            pnode curr= search(head, id);
            pedge *first_edge= &(curr->edges);
            int dest = -1;
            int w= -1;
            while(scanf("%d", &dest)){
                // scanf("%c", &space);
                *first_edge= (pedge) malloc(sizeof (edge));
                if(*first_edge == NULL){
                    return;
                }
                (*first_edge)->endpoint= search(head, dest);
                (*first_edge)->next= NULL;
                scanf("%d", &w);
                // scanf("%c", &space);
                (*first_edge)->weight= w;
                first_edge= &((*first_edge)->next);
            }
        }
        if(counter == 0){
            break;
        }
    }
    *head= start;
}

void insert_node_cmd(pnode *head){
    int id= -1;
    // char space= '!';
    scanf("%d", &id);
    // scanf("%c", &space);
    pnode *pointer;
    pnode n= search(head, id);
    if(n != NULL){
        pointer= &n;
        pedge e= n->edges;
        while (e != NULL){
            e= n->edges;
            int des= e->endpoint->node_num;
            delete_edge(pointer, des);
            e= n->edges;
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
    while (scanf("%d", &dest) && dest != EOF){
        // scanf("%c", &space);
        *first= (pedge) malloc(sizeof (edge));
        if (*first == NULL){
            return;
        }
        (*first)->endpoint= search(head, dest);
        (*first)->next= NULL;
        scanf("%d", &w);
        // scanf("%c", &space);
        (*first)->weight = w;
        first= &((*first)->next);
    }
    // printf("the node add");
}

pnode low_n(pnode *head){
    pnode temp= *head;
    pnode min= temp;
    int maxi= INFINI;
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
    int counter= 0;
    pnode temp= *head;
    while (temp != NULL){
        temp->visit= 0;
        temp->weight= INFINI-10;
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

void permotion(pnode *head, int arr[], int size, int num_of_cities){
    if (size==1){
        int path=0;
        for(int j=0; j<num_of_cities-1; j++){
            path+= shortsPath_cmd(head, arr[j], arr[j+1]);
        }
        if(path< min){
            min= path;
        }
        return;
    }
    for(int j=0; j<size; j++){
        permotion(head, arr,  size-1, num_of_cities);
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
    // char space= '!';
    int num= -1;
    min = INFINI;
    // int a= 0;
    // int *min= &a;
    // min = (int)INFINITY;
    scanf("%d", &size);
    // scanf("%c", &space);
    int arr[size];
    for(int i=0; i<size; i++){
        scanf("%d", &num);
        // scanf("%c", &space);
        arr[i]= num;
    }
    permotion(head, arr, size, size);
    int eps = 3;
    if(INFINI-min<=eps){
        min= -1;
    }
    printf("TSP shortest path: %d \n", min);
}



