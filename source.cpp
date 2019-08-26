#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

float sign(float x, float precision){
	if(x>precision) return 1;//if a number is greater than the precision, i.e. greater than almost 0, return 1 which signifies it's positive
	else if(x<-precision) return -1;//if a number is smaller than the precision, i.e. smaller than almost 0, return -1 which signifies it's negative
	else return 0;//for all the other cases, the number is almost 0
}//finds the sign of a number

float midpoint(float a, float b){
	return a+(b-a)/2;
}//finds the midpoint of two numbers

class function{
	public:
		float *coef;//creates an array to hold the coefficients of a function
		int order;//creates a number to hold the order of a function
		function(){order=0;}//creates a default constructor
		function(int,char**);//creates a constructor
		float findValue(float);//finds the value of the function for a given number, i.e. f(x)
		float bisection(float, float, float, int*);//solves the function, i.e. f(x)=0, by bisection method
		float secant(float, float, float, int*);//solves the function, i.e. f(x)=0, by secant method
		float hybrid(float, float, float, int*);//solves the function, i.e. f(x)=0, by hybrid method: bisection method for 2 iterations and secant method for others
		~function(){delete coef;}//creates a destructor
};

function::function(int n, char** co){
	order=n-4;//sets the order according to inputs
	coef=new float[order];//creates a dynamically allocated memory of the order size
	for(int i=0; i<order; i++){
		coef[i]=atof(co[i+4]);//sets the coefficients according to inputs
	}
}

float function::findValue(float x){
	float value=0;
	for(int i=0; i<order; i++){
		value+=coef[i]*pow(x,order-i-1);
	}//finds the value of a function by multiplying its corresponding power with its corresponding coefficient and summing them up
	return value;//returns this value
}

float function::bisection(float LIV, float HIV, float tol, int* iteration){
	float mid;//creates a variable to hold the midpoint
	iteration[0]=0;//holds the iteration number
	if(sign(findValue(LIV),tol)==sign(findValue(HIV),tol)){
		cout << "The signs of the functions values of the initial guesses are the same." << endl;
		return 0;
	}//exists if the signs of the functions values of the initial guesses are the same
	while(fabs(HIV-LIV)>tol){//convergence condition
		iteration[0]++;//counts the iterations
		if(iteration[0]>15){
			cout << "The number of iteration exceeded the threshold." << endl;
			return 0;
		}//if the iterations exceeds the threshold, exits the function with a warning and exits
		mid=midpoint(LIV,HIV);//finds the midpoint
		if(fabs(sign(findValue(LIV),tol)-sign(findValue(mid),tol))<tol){
			LIV=mid;
		}//if the signs of the function values of the lower value and the midpoint, assigns the midpoint to the new lower value
		else HIV=mid;//if not, assigns the midpoint to the new higher value
	}
	return mid;//returns the root, i.e. the point where the function changes sign
}

float function::secant(float LIV, float HIV, float tol, int* iteration){
	float mid;//creates a variable to keep the root
	iteration[1]=0;//holds the iteration number
	while(fabs((HIV-LIV)/LIV)>tol){
		iteration[1]++;//counts the iterations
		if(iteration[1]>15){
			cout << "The number of iteration exceeded the threshold." << endl;
			return 0;
		}//if the iterations exceeds the threshold, exits the function with a warning
		mid=HIV-findValue(HIV)*(HIV-LIV)/(findValue(HIV)-findValue(LIV));//approximates the function by the secant line through previous two iterates and finds the point which intersects the x axis
		LIV=HIV;//sets new lower point as old higher point
		HIV=mid;//sets new higher point as the root
	}
	return mid;//returns the root, i.e. the point where the secant line intersects the x axis
}

float function::hybrid(float LIV, float HIV, float tol, int* iteration){
	float mid;//creates a variable to keep the root
	iteration[2]=0;//holds the iteration number
	for(int i=0; i<2; i++){//iterates twice the bisection method
		if(sign(findValue(LIV),tol)==sign(findValue(HIV),tol)){
		break;
		}//exists the bisection part if the signs of the functions values of the initial guesses are the same
		if(iteration[0]>15){
			cout << "The number of iteration exceeded the threshold." << endl;
			return 0;
		}//if the iterations exceeds the threshold, exits the function with a warning
		iteration[2]++;//counts the iterations
		mid=midpoint(LIV,HIV);//finds the midpoint
		if(fabs(sign(findValue(LIV),tol)-sign(findValue(mid),tol))<tol){
			LIV=mid;//if the signs of the function values of the lower value and the midpoint, assigns the midpoint to the new lower value
		}
		else HIV=mid;//if not, assigns the midpoint to the new higher value
	}
	
	while(fabs((HIV-LIV)/LIV)>tol){//applies the secant method for the rest iterations
		iteration[2]++;//counts the iterations
		if(iteration[2]>15){
			cout << "The number of iteration exceeded the threshold." << endl;
			return 0;
		}//if the iterations exceeds the threshold, exits the function with a warning
		mid=HIV-findValue(HIV)*(HIV-LIV)/(findValue(HIV)-findValue(LIV));//approximates the function by the secant line through previous two iterates and finds the point which intersects the x axis
		LIV=HIV;//sets new lower point as old higher point
		HIV=mid;//sets new higher point as the root
	}
	return mid;//returns the root, i.e. the point where the secant line intersects the x axis
}

int main(int argc, char** argv){
	float LIV=atof(argv[1]);//receives the first entry of the user's input as the lower initial guess
	float HIV=atof(argv[2]);//receives the second entry of the user's input as the higher initial guess
	float tolerance=atof(argv[3]);//receives the third entry of the user's input as the tolerance value
	function f(argc,argv);//creates the function class by using constructor
	
	
	int iteration[3];//creates an array to keep iteration numbers
	/*bisection method*/
	float result=f.bisection(LIV,HIV,tolerance,iteration);//applies bisection method
	if(iteration[0]<=15 && iteration[0]!=0){
		cout << "The bisection method converges to " << result << " in " << iteration[0] << " steps." << endl;
	}//prints the result if the iteration number didn't exceed the threshold
	/*secant method*/
	result=f.secant(LIV,HIV,tolerance,iteration);//applies secant method
	if(iteration[1]<=15){
		cout << "The secant method converges to " << result << " in " << iteration[1] << " steps." << endl;
	}//prints the result if the iteration number didn't exceed the threshold
	/*hybrid method*/
	result=f.hybrid(LIV,HIV,tolerance,iteration);//applies hybrid method
	if(iteration[2]<=15){
		cout << "The hybrid method converges to " << result << " in " << iteration[2] << " steps." << endl;
	}//prints the result if the iteration number didn't exceed the threshold
}
