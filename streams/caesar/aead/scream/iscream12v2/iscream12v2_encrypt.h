#ifndef ISCREAM12V2_ENCRYPT_H
#define ISCREAM12V2_ENCRYPT_H

#include "iscream12v2_api.h"

namespace Iscream12v2_raw {
extern int numRounds;

int crypto_aead_encrypt(unsigned char *c, unsigned long long *clen,
                        const unsigned char *m, unsigned long long mlen,
                        const unsigned char *ad, unsigned long long adlen,
                        const unsigned char *nsec, const unsigned char *npub,
                        const unsigned char *k);

int crypto_aead_decrypt(unsigned char *m, unsigned long long *outputmlen,
                        unsigned char *nsec,
                        const unsigned char *c, unsigned long long clen,
                        const unsigned char *ad, unsigned long long adlen,
                        const unsigned char *npub, const unsigned char *k);
} // namespace Iscream12v2_raw

#endif // ISCREAM12V2_ENCRYPT_H
