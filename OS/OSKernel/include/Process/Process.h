struct PsProcess
	KeProcess_SIZEOF PCB

	4 GlobalListNext
	4 GlobalListPrev

	// memory management

	4 QuotaBlock

	// security

	4 OwningUser

	// object manager

	4 HandleTable

	// virtual memory information

	4 WorkingSetSize
	4 WorkingSetMaximum

	4 WorkingSetThrashMaximum

	4 PageFaultCount
endstruct

struct PsThread
	KeThread_SIZEOF TCB
endstruct

externptr PsProcessObjectType

externptr PsProcessTable

externptr PsProcessListHead

extern PsInitPhase0 { -- }

extern PsInitPhase1 { -- }

extern PsProcessCreate { permissions name -- processhandle ok }

extern PsProcessObjectDelete { object -- }