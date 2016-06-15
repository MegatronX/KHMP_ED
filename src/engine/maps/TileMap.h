#include <maps/Map.h>
#include <maps/MapLayer.h>
#include <sfml\Graphics.hpp>
#include <sfml\System.hpp>
#include <maps/TileSet.h>
class Engine;

namespace Cache
{
	enum GameStyle;
	enum World;
	enum ResourceClass;
}


class TileMap : public Map
{
public:
	enum MapStringEncoding
	{
		Base64,
		NoEncoding
	};
	enum MapCompType
	{
		GZip,
		Zlib,
		NoCompression
	};

	TileMap();
	TileMap(const std::string &name, int tilesWide, int tilesHigh, int tilewidth, int tileheight);
	TileMap(const std::string &file, const std::string &name, Engine* engine);
	std::string getName() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned int getTilesInX() const;
	unsigned int getTilesInY() const;
	unsigned int getTileWidth() const;
	unsigned int getTileHeight() const;
	unsigned int getLayerCount() const;
	tile_layer_ptr getLayer(int index) const;

	void addLayer(tile_layer_ptr layer, int insertAt = -1, bool active = true);
	//void addAnimatedLayer(anim_layer_ptr layer, int insertAt = -1, bool active = true);
	//void addCollisionLayer(col_layer_ptr layer, int insertAt = -1, bool active = true);

	//void addTileSet(tileset_ptr set);
	//void addAnimatedTileSet(anim_tile_ptr set);

	bool walkable(int x, int y, int layer = -9000);
	bool walkable(sf::Vector2<int> &xy, int layer = -9000);
	bool validTile(int x, int y);
protected:
private:
	std::vector<tile_layer_ptr> m_layers;

	unsigned int m_tileWidth;
	unsigned int m_tileHeight;
	unsigned int m_tilesInX;
	unsigned int m_tilesInY;
};