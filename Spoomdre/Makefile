GPP=g++
GPPOPT=-std=c++11

DEPENDENCIES= -lSDL2
SPOOMDRE_OUT=spoomdre
TEST_OUT=test

OFILES= game.o spoomdre_main.o
OTEST= hello_world.o



all: $(SPOOMDRE_OUT)


%.o: %.cpp
	$(GPP) $(GPPOPT) -c $< -o $@ $(DEPENDENCIES)


spoomdre: $(OFILES)
	$(GPP) $(GPPOPT)  $(OFILES) -o $(SPOOMDRE_OUT) $(DEPENDENCIES)

test: $(OTEST)
	$(GPP) $(GPPOPT)  $(OTEST) -o $(TEST_OUT) $(DEPENDENCIES)



clean: 
	-$(RM) $(SPOOMDRE_OUT) $(TEST_OUT)
	
again: clean spoomdre test