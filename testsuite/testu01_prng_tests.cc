//
// Created by mhajas on 1/8/18.
//

#include <gtest/gtest.h>
#include <memory>
#include <streams/prngs/testu01-prngs/functions/ulcg/ulcg_generator.h>
#include <streams/prngs/testu01-prngs/testu01_interface.h>
#include <streams/prngs/testu01-prngs/functions/umrg/umrg_generator.h>
#include <streams/prngs/testu01-prngs/functions/ucarry/ucarry_generator.h>


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

TEST(CARRY, AWS) {
    auto test = std::make_unique<prng::ucarry_AWS_generator>(1, 2, 0, INT32_MAX, std::vector<unsigned long>{0,1}.data()); // Fibonacci numbers
    std::vector<uint32_t> data(40);
    test->generate_bits(reinterpret_cast<uint8_t *>(data.data()), data.size() * 4);

    uint32_t x_1 = 0;
    uint32_t x_2 = 1;

    uint32_t  temp = 0;

    for (auto i : data) {
        temp = x_1 + x_2;
        x_1 = x_2;
        x_2 = temp;

        ASSERT_EQ(x_2, i);
    }
}

TEST(CARRY, SWB) {
    auto test = std::make_unique<prng::ucarry_SWB_generator>(1, 2, 0, UINT32_MAX, std::vector<unsigned long>{0,1}.data()); // Fibonacci numbers
    std::vector<uint32_t> data(40);
    test->generate_bits(reinterpret_cast<uint8_t *>(data.data()), data.size() * 4);

    uint32_t x_1 = 0;
    uint32_t x_2 = 1;
    uint32_t c = 0;

    uint32_t  temp = 0;

    for (auto i : data) {
        temp = x_2 - x_1 - c;
        c = (static_cast<int64_t>(x_2) - static_cast<int64_t>(x_1) - static_cast<int>(c) < 0) ? 1 : 0;
        x_1 = x_2;
        x_2 = temp;

        //ASSERT_EQ(x_2, i);

        std::cout << i << " - " << x_2 << std::endl;
    }
}