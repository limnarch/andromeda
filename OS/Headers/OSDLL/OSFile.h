const OSFILETYPE_FILE        1
const OSFILETYPE_DIRECTORY   2
const OSFILETYPE_CHARDEVICE  3
const OSFILETYPE_BLOCKDEVICE 4

const OSFILEFLAG_NOCACHE     1
const OSFILEFLAG_CREATE      2
const OSFILEFLAG_MUSTBEFILE  4
const OSFILEFLAG_CREATEDIR   8
const OSFILEFLAG_MUSTCREATE  16
const OSFILEFLAG_EXCLUSIVE   32
const OSFILEFLAG_SWAPFILE    64

// set of flags that are reserved for system usage
const OSFILEFLAG_KERNELSET   OSFILEFLAG_SWAPFILE

// only block if theres nothing available, otherwise return whatever is there
const OSACCESSFLAG_RETURNANY   1

// avoid readahead in the IO layer
const OSACCESSFLAG_NOREADAHEAD 2

// return immediately. post IO completion message to port object
const OSACCESSFLAG_ASYNC       4

// set of flags that are reserved for system usage
const OSACCESSFLAG_KERNELSET   OSACCESSFLAG_ASYNC

const OSSEEK_SET 1
const OSSEEK_CUR 2
const OSSEEK_END 3

const OSMOUNT_READONLY 1
const OSMOUNT_NOUID    2

const OSDEFAULTFILEPERMISSIONS 438
const OSDEFAULTDIRPERMISSIONS  511

const OSFILEPATHMAX 256

struct OSDirectoryEntry
	256 Name
	32  Reserved
endstruct

struct OSFileInformation
	4 Size
	4 Type
	4 ATimeSecPart
	4 ATimeMsPart
	4 MTimeSecPart
	4 MTimeMsPart
	4 CTimeSecPart
	4 CTimeMsPart
	48 Reserved
endstruct

externptr OSStdIn
externptr OSStdOut
externptr OSStdErr

extern OSSetUMask { umask -- }
extern OSGetUMask { -- umask }

extern OSFileOpen { flags access path ftype -- handle ok }

extern OSDirectoryCreate { permissions flags access path -- handle ok }
extern OSFileCreate { permissions flags access path -- handle ok }