#ifndef GRAPHICS_INDEX_H
#define GRAPHICS_INDEX_H

#include <string>
#include <vector>

class GraphicsIndex
{

public:
  struct Index
  {
    int xs;
    int ys;
    int off;
  };

  static const constexpr unsigned int MAX_INDICES = 40000;

  GraphicsIndex( const std::string& pathToIndexFile );
  ~GraphicsIndex() = default;

  void load();

  Index getIndex( std::size_t n ) const;

private:
  std::vector< Index > indices_;
  std::string          pathToIndexFile_;
  bool                 isLoaded_;
};

#endif