#include <iostream>
#include <sys/stat.h>
#include <string.h>
#include "colors/Colors.hpp"
#include "lang/tokenizer.cpp"

static string progName = "flare";
const string msgUpArr = "↑";
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
            std::cout << BOLD + "    --prefer-build-opts    " + RESET + " To override build parameters with build options as much as possible.\n";
            std::cout << BOLD + "    --prefer-build-params  " + RESET + " [DEFAULT] To override build options with build parameters as much as\n" +
                                "                            possible.\n";
            std::cout << BOLD + "    --build-output-type    " + RESET + " Set output type to interpreted/compiled/transpiled. [DEFAULT=\n" +
                                       "                            interpreted, if not specified in the project files]\n";
            std::cout << RED + BOLD + "    --[disable]-EFFOT      " + RESET + " EFFOT means Enforce File Function Out Types, it is very\n" +
                                       "                            unsafe if disabled, if it is, it disables file output checks\n" +
                                       "                            (such as files that are meant to be compiled being ran on interpreter\n" +
                                       "                            output type) [DEFAULT=Enabled]\n";
            std::cout << BOLD + "    --[disable]-fast-build " + RESET + " Fast Build will do a few optimizations to get a fast build\n";
            std::cout << BOLD + "    --project-output-type  " + RESET + " To select a project out type. [Options: Program/Library]\n";
            std::cout << BOLD + "    --[disable]-unsafe     " + RESET + " If enabled, will not perform null or type checks.\n";
            std::cout << BOLD + "    --[disable]-stdlibs    " + RESET + " If disabled, will remove included stdlibs such as 'io', 'sys', \n" + 
                                "                            'term', etc. Recommended for low-level use only. [DEFAULT=Enabled]\n";
            std::cout << RESET + "\nPlease do note, all build flags will just add on top of your build file's options unless modified, it's better to use in-file buildOpts than using these flags.\n";
            return;
        default:
            return;
    }
}

int get_context_by_string(string context_arg) {
    if (context_arg == "-b" || context_arg == "build" || context_arg == "--build" || context_arg == "b") {
        return 1;
    } else if (context_arg == "") {
        return 0;
    }
    return -1;
}

void write_compiler_err(string err, int ln, string file, string lnContents, int errStartCh, int errEndCh, string prevLine, string suggestion) {
    std::cout << "(" + BOLD << RED << "ERROR" << RESET << "): " << BOLD << file << RESET << ": at line " << ln << ", char " << errStartCh << "\n";
    std::cout << BRIGHT_BLACK << "  " << ln - 1 << " | " << prevLine << RESET << "\n  " << ln << " | " << BOLD;
    if (errStartCh != 1) {
        errStartCh++;
    }
    for (int i = 0; i < strlen(lnContents.c_str()); i++) {
        if (i >= errStartCh - 1 && i <= errEndCh - 1) {
            std::cout << RED << BOLD << ITALIC << STRIKETHROUGH;
        } else if (i >= errEndCh - 1) {
            std::cout << RESET << BOLD;
        }
        std::cout << lnContents[i];
    }
    std::cout << RESET << "\n     | " << RED;
    for (int i = 0; i <= errStartCh - 1; i++) {
        std::cout << " ";
    }
    std::cout << msgUpArr << " " << BOLD << err << RESET;
    if (suggestion != "") {
        std::cout << ITALIC << YELLOW << " did you mean: " << BOLD << suggestion << RESET << YELLOW << ITALIC << "?" << RESET;
    }
    std::cout << "\n\n";
}

int parse_arg(string arg, string next_arg, string &build_file) {
    if (arg == "-h" || arg == "help" || arg == "--help" || arg == "h") {
        print_help(get_context_by_string(next_arg), arg);
        return 256; // quit right after
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
        write_flare_message(fatal, "invalid arguments found");
        return -1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    list<token> newTokenList;
    tokenizeCode(newTokenList, "int test = 10;");
    return 0;
    
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
        string next_arg = "";
        if (argc > i+1) {
            next_arg = argv[i+1];
        }
        int ret_code = parse_arg(argv[i], next_arg, buildFile);
        if (ret_code != 0) {
            if (ret_code == 256) { // to quit without error code
                return 0;
            }
            return ret_code;
        }
        if (argv[i] == "--help" || argv[i] == "-h" || argv[i] == "help" || argv[i] == "h") {
            break; // avoid repeating other args
        }
    }
    // std::cout << "Build File: " << buildFile;

    std::cout << RESET;
    return 0;
}