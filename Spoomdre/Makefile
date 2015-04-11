GPP=g++
GPPOPT=-std=c++11

DEPENDENCIES= -lSDL2
OUTPUT=spoomdre

OFILES= hello_world.o



all: $(OUTPUT)


%.o: %.cpp
	$(GPP) $(GPPOPT) -c $< -o $@ $(DEPENDENCIES)


spoomdre: $(OFILES)
	$(GPP) $(GPPOPT)  $(OFILES) -o $(OUTPUT) $(DEPENDENCIES)



clean: 
	-$(RM) $(OUTPUT)
	
again: clean spoomdre