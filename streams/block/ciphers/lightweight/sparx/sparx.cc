//
// Created by mhajas on 7/24/18.
//

#include <streams/block/ciphers/lightweight/common/cipher.h>
#include "sparx.h"

namespace block {

    void sparx64::keysetup(const std::uint8_t *key, const std::uint64_t keysize) {
        if (keysize != SPARX_KEY_SIZE) {
            throw std::runtime_error("ROAD-RUNNER function only support key size: "
                                     + std::to_string(SPARX_KEY_SIZE));
        }

        uint8_t i;
        uint16_t temp[2];

        uint16_t *Key = (uint16_t *)key;
        uint16_t *RoundKeys = (uint16_t *)_key;


        RoundKeys[0] = Key[0];
        RoundKeys[1] = Key[1];

        RoundKeys[2] = Key[2];
        RoundKeys[3] = Key[3];

        RoundKeys[4] = Key[4];
        RoundKeys[5] = Key[5];

        temp[0] = Key[6];
        temp[1] = Key[7];


        for(i = 1; i < 2 * _rounds; i++)
        {
            RoundKeys[6 * i + 0] = temp[0];
            RoundKeys[6 * i + 1] = temp[1] + i;

            temp[0] = RoundKeys[6 * (i - 1) + 0];
            temp[1] = RoundKeys[6 * (i - 1) + 1];
            speckey(temp, temp + 1);

            RoundKeys[6 * i + 2] = temp[0];
            RoundKeys[6 * i + 3] = temp[1];

            RoundKeys[6 * i + 4] = temp[0] + RoundKeys[6 * (i - 1) + 2];
            RoundKeys[6 * i + 5] = temp[1] + RoundKeys[6 * (i - 1) + 3];

            temp[0] = RoundKeys[6 * (i - 1) + 4];
            temp[1] = RoundKeys[6 * (i - 1) + 5];
        }


        RoundKeys[6 * 2 * _rounds + 0] = temp[0];
        RoundKeys[6 * 2 * _rounds + 1] = temp[1] + 2 * _rounds;

        temp[0] = RoundKeys[6 * (2 * _rounds - 1) + 0];
        temp[1] = RoundKeys[6 * (2 * _rounds - 1) + 1];
        speckey(temp, temp + 1);

        RoundKeys[6 * 2 * _rounds + 2] = temp[0];
        RoundKeys[6 * 2 * _rounds + 3] = temp[1];
    }

    void sparx64::Encrypt(uint8_t *block) {
        uint8_t i;

        uint32_t *left = (uint32_t *)block;
        uint32_t *right = (uint32_t *)block + 1;
        uint32_t *RoundKeys = (uint32_t *)_key;


        for (i = 0; i < _rounds; i++)
        {
            round_f(left, right, &RoundKeys[6 * i]);
        }


        /* post whitening */
        *left ^= READ_ROUND_KEY_DOUBLE_WORD(RoundKeys[6 * _rounds]);
        *right ^= READ_ROUND_KEY_DOUBLE_WORD(RoundKeys[6 * _rounds + 1]);
    }

    void sparx64::Decrypt(uint8_t *block) {
        int8_t i;

        uint32_t *left = (uint32_t *)block;
        uint32_t *right = (uint32_t *)block + 1;
        uint32_t *RoundKeys = (uint32_t *)_key;


        /* post whitening */
        *left ^= READ_ROUND_KEY_DOUBLE_WORD(RoundKeys[6 * _rounds]);
        *right ^= READ_ROUND_KEY_DOUBLE_WORD(RoundKeys[6 * _rounds + 1]);


        for (i = _rounds - 1; i >= 0 ; i--)
        {
            round_f_inverse(left, right, &RoundKeys[6 * i]);
        }
    }

    void sparx128::keysetup(const std::uint8_t *key, const std::uint64_t keysize) {
        uint8_t i;
        uint16_t temp[2];

        uint16_t *Key = (uint16_t *)key;
        uint16_t *RoundKeys = (uint16_t *)_key;


        RoundKeys[0] = Key[0];
        RoundKeys[1] = Key[1];

        RoundKeys[2] = Key[2];
        RoundKeys[3] = Key[3];

        RoundKeys[4] = Key[4];
        RoundKeys[5] = Key[5];

        RoundKeys[6] = Key[6];
        RoundKeys[7] = Key[7];


        for(i = 1; i < 4 * _rounds + 1; i++)
        {
            temp[0] = RoundKeys[8 * (i - 1) + 4];
            temp[1] = RoundKeys[8 * (i - 1) + 5];
            speckey(temp, temp + 1);
            RoundKeys[8 * i  + 6] = temp[0];
            RoundKeys[8 * i  + 7] = temp[1];

            RoundKeys[8 * i + 0] = temp[0] + RoundKeys[8 * (i - 1) + 6];
            RoundKeys[8 * i + 1] = temp[1] + RoundKeys[8 * (i - 1) + 7] + i;


            temp[0] = RoundKeys[8 * (i - 1) + 0];
            temp[1] = RoundKeys[8 * (i - 1) + 1];
            speckey(temp, temp + 1);
            RoundKeys[8 * i + 2] = temp[0];
            RoundKeys[8 * i + 3] = temp[1];

            RoundKeys[8 * i + 4] = temp[0] + RoundKeys[8 * (i - 1) + 2];
            RoundKeys[8 * i + 5] = temp[1] + RoundKeys[8 * (i - 1) + 3];
        }

    }

    void sparx128::Encrypt(uint8_t *block) {
        uint8_t i;

        uint16_t *Block = (uint16_t *)block;
        uint16_t *RoundKeys = (uint16_t *)_key;


        for (i = 0; i < NUMBER_OF_ROUNDS; i++)
        {
            round_f(Block, &RoundKeys[32 * i]);
        }


        /* post whitening */
        for (i = 0; i < 8; i ++)
        {
            Block[i] ^= READ_ROUND_KEY_WORD(RoundKeys[32 * NUMBER_OF_ROUNDS + i]);
        }
    }

    void sparx128::Decrypt(uint8_t *block) {
        int8_t i;

        uint16_t *Block = (uint16_t *)block;
        uint16_t *RoundKeys = (uint16_t *)_key;


        /* post whitening */
        for (i = 0; i < 8; i++)
        {
            Block[i] ^= READ_ROUND_KEY_WORD(RoundKeys[32 * NUMBER_OF_ROUNDS + i]);
        }


        for (i = NUMBER_OF_ROUNDS - 1; i >= 0 ; i--)
        {
            round_f_inverse(Block, &RoundKeys[32 * i]);
        }
    }
}