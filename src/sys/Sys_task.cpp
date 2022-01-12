#include "Sys_task.h"
#define MAX_TASKS_NUM 3
#define NONE ((sys_task_t *)0)
sys_task_t * taskList[MAX_TASKS_NUM];

void sys_task_trigered(sys_task_t ** p_task);

void sys_task_init()
{
    for (int i = 0; i < MAX_TASKS_NUM; i++)
        taskList[i] = NONE;
}

void sys_task_handle()
{
    for (int i = 0; i < MAX_TASKS_NUM; i++)
    {
        if (taskList[i] != NONE)
        {
            // if on time, execute
            if (taskList[i]->millis < millis())
            {
                int time_start = millis();
                sys_task_trigered(&taskList[i]);
                int time_end = millis();
                if(time_end-time_start>1000) {
                    Serial.print("task ");
                    Serial.print(i);
                    Serial.print(": ");
                    Serial.print(time_end-time_start);
                    Serial.println("ms");
                }
            }
        }
    }
}

void sys_task_trigered(sys_task_t ** p_task)
{
    sys_task_t * task = * p_task;
    (* task->ptr)();
    switch (task->run_type)
    {
    case SYS_TASK_RUN_ONCE:
        //delete it
        free(task);
        (* p_task) = NONE;
        break;
    case SYS_TASK_RUN_REPEAT:
        task->millis = millis() + task->gap;
        break;
    default:
        break;
    }
}

void sys_task_run_once(void (*callback)(), int micro_time)
{
    sys_task_t *task = (sys_task_t *)malloc(sizeof(sys_task_t));
    task->millis = millis() + micro_time;
    task->ptr = callback;
    task->run_type = SYS_TASK_RUN_ONCE;
    // insert to the list
    for (int i = 0; i < MAX_TASKS_NUM; i++)
    {
        if (taskList[i] == NONE)
        {
            taskList[i] = task;
            break;
        }
    }
}

void sys_task_run_repeat(void (*callback)(), int gap) {
    sys_task_t *task = (struct sys_task *)malloc(sizeof(sys_task_t));
    task->millis = millis() + gap;
    task->ptr = callback;
    task->run_type = SYS_TASK_RUN_REPEAT;
    task->gap = gap;
    for (int i = 0; i < MAX_TASKS_NUM; i++) {
        if (taskList[i] == NONE)
        {
            taskList[i] = task;
            break;
        }
    }
}