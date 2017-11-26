//
// Created by mhajas on 11/14/17.
//

#include "prng_generator.h"
#include <memory.h>
#include <streams/prngs/testu01-prngs/testu01_generator.h>
namespace prng {

    prng_generator::prng_generator(const json& config, default_seed_source& seeder)
            : _generator(create_prng_interface(config, seeder))
    {}

    void prng_generator::generate_bits(unsigned char *data, size_t number_of_bytes) {
        _generator->generate_bits(data, number_of_bytes);
    }
}
