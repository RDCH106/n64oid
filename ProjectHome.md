N64 emulator for the Android platform which will primarily target the Motorola Droid, and other Android devices with hardware 3D acceleration. Will primary use Mupen64Plus as codebase. Will require extensive rewrites of Mupen64Plus to support Android platform.

### What has been done: ###
-**Ported core to Android platform with interpreted CPU (no dynarec yet)**


&lt;BR&gt;

-**Ported RSP HLE plugin and main program to Android**


&lt;BR&gt;

-**Ported SDL to Android platform**


&lt;BR&gt;

-**Compiled SDL input plugin for Android**


&lt;BR&gt;

-**Compiled SDL audio plugin for Android**


&lt;BR&gt;

-**Compiled rice video plugin for Android**

### Current challenges: ###
-**Porting video module to Android platform (ex rice video plugin)**


&lt;BR&gt;

-**Remove any SDL joystick code from input plugin, fix segfault issue**


&lt;BR&gt;

-**Write Android video driver for SDL which sets up OpenGL (fbcon doesn't support OpenGL)**