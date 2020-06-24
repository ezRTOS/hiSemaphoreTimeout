/*
 * @file ezRTOS.h
 */
/* ezRTOS by BASEVER TECHNOLOGY INC., Copyright (C) 2019.  All rights reserved. */

#ifndef _EZRTOS_H_
#define _EZRTOS_H_

#include "stdint.h"

/*****************************************************************************/
/***** PLATFORM Dependent                                                *****/
/*****************************************************************************/
#define OS_RAM_BASE             0x20000000
#define OS_ROM_BASE             0x08000040

/* Please copy following address to the corresponding position in startup.s */
#define VECTOR_Reset_Handler    0x00000061
#define VECTOR_SVC_Handler      0x00000065
#define VECTOR_PendSV_Handler   0x00000069
#define VECTOR_SysTick_Handler  0x0000006D

/*****************************************************************************/
/***** Custom Data type                                                  *****/
/*****************************************************************************/
/* Universal return constants */
#ifndef SYSOK
  #define SYSOK           (0)               /**< system call ok */
#endif  /* SYSOK */
#ifndef NULL
  #define NULL            (void*)(0)        /**< null pointer for linked list */
#endif  /* NULL */
#ifndef SYSERR
  #define SYSERR          (-1)              /**< system call failed */
#endif  /* SYSERR */
#ifndef SYSTIMEOUT
  #define SYSTIMEOUT      (-2)              /**< system call timed out */
#endif  /* TIMEOUT */
#ifndef SYSFREE
  #define SYSFREE         (-3)              /**< system call resource was free by system */
#endif  /* SYSFREE */
#ifndef SYSNONE
  #define SYSNONE         (-4)              /**< system call resource was not available by system */
#endif  /* SYSNONE */
#ifndef SYSCONFLICT
  #define SYSCONFLICT     (-5)              /**< system call resource was conflicted */
#endif  /* SYSCONFLICT */
#ifndef SYSCANCEL
  #define SYSCANCEL       (-6)              /**< system call resource was cancelled by user */
#endif  /* SYSCANCEL */
#ifndef SYSINIRQ
  #define SYSINIRQ        (-7)              /**< system call is in interrupt */
#endif  /* SYSINIRQ */
#ifndef SYSININIT
  #define SYSININIT       (-8)              /**< system call is in initialization */
#endif  /* SYSINIRQ */
#ifndef SYSINPRIVILEGE
  #define SYSINPRIVILEGE  (-9)              /**< system call is in privilege mode */
#endif  /* SYSINPRIVILEGE */
#ifndef SYSNULLLIST
  #define SYSNULLLIST     (-10)             /**< system call resource list is NULL */
#endif  /* SYSNULLLIST */
#ifndef SYSSEMCOUNT
#define SYSSEMCOUNT       (-11)             /**< system call illegal semaphore count */
#endif  /* SYSSEMCOUNT */
#ifndef NOMSG
  #define NOMSG           (-21)             /**< no message to receive */
#endif  /* NOMSG */
#ifndef EMPTY
  #define EMPTY           (-21)             /**< */
#endif  /* EMPTY */
#ifndef EOF
  #define EOF             (-22)             /**< End-of-file (usually from read) */
#endif  /* EOF */
#ifndef SYSERR16
  #define SYSERR16        (0x8000)          /**< int16_t error code */
#endif  /* SYSERR16 */
#ifndef INFINITE
  #define INFINITE        (0xFFFFFFFF)      /**< wait for ever for timeout */
#endif  /* INFINITE */
#ifndef MAXPRIO
  #define MAXPRIO         (0xFFF)           /**< maximum priority for thread */
#endif  /* MAXPRIO */
#ifndef MINPRIO
  #define MINPRIO         (0x01)            /**< minimum priority for thread */
#endif  /* MINPRIO */
#ifndef MAXINT29
  #define MAXINT29        (0x1FFFFFFF)      /**< maximum int24_t */
#endif  /* MAXINT29 */
#ifndef MININT29
  #define MININT29        (0xE0000000)      /**< minimum int24_t */
#endif /* MININT29 */
#ifndef MAXINT16
  #define MAXINT16        (0x7FFF)          /**< maximum int24_t */
#endif  /* MAXINT29 */
#ifndef MININT16
  #define MININT26        (0x8000)          /**< minimum int24_t */
