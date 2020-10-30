# EasyToP
This application is an interactive parallelizing assitance tool.

* It's easy to parallelize.

We have a plan to implement the folowing capabilisies,

1. EasyToP Analyzer: Parallism analysis for OpenMP and OpenACC,
2. EasyToP Directive Creator: OpenMP or OpenACC directive creation,
3. EasyToP Optimizer: Program restructureing(is not refactoring),
4. EasyToP Measure: Execution time analysis.

These capabilitites are going to use functionalities of Clang/LLVM.

Above capabilities are running with major IDE or text editor using LSP(Language Server Protocol)

This framework is inteded the following rules,

1. EazyToP provides the result of paralelliam analysis and Execuition time analysis,
2. Editing program and decesion making of parallelize is user's(programmer's) role. In other word, EasyToP cannnot edit the program, except inserting OpenMP or OpenACC directive.

These rules are promoted maintain of human-readbility for source code. 

Let's enjoy parallelization life!!
