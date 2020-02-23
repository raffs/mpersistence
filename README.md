# Multiplicative Persistence Overview

According to wikipedia the persistence of a number is:

> The number of times one must apply a given operation to an integer
> before reaching a fixed point at which the operation no longer alters the number.
> The persistence of a number is undefined if a fixed point is never reached.

For multiplicative persistence we multiply every digit of a given integer, until
you reach a point where the number is `> 10` where you no longer can multiply the digits

## Problem

In a discussion with some coleagues, [@hcassus](https://github.com/hcassus) proposed that we
implemented an algorithm to find the smallest multiplicactive persistence of the numbers from 1..`inf`.

The final goal was not only to implement the algorithm, but it was optmize that time
that the algorithm find the smallest number that has a multiplicative persistence of `11`.

## Design Decision

All of the optmization implemented on the algorithm was based on the mathematical optimization

All the hard work implemneted on this algorithm, which is the mathematical work and observation
of the following:

 * [David A. Corneth](http://oeis.org/wiki/User:David_A._Corneth)
 * [Kohei Sakai](http://oeis.org/wiki/User:Kohei_Sakai)
 * [Benjamin Chaffin](http://oeis.org/wiki/User:Benjamin_Chaffin)
 * _et all_

You can find the optmization at [The on-line encryclopedia of integer sequences](http://oeis.org/A003001).

## Last recorded output

Running the algorithm in Virtual Machine using the VirtualBox technology, with the specs:

* Virtual Machine:
  * Archlinux Distribution
  * 2 vCPU
  * 8 Gib of Memory
* The underlying hardware running the virtual machine contains:
  * Processor: 2,7 GHz Quad-Core Intel Core i7
  * Memory:    16 GB 2133 MHz LPDDR3

```sh
$ ./mpersistence
Minimum number of persistency 0 is 0 calculated in  0.000036s
Minimum number of persistency 1 is 10 calculated in  0.000088s
Minimum number of persistency 2 is 25 calculated in  0.000096s
Minimum number of persistency 3 is 39 calculated in  0.000103s
Minimum number of persistency 4 is 77 calculated in  0.000110s
Minimum number of persistency 5 is 679 calculated in  0.000122s
Minimum number of persistency 6 is 6788 calculated in  0.000145s
Minimum number of persistency 7 is 68889 calculated in  0.000194s
Minimum number of persistency 8 is 2677889 calculated in  0.000301s
Minimum number of persistency 9 is 26888999 calculated in  0.000589s
Minimum number of persistency 10 is 3778888999 calculated in  0.002118s
Minimum number of persistency 11 is 277777788888899 calculated in  0.014940s
```

## References

* [Wikipedia: Persistence of a Number](https://en.wikipedia.org/wiki/Persistence_of_a_number)
* [The on-line encryclopedia of integer sequences](http://oeis.org/A003001)
