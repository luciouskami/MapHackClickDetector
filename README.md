# MapHackClickDetector

This is a tool for detecting the selection of invisible heroes by maphack in Warcraft III. I rebulit this project using VS2015. This project supports Windows 7 32-bit and Warcraft III 1.24b. 

## Usage
Build using VS2015, then copy MHCDDLL.dll into the same folder with war3.exe. Start war3 and MHCDGUI, then click "Initialize". If everything is OK, "Started" will be shown in the MHCDGUI.

Here is the example: I used maphack and selected an invisible enemy hero, the tool would detected the cheating. If some other player has maphack and do so, it will also be detected.
![alt tag](https://github.com/zhujf553/MapHackClickDetector/blob/master/Illustration.png?raw=true)

## Implementation

By calling native JASS function in war3 game engine, we can get information like whether a unit is a hero (GetHeroLevel), whether a unit is visible to some player (IsUnitVisible), whether a unit is selected by some player (IsUnitSelected). 

First of all, we need to get handles of all heroes. By hooking assignment operation in game.dll, handles can be got. For each handle, GetHeroLevel is called to check whether the handle is a hero, so that the player of a hero can also be found. 

Then continuously scan all heroes, for all players, whether one player selects an invisible hero. However, if a player selected a visible hero, then hero became invisible, IsUnitSelected would still give a "true". Therefore I used a timer to check when a visible hero is selected and when it is visible. 

Suwuhao is my used name. You can contact suwuhao@yahoo.com to verify.
