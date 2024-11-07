#ifndef COMMANDS_H
#define COMMANDS_H

#include "local.h"
#include "Shape.h"

namespace commands
{
  int convertToNumber(const std::string& str);
  void getFullArea(const std::vector<kuzn::Polygon>& polygons);
  void getMin(const std::vector<kuzn::Polygon>& data);
  void getMax(const std::vector<kuzn::Polygon>& data);
  void countFigures(const std::vector<kuzn::Polygon>& polygons);
  kuzn::FrameRectangle getFrameRectangle(const std::vector<kuzn::Polygon>& polygons);
  void checkStream();
  void lessarea(std::vector<kuzn::Polygon>& value);
  void intersections(const std::vector<kuzn::Polygon>& data);
}
#endif


