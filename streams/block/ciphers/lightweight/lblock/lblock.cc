//
// Created by mhajas on 7/8/18.
//

#include "lblock.h"

void block::lblock::keysetup(const std::uint8_t *key, const std::uint64_t keysize) {
    if (keysize != LBLOCK_KEY_SIZE) {
        throw std::runtime_error("LBLOCK function only support key size: " + std::to_string(LBLOCK_KEY_SIZE));
    }

    uint16_t shiftedKey[2];
    uint8_t keyCopy[LBLOCK_KEY_SIZE];


    uint16_t *Key = (uint16_t *) key;
    uint32_t *RoundKeys = (uint32_t *) _key;


    uint16_t *KeyCopy = (uint16_t *) keyCopy;


    KeyCopy[4] = Key[4];
    KeyCopy[3] = Key[3];
    KeyCopy[2] = Key[2];
    KeyCopy[1] = Key[1];
    KeyCopy[0] = Key[0];


    if (_rounds >= 1) {
        /* Set round subkey K(1) */
        RoundKeys[0] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
    }

    if (_rounds >= 2) {
        /* Set round subkey K(2) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x00;
        keyCopy[5] = keyCopy[5] ^ 0x40;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[1] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(2) - End */
    }

    if (_rounds >= 3) {
        /* Set round subkey K(3) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x00;
        keyCopy[5] = keyCopy[5] ^ 0x80;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[2] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(3) - End */
    }

    if (_rounds >= 4) {
        /* Set round subkey K(4) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x00;
        keyCopy[5] = keyCopy[5] ^ 0xC0;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[3] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(4) - End */


    }

    if (_rounds >= 5) {
        /* Set round subkey K(5) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x01;
        keyCopy[5] = keyCopy[5] ^ 0x00;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[4] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(5) - End */


    }

    if (_rounds >= 6) {
        /* Set round subkey K(6) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x01;
        keyCopy[5] = keyCopy[5] ^ 0x40;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[5] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(6) - End */

    }

    if (_rounds >= 7) {
        /* Set round subkey K(7) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x01;
        keyCopy[5] = keyCopy[5] ^ 0x80;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[6] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(7) - End */


    }
    if (_rounds >= 8) {
        /* Set round subkey K(8) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x01;
        keyCopy[5] = keyCopy[5] ^ 0xC0;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[7] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(8) - End */


    }
    if (_rounds >= 9) {
        /* Set round subkey K(9) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];;


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x02;
        keyCopy[5] = keyCopy[5] ^ 0x00;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[8] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(9) - End */


    }
    if (_rounds >= 10) {
        /* Set round subkey K(10) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x02;
        keyCopy[5] = keyCopy[5] ^ 0x40;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[9] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(10) - End */


    }
    if (_rounds >= 11) {
        /* Set round subkey K(11) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x02;
        keyCopy[5] = keyCopy[5] ^ 0x80;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[10] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(11) - End */


    }
    if (_rounds >= 12) {
        /* Set round subkey K(12) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x02;
        keyCopy[5] = keyCopy[5] ^ 0xC0;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[11] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(12) - End */


    }
    if (_rounds >= 13) {
        /* Set round subkey K(13) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x03;
        keyCopy[5] = keyCopy[5] ^ 0x00;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[12] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(13) - End */


    }
    if (_rounds >= 14) {
        /* Set round subkey K(14) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x03;
        keyCopy[5] = keyCopy[5] ^ 0x40;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[13] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(14) - End */


    }
    if (_rounds >= 15) {
        /* Set round subkey K(15) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x03;
        keyCopy[5] = keyCopy[5] ^ 0x80;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[14] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(15) - End */


    }
    if (_rounds >= 16) {
        /* Set round subkey K(16) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x03;
        keyCopy[5] = keyCopy[5] ^ 0xC0;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[15] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(16) - End */


    }
    if (_rounds >= 17) {
        /* Set round subkey K(17) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x04;
        keyCopy[5] = keyCopy[5] ^ 0x00;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[16] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(17) - End */


    }
    if (_rounds >= 18) {
        /* Set round subkey K(18) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x04;
        keyCopy[5] = keyCopy[5] ^ 0x40;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[17] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(18) - End */


    }
    if (_rounds >= 19) {
        /* Set round subkey K(19) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x04;
        keyCopy[5] = keyCopy[5] ^ 0x80;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[18] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(19) - End */


    }
    if (_rounds >= 20) {
        /* Set round subkey K(20) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x04;
        keyCopy[5] = keyCopy[5] ^ 0xC0;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[19] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(20) - End */


    }
    if (_rounds >= 21) {
        /* Set round subkey K(21) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x05;
        keyCopy[5] = keyCopy[5] ^ 0x00;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[20] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(21) - End */


    }
    if (_rounds >= 22) {
        /* Set round subkey K(22) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x05;
        keyCopy[5] = keyCopy[5] ^ 0x40;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[21] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(22) - End */


    }
    if (_rounds >= 23) {
        /* Set round subkey K(23) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x05;
        keyCopy[5] = keyCopy[5] ^ 0x80;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[22] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(23) - End */


    }
    if (_rounds >= 24) {
        /* Set round subkey K(24) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x05;
        keyCopy[5] = keyCopy[5] ^ 0xC0;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[23] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(24) - End */


    }
    if (_rounds >= 25) {
        /* Set round subkey K(25) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x06;
        keyCopy[5] = keyCopy[5] ^ 0x00;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[24] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(25) - End */


    }
    if (_rounds >= 26) {
        /* Set round subkey K(26) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x06;
        keyCopy[5] = keyCopy[5] ^ 0x40;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[25] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(26) - End */


    }
    if (_rounds >= 27) {
        /* Set round subkey K(27) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x06;
        keyCopy[5] = keyCopy[5] ^ 0x80;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[26] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(27) - End */


    }
    if (_rounds >= 28) {
        /* Set round subkey K(28) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x06;
        keyCopy[5] = keyCopy[5] ^ 0xC0;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[27] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(28) - End */


    }
    if (_rounds >= 29) {
        /* Set round subkey K(29) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x07;
        keyCopy[5] = keyCopy[5] ^ 0x00;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[28] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(29) - End */


    }
    if (_rounds >= 30) {
        /* Set round subkey K(30) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x07;
        keyCopy[5] = keyCopy[5] ^ 0x40;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[29] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(30) - End */


    }
    if (_rounds >= 31) {
        /* Set round subkey K(31) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x07;
        keyCopy[5] = keyCopy[5] ^ 0x80;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[30] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(31) - End */


    }
    if (_rounds >= 32) {
        /* Set round subkey K(32) - End */

        /* (a) K <<< 29 */
        shiftedKey[1] = KeyCopy[4];
        shiftedKey[0] = KeyCopy[3];


        KeyCopy[4] = (KeyCopy[3] << 13) ^ (KeyCopy[2] >> 3);
        KeyCopy[3] = (KeyCopy[2] << 13) ^ (KeyCopy[1] >> 3);
        KeyCopy[2] = (KeyCopy[1] << 13) ^ (KeyCopy[0] >> 3);
        KeyCopy[1] = (KeyCopy[0] << 13) ^ (shiftedKey[1] >> 3);
        KeyCopy[0] = (shiftedKey[1] << 13) ^ (shiftedKey[0] >> 3);


        /* (b) S-boxes */
        keyCopy[9] = (READ_SBOX_BYTE(S9[keyCopy[9] >> 4]) << 4) ^ READ_SBOX_BYTE(S8[(keyCopy[9] & 0x0F)]);


        /* (c) XOR */
        keyCopy[6] = keyCopy[6] ^ 0x07;
        keyCopy[5] = keyCopy[5] ^ 0xC0;


        /* (d) Set the round subkey K(i+1) */
        RoundKeys[31] = (((uint32_t) KeyCopy[4]) << 16) ^ (uint32_t) KeyCopy[3];
        /* Set round subkey K(32) - End */
    }
}

