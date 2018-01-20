//
// Created by mhajas on 1/8/18.
//

#include <gtest/gtest.h>
#include <memory>
#include <streams/prngs/testu01-prngs/functions/ulcg/ulcg_generator.h>
#include <streams/prngs/testu01-prngs/testu01_interface.h>
#include <streams/prngs/testu01-prngs/functions/umrg/umrg_generator.h>


TEST(LCG, basic_test) {
    auto test = std::make_unique<prng::ulcg_generator>(500 + 1, 1, 1, 0); // +1 in order to avoid last zero
    std::vector<uint32_t> data(500);
    test->generate_bits(reinterpret_cast<uint8_t *>(data.data()), data.size() * 4);

    uint64_t j = 0;

    for (auto i : data) {
        ASSERT_EQ(++j, i);
    }
}

TEST(MRG, basic_test) {
    auto test = std::make_unique<prng::umrg_generator>(INT32_MAX, 2, std::vector<long>{1,1}.data(), std::vector<long>{1,1}.data()); // Fibonacci numbers
    std::vector<uint32_t> data(40);
    test->generate_bits(reinterpret_cast<uint8_t *>(data.data()), data.size() * 4);

    uint32_t x_1 = 1;
    uint32_t x_2 = 1;

    uint32_t  temp = 0;

    for (auto i : data) {
        temp = x_1 + x_2;
        x_1 = x_2;
        x_2 = temp;

        ASSERT_EQ(x_2, i);
    }
}