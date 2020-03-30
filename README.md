## X-Tasker
> 基于时间片轮询的一个简单任务调度器。  
> 不涉及RTOS的抢占式任务调度。硬件资源只需定时器Timer，无需额外的任务堆栈。  
> 任务数量由宏`TASK_NUM`指定，最大256。

### 实现
#### 1. Task Tick
在Timer中断中调用`void Task_Tick(void);`。
> CubeMX生成的STM32 Project默认提供时基为1ms的SysTick。  
> 在`void HAL_SYSTICK_Callback(void);`中调用`void Task_Tick(void);`，即可实现时间周期为1ms的Task Tick。

#### 2. Task Create
`Task_Create`函数中将任务函数传递给`pTask`，任务时间片传递给`RunTime`。

#### 3. Task Delete
`Task_Delete`函数中将任务函数传递给`pTask`。

#### 4. Task Init
`Task_Init`函数中调用`Task_Create`函数创建初始化任务。任务调用完毕后，调用`Task_Delete`函数删除已创建的函数。

#### 5. Task Handle
在`main.c`中的任务轮询中调用`Task_Handle`函数。

```
void main(void)
{
  while(1)
  {
    Task_Handle();  
  }
}

```

### 任务
任务函数格式为`void Task_Task1(void);`。  
特殊用法：任务Task1中创建Task2后，删除Task3。

```
void Task_Task1(void)
{
  Task_Create(Task_Task2, 200);   /* 创建Task_Task2任务，时间片200ms */
  Task_Delete(Task_Task3);        /* 删除Task_Task3任务 */

  /* other actions */
}

```

