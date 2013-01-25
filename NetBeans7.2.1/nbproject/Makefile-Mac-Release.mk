#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=MinGW_1-Windows
CND_DLIB_EXT=dll
CND_CONF=Mac-Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1472/render.o \
	${OBJECTDIR}/_ext/1472/Screen.o \
	${OBJECTDIR}/_ext/1472/Surface.o \
	${OBJECTDIR}/_ext/1472/game.o \
	${OBJECTDIR}/_ext/1472/MessageBox.o \
	${OBJECTDIR}/_ext/1472/ScreenElement.o \
	${OBJECTDIR}/_ext/1472/misc.o \
	${OBJECTDIR}/_ext/1472/Entity.o \
	${OBJECTDIR}/_ext/1472/Location.o \
	${OBJECTDIR}/_ext/1472/Debug.o \
	${OBJECTDIR}/_ext/1472/main.o \
	${OBJECTDIR}/_ext/1472/update.o \
	${OBJECTDIR}/_ext/1472/util.o \
	${OBJECTDIR}/_ext/1472/Sound.o \
	${OBJECTDIR}/_ext/1472/Point.o \
	${OBJECTDIR}/_ext/1472/GameState.o


# C Compiler Flags
CFLAGS=-m32 -ObjC -framework Cocoa

# CC Compiler Flags
CCFLAGS=-m32 -ObjC++ -framework Cocoa
CXXFLAGS=-m32 -ObjC++ -framework Cocoa

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans7.2.1.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans7.2.1.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -framework Cocoa -framework SDL -framework SDL_image -framework SDL_mixer -framework SDL_ttf -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans7.2.1 ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1472/render.o: ../render.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/render.o ../render.cpp

${OBJECTDIR}/_ext/1472/Screen.o: ../Screen.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/Screen.o ../Screen.cpp

${OBJECTDIR}/_ext/1472/Surface.o: ../Surface.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/Surface.o ../Surface.cpp

${OBJECTDIR}/_ext/1472/game.o: ../game.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/game.o ../game.cpp

${OBJECTDIR}/_ext/1472/MessageBox.o: ../MessageBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/MessageBox.o ../MessageBox.cpp

${OBJECTDIR}/_ext/1472/ScreenElement.o: ../ScreenElement.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/ScreenElement.o ../ScreenElement.cpp

${OBJECTDIR}/_ext/1472/misc.o: ../misc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/misc.o ../misc.cpp

${OBJECTDIR}/_ext/1472/Entity.o: ../Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/Entity.o ../Entity.cpp

${OBJECTDIR}/_ext/1472/Location.o: ../Location.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/Location.o ../Location.cpp

${OBJECTDIR}/_ext/1472/Debug.o: ../Debug.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/Debug.o ../Debug.cpp

${OBJECTDIR}/_ext/1472/main.o: ../main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/main.o ../main.cpp

${OBJECTDIR}/_ext/1472/update.o: ../update.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/update.o ../update.cpp

${OBJECTDIR}/_ext/1472/util.o: ../util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/util.o ../util.cpp

${OBJECTDIR}/_ext/1472/Sound.o: ../Sound.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/Sound.o ../Sound.cpp

${OBJECTDIR}/_ext/1472/Point.o: ../Point.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/Point.o ../Point.cpp

${OBJECTDIR}/_ext/1472/GameState.o: ../GameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1472
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DNDEBUG -DRELEASE -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1472/GameState.o ../GameState.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeans7.2.1.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
