// 
// Basic Easing functions
// https://github.com/gcsalzburg
// © George Cave 2020
//

#include "Arduino.h"
#include "Ease.h"

Ease::Ease(){}

Ease::Ease(ease_type type) :
   _ease_type(type)
{
   _set_param_defaults();  
}

Ease::Ease(ease_type type, double param) :
	_ease_type(type),
	_param(param)
{}


void Ease::set_type(ease_type type){
   _ease_type = type;
   _set_param_defaults();
}
void Ease::set_type(ease_type type, double param){
   _ease_type = type;
   _param = param;
}

uint8_t Ease::y(uint8_t x){
   return y((double)x/256)*256;
}
int16_t Ease::yOver(uint8_t x){
   return y((double)x/256)*256;
}

double Ease::y(double x){

   // Clamp between 0 and 1 (inclusive)
   if(x <= 0){
      return 0;
   }else if(x >= 1){
      return 1;
   }

   switch(_ease_type){
      case LINEAR:
         return x;
         break;
      case QUADRATIC_IN:
         return _xtic_in(x,2);
         break;
      case QUADRATIC_OUT:
         return _xtic_out(x,2);
         break;
      case QUADRATIC_INOUT:
         return _xtic_inout(x,2);
         break;
      case CUBIC_IN:
         return _xtic_in(x,3);
         break;
      case CUBIC_OUT:
         return _xtic_out(x,3);
         break;
      case CUBIC_INOUT:
         return _xtic_inout(x,3);
         break;
      case QUARTIC_IN:
         return _xtic_in(x,4);
         break;
      case QUARTIC_OUT:
         return _xtic_out(x,4);
         break;
      case QUARTIC_INOUT:
         return _xtic_inout(x,4);
         break;
      case QUINTIC_IN:
         return _xtic_in(x,5);
         break;
      case QUINTIC_OUT:
         return _xtic_out(x,5);
         break;
      case QUINTIC_INOUT:
         return _xtic_inout(x,5);
         break;
      case XTIC_IN:
         return _xtic_in(x,_param);
         break;
      case XTIC_OUT:
         return _xtic_out(x,_param);
         break;
      case XTIC_INOUT:
         return _xtic_inout(x,_param);
         break;
      case ELASTIC_IN:
         return _elastic_in(x,_param);
         break;
      case ELASTIC_OUT:
         return _elastic_out(x,_param);
         break;
      case ELASTIC_INOUT:
         return _elastic_inout(x,_param);
         break;
      case EXP_IN_BASIC:
         return _exp_in_basic(x);
         break;
      case EXP_OUT_BASIC:
         return _exp_out_basic(x);
         break;
      case EXP_IN:
         return _exp_in(x,_param);
         break;
      case EXP_OUT:
         return _exp_out(x,_param);
         break;
      case BOUNCE_IN:
         return _bounce_in(x);
         break;
      case BOUNCE_OUT:
         return _bounce_out(x);
         break;
      case BREATHE:
         return _breathe(x);
         break;
      default:
         return x; // Default is to return a linear response
    }
}

void Ease::_set_param_defaults(){
   switch(_ease_type){
      case XTIC_IN:
         _param = 2;
         break;
      case XTIC_OUT:
         _param = 2;
         break;
      case XTIC_INOUT:
         _param = 2;
         break;
      case ELASTIC_IN:
         _param = 20;
         break;
      case ELASTIC_OUT:
         _param = 20;
         break;
      case ELASTIC_INOUT:
         _param = 20;
         break;
      case EXP_IN:
         _param = 20;
         break;
      case EXP_OUT:
         _param = 20;
         break;
      default:
         _param = 1;
    }
}



double Ease::_xtic_in(double x, uint8_t power){
    return pow(x, power);
}
double Ease::_xtic_out(double x, uint8_t power){
    return 1 - pow(1-x, power);
}
double Ease::_xtic_inout(double x, uint8_t power){
    if(x < 0.5){
        return 0.5*_xtic_in(2*x, power);
    }else{
        return 0.5*(_xtic_out((2*x) - 1, power)+1);
    }
}

double Ease::_elastic_in(double x, double q){
    return (1/q) * ((1/(1-x))-1) * sin(q*(1-x));
}
double Ease::_elastic_out(double x, double q){
    return (((1/q)-(1/(q*x))) * sin(q*x)) + 1;
}
double Ease::_elastic_inout(double x, double q){
    if(x < 0.5){
        return 0.5*_elastic_in(2*x,q);
    }else{
        return 0.5*(_elastic_out((2*x) - 1,q) + 1);
    }
}

// Penner log/exp functions
double Ease::_exp_in_basic(double x){
	return pow(2,10*(x-1));
}
double Ease::_exp_out_basic(double x){
	return 1-pow(2,-10*x);
}

// CAVE designed log/exp functions
double Ease::_exp_in(double x, double q){
    // y = (((b+1)^y)-1)/b
    return (pow(q+1,x)-1)/q;
}
double Ease::_exp_out(double x, double q){

    // First principles
    // log(x)n = log(y)n / log(y)x

    // log(scale+1)[input*scale + 1]
    return log(double(x*q) + 1) / log(q+1);
}

// Bounce functions
double Ease::_bounce_in(double x){
	return 1- _bounce_out(1-x);
}
double Ease::_bounce_out(double x){
	// Use abs(x) so we can pass in (1-x) from bounce_in function
    if(abs(x) < (1/2.75)){

        return 7.5625 * pow(x,2);

    }else if(abs(x) < (2/2.75)){

        return (7.5625 * pow(x - (1.5/2.75),2)) + ((double)3/4);

    }else if(abs(x) < (2.5/2.75)){

        return (7.5625 * pow(x - (2.25/2.75),2)) + ((double)15/16);

	}else{

        return (7.5625 * pow(x - (2.625/2.75),2)) + ((double)63/64);

	}
}

double Ease::_breathe(double x){
	return exp(sin(2*PI*(x-0.25))-1);
}