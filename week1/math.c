double power(double base, int exp) {
   double result = 1.0;
  
   // Check if the exponent is negative
   int is_negative = 0;
   if (exp < 0) {
       is_negative = 1;
       exp = -exp; // Convert to positive for the loop
   }


   // Multiply the base 'exp' times
   for (int i = 0; i < exp; i++) {
       result *= base;
   }


   // If original exponent was negative, invert the result
   if (is_negative) {
       return 1.0 / result;
   }


   return result;
}