void block::lblock::Encrypt(uint8_t *block) {
    uint8_t temp[4];
    uint8_t p[4];


    uint8_t *x = block;
    uint8_t *k = _key;


    uint32_t *X = (uint32_t *) x;
    uint32_t *K = (uint32_t *) k;

    uint32_t *Temp = (uint32_t *) temp;


    /* Save a copy of the left half of X */
    Temp[0] = X[1];

    for (auto i = 1; i <= _rounds; i++) {
        if (i % 2 == 0) {
            X[0] = Temp[0];
        } else {
            if (i != 1) /* Save a copy of the left half of X */
                X[1] = Temp[0];
        }

        /* XOR X left half with the round key: X XOR K(j) */
        Temp[0] = Temp[0] ^ READ_ROUND_KEY_DOUBLE_WORD(K[i - 1]);

        /* (2) Confusion function S: S(X XOR K(i)) */
        temp[3] = (READ_SBOX_BYTE(S7[temp[3] >> 4]) << 4) ^ READ_SBOX_BYTE(S6[temp[3] & 0x0F]);
        temp[2] = (READ_SBOX_BYTE(S5[temp[2] >> 4]) << 4) ^ READ_SBOX_BYTE(S4[temp[2] & 0x0F]);
        temp[1] = (READ_SBOX_BYTE(S3[temp[1] >> 4]) << 4) ^ READ_SBOX_BYTE(S2[temp[1] & 0x0F]);
        temp[0] = (READ_SBOX_BYTE(S1[temp[0] >> 4]) << 4) ^ READ_SBOX_BYTE(S0[temp[0] & 0x0F]);

        /* (3) Diffusion function P: P(S(X XOR K(i))) */
        p[3] = (temp[3] << 4) ^ (temp[2] & 0x0F);
        p[2] = (temp[3] & 0xF0) ^ (temp[2] >> 4);
        p[1] = (temp[1] << 4) ^ (temp[0] & 0x0F);
        p[0] = (temp[1] & 0xF0) ^ (temp[0] >> 4);

        if (i % 2 == 0) {
            /* F(X(i-1), K(i-1)) XOR (X(i-2) <<< 8) */
            temp[3] = p[3] ^ x[6];
            temp[2] = p[2] ^ x[5];
            temp[1] = p[1] ^ x[4];
            temp[0] = p[0] ^ x[7];
        } else {
            /* F(X(i-1), K(i-1)) XOR (X(i-2) <<< 8) */
            temp[3] = p[3] ^ x[2];
            temp[2] = p[2] ^ x[1];
            temp[1] = p[1] ^ x[0];
            temp[0] = p[0] ^ x[3];
        }

    }

    X[1] = X[0];

    X[0] = Temp[0];
}

