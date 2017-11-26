//
// Created by mhajas on 11/14/17.
//

#include "prng_stream.h"
namespace prng {

    vec_view prng_stream::next() {
        _generator.generate_bits(_data.data(), _data.size());
        return make_cview(_data);
    }

    prng_stream::prng_stream(const json& config, default_seed_source& seeder, std::size_t osize)
            : stream(osize)
            , _generator(config, seeder)
            , _data(osize)
    {}
}
