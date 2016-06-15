#pragma once
#ifndef _MAPLAYER_H_
#define _MAPLAYER_H_
#include <vector>
#include <boost/shared_ptr.hpp>

#include <utilities/PropertyManager.h>

class TileMapLayer : public PropertyManager
{
public:
	TileMapLayer();
	TileMapLayer(const std::string& layerName, const unsigned int width, const unsigned int height, const unsigned int tileWidth, const unsigned int tileHeight, const std::string& decodedString);
	TileMapLayer(const std::string& layerName, const unsigned int width, const unsigned int height, const unsigned int tileWidth, const unsigned int tileHeight, const std::string& b64String, const bool decodedFromBase64);
	virtual ~TileMapLayer();

	int getWidth() const;
	int getHeight() const;
	int getTileWidth() const;
	int getTileHeight() const;

	int getLayerNumber() const;
	int getDrawOrder() const;

	float getOpacity() const;

	bool getIsAniamted() const;
	bool isActive() const;

	void setLayerNumber(const int layerNum);
	void setDrawOrder(const int drawOrder);
	void setOpacity(const float opacity = 1.f);

	unsigned int at(const int index) const;
	unsigned int at(const int x, const int y) const;

	static void generateDataFromDecodedString(std::vector<unsigned int>& data, const std::string& decodedString, const unsigned int width, const unsigned int height);
	static void generateDataFromBase64String(std::vector<unsigned int>& data, const std::string& base64String, const unsigned int width, const unsigned int height);
protected:


private:
	bool m_isAnimated;
	bool m_active;
	std::vector<unsigned int> m_layerData;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_tileWidth;
	unsigned int m_tileHeight;
	int m_layerIndex;
	int m_layerNumber;
	int m_drawOrder;
	float m_opacity;
	std::string m_layerName;
	std::vector<int> m_collisionLayerIndexes;

};

typedef boost::shared_ptr<TileMapLayer> tile_layer_ptr;

#endif