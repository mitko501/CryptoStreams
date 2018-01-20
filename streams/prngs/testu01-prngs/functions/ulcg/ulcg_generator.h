//
// Created by mhajas on 1/8/18.
//

#ifndef EACIRC_STREAMS_ULCG_GENERATOR_H
#define EACIRC_STREAMS_ULCG_GENERATOR_H

#include <streams/prngs/testu01-prngs/testu01_interface.h>
#include <eacirc-core/json.h>

extern "C" {
#include "ulcg.h"
};

namespace prng {

    /**
     * Linear congruential generator LCG (http://www.iro.umontreal.ca/~simardr/testu01/guideshorttestu01.pdf on page 23)
     *
     * x_i = [a * x_(i - 1) + x] mod m
     *
     * s : initial state
     */
    class ulcg_generator : public uniform_generator_interface {
    public:
        explicit ulcg_generator(const json& config) : ulcg_generator(config.at("m"), config.at("a"), config.at("c"), config.at("s")) {}

        ulcg_generator(int32_t m, int32_t a, int32_t c, int32_t s) : uniform_generator_interface(ulcg_CreateLCG(m, a, c, s), ulcg_DeleteGen) {}
    };
}

#endif //EACIRC_STREAMS_ULCG_GENERATOR_H
