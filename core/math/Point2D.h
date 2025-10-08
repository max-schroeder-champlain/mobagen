#ifndef POINT2D_H
#define POINT2D_H
#include <string>
#include <cstdint>

struct Point2D {
public:
  Point2D(int x, int y) : x(x), y(y){};
  Point2D() = default;
  int x, y;
  bool operator==(const Point2D& rhs) const;
  bool operator!=(const Point2D& rhs) const;
  Point2D& operator=(const Point2D& rhs);
  Point2D operator+(const Point2D& rhs) const;
  Point2D& operator+=(const Point2D& rhs);
  Point2D operator-(const Point2D& rhs) const;
  Point2D& operator-=(const Point2D& rhs);

  inline Point2D Up() const { return *this + UP; };
  inline Point2D Left() const { return *this + LEFT; };
  inline Point2D Right() const { return *this + RIGHT; };
  inline Point2D Down() const { return *this + DOWN; };

  const static Point2D UP;
  const static Point2D DOWN;
  const static Point2D LEFT;
  const static Point2D RIGHT;
  const static Point2D INFINITE;
  std::string to_string();

  // for unordered set
  size_t operator()(const Point2D& p) const noexcept { return ((uint64_t)p.x) << 32 | (uint64_t)p.y; };

  uint64_t hash(Point2D const& p) const noexcept { return ((uint64_t)p.x) << 32 | (uint64_t)p.y; }
};

namespace std {
  template <> struct hash<Point2D> {
    std::size_t operator()(const Point2D& p) const noexcept { return p(p); }
  };
}  // namespace std

struct Point2DPrioritized {
  Point2D position;
  int priority;
  Point2DPrioritized(Point2D point, int priority): position(point), priority(priority){}
  bool operator<(const Point2DPrioritized& other) const {
    return priority > other.priority;
  }
  bool operator==(const Point2DPrioritized& other) const {
    return priority == other.priority;
  }
};

template<>
struct std::hash<Point2DPrioritized> {
  size_t operator()(const Point2DPrioritized &p) const {
    return  hash<int>()(p.position.x) ^ (hash<int>()(p.position.y) << 1);
  }
};

#endif  // POINT2D_H
