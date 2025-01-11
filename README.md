# `dots`

This repository contains drivers for an sd card module and an 8x8 matrix display, along with some application code to work with them.

The goal is to fetch 'images' that have 64 pixels in them (hence the air quotes) from the sd card and then display them (in off and on) on the matrix display. You can switch between the
images using a rotary encoder.

It is expected that proper project structure, logging, testing, and embedded software best practices will be upheld to the best of my ability.

Note that this is only for learning purposes, do not use anything here in production.

## Running

It should be as simple as:

```bash
$ idf.py flash
```
