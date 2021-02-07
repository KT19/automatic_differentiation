# Implementation of Automatic Differentiation (C++)

## Brief introduction
Automatic differentiation is a method in which
the program automatically performs partial differentiation
of a given mathematical expression.

In a computer, some methods are existed to calculate differential value when a certain formula is given.
For example,
1. using numerical differentiation.
2. Actually differentiate by human hand and then write it in source code.
3. using automatic differentiation.

However, there are problems with 1 and 2.
Numerical differentiation of 1 is a method that uses the difference when the input is changed with a minute value, but
it is impossible to obtain an exact solution.
In the case of using the human-hand method of 2, it is difficult
to differentiate a complicated mathematical formula.

On the other hand, automatic differentiation is a method based on the chain rule of differentiation, and an exact solution can be obtained.
With automatic differentiation, even complicated mathematical expressions can be expressed by a combination of simple arithmetic operations, and the differential value can be obtained by applying the chain rule to it many times.

In this repository, c++ is used to implement automatic differentiation for simple arithmetic operations.
It only supports some combinations of arithmetic operations,
but it can be extended to other arithmetic operations or math functions by defining them in the same way.

## Contents
### forward
Implementation of forward mode automatic differentiation.
#### Advantage of forward mode.
Easy to implement. But when we want to find the derivative values for many variables, it takes a long calculation time in proportion to the number of variables.


### reverse
Implementation of reverse mode automatic differentiation.
#### Advantage of reverse mode.
Complex implementation. But even if we want to find the derivative values for many variables, the calculation time is not increased. Because, in reverse mode automatic differentiation, the calculation time is proportional to the number of output variables.

## How to compile?
This program is written in C++11.

In case of g++ (clang), the command is

```
g++ -std=c++11 main.cpp
```
Then for run,
```
./a.out
```
