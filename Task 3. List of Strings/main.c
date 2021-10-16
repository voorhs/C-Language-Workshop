#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct not_used {
	char* string;
	struct not_used* next;
} List;

char* get_string() {
    char *string, character, size = 0;
    string = malloc(sizeof(char));

    while ((character = getchar()) != '\n') {
        string[size++] = character;
        string = realloc(string, sizeof(char) * (size + 1));
    }

    string[size] = '\0';
    if (size == 0)
        return NULL;
    return string;
}

void print(List* list) {
    if (list == NULL)
        return;
    printf("%s\n", list -> string);
    print(list -> next);
}

void insertion(List** list, char* row) {
    List *new_node;

    new_node = (List*)malloc(sizeof(List));
    new_node -> next = NULL;
    new_node -> string = row;

    if (*list == NULL) {
        *list = new_node;
        return;
    }

    List *list_pointer = *list, *prev = NULL;

    while (list_pointer != NULL && strcmp(list_pointer -> string, row) <= 0) {
        prev = list_pointer;
        list_pointer = list_pointer -> next;
    }
        
    if (list_pointer == NULL)
        prev -> next = new_node;

    else if (prev == NULL) {
        new_node -> next = *list;
        *list = new_node;
    }
    else {
        prev -> next = new_node;
        new_node -> next = list_pointer;
    }
}

void get_list(List** list) {
    char* row;
    while ((row = get_string()) != NULL)
        insertion(list, row);
}

void free_list(List** list) {
    List* list_pointer = *list, *tmp;
    while (list_pointer != NULL) {
        tmp = list_pointer;
        list_pointer = list_pointer -> next;
        free(tmp -> string);
        free(tmp);
    }
    *list = NULL;
}

int main() {
    List* list = NULL;
    int stop_flag;
    char tmp;

    stop_flag = 0;
    while (!stop_flag) {
        printf("%s", "enter list of srtings\n");

        get_list(&list);
        print(list);
        free_list(&list);

        printf("%s\n", "do you want to finish? [1/0]");
        scanf("%d%c", &stop_flag, &tmp);
        printf("\n");
    }
    return 0;
}