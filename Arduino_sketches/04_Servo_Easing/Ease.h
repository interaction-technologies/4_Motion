// 
// Basic Easing functions
// https://github.com/gcsalzburg
// © George Cave 2020
//

#ifndef Ease_H_
#define Ease_H_

// Use one of these types to specify a different easing curves
// Graphs of easing curves: https://www.desmos.com/calculator/ctcmqijlpi
enum ease_type{
   LINEAR,

   QUADRATIC_IN, QUADRATIC_OUT, QUADRATIC_INOUT, 
   CUBIC_IN,     CUBIC_OUT,     CUBIC_INOUT, 
   QUARTIC_IN,   QUARTIC_OUT,   QUARTIC_INOUT,  
   QUINTIC_IN,   QUINTIC_OUT,   QUINTIC_INOUT,
   XTIC_IN,      XTIC_OUT,      XTIC_INOUT,

   ELASTIC_IN,   ELASTIC_OUT,   ELASTIC_INOUT,

   EXP_IN_BASIC, EXP_OUT_BASIC,
   EXP_IN,       EXP_OUT,
   BOUNCE_IN,    BOUNCE_OUT,

   BREATHE
};

class Ease{

   public:

      Ease();
      Ease(ease_type type);
      Ease(ease_type type, double param);

      void   set_type(ease_type type);
      void   set_type(ease_type type, double param);

      // Returns x value for a given y value
      double  y(double x);
      uint8_t y(uint8_t x);
      int16_t yOver(uint8_t x); // Will return value outside of uint8_t range if needed (0->255)

   protected:

      // Variables for the ease
      ease_type	_ease_type = LINEAR;
      double		_param = 1;

      // Sets _param if not set by initial call
      void   _set_param_defaults();

      // Private scaling functions
      double _xtic_in(double x, uint8_t power);
      double _xtic_out(double x, uint8_t power);
      double _xtic_inout(double x, uint8_t power);

      double _elastic_in(double x, double q);
      double _elastic_out(double x, double q);
      double _elastic_inout(double x, double q);

      double _exp_in_basic(double x);
      double _exp_out_basic(double x);
      double _exp_in(double x, double q);
      double _exp_out(double x, double q);

      double _bounce_in(double x);
      double _bounce_out(double x);

      double _step(double x, double q);
      double _breathe(double x);
};

#endif