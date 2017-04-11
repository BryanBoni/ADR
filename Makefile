CXX      = g++

SOURCES = src/pioche.cpp src/jeu.cpp src/jeu_io.cpp src/joueur_simple.cpp
HEADERS = $(SOURCES:.cpp=.hpp)
OBJECTS = $(SOURCES:.cpp=.o)

CXXFLAGS  += -g -Wall -std=c++11 -pedantic
LDFLAGS += -g

all : test_pioche test_jeu arail_game

$(OBJECTS) : %.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $? -o $@

########## test_pioche ##########

PIOCHE_SOURCES = src/test_pioche.cpp
PIOCHE_OBJECTS = $(PIOCHE_SOURCES:.cpp=.o)

test_pioche : $(PIOCHE_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(PIOCHE_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(PIOCHE_OBJECTS): %.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $? -o $@

########## test_jeu ##########

JEU_SOURCES = src/test_jeu.cpp
JEU_OBJECTS = $(JEU_SOURCES:.cpp=.o)

test_jeu : $(JEU_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(JEU_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(JEU_OBJECTS): %.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $? -o $@

########## arail_game ##########

ARAIL_SOURCES = src/arail_game.cpp
ARAIL_OBJECTS = $(ARAIL_SOURCES:.cpp=.o)

arail_game : $(ARAIL_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(ARAIL_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(ARAIL_OBJECTS): %.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $? -o $@

########## cleanup ##########

clean:
	@rm -f test_pioche test_jeu arail_game $(OBJECTS) $(PIOCHE_OBJECTS) $(JEU_OBJECTS) $(ARAIL_OBJECTS)