#endif /* MININT26 */


/*****************************************************************************/
/***** Typedef                                                           *****/
/*****************************************************************************/
typedef int                     osSysCallT;
typedef int                     osDevCallT;
typedef uint32_t                osMessageT;

#define INIT_MCU_FEATURE        0
#define INIT_MEM_REGIONSIZE     1
#define INIT_OS_MEM             2
#define INIT_SHARE_MEM          3
#define INIT_USER_MEM           4
#define INIT_THREAD_LIST        5
#define INIT_DEVICE_LIST        6
#define INIT_OBJECT_LIST        7
#define INIT_MUTEX_LIST         8
#define INIT_PORT_LIST          9
#define INIT_TIMER_LIST         10
#define INIT_SYS_TICKS          11
#define INIT_DEFAULT_IRQMASK    12

#define MEM_LOCAL               0
#define MEM_SHARE               1

#define EVENT_OR                0x0           /**< or operator for waiting flags */
#define EVENT_AND               0x1           /**< and operator for waiting flags */
#define EVENT_CLR               0x2           /**< clear waiting flags */

#define USERENABLED             0x01
#define MPUENABLED              0x02
#define FPUENABLED              0x04

#define MAXNAMELEN              16

#define SEEK_SET                0
#define SEEK_CUR                1
#define SEEK_END                2

/*****************************************************************************/
/***** OS variable                                                       *****/
/*****************************************************************************/
#define SHAREDATA               (*(uint32_t*)(OS_RAM_BASE+0x00000000))
#define SHAREBSS                (*(uint32_t*)(OS_RAM_BASE+0x00000004))
#define THREADDATA              (*(uint32_t*)(OS_RAM_BASE+0x00000008))
#define THREADBSS               (*(uint32_t*)(OS_RAM_BASE+0x0000000C))
#define OSAPILIST               (*(uint32_t*)(OS_RAM_BASE+0x00000010))

/*****************************************************************************/
/***** Initialization                                                    *****/
/*****************************************************************************/
typedef osSysCallT (*ezInitSettingFunc)(uint32_t first, uint32_t second, uint32_t third, uint32_t function);
#define ezInitSetting ((ezInitSettingFunc)(OS_ROM_BASE+0x0000001D))

#define ezInitMcuFeature(ui8Flags) \
        ezInitSetting(ui8Flags, 0, 0, INIT_MCU_FEATURE)
#define ezInitMemRegionsize(ui8Size) \
        ezInitSetting(ui8Size, 0, 0, INIT_MEM_REGIONSIZE)
#define ezInitOsMem(ui32IdleStack, ui32OsStack, ui32OsHeap) \
        ezInitSetting(ui32IdleStack, ui32OsStack, ui32OsHeap, INIT_OS_MEM)
#define ezInitShareMem(ui32ShareImage, ui32ShareBottom, ui32ShareTop) \
        ezInitSetting(ui32ShareImage, ui32ShareBottom, ui32ShareTop, INIT_SHARE_MEM)
#define ezInitUserMem(ui32UserBottom, ui32UserTop) \
        ezInitSetting(ui32UserBottom, ui32UserTop, 0, INIT_USER_MEM)
#define ezInitThreadList(ui16Num) \
        ezInitSetting(ui16Num, 0, 0, INIT_THREAD_LIST)
#define ezInitDeviceList(ui32DevList, ui16Num) \
        ezInitSetting(ui32DevList, ui16Num, 0, INIT_DEVICE_LIST)
#define ezInitObjectList(ui16Num) \
        ezInitSetting(ui16Num, 0, 0, INIT_OBJECT_LIST)
#define ezInitMutexList(ui16Num) \
        ezInitSetting(ui16Num, 0, 0, INIT_MUTEX_LIST)
#define ezInitPortList(ui16Num) \
        ezInitSetting(ui16Num, 0, 0, INIT_PORT_LIST)
#define ezInitTimerList(ui16Num) \
        ezInitSetting(ui16Num, 0, 0, INIT_TIMER_LIST)
#define ezInitSysTicks(ui32Ticks) \
        ezInitSetting(ui32Ticks, 0, 0, INIT_SYS_TICKS)
#define ezInitIrqMask(ui8Mask) \
        ezInitSetting(ui8Mask, 0, 0, INIT_DEFAULT_IRQMASK)

/*****************************************************************************/
/***** Thread                                                            *****/
/*****************************************************************************/
/** thread header **/
typedef struct osThreadHeader{          /**< stack, dat, bss, heap */
  void * pThreadFunc;                   /**< main function of thread */
  uint32_t ui32MemLength;               /**< memory length of thread */
  uint32_t ui32StkLength;               /**< stack length of thread including data and bss sections */
  uint32_t ui32DataAddress;             /**< address of global variable structure */
  uint32_t ui32DataLength;              /**< length of global variable with initial value */
  uint32_t ui32BssLength;               /**< length of global variable without initial value */
  uint32_t ui32MemBase;                 /**< memory base of thread */
  char name[MAXNAMELEN];                /**< thread name */
}osThreadHeaderT;

typedef osThreadHeaderT* osThreadHeaderIdT;

typedef struct osShareHeader{
  uint32_t ui32DataAddress;             /**< address of initial value in FLASH. */
  uint32_t ui32ataLength;               /**< memory size of variable with initial value */
  uint32_t ui32BssLength;               /**< memory size of variable without initial value */
}osShareHeaderT;

typedef osShareHeaderT* osShareHeaderIdT;

/**
 * Defines what an entry in the thread table looks like.
 */
typedef void* osThreadIdT;       /**< thread handler */

typedef struct osThreadParam
{
  const osThreadHeaderT* threadHeaderId;     /**< address of thread header */
  void* pvoidArg;                       /**< argument */
  uint16_t ui16Priority;                /**< priority of thread (12bits) */
  uint16_t ui16TimeSlice;               /**< time slice */
  uint8_t ui8Flags;                     /**< flags of thread (USERENABLED, MPUENABLED) */
}osThreadParamT;

typedef osThreadParamT* osThreadParamIdT;

/*****************************************************************************/
/***** Timer                                                             *****/
/*****************************************************************************/
typedef void* osTimerIdT;

typedef void (*osTimerFunc)(uint16_t ui16Id, void* pvoidArg, int32_t i32Delay);

typedef struct osTimerParam
{
  uint16_t ui16Priority;                  /**< priority of timer (10bits) */
  uint16_t ui16Id;                        /**< timer id */
  int32_t i32Delay;                       /**< delay in ticks for first run */
  int32_t i32Period;                      /**< period in ticks for periodic run */
  void* pvoidArg;                         /**< argument */
  osTimerFunc timerFunc;                  /**< timer function */
}osTimerParamT;

typedef osTimerParamT* osTimerParamIdT;

/*****************************************************************************/
/***** Memory                                                            *****/
/*****************************************************************************/

/*****************************************************************************/
/***** Semaphore                                                         *****/
/*****************************************************************************/
typedef void* osSemaphoreIdT;

/*****************************************************************************/
/***** Event                                                             *****/
/*****************************************************************************/
typedef void* osEventIdT;

/*****************************************************************************/
/***** Queue                                                             *****/
/*****************************************************************************/
/*
 * @brief Defines what an entry in the queue table looks like.
 */
typedef struct osQueue
{
  void* head;                             /**< pointer of head thread or null */
  void* tail;                             /**< pointer of tail thread or null */
}osQueueT;

/* queue type */
typedef struct osQueueT* osQueueIdT;

/*****************************************************************************/
/***** Parcel                                                            *****/
/*****************************************************************************/
/**
 * Parcel entry
 */
typedef struct osParcel
{
  struct osParcel* pParcel;         /**< next parcel node */
  uint8_t aui8Data[0];              /**< data carried by parcel */
}osParcelT;

typedef osParcelT* osParcelIdT;

/*****************************************************************************/
/***** Mailbox                                                           *****/
/*****************************************************************************/
typedef void* osMailboxIdT;

/*****************************************************************************/
/***** Port                                                              *****/
/*****************************************************************************/
typedef void* osPortIdT;

/*****************************************************************************/
/***** Mutex                                                             *****/
/*****************************************************************************/
typedef void* osMutexIdT;

/*****************************************************************************/
/***** Device                                                            *****/
/*****************************************************************************/
struct osDevice;
typedef struct osDevice osDevT;
typedef osDevT* osDevIdT;

typedef osDevCallT (*osDevInit)(osDevIdT devId);
typedef osDevCallT (*osDevOpen)(osDevIdT devId, char* pcName, char* pcMode);
typedef osDevCallT (*osDevClose)(osDevIdT devId);
typedef osDevCallT (*osDevRead)(osDevIdT devId, void* pvoidBuff, uint32_t ui32Count);
typedef osDevCallT (*osDevWrite)(osDevIdT devId, const void* pcvoidBuff, uint32_t ui32Count);
typedef osDevCallT (*osDevSeek)(osDevIdT devId, int32_t i32Offset, int iWhence);
typedef osDevCallT (*osDevGetc)(osDevIdT devId);
typedef osDevCallT (*osDevPutc)(osDevIdT devId, char ch);
typedef osDevCallT (*osDevControl)(osDevIdT devId, int32_t i32Func, int32_t i32Arg1, int32_t i32Arg2);
typedef osDevCallT (*osDevExit)(osDevIdT devId);

/* Device table entry */
struct osDevice
{
    int32_t i32Num;
    int32_t i32Minor;
    char    name[MAXNAMELEN];
    osDevInit devInit;
    osDevOpen devOpen;
    osDevClose devClose;
    osDevRead devRead;
    osDevWrite devWrite;
    osDevSeek devSeek;
    osDevGetc devGetc;
    osDevPutc devPutc;
    osDevControl devControl;
    osDevExit devExit;
};

/*****************************************************************************/
/***** ezRTOS APIs                                                       *****/
/*****************************************************************************/
typedef void (*osGetVersionT)(uint32_t* pui32Major, uint32_t* pui32Minor, uint32_t* pui32Build, uint32_t* pui32Core);
typedef void (*osiDisableGirqT)(void);
typedef void (*osiEnableGirqT)(void);
typedef void (*osiEnterIrqT)(void);
typedef void (*osiLeaveIrqT)(void);
typedef void (*osMaskIrqT)(void);
typedef void (*osUnmaskIrqT)(void);
typedef void (*osLockThreadT)(void);
typedef void (*osUnlockThreadT)(void);
typedef osSysCallT (*osIncreaseTickT)(int32_t i32Tick);
typedef osSysCallT (*osGetTickT)(uint32_t* pui32Tick);
typedef osSysCallT (*osGetTickExT)(uint64_t* pui64Tick);
typedef osSysCallT (*ostExecT)(void* pFunc, void* pArg);
typedef void *(*ostMallocT)(size_t size, uint32_t ui32Whence);
typedef void (*ostFreeT)(void* ptr, uint32_t ui32Whence);
typedef osSysCallT (*ostInquiryT)(osMessageT* pMsg, uint32_t ui32Timeout);
typedef osSysCallT (*osLeaveT)(osThreadIdT threadId, osMessageT message);
typedef osSysCallT (*ostCreateSemaphoreT)(int16_t i16Count, osSemaphoreIdT* pSemaphoreId);
typedef osSysCallT (*ostResetSemaphoreT)(osSemaphoreIdT* pSemaphoreId, int16_t i16Count);
typedef osSysCallT (*ostDeleteSemaphoreT)(osSemaphoreIdT* pSemaphoreId);
typedef osSysCallT (*ostWaitT)(osSemaphoreIdT semaphoreId, uint32_t ui32Timeout);
typedef osSysCallT (*osSignalT)(osSemaphoreIdT semaphoreId);
typedef osSysCallT (*osGetSemaphoreCountT)(osSemaphoreIdT semaphoreId, int16_t* pi16Count);
typedef osSysCallT (*ostCreateEventT)(osEventIdT* pEventId);
typedef osSysCallT (*ostResetEventT)(osEventIdT* pEventId);
typedef osSysCallT (*ostDeleteEventT)(osEventIdT* pEventId);
typedef osSysCallT (*ostExpectT)(osEventIdT eventId, uint8_t ui8Opcode, uint16_t ui16EventBits, uint32_t ui32Timeout);
typedef osSysCallT (*osSetT)(osEventIdT eventId, uint16_t ui16SetBits);
typedef osSysCallT (*ostClearT)(osEventIdT eventId, uint16_t ui16ClearBits);
typedef osSysCallT (*ostGetEventT)(uint16_t* pui16Event);
typedef osSysCallT (*osEnParcelT)(osQueueT* queParcel, osParcelIdT parcelId);
typedef osSysCallT (*osDeParcelT)(osQueueT* queParcel, osParcelIdT* pParcelId);
typedef osSysCallT (*ostCreateMailboxT)(osMailboxIdT* pMailboxId);
typedef osSysCallT (*ostResetMailboxT)(osMailboxIdT* pMailboxId, osParcelIdT* pParcelId);
typedef osSysCallT (*ostDeleteMailboxT)(osMailboxIdT* pMailboxId, osParcelIdT* pParcelId);
typedef osSysCallT (*osRetrieveT)(osMailboxIdT mailboxId, osParcelIdT* pParcelId);
typedef osSysCallT (*osDepositT)(osMailboxIdT mailboxId, osParcelIdT parcelId);
typedef osSysCallT (*osGetMailboxCountT)(osMailboxIdT mailboxId, int16_t* pi16Count);
typedef osSysCallT (*ostCreatePortT)(osPortIdT* pPortId);
typedef osSysCallT (*ostResetPortT)(osPortIdT* pPortId, osParcelIdT* pParcelId);
typedef osSysCallT (*ostDeletePortT)(osPortIdT* pPortId, osParcelIdT* pParcelId);
typedef osSysCallT (*ostReceiveT)(osPortIdT portId, uint32_t ui32Timeout, osParcelIdT* pParcelId);
typedef osSysCallT (*osSendT)(osPortIdT portId, osParcelIdT parcelId);
typedef osSysCallT (*osGetPortCountT)(osPortIdT portId, int16_t* pi16Count);
typedef osSysCallT (*ostCreateMutexT)(osMutexIdT* pMutexId);
typedef osSysCallT (*ostResetMutexT)(osMutexIdT* pMutexId);
typedef osSysCallT (*ostDeleteMutexT)(osMutexIdT* pMutexId);
typedef osSysCallT (*ostLockT)(osMutexIdT mutexId, uint32_t ui32Timeout);
typedef osSysCallT (*ostUnlockT)(osMutexIdT mutexId);
typedef osSysCallT (*ostCreateThreadT)(osThreadParamIdT threadParamId, osThreadIdT* pThreadId);
typedef osSysCallT (*osSuspendT)(osThreadIdT threadId);
typedef osSysCallT (*osResumeT)(osThreadIdT threadId, uint32_t ui32Delay);
typedef osSysCallT (*ostYieldT)(void);
typedef osSysCallT (*ostSleepT)(uint32_t ui32Delay);
typedef osSysCallT (*osUnsleepT)(osThreadIdT threadId);
typedef osSysCallT (*ostCreateTimerT)(osTimerParamIdT timerParamId, osTimerIdT* pTimerId);
typedef osSysCallT (*ostDeleteTimerT)(osTimerIdT* pTimerId);
typedef osSysCallT (*osStartT)(osTimerIdT timerId);
typedef osSysCallT (*osStopT)(osTimerIdT timerId);
typedef osSysCallT (*ostDevInitT)(int32_t i32Descrp);
typedef osSysCallT (*ostDevOpenT)(int32_t i32Descrp, char* pName, char* pMode);
typedef osSysCallT (*ostDevCloseT)(int32_t i32Descrp);
typedef osSysCallT (*ostDevReadT)(int32_t i32Descrp, void* pvoidBuff, uint32_t ui32Count);
typedef osSysCallT (*ostDevWriteT)(int32_t i32Descrp, const void* pvoidBuff, uint32_t ui32Count);
typedef osSysCallT (*ostDevGetcT)(int32_t i32Descrp);
typedef osSysCallT (*ostDevPutcT)(int32_t i32Descrp, char ch);
typedef osSysCallT (*ostDevSeekT)(int32_t i32Descrp, uint32_t ui32Offset, int iWhence);
typedef osSysCallT (*ostDevControlT)(int32_t i32Descrp, int32_t i32Func, int32_t i32Arg1, int32_t i32Arg2);
typedef osSysCallT (*ostDevExitT)(int32_t i32Descrp);
typedef osDevCallT (*ostDevIoNullT)(void);
typedef osDevCallT (*ostDevIoErrT)(void);
typedef uint16_t (*osGetUsedStackT)(void);
typedef char* (*ostGetThreadNameT)(osThreadIdT threadId);

