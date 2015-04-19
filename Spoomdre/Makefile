##COMPILER
GPP=g++
GPPOPT=-std=c++11

##DEPENDENCIES
DEPENDENCIES= -lSDL2
EIGENLOCAL=-I/usr/include/eigen3

##FILES FOR OUTPUT
SPOOMDRE_OUT=spoomdre
TEST_OUT=test

OFILES= game.o spoomdre_main.o keyboard_handler.o player.o sector.o gfx_util.o entity.o
OTEST= hello_world.o keyboard_handler.o



all: $(SPOOMDRE_OUT) $(TEST_OUT)


%.o: %.cpp
	$(GPP) $(GPPOPT) $(EIGENLOCAL) -c $< -o $@ $(DEPENDENCIES)


spoomdre: $(OFILES)
	$(GPP) $(GPPOPT) $(OFILES) -o $(SPOOMDRE_OUT) $(DEPENDENCIES)

test: $(OTEST)
	$(GPP) $(GPPOPT)  $(OTEST) -o $(TEST_OUT) $(DEPENDENCIES)



clean: 
	-$(RM) $(SPOOMDRE_OUT)
	-$(RM) $(TEST_OUT)
	-$(RM) $(OFILES)
	-$(RM) $(OTEST)
	
again: clean spoomdre test

check: again clean
