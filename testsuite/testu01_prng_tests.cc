//
// Created by mhajas on 1/8/18.
//

#include <gtest/gtest.h>
#include <memory>
#include <streams/prngs/testu01-prngs/functions/ulcg/ulcg_generator.h>
#include <streams/prngs/testu01-prngs/testu01_interface.h>


TEST(LCG, basic_test) {
    auto test = std::make_unique<prng::ulcg_generator>(500, 1, 1, 0);

    std::vector<uint8_t > data(500*4);

    test->generate_bits(data.data(), data.size());

    for (auto i : data) {
        std::cout << static_cast<int>(i) << std::endl;
    }
}