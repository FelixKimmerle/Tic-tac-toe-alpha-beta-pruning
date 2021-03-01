PROJECT_FILE := ./Tic-tac-toe.cbp

.PHONY: clean release debug run rund all remake

all: release debug
remake: clean all

release: 
	codeblocks --target="Release" --build $(PROJECT_FILE)

debug: 
	codeblocks --target="Debug" --build $(PROJECT_FILE)

clean: 
	codeblocks --target="Release" --clean $(PROJECT_FILE)
	codeblocks --target="Debug" --clean $(PROJECT_FILE)

rund: 
	./bin/Debug/Tic-tac-toe

run: 
	./bin/Release/Tic-tac-toe