void block::lblock::Decrypt(uint8_t *block) {
    uint8_t temp[4];
    uint8_t p[4];


    uint8_t *x = block;
    uint8_t *k = _key;


    uint32_t *X = (uint32_t *) x;
    uint32_t *K = (uint32_t *) k;

    uint32_t *Temp = (uint32_t *) temp;


    /* Save a copy of the left half of X */
    Temp[0] = X[1];

    for (auto i = 1; i <= _rounds; i++) {
        if (i % 2 == 0) {
            X[0] = Temp[0];
        } else {
            if (i != 1) /* Save a copy of the left half of X */
                X[1] = Temp[0];
        }

        /* XOR X left half with the round key: X XOR K(j) */
        Temp[0] = Temp[0] ^ READ_ROUND_KEY_DOUBLE_WORD(K[32 - i]);

        /* (2) Confusion function S: S(X XOR K(j)) */
        temp[3] = (READ_SBOX_BYTE(S7[temp[3] >> 4]) << 4) ^ READ_SBOX_BYTE(S6[temp[3] & 0x0F]);
        temp[2] = (READ_SBOX_BYTE(S5[temp[2] >> 4]) << 4) ^ READ_SBOX_BYTE(S4[temp[2] & 0x0F]);
        temp[1] = (READ_SBOX_BYTE(S3[temp[1] >> 4]) << 4) ^ READ_SBOX_BYTE(S2[temp[1] & 0x0F]);
        temp[0] = (READ_SBOX_BYTE(S1[temp[0] >> 4]) << 4) ^ READ_SBOX_BYTE(S0[temp[0] & 0x0F]);

        /* (3) Diffusion function P: P(S(X XOR K(j))) */
        p[3] = (temp[3] << 4) ^ (temp[2] & 0x0F);
        p[2] = (temp[3] & 0xF0) ^ (temp[2] >> 4);
        p[1] = (temp[1] << 4) ^ (temp[0] & 0x0F);
        p[0] = (temp[1] & 0xF0) ^ (temp[0] >> 4);

        if (i % 2 == 0) {
            /* F(X(j+1), K(j+1)) XOR X(j+2)) >>> 8) */
            temp[3] = x[4] ^ p[0];
            temp[2] = x[7] ^ p[3];
            temp[1] = x[6] ^ p[2];
            temp[0] = x[5] ^ p[1];
        } else {
            /* F(X(j+1), K(j+1)) XOR X(j+2)) >>> 8) */
            temp[3] = x[0] ^ p[0];
            temp[2] = x[3] ^ p[3];
            temp[1] = x[2] ^ p[2];
            temp[0] = x[1] ^ p[1];
        }

    }

    X[1] = X[0];

    X[0] = Temp[0];

}
