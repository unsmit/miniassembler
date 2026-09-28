
CDIR = ./code  # Allows multiple versions of code in different subdirectories

# This Makefile assumes you are in a directory with the following sub-directories:
#    $(CDIR) ./code by default where all your code resides
#    ./pgms where all the example input programs are provided to you
#    ./correct_obj where the correct results provided to you reside


# Define which program should be used in the simple tests
TCASE=pgms/c2f.s

test : checkBuild
	./asm $(TCASE)
	
gdb : checkBuild
	gdb -ex 'set args $(TCASE)' ./asm
	
checkMem : checkBuild
	valgrind --leak-check=full ./asm $(TCASE)
	
checkBuild :  
	make --directory $(CDIR) ../asm 2>&1 | tee compileMsgs.txt	

# Get a list of all cases in all configurations for the full test
CASES := $(notdir $(wildcard pgms/*.s))
RESULTS := $(addprefix pgms/,$(CASES:.s=.o))

fullTest : checkBuild $(RESULTS)

# Implicit rules to make results and check those results if possible
pgms/%.o  :  ./asm pgms/%.s 
	./asm pgms/$*.s  
	@if [ -f correct_obj/$*.o ]; then \
		echo diff -iw correct_obj/$*.o pgms/$*.o; \
		diff correct_obj/$*.o $@; \
	fi

submit : 
	make --directory $(CDIR) clean # clean up the code directory first
	tar -cvzf proj1_code.tar.gz $(CDIR) # Tar up whatever is in the code directory
	
clean : 
	make --directory $(CDIR) clean
	-rm pgms/*.o compileMsgs.txt
