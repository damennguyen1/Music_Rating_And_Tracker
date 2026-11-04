# Music Rating and Tracker

COP 3003 team project.

Project Team Members: Sid Dcosta, Nate Haas, Damen Nguyen

## Synopsis

Music Rating and Tracker is a C++ program for people who want to keep track of the
music they listen to. Users enter songs, albums, and artists by hand, rate each one
from 1 to 10, and see their collection ranked. Nothing is streamed or pulled from
an online service, so everything in the library is something the user added.

The project is built around a small class hierarchy. `MusicItem` is an abstract base
class that holds a title and a rating and enforces the rating rules. `Song`, `Album`,
and `Artist` derive from it, and each one prints and describes itself differently.
The program works with all three through base-class pointers, so adding a new kind of
item later does not require changing the code that displays or ranks them. Invalid
input, such as a rating outside 1 to 10 or an empty title, is rejected with an
exception and leaves the library unchanged.

