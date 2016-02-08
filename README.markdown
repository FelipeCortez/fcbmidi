I got a Behringer FCB1010 and was a bit frustrated on how time-consuming it is to program the thing using the footswitches and the lack of momentary control change support (unless you get an UnO). It's, however, a nice piece of hardware so I set all footswitches to note MIDI messages and made this program to convert these messages to appropriate control change ones that can be switched between latch, momentary and an alternative mode with software only. Uses SFML for the GUI and RtMIDI. Compiled for OS X.

As of now, there's an issue with the way I put the dylib in the Xcode project that prevents it from running on other machines. Hopefully I'll fix it soon.

![FCB1010+](app.png?raw=true)