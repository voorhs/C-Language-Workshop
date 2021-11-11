#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_one_string(char**, char**, int*, int*);   // считать одно слово
int getchar_condition(char*);                       // вспомогательная утилита
char** read_line(int*);                             // прочитать строку
void print_string_array(char**);                    // напечатать массив строк

int main() {
    char** string_array;
    int end_of_file = 0;

    string_array = read_line(&end_of_file);

    while (!end_of_file) {
        print_str_array(string_array);
        string_array = read_line(&end_of_file);        
    }

    print_str_array(string_array);
    return 0;
}

int getchar_condition(char* char_) {
    *char_ = getchar();
    return (*char_ != '\n') && (*char_ != EOF);
}

// результат работы: символьное слово, служебное слово, буферный char, флаг пустых символов и флаг конца файла
char* get_one_string(char** service_word, char** last_char, int* continue_, int* eof_flag) {
    char *result = (char*)malloc(sizeof(char));
    char char_;

    int size_of_string = 0;
    int size_alloc = sizeof(char);

    char* service = NULL;
    char* next_char = NULL;

    int raw_string = 0;     // режим считывания без интерпретирования

    while (getchar_condition(&char_)) {
        if (char_ == '\"') {
            raw_string = !raw_string;
            continue;
        }

        if (!raw_string && (char_ == ' '))
            break;
        
        // если встретили служебное слово
        if (!raw_string && ((char_ == '&') || (char_ == '|') || (char_ == '>'))) {
            next_char = malloc(sizeof(char));
            next_char[0] = getchar();
            if (char_ == *next_char) {
                service = malloc(sizeof(char) * 3);
                service[0] = char_;
                service[1] = char_;
                service[2] = '\0';
                
                next_char[0] = getchar();
                if (next_char[0] == '\n') {
                    break;                    
                }                
                break;
            }
            else {
                service = malloc(sizeof(char) * 2);
                service[0] = char_;
                service[1] = '\0';                
                break;
            }
        }

        // если встретили одинарное служебное слово
        if (!raw_string && ((char_ == ';') || (char_ == '<') \
            || (char_ == '(') || (char_ == ')') || (char_ == '.'))) {
            next_char = malloc(sizeof(char));
            next_char[0] = getchar();
            if (next_char[0] == EOF) {
                *eof_flag = 1;                
            }
            service = malloc(sizeof(char) * 2);
            service[0] = char_;
            service[1] = '\0';
            break;
        }

        result[size_of_string++] = char_;
        size_alloc += sizeof(char);
        result = realloc(result, size_alloc);
    }

    result[size_of_string] = '\0';

    *last_char = next_char;
    *service_word = service;

    *continue_ = 0;

    if ((char_ == EOF) || *eof_flag) {
        *eof_flag = 1;
        return NULL;
    }
    else if (char_ == '\n') {        
        *last_char = malloc(sizeof(char));
        **last_char = '\n';
    }
    else if (size_of_string == 0) {
        if (*service_word == NULL)
            *continue_ = 1;        
    }
    return result;
}

// результат работы: массив строк и флаг конца файла
char** read_line(int* eof_flag) {
    printf("\nВход:\n");

    char** result = malloc(sizeof(char*));
    char* service_word;
    char* buffer;
    char prefix = '\0';
    int continue_flag = 0;    
    int eof_string_flag = 0;
    char* word = get_one_string(&service_word, &buffer, &continue_flag, &eof_string_flag);

    int size_alloc = 0;
    int string_count = 0;

    while (word) {
        if (!continue_flag) {
            if (strcmp(word, "") != 0) {
                size_alloc += sizeof(char*);
                result = realloc(result, size_alloc);
                result[string_count++] = word;
            }
        }

        if (service_word) {
            size_alloc += sizeof(char*);
            result = realloc(result, size_alloc);
            result[string_count++] = service_word;
        }            
        
        if (buffer) {
            prefix = *buffer;
            if (*buffer == '\n') {
                size_alloc += sizeof(char*);
                result = realloc(result, size_alloc);
                result[string_count++] = NULL;
                break;
            } else if (*buffer == EOF) {
                size_alloc += sizeof(char*);
                result = realloc(result, size_alloc);
                result[string_count++] = NULL;
                *eof_flag = 1;
                break;
            } else if ((prefix == ';') || (prefix == '<') \
            || (prefix == '(') || (prefix == ')') || (prefix == '.')) {
                size_alloc += sizeof(char*);
                result = realloc(result, size_alloc);
            
                service_word = malloc(sizeof(char) * 2);
                service_word[0] = prefix;
                service_word[1] = '\0';
                prefix = '\0';
            
                result[string_count++] = service_word;
                free(service_word);
                service_word = NULL;
                continue;
            } else if ((prefix == '&') || (prefix == '|') || (prefix == '>')) {
                prefix = getchar();
                if (*buffer == prefix) {
                    service_word = malloc(sizeof(char) * 3);
            
                    service_word[0] = *buffer;
                    service_word[1] = prefix;
                    service_word[2] = '\0';
            
                    size_alloc += sizeof(char*);
                    result = realloc(result, size_alloc);
                    result[string_count++] = service_word;
                    free(service_word);
                    service_word = NULL;
            
                    prefix = getchar();
                    if (prefix == '\n') {
                        size_alloc += sizeof(char*);
                        result = realloc(result, size_alloc);
                        result[string_count++] = NULL;
                        break;
                    }
                    continue;
                } else if (prefix == '\n') {
                    service_word = malloc(sizeof(char) * 2);
                                
                    service_word[0] = *buffer;
                    service_word[1] = '\0';
            
                    size_alloc += sizeof(char*);
                    result = realloc(result, size_alloc);
                    result[string_count++] = service_word;
                    size_alloc += sizeof(char*);
                    result = realloc(result, size_alloc);
                    result[string_count++] = NULL;
                    free(service_word);
                    break;
                }             
            }
        }

        if (eof_string_flag) {
            size_alloc += sizeof(char*);
            result = realloc(result, size_alloc);
            result[string_count++] = NULL;
            *eof_flag = 1;
        }

        word = get_one_string(&service_word, &buffer, &continue_flag, &eof_string_flag);
        if (continue_flag && (prefix != '\0') && (prefix != ' ')) {                        
            word = realloc(word, 2);
            word[0] = prefix;
            word[1] = '\0';
            prefix = '\0';            
            continue_flag = 0;
            continue;            
        }
        
        if ((prefix != '\0') && (prefix != ' ')) {
            word = realloc(word, (1 + strlen(word)) * sizeof(char));
            word[strlen(word) + 1] = '\0';
            int i;
            for (i = strlen(word); i > 0; i--) {
                word[i] = word[i-1];
            }
            word[0] = prefix;
            prefix = '\0';
        }
    }

    if (string_count == 0) {
        *eof_flag = 1;
        return NULL;
    }
    else
        return result;
}

void print_str_array(char** sarray) {
    if (sarray == NULL)
        return;
    int i;
    printf("\nВыход\n");
    for(i = 0; sarray[i]; i++) {
        printf("%s\n", sarray[i]);
    }
    printf("\n\n");
}