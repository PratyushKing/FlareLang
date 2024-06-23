#include <iostream>
#include "colors/Colors.hpp"

typedef enum {
    err,
    fatal,
    warn
} msg_type;

string msg_type_gen(msg_type type) {
    switch (type) {
        case err:
            return BOLD + RED + "error" + RESET + ": ";
        case fatal:
            return BOLD + RED + "fatal" + RESET + ": ";
        case warn:
            return UNDERLINE + YELLOW + "warn" + RESET + ": ";
        default:
            return "";
    }
}

void write_flare_message(msg_type type, string msg) {
    std::cout << BLUE << BOLD << "flare" << RESET << ": " << msg_type_gen(type) << msg << std::endl;
}

int main(int argc, char* argv[]) {
    write_flare_message(err, "build terminated");

    std::cout << RESET;
    return 0;
}