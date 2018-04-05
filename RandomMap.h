#pragma once
#include <vector>
/*
	Tworzy losow� map� za pomoc� automatu kom�rkowego

	TODO: Zlikwidowa� ma�e, niedost�pne przestrzenie / 
	po��czy� je z najwi�kszym pomieszczeniem / 
	mo�e jakie� teleporty / 
	generowa� tak d�ugo, a� ich nie b�dzie
	TODO: Nie wiem jak to technologicznie wygl�da, ale mo�e lepiej zrobi� z tego klas� z metodami statycznymi /
	Co wtedy z dynamicznymi tablicami w konstruktorze?
*/
class RandomMap
{
private:
	// Parametry automatu kom�rkowego
	const int LIVE_LIMIT = 4;
	const int DEAD_LIMIT = 4;
	const int STEPS = 20;
	const float LIVE_CELL_CHANCE = 0.45;
	const int MAP_WIDTH;
	const int MAP_HEIGHT;

	// Wektory przechowuj�ce map� oraz tymczasow� map�, kt�ra potrzebna jest do tworzenia ostatecznej mapy.
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
	std::vector< std::vector<int> > getEnemies();
	void generateMap();
};

