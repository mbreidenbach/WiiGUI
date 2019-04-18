# WiiGUI
Nintendo Wii homebrew app built using DevKitPro libraries.

## In This Repo
This repo contains all files used to maintain, compile, and run the application.
- Source Folder
  - Includes main.c and all .s files for Image Declaration
- Include Folder
  - All Images
- Makefile
  - NOT made by me. Template found from CodeMii tutorial and based from generic DKP makefile.
- .DOL and .elf Files
  - The application itself
## How to Use
- To Use the Application (Assuming you have homebrew set up on your Wii)
  - Put the .DOL file into a new folder. Rename the .DOL file to "boot" and place the folder in /apps on your SD card.
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
- Why the hell didnt I write v3.0 already
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

