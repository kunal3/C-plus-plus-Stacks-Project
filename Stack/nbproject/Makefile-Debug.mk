#
# Gererated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/Cygwin-Windows

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Stacks.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Debug/Cygwin-Windows/stack.exe

dist/Debug/Cygwin-Windows/stack.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/Cygwin-Windows
	${LINK.cc} -o dist/Debug/Cygwin-Windows/stack ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Stacks.o: Stacks.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/Stacks.o Stacks.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/Cygwin-Windows/stack.exe

# Subprojects
.clean-subprojects:
