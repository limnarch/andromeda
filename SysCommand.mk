COMPONENTS := .

OUTPUTFILE := $(SYSROOT)/$(CMDNAME).exe

DYLIBS += OSDLL.dll:$(OSDLLBIN)

EXECFILEMODE := 492

INCDIR := ./

include $(REPO)/Project.mk