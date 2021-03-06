.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_base
INPUTLATEX= g09_prof_report.tex
INPUTAUX = g09_prof_report.aux
TARGETDVI = g09_prof_report.dvi
TARGETPS = g09_prof_report.ps
TARGETLATEX = g09_prof_report.pdf

# Project Paths
PROJECT_ROOT=$(HOME)/Desktop/lab7/g09_lab07/cs296_base_code
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -Wall -pg
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib -pg

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


.PHONY: all setup doc clean distclean

all: setup $(BINDIR)/$(TARGET)

debug_prof: setup opend $(BINDIR)/$(TARGET)
	@$(BINDIR)/$(TARGET) 15000
	@gprof $(BINDIR)/$(TARGET) gmon.out > ./profile/g09_debug_prof.dat

release_prof: setup openr filechanger $(BINDIR)/$(TARGET)
	@$(BINDIR)/$(TARGET) 15000
	@gprof $(BINDIR)/$(TARGET) gmon.out > ./profile/g09_release_prof.dat
	
	
opend:
	@ cd $(EXTERNAL_ROOT)/src/Box2D/build296;cmake -DCMAKE_BUILD_TYPE=Debug ../;make;make install
	

openr:
	@ cd $(EXTERNAL_ROOT)/src/Box2D/build296;cmake -DCMAKE_BUILD_TYPE=Release ../;make;make install

filechanger:
	@$(eval CPPFLAGS+= -O3)
	

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin
	@mkdir -p plots
	@mkdir -p profile
	@mkdir -p data
	@ cd $(EXTERNAL_ROOT)/src;tar -xf Box2D.tgz;mkdir -p ./Box2D/build296
	

$(BINDIR)/$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"
	
plot01: $(BINDIR)/$(TARGET)
	@chmod 755 ./scripts/*.sh
	@./scripts/gen_data.sh
	@./scripts/gen_csv.sh
	@./scripts/gen_data_csv2.sh
	@gnuplot> load './scripts/g09_plot01.p'
	@gnuplot> load './scripts/g09_plot02.p'
	@gnuplot> load './scripts/g09_plot03.p'
	@gnuplot> load './scripts/g09_plot04.p'
	@gnuplot> load './scripts/g09_plot05.p'
	@gnuplot> load './scripts/g09_plot06.p'
	@rm -rf load
	
	
plot02: $(BINDIR)/$(TARGET)
	@chmod 755 ./scripts/*.sh
	@./scripts/gen_data_csv.sh
	@./scripts/gen_data_csv2.sh
	@gnuplot> load './scripts/g09_plot01.p'
	@gnuplot> load './scripts/g09_plot02.p'
	@gnuplot> load './scripts/g09_plot03.p'
	@gnuplot> load './scripts/g09_plot04.p'
	@gnuplot> load './scripts/g09_plot05.p'
	@gnuplot> load './scripts/g09_plot06.p'
	@rm -rf load
	
clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~
	@rm -rf ./plots
	@rm -rf ./data
	@rm -rf ./src/*.o
	@rm -rf ./external/include/*
	@rm -rf ./external/lib/*
	@rm -rf ./external/src/Box2D
	@rm -rf ./gmon.out
	@rm -rf ./bin
	@rm -rf ./profile
	@rm -rf $(DOCDIR)/*.dvi *.ps *.aux *.bbl *.blg *.log *.pdf
	@$(ECHO) "Done"

distclean: clean
	@rm -rf ./plots
	@rm -rf ./data
	@$(RM) -rf $(BINDIR) $(DOCDIR)/html
	
report: $(DOCDIR)/$(INPUTLATEX)
	@latex $(DOCDIR)/$(INPUTLATEX)
	@dvips $(TARGETDVI)
	@ps2pdf $(TARGETPS) $(DOCDIR)/$(TARGETLATEX)
	@rm -rf *.dvi *.ps *.aux *.bbl *.blg *.log	
