#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>

/* structures */

// info about one process
typedef struct {     
    char** args;
    int arg_count;
    int end;
} proc_info;

// info about one conveyor
typedef struct {
    proc_info* procs; 
    int proc_count;
    char* input, *output;
    int background_launch;
    int cd;
    int end;
} conv_info;

// info about whole command line
typedef struct {
    conv_info* convs;
    int conv_count;
} line_info;

/* prototypes */

// считать сырую строку до \n (без парсинга)
char* get_line();

// парсинг
char** split_line(char*, int*);

// вывод массива строк
void print_str_array(char**);

// true, если в строке нечётное число кавычек, false иначе
int odd_quotes(char*);

// запуск команты
int shell_execute(line_info);

// утилита
int vector_length(char**);

// удалить кавычки из строки
void delete_quotes(char**);

// находит все мэтчи с помощью regex
char** find_all_simple(char*, char*, int*); 

// функция парсинга введённой строки
line_info parse_line(char*);    

// функция парсинга одной команды
proc_info analyze(char**, char**, char**, int*, int*, int*);

// функция парсинга одного конвейера
conv_info build(char*);

// утилита
void print_line(line_info);

// реализация конвейера
void conveyor(conv_info);

/* main */

int main() {
    char* line;
    char** args;
    int size;    

    while (line = get_line()) {
        if (odd_quotes(line)) {
            printf("\nError: Unbalanced quotes\n");            
            continue;
        }
        
        line_info l = parse_line(line);
        shell_execute(l);
        // print_line(l);
    }

    return 0;
}

/* implementation */

