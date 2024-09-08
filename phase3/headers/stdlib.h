#ifndef STD_LIB_H
#define STD_LIB_H

// general headers
#include "../../headers/const.h"
#include "../../headers/listx.h"
#include "../../headers/types.h"

// phase 1 headers
#include "../../phase1/headers/msg.h"
#include "../../phase1/headers/pcb.h"

// phase 2 headers
#include "../../phase2/headers/nucleus.h"

// uriscv headers
#include <uriscv/aout.h>
#include <uriscv/arch.h>
#include <uriscv/bios.h>
#include <uriscv/const.h>
#include <uriscv/cpu.h>
#include <uriscv/csr.h> //ucode.h <--- da errore 'impossibile aprire il codice errore "uriscv/ucode.h" del file origine',
#include <uriscv/liburiscv.h>
#include <uriscv/regdef.h>
#include <uriscv/types.h>

/* external global variables */
extern pcb_PTR swap_mutex;
extern swap_t swap_pool[POOLSIZE];
// static support array (NOTE: the support[i] is shared by SST[i] & uProcess[i])
extern support_t support_arr[MAXSSTNUM];
extern void pager(void);
extern void supportExceptionHandler(void);
// external phase2 global variables & functions
extern pcb_PTR ssi_pcb;

#define OFFINTERRUPTS() setSTATUS(getSTATUS() & (~MSTATUS_MIE_MASK))
#define ONINTERRUPTS() setSTATUS(getSTATUS() | MSTATUS_MIE_MASK)

// init and fill the support page table with the correct values
void initUprocPageTable(pteEntry_t *tbl, int asid);
// initialization of a single user process
pcb_PTR initUProc(state_t *u_proc_state,support_t *sst_support);
/*function to get support struct (requested to SSI)*/
support_t *getSupportData(void);
/*function to request creation of a child (to SSI)*/
pcb_t *createChild(state_t *state, support_t *support);
// gain mutual exclusion over the swap pool
void gainSwapMutex(void);
// release mutual exclusion over the swap pool
void releaseSwapMutex(void);
// check if is a SST pid
int isOneOfSSTPids(int pid);
// terminate a process
void terminateProcess(pcb_PTR process_to_terminate);
// send notification (void message) to the process
void notify(pcb_PTR process_to_notify);
// init default support struct
void defaultSupportData(support_t *support_data, int asid);
// assign the current stack top and decrement it
memaddr getCurrentFreeStackTop(void);
// set the current stack top to the first free stack page
void initFreeStackTop(void);
// invalidate the page table of the current process, tbl and swap pool
void invalidateUProcPageTable(support_t *support);
// insert page into TLB, if not present
void updateTLB(pteEntry_t *page);

#endif // !STD_LIB_H
