# Narwhal (WIP)
Narwhal is basically a frontend for the Unicorn Framework. The idea is to have a visual way to build up embedded systems in software to aid in reverse engineering.

## The End Goal
My lofty goal for Narwhal is to have a full GUI based lab for defining a small embedded system in software. 

For example, if I have code for an ARM SoC that is completely undocumented, then I have to guess at a lot of how the internals work. I think it'd be easier to understand what's going on if I could not only simulate the code, but also emulate non-standard peripherals so execution can continue. In doing so, I might discover something about the SoC outside of the processing core.

I want this to be done through scripting callbacks so as to simulate DMA. If the software writes to a reigon of memory you have defined a software peripheral for, your code will get called and it will be able to do whatever it needs to.

## Why a GUI?
Doing this with a GUI might help in visually understanding what's going on. There are a lot of things that I can understand graphically far better than with text.

## Current Progress
Narwhal is under infrequent development. I had the idea, I started writing it, but I will likely lose steam on it once I get basic ARM functionality down (since for my current project that's all I need). Still, I want to make it extendable to all other archetectures that Unicorn supports. Contributions are _very_ welcome.

## Building
To build Narwhal, you need a C++ compiler, `make`, Unicorn, and SDL and OpenGL (these can be substituted for any backend ImGUI supports). Simply running `make` will build the binary (on linux, at least).

## To Do (in order of my personal priority)
 - Finish basic graphical ARM execution
 - Graphical memory mapping
 - Loading binaries from file
 - Defining peripherals in some sort of scripting language (python?)
 - Organize the code better, because yikes
 - Refine the UI
 - Begin implementing "CPU Windows" for architectures other than ARM

## Feature Requests?
I am ignorant to what real, non-hobbyist reverse engineers need their tools to do. I'm writing this for the things I need it to do, but that might just be a small sliver of what real professionals need their software to do. As such, you can ask me to add stuff, but in general I'd much rather merge in pull requests. It's less work. 😁

## License
GNU General Public License v3.0

## Used Libraries
 - [SDL](https://www.libsdl.org/)
 - [Unicorn Framework](https://github.com/unicorn-engine/unicorn)
 - [Dear ImGUI](https://github.com/ocornut/imgui)