#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* prototypes */

char* get_line();                   // считать сырую строку до \n (без парсинга)
char** parse_line(char*);           // парсинг
void print_str_array(char**);       // вывод массива строк
int odd_quotes(char*);              // true, если в строке нечётное число кавычек, false иначе
int shell_execute(char**);
int vector_length(char**);
void delete_quotes(char**);

/* main */

int main() {
    char* line;
    char** args;
        
    while (line = get_line()) {
        if (odd_quotes(line)) {
            printf("\nError: Unbalanced quotes\n");            
            continue;
        }
        
        args = parse_line(line);
        print_str_array(args); 
        shell_execute(args);
    }

    return 0;
}

/* implementation */

char* get_line() {
    printf("input: ");

    char* result = malloc(sizeof(char));
    int size_alloc = sizeof(char);
    int size_of_string = 0;
    char c;

    c = getchar();
    if (c == EOF) {
        free(result);
        return NULL;
    }

    while (c != '\n') {
        result[size_of_string++] = c;
        size_alloc += sizeof(char);
        result = realloc(result, size_alloc);
        c = getchar();
    }

    result[size_of_string] = '\0';

    return result;
}

int odd_quotes(char* line) {
    int quotes_count = 0;
    char* p;
    for (p = line; *p; p++) {
        quotes_count += (*p == '\"');
    }
    return quotes_count % 2;
}

char** parse_line(char* line) {
    char* start;                // указатель, с помощью которого будем перемещаться по line
    char** result;
    
    result = malloc(sizeof(char*));
    int size_alloc = sizeof(char*);
    int size_result = 0;
    
    regex_t regex;              // регулярное выражение
    regmatch_t pmatch[1];       // struct, в которую запишется результат
    regoff_t match, len;        // смещение и длина мэтча

    static const char *const re_pattern = \
    "[^ &()|;><\\.]*?\"[^\"]*\"[^ &()|;><\\.]*|[^ &()|;><\\.]+|[&]{1,2}|[>]{1,2}|[|]{1,2}|[;<()\\.]{1}";

    int error_code;

    if (error_code = regcomp(&regex, re_pattern, REG_EXTENDED)) {
        // в случае неправильного re_pattern
        char error_msg[60];
        regerror(error_code, &regex, error_msg, 60);
        printf("%s\n", error_msg);
        return NULL;
    }

    start = line;

    while (regexec(&regex, start, 1, pmatch, 0) == 0) {
        match = pmatch[0].rm_so;                        // первый символ мэтча
        len = pmatch[0].rm_eo - pmatch[0].rm_so;        // длина мэтча

        result[size_result] = malloc((len + 1) * sizeof(char));
        memmove(result[size_result], start + match, len * sizeof(char));
        result[size_result++][len] = '\0';

        delete_quotes(&result[size_result - 1]);
        
        size_alloc += sizeof(char*);
        result = realloc(result, size_alloc);        

        start += pmatch[0].rm_eo;                       // сужаем область поиска мэтчей
    }
    
    result[size_result] = NULL;

    return result;
}

void delete_quotes(char** string) {    
    char* result;
    char* cpy = *string;
    int i;

    int size_result = 0;
    int size_alloc = sizeof(char);

    result = malloc(sizeof(char));

    for (i = 0; cpy[i]; i++)
        if (cpy[i] != '\"') {
            result[size_result++] = cpy[i];
            size_alloc += sizeof(char);
            result = realloc(result, size_alloc * sizeof(char));
        }

    result[size_result] = '\0';

    memmove(*string, result, i);   // ответ
    free(result);
}

void print_str_array(char** sarray) {
    if (sarray == NULL)
        return;    

    printf("output:\n");

    char** p;

    for(p = sarray; *p; p++) {
        printf("%s\n", *p);
    }
    printf("\n");
}

int vector_length(char** vect) {
    char** p;
    int result = 0;
    
    for (p = vect; *p; p++) {
        result += 1;
    }

    return result;
}

int shell_execute(char** args) {
    if (strcmp(args[0], "cd") == 0) {
        char* dir;
        
        if (vector_length(args) == 1)
            dir = getenv("HOME");
        else 
            dir = args[1];
        
        if (chdir(dir) == -1) {
            printf(">> Error\n");
        }
        return 0;
    }

    if (fork() == 0) {
        execvp(args[0], args);
        printf(">> Error\n");
    }
    
    wait(NULL);
    
    return 0;
}