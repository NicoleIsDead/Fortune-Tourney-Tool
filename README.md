# Fortune-Tourney-Tool
A small RNG based tool that I made for masterofn00bs's mahjong tourney.
Your chance increases/decreases based on your score. It then decides if you win or lose by using an RNG value.


## How to compile/setup
You need Qt to compile this.
I used Qt version 6.0.1
I highly recommend using QT Creator.

After building, copy the 'PlayerData' folder to the build folder. The software will check this folder for the emote data.
If you get the error message "PlayerDatabase folder missing at: ...", that is the folder path it is looking for. Copy the emote data there.

Player folders contain 4 emotes: sad.png, default.png, happy.png, rolling.png
You are free to edit these to whatever image you like, as long as you keep the correct names

An example PlayerData folder is provided in the PlayerData.zip file.
It should look like this:

    ├── default
    │   ├── default.png
    │   ├── happy.png
    │   ├── rolling.png
    │   └── sad.png
    ├── kaavi
    │   ├── Thumbs.db
    │   ├── default.png
    │   ├── happy.png
    │   ├── rolling.png
    │   └── sad.png
    └── playerDatabase
        ├── Isaac Clarke
        │   ├── Thumbs.db
        │   ├── default.png
        │   ├── happy.png
        │   ├── rolling.png
        │   └── sad.png
        ├── Player 1
        │   ├── default.png
        │   ├── happy.png
        │   ├── rolling.png
        │   └── sad.png
        ├── Player 2
        │   ├── default.png
        │   ├── happy.png
        │   ├── rolling.png
        │   └── sad.png
        └── Player 3
            ├── default.png
            ├── happy.png
            ├── rolling.png
            └── sad.png

## How to use
1. Start the program
2. Pick your character and type in the amount of fortune points
3. Click the spin button
4. ???
5. Profit

## Sample images
![gui](/sample/gui.png?raw=true "Optional Title")

## Changelog
V1.0
- Initial Release

V1.1
- Added a seperate character emote while spinning

V1.2
- Code cleanup
- Changed the default character image folder name from 'freed jyanshi' to 'default'
- Added error messages when not finding the PlayerData folder
