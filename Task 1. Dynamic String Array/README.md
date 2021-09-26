# Первое задание:
1. Ввести с клавиатуры произвольное количество строк произвольной длины и расположить их в массиве указателей на char.
2. Отсортировать строки лексикографически (по алфавиту)  любым известным методом, меняя местами только указатели
3. Распечатать результат столбиком.

**Требования к программе**: программа должна
- содержать минимум три функции (не считая `main()`):
    - ввода динамической строки,
    - сортировки массива строк,
    - вывода результата.
 - компилироваться без предупреждений (warnings);
 - корректно сортировать входные данные;
 - корректно обрабатывать пустые строки;
 - не падать (segmentation fault) вне зависимости от объема входных данных;
 - быть правильно оформленной (структурные отступы);
 - выделенная динамическая память должна освобождаться (free).

Рекомендуемые способы тестирования:

$ ./mysort <mysort.c  # проверять глазами

$ ./mysort </etc/passwd >p1
$ sort </etc/passwd >p2
$ diff -u p1 p2  # должны совпадать
$ valgrind   --leak-check=full  -v  ./mysort