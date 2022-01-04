//#include <stdlib.h>
#include <Arduino.h>
typedef enum {
    SYS_TASK_RUN_ONCE,
    SYS_TASK_RUN_REPEAT
} run_t;

typedef struct sys_task
{
    unsigned long int millis;
    void (*ptr)();
    run_t run_type;
    int gap;
} sys_task_t;

void sys_task_init();

void sys_task_handle();

void sys_task_run_once(void (*callback)(), int micro_time);

void sys_task_run_repeat(void (*callbac)(), int gap);
