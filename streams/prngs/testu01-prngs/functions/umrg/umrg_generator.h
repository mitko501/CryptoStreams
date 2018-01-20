//
// Created by mhajas on 1/19/18.
//

#ifndef EACIRC_STREAMS_UMRG_GENERATOR_H
#define EACIRC_STREAMS_UMRG_GENERATOR_H

#include <vector>
#include <streams/prngs/testu01-prngs/testu01_interface.h>
#include <eacirc-core/json.h>

extern "C" {
#include "umrg.h"
};

namespace prng {

    /**
     * Multiple recursive generator MRG (http://www.iro.umontreal.ca/~simardr/testu01/guideshorttestu01.pdf on page 28)
     *
     * x_n = (a_1 * x_(n−1) + · · · + a_k * x_(n−k)) mod m.
     *
     * s : initial state
     */
    class umrg_generator : public uniform_generator_interface {
    public:
        explicit umrg_generator(const json& config) : umrg_generator(config.at("m"), config.at("k"), config.at("a").get<std::vector<long>>().data(), config.at("s").get<std::vector<long>>().data()) {}

        umrg_generator(int32_t m, int32_t k, long* a, long* s) : uniform_generator_interface(umrg_CreateMRG(m, k, a, s), umrg_DeleteMRG) {}
    };
}

#endif //EACIRC_STREAMS_UMRG_GENERATOR_H
