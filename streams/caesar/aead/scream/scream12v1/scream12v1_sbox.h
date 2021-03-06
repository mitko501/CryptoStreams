namespace Scream12v1_raw {

/* Scream S-box */

#define SBOX(x) do {				\
  /* S5 */ 					\
  x[2] ^= x[0] & x[1];				\
  x[1] ^= x[2];					\
  x[3] ^= x[0] & x[4];				\
  x[2] ^= x[3];					\
  x[0] ^= x[1] & x[3];				\
  x[4] ^= x[1];					\
  x[1] ^= x[2] & x[4];				\
  x[1] ^= x[0];					\
						\
  /* Extend-Xor */				\
  x[0] ^= x[5];					\
  x[1] ^= x[6];					\
  x[2] ^= x[7];					\
						\
  /* Key */					\
  x[3] = ~x[3];					\
  x[4] = ~x[4];					\
						\
  /* S3: 3-bit Keccak S-box */			\
  {						\
    crypto_uint16 __t0 = x[5];			\
    crypto_uint16 __t1 = x[6];			\
    crypto_uint16 __t2 = x[7];			\
    x[5] ^= (~__t1) & __t2;			\
    x[6] ^= (~__t2) & __t0;			\
    x[7] ^= (~__t0) & __t1;			\
  }						\
						\
  /* Truncate-Xor */				\
  x[5] ^= x[0];					\
  x[6] ^= x[1];					\
  x[7] ^= x[2];					\
						\
  /* S5 */					\
  x[2] ^= x[0] & x[1];				\
  x[1] ^= x[2];					\
  x[3] ^= x[0] & x[4];				\
  x[2] ^= x[3];					\
  x[0] ^= x[1] & x[3];				\
  x[4] ^= x[1];					\
  x[1] ^= x[2] & x[4];				\
  x[1] ^= x[0];					\
  } while(0)

#define SBOX_Inv(x) do {                        \
  /* S5 Inv */ 					\
  x[1] ^= x[0];					\
  x[1] ^= x[2] & x[4];				\
  x[4] ^= x[1];					\
  x[0] ^= x[1] & x[3];				\
  x[2] ^= x[3];					\
  x[3] ^= x[0] & x[4];				\
  x[1] ^= x[2];					\
  x[2] ^= x[0] & x[1];				\
						\
  /* Truncate-Xor */				\
  x[5] ^= x[0];					\
  x[6] ^= x[1];					\
  x[7] ^= x[2];					\
						\
  /* S3: 3-bit Keccak S-box (involution) */	\
  {						\
    crypto_uint16 __t0 = x[5];			\
    crypto_uint16 __t1 = x[6];			\
    crypto_uint16 __t2 = x[7];			\
    x[5] ^= (~__t1) & __t2;			\
    x[6] ^= (~__t2) & __t0;			\
    x[7] ^= (~__t0) & __t1;			\
  }						\
						\
  /* Key */					\
  x[3] = ~x[3];					\
  x[4] = ~x[4];					\
						\
  /* Extend-Xor */				\
  x[0] ^= x[5];					\
  x[1] ^= x[6];					\
  x[2] ^= x[7];					\
						\
  /* S5 Inv */					\
  x[1] ^= x[0];					\
  x[1] ^= x[2] & x[4];				\
  x[4] ^= x[1];					\
  x[0] ^= x[1] & x[3];				\
  x[2] ^= x[3];					\
  x[3] ^= x[0] & x[4];				\
  x[1] ^= x[2];					\
  x[2] ^= x[0] & x[1];				\
  } while(0)

} // namespace Scream12v1_raw
