##COMPILER
GPP=g++
GPPOPT=-std=c++11

##DEPENDENCIES
DEPENDENCIES= -lSDL2 -lSDL2_image
EIGENLOCAL=-I/usr/include/eigen3

##FILES FOR OUTPUT
SPOOMDRE_OUT=spoomdre

OFILES= mapmaker.o render_util.o game.o spoomdre_main.o player.o enemy.o sector.o gfx_util.o entity.o door.o normal_sector_factory.o 



all: $(SPOOMDRE_OUT)


%.o: %.cpp
	$(GPP) $(GPPOPT) $(EIGENLOCAL) -c $< -o $@ $(DEPENDENCIES)


spoomdre: $(OFILES)
	$(GPP) $(GPPOPT) $(OFILES) -o $(SPOOMDRE_OUT) $(DEPENDENCIES)

clean: 
	-$(RM) $(SPOOMDRE_OUT)
	-$(RM) $(OFILES)
	
again: clean spoomdre
