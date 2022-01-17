const IOCACHEPAGEBUCKETS 16 // must be a power of two
const IOCACHEPAGESHIFT 4 // 1<<IOCACHEPAGESHIFT must equal IOCACHEPAGEBUCKETS
const IOCACHEPAGEMASK (IOCACHEPAGEBUCKETS 1 -)

struct IOCacheInfoBlock
	ExRwLock_SIZEOF RwLock

	4 PageReferences
	4 ModifiedPages
	4 Flags

	(IOCACHEPAGEBUCKETS KeMutex_SIZEOF *) PageBucketMutexes
	(IOCACHEPAGEBUCKETS 8 *) PageBucketListHeads
endstruct

const IOCACHEBLOCKFLAG_TRUNCATING 1

// should be kept in sync with MmPageFrameEntryEvictable
struct IOPageFrameEntryCache
	4 Next
	4 PFN
	4 Prev
	4 EvictionFlags
	4 EvictionFunction
	4 References
	4 WorkingSetIndexHint
	4 Context3
	4 ModifiedExtent
	4 ModifiedQuotaBlock
	4 ModifiedPTE
	4 FCB
	4 Flags
	4 OffsetInFile
	4 NextCachePage
	4 PrevCachePage
endstruct

const IOCACHEPAGEFLAG_VALID 1 // does the page contain valid data (does it need to be read in)?
const IOCACHEPAGEFLAG_DIRTY 2 // is the page dirty (does it need to be written out)?

extern IOModifiedPageWorker { context1 context2 -- }
extern IOFilesystemSyncWorker { context1 context2 -- }

extern IOCacheDumpInfo { cacheblock -- }

extern IOCacheInfoBlockCreate { -- cacheblock ok }

extern IOCacheInfoBlockLock { cacheblock -- ok }
extern IOCacheInfoBlockLockShared { cacheblock -- ok }
extern IOCacheInfoBlockTryLock { cacheblock -- ok }
extern IOCacheInfoBlockTryLockShared { cacheblock -- ok }
extern IOCacheInfoBlockUnlock { cacheblock -- }

extern IOCacheInfoBlockLockBucket { bucket cacheblock -- ok }
extern IOCacheInfoBlockTryLockBucket { bucket cacheblock -- locked }
extern IOCacheInfoBlockUnlockBucket { bucket cacheblock -- }

extern IOCacheInfoBlockReference { cacheblock -- oldcount }
extern IOCacheInfoBlockTryReference { cacheblock -- oldcount ok }
extern IOCacheInfoBlockDereference { cacheblock -- oldcount }

extern IOCacheInfoBlockDestroy { writeout cacheblock -- ok }
extern IOCacheInfoBlockFlush { cacheblock -- ok }
extern IOCacheInfoBlockTruncate { newsize writeout cacheblock -- ok }

extern IOCacheInfoBlockZeroEnd { pfdbe offset fcb -- }

extern IOCachePageRemove { pfdbe buckethead -- }
extern IOCachePageInsert { pfdbe buckethead -- }

extern IOCachePageRemoveModified { pfdbe -- }
extern IOCachePageInsertModified { pfdbe -- }

extern IOCachePageWriteModified { pfdbe -- ok }

extern IOCachePageGet { kflags locked offset fcb -- pageframe pfdbe ok }
extern IOCachePageRead { flags kflags offset fcb -- pageframe pfdbe ok }
extern IOCachePageModifyFunction { extent pfdbe -- ok }

extern IOCachePageModifiedCleanup { pfdbe -- extent }

extern IOCachePageModifyQuotaCharge { quotablock pfdbe -- charged }
extern IOCachePageModifyQuotaUncharge { pfdbe -- }

extern IOCacheFileWrite { flags length offset buffer fcb lastmode -- byteswritten ok }
extern IOCacheFileRead { flags length offset buffer fcb lastmode -- bytesread ok }

extern IOCacheInitialize { fcb -- cacheblock ok }

externptr IOCacheModifiedPageListHead
externptr IOCacheModifiedPageListTail

externptr IOCachePagesModifiedCount

externptr IOCachePagesUsed

externptr IOCachePagesModifiedMaximum

externptr IOModifiedPageEvent