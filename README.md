# STM8S-time-base-using-SDCC
Timebase function using TIM1 overflow INT and multi-file project example

This is an example of inmplementing a time base for the STM8 with SDCC. It demonstrates a blocking Dleayms function, and a non blocking function. It also shows how a multiple file project can be built using multiple Makefiles.

To run, connect the STM8S103F board over a ST-LINK programmer SWIM port, modify the two Makefiles to suit your directory structure, and type

```
make flash
```

Please see [my companion blog post](http://aviatorahmet.blogspot.com/2018/09/stm8s-time-base-using-sdcc.html) for more details.

Also see my [blog post for setting up an environment for STM8](https://aviatorahmet.blogspot.com/2018/01/programming-stm8s-using-sdcc-and-gnu.html).

