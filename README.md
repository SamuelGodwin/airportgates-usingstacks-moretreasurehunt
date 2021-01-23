# Further C++ practice

For this assignment you will get more practice working with the basic building blocks of C++: vectors, functions, and classes.

Where you are to write functions, ensure you use constness and references where appropriate, to avoid needlessly copying objects, and to help ensure you have written correct code.

Note this coursework has a split deadline: an earlier deadline for the airport gates and stacks question; and a later deadline for 'treasure hunt, continued'.

# Calculating how many airport gates are needed [3 marks]

The arrival and departure times of planes at an airport can be defined by a pair of vectors:

- A vector `arrives` containing arrival times
- A vector `departs` containing departure times


We can represent the times as a whole number of minutes after midnight on monday, at the start of some week.  For instance:

- the time 7:17am on Monday this week would be recorded as `(7 * 60) + 17 = 437`
- 14:25 on Tuesday would be recorded as `(24 * 60 * 1) + (14 * 60) + 25`
- 14:25 on Tuesday in the following week would be recorded as `(24 * 60 * 8) + (14 * 60) + 25`

Plane `i` then arrives at time `arrives[i]` and departs at time `departs[i]`.  The number of gates an airport needs so that no plane needs to wait for a gate is equal to the maximum number of gates needed, over the time period covered by the given arrivals and departures

In the file `MaximumGates.h` implement a function `maximumGates` that takes:

- The arrives vector
- The departs vector

...and returns the maximum number of gates needed at the airport.  For instance, given the inputs: 

`arrives = {360, 400, 700}`  
`departs = {900, 515, 780}`  

...it should return 2.  Going through the day in chronological order:

* t=360: Plane 0 arrives: 1 gate now in use
* t=400: Plane 1 arrives: *2* gates now in use
* t=515: Plane 1 departs: 1 gate now in use
* t=700: Plane 2 arrives: *2* gates now in use
* t=780: Plane 2 departs: 1 gate now in use
* t=900: Plane 0 departs: 0 gates now in use


Conversely, if plane 2 had arrived *before* plane 1 had departed, e.g:

`arrives = {360, 400, 700}`  
`departs = {900, 720, 780}`  

...the maximum number of gates to return would be 3.

Notes:

- You can use the normal `std::vector` for this.
- You can assume `arrives` is sorted into ascending order
- One plane will never arrive at the exact same time another departs
- The maximum arrival/departure time might be quite big (e.g. for an arrival in several weeks' or months' time)

To test your implementation, use TestMaximumGates.cpp.  To compile to an executable `TestMaximumGates`:

`g++ -std=c++11 -o TestMaximumGates TestMaximumGates.cpp`  


# Using stacks [4 marks]

In `Stack.h`, implement a class `Stack` that is a Stack of `double`s.  You should implement this using the provided `pep::vector` class: Stack.h already contains the necessary `include` and `using` lines for this.

Your `Stack` class needs to provide three functions:

- `empty()` that returns true if the stack is empty
- `pop()` that removes and returns the top element off the stack
- `push()` that takes a double and pushes it onto the stack

Once you have written a Stack class, after it -- but still in `Stack.h` -- implement a function `evaluate` that takes a `string` containing a mathematical expression written in [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation), and returns the result of evaluating the expression, as a `double`.

In reverse polish notation (RPN), operators are written *after* rather than between what they act upon.  For instance:

`3.0 4.0 +`

...is the same as the usual (infix) notation `(3.0 + 4.0)`.  Or:

`3.0 4.0 + 2.0 *`

...is the same as `(3.0 + 4.0) * 2`.  The advantage of RPN is that there is no need to worry about brackets and order of precedence.

To implement the `evaluate` function, use your Stack class.  RPN expressions can be evaluated by splitting the input string by spaces into tokens, and working through it one token at a time:
 
 * If the token is a `+`, pop two numbers a and b off the stack, and push (b + a) onto the stack
 * If the token is a `-`, pop two numbers a and b off the stack, and push (b - a) onto the stack
 * If the token is a `*`, pop two numbers a and b off the stack, and push (b * a) onto the stack
 * If the token is a `/`, pop two numbers a and b off the stack, and push (b / a) onto the stack
 * Otherwise, the token is a number: push it onto the stack
 
 After going through all the tokens, the answer is then on the top of the stack: return it.
 
 To test your code, compile and run `TestStack.cpp`.  This will to evaluate three expressions, and check they give the right answer.
 
Notes:

- `std::stod(s)` will convert the string `s` into a double, and return its value

# Treasure hunt, continued [3 marks]

This is the advanced part of this assignment -- note it has a later deadline than the earlier parts.

*For this part, first, copy across your Item.h file from assignment 1, over the (basically empty) file provided.*

## A map of items

In MapOfItems.h, make a class `MapOfItems`. It needs to have:

- a private member variable that stores a vector of `Item`s
- a public function 'addItem' for adding an item to the end of this vector
- a public function 'size()' for returning the size of this vector

You can use the normal `std::vector` for this.

## Taking a tour of the Map

For this part of the assignment, you will implement a greedy algorithm that finds an order in which to visit the Items, allowing for a walking speed between them, and during the times at which they are available (i.e. from a given number of seconds past the hour, until 15 minutes after).

It should be in a class function called `getTour`, implemented within the MapOfItems class.  It should take a walking speed as an argument.  The tour should take no longer than 3600 seconds; that is, the last item you visit, must be visited before 3600.  It should return the tour as a `vector` of `Item`s.

The algorithm specification is as follows:

- The tour must finish before time 3600.
- The tour must start at the Item that is available first, at the time it becomes available.  For instance, if there are five items on the map, available from times 3,10,14,16,18, the item at time 3 would be visited first, at time 3.  (That is, the current time is 3.)
- Then, repeatedly:
  - For each Item *I* that hasn't been visited yet, 
    - Calculate the time that it would take to walk from the previous Item visited, to *I* (using the distance between them, and the walking speed).  This time, plus the current time, is the time that *I* would be visited -- if we went there next.  This time is denoted *visit(I)*.
    - If *visit(I)* is too late (more than fifteen minutes after the item appears), we can't visit that Item
    - If it's too early (before the time at which the item appears), we would need to wait at *I* until it appeared.  This is okay. but we would set *visit(I)* to the time at which *I* appears.
  - The next item to visit is then the one with the smallest *visit(I)*: add this to the tour, and set the current time to *visit(I)*..
  - Or, if we are too late for all the remaining Items, the tour has finished.  (Yes, it might not be able to visit all the items.)
- The function then returns the tour


To test your implementation, use MapOfItemsTest.cpp.
