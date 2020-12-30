#include "Level_map.h"
#include "ResourcePath.hpp"
#include <iostream>

int Object::GetPropertyInt(const std::string &getName) {
  return atoi(properties[getName].c_str());
}

float Object::GetPropertyFloat(const std::string &getName) {
  return strtod(properties[getName].c_str(), nullptr);
}

std::string Object::GetPropertyString(const std::string &getName) {
  return properties[getName];
}

bool Level::LoadFromFile(const std::string &filename) {
  TiXmlDocument levelFile(filename.c_str());
  // Загружаем XML-карту
  if (!levelFile.LoadFile()) {
    std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
    return false;
  }

  // Работаем с контейнером map
  TiXmlElement *map;
  map = levelFile.FirstChildElement("map");

  // Пример карты: <map version="1.0" orientation="orthogonal"
  // width="10" height="10" tilewidth="34" tileheight="34">
  width = atoi(map->Attribute("width"));
  height = atoi(map->Attribute("height"));
  tileWidth = atoi(map->Attribute("tilewidth"));
  tileHeight = atoi(map->Attribute("tileheight"));

  // Берем описание тайлсета и идентификатор первого тайла
  TiXmlElement *tilesetElement;
  tilesetElement = map->FirstChildElement("tileset");
  firstTileID = atoi(tilesetElement->Attribute("firstgid"));

  // source - путь до картинки в контейнере image
  TiXmlElement *image;
  image = tilesetElement->FirstChildElement("image");
  std::string imagepath = resourcePath() + image->Attribute("source");

  // Пытаемся загрузить тайлсет
  sf::Image img;

  if (!img.loadFromFile(imagepath)) {
    std::cout << "Failed to load tile sheet." << std::endl;
    return false;
  }

  img.createMaskFromColor(sf::Color(255, 255, 255));
  tilesetImage.loadFromImage(img);
  tilesetImage.setSmooth(false);

  // Получаем количество столбцов и строк тайлсета
  int columns = tilesetImage.getSize().x / tileWidth;
  int rows = tilesetImage.getSize().y / tileHeight;

  // Вектор из прямоугольников изображений (TextureRect)
  std::vector<sf::Rect<int> > subRects;

  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < columns; x++) {
      sf::Rect<int> rect;
      rect.top = y * tileHeight;
      rect.height = tileHeight;
      rect.left = x * tileWidth;
      rect.width = tileWidth;
      subRects.push_back(rect);
    }
  }
  // Работа со слоями
  TiXmlElement *layerElement;
  layerElement = map->FirstChildElement("layer");
  while (layerElement) {
    Layer layer;
    // Если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
    if (layerElement->Attribute("opacity") != nullptr) {
      float opacity = strtod(layerElement->Attribute("opacity"), nullptr);
      layer.opacity = 255 * opacity;
    } else {
      layer.opacity = 255;
    }
    // Контейнер <data>
    TiXmlElement *layerDataElement;
    layerDataElement = layerElement->FirstChildElement("data");

    if (layerDataElement == nullptr) {
      std::cout << "Bad map. No layer information found." << std::endl;
    }

    // Контейнер <tile> - описание тайлов каждого слоя
    TiXmlElement *tileElement;
    tileElement = layerDataElement->FirstChildElement("tile");

    if (tileElement == nullptr) {
      std::cout << "Bad map. No tile information found." << std::endl;
      return false;
    }

    int x = 0;
    int y = 0;

    while (tileElement) {
      int tileGID = atoi(tileElement->Attribute("gid"));
      int subRectToUse = tileGID - firstTileID;

      // Устанавливаем TextureRect каждого тайла
      if (subRectToUse >= 0) {
        sf::Sprite sprite;
        sprite.setTexture(tilesetImage);
        sprite.setTextureRect(subRects[subRectToUse]);
        sprite.setPosition(x * tileWidth, y * tileHeight);
        sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

        layer.tiles.push_back(sprite);
      }

      tileElement = tileElement->NextSiblingElement("tile");

      x++;
      if (x >= width) {
        x = 0;
        y++;
        if (y >= height) {
          y = 0;
        }
      }
    }

    layers.push_back(layer);

    layerElement = layerElement->NextSiblingElement("layer");
  }

  // Работа с объектами
  TiXmlElement *objectGroupElement;

  // Если есть слои объектов
  if (map->FirstChildElement("objectgroup") != nullptr) {
    objectGroupElement = map->FirstChildElement("objectgroup");
    while (objectGroupElement) {
      // Контейнер <object>
      TiXmlElement *objectElement;
      objectElement = objectGroupElement->FirstChildElement("object");

      while (objectElement) {
        // Получаем все данные - тип, имя, позиция, etc
        std::string objectType;
        if (objectElement->Attribute("type") != nullptr) {
          objectType = objectElement->Attribute("type");
        }
        std::string objectName;
        if (objectElement->Attribute("name") != nullptr) {
          objectName = objectElement->Attribute("name");
        }
        int x = atoi(objectElement->Attribute("x"));
        int y = atoi(objectElement->Attribute("y"));

        int width, height;

        sf::Sprite sprite;
        sprite.setTexture(tilesetImage);
        sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
        sprite.setPosition(x, y);

        if (objectElement->Attribute("width") != nullptr) {
          width = atoi(objectElement->Attribute("width"));
          height = atoi(objectElement->Attribute("height"));
        } else {
          width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
          height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
          sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
        }

        // Экземпляр объекта
        Object object;
        object.name = objectName;
        object.type = objectType;
        object.sprite = sprite;

        sf::Rect<float> objectRect;
        objectRect.top = y;
        objectRect.left = x;
        objectRect.height = height;
        objectRect.width = width;
        object.rect = objectRect;

        // "Переменные" объекта
        TiXmlElement *properties;
        properties = objectElement->FirstChildElement("properties");
        if (properties != nullptr) {
          TiXmlElement *prop;
          prop = properties->FirstChildElement("property");
          if (prop != nullptr) {
            while (prop) {
              std::string propertyName = prop->Attribute("name");
              std::string propertyValue = prop->Attribute("value");

              object.properties[propertyName] = propertyValue;

              prop = prop->NextSiblingElement("property");
            }
          }
        }

        objects.push_back(object);
        objectElement = objectElement->NextSiblingElement("object");
      }
      objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
    }
  } else {
    std::cout << "No object layers found..." << std::endl;
  }
  return true;
}

bool Containt(std::string name) {
  return (name == "player");
}

Object Level::GetObject(const std::string &name) {
  // Только первый объект с заданным именем
  for (auto &object : objects) {
    if (object.name == name) {
      return object;
    }
  }
}

std::vector<Object> Level::GetObjects(const std::string &name) {
  // Все объекты с заданным именем
  std::vector<Object> vec;
  for (auto &object : objects) {
    if (object.name == name) {
      vec.push_back(object);
    }
  }
  return vec;
}

std::vector<Object> Level::GetAllObjects() {
  return objects;
}

sf::Vector2i Level::GetTileSize() const {
  return {tileWidth, tileHeight};
}

void Level::Draw(sf::RenderWindow &window, unsigned int height, unsigned int width, float x, float y) {
  auto currentRect = sf::FloatRect(x - width / 2 - 64, y - height / 2 - 64, width + 128, height + 128);

  // Рисуем все тайлы (объекты НЕ рисуем!)
  for (auto &layer : layers) {
    for (const auto &tile : layer.tiles) {
      if (currentRect.contains(tile.getPosition().x, tile.getPosition().y)) {
        window.draw(tile);
      }
    }
  }
}
