/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_ProcessList
#define HEADER_ProcessList
/*
htop - ProcessList.c
(C) 2004,2005 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#ifndef CONFIG_H
#define CONFIG_H
#include "config.h"
#endif

#include "Process.h"
#include "TypedVector.h"
#include "UsersTable.h"
#include "Hashtable.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/utsname.h>
#include <stdarg.h>

#include "debug.h"
#include <assert.h>

#ifndef PROCDIR
#define PROCDIR "/proc"
#endif

#ifndef PROCSTATFILE
#define PROCSTATFILE "/proc/stat"
#endif

#ifndef PROCMEMINFOFILE
#define PROCMEMINFOFILE "/proc/meminfo"
#endif

#ifndef MAX_NAME
#define MAX_NAME 128
#endif

#ifndef MAX_READ
#define MAX_READ 8192
#endif



typedef struct ProcessList_ {
   TypedVector* processes;
   TypedVector* processes2;
   Hashtable* processTable;
   Process* prototype;
   UsersTable* usersTable;

   int processorCount;
   int totalTasks;
   int runningTasks;

   long int* totalTime;
   long int* userTime;
   long int* systemTime;
   long int* idleTime;
   long int* niceTime;
   long int* totalPeriod;
   long int* userPeriod;
   long int* systemPeriod;
   long int* idlePeriod;
   long int* nicePeriod;

   long int totalMem;
   long int usedMem;
   long int freeMem;
   long int sharedMem;
   long int buffersMem;
   long int cachedMem;
   long int totalSwap;
   long int usedSwap;
   long int freeSwap;

   ProcessField* fields;
   ProcessField sortKey;
   int direction;
   bool hideThreads;
   bool shadowOtherUsers;
   bool hideKernelThreads;
   bool hideUserlandThreads;
   bool treeView;
   bool highlightBaseName;
   bool highlightMegabytes;
   #ifdef DEBUG
   FILE* traceFile;
   #endif

} ProcessList;


#ifdef DEBUG


#define ProcessList_read(this, buffer, format, ...) ProcessList_xread(this, (vxscanf) vsscanf, buffer, format, ## __VA_ARGS__ )
#define ProcessList_fread(this, file, format, ...)  ProcessList_xread(this, (vxscanf) vfscanf, file, format, ## __VA_ARGS__ )



#else

#ifndef ProcessList_read
#define ProcessList_fopen(this, path, mode) fopen(path, mode)
#define ProcessList_read(this, buffer, format, ...) sscanf(buffer, format, ## __VA_ARGS__ )
#define ProcessList_fread(this, file, format, ...) fscanf(file, format, ## __VA_ARGS__ )
#endif

#endif

ProcessList* ProcessList_new(UsersTable* usersTable);

void ProcessList_delete(ProcessList* this);

void ProcessList_invertSortOrder(ProcessList* this);

RichString ProcessList_printHeader(ProcessList* this);


void ProcessList_prune(ProcessList* this);

void ProcessList_add(ProcessList* this, Process* p);

void ProcessList_remove(ProcessList* this, Process* p);

Process* ProcessList_get(ProcessList* this, int index);

int ProcessList_size(ProcessList* this);


void ProcessList_sort(ProcessList* this);


bool ProcessList_readStatusFile(ProcessList* this, Process* proc, char* dirname, char* name);

void ProcessList_processEntries(ProcessList* this, char* dirname, int parent, float period);

void ProcessList_scan(ProcessList* this);

void ProcessList_dontCrash(int signal);

#endif