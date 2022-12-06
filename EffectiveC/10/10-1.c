#include <stdlib.h>

int a;          // Неявная внешняя компоновка
static int i;   // Объявляется с явной внутренней компоновкой 
                // из-за static и объявления на уровне файла

extern void foo(int j) {
    // foo объявляется с явной внешней компоновкой
    // у j нет компоновки, так как это параметр
    
    static int s; // нет компоновки так как это блочный идентификатор
}