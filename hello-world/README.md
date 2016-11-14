#Working with kernel 4+

```
  $ make
  $ sudo su 
  $ insmod hello.ko 
  $ dmesg | tail -1 
  $ rmmod hello.ke 
  $ dmesg | tail -1 
```

#Working with kernel 2.6

``` 
  $ make
  $ sudo su
  $ insmod ./hello.ko
  $ rmmod ./hello.ko
