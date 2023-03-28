#include <stdlib.h>

static int GLOBAL_INIT = 1;                         // Сегмент данных, глобальная
static int global_uninit;                           // Сегмент BSS, глобальная

int main(int argc, char **argv) {                   // Стек, локальная
    int local_init = 1;                             // Стек, локальная
    int local_uinit;                                // Стек, локальная
    
    static int local_static_init = 1;               // Сегмент данных, локальная
    static int local_static_uinit;                  // Сегмент BSS, локальная
    
    int *buff_ptr = (int *)malloc(sizeof(int));     // Стек, локальная, указывает на память в куче
}