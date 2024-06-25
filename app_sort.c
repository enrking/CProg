#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    struct node* next;
    struct node* prev;
} NODE;

typedef struct list {
    NODE* head;
    int size;
} LIST;

typedef struct record {
    NODE node;
    char name[50];
    int years;
} DATA;

//
void printRecord(LIST* list);
//

NODE* createRecord(char* name, int years){
    DATA* newData = (DATA*)malloc(sizeof(DATA));

    newData->node.next = NULL;
    newData->node.prev = NULL;

    strcpy(newData->name, name);
    newData->years = years;

    return (NODE*) newData;
}

DATA* addRecord (){
    
    DATA* newRecord;
    
    char name[50];
    int years = 0;
    
    printf("Name: ");
    scanf("%s", name);
    printf("Experience: ");
    scanf("%d", &years);
    
    newRecord = (DATA*) createRecord(name, years);
    
    return newRecord;
}

void insertToLast(LIST* list, NODE* recordToInsert){

    if(list->head == NULL){
        list->head = recordToInsert;
        return;
    }
    
    NODE* head = list->head;
    
    while(head->next != NULL){
        head = head->next;
    }
    head->next = recordToInsert;
    recordToInsert->prev = head;
}

void printRecord(LIST* list){
    
    NODE* head = list->head;

    if ( head->prev != NULL ){
        head = head->prev;
    }

    for (int i = 1; head != NULL; i++){
        printf("%d.Name:%s Experience:%d\n", i, ((DATA*)head)->name, ((DATA*)head)->years);
        //printf("%d. (%p)<-(%p)->(%p) \tName:%s Experience:%d\n", i, head->prev, head, head->next, ((DATA*)head)->name, ((DATA*)head)->years);
        head = head->next;
    }
}

void print_node(NODE* head){

    if( head == NULL ) return;

    printf("tmp0(%p)<-head(%p)->tmp1(%p)\n", head->prev, head, head->next);
}

void clear(LIST* list){
    NODE* head = list->head;

    if ( head->prev != NULL ){
        head = head->prev;
    }

    for (int i = 1; head != NULL; i++){
        free(head);
        head = head->next;
    }
    printRecord(list);
}

void sort(LIST* list){

    bool is_swap = false;
    int size = list->size;

    NODE* p_head = list->head;

    if ( p_head == NULL){
        p_head = p_head->next;
    }

    do{
        is_swap = false;
        p_head = list->head;

            for(int i = 0; i < size-1; i++){
                if ( p_head->next == NULL ) continue;

                if ( ((((DATA*)p_head)->years) > ((DATA*)p_head->next)->years) ){
    
                    NODE* tmp0;
                    NODE* tmp1;
                    NODE* tmp2;

                    tmp0 = p_head->prev;
                    tmp1 = p_head->next;
                    tmp2 = tmp1->next;

                    if( tmp0 != NULL ){
                        tmp0->next = tmp1;
                    }

                    tmp1->next = p_head;
                    p_head->next = tmp2;

                    if ( tmp2 != NULL ){
                        tmp2->prev = p_head;
                    }
                    p_head->prev = tmp1;
                    tmp1->prev = tmp0;
    
                    is_swap = true;
            } else {
                p_head = p_head->next;
            }
        }
    }while(is_swap == true);

    printRecord(list);
}

int option(){
    int choice = 0;

    while (choice == 0){
        printf("Select Option\n");
        printf("1. Add Record\n");
        printf("2. Edit Record\n");
        printf("3. Delete Record\n");
        printf("4. List of Employees\n");
        printf("5. List of Employees vs years of experience\n");
        printf("6. Sort base on years of experience\n");
        printf("7. Exit\n");
        printf(">>: ");
        
        scanf("%d", &choice);

        bool is_valid_input = choice >= 1 && choice < 8;

        if(is_valid_input){
            return choice;
        } else if (choice == 7){
            break;
        }
        else{
            printf("Invalid input. Try again.\n\n");
            choice = 0;
        }
    }
}

int main()
{
    int choice = 0;
    int size = 0;

    LIST data_list;
    data_list.head = NULL;
    data_list.size = 0;

    while (choice != 7){
        printf("\n");
        choice = option();

        if (choice == 1){
            do{
                printf("1. add more record\n");
                printf("2. exit\n");
                scanf("%d", &choice);
                if(choice != 1) break;

                DATA* RecordToAdd = addRecord();
                if(RecordToAdd != NULL){
                size = data_list.size++;
                }
                insertToLast(&data_list, (NODE*)RecordToAdd);
            } while(choice == 1);
            
            
        } else if(choice == 2){
            
            //editRecord(&data_list);
            
        } else if(choice == 3){
            
            //deleteRecord(&data_list);
            
        } else if(choice == 4){
            printRecord(&data_list);

        } else if (choice == 5){
            //printRecordYearsExperience(&list);
        } else if (choice == 6){
            sort(&data_list);
        } else if (choice == 7){
            clear(&data_list);
        } 
    }
    return 0;
}
