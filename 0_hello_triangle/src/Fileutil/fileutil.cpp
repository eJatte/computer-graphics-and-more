//
// Created by jatte on 2022-10-16.
//

#include "fileutil.h"

#include <string>
#include <fstream>
#include <sstream>

namespace fileutil {
    std::string readFile(const std::string &filename) {
        std::ifstream t(filename);
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }
}
