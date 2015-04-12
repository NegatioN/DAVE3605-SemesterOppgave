#include "game_util.hpp"

void GameUtil::fpsCounter(){
	int avgFps = countedFrames / (fpsTimer.getTicks() / 1000.f);
	if(avgFps > 2000000)
		avgFps = 0;

	++countedFrames;
}