fnptr MmEvictionFunction { pfdbe -- }

// should be kept in sync with IOPageFrameEntryCache,
// and the page frame entries below
struct MmPageFrameEntryEvictable
	4 Next
	4 Prev
	1 EvictionFlagsB  1 EvictionTypeB  2 ReferencesI
	4 Context0
	4 Context1
	4 Context2
	4 Context3
	4 Context4
endstruct

struct MmPageFrameEntryAnonymous
	4 Next
	4 Prev
	1 EvictionFlagsB  1 EvictionTypeB  2 ReferencesI
	4 SwapPTE
	4 PrototypePTE
	4 Process        // for reclaiming DEMANDZERO private pages.
	4 VirtualAddress // for reclaiming DEMANDZERO private pages.
	4 Context3
endstruct

struct MmPageFrameEntryPageTable
	4 Next
	4 Prev
	1 EvictionFlagsB  1 EvictionTypeB  2 ReferencesI
	4 SwapPTE
	4 PrototypePTE
	4 PTECountTableEntry // overlaps Anonymous_Process but that's fine since these are both pointers and will therefore be unique with respect to eachother
	4 HoldCount          // overlaps Anonymous_VirtualAddress but that's fine since we won't ever check that for page tables
	4 PDEAddress
endstruct

struct MmPageFrameEntryWaitable
	4 EventBlock
	4 OwningThread
	1 EvictionFlagsB  1 EvictionTypeB  2 ReferencesI
	4 Context2
	4 Context3
	4 Context4
	4 Context5
	4 Context6
endstruct

const MMEVICTFLAG_MODIFIED   1
const MMEVICTFLAG_DELETED    2
const MMEVICTFLAG_PRIVATE    16
const MMEVICTFLAG_WORKINGSET 32 // indicates that a page is considered for
                                // working set accounting.
const MMEVICTFLAG_VALID      64 // file cache
const MMEVICTFLAG_IOINPROGRESS 128

const MMEVICTTYPE_FILE       0
const MMEVICTTYPE_ANON       1

extern MmEvictablePageGet { flags evictabletype priority -- pfdbe pfn ok }
extern MmEvictablePageDelete { pfdbe -- }
extern MmEvictablePageDereference { pfdbe -- oldcount }
extern MmEvictablePageReference { pfdbe -- oldcount }
extern MmEvictablePageRemove { pfdbe -- }
extern MmEvictablePageInsert { pfdbe -- }

extern MmEvictablePageModify { pfdbe process -- }

extern MmEvictSinglePage { -- pfdbe ok }

struct MmEvictablePageEvent
	KeEvent_SIZEOF Event
	4 References
	4 WasMemoryPrivileged
endstruct

extern MmEvictablePageWait { process pri pfdbe -- ok }
extern MmEvictablePageSatisfy { pfdbe -- }
extern MmEvictablePageStartIO { pfdbe -- }

externptr MmModifiedPageListHead
externptr MmModifiedPageListTail

externptr MmModifiedPageCount
externptr MmModifiedFilePageCount

externptr MmEvictablePageListHead
externptr MmEvictablePageListTail

externptr MmEvictablePageCount

externptr MmModifiedPageMaximum
externptr MmModifiedPageMinimum