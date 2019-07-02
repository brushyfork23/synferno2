# Synferno

Synferno is a flame-effect synchronizer which allows a DJ to easily trigger complex sequences of fireballs which perfectly match the music they’re playing.  The system consists of a console and four flame effects.  This codebase contains designs for building the console, the software which runs on it, and a the software for a flame-effect simulator to allow for bench testing.

## Physical Layout

The face of the console has 16 interface components:

 * One key-lock switch to ensure user is permitted to run console
 * One arming switch to ensure user wants to run console
 * Five white illuminated push-buttons to select sequence
 * Four red illuminated push-buttons for manually firing each of the four output channels individually
 * One large red illuminated push-button for manually firing all four output channels at once
 * One yellow illuminated push-button for resetting the down-beat and for flashing at the first beat of each stanza
 * One yellow illuminated push-button for manually tapping out a BPM and for flashing on each beat
 * One OLED screen which displays a menu
 * One rotary-encoder with integrated push-button for selecting and changing menu options

The back of the console has seven interface components:

 * One IEC power socket
 * One DIN-5 MIDI input port
 * Four SpeakOn connectors to deliver activation power to the four flame effects
 * One rocker-style power switch

![Synferno Console Face](docs/media/Synferno%20Console%20Face.jpg)

Included in `docs/diagrams/` are [renderings of each face and the positioning of internal components](docs/diagrams/Synferno2%20Console%20Interface%20Layout)

## Usage

The console’s primary function is to accept a BPM and energize the four SpeakOn output ports according to a selected sequence.  BPM can be read from a connected MIDI device or manually set by either tapping repeatedly on the Tap button or setting a value in the menu with the rotary encoder.  The beginning of a stanza (AKA the down-beat) can be set by pressing the Zero button.  A sequence is selected by toggling one of the five white buttons, and the sequence each button represents can be changed in the menu.  The duration of each activation is set in the menu.  Each output channel can be activated manually at any time by pressing the corresponding smaller red button, and all four channels may be triggered at once with the large red button.  There is a delay of several milliseconds between activation of an output port and the audible “POOF” from a flame effect, which can be compensated for by setting a delay in the menu.

## Testing

To bench test the console without connecting flame effects, the output ports can be connected to an adapter, which then connects to a computer running a flame-effect simulator.  The adaptor accepts 12V DC from the console via SpeakOn connectors, uses a four-channel optocoupler to convert their signals to 3.3V, reads those signals with an Arduino, and sends samples to the computer over a serial line.  The simulator running on the computer is a Processing application which looks for a positive signal coming from each channel then draws a rising ellipse and plays a POOF sound.