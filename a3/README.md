# Description of files in this directory.

The files here are starter files for UVic SENG 265, Fall 2022,
Assignment #3. This is the third version of the concordance-generation
program.

* ```makefile```: Needed to build the assignment. In order to
construct the ```concord3``` executable, enter either ```make``` or
```make concord3```.

* ```concord3.c```: The C file containing the ```main()``` function.
(There must only exist one ```main``` in any program.)  This should be
suitably modified to complete the assignment.

* ```emalloc.[ch]```: Source code and header file for the
```emalloc``` function described in lecture. This is kept in its own
source-code file as it can be used independently in both
```concord3.c``` and ```seng265-list.c```.

* ```seng265-list.[ch]```: Linked-list routines based on the lectures. The
routines here may be added to or modified. Regardless, however,
students are responsible for any segmentation faults that occur as a
result of using this code.
