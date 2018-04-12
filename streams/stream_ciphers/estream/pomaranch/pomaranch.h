#include "ecrypt-sync.h"

namespace stream_ciphers {
namespace estream {

/* ------------------------------------------------------------------------- */

/* My functions */
void state_upd(u16 *state, const u16 F_mask);
u16 KeyMap(const u16 state, const u16 Key);

/* My constants */
const u16 pi[9] = {0x90F,  0x36A8, 0x2216,
				   0x2308, 0x34C4, 0x3198,
				   0x28B8, 0x370,  0x1CD1}; /* binary expansion of the decimal part of pi */

const u8 S[512] = {
  0,0,0,127,64,85,127,54,96,18,42,57,63,83,91,51,112,17,73,38,21,103,92,49,95,
  122,105,113,45,104,25,61,120,107,8,112,100,89,19,39,74,102,115,41,110,80,88,
  119,47,62,61,15,52,29,56,88,22,16,52,26,12,125,94,93,124,75,53,14,4,77,120,84,
  114,2,44,112,73,9,19,19,101,121,115,21,57,5,20,115,55,72,104,14,108,63,59,
  116,87,121,31,89,94,80,7,91,90,98,14,33,92,84,44,72,75,82,72,82,90,85,13,48,
  70,97,62,34,47,24,46,108,126,91,101,76,26,69,71,119,66,30,38,95,60,97,106,117,
  57,82,65,78,86,78,56,82,100,111,4,34,73,65,9,51,50,94,124,87,57,72,10,77,92,
  54,2,64,74,78,121,48,27,56,100,18,52,98,7,51,54,84,31,94,93,31,122,12,43,29,
  60,70,79,5,108,110,111,76,40,121,3,39,45,68,45,14,113,13,71,117,16,120,46,
  63,42,1,22,80,100,76,37,44,105,13,36,2,41,21,109,125,106,71,70,122,88,23,35,
  84,48,87,95,12,81,7,87,81,12,30,23,105,54,3,127,1,109,42,114,36,102,39,77,34,
  98,79,99,117,123,81,97,86,79,51,83,77,111,33,30,125,48,59,53,33,58,123,28,22,
  41,27,96,4,39,19,43,115,103,10,28,16,105,126,50,114,55,32,66,69,17,41,36,37,
  96,43,68,66,89,49,25,55,111,11,62,61,107,67,28,37,36,28,69,95,102,3,46,60,
  27,17,1,109,96,29,37,112,103,68,60,40,24,62,13,59,92,11,114,24,9,79,26,29,113,
  106,3,127,25,32,27,88,42,5,15,123,47,116,46,40,15,25,61,34,6,83,85,2,78,73,
  30,68,35,107,103,45,66,26,118,122,119,67,55,44,38,9,20,102,124,32,65,101,83,
  10,86,74,98,5,22,110,7,123,56,75,6,63,35,120,58,90,8,97,124,81,23,119,31,49,
  85,58,64,126,11,49,104,118,50,80,38,69,18,4,86,8,52,90,6,117,18,89,65,76,20,
  74,10,21,118,93,126,23,53,113,35,67,99,110,125,116,108,99,11,33,17,8,106,53,
  24,50,43,20,47,59,6,99,104,93,67,71,107,16,40,101,70,118,15,58,75,32,116,109,
  91,64,1,0}; /* 9-to-7 S-box */

const u8 F[128] = {0,1,1,1,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,0,0,0,0,1,0,1,1,1,1,1,0,0,
				   1,1,0,0,0,1,0,1,1,0,0,0,1,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,1,1,0,
				   1,0,1,0,1,1,0,0,0,0,1,1,0,0,1,0,0,1,1,0,1,1,1,0,0,1,0,0,0,1,1,1,
				   0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,0,0,0};

const u16 F_mask[2] = {0x15C5, 0x2A3A};	/* location of F-cells on the register and the complement */
const u16 tap_mask[2] = {0x7C0, 0x1E};	/* taps to the S-box */
const u16 fdk_mask = 0x2020,			/* feedback from cells 14 and 6 */
		  out_mask = 0x1000,			/* key stream contribution from cell 13 */
		  mask9 = 0x1;					/* initialization feedback from section 9 is from cell 1 */

/* My globals */
u8 wt_mod2[256] = {0};					/* binary weight of all bytes */

/* ------------------------------------------------------------------------- */


} // namespace estream
} // namespace stream_ciphers