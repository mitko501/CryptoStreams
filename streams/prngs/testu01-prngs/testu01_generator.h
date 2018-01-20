//
// Created by mhajas on 11/14/17.
//

#ifndef EACIRC_STREAMS_TESTU01_GENERATOR_H
#define EACIRC_STREAMS_TESTU01_GENERATOR_H

#include <memory>
#include <streams/prngs/prng_interface.h>
#include <eacirc-core/json.h>
#include <memory.h>
#include <streams/prngs/testu01-prngs/functions/unif01/dummy_generator.h>
#include <streams/prngs/testu01-prngs/functions/ulcg/ulcg_generator.h>
#include <streams/prngs/testu01-prngs/functions/umrg/umrg_generator.h>

namespace prng {

    struct testu01_generator {

        static std::unique_ptr<prng_interface>
        create_testu01_interface(const json& configuration, default_seed_source& seeder) {
            auto name = configuration.at("name");

            if(name == "testu01-dummy") return std::make_unique<dummy_generator>(configuration);
            if(name == "testu01-ulcg") return std::make_unique<ulcg_generator>(configuration);
            if(name == "testu01-umrg") return std::make_unique<umrg_generator>(configuration);
        }
    };
}

#endif //EACIRC_STREAMS_TESTU01_GENERATOR_H
