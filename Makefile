COMPILER=g++
OUTPUT=bin/flare
OUTDIR=bin/

MAIN_FILE=src/CLI.cpp

all: cli

clean:
	@rm -rf bin/

cli: src/CLI.cpp
	@mkdir $(OUTDIR) -p
	@$(COMPILER) -o $(OUTPUT) $(MAIN_FILE)