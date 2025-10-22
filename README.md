
## Vector Calculator

This program is called the Vector Calculator. It has a MATLAB-like user interface where the user may create vector to their desire and perform numerous operations on them. It also has vector-specific operations like cross product and dot product. The ability to save and load lists of vectors is available. The program has many input limitations, but is efficient nonetheless. 

The program utilizes dynamic memory, in which the storage size for vectors increases as the user continuously adds vectors to memory. A series of malloc()'s are used to prevent stack smashing, and free() is used to prevent memory leaks.

To build the program, make sure all the necessary files exist in the working directory, and issue the command "**make**". You can also run "**gcc -o main main.c vector.c**" and add any additional flags.

Once the program has been built, issue "./main" to run the Vector Calculator. Below is a list of supported functions. 
- Assignment: Vector = Scalar Scalar
- Addition: Vector + Vector (with assignment functionality)
- Subtraction: Vector - Vector (with assignment functionality)
- Scalar Multiplication: Vector * Scalar (communitive with assignment functionality)
- Dot Product: Vector . Vector
- Cross Product: Vector X Vector (with assignment functionality)
- Save Vector Array: save directory.csv
- Load Vector Array: load directory.csv

Misc. Commands:
- list: Lists the vectors stored in memory.
- clear: Clears the memory of vectors and reduces the memory size.
- help: Provides a brief overview of the Vector Calculator.

Warnings: 
Make sure to include spaces in between **each** argument, even after the last one.
Any assignment operation stores the vector in memory.
When using load/save, put .csv at the end of the directory. **Only .csv files are supported.**
