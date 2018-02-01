//
// Created by mhajas on 1/20/18.
//

#ifndef EACIRC_STREAMS_UCARRY_GENERATOR_H
#define EACIRC_STREAMS_UCARRY_GENERATOR_H

#include <streams/prngs/testu01-prngs/testu01_interface.h>
#include <eacirc-core/json.h>

extern "C" {
#include "ucarry.h"
};

namespace prng {

    /**
     * Generators based on linear recurrences with carry (http://www.iro.umontreal.ca/~simardr/testu01/guideshorttestu01.pdf on page 31)
     *
     * x_i = (x_(i−r) + x_(i−s) + c_(i−1)) mod m
     * c_i = (x_(i−r) + x_(i−s) + c_(i−1)) div m
     *
     * s : initial state - The vector S[0..k-1] contains the k initial values (x_0, . . . , x_(k−1)), where k = max{r, s},
     */
    class ucarry_AWS_generator : public uniform_generator_interface {
    public:
        explicit ucarry_AWS_generator(const json& config) : ucarry_AWS_generator(config.at("r"), config.at("s"), config.at("c"), config.at("m"), config.at("s").get<std::vector<unsigned long>>().data()) {}

        ucarry_AWS_generator(uint32_t r, uint32_t s, uint32_t c, uint32_t m, unsigned long* S) : uniform_generator_interface(ucarry_CreateAWC(r, s, c, m, S), ucarry_DeleteAWC) {}
    };
}

#endif //EACIRC_STREAMS_UCARRY_GENERATOR_H
