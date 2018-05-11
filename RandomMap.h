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
	// Parametry automatu komórkowego
	const int LIVE_LIMIT = 4;
	const int DEAD_LIMIT = 4;
	const int STEPS = 20;
	const float LIVE_CELL_CHANCE = 0.45;
	const int MAP_WIDTH;
	const int MAP_HEIGHT;

	// Wektory przechowuj¹ce mapê oraz tymczasow¹ mapê, która potrzebna jest do tworzenia ostatecznej mapy.
	std::vector< std::vector<int> > map;
	std::vector< std::vector<int> > tempMap;

	void randomizeMap();
	void addCellRect(int cell_type, int xx, int yy, int width, int height);
	int getNeightboursCount(int cellType, int x, int y, bool countOutbounds);
	void doStep();
	void addWallLayers();
public:
	RandomMap(int width, int height);
	std::vector< std::vector<int> > getMap();
	void generateMap();
};

