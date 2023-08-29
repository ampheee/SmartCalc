# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rustam/SmartCalc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rustam/SmartCalc

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rustam/SmartCalc/CMakeFiles /home/rustam/SmartCalc//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rustam/SmartCalc/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named SmartCalc

# Build rule for target.
SmartCalc: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 SmartCalc
.PHONY : SmartCalc

# fast build rule for target.
SmartCalc/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/build
.PHONY : SmartCalc/fast

arithmetics.o: arithmetics.c.o
.PHONY : arithmetics.o

# target to build an object file
arithmetics.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/arithmetics.c.o
.PHONY : arithmetics.c.o

arithmetics.i: arithmetics.c.i
.PHONY : arithmetics.i

# target to preprocess a source file
arithmetics.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/arithmetics.c.i
.PHONY : arithmetics.c.i

arithmetics.s: arithmetics.c.s
.PHONY : arithmetics.s

# target to generate assembly for a file
arithmetics.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/arithmetics.c.s
.PHONY : arithmetics.c.s

bonus/credit/credit.o: bonus/credit/credit.c.o
.PHONY : bonus/credit/credit.o

# target to build an object file
bonus/credit/credit.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/bonus/credit/credit.c.o
.PHONY : bonus/credit/credit.c.o

bonus/credit/credit.i: bonus/credit/credit.c.i
.PHONY : bonus/credit/credit.i

# target to preprocess a source file
bonus/credit/credit.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/bonus/credit/credit.c.i
.PHONY : bonus/credit/credit.c.i

bonus/credit/credit.s: bonus/credit/credit.c.s
.PHONY : bonus/credit/credit.s

# target to generate assembly for a file
bonus/credit/credit.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/bonus/credit/credit.c.s
.PHONY : bonus/credit/credit.c.s

calculator.o: calculator.c.o
.PHONY : calculator.o

# target to build an object file
calculator.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/calculator.c.o
.PHONY : calculator.c.o

calculator.i: calculator.c.i
.PHONY : calculator.i

# target to preprocess a source file
calculator.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/calculator.c.i
.PHONY : calculator.c.i

calculator.s: calculator.c.s
.PHONY : calculator.s

# target to generate assembly for a file
calculator.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/calculator.c.s
.PHONY : calculator.c.s

callbacks.o: callbacks.c.o
.PHONY : callbacks.o

# target to build an object file
callbacks.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/callbacks.c.o
.PHONY : callbacks.c.o

callbacks.i: callbacks.c.i
.PHONY : callbacks.i

# target to preprocess a source file
callbacks.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/callbacks.c.i
.PHONY : callbacks.c.i

callbacks.s: callbacks.c.s
.PHONY : callbacks.s

# target to generate assembly for a file
callbacks.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/callbacks.c.s
.PHONY : callbacks.c.s

debug.o: debug.c.o
.PHONY : debug.o

# target to build an object file
debug.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/debug.c.o
.PHONY : debug.c.o

debug.i: debug.c.i
.PHONY : debug.i

# target to preprocess a source file
debug.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/debug.c.i
.PHONY : debug.c.i

debug.s: debug.c.s
.PHONY : debug.s

# target to generate assembly for a file
debug.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/debug.c.s
.PHONY : debug.c.s

interface.o: interface.c.o
.PHONY : interface.o

# target to build an object file
interface.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/interface.c.o
.PHONY : interface.c.o

interface.i: interface.c.i
.PHONY : interface.i

# target to preprocess a source file
interface.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/interface.c.i
.PHONY : interface.c.i

interface.s: interface.c.s
.PHONY : interface.s

# target to generate assembly for a file
interface.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/interface.c.s
.PHONY : interface.c.s

parse.o: parse.c.o
.PHONY : parse.o

# target to build an object file
parse.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/parse.c.o
.PHONY : parse.c.o

parse.i: parse.c.i
.PHONY : parse.i

# target to preprocess a source file
parse.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/parse.c.i
.PHONY : parse.c.i

parse.s: parse.c.s
.PHONY : parse.s

# target to generate assembly for a file
parse.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/parse.c.s
.PHONY : parse.c.s

queue.o: queue.c.o
.PHONY : queue.o

# target to build an object file
queue.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/queue.c.o
.PHONY : queue.c.o

queue.i: queue.c.i
.PHONY : queue.i

# target to preprocess a source file
queue.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/queue.c.i
.PHONY : queue.c.i

queue.s: queue.c.s
.PHONY : queue.s

# target to generate assembly for a file
queue.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/queue.c.s
.PHONY : queue.c.s

stack.o: stack.c.o
.PHONY : stack.o

# target to build an object file
stack.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/stack.c.o
.PHONY : stack.c.o

stack.i: stack.c.i
.PHONY : stack.i

# target to preprocess a source file
stack.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/stack.c.i
.PHONY : stack.c.i

stack.s: stack.c.s
.PHONY : stack.s

# target to generate assembly for a file
stack.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/SmartCalc.dir/build.make CMakeFiles/SmartCalc.dir/stack.c.s
.PHONY : stack.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... SmartCalc"
	@echo "... arithmetics.o"
	@echo "... arithmetics.i"
	@echo "... arithmetics.s"
	@echo "... bonus/credit/credit.o"
	@echo "... bonus/credit/credit.i"
	@echo "... bonus/credit/credit.s"
	@echo "... calculator.o"
	@echo "... calculator.i"
	@echo "... calculator.s"
	@echo "... callbacks.o"
	@echo "... callbacks.i"
	@echo "... callbacks.s"
	@echo "... debug.o"
	@echo "... debug.i"
	@echo "... debug.s"
	@echo "... interface.o"
	@echo "... interface.i"
	@echo "... interface.s"
	@echo "... parse.o"
	@echo "... parse.i"
	@echo "... parse.s"
	@echo "... queue.o"
	@echo "... queue.i"
	@echo "... queue.s"
	@echo "... stack.o"
	@echo "... stack.i"
	@echo "... stack.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

