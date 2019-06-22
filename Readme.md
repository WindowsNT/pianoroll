# Pianoroll for Windows 

A flexible, featured pianoroll control, using Direct2D to paint.
![	Pianoroll](https://raw.githubusercontent.com/WindowsNT/pianoroll/master/1.jpg)

Article:
https://www.codeproject.com/Articles/4042343/A-flexible-Direct2D-Pianoroll-for-your-music-apps

## To use

1. Instantiate PR::PIANOROLL object
2. Pass WM_KEYDOWN, WM_LBUTTONDBLCLK, WM_LBUTTONDOWN, WM_RBUTTONDOWN, WM_MOUSEMOVE,WM_LBUTTONUP, WM_SYSKEYDOWN to the control
3. When you want to paint it, call member "Paint()" passing a Direct2D object and the RECT

## Features

* Notes support channel (0-15), velocity (0-127) , layer (unlimited)
* Moving, Resizing with snap controls
* Supports diatonic movement through specified Key and Mode (Major/Minor)
* Unlimited undo/redo
* Unlimited layers
* Piano side (Left/Right) 
* Callbacks
* Tools - Auto, Eraser, Single click entry, Quantizer, Paint
* Serialization/Deserialization to XML
* Key per measure
* Tempo per measure
* Time signature per measure
* MIDI export 
* Partial MIDI import (in progress)
* Non-note MIDI notes
* Meta events (Raw hex and specific items)
* Aftertouch events
* Pitch shift events
* Note quantization
* Markers
* Long text show
* Chromatic/Diatonic transposes
* Record from MIDI in device
* Event streaming to callback
* Live note viewer
* Part editing mode

## Callbacks
Your callbacks are notified when:
* Note is changed or inserted or removed
* Piano note is tapped
* Redraw requested

## Keyboard shortcuts
* A : auto tool
* E : eraser tool
* I : single entry tool
* Q : quantize tool
* N : paint tool
* 1,2,3,4 (up row) : Select beat duration for next note
* Shift+1,2,3,4 (up row) : Beat duration 1/8, 1/16, 1/32,  1/64
* < and > : Change selected items velocity
* Ctrl+ < and > : Velocity off/full
* < and > when pitch shift: Up/Down pitch shift (combine with Ctrl/Shift/Alt)
* +/- : Change selected items position diatonically
* Shift +/- : Change selected items position chromatically
* Numpad +/-/* : Zoom in,out,all
* Shift + Arrows up/down : Change channel
* Alt + Arrows up/down : Change layer
* / and \ : Enlarge/reduce notes
* D,H,': Double/Half/+1/2 notes
* Ctrl+Q : Quantize notes
* Ctrl+G : Go to measure
* J : Join notes
* Ctrl+1...6 : Snapping resolution
* Alt+1-9 Numpad : Toggle layers
* 1-9 Numpad : Next layer
* Ctrl+A : Select all
* Ctrl+C : Copy
* Ctrl+T : Diatonic transpose
* Ctrl+Shift+T : Chromatic transpose
* Ctrl+V : Paste to last clicked measure
* Ctrl+Z : Undo
* Ctrl+Y : Redo
* Z : Move left
* X : Move right
* [,] : Next/Prev marker
* Right/Left arrow : move roll 
* Del : Delete selected notes
* Ctrl+Home : Scroll to start
* P : Toggle part editing mode
* Alt+P : Select next part
* Shift+P : Selected parts names
* Tab : Go next note or part
* Shift + Tab : Go prev note or part

## Mouse
* Dblclick : insert note (auto tool) 
* Control + Dblclick : insert non note event
* Control + Shift + Dblclick : insert aftertouch
* Dblclick on note : remove note
* Click on note : select/unselect (quantize in quantize tool)
* Drag outside note: select (insert in single entry tool, delete in eraser tool, quantize in quantize tool)
* Drag/Resize note

## Part editing
In part editing, selections of parts affect all part notes (for example, copy/paste/delete)
The J command combines parts

