#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct list{
    char* string;
    struct list* next;
	struct list* prev;
} List;

List* new_node(List* head, char* str) {
    List *t = NULL;
    if(head == NULL){
        head = (List*)malloc(sizeof(List));
        head->string = (char*)malloc(strlen(str));
        strcpy(head->string, str);
        head->next = NULL;
		head->prev = NULL;
        return head;
    }
    t = (List*)malloc(sizeof(List));
    t->string = (char*)malloc(strlen(str) + 1);
    strcpy(t->string, str);
    t->next = head;
	t->prev = NULL;
	head->prev = t;
    return t;
}
/*List* reverse(List *head){
    List *p = NULL;
    List *t = NULL;
    while(head) {
        p = head;
        head = head->next;
        p->next = t;
        t = p;
    }
    return t;
}*/

/*void print_list(List* head){
	List *t = NULL;
	while(head != NULL){
        printf("---> %s\n", head->string);
        t = head->next;
        free(head->string);
        free(head);
        head = t;

    }
}*/

void print_list(List* head){
	List *t = NULL;
	while(head->next != NULL){
		printf("---> %s\n", head->string);
		head = head->next;
	}
	while(head->prev != NULL){
		printf("---> %s\n", head->string);
		head = head->prev;
	}
}

int main(){
    List *head = NULL;
    char tmp[256];

    while(1){
        gets(tmp);
        if(tmp[0] == '.') {
            head = new_node(head, tmp);
            break;
        }
        head = new_node(head, tmp);
    }
    printf("\nList:\n");
   	//head = reverse(head);
    
    print_list(head);
 
    return 0;
}