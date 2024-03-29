#ifndef SAKURA_CONSTANTS_HPP
#define SAKURA_CONSTANTS_HPP

constexpr unsigned int COLOR_TABLE_RAM_NUMBER_OF_COLORS_PER_AREA = 16;
constexpr unsigned int COLOR_TABLE_RAM_NUMBER_OF_AREAS = 16;
constexpr unsigned int COLOR_TABLE_RAM_NUMBER_OF_SECTIONS = 2;
constexpr unsigned int COLOR_TABLE_RAM_NUMBER_OF_COLORS_PER_SECTION =
    COLOR_TABLE_RAM_NUMBER_OF_COLORS_PER_AREA * COLOR_TABLE_RAM_NUMBER_OF_AREAS;
constexpr unsigned int COLOR_TABLE_RAM_NUMBER_OF_COLORS =
    COLOR_TABLE_RAM_NUMBER_OF_COLORS_PER_SECTION *
    COLOR_TABLE_RAM_NUMBER_OF_SECTIONS;
constexpr unsigned int COLOR_TABLE_RAM_DATA_LENGTH =
    COLOR_TABLE_RAM_NUMBER_OF_COLORS * 3;

constexpr unsigned int CHARACTER_DOTS_WIDTH = 8;
constexpr unsigned int CHARACTER_DOTS_HEIGHT = 8;
constexpr unsigned int CHARACTER_DOTS =
    CHARACTER_DOTS_WIDTH * CHARACTER_DOTS_HEIGHT;
constexpr unsigned int CHARACTER_DATA_LENGTH = CHARACTER_DOTS * 3;

constexpr unsigned int BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_ROWS = 32;
constexpr unsigned int BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS_PER_ROW =
    32;
constexpr unsigned int BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS =
    BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_ROWS *
    BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS_PER_ROW;
constexpr unsigned int BACKGROUND_ATTRIBUTE_TABLE_DATA_LENGTH =
    BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS * CHARACTER_DATA_LENGTH;

constexpr unsigned int BACKGROUND_CHARACTER_GENERATOR_WORDS_LENGTH = 16;

constexpr unsigned int CHARACTER_GENERATOR_NUMBER_OF_ROWS = 128;
constexpr unsigned int CHARACTER_GENERATOR_NUMBER_OF_CHARACTERS_PER_ROW = 16;
constexpr unsigned int CHARACTER_GENERATOR_NUMBER_OF_CHARACTERS =
    CHARACTER_GENERATOR_NUMBER_OF_ROWS *
    CHARACTER_GENERATOR_NUMBER_OF_CHARACTERS_PER_ROW;
constexpr unsigned int CHARACTER_GENERATOR_DATA_LENGTH =
    CHARACTER_GENERATOR_NUMBER_OF_CHARACTERS * CHARACTER_DATA_LENGTH;

#endif
