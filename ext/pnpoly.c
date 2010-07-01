// pnpoly.c
// (c) 2010 Matt Griffith
// 
// A native Ruby extension for determining if a point is in a polygon. 
// 
// (The MIT License)
// 
// Copyright (c) 2010 Matt Griffith, AgriSmart Information Systems, LLC
// 
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// 'Software'), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// --------------------------------------------------------
// The pnpoly function is covered by the following license. 
// For more inforation see: 
// http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
//
// Copyright (c) 1970-2003, Wm. Randolph Franklin
// 
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimers.
// Redistributions in binary form must reproduce the above copyright
// notice in the documentation and/or other materials provided with the
// distribution. The name of W. Randolph Franklin may not be used to
// endorse or promote products derived from this Software without
// specific prior written permission. THE SOFTWARE IS PROVIDED "AS IS",
// WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

#include "ruby.h"
#include "pnpoly.h"

static int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy)
{
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if (  ((verty[i]>testy) != (verty[j]>testy)) && 
          (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
       c = !c;
  }
  return c;
}

VALUE point_in_poly(VALUE self, VALUE rb_x, VALUE rb_y, VALUE rb_points) {
  Check_Type(rb_x, T_FLOAT);
  Check_Type(rb_y, T_FLOAT);
  Check_Type(rb_points, T_ARRAY);
  
  int i = 0;
  int s = RARRAY(rb_points)->len;
  float *vertx;
  float *verty;
  
  vertx = calloc(s, sizeof(float));
  verty = calloc(s, sizeof(float));
  
  float test_x = RFLOAT(rb_x)->value;
  float test_y = RFLOAT(rb_y)->value;
  
  ID i_x = rb_intern("x");
  ID i_y = rb_intern("y");
  
  for(i = 0; i < s; i++) {
    VALUE point = RARRAY_PTR(rb_points)[i];
    VALUE x = rb_funcall(point, i_x, 0);
    VALUE y = rb_funcall(point, i_y, 0);
    Check_Type(x, T_FLOAT);
    Check_Type(y, T_FLOAT);
    vertx[i] = RFLOAT(x)->value;
    verty[i] = RFLOAT(y)->value;
  }
  
  return pnpoly(s, vertx, verty, test_x, test_y);
}

// end