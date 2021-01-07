# Fungal UI
### A lightweight UI framework for console-based applications

<p align="center">
<img src="https://i.imgur.com/CU2n2Ll.png" width="75%">
</p>

## About

Fungal UI is a simple library, made mostly for fun, to create UIs in console-based C++ applications.

Much like VIM, you can launch a Fungal UI program from the terminal and return to the original console buffer after exiting.

Navigation between controls is performed with the **Arrow up-down keys** and the **Tab key**, navigation within a control is performed with the **Arrow left-right keys**, and controls are drawn vertically, in a list-like fashion.

**Escape** allows you to go back to whichever control was displayed previously and if there are none, the program exits.

Nothing fancy, but one could reasonably extend the project to handle both mouse events and 2D control positioning -- the reason I haven't is that such features seemed outside the scope of the simple UI library I wanted to make but I might revisit at a later date and build upon it further.

## Wiki
* [Getting started](https://github.com/userexit/Fungal-UI/wiki)
* [Basic usage](https://github.com/userexit/Fungal-UI/wiki/Basic-usage)
* [Standard controls](https://github.com/userexit/Fungal-UI/wiki/Standard-controls)
* [Internal structure](https://github.com/userexit/Fungal-UI/wiki/Internal-structure)
* [Creating custom controls](https://github.com/userexit/Fungal-UI/wiki/Creating-custom-controls)

## Building

The project uses C++17 and has no external dependencies. At the moment it is only available for Windows but there are only a few functions in [ui.cpp](https://github.com/userexit/Fungal-UI/blob/main/src/ui.cpp) that depend on Windows that could with some _minor_ trouble be rewritten to work with Linux but I can't be arsed looking into the Linux API so.

## Known issues

* [ ] Resizing the Window causes all kinds of issues
* [ ] If a non-page control is taller than the console-window, it would go out of bounds. Should attempt to generalize the scrolling implementation in [page.cpp](https://github.com/userexit/Fungal-UI/blob/main/src/page.cpp)


## Example

<p align="center">
<img src="https://i.imgur.com/jQYTTnb.gif" width="75%">
</p>
