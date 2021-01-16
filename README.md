# :mushroom: Fungal UI
### A simple terminal UI framework

<p align="center">
<img src="https://i.imgur.com/So3aaF3.gif" width="75%">
</p>

---

## :grey_question: About

Fungal UI is a simple library, made mostly for fun, to create UIs in console-based C++ applications.

Much like VIM, you can launch a Fungal UI program from the terminal and return to the original console buffer after exiting.

Nothing fancy, but one could reasonably extend the project to handle both mouse events and 2D control positioning -- the reason I haven't is that such features seemed outside the scope of the simple UI library I wanted to make but I might revisit at a later date and build upon it further.

### Key bindings

Navigation between controls is performed with the **Arrow up-down keys** and the **Tab key**, navigation within a control is performed with the **Arrow left-right keys**, and controls are drawn vertically, in a list-like fashion.

**Escape** allows you to go back to whichever control was displayed previously and if there are none, the program exits.

### Compatability
This library is compatible with windows projects using C++17 and above. Since there are only a few functions which are Windows-dependant, one could with some _minor_ trouble generalize it to work for Linux as well.

## :closed_book: Wiki
* [Getting started](https://github.com/userexit/Fungal-UI/wiki)
* [Basic usage](https://github.com/userexit/Fungal-UI/wiki/Basic-usage)
* [Standard controls](https://github.com/userexit/Fungal-UI/wiki/Standard-controls)
* [Internal structure](https://github.com/userexit/Fungal-UI/wiki/Internal-structure)
* [Creating custom controls](https://github.com/userexit/Fungal-UI/wiki/Creating-custom-controls)

## :test_tube: Building

Use the included CMake files and build as normal.

## :x: Known issues

* [ ] Resizing the Window causes all kinds of issues
* [ ] If a non-page control is taller than the console-window, it would go out of bounds. Should attempt to generalize the scrolling implementation in [page.cpp](https://github.com/userexit/Fungal-UI/blob/main/src/page.cpp)


## :toolbox: Example

<p align="center">
<img src="https://i.imgur.com/jQYTTnb.gif" width="75%">
</p>

## :trophy: Credit
CMake files generated from a Visual Studio project with [pavelliavonau/cmakeconverter](https://github.com/pavelliavonau/cmakeconverter).
