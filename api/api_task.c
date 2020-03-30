#include "task.h"
//#include "includes.h"

Task_TypeDef   Task[TASK_NUM];
uint8_t        TaskIndex = 0;

void Task_Tick(void)
{
  uint8_t i = 0;
  
  for(i=0;i<TaskIndex;i++)
  {
    if(Task[i].Tick < Task[i].Time)
    {
      Task[i].Tick++;
    }
    else if(Task[i].Tick == Task[i].Time)
    {
      Task[i].Tick = 0;
      Task[i].Rflag = 1;
    }
  }
}

void Task_Handle(void)
{
  uint8_t i = 0;
  
  for(i=0;i<TaskIndex;i++)
  {
    if(Task[i].Rflag == 1)
    {
      Task[i].TaskFunc();
      Task[i].Rflag = 0;
    }
  }
}

void Task_Init(void)
{
  /* add your task here */
  Task_Create(Task_LED0_Toggle, 1000);
  Task_Create(Task_Get_RTC, 1000);
  Task_Create(Task_Battery_Monitor, 1000);
  Task_Create(Task_Instruction_Handle, 0);
}

uint8_t Task_Create(void (*pTask)(void), uint16_t RunTime)
{
  uint8_t i = 0;
  
  for(i=0;i<TaskIndex;i++)
  { 
    /* the task has been created */
    if(Task[i].TaskFunc == pTask)
      return 0;
  }
	
  if(TaskIndex < TASK_NUM)
  {
    Task[TaskIndex].Rflag = 0;
    Task[TaskIndex].Tick = 0;
    Task[TaskIndex].Time = RunTime;
    Task[TaskIndex].TaskFunc = pTask;
  }
  else
  {
    /* task queue is full */
    return 0;
  }
	
  TaskIndex++;
  return 1;	
}

uint8_t Task_Delete(void (*pTask)(void))
{
  uint8_t i, k = 0;

  for(i=0;i<TaskIndex;i++)
  {
    if(Task[i].TaskFunc == pTask)
      break;
  }
  
  /* the task has not been created */
  if(i == TaskIndex)
  {
    return 0;
  }

  for(k=i;k<TaskIndex-1;k++)
  {
    Task[k] = Task[k+1];
  }

  Task[TaskIndex-1].Rflag = 0;
  Task[TaskIndex-1].Tick = 0;
  Task[TaskIndex-1].Time = 0;
  Task[TaskIndex-1].TaskFunc = NULL;

  TaskIndex--;
  return 1;
}




