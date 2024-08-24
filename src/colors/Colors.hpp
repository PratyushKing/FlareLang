#ifndef COLORS_HPP

#include <iostream>
using namespace std;

    // Text Colors
    std::string RESET = "\033[0m";
    std::string BLACK = "\033[30m";
    std::string RED = "\033[31m";
    std::string GREEN = "\033[32m";
    std::string YELLOW = "\033[33m";
    std::string BLUE = "\033[34m";
    std::string MAGENTA = "\033[35m";
    std::string CYAN = "\033[36m";
    std::string WHITE = "\033[37m";

    // Bright Text Colors
    std::string BRIGHT_BLACK = "\033[90m";
    std::string BRIGHT_RED = "\033[91m";
    std::string BRIGHT_GREEN = "\033[92m";
    std::string BRIGHT_YELLOW = "\033[93m";
    std::string BRIGHT_BLUE = "\033[94m";
    std::string BRIGHT_MAGENTA = "\033[95m";
    std::string BRIGHT_CYAN = "\033[96m";
    std::string BRIGHT_WHITE = "\033[97m";

    // Background Colors
    std::string BG_BLACK = "\033[40m";
    std::string BG_RED = "\033[41m";
    std::string BG_GREEN = "\033[42m";
    std::string BG_YELLOW = "\033[43m";
    std::string BG_BLUE = "\033[44m";
    std::string BG_MAGENTA = "\033[45m";
    std::string BG_CYAN = "\033[46m";
    std::string BG_WHITE = "\033[47m";

    // Bright Background Colors
    std::string BG_BRIGHT_BLACK = "\033[100m";
    std::string BG_BRIGHT_RED = "\033[101m";
    std::string BG_BRIGHT_GREEN = "\033[102m";
    std::string BG_BRIGHT_YELLOW = "\033[103m";
    std::string BG_BRIGHT_BLUE = "\033[104m";
    std::string BG_BRIGHT_MAGENTA = "\033[105m";
    std::string BG_BRIGHT_CYAN = "\033[106m";
    std::string BG_BRIGHT_WHITE = "\033[107m";

    // Text Styles
    std::string BOLD = "\033[1m";
    std::string UNDERLINE = "\033[4m";
    std::string ITALIC = "\033[3m";
    std::string STRIKETHROUGH = "\033[9m";

#endif