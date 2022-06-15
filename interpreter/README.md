# Интерпретатор модельного языка программирования

Исполняемый бинарный файл интерпретатора `bin/myapp`. Пример программы `bin/example`.

## Вариант

Все правила написания программы описаны в файле `model_lang_prac.pdf`. Вариантная часть:
1. Условный оператор `if` (без `else`), вариант 1
2. Оператор цикла `while`
3. Оператор перехода `continue`, вариант 2
4. Тип данных `bool`, вариант 1
5. Дополнительная операция унарный плюс, вариант 1
6. Логические выражения вычисляются по обычной схеме, вариант 2

## Этапы работы:
- лексический анализатор (файл `scanner.h`)
- синтаксически управляемый перевод в польскую инвертированную запись с проверкой контекстных условий (файл `parser.h`)
- счёт программы (файл `executer.h`)

## Пример работы:

### Программный код:
```
/*
    you can see the work of semantic analizator by uncommenting lines:
    it will cause errors described on the same line
*/

program
{
    int a = 51, b = 6, c;
    string x = "abc", y, z = "abcd";
    bool d;
    /* string f = 17; */        /* incompatible data type for initialization */
    /* bool a; */               /* identifire 'a' is already declared */
    /* read(d); */              /* you can't read boolean variables*/

    c = (a + b) * 2;
    
    /* a = b + d; */            /* you can't use deveral data types within one equation */
    
    if (c >= 100 and x == z)
    {
        read (y);
        write (y);
        write (x + y + z, c);
    }
    
    while (c > 100)
    {
        c = c - 5;
        write (c);
        x = x + "step";
    }
    write (x);
} 
```

### Вывод:
```
109
104
99
abcstepstepstep
```

### Работа лексического анализатора:
```
        type code       type            lexeme

        8               (TW)            program
        20              (TD)            {
        5               (TW)            int
        49              (TID)           a 0
        22              (TD)            =
        46              int literal     51
        17              (TD)            ,
        49              (TID)           b 1
        22              (TD)            =
        46              int literal     6
        17              (TD)            ,
        49              (TID)           c 2
        16              (TD)            ;
        11              (TW)            string
        49              (TID)           x 3
        22              (TD)            =
        47              string literal  abc
        17              (TD)            ,
        49              (TID)           y 4
        17              (TD)            ,
        49              (TID)           z 5
        22              (TD)            =
        47              string literal  abcd
        16              (TD)            ;
        10              (TW)            bool
        49              (TID)           d 6
        16              (TD)            ;
        49              (TID)           c 2
        22              (TD)            =
        18              (TD)            (
        49              (TID)           a 0
        29              (TD)            +
        49              (TID)           b 1
        19              (TD)            )
        31              (TD)            *
        46              int literal     2
        16              (TD)            ;
        4               (TW)            if
        18              (TD)            (
        49              (TID)           c 2
        28              (TD)            >=
        46              int literal     100
        1               (TW)            and
        49              (TID)           x 3
        23              (TD)            ==
        49              (TID)           z 5
        19              (TD)            )
        20              (TD)            {
        9               (TW)            read
        18              (TD)            (
        49              (TID)           y 4
        19              (TD)            )
        16              (TD)            ;
        14              (TW)            write
        18              (TD)            (
        49              (TID)           y 4
        19              (TD)            )
        16              (TD)            ;
        14              (TW)            write
        18              (TD)            (
        49              (TID)           x 3
        29              (TD)            +
        49              (TID)           y 4
        29              (TD)            +
        49              (TID)           z 5
        17              (TD)            ,
        49              (TID)           c 2
        19              (TD)            )
        16              (TD)            ;
        21              (TD)            }
        13              (TW)            while
        18              (TD)            (
        49              (TID)           c 2
        26              (TD)            >
        46              int literal     100
        19              (TD)            )
        20              (TD)            {
        49              (TID)           c 2
        22              (TD)            =
        49              (TID)           c 2
        30              (TD)            -
        46              int literal     5
        16              (TD)            ;
        14              (TW)            write
        18              (TD)            (
        49              (TID)           c 2
        19              (TD)            )
        16              (TD)            ;
        49              (TID)           x 3
        22              (TD)            =
        49              (TID)           x 3
        29              (TD)            +
        47              string literal  step
        16              (TD)            ;
        21              (TD)            }
        14              (TW)            write
        18              (TD)            (
        49              (TID)           x 3
        19              (TD)            )
        16              (TD)            ;
        21              (TD)            }
        15
```

Польская инвертированная запись:
```
        type code       type            lexeme

0       53              RPN             adress  0
1       46              int literal     51
2       22
3       16              (TD)            ;
4       53              RPN             adress  1
5       46              int literal     6
6       22
7       16              (TD)            ;
8       53              RPN             adress  3
9       47              string literal  abc
10      38
11      16              (TD)            ;
12      53              RPN             adress  5
13      47              string literal  abcd
14      38
15      16              (TD)            ;
16      53              RPN             adress  2
17      49              (TID)           a 0
18      49              (TID)           b 1
19      29              (TD)            +
20      46              int literal     2
21      31              (TD)            *
22      22
23      16              (TD)            ;
24      49              (TID)           c 2
25      46              int literal     100
26      28              (TD)            >=
27      49              (TID)           x 3
28      49              (TID)           z 5
29      39
30      1               (TD)
31      52              RPN             label   45
32      55              RPN             FGO
33      53              RPN             adress  4
34      9               (TW)            read
35      49              (TID)           y 4
36      51              (TW)
37      49              (TID)           x 3
38      49              (TID)           y 4
39      45
40      49              (TID)           z 5
41      45
42      51              (TW)
43      49              (TID)           c 2
44      51              (TW)
45      49              (TID)           c 2
46      46              int literal     100
47      26              (TD)            >
48      52              RPN             label   66
49      55              RPN             FGO
50      53              RPN             adress  2
51      49              (TID)           c 2
52      46              int literal     5
53      30              (TD)            -
54      22
55      16              (TD)            ;
56      49              (TID)           c 2
57      14              (TW)            write
58      53              RPN             adress  3
59      49              (TID)           x 3
60      47              string literal  step
61      45
62      38
63      16              (TD)            ;
64      52              RPN             label   45
65      54              RPN             GO
66      49              (TID)           x 3
67      51              (TW)
```

## Запуск и отладка в vscode

### Файл `task.json`

```
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "make",
            "group": "build",
            "problemMatcher": "$gcc"
        },
        {
            "type": "cppbuild",
            "label": "C/C++: g++ build active file",
            "command": "/usr/bin/g++",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Task generated by Debugger."
        }
    ]
}
```

### Файл `launch.json`

```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/bin/myapp",
            "args": ["${workspaceFolder}/bin/example"],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```