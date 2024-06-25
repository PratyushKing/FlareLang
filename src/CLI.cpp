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

// CONTEXTS:
// 0 = flare help
// 1 = flare help build
// 2 = flare help run
// 3 = flare help test
// 4 = flare help shell
// 5 = flare help examples (more examples)
void print_help(int context, string argument_used) {
    std::cout << "\n  " + BLUE + BOLD + "FlareLang " + RESET + version + "\n";
    switch (context) {
        case 0:
            std::cout << "    Usage: " + GREEN + progName + RESET + " [commands]\n";
            std::cout << "\n  Commands:\n";
            std::cout << BOLD + "     build" + RESET + "  To build a specified project via the Build File or any standalone Flare program.\n";
            std::cout << BOLD + "     run  " + RESET + "  To run and/or build a specified project via the Build File or standalone Flare\n" +
                             "            program.\n";
            std::cout << BOLD + "     help " + RESET + "  To show this help page.\n";
            std::cout << BOLD + "     test " + RESET + "  To test with one of test cases if found in Build File\n";
            std::cout << BOLD + "     shell" + RESET + "  To enter flare shell mode (live interpreter)\n";

            std::cout << RESET + "\n  Examples:\n";
            std::cout << GREEN + "     " + progName + RESET + " build MyProject.fl\n";
            std::cout << GREEN + "     " + progName + RESET + " t testCase1 --file MyProject.fl\n";
            std::cout << GREEN + "     " + progName + RESET + YELLOW + " -r" + RESET + " MyStandaloneProgram.fl\n";

            std::cout << RESET + "\nYou can check the FlareLang wiki for further options and you can also do help for options such as " + BOLD + "`flare " + argument_used + " build`" + RESET + " for the build option.\n";
            return;
        case 1:
            std::cout << "    Usage: " + GREEN + progName + RESET + " build [file(s)] [build_params]\n";
            std::cout << "\n  Build Parameters:\n";
            std::cout << BOLD + "    --prefer-build-opts" + RESET + " To override build parameters with build options as much as possible.\n";
            std::cout << BOLD + "    --prefer-build-params" + RESET + " [DEFAULT] To override build options with build parameters as much as possible.\n";
            std::cout << BOLD + "    --";
            return;
        default:
            return;
    }
}

int parse_arg(string arg, string &build_file) {
    if (arg == "-h" || arg == "help" || arg == "--help" || arg == "h") {
        print_help(1, arg);
    } else if (arg == "-b" || arg == "build" || arg == "--build" || arg == "b") {
        write_flare_message(fatal, "still work in progress");
        return -1;
    } else if (arg == "-r" || arg == "run" || arg == "--run" || arg == "r") {
        write_flare_message(fatal, "still work in progress");
        return -1;
    } else if (arg == "-t" || arg == "test" || arg == "--test" || arg == "t") {
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