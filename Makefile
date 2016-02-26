CXX 		= g++
CXXFLAGS 	= -g -mtune=i686 -march=i686 -ffast-math -fomit-frame-pointer -O3 -DNDEBUG -Wall -fno-rtti -pipe -w
LDFLAGS 	= -lcv -lhighgui -lcvaux -lcxcore
TOP			= $(HOME)/Desktop/projectsura

SRC			= $(TOP)/src
OBJ			= $(TOP)/obj
BIN			= $(TOP)/bin
INCLUDE     = $(TOP)/include

all:createfile $(BIN)/main

createfile:
	@echo "#ifndef INCLUDE_H" > $(TOP)/include/include.h
	@echo "#define INCLUDE_H\n" >> $(TOP)/include/include.h
	@echo "#define DEBUG_MODE" >> $(TOP)/include/include.h
	@echo "#define PROJECT_PATH \"$(TOP)/\"" >> $(TOP)/include/include.h
	@echo "#define NO_OF_CAMERAS 4" >> $(TOP)/include/include.h
	@echo "#define NO_OF_ACTIVITIES 3" >> $(TOP)/include/include.h
	@echo "#define NO_OF_PERSONS 20" >> $(TOP)/include/include.h
	@echo "#define MAX_ROI 10\n" >> $(TOP)/include/include.h
	@echo "#include<cstdlib>" >> $(TOP)/include/include.h
	@echo "using namespace std;\n" >> $(TOP)/include/include.h
	@echo "#ifndef DEBUG_MODE" >> $(TOP)/include/include.h
	@echo "#define PRINT(x)" >> $(TOP)/include/include.h
	@echo "#define PRINTVAL(x)" >> $(TOP)/include/include.h
	@echo "#else" >> $(TOP)/include/include.h
	@echo "#define PRINT(x) cout << x << endl;" >> $(TOP)/include/include.h
	@echo "#define PRINTVAL(x) cout << #x << \": \" << x << endl;" >> $(TOP)/include/include.h
	@echo "#endif\n" >> $(TOP)/include/include.h
	@echo "#define ASSERT(x) if (!(x)) { cout << \"ERROR! Assert \" << #x << \" failed\" << \" on line \" << __LINE__  << \" in file \" << __FILE__ << endl; exit(1);}\n" >> $(TOP)/include/include.h
	@echo "#endif" >> $(TOP)/include/include.h

$(BIN)/main:$(OBJ)/activity.o $(OBJ)/detection.o $(OBJ)/dlist.o $(OBJ)/hierarchy.o $(OBJ)/init.o $(OBJ)/main.o $(OBJ)/person.o $(OBJ)/physicallayer.o $(OBJ)/recognition.o $(OBJ)/searchfunctions.o $(OBJ)/setHomography.o $(OBJ)/setROI.o $(OBJ)/state.o 
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(OBJ)/activity.o:$(SRC)/activity.cpp $(INCLUDE)/activity.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/detection.o:$(SRC)/detection.cpp $(INCLUDE)/detection.h $(INCLUDE)/recognition.h $(INCLUDE)/physicallayer.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/dlist.o:$(SRC)/dlist.cpp $(INCLUDE)/dlist.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/hierarchy.o:$(SRC)/hierarchy.cpp $(INCLUDE)/hierarchy.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/init.o: $(SRC)/init.cpp $(INCLUDE)/hierarchy.h $(INCLUDE)/init.h $(INCLUDE)/activity.h $(INCLUDE)/detection.h $(INCLUDE)/person.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/main.o:$(SRC)/main.cpp $(INCLUDE)/*.*
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/person.o: $(SRC)/person.cpp $(INCLUDE)/person.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/physicallayer.o:$(SRC)/physicallayer.cpp $(INCLUDE)/physicallayer.h $(INCLUDE)/searchfunctions.h $(INCLUDE)/dlist.h $(INCLUDE)/init.h $(INCLUDE)/person.h  $(INCLUDE)/hierarchy.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/recognition.o: $(SRC)/recognition.cpp $(INCLUDE)/recognition.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/searchfunctions.o:$(SRC)/searchfunctions.cpp $(INCLUDE)/searchfunctions.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/setHomography.o:$(SRC)/setHomography.cpp $(INCLUDE)/setHomography.h $(INCLUDE)/include.h	
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/setROI.o:$(SRC)/setROI.cpp $(INCLUDE)/setROI.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/state.o:$(SRC)/state.cpp $(INCLUDE)/state.h $(INCLUDE)/searchfunctions.h $(INCLUDE)/include.h
	@$(CXX) -c $(CXXFLAGS) $< -o $@

clean:	
	@rm -rf $(TOP)/logs/*
