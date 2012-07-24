#if !defined(_pnpoly_h_)
#define _pnpoly_h_

VALUE point_in_poly(VALUE self, VALUE rb_lat, VALUE rb_lon, VALUE rb_points);

#ifndef RUBY_19
#ifndef RARRAY_LEN
#define RARRAY_LEN(v) (RARRAY(v)-len)
#endif
#ifndef RARRAY_PTR
#define RARRAY_PTR(v) (RARRAY(v)-ptr)
#endif
#ifndef RFLOAT_VALUE
#define RFLOAT_VALUE(v) (RFLOAT(v)->value)
#endif
#endif

#endif // _pnpoly_h_
