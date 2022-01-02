//
// Created by Deepak Ramalingam on 12/25/21.
//

#ifndef CORE_UUID_H
#define CORE_UUID_H

#include <random>
#include <sstream>

namespace uuid {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::string generate_uuid_v4();
}

#endif //CORE_UUID_H
