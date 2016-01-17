#include "utest.h"
#include <stdio.h>
#include <math.h>

#include "typedef.h"
#include "pwa.h"

static const s16 dom1_tab[] = {
  /* 1st interval increasing, 2nd decreasing */
  50, 200, -10000                         /* -500, -244, 12 */
};
static const pwa_descriptor_t   dom1_desc = PWA_DESCRIPTOR_INIT(dom1_tab, -500, 8);

static const s16 dom2_tab[] = {
  -32768, 0                               /* -32768, 0 */
};
static const pwa_descriptor_t   dom2_desc = PWA_DESCRIPTOR_INIT(dom2_tab, -32768, 15);

static const s16 dom3_tab[] = {
  0, 32767                               /* 0, 32767 */
};
static const pwa_descriptor_t   dom3_desc = PWA_DESCRIPTOR_INIT(dom3_tab, 0, 15);

static char message[100];

static u16 step;

/* reference implementation in floating point arithmetic */                       
static double pwa_interp_FP(const pwa_descriptor_t *pwa, double x)
{
  // pwa domain step
  double step  = 1ul << pwa->step_d;
  // x relative to min(dom) 
  double  dx   = x - pwa->min_d;
  // max(dom) - min(dom)
  double maxdx = pwa->n_fn * step;
  // interval index (starting from 0) 
  int      idx = floor(dx / step);

  // saturate below  
  if(dx < 0)      dx = 0;
  //saturate above, return 
  if(dx >= maxdx) return (*pwa->fn)[pwa->n_fn]; 

  // dx within the selected interval
  dx = dx - idx * step;

  // dy in the current interval
  double dt = (double)((*pwa->fn)[idx+1]) - (*pwa->fn)[idx];

  // y
  return (*pwa->fn)[idx] + dt*dx/step;
}
                       
/******************************************************************************/
TEST_GROUP(intmax);

TEST_SETUP(intmax) {
  step = 1u << dom3_desc.step_d;              
}

TEST_TEAR_DOWN(intmax) {}

TEST(intmax, interval)
{
  /* scan every input value from the interval */
  for(int i = dom3_desc.min_d; i < dom3_desc.min_d + step; i++)
  {
    s16 result = pwa_interp(&dom3_desc, i);
    /* calculate the interpolated value in doubles, round half towards infinity */
    s16 reference = round(pwa_interp_FP(&dom3_desc, i));

    snprintf(message, 100, "i = %d", i);
    TEST_ASSERT_EQUAL_MESSAGE(reference, result, message);
  }              
}
/******************************************************************************/
TEST_GROUP(intmin);

TEST_SETUP(intmin) {
  step = 1u << dom2_desc.step_d;              
}

TEST_TEAR_DOWN(intmin) {}

TEST(intmin, interval)
{
  /* scan every input value from the interval */
  for(int i = dom2_desc.min_d; i < dom2_desc.min_d + step; i++)
  {
    s16 result = pwa_interp(&dom2_desc, i);
    /* calculate the interpolated value in doubles, round half towards infinity */
    s16 reference = round(pwa_interp_FP(&dom2_desc, i));

    snprintf(message, 100, "i = %d", i);
    TEST_ASSERT_EQUAL_MESSAGE(reference, result, message);
  }              
}

/******************************************************************************/
TEST_GROUP(interval);

TEST_SETUP(interval) {
  step = 1 << dom1_desc.step_d;              
}

TEST_TEAR_DOWN(interval) {}

TEST(interval, first)
{
  /* scan every input value from the first interval */
  for(int i = dom1_desc.min_d; i < dom1_desc.min_d + step; i++)
  {
    s16 result = pwa_interp(&dom1_desc, i);
    /* calculate the interpolated value in doubles, round half towards infinity */
    s16 reference = round(pwa_interp_FP(&dom1_desc, i));

    snprintf(message, 100, "i = %d", i);
    TEST_ASSERT_EQUAL_MESSAGE(reference, result, message);
  }              
}

TEST(interval, second)
{
  /* scan every input value from the second interval */
  for(int i = dom1_desc.min_d + step; i < dom1_desc.min_d + 2*step; i++)
  {
    s16 result = pwa_interp(&dom1_desc, i);
    /* calculate the interpolated value in doubles, round half towards infinity */
    s16 reference = round(pwa_interp_FP(&dom1_desc, i));

    snprintf(message, 100, "i = %d", i);
    TEST_ASSERT_EQUAL_MESSAGE(reference, result, message);
  }              
}
/******************************************************************************/
TEST_GROUP(grid);

TEST_SETUP(grid) {
  step = 1 << dom1_desc.step_d;              
}

TEST_TEAR_DOWN(grid) {}

TEST(grid, first_ctrl_point)
{
  s16 result = pwa_interp(&dom1_desc, dom1_desc.min_d);
                
  TEST_ASSERT_EQUAL(dom1_tab[0], result);
}

TEST(grid, second_ctrl_point)
{
  s16 result = pwa_interp(&dom1_desc, dom1_desc.min_d + 1*step);
                
  TEST_ASSERT_EQUAL(dom1_tab[1], result);
}

TEST(grid, last_ctrl_point)
{
  s16 result = pwa_interp(&dom1_desc, dom1_desc.min_d + dom1_desc.n_fn * step);
                
  TEST_ASSERT_EQUAL(dom1_tab[dom1_desc.n_fn], result);
}

/******************************************************************************/
TEST_GROUP(domain);

TEST_SETUP(domain) {}

TEST_TEAR_DOWN(domain) {}

TEST(domain, ood_below)
{
  s16 result = pwa_interp(&dom1_desc, S16_MIN);
                
  TEST_ASSERT_EQUAL(dom1_tab[0], result);
}

TEST(domain, ood_above)
{
  s16 result = pwa_interp(&dom1_desc, S16_MAX);
                
  TEST_ASSERT_EQUAL(dom1_tab[dom1_desc.n_fn], result);
}
