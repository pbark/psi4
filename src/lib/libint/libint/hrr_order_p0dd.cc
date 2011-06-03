#include <stdio.h>
#include <string.h>
#include "libint.h"
#include "hrr_header.h"

extern void vrr_order_p0dd(Libint_t*, prim_data*);

  /* Computes quartets of (p0|dd) integrals */

REALTYPE *hrr_order_p0dd(Libint_t *Libint, int num_prim_comb)
{
 prim_data *Data = Libint->PrimQuartet;
 REALTYPE *int_stack = Libint->int_stack;
 int i;

 Libint->vrr_classes[1][2] = int_stack + 0;
 Libint->vrr_classes[1][3] = int_stack + 18;
 Libint->vrr_classes[1][4] = int_stack + 48;
 memset(int_stack,0,93*sizeof(REALTYPE));

 Libint->vrr_stack = int_stack + 93;
 for(i=0;i<num_prim_comb;i++) {
   vrr_order_p0dd(Libint, Data);
   Data++;
 }
 /*--- compute (p0|dp) ---*/
 hrr3_build_dp(Libint->CD,int_stack+93,int_stack+18,int_stack+0,3);
 /*--- compute (p0|fp) ---*/
 hrr3_build_fp(Libint->CD,int_stack+147,int_stack+48,int_stack+18,3);
 /*--- compute (p0|dd) ---*/
 hrr3_build_dd(Libint->CD,int_stack+237,int_stack+147,int_stack+93,3);
 return int_stack+237;}