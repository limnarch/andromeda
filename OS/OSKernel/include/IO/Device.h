struct IODriver
	4 VersionMajor
	4 VersionMinor

	4 Name
	4 DeviceType
	4 DispatchTable
	4 ExtensionSize
	4 BlockSize
endstruct

struct IODevice
	4 Driver
	4 Extension
	4 FileControlBlock
	4 BlockSize
endstruct