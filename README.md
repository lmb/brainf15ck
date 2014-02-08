Brainf15ck - Interpreting Brainfuck in 15 minutes
===

This Brainfuck interpreter is part of an unconference talk given at EF 2014.
Feel free to modify in whatever way.

Building
---

```bash
gcc -Wall -pedantic brainf15ck.c -o brainf15ck
```

Clang works just as well.

Try it
---

There is a Hello World included, shamelessly stolen from [Wikipedia](http://en.wikipedia.org/wiki/Brainfuck#Hello_World.21). Run it with

```bash
./brainf15ck helloworld.bf
```

Bugs
---

`brainf15ck` does not check for over- / underflows of memory and program
buffers. Also, nested loops are not supported (thanks for reporting this
@rdebath!)This is left as an excercise to the reader :)