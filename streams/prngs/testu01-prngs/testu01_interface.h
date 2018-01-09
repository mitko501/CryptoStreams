//
// Created by mhajas on 11/14/17.
//

#ifndef EACIRC_STREAMS_TESTU01_INTERFACE_H
#define EACIRC_STREAMS_TESTU01_INTERFACE_H
#include <streams/prngs/prng_interface.h>
extern "C" {
#include <streams/prngs/testu01-prngs/includes/unif01.h>
};

namespace prng {

    template<typename GENERATOR, typename  DELETER>
    class testu01_interface : public prng_interface {
    protected:
        std::unique_ptr<GENERATOR, DELETER> _generator;

    public:
        explicit testu01_interface(GENERATOR* generator, DELETER deleter = nullptr) : _generator(generator, deleter) {}

        void generate_bits(std::uint8_t* data, size_t number_of_bytes) override {
            int current_index = 0;

            while (number_of_bytes > 0) {
                uint32_t generated_data = _generator->GetBits(_generator->param, _generator->state); // Get 4 Bytes from generator

                for (auto i = 0; i < std::min<size_t>(number_of_bytes, 4); i++) {
                    data[current_index++] = static_cast<std::uint8_t>(generated_data & 0xFF);
                    generated_data >>= 8;
                }

                number_of_bytes -= 4;
            }
        }
    };

    class uniform_generator_interface : public testu01_interface<unif01_Gen, void(*) (unif01_Gen*)> {
    public:
        uniform_generator_interface(unif01_Gen *generator, void (*deleter)(unif01_Gen *))
                : testu01_interface(generator, deleter)
        {}
    };
}
#endif //EACIRC_STREAMS_TESTU01_INTERFACE_H
