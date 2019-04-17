# WiiGUI
Nintendo Wii homebrew app built using DevKitPro libraries.

## In This Repo

## How to Use

## Future Plans


## Versions
All progress that has been made on the design.
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

