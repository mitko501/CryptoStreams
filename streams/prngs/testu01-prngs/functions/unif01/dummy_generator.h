//
// Created by mhajas on 11/14/17.
//

#ifndef EACIRC_STREAMS_DUMMY_GENERATOR_H
#define EACIRC_STREAMS_DUMMY_GENERATOR_H

#include <streams/prngs/testu01-prngs/testu01_interface.h>
#include <eacirc-core/json.h>

extern "C" {
#include <streams/prngs/testu01-prngs/includes/unif01.h>
};

namespace prng {

    class dummy_generator : public uniform_generator_interface {
    public:
        explicit dummy_generator(const json& config) : uniform_generator_interface(unif01_CreateDummyGen(), unif01_DeleteDummyGen) {}
    };
}
#endif //EACIRC_STREAMS_DUMMY_GENERATOR_H