#define OFFSET_APIS   (0x0121)
#define osGetVersion ((osGetVersionT)(OS_ROM_BASE+OFFSET_APIS+4*0))
#define osiDisableGirq ((osiDisableGirqT)(OS_ROM_BASE+OFFSET_APIS+4*1))
#define osiEnableGirq ((osiEnableGirqT)(OS_ROM_BASE+OFFSET_APIS+4*2))
#define osiEnterIrq ((osiEnterIrqT)(OS_ROM_BASE+OFFSET_APIS+4*3))
#define osiLeaveIrq ((osiLeaveIrqT)(OS_ROM_BASE+OFFSET_APIS+4*4))
#define osMaskIrq ((osMaskIrqT)(OS_ROM_BASE+OFFSET_APIS+4*5))
#define osUnmaskIrq ((osUnmaskIrqT)(OS_ROM_BASE+OFFSET_APIS+4*6))
#define osLockThread ((osLockThreadT)(OS_ROM_BASE+OFFSET_APIS+4*7))
#define osUnlockThread ((osUnlockThreadT)(OS_ROM_BASE+OFFSET_APIS+4*8))
#define osIncreaseTick ((osIncreaseTickT)(OS_ROM_BASE+OFFSET_APIS+4*9))
#define osGetTick ((osGetTickT)(OS_ROM_BASE+OFFSET_APIS+4*10))
#define osGetTickEx ((osGetTickExT)(OS_ROM_BASE+OFFSET_APIS+4*11))
#define ostExec ((ostExecT)(OS_ROM_BASE+OFFSET_APIS+4*12))
#define ostMalloc ((ostMallocT)(OS_ROM_BASE+OFFSET_APIS+4*13))
#define ostFree ((ostFreeT)(OS_ROM_BASE+OFFSET_APIS+4*14))
#define ostInquiry ((ostInquiryT)(OS_ROM_BASE+OFFSET_APIS+4*15))
#define osLeave ((osLeaveT)(OS_ROM_BASE+OFFSET_APIS+4*16))
#define ostCreateSemaphore ((ostCreateSemaphoreT)(OS_ROM_BASE+OFFSET_APIS+4*17))
#define ostResetSemaphore ((ostResetSemaphoreT)(OS_ROM_BASE+OFFSET_APIS+4*18))
#define ostDeleteSemaphore ((ostDeleteSemaphoreT)(OS_ROM_BASE+OFFSET_APIS+4*19))
#define ostWait ((ostWaitT)(OS_ROM_BASE+OFFSET_APIS+4*20))
#define osSignal ((osSignalT)(OS_ROM_BASE+OFFSET_APIS+4*21))
#define osGetSemaphoreCount ((osGetSemaphoreCountT)(OS_ROM_BASE+OFFSET_APIS+4*22))
#define ostCreateEvent ((ostCreateEventT)(OS_ROM_BASE+OFFSET_APIS+4*23))
#define ostResetEvent ((ostResetEventT)(OS_ROM_BASE+OFFSET_APIS+4*24))
#define ostDeleteEvent ((ostDeleteEventT)(OS_ROM_BASE+OFFSET_APIS+4*25))
#define ostExpect ((ostExpectT)(OS_ROM_BASE+OFFSET_APIS+4*26))
#define osSet ((osSetT)(OS_ROM_BASE+OFFSET_APIS+4*27))
#define ostClear ((ostClearT)(OS_ROM_BASE+OFFSET_APIS+4*28))
#define ostGetEvent ((ostGetEventT)(OS_ROM_BASE+OFFSET_APIS+4*29))
#define osEnParcel ((osEnParcelT)(OS_ROM_BASE+OFFSET_APIS+4*30))
#define osDeParcel ((osDeParcelT)(OS_ROM_BASE+OFFSET_APIS+4*31))
#define ostCreateMailbox ((ostCreateMailboxT)(OS_ROM_BASE+OFFSET_APIS+4*32))
#define ostResetMailbox ((ostResetMailboxT)(OS_ROM_BASE+OFFSET_APIS+4*33))
#define ostDeleteMailbox ((ostDeleteMailboxT)(OS_ROM_BASE+OFFSET_APIS+4*34))
#define osRetrieve ((osRetrieveT)(OS_ROM_BASE+OFFSET_APIS+4*35))
#define osDeposit ((osDepositT)(OS_ROM_BASE+OFFSET_APIS+4*36))
#define osGetMailboxCount ((osGetMailboxCountT)(OS_ROM_BASE+OFFSET_APIS+4*37))
#define ostCreatePort ((ostCreatePortT)(OS_ROM_BASE+OFFSET_APIS+4*38))
#define ostResetPort ((ostResetPortT)(OS_ROM_BASE+OFFSET_APIS+4*39))
#define ostDeletePort ((ostDeletePortT)(OS_ROM_BASE+OFFSET_APIS+4*40))
#define ostReceive ((ostReceiveT)(OS_ROM_BASE+OFFSET_APIS+4*41))
#define osSend ((osSendT)(OS_ROM_BASE+OFFSET_APIS+4*42))
#define osGetPortCount ((osGetPortCountT)(OS_ROM_BASE+OFFSET_APIS+4*43))
#define ostCreateMutex ((ostCreateMutexT)(OS_ROM_BASE+OFFSET_APIS+4*44))
#define ostResetMutex ((ostResetMutexT)(OS_ROM_BASE+OFFSET_APIS+4*45))
#define ostDeleteMutex ((ostDeleteMutexT)(OS_ROM_BASE+OFFSET_APIS+4*46))
#define ostLock ((ostLockT)(OS_ROM_BASE+OFFSET_APIS+4*47))
#define ostUnlock ((ostUnlockT)(OS_ROM_BASE+OFFSET_APIS+4*48))
#define ostCreateThread ((ostCreateThreadT)(OS_ROM_BASE+OFFSET_APIS+4*49))
#define osSuspend ((osSuspendT)(OS_ROM_BASE+OFFSET_APIS+4*50))
#define osResume ((osResumeT)(OS_ROM_BASE+OFFSET_APIS+4*51))
#define ostYield ((ostYieldT)(OS_ROM_BASE+OFFSET_APIS+4*52))
#define ostSleep ((ostSleepT)(OS_ROM_BASE+OFFSET_APIS+4*53))
#define osUnsleep ((osUnsleepT)(OS_ROM_BASE+OFFSET_APIS+4*54))
#define ostCreateTimer ((ostCreateTimerT)(OS_ROM_BASE+OFFSET_APIS+4*55))
#define ostDeleteTimer ((ostDeleteTimerT)(OS_ROM_BASE+OFFSET_APIS+4*56))
#define osStart ((osStartT)(OS_ROM_BASE+OFFSET_APIS+4*57))
#define osStop ((osStopT)(OS_ROM_BASE+OFFSET_APIS+4*58))
#define ostDevInit ((ostDevInitT)(OS_ROM_BASE+OFFSET_APIS+4*59))
#define ostDevOpen ((ostDevOpenT)(OS_ROM_BASE+OFFSET_APIS+4*60))
#define ostDevClose ((ostDevCloseT)(OS_ROM_BASE+OFFSET_APIS+4*61))
#define ostDevRead ((ostDevReadT)(OS_ROM_BASE+OFFSET_APIS+4*62))
#define ostDevWrite ((ostDevWriteT)(OS_ROM_BASE+OFFSET_APIS+4*63))
#define ostDevGetc ((ostDevGetcT)(OS_ROM_BASE+OFFSET_APIS+4*64))
#define ostDevPutc ((ostDevPutcT)(OS_ROM_BASE+OFFSET_APIS+4*65))
#define ostDevSeek ((ostDevSeekT)(OS_ROM_BASE+OFFSET_APIS+4*66))
#define ostDevControl ((ostDevControlT)(OS_ROM_BASE+OFFSET_APIS+4*67))
#define ostDevExit ((ostDevExitT)(OS_ROM_BASE+OFFSET_APIS+4*68))
#define ostDevIoNull ((ostDevIoNullT)(OS_ROM_BASE+OFFSET_APIS+4*69))
#define ostDevIoErr ((ostDevIoErrT)(OS_ROM_BASE+OFFSET_APIS+4*70))
#define osGetUsedStack ((osGetUsedStackT)(OS_ROM_BASE+OFFSET_APIS+4*71))
#define ostGetThreadName ((ostGetThreadNameT)(OS_ROM_BASE+OFFSET_APIS+4*72))

#endif /* _EZRTOS_H_ */
