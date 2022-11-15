## CompilerParser
The Jack CompilerParser is intended take in a list of tokens which were generated from a file stream - it does not perform the tokenisation process.

The CompilerParser organises tokens into ParseTrees, applying/enforcing the grammar rules for Jack whilst generating a structure that represents the semantics of the input program.
It is intended that these semantics are later recreated by the code generator, which is not implemented in this practical task.
