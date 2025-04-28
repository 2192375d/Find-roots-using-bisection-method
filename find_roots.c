#include <stdio.h>
#include <stdlib.h>

double absolute_value(double x){
  /*
   * Takes input x, returns |x|
  */
  return x > 0.0 ? x : -x;
}

double polynomial(double coefficients[], const int NUM_COEFFICIENTS, double x){
/*
 * Purpose:
 * Calculate the result of a polynomial function P(x), given input x
 * 
 * Parameters:
 *    double coefficients[]:
 *        a double array holding each of the coefficients of P(x). 
 *        For P(x) = a_0 + a_1 x + a_2 x^2 + ... + a_n x^n, the array will be
 *        coefficients[n + 1] = {a_0, a_1, a_2, ..., a_n}
 *        
 *        ex: For P(x) = 3 + 2x + x^2, the array wil be
 *        coefficeints[3] = {3, 2, 1}
 *    int NUM_COEFFICIENTS:
 *        The number of coefficients in the coefficients[] array, in other words,
 *        NUM_COEFFICIENTS = deg(P(x)) + 1
 *    double x:
 *        Input into the P(x)
 * 
 * Returns:
 * The function returns a double equal to P(x) from the given input x
*/
  double sum = 0.0;

  for(int i = 0; i < NUM_COEFFICIENTS; i++){
    double product = 1;

    for(int j = 0; j < i; j++){
      product *= x;
    }

    // printf("The i'th product is: %f\n", product);

    sum += coefficients[i] * product;
  }

  return sum;
}

double bisection_method(double coefficients[], int NUM_COEFFICIENTS, double a, double b, double accuracy){
  double between;
  between = polynomial(coefficients, NUM_COEFFICIENTS, (a + b) / 2);


  if(absolute_value(between) < accuracy){
    return (a + b) / 2;
  }

  if((polynomial(coefficients, NUM_COEFFICIENTS, a) > 0 && polynomial(coefficients, NUM_COEFFICIENTS, b) > 0)||
     (polynomial(coefficients, NUM_COEFFICIENTS, a) < 0 && polynomial(coefficients, NUM_COEFFICIENTS, b) < 0)){
    printf("does not work\n");
    return (a + b) / 2;
  }

  if(between > 0.0){
    return bisection_method(coefficients, NUM_COEFFICIENTS, (a + b) / 2, b, accuracy);
  }
  else{
    return bisection_method(coefficients, NUM_COEFFICIENTS, a, (a + b) / 2, accuracy);
  }
}

void find_roots(double MIN, double MAX, 
                double interval, 
                double coefficients[], 
                int NUM_COEF,
                double accuracy,
                double roots[],
                int *num_root){

  double current_value;
  double next_value;

  int count = 0;
  // printf("*numroot: %d\n", *num_root);

  for(double i = MIN; i < MAX - interval; i += interval){
    current_value = polynomial(coefficients, NUM_COEF, i);
    next_value = polynomial(coefficients, NUM_COEF, i + interval);
    // printf("current value: %f, next value: %f\n", current_value, next_value);
    // if(absolute_value(i + 3.0) < accuracy){
    //   printf("current value: %f\n", current_value);
    // }
    if((current_value < 0 && next_value > 0) || (current_value > 0 && next_value < 0)){
      if(absolute_value(current_value) < accuracy){
        roots[count] = i;
        (count) += 1;
      }
      else if(absolute_value(next_value) < accuracy){
        roots[count] = i + interval;
        (count) += 1;
      }
      else{
        roots[count] = bisection_method(coefficients, NUM_COEF, i, i + interval, accuracy);
        (count) += 1;
      }
    }
  }

  *num_root = count;
}

int main(){
  double coefficients[9] = {0, 216, 324, 18, -145, -50, 12, 8, 1};
  double roots[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int num_root = 0;

  find_roots(-10.0, 10.0, 0.1, coefficients, 9, 0.01, roots, &num_root);

  for(int i = 0; i < num_root; i++){
    printf("root %d: %f\n", i, roots[i]);
  }
}
