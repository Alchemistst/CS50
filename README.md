# Questions

## What's `stdint.h`?

It's a header file which contains the necessary data structures for exact-width integers.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

As defined in stdint.h, those are special types of integers, special in the sense that their structure is fixed (ie, 8 bits, 32 bits without sign, etc.).

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 6, 6, 4, respectively.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x42 0x4D, corresponding to the letters BM.

## What's the difference between `bfSize` and `biSize`?

bfSize specifies the size of the entire file, whereas biSize defines the size of the BITMAPINFOHEADER structure. Both in bytes.

## What does it mean if `biHeight` is negative?

A negative biHeight means that the DIB starts from the top to the bottom, on the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Because the file couldn't be opened. Maybe it's impossible to open that file on read mode or the string provided didn't return a file pointer.

## Why is the third argument to `fread` always `1` in our code?

As we want to read the whole BITMAPFILEHEADER and BITMAPINFOHEADER, and because we define as the "amount we want to read" (second parameter)
as the size of each one of the structures, that 1 means that, instead of reading it byte by byte, it's going to read the whole of the structure
all at once.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

From where we are reading on the file (first argument), we move the cursor a specific offset (second argument) from where the cursor
is (third argument, other options available to set from where the offset starts).

## What is `SEEK_CUR`?

In the context of the fseek function, SEEK_CUR means that the offset will be applied from the last position we were reading the file.
