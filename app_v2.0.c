
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



typedef struct node {
    struct node* next;
    struct node* prev;
} NODE;

typedef struct record {
    NODE node;
    char name[50];
    int years;
} DATA;

//
void printRecord(DATA* record);
DATA* searchRecord(DATA* recordToSearch, int index);
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
    printf("Name2:%s \texperience:%d", newRecord->name, newRecord->years);
    
    return newRecord;
}

void insertToLast(NODE* recordExist, NODE* recordToInsert){
    if(recordExist == NULL){
        return;
    }
    if(recordToInsert == NULL){
        return;
    }

    while(recordExist->next != NULL){
        recordExist = recordExist->next;
    }
    recordExist->next = recordToInsert;
    recordToInsert->prev = recordExist;
}

void editRecord(DATA* recordToEdit){
    int index = 0;
    printRecord(recordToEdit);
    printf("Select number to edit: ");
    scanf("%d", &index);
    

    DATA* record_exist = searchRecord(recordToEdit, index);

    if(record_exist != NULL){
        printf("Name: ");
        scanf("%s", record_exist->name);
        printf("Experience: ");
        scanf("%d", &record_exist->years);
    } else {
        printf("Record does not exist!");
    }

    return;
}

void deleteRecord(DATA** p_recordToDelete){
    int index = 0;
    DATA* recordToDelete = *p_recordToDelete;
    
    printRecord(recordToDelete);
    printf("Select number to delete: ");
    scanf("%d", &index);

    DATA* record_exist = searchRecord(recordToDelete, index);

    if(record_exist != NULL){
        NODE* current = (NODE*)record_exist;
        NODE* current_next = current->next;
        NODE* current_prev = current->prev;

        if(current_next == NULL){
            current = current_prev;
            current_prev->next = NULL;
        } else if(current_prev == NULL){
            current = current_next;
            current_next->prev = NULL;
            
            *p_recordToDelete = (DATA*)current_next;
        } else {
            current = current_prev;
            current_prev->next = current_next;
            current_next->prev = current;
        }

        free (record_exist);
    } else {
        printf("Record does not exist!");
    }

    return;
}

DATA* searchRecord(DATA* recordToSearch, int index){

    bool record_found = false;
    DATA* current = (DATA*)recordToSearch;
    NODE* pcurrent = (NODE*)current;
    
    while(pcurrent->prev != NULL){
        pcurrent = pcurrent->prev;
    }

    for (int i = 1;pcurrent != NULL; i++){
        if(i == index){
            current = (DATA*)pcurrent;
            record_found = true;
            break;
        }
        pcurrent = pcurrent->next;
    }

    if(record_found != true){
        current = NULL;
    }

    return current;
}

//print all records.
void printRecord(DATA* initialRecord){
    
    NODE* p_initialRecord = (NODE*)initialRecord;
    
    printf("\n");
        
    for (int i = 1; p_initialRecord != NULL; i++){
        printf("%d. Name: %s Experience: %d\n", i, ((DATA*)p_initialRecord)->name, ((DATA*)p_initialRecord)->years);
        p_initialRecord = p_initialRecord->next;
    }
}

//base on years of experience.
void printRecordYearsExperience(DATA* records){
    if (records == NULL){
        return;
    }
    
    NODE* p_records = (NODE*)records;
    int index = 0;
    int records_count = 1;
    int i = 1;

    printf("Search number of years of experience.");
    scanf("%d", &index);

    while (p_records->prev != NULL){
        p_records = p_records->prev;
    }

   while (p_records != NULL){
       if (((DATA*)p_records)->years == index){
            printf("%d.Name: %s Experience: %d\n", records_count, ((DATA*)p_records)->name, ((DATA*)p_records)->years);
       }
       records_count++;
       p_records = p_records->next;
   }

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
        printf("6. Exit\n");
        printf(">>: ");
        
        scanf("%d", &choice);

        bool is_valid_input = choice >= 1 && choice < 6;

        if(is_valid_input){
            return choice;
        } else if (choice == 6){
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
    DATA* initialRecord;;
    DATA* RecordToAdd;
    
    initialRecord = (DATA*) createRecord("Khier", 1);

    while (choice != 6){
        printf("\n");
        choice = option();
        
        if (choice == 1){
            
            RecordToAdd = addRecord();
            insertToLast((NODE*)initialRecord, (NODE*)RecordToAdd);
            
        } else if(choice == 2){
            
            editRecord(initialRecord);
            
        } else if(choice == 3){
            
            deleteRecord(&initialRecord);
            
        } else if(choice == 4){
            printRecord(initialRecord);

        } else if (choice == 5){
            printRecordYearsExperience(initialRecord);
        } 
    }
    return 0;
}