char* get_line() {
    char dir[100];
    
    if (getcwd(dir, 100) == NULL) {
        printf("\nops\n");
    }
    
    printf("\n%s$ ", dir);

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

char** find_all_simple(char* pattern, char* string, int* word_count) {
    char* start;                // указатель, с помощью которого будем перемещаться по line
    char** result;
    
    result = malloc(sizeof(char*));
    int size_alloc = sizeof(char*);
    int size_result = 0;
    
    regex_t regex;              // регулярное выражение
    regmatch_t pmatch[1];       // struct, в которую запишется результат
    regoff_t match, len;        // смещение и длина мэтча    

    int error_code;

    if (error_code = regcomp(&regex, pattern, REG_EXTENDED)) {
        // в случае неправильного re_pattern
        char error_msg[60];
        regerror(error_code, &regex, error_msg, 60);
        printf("%s\n", error_msg);
        return NULL;
    }

    start = string;

    while (regexec(&regex, start, 1, pmatch, 0) == 0) {
        match = pmatch[0].rm_so;                        // первый символ мэтча
        len = pmatch[0].rm_eo - pmatch[0].rm_so;        // длина мэтча

        result[size_result] = malloc((len + 1) * sizeof(char));
        memmove(result[size_result], start + match, len * sizeof(char));
        result[size_result++][len] = '\0';        
        
        size_alloc += sizeof(char*);
        result = realloc(result, size_alloc);        

        start += pmatch[0].rm_eo;                       // сужаем область поиска мэтчей
    }
    
    result[size_result] = NULL;

    *word_count = size_result;

    return result;
}

line_info parse_line(char* string) {
    /* split line into conveyors by semicolon ; */
    int conv_count;
    char* pattern = "[^;]+";
    char** conv = find_all_simple(pattern, string, &conv_count);

    conv_info* convs = malloc(sizeof(conv_info));
    int alloc = sizeof(conv_info);
    
    int i;
    for (i = 0; i < conv_count; i++) {        
        convs[i] = build(conv[i]);        

        alloc += sizeof(conv_info);
        convs = realloc(convs, alloc);
    }

    conv_info tmp = {NULL, 0, NULL, NULL, 0, 0, 1};
    convs[i] = tmp;

    line_info result;
    result.convs = convs;
    result.conv_count = conv_count;    

    return result;
}

proc_info analyze(char** args, char** input, char** output, int* append, int* back, int* cd) {
    proc_info   result      = {NULL, 0, 0};
    char**      args_new    = malloc(sizeof(char*));
    int         size_alloc  = sizeof(char*);
    int         arg_count   = 0;
    
    *back   = 0;
    *input  = NULL;
    *output = NULL;
    *append = 0;

    char** p;
    for (p = args; *p; p++) {
        if (strcmp(*p, "<") == 0) {
            /* looking for file of input redirection */
            p++;
            if (*p != NULL) 
                *input = *p;
            else {
                printf("\nSomething's wrong with this:\n");
                print_str_array(args);
                exit(1);
            }            
        } else if (strcmp(*p, ">") == 0) {
            /* looking for file of ouput redirection */
            p++;
            if (*p != NULL) 
                *output = *p;
            else {
                printf("\nSomething's wrong with this:\n");
                print_str_array(args);
                exit(1);
            }            
        } else if (strcmp(*p, ">>") == 0) {
            /* looking for file of output redirection */
            p++;
            if (*p != NULL) {
                *output = *p;
                *append = 1;
            }
            else {
                printf("\nSomething's wrong with this:\n");
                print_str_array(args);
                exit(1);
            }            
        } else if (strcmp(*p, "&") == 0) {
            *back = 1;
        } else {
            if (strcmp(*p, "cd") == 0)
                *cd = 1;                
            /* build vector of arguments */
            int len = strlen(*p);

            args_new[arg_count] = malloc((len + 1) * sizeof(char));
            memmove(args_new[arg_count], *p, len * sizeof(char));
            args_new[arg_count++][len] = '\0';

            delete_quotes(&args_new[arg_count - 1]);
            
            size_alloc += sizeof(char*);
            args_new = realloc(args_new, size_alloc);
        }
    }

    args_new[arg_count] = NULL;

    result.args = args_new;
    result.arg_count = arg_count;
    
    return result;    
}

conv_info build(char* conveyor) {
    /* split conv into procs by vertical line | */
    int proc_count;
    char** procs = find_all_simple("[^|]+", conveyor, &proc_count);

    /* parsing first proc in conv separately */
    int arg_count;
    char* pattern = "&{1,2}|<|>{1,2}|[^ &<>]+|[^ &><]*?\"[^\"]*\"[^ &><]*";
    char** args = find_all_simple(pattern, procs[0], &arg_count);
    
    /* analyzing first proc */
    char *input = NULL,     // path to input redirect file
         *output = NULL,    // path to input redirect file
         *buf = NULL;

    int append,             // flag whether output needs to append, not overwrite
        back,               // flag whether launch conv in background
        cd = 0;
    
    proc_info proc = analyze(args, &input, &output, &append, &back, &cd);

    /* creating conveyor: array of 'proc_info' structures */
    proc_info* conv = malloc(sizeof(proc_info));
    int alloc = sizeof(proc_info);
    int size = 0;

    /* filling in conveyor */
    conv[size++] = proc;        // first proc
    alloc += sizeof(proc_info);
    conv = realloc(conv, alloc);

    int j;        
    for (j = 1; j < proc_count; j++) {
        args = find_all_simple(pattern, procs[j], &arg_count);
        proc = analyze(args, &buf, &output, &append, &back, &cd);

        conv[size++] = proc;
        alloc += sizeof(proc_info);
        conv = realloc(conv, alloc);
    }

    proc_info tmp = {NULL, 0, 1};   
    conv[size] = tmp;

    /* creating result */
    conv_info result;
    result.procs = conv;
    result.proc_count = proc_count;
    result.input = input;
    result.output = output;
    result.background_launch = back;
    result.cd = cd;
    result.end = 0;
    
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

int shell_execute(line_info line) {  
    if (line.convs[0].cd) {    
        char* dir;
        
        if (line.convs[0].procs[0].arg_count == 1)
            dir = getenv("HOME");
        else 
            dir = line.convs[0].procs[0].args[1];
        
        if (chdir(dir) == -1) {
            printf(">> Error\n");
        }
        return 0;
    }
    
    conv_info* t;
    for(t = line.convs; !t->end; t++) {
        conveyor(*t);
    }    
    
    
    wait(NULL);
    
    return 0;
}

void print_line(line_info line) {
    conv_info* t;
    for (t = line.convs; t -> end != 1; t++) {                      
        printf("\ninput: %s\n", t -> input);
        printf("output: %s\n", t -> output);
        printf("back: %d\n", t -> background_launch);
        printf("cd: %d\n", t -> cd);

        proc_info* k;
        for (k = t -> procs; k -> end != 1; k++) {
            printf("procs %d:\n", k->arg_count);
            char** s;
            for (s = k -> args; *s; s++)
                printf("%s\n", *s);
            printf("\n");
        }
    }
}

void conveyor(conv_info conv) {
    pid_t pid = fork();
    if (pid == 0) {
        /* conveyor */        
        if (conv.proc_count == 0) {
            printf("\nsomething's wrong with parameters\n");
            exit(1);
        }

        if (conv.input != NULL) {
            int in;
            
            if ((in = open(conv.input, O_RDONLY)) == -1) {
                printf("\nsomething's wrong with %s\n", conv.input);
                exit(1);
            }
            
            dup2(in, 0);
        }

        if (conv.output != NULL) {
            int out;    

            if ((out = open(conv.output, O_WRONLY | O_CREAT, 0666)) == -1) {
                printf("\nsomething's wrong with %s\n", conv.output);
                exit(1);
            }

            dup2(out, 1);
        }                

        if (conv.proc_count == 1) {
            if (fork() == 0) { 
                int arg_count = 0;           
                char** args = conv.procs[0].args;
                execvp(args[0], args);
                printf("\nSomething's wrong with proccess 0: %s\n", args[0]);            
                exit(1);
            } else {
                wait(NULL);            
                exit(0);            
            }
        }    
        
        int fd[2];
        int i;
        proc_info* proc;        

        for (proc = conv.procs, i = 0; i < conv.proc_count; proc++, i++) {
            pipe(fd);        
        
            char** args = proc->args;

            switch (fork()) {
            case -1: {
                printf("doesn't fork()");
                break;
            }
            
            case 0: {
                if (i != conv.proc_count - 1) {
                    dup2(fd[1], 1);                                    
                }
                
                close(fd[1]); 
                close(fd[0]);                                            

                execvp(args[0], args);
                printf("error on proc %s\n", args[0]);
                exit(1);
            }
            
            default:                                
                close(fd[1]);     
                dup2(fd[0], 0);
                close(fd[0]);
            }
        }

        while (wait(NULL) != -1) {;}
        exit(0);        
        printf("\nsomething's wrong here!\n");
    }
    
    if (pid == -1) {
        /* fork error */
        return;
    } else {
        /* waiting until conveyor is done */
        int status;
        wait(&status);        
        return;
    }
}