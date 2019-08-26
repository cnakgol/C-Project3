This program solves f(x)=0 by 3 different methods: bisection method, secant method and a hybrid of both.
***To run the program, you should open the command line from your search button. 
It is better you change the direction to the program file.
Ex: This is written on your cmd:  C:\Users\Ceyda>
You should write cd and then write the file name containing the program: cd C:\Users\Ceyda\Desktop\CeydaNurAkgol
***After changing the location, you should call the program with the .exe version and enter the inputs.
***n+4 inputs are required: lower initial guess, higher initial guess, tolerance value and 
the coefficients of f(x) from the highest to the lowest order.
***Between each input, one space is required.
Ex: C:\Users\Ceyda\Desktop\CeydaNurAkgol>source.exe 1.5 1.8 0.001 2 2 -7 1 -7
1.5 is lower guess and 1.8 is higher guess. 0.001 is the tolerance value. f(x)=2x^4+2x^3-7x^2+x-7
The result is as follows: The bisection method converges to 1.66992 in 8 steps.
The secant method converges to 1.66941 in 4 steps.
The hybrid method converges to 1.66934 in 4 steps.

*The solution of each method is given with the number of iteration in each step.
*The converges condition for secant method is set by difference between the new step value and the old step value per the old step value 
as suggested.
*When the signs of the function values of initial guesses are the same, bisection method is terminated by giving the warning 
"The signs of functions values of the initial guesses are the same."
*When the number of iterations for each method exceeds 15, the program is terminated by giving the warning 
"The number of iterations exceeded the threshold."