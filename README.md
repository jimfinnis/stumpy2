# Introduction
Stumpy is the second incarnation of a tree-based (really a 
directed-graph-based) visual programming
language, originally designed for generating geometric 3D moving
backgrounds (and later front-ends) for PS2 games way back in 2005(ish).
The user wires together various components, ultimately all connecting
into an output component. Each component generates data which can be
modified by the components it outputs into, or does something which
can be modified by inputs (*modulation*) or by other things between
it and the output (*state*).

As an example, consider a 3D system. Here, we might have a primitive
(such as a cube) going into a rotate box (a state change), which will
rotate everything which connects into it. This could be modulated
using a clock component, so the cube will spin. Other state changes,
anywhere between the primitive and the output could apply a texture or
an environment map, change colour, and so on.

## Applications
Stumpy - the language proper - is implemented as a Java client. This
synchronises with a server implementing the Stumpy application using
a simple protocol. This sends changes in the component graph and
parameters. There are currently two applications: a 3D rendering
app and a (rather better documented) generative music app.
These can be found in the **qtserver** and **music** directories
respectively. Each application has different dependencies which will
be discussed below.

The applications run only on Linux, but could be made to compile
on most things (notably qtserver, the music app might be more...
problematic).
### Building qtserver
Dependencies:
* qt4
* OpenGL/GLU

Cd to '''qtserver'''
Run '''qmake-qt4''' to build the makefile, and run '''make'''.

#### Notes on qtserver
At the moment, this application's components have no documentation!
Qtserver uses [http://lodev.org/lodepng/](lodepng) to load PNG
textures. It can also load (some) TGAs, uses old code I had lying
about. The meshes are a subset of DirectX files I used while at
Broadsword, and the code for loading them is very old indeed:
we need better mesh loading code. Writing an OBJ loader is probably
simpler than an X loader, I just haven't done it yet.

### Building the music app
Dependencies
* liblo (for Open Sound Control input and output) (http://liblo.sourceforge.net/)
* jack client library (can be found in most distro's repos)
* Diamond Apparatus (my publish/subscribe system used for my controller
systems) (https://github.com/jimfinnis/DiamondApparatus/)
(If you don't want this, just set DIAMOND to 0 in components/data.cpp
and remove "diamondapparatus" from the libraries in the CMakeLists.txt file).

If you want neither Diamond Apparatus or OSC support, just remove
"lo" and "diamondapparatus" from the libraries
and "components/data.cpp" from the source files in CMakeFiles.txt.

Documentation for the music app's components can be found in
music/doc, in LaTeX.

### Notes on the music app
You'll need to connect synths to it with Jack; it creates a single
MIDI port called stumpymusic:out for this purpose. The various
note playing components allow the channel to be set. There is currently
no MIDI in; I use OSC and Diamond Apparatus for this (since MIDI controller
input has only 128 values).

## Patches and libraries
A graph of components in Stumpy is called a "patch", from the
terminology used in electronic music. Patches are arranged into
patch libraries, and each library has an active patch. The files
saved by the editor are patch libraries.

# Using the editor client
(Before running the client, make sure you can compile and run at
least one of the application servers for reasons which will become
obvious.)
The source code for the editor can be found in the ''StumpyEditor''
directory: it's a Java swing app using the Docking Frames framework
(http://www.docking-frames.org/). A JAR is included in the release,
however, as '''client.jar'''.

When the client is open, a toolbar will appear. Before doing anything
else, use the arrow-out-of-box icon to connect to a running application
server:
you can't do any editing until you connect to a server, because the
server needs to send all the information about which components the
application supports. Once this has been done, a few more buttons will
become active:
* '''stop button''': disconnect from server (or close connection to
dead server)
* '''open''': open a saved patch library
* '''create''' (box with star in corner): create a new patch library
* '''X''' : stop a running patch and clear the server
Additionally the "upload" (green arrow) button will become active on
the right hand side, although clicking it without a library will
result in an error.

Clicking on "create" will create a new patch library, which will be
unnamed until it is saved. Doing this will make a new box appear showing
the patches in the library (none yet). More buttons will become
available: the "new" button (to create a new patch) and the "save" button
(to save the library).

Clicking on the "new" button will create a new untitled patch. The right
mouse button will pop up a context menu, while double-clicking will
open the patch. The right-arrow button on the toolbar will make the
selected patch active, which you need to do before uploading or nothing
will happen.

Make the selected patch active and open it, and a graph editor will open.
The big window with the boxes in the corner, which is still empty, is
the component editor. We'll use that later.

You can upload this empty patch if you wish by clicking on the green
up arrow in the toolbar. Be sure to activate it first. Once a patch is
uploaded and active, the client will send live changes to the server.

Right-clicking in the editor window will open a context menu from
which you can create new components. Create an output component (under
"control"). The small pads are connection points, and their colour
indicates the type (see below). Components can be dragged and
selected, either single or as a group by dragging around them. They
can be deleted, copied, cut and pasted with the usual keys.
Connections between components can be made by dragging the connection,
and clicking on a connected input will disconnect it. Note that one 
output can go to many inputs, but one input can only be fed by one
output. Connections can only be made between inputs and outputs of
the same time (except for "any" connections).

## Connection types
* '''blue''' - these are floating point numbers, typically used for
all numeric connections (even integers in quite a few components)
* '''green''' - integers, often used as "trigger" values
* '''black''' - "flow" connections: no data is passed, but the output
component calls the input component as part of its processing.
The move and primitive components in the example above are connected by a flow,
which means that the move changes the current 3D transform state, calls
the primitive (which draws the cube) and then resets the transform state.
Many components work like this. The output only accepts flows.
* '''yellow''' - these accept any connection type, and are generally used for
"switcher" components which pass a particular input through to their output.
Make very sure that you pass the appropriate type through, or Bad Things
will happen: you lose the type checking when these are used.
* '''other''' - some applications define their
own types (like the music system's "chord" type)

## Component view
Double-clicking on a component will open its parameter list in the component
view box. Each component has a big bar at the top, and double-clicking 
a component either opens it or brings it to the top of the list. Components
can be closed with the close icon in the bar, or minimised to just the bar by
clicking the minimise icon.

At the top of each component's box is a list of its inputs and outputs
(useful if you forget). Each output also has a "runalways" box, so you
can make that component always run even for multiple gets of the same
output (see below).

Below this are the parameters, which are of the following types:
* Integer
* Float
* Boolean
* Enumerated list

Note that with float boxes you can type a number, but the change will
not be registered until you hit enter.


# What happens during an update
The server calls the output component, which calls all its inputs
in turn (look at the source [https://github.com/jimfinnis/stumpy2/blob/master/qtserver/components/output.cpp](here).
Each of those components runs, which may involve getting inputs (flows
or otherwise) - and each of the those input components calls their
inputs and so on, recursively. In general, if two components connect
to the same input, that input component will only run the first time - 
the second component will use the stored value. However,
flow inputs always cause their component to run, no matter how many times
they are called.

# A basic example in the Qtserver app
* Start the server - a blue (empty) output window should open.
* Start the client and connect it to the server.
* Open a new library and a new patch, and make it active.
* Open the patch, and create an output.
* Create a transforms/move component, double click it, and set the Z
to about -20 (away from the camera). Connect its output to the output
component.
* Create a transforms/ring component and connect its flow output
to the move. This ring of objects (which we don't have yet) will now
be moved -20.
* Create another ring component and connect its flow to the first ring. We
now have a ring of rings.
* Create a primitive component and connect it to this new ring.
* Click the upload button and check the server's output window: you
should see a geometric bunch of cubes (the default primitive).
* Try changing the number of objects in each ring.
* Connect a transforms/rotate component between the rings.
* Create a time/clock component (which just outputs the time in seconds
since the program started).
* Double click the clock and turn the rate up (this just multiplies the
output value by a constant).
* Connect the clock to the rotate's float input, which is the "modulator" input.
* Double click the rotate, and change its mod values. The inner rings
should now be rotating.
* Try adding more rotators between the ring and the primitive, and the
other ring and the output, connecting them all to the same clock,
and setting the modulator values on them.
* Play about. Change the ring radii (if the inner ring is wider than the
outer, interesting things happen). Add an environment map between the move and the output, to
make everything shiny. Maybe a texture too. Use a mixer to get more than
one thing rendered in the same place.
* You can even use the ring's float output to connect to places
below it in the graph - it outputs the current index in the ring,
so you can change how each element in the ring renders. This, of course,
breaks the original directed graph idea :)

# Issues and gotchas
Too many to count at the moment, particularly with the UI. It's very
scary in there. Bear with me.

One notable thing is that if components change their spec, it will naturally
break any save files. A subtle effect here is with qtserver, if you add new textures
to the media/textures directory: the enumerated parameters are stored
as integers in the files, so those numbers may now be out of step.


# Writing applications and new components
Please read the (brief) [developer docs](./DEVELOPER.md) and
the source code.
