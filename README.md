Variable Operations
set <variable> <value>: Sets the variable to the given value. Supports integers only

add <var1> <var2> <result>: Adds the values of var1 and var2, storing the result in result.

subtract <var1> <var2> <result>: Subtracts var2 from var1, storing the result in result.

random <variable> <max_value>: Generates a random integer between 1 and max_value, storing it in the given variable.

Printing
print <variable>: Prints the value of the given variable to the console.

Loops
loop <iterations>: Repeats a set of commands a specified number of times. Ends with end.

Conditionals
while <variable> <value>: Executes a set of commands while the variable is not equal to the given value. Ends with end. Supports an optional else block for commands to execute if the condition is initially false.

Functions
def <function_name>: Defines a function with the given name. Ends with end.

<function_name>: Calls the specified function.

Program Saving
exit: Prompts to save the session's code to H#project.txt on the desktop and exits the interpreter.
NOTE: you NEED to have a file named H#project.txt on your desktop.
