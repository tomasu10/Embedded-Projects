

//Part of your documentation should be listing the valid inputs and outputs for the functions you create.
int math(int num1, int num2, char Operator){
	if(Operator == '+'){
		return num1 + num2;
	}
	else if(Operator == '-'){
		return num1 - num2;
	}
	else if(Operator == '*'){
		return num1 * num2;
	}
	else if(Operator == '/'){
		return num1 / num2;
	}
	else if(Operator == '%'){
		return num1 % num2;
	}
	else{
		return -1;
	}	
}
 /* MATH_H_ */