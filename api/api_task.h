#ifndef __API_TASK_H_
#define __API_TASK_H_

#define TASK_NUM      (uint8_t)(64u)      /* task number */

/* Definition for Task Handler */
typedef struct
{
  uint8_t             Rflag;
  uint16_t            Tick;
  uint16_t            Time;
  
  void                (*TaskFunc)(void);  
} Task_TypeDef;

extern Task_TypeDef   Task[TASK_NUM];
extern uint8_t        TaskIndex;

void Task_Tick(void);
void Task_Handle(void);
void Task_Init(void);

uint8_t Task_Create(void (*pTask)(void), uint16_t RunTime);
uint8_t Task_Delete(void (*pTask)(void));

#endif /* __API_TASK_H_ */
