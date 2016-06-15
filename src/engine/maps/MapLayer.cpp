#include "MapLayer.h"
#include <log/Log.h>
#include <utilities/base64.h>
#include <sfml/graphics.hpp>
TileMapLayer::TileMapLayer()
{

}
TileMapLayer::TileMapLayer(const std::string& layerName, const unsigned int width, const unsigned int height, const unsigned int tileWidth, const unsigned int tileHeight, const std::string& decodedString) :
m_layerName(layerName), m_width(width), m_height(height), m_tileWidth(tileWidth), m_tileHeight(tileHeight), m_isAnimated(false), m_layerIndex(0), m_layerNumber(0), m_opacity(1.f), m_active(true)
{
	TileMapLayer::generateDataFromDecodedString(m_layerData, decodedString, width, height);
}
TileMapLayer::TileMapLayer(const std::string& layerName, const unsigned int width, const unsigned int height, const unsigned int tileWidth, const unsigned int tileHeight, const std::string& b64String, const bool decodedFromBase64) :
m_layerName(layerName), m_width(width), m_height(height), m_tileWidth(tileWidth), m_tileHeight(tileHeight), m_isAnimated(false), m_layerIndex(0), m_layerNumber(0), m_opacity(1.f), m_active(true)
{
	if (decodedFromBase64)
	{
		TileMapLayer::generateDataFromDecodedString(m_layerData, b64String, width, height);
	}
	else
	{
		TileMapLayer::generateDataFromBase64String(m_layerData, b64String, width, height);
	}
}
TileMapLayer::~TileMapLayer()
{

}

int TileMapLayer::getWidth() const
{
	return m_width;
}
int TileMapLayer::getHeight() const
{
	return m_height;
}
int TileMapLayer::getTileWidth() const
{
	return m_tileWidth;
}
int TileMapLayer::getTileHeight() const
{
	return m_tileHeight;
}

int TileMapLayer::getLayerNumber() const
{
	return m_layerNumber;
}
int TileMapLayer::getDrawOrder() const
{
	return m_drawOrder;
}

float TileMapLayer::getOpacity() const
{
	return m_opacity;
}

bool TileMapLayer::getIsAniamted() const
{
	return m_isAnimated;
}
bool TileMapLayer::isActive() const
{
	return m_active;
}

void TileMapLayer::setLayerNumber(const int layerNum)
{
	m_layerNumber = layerNum;
}
void TileMapLayer::setDrawOrder(const int drawOrder)
{
	m_drawOrder = drawOrder;
}
void TileMapLayer::setOpacity(const float opacity)
{
	m_opacity = opacity;
}

unsigned int TileMapLayer::at(const int index) const
{
	if (index >= m_layerData.size())
	{
		LOG_ERROR("Tried to acces map data outside of bounds. At index " << index << " | max allowed index " << m_layerData.size());
		return 0;
	}
	return m_layerData[index];
}
unsigned int TileMapLayer::at(const int x, const int y) const
{
	return at(y * m_width + x);
}

void TileMapLayer::generateDataFromDecodedString(std::vector<unsigned int>& data, const std::string& decodedString, const unsigned int width, const unsigned int height)
{
	unsigned int tiles = width * height;
	data.resize(tiles);
	int index = 0;
	for (unsigned int i = 0; i < tiles; ++i)
	{
		data[i] = static_cast<unsigned char>(decodedString[index]) |
				  static_cast<unsigned char>(decodedString[index + 1]) << 8 |
				  static_cast<unsigned char>(decodedString[index + 2]) << 16 |
				  static_cast<unsigned char>(decodedString[index + 3]) << 24;
		index += 4;
	}
}
void TileMapLayer::generateDataFromBase64String(std::vector<unsigned int>& data, const std::string& base64String, const unsigned int width, const unsigned int height)
{
	base64TMXDecode(data, base64String, width * height);
}