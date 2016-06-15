#pragma once
#ifndef _MAP_H_
#define _MAP_H_

#include <utilities/PropertyManager.h>
#include <vector>

enum MapCompressionType
{
	GZip,
	ZLib,
	Uncompressed
};
enum MapStringEncoding
{
	Base64,
	NoEncoding
};

struct MapExit
{
	MapExit(const int x = 0, const int y = 0, const int z = 0, const std::string& newMap = "debug_map", const int new_x = 0, const int new_y = 0, const int new_z = 0) :
		x(x), y(y), z(z), newMap(newMap), newx(new_x), newy(new_y), newz(new_z), validExit(true), active(true)
	{
	}
	int x;
	int y;
	int z; //for 2-D maps, serves as map layer for player
	std::string newMap;
	int newx;
	int newy;
	int newz; //for 2-D maps serves as map layer for player
	bool validExit;
	bool active;
};

class Engine;

class Map : public PropertyManager
{
public:
	Map();
	virtual ~Map();
protected:
	//exits hashed by layer active on
	boost::unordered_map<int, std::vector<MapExit> > m_exits;
	unsigned int m_mapWidth;
	unsigned int m_mapHeight;
private:
	
};

#endif