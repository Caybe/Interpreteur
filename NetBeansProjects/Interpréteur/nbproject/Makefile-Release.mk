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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/414263ba/ArbreAbstrait.o \
	${OBJECTDIR}/_ext/414263ba/Interpreteur.o \
	${OBJECTDIR}/_ext/414263ba/Lecteur.o \
	${OBJECTDIR}/_ext/414263ba/Symbole.o \
	${OBJECTDIR}/_ext/414263ba/SymboleValue.o \
	${OBJECTDIR}/_ext/414263ba/TableSymboles.o \
	${OBJECTDIR}/_ext/414263ba/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/interpr_teur

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/_ext/96b9438c/TestTantQue.o \
	${TESTDIR}/_ext/96b9438c/newtestrunner2.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/interpr_teur

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/interpr_teur: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/interpr_teur ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/414263ba/ArbreAbstrait.o: ../../M3105/tp5/ArbreAbstrait.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/ArbreAbstrait.o ../../M3105/tp5/ArbreAbstrait.cpp

${OBJECTDIR}/_ext/414263ba/Interpreteur.o: ../../M3105/tp5/Interpreteur.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/Interpreteur.o ../../M3105/tp5/Interpreteur.cpp

${OBJECTDIR}/_ext/414263ba/Lecteur.o: ../../M3105/tp5/Lecteur.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/Lecteur.o ../../M3105/tp5/Lecteur.cpp

${OBJECTDIR}/_ext/414263ba/Symbole.o: ../../M3105/tp5/Symbole.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/Symbole.o ../../M3105/tp5/Symbole.cpp

${OBJECTDIR}/_ext/414263ba/SymboleValue.o: ../../M3105/tp5/SymboleValue.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/SymboleValue.o ../../M3105/tp5/SymboleValue.cpp

${OBJECTDIR}/_ext/414263ba/TableSymboles.o: ../../M3105/tp5/TableSymboles.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/TableSymboles.o ../../M3105/tp5/TableSymboles.cpp

${OBJECTDIR}/_ext/414263ba/main.o: ../../M3105/tp5/main.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/main.o ../../M3105/tp5/main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/interpr_teur: ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/interpr_teur $^ ${LDLIBSOPTIONS}   


${OBJECTDIR}/_ext/414263ba/ArbreAbstrait_nomain.o: ${OBJECTDIR}/_ext/414263ba/ArbreAbstrait.o ../../M3105/tp5/ArbreAbstrait.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/414263ba/ArbreAbstrait.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/ArbreAbstrait_nomain.o ../../M3105/tp5/ArbreAbstrait.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/414263ba/ArbreAbstrait.o ${OBJECTDIR}/_ext/414263ba/ArbreAbstrait_nomain.o;\
	fi

${OBJECTDIR}/_ext/414263ba/Interpreteur_nomain.o: ${OBJECTDIR}/_ext/414263ba/Interpreteur.o ../../M3105/tp5/Interpreteur.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/414263ba/Interpreteur.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/Interpreteur_nomain.o ../../M3105/tp5/Interpreteur.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/414263ba/Interpreteur.o ${OBJECTDIR}/_ext/414263ba/Interpreteur_nomain.o;\
	fi

${OBJECTDIR}/_ext/414263ba/Lecteur_nomain.o: ${OBJECTDIR}/_ext/414263ba/Lecteur.o ../../M3105/tp5/Lecteur.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/414263ba/Lecteur.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/Lecteur_nomain.o ../../M3105/tp5/Lecteur.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/414263ba/Lecteur.o ${OBJECTDIR}/_ext/414263ba/Lecteur_nomain.o;\
	fi

${OBJECTDIR}/_ext/414263ba/Symbole_nomain.o: ${OBJECTDIR}/_ext/414263ba/Symbole.o ../../M3105/tp5/Symbole.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/414263ba/Symbole.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/Symbole_nomain.o ../../M3105/tp5/Symbole.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/414263ba/Symbole.o ${OBJECTDIR}/_ext/414263ba/Symbole_nomain.o;\
	fi

${OBJECTDIR}/_ext/414263ba/SymboleValue_nomain.o: ${OBJECTDIR}/_ext/414263ba/SymboleValue.o ../../M3105/tp5/SymboleValue.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/414263ba/SymboleValue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/SymboleValue_nomain.o ../../M3105/tp5/SymboleValue.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/414263ba/SymboleValue.o ${OBJECTDIR}/_ext/414263ba/SymboleValue_nomain.o;\
	fi

${OBJECTDIR}/_ext/414263ba/TableSymboles_nomain.o: ${OBJECTDIR}/_ext/414263ba/TableSymboles.o ../../M3105/tp5/TableSymboles.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/414263ba/TableSymboles.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/TableSymboles_nomain.o ../../M3105/tp5/TableSymboles.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/414263ba/TableSymboles.o ${OBJECTDIR}/_ext/414263ba/TableSymboles_nomain.o;\
	fi

${OBJECTDIR}/_ext/414263ba/main_nomain.o: ${OBJECTDIR}/_ext/414263ba/main.o ../../M3105/tp5/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/414263ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/414263ba/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/414263ba/main_nomain.o ../../M3105/tp5/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/414263ba/main.o ${OBJECTDIR}/_ext/414263ba/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/interpr_teur || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
