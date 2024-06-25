#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct node {
    struct node* next;
    struct node* prev;
} NODE;
 
typedef struct data {
    NODE node;
    int data;
} DATA;
 
NODE* createData(int data) {
    DATA* pdata = (DATA*) malloc(sizeof(DATA));
 
    pdata->data = data;
    pdata->node.next = NULL;
    pdata->node.prev = NULL;
    return (NODE*) pdata;
}
 
void insertFront(NODE* src, NODE* node_to_insert) {
    NODE* tmp = src->next;
    src->next = node_to_insert;
    node_to_insert->next = tmp;
    node_to_insert->prev = src;
}
 
void printData(DATA* data) {
    printf("prev(%p) <- %d -> next(%p)\n", data->node.prev, data->data, data->node.next);    
}
 
void printList(DATA* data) {
    NODE* tmp = (NODE*) data;
    while (tmp != NULL) {
        DATA* tmp_data = (DATA*) tmp;
        printf("%d -> ", tmp_data->data);
        tmp = tmp->next;
    }
    printf("NULL\n");
}
 
int main()
{
    DATA* data1;
    DATA* data2;
    data1 = (DATA*) createData(10);
    data2 = (DATA*) createData(20);
 
    insertFront((NODE*) data1, (NODE*) data2);
    printList(data1);
    free(data1);
    free(data2);
 
    return 0;
}