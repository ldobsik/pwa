###############################
# Unit testing build with UTE #
###############################
# Lubomir Dobsik, 2013 #
########################

# list the modules that should be cross-compiled for unit testing
PROJ_SRC = pwa.c

# location of the original project source code
ORIG_SRCDIR  = ../src
ORIG_INCDIR  = ../inc

TEST_SRCDIR  = test
TEST_INCDIR  = headers-x86

UTEST_FRAMEWORK_DIR = ../../ute

RUNNER_SRCDIR= gen

BIN_DIR = bin
TEST_BIN = test.exe
PROJ_LIB = test

################################################
# you shouldn't need to modify the lines below #
################################################
UTEST_SRCDIR  = $(wildcard $(UTEST_FRAMEWORK_DIR)/src)
UTEST_SCRIPTS_SRCDIR = $(wildcard $(UTEST_FRAMEWORK_DIR)/scripts)

MACRO_DEFINITION_FILE := $(TEST_INCDIR)/defines.h

TEST_INC =  -I$(RUNNER_SRCDIR) -I$(TEST_INCDIR) -I$(TEST_SRCDIR) -I$(UTEST_SRCDIR) -I$(ORIG_INCDIR) -I$(ORIG_SRCDIR)

TEST_SRC   := $(wildcard $(TEST_SRCDIR)/*.c)
TEST_FILES := $(wildcard $(TEST_SRCDIR)/*Test.c)
TEST_DESCR := $(RUNNER_SRCDIR)/ute_test_descr.txt
TEST_IDS   := $(RUNNER_SRCDIR)/ute_test_id.h
RUNNER_SRC := $(RUNNER_SRCDIR)/ute_run_all.c
UTEST_SRC  := $(wildcard $(UTEST_SRCDIR)/*.c)  

VPATH      := $(UTEST_SRCDIR):$(RUNNER_SRCDIR):$(TEST_SRCDIR):$(ORIG_SRCDIR)

PROJ_OBJ   := $(patsubst %.c,$(BIN_DIR)/%.o,$(PROJ_SRC))
TEST_OBJ   := $(patsubst $(TEST_SRCDIR)/%.c,$(BIN_DIR)/%.o,$(TEST_SRC))
RUNNER_OBJ := $(patsubst $(RUNNER_SRCDIR)/%.c,$(BIN_DIR)/%.o,$(RUNNER_SRC))
UTEST_OBJ  := $(patsubst $(UTEST_SRCDIR)/%.c,$(BIN_DIR)/%.o,$(UTEST_SRC))

UTEST_ARGS = 
CFLAGS = -g -std=c99 -Wall -DUTE_PRINT_RESULT_ON=1
CC = gcc 
LD = gcc 

all: clean test

# execute
test: $(BIN_DIR)/$(TEST_BIN)
	@$(BIN_DIR)/$(TEST_BIN) $(UTEST_ARGS)

# link test executable
$(BIN_DIR)/$(TEST_BIN): $(BIN_DIR)/lib$(PROJ_LIB).a $(TEST_IDS) $(TEST_DESCR) $(RUNNER_SRC) $(RUNNER_OBJ) $(TEST_OBJ) $(UTEST_OBJ)
	@echo Test files compiled
	@$(LD) $(UTEST_OBJ) $(TEST_OBJ) $(RUNNER_OBJ) -o $(BIN_DIR)/$(TEST_BIN) -L$(BIN_DIR) -l$(PROJ_LIB)

# make the project and the tests
$(BIN_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c -MMD $(TEST_INC) -include $(MACRO_DEFINITION_FILE) -o $@ $<
	@cp $(BIN_DIR)/$*.d $(BIN_DIR)/$*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' \
	    < $(BIN_DIR)/$*.d >> $(BIN_DIR)/$*.P; \
	rm -f $(BIN_DIR)/$*.d
-include $(PROJ_SRC:%.c=$(BIN_DIR)/%.P)
-include $(BIN_DIR)/AllTest.P
-include $(TEST_SRC:$(TEST_SRCDIR)/%.c=$(BIN_DIR)/%.P)

# make project library
$(BIN_DIR)/lib$(PROJ_LIB).a:$(PROJ_OBJ)
	@echo Project files compiled
	@ar rcs $(BIN_DIR)/lib$(PROJ_LIB).a $(PROJ_OBJ)

# build runner sources
$(RUNNER_SRC): $(TEST_FILES)
	@$(UTEST_SCRIPTS_SRCDIR)/make_alltest.sh $(TEST_FILES) > $@  

$(TEST_IDS): $(TEST_FILES) 
	@$(UTEST_SCRIPTS_SRCDIR)/make_ids.sh $(TEST_FILES) > $@  

$(TEST_DESCR): $(TEST_FILES) 
	@$(UTEST_SCRIPTS_SRCDIR)/make_descr.sh $(TEST_FILES) > $@  

# clean
clean:
	@rm -f $(RUNNER_SRCDIR)/*
	@rm -f $(BIN_DIR)/*
	@echo "Clean!"
	
