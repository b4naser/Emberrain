#pragma once
#include <vector>
/*
	Tworzy losow¹ mapê za pomoc¹ automatu komórkowego

	TODO: Zlikwidowaæ ma³e, niedostêpne przestrzenie / 
	po³¹czyæ je z najwiêkszym pomieszczeniem / 
	mo¿e jakieœ teleporty / 
	generowaæ tak d³ugo, a¿ ich nie bêdzie
	TODO: Nie wiem jak to technologicznie wygl¹da, ale mo¿e lepiej zrobiæ z tego klasê z metodami statycznymi /
	Co wtedy z dynamicznymi tablicami w konstruktorze?
*/
class RandomMap
{
private:
	// Parameters used to create proper map
	const int LIVE_LIMIT = 4;
	const int DEAD_LIMIT = 4;
	const int STEPS = 20;
	const float LIVE_CELL_CHANCE = 0.45;
	const int MAP_WIDTH = 70;
	const int MAP_HEIGHT = 40;

	// Dynamic arrays contain map and temp map used to get state of each cell
	std::vector< std::vector<int> > map;
	std::vector< std::vector<int> > tempMap;


public:
	void randomizeMap();
	void addBorder();
	int getNeightboursCount(int type, int x, int y, bool countOutbounds);
	void doStep();
	void addFirstWallBorder();
	void addSecondWallBorder();
	void addThirdWallBorder();

	RandomMap();
	std::vector< std::vector<int> > getMapArray();
	void generateMap();
	void print_map();
	~RandomMap();
};

