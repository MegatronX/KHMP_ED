#include <maps/TileMap.h>
#include <log/Log.h>
#include <input/files/xml/pugixml.hpp>
#include <boost/algorithm/string.hpp>
#include <Engine.h>

TileMap::TileMap()
{

}
TileMap::TileMap(const std::string &name, int tilesWide, int tilesHigh, int tilewidth, int tileheight)
{

}
TileMap::TileMap(const std::string &file, const std::string &name, Engine* engine)
{
	using namespace pugi;
	xml_document mapDoc;
	auto result = mapDoc.load_file(file.c_str());
	
	if (!result)
	{
		LOG_ERROR("Failed to open map file. Error: " << result.description() << std::endl);
	}
	else
	{
		for (xml_node map = mapDoc.child("map"); map; map = mapDoc.next_sibling("map"))
		{
			int width, height, tilewidth, tileheight;
			width = map.attribute("width").as_int();
			height = map.attribute("height").as_int();
			tilewidth = map.attribute("tilewidth").as_int();
			tileheight = map.attribute("tileheight").as_int();
			this->m_tileHeight = tileheight;
			this->m_tileWidth = tilewidth;
			this->m_mapWidth = width * tilewidth;
			this->m_mapHeight = height * tileheight;
			this->m_tilesInX = width;
			this->m_tilesInY = height;
			//TileMap tilemap(mapName, width, height, tilewidth, tileheight);
			xml_node properties = map.child("properties");
			//boost::unordered_map<std::string, AnimTileSetProperties> AnimTileSets;
			for (xml_node prop = properties.child("property"); prop; prop = prop.next_sibling("property"))
			{
				std::string name = prop.attribute("name").value();
				std::string value = prop.attribute("value").value();

				if (name == std::string("AnimateTileSet"))
				{
					/*std::vector<std::string> PropertyVals;
					boost::split(PropertyVals, value, boost::is_any_of("|"));
					//AnimTileSetProperties animproperties;
					for (auto pval = PropertyVals.begin(); pval != PropertyVals.end(); ++pval)
					{
						boost::trim(*pval);
						std::vector<std::string> valset;
						boost::split(valset, *pval, boost::is_any_of(":"));
						if (valset.size() > 1)
						{

							for (auto val = valset.begin(); val != valset.end(); ++val)
							{
								boost::trim(*val);
							}
							std::string pname = valset[0];
							std::string animval = valset[1];
							if (pname == "fps")
							{
								animproperties.fps = boost::lexical_cast<float>(animval);
							}
							else if (pname == "startingindex")
							{
								animproperties.startingIndex = boost::lexical_cast<int>(animval);
							}
							else
							{
								std::vector<std::string> cycleset;
								boost::split(cycleset, animval, boost::is_any_of(","));
								animproperties.tileset = pname;
								for (auto cset = cycleset.begin(); cset != cycleset.end(); ++cset)
								{
									boost::trim(*cset);
									animproperties.tilesetImages.push_back(*cset);
								}
							}
						}
					}*/
					//AnimTileSets[animproperties.tileset] = animproperties;
				}
				else
				{
				 this->addProperty(name, value);
				}
			}

			for (xml_node tileset = map.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
			{
				int firstGID, tstilewidth, tstileheight;
				std::string name = tileset.attribute("name").value();
				firstGID = tileset.attribute("firstgid").as_int();
				tstilewidth = tileset.attribute("tilewidth").as_int();
				tstileheight = tileset.attribute("tileheight").as_int();
				xml_node imageFile = tileset.child("image");
				std::string imageSource = imageFile.attribute("source").value();
				std::vector<std::string> frags;
				boost::split(frags, imageSource, boost::is_any_of("."));
				std::string fileName;
				std::string extension;
				for (auto piece = frags.begin(); piece != frags.end(); ++piece)
				{
					auto next = piece;
					next++;
					if (next == frags.end())
					{
						extension = "." + *piece;
					}
					else
					{
						fileName += *piece;
					}
				}
				tileset_ptr tileset;
				/*auto it = AnimTileSets.find(name);
				if (it != AnimTileSets.end())
				{
					std::vector<boost::shared_ptr<sf::Texture> > textures;
					for (auto tileimage = it->second.tilesetImages.begin(); tileimage != it->second.tilesetImages.end(); ++tileimage)
					{
						frags.clear();
						boost::split(frags, *tileimage, boost::is_any_of("."));
						std::string animFileName;
						std::string animExtension;
						for (auto piece = frags.begin(); piece != frags.end(); ++piece)
						{
							auto next = piece;
							next++;
							if (next == frags.end())
							{
								animExtension = "." + *piece;
							}
							else
							{
								animFileName += *piece;
							}
						}
						textures.push_back(engine->GetContentManager().RequestTexture(animFileName, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::TileSet, engine->GetTime(), animExtension.c_str()));
					}
					if (textures.size() > 0)
					{
						tileset = tileset_ptr(new AnimatedTileSet(name, firstGID, tstilewidth, tstileheight, textures, it->second.fps, it->second.startingIndex));
						AddTileSet(tileset);
					}
				}
				else*/
				{
					auto tileSetImage = engine->getContentManager().requestTexture(fileName, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::TileSet, engine->GetTime(), extension.c_str());
					tileset = tileset_ptr(new TileSet(name, firstGID, tstilewidth, tstileheight, tileSetImage));
					addTileSet(tileset);
				}
			}
			for (xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
			{
				/*std::string name;
				int lwidth, lheight;
				int drawOrder = 0;
				float opacity = 1;
				bool isCollision = false;
				CompType compression = CompType::NoCompression;
				StringEncoding encoding = StringEncoding::NoEncoding;
				std::vector<LayerProperty> layerPropertySet;
				boost::unordered_set<std::string> enforceOn;
				name = layer.attribute("name").value();
				lwidth = layer.attribute("width").as_int();
				lheight = layer.attribute("height").as_int();
				xml_node layerProperties = layer.child("properties");
				for (xml_node prop = layerProperties.child("property"); prop; prop = prop.next_sibling("property"))
				{
					std::string name, value;
					name = prop.attribute("name").value();
					value = prop.attribute("value").value();
					boost::to_lower(name);
					boost::to_lower(value);
					if ((name == "collision layer") && (value == "true"))
					{
						isCollision = true;
					}
					else if (name == "draw order")
					{
						drawOrder = atoi(value.c_str());
					}
					else if (name == "enforce on" && value.length() > 0)
					{
						std::vector<std::string> frags;
						boost::split(frags, value, boost::is_any_of(":;,"));
						for (unsigned int i = 0; i < frags.size(); ++i)
						{
							std::string target = frags[i];
							boost::trim(target);
							enforceOn.insert(target);
						}
					}
					else
					{
						LayerProperty prop(name, value);
						layerPropertySet.push_back(prop);
					}
				}
				xml_node data = layer.child("data");
				std::string encodingAttr = data.attribute("encoding").value();
				if (encodingAttr == "base64")
					encoding = StringEncoding::Base64;
				std::string compressAttr = data.attribute("compression").value();
				if (compressAttr == "gzip")
					compression = CompType::GZip;
				else if (compressAttr == "zlib")
					compression = CompType::Zlib;
				std::string dataString = data.child_value();
				boost::trim(dataString);
				auto test = Base64_DecodeInFours(dataString);
				if (false)
				{
				}
				else
				{
					if (encoding == StringEncoding::Base64)
						dataString = Base64_StringDecode(dataString);
					if (compression == CompType::GZip)
						dataString = GunzipString(dataString);
					else if (compression == CompType::Zlib)
						dataString = UnZlibString(dataString);
					if (isCollision)
					{
						col_layer_ptr colLayer = col_layer_ptr(new CollisionLayer(name, lwidth, lheight, tilewidth, tileheight,
							dataString, enforceOn));
						colLayer->SetExtendedProperties(layerPropertySet);
						colLayer->SetDrawOrder(drawOrder);
						AddCollisionLayer(colLayer);
					}
					else
					{
						layer_ptr layerptr = layer_ptr(new Layer(name, lwidth, lheight, tilewidth, tileheight, dataString));
						//Layer layer(name, lwidth, lheight, tilewidth, tileheight, dataString);
						layerptr->SetDrawOrder(drawOrder);
						layerptr->SetExtendedProperties(layerPropertySet);
						AddLayer(layerptr);

					}
				}*/

			}
		}
		/*SortLayers();
		int layerIndex = 0;
		int colLayerIndex = 0;
		for (auto layer = layers.begin(); layer != layers.end(); ++layer, ++layerIndex, colLayerIndex = 0)
		{
			for (auto col_layer = collisionLayers.begin(); col_layer != collisionLayers.end(); ++col_layer, ++colLayerIndex)
			{
				if ((*col_layer)->ActiveOnLayer((*layer)->GetName()))
				{
					(*col_layer)->AddAsActiveLayer(layerIndex);
				}
			}
		}*/
		//BuildExits();
	}


}
std::string TileMap::getName() const
{
	return "test";
}
unsigned int TileMap::getWidth() const
{
	return m_mapWidth;
}
unsigned int TileMap::getHeight() const
{
	return m_mapHeight;
}
unsigned int TileMap::getTilesInX() const
{
	return m_tilesInX;
}
unsigned int TileMap::getTilesInY() const
{
	return m_tilesInY;
}
unsigned int TileMap::getTileWidth() const
{
	return m_tileWidth;
}
unsigned int TileMap::getTileHeight() const
{
	return m_tileHeight;
}
unsigned int TileMap::getLayerCount() const
{
	return m_layers.size();
}
tile_layer_ptr TileMap::getLayer(int index) const
{
	return tile_layer_ptr();
}

void TileMap::addLayer(tile_layer_ptr layer, int insertAt, bool active)
{

}