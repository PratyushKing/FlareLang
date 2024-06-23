#include <iostream>
#include <sys/stat.h>
#include <string.h>
#include "colors/Colors.hpp"

static string progName = "flare";
const string version = "v0.1";

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
    std::cout << BLUE << BOLD << progName << RESET << ": " << msg_type_gen(type) << msg << std::endl;
}

bool file_exists(string name) {
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0);
}

bool has_ending(string fullString, string ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void print_help() {
    std::cout << "\n  " + BLUE + BOLD + "FlareLang " + RESET + version + "\n";
    std::cout << "    Usage: " + GREEN + progName + RESET + " [commands]" + "\n";
    std::cout << "\n  Commands:\n";
    std::cout << BOLD + "     build" + RESET + "  To build a specified project via the Build File or any standalone Flare program.\n";
    std::cout << BOLD + "     run  " + RESET + "  To run and/or build a specified project via the Build File or standalone Flare program.\n";
    std::cout << BOLD + "     help " + RESET + "  To show this help page.\n";
    std::cout << BOLD + "     test " + RESET + "  To test with one of test cases if found in Build File\n";
    std::cout << BOLD + "     shell" + RESET + "  To enter flare shell mode (live interpreter)\n";
    
}

int parse_arg(string arg, string &build_file) {
    if (arg == "-h" || arg == "help" || arg == "--help" || arg == "h") {
        print_help();
    } else if (arg == "-b" || arg == "build" || arg == "--build" || arg == "b") {
        write_flare_message(fatal, "still work in progress");
        return -1;
    } else {
        if (file_exists(arg)) {
            if (!has_ending(arg, ".fl")) {
                write_flare_message(err, "file has invalid extension (expected: *.fl)");
                return -1;
            }
            build_file += arg;
        } else {
            write_flare_message(fatal, "invalid arguments found");
            return -1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    progName = argv[0];
    if (argc <= 1) {
        write_flare_message(err, "build terminated");
        return -1;
    }
    
    string buildFile = "";
    for (int i = 1; i < argc; i++) {
        if (argv[i] == nullptr) {
            return -1;
        }
        if (parse_arg(argv[i], buildFile) != 0) {
            return -1;
        }
    }
    // std::cout << "Build File: " << buildFile;

    std::cout << RESET;
    return 0;
}