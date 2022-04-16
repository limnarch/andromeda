const MMHIGHESTUSERADDRESS  0x7FFEFFFF
// 64kb no-mans-land
const MMLOWESTSYSTEMADDRESS 0x80000000

struct MmPageFrameEntry
	4 R1
	4 PFN
	4 R3
	4 R4
	4 R5
	4 R6
	4 R7
	4 R8
	4 R9
	4 R10
	4 R11
	4 R12
	4 R13
	4 R14
	4 R15
	4 R16
endstruct

struct MmPageFrameEntryFree
	4 Next
	4 PFN
	4 R3
	4 R4
	4 R5
	4 R6
	4 R7
	4 R8
	4 R9
	4 R10
	4 R11
	4 R12
	4 R13
	4 R14
	4 R15
	4 R16
endstruct

struct MmPageFrameEntryPool
	4 Next
	4 PFN
	4 Prev
	4 ByteSize
	4 Tag
	4 VirtualAddress
	4 Context4
	4 Context5
	4 Context6
	4 Context7
	4 Context8
	4 Context9
	4 Context10
	4 BucketIndex
	4 PoolListNext
	4 PoolListPrev
endstruct

extern MmUsageDump { -- }

extern MmInitPhase0 { -- }
extern MmInitPhase1 { -- }

extern MmQuery { query -- ok }

extern MmResourceJettison { -- }

extern MmPoolInit { -- }

extern MmPageAlloc { priority -- pfdbe pfn ok }
extern MmPageFree { pfn -- }
extern MmHeapCheck { -- }
extern MmHeapDumpBuckets { -- }
extern MmHeapDumpBlockInfo { block -- }
extern MmAllocWithTag { bytes tag flags -- ptr ok }
extern MmFree { ptr -- }
extern MmChargeBytesGet { bytes -- charge }
extern MmBlockChargeGet { block -- charge }

extern MmKernelStackAlloc { -- kstack ok }
extern MmKernelStackFree { kstack -- }
extern MmKernelStackSwapOut { thread -- }
extern MmKernelStackSwapIn { thread -- }

extern MmPageDirectoryAlloc { -- pdir ok }
extern MmPageDirectoryFree { pdir -- }

extern MmModifiedPageWriter { context1 context2 -- }
extern MmBalanceSetManager { -- }
extern MmZeroPageWorker { -- }

extern MmPageFault { writing badaddr trapframe -- handled }

externptr MmPageFrameDatabase
externptr MmPageFreeListHead
externptr MmPageZeroListHead
externptr MmPageFreeCount
// externptr MmHeapBuckets
// externptr MmHeapSize
// externptr MmHeapBytesFree
// externptr MmHeap
externptr MmInited
externptr MmEventPageAvailable
externptr MmEventLowMemory
externptr MmModifiedPageEvent
externptr MmPageFreeCountLow
externptr MmPageFreeCountSufficient
externptr MmSectionObjectType

externptr MmPageFaultCount
externptr MmTotalWorkingSetSize
externptr MmPeakWorkingSetSize

externptr MmCommitLimit
externptr MmCommitUsage

externptr MmPoolLimit

externptr MmPageTotal

// arbitrary margin to avoid overcommiting

const MMCOMMITLIMITMARGIN (128 1024 *)

// pool allocation thresholds at which various types of pool allocation
// will fail when the global limit is reached.

const MMPOOL_NORMALTHRESH        (16 1024 *)
const MMPOOL_MUSTSUCCEEDL2THRESH (8 1024 *)
const MMPOOL_MUSTSUCCEEDTHRESH   0

// free page count thresholds at which various types/priorities of page
// allocation will block or fail.

const MMNORMALTHRESH        15 // normal allocations
const MMPOOLTHRESH          8  // nonblockable pool allocations
const MMMUSTSUCCEEDL2THRESH 4  // mustsucceed level 2
const MMMUSTSUCCEEDTHRESH   0  // mustsucceed

// free page count threshold that counts as "dire", meaning the working set
// trimmer will ignore working set lower limits and go woo wild.

const MMDIREPAGES           (MMNORMALTHRESH 1 -)

// default working set heuristics

const MMWORKINGSETDEFAULTMINIMUM 16
const MMWORKINGSETDEFAULTMAXIMUM 64

// page allocation priorities

const ZEROMUST    1
const FREEFIRST   2

const MUSTSUCCEED   0x8000
const CANBLOCK      0x10000
const CACHEALLOC    0x20000
const MUSTSUCCEEDL2 0x40000
const TRYFOREVER    0x80000
const POOLALLOC     0x100000