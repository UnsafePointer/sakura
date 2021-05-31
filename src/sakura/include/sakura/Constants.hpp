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

constexpr unsigned int
    BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS_PER_COLUMN = 32;
constexpr unsigned int BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS_PER_ROW =
    32;
constexpr unsigned int BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS =
    BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS_PER_COLUMN *
    BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS_PER_ROW;
constexpr unsigned int BACKGROUND_CHARACTER_DOTS_WIDTH = 8;
constexpr unsigned int BACKGROUND_CHARACTER_DOTS_HEIGHT = 8;
constexpr unsigned int BACKGROUND_CHARACTER_DOTS =
    BACKGROUND_CHARACTER_DOTS_WIDTH * BACKGROUND_CHARACTER_DOTS_HEIGHT;
constexpr unsigned int BACKGROUND_ATTRIBUTE_TABLE_DATA_LENGTH =
    BACKGROUND_ATTRIBUTE_TABLE_NUMBER_OF_CHARACTERS *
    BACKGROUND_CHARACTER_DOTS * 3;

#endif
