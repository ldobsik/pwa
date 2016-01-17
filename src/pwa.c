#include "pwa.h"
#include "pwa_config.h"

#include "typedef.h"

s16 pwa_interp(PWA_CONST_SEG_ATTR const pwa_descriptor_t *pwa, s16 x)
{
  /* calculate 'x' relative to start of the domain */
  /* cast to u16 to enforce modular arithmetic instead of integer overflow */
  u16 dx = (u16)x - (u16)pwa->min_d;
  u16 idx;
  s16 y; 
                   
  /* saturate 'x' below domain interval */
  if(x < pwa->min_d)
  {
    dx = 0U;
  }
  
  /* calculate interval index = dx/step */
  idx = dx >> pwa->step_d;
  
  /* calculate dx relative to start of interval */
  dx = dx & pwa->msk_s;
  
  /* saturate 'x' above domain interval */
  if(idx >= pwa->n_fn)
  {
    y = (*pwa->fn)[pwa->n_fn];
  }
  else
  {
    /* 'x' is inside the domain */
    s16 y1 = (*pwa->fn)[idx];
    s16 y2 = (*pwa->fn)[idx+1U];

    /* rounds half towards infinity */
    if(y2 > y1)
    {
      u16 dy = (u16)y2 - (u16)y1; 
      dy = (u16)(((u32)dy*dx + pwa->half_s) >> pwa->step_d);  
      y = y1 + (s16)dy;
    }
    else
    {
      u16 dy = (u16)y1 - (u16)y2; 
      dy = (u16)(((u32)dy*dx + pwa->half_s) >> pwa->step_d);  
      y = y1 - (s16)dy;
    }
  }  
  
  return y;
}
