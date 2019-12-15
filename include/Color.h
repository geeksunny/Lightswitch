#ifndef LIGHTSWITCH_INCLUDE_COLOR_H_
#define LIGHTSWITCH_INCLUDE_COLOR_H_

#include <cstdint>
#include <memory>

namespace color {

// Color structs
struct Rgb {
  double red;
  double green;
  double blue;
};

struct Rgb24 {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

struct Rgb48 {
  uint16_t red;
  uint16_t green;
  uint16_t blue;
};

struct Hsv {
  double hue;
  double saturation;
  double value;
};

struct Hsv32 {
  uint16_t hue;
  uint8_t saturation;
  uint8_t value;
};

// Color factory
template<typename ColorFrom, typename ColorTo>
ColorTo convert_color(const ColorFrom &color_from);

template<>
Rgb convert_color<Rgb24, Rgb>(const Rgb24 &color_from);
template<>
Rgb convert_color<Rgb48, Rgb>(const Rgb48 &color_from);

template<>
Rgb24 convert_color<Hsv, Rgb24>(const Hsv &color_from);
template<>
Rgb24 convert_color<Hsv32, Rgb24>(const Hsv32 &color_from);
template<>
Rgb24 convert_color<Rgb48, Rgb24>(const Rgb48 &color_from);

template<>
Rgb48 convert_color<Rgb24, Rgb48>(const Rgb24 &color_from);

template<>
Hsv convert_color<Rgb24, Hsv>(const Rgb24 &color_from);
template<>
Hsv convert_color<Hsv32, Hsv>(const Hsv32 &color_from);

template<>
Hsv32 convert_color<Rgb24, Hsv32>(const Rgb24 &color_from);
template<>
Hsv32 convert_color<Hsv, Hsv32>(const Hsv &color_from);

// Color cycler
template<typename ColorType>
class ColorCycle {
 public:
  explicit ColorCycle(long color_duration, ColorType *colors_begin, ColorType *colors_end)
      : ColorCycle(color_duration, 0, colors_begin, colors_end) {}
  explicit ColorCycle(long color_duration, std::initializer_list<ColorType> colors)
      : ColorCycle(color_duration, 0, colors.begin(), colors.end()) {}
  explicit ColorCycle(long color_duration, long step_duration, std::initializer_list<ColorType> colors)
      : ColorCycle(color_duration, step_duration, colors.begin(), colors.end()) {}
  explicit ColorCycle(long color_duration, long step_duration, ColorType *colors_begin, ColorType *colors_end);

 private:
  std::unique_ptr<std::unique_ptr<ColorType[]>[]> cycles_;
  uint8_t color_count_;
  long color_duration_;
  long step_duration_;

  uint8_t step_index_ = 0;
  long next_action_ = 0;
};

}

#endif //LIGHTSWITCH_INCLUDE_COLOR_H_
