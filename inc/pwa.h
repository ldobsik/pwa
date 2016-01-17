#ifndef PWA_H
#define PWA_H

#include "pwa_config.h"

#include "typedef.h"

#define PWA_DESCRIPTOR_INIT(TABLE, MIN, STEP) {&TABLE, ARRAY_SIZE(TABLE)-1, MIN, STEP, (1UL << STEP)-1, 1UL << (STEP-1)}

typedef struct
{
  PWA_CONST_SEG_ATTR const s16 (*fn)[]; /* function values at control points */
  u16 n_fn;      /* number of intervals */  
  s16 min_d;     /* domain interval minimum */
  u8  step_d;    /* log2 of domain step size (step size is 2**step_d) */
  u16 msk_s;     /* bit mask for step size (initialize to 2**step_d - 1) */
  u16 half_s;    /* pre-computed half-step (used for correct rounding) */
} pwa_descriptor_t;

s16 pwa_interp(PWA_CONST_SEG_ATTR const pwa_descriptor_t *pwa, s16 x);

#endif
