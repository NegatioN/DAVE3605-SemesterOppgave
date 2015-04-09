GPP=g++
GPPOPT=-std=c++11

DEPENDENCIES=-lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
OUTPUT=spoomdre

OFILES= nothing.o



all: $(OUTPUT)


%.o: %.cpp
	$(GPP) $(GPPOPT) -c $< -o $@ $(DEPENDENCIES)


spoomdre: $(FIREWORKSO)
	$(GPP) $(GPPOPT)  $(OFILES) -o $(OUTPUT) $(DEPENDENCIES)



clean: 
	-$(RM) $(OUTPUT)
	
again: clean spoomdre