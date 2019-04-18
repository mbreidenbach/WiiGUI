# WiiGUI
Nintendo Wii homebrew app built using DevKitPro libraries.
## Inspiration
Homebrew has been a hobby of mine for a few years now. The Nintendo Wii was the first console I ever soft modded, and I've downloaded plenty of other users projects and programs to run for myself. I felt that it was my turn to give to the scene and try my best at making a homebrew application of my own. I'm a long way from proficient, but this is a small step towards hopefully a lot of future projects not just on the Wii but other platforms as well.

## What I Learned
This was my first ever time making homebrew content, and so learning the capabilities of the DevKitPro libraries was a struggle. I took a long time looking at tutorials online (CodeMii was a great source) and followed along with their code as it expanded. This was also my first time coding in assembly and C. Not many features of these programming languages we're used but it was a great way to learn the basics.

The hardest part honestly was trying to find workarounds when the tutorials I found we're inaccurate. The homebrew scene for the Nintendo Wii is thinning now that its over a decade old, and finding links and sources is more difficult than ever. The tutorial I used was from 2009, and so there we're always a couple things that needed to be tweaked in order to get it working.

## What WiiGUI Does
The GUI in its final state will hopefully contain fun little click based games and ways of checking controller functionality. This entire program is built from the bottom up. The full program will hopefully include:
- GC and Wii Controller Testing
- Connect 4
- Tic Tac Toe
- Target Shooting
- and anything else I think of! :)

## In This Repo
This repo contains all files used to maintain, compile, and run the application.
- Source Folder
  - Includes main.c and all .s files for Image/ImgMem Declaration
- Include Folder
  - All Images
- Makefile
  - NOT made by me. Template found from CodeMii tutorial and based from generic DKP makefile.
- .DOL and .elf Files
  - The application itself
  
## How to Use
- To Use the Application (Assuming you have homebrew set up on your Wii)
  - Put the .DOL file into a new folder. Rename the .DOL file to "boot" and place the folder in /apps on your SD card.
  - Side note: some functionality has trouble working on Dolphin Emulator. All of my testing was done on my personal wii, not an emulator.
  
## Future Plans
- Working GUI
- Connect 4
- Tic Tac Toe
- Target Shooting
- Cursor Selection

## Versions
All progress that has been made on the design.
### v5.0:
- Removed useless code snippets (I was misimforned on how controller input was handled with 2+ controllers)
- Wii Controller can now control the cursor using IR sensor!
  - Code can detect if input is from IR or GC Stick, even after program init. (IR will overpower GC)
- Code now has some commented out function calls
  - Eventually I want to make it so that you can switch between "modes" of the cursor but for right now dol has to be remade for it to apply
- Docstrings on functions I forgot about.

### v3.0 and v4.0: Controller Input
- Why in the world didnt I write v3.0 already
- All upper GC Controller buttons (so not d-pad and c-stick) mapped and will show on screen.
- A and Home buttons on Wii Controller detect press, hold, and release.
- Found out the Wii can and will dump its stack if you dont initialize controller properly
  - or if you set two controllers to the same input (p0, p1, etc)
    - that took way too long to debug

### v2.0: JPEG's
- New Functions!
  - PictureInit
    - Initializes all picture data (currently only 1)
    - called by Init()
  - DisplayJPEG
    - Takes a given picutre and position and displays the image.
- DrawPictureCursor updated to actually make a cursor
  - DrawBox no longer used
  - its (the cursor) really big rn, and i think the code is refusing to change that

### v1.0:
- I don't know how to make a readme oof
- Makefile created and libraries added
- Starter code written
  - General Wii/library function calls
  - Working box drawing functions
    - Vertical line function
    - Horizonal line function
    - DrawBox function
  - Working cursor (using box functions)

