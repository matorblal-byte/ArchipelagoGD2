# ArchipelagoGD
A mod for bridging Archipelago to Geometry Dash! \
At the top right, you should see a Archipelago button, click it and enter the URL to the server, your slot name (basically player name) and password if it has it! You should be connected to the game, and you can start playing levels! \
This mod only partially saves your progress. It will save everything but your stats, which my be changed in the future. \
\
You may want to look at the [setup](https://github.com/matorblal-byte/APWorldForGDArch/blob/main/worlds/geometrydash/docs/setup_en.md) to see how to use this more in depth
# Non-Archipelago Users
Archipelago is a multi-game (or you can put only one game i guess) randomizer randomizing items across games. This is the client mod for that.
## Hosting
Archipelago requires hosting to actually play it, so here's how! \
1. Download [Archipelago](https://github.com/ArchipelagoMW/Archipelago/releases/latest) and run it
2. When it’s finished being setup [download](https://github.com/matorblal-byte/ArchipelagoGD2/releases/latest) and open the APWorld, this will download it into Archipelago
3. Open the archipelago launcher and find the shortcut called “Generate Template Options” and click it, ignore the window that will pop up when you do this
4. Go to the "Options Creator" shortcut, set a name (this will be the slot name field on the mod), scroll down to Geometry Dash, select your desired options, and click Export Options, then save the file to Archipelago's "Players" directory (usally C:\ProgramData\Archipelago\Players on windows but if you're unsure you can click the "Browse Files" shortcut).  
5. Click on the "Generate" shortcut. This will generate the item randomization. If there is a "Fill.FillError", try regenerating again. If it persists please report it
6. Head to https://archipelago.gg/uploads, upload the generated file in the Outputs folder of the Archipelago directory (You can also host locally but that requires port forwarding and disabling firewall so I don't recommend it).
7. After the server finishes setting up it will display a url that you put into the mod to ultimately connect! 
\
\
If that was too confusing for you, there’s also a offical [guide](https://archipelago.gg/tutorial/Archipelago/setup_en) and multiple videos online. Just remember that you will have to run the APWorld to use this mod. \
\
Also, you don't have to host if somebody else is hosting. They will likely tell you what to do, then give you the URL so you can connect.
## "What options are what??? Helloo???"
Hover over the names to see their description. Also ultimates do nothing as of 1.0.0
## Progression (wip)
All levels are locked by default, but the number unlocked is decided by what you set in the options. Each level you complete releases a check, every coin does aswell!\
You can win by reaching 180 or more stars which will send out all of your unclaimed items! \
If you enabled the check shop stetting, you can buy Archipelago items from the shop keepers shop - items will be at the last page. /
This mod prioritizes main levels heavily. You can still progress using online levels, but you wont be able to send out items.
# More information
## <cr>Partial Incompatabilities</c>
<co>BetterProgression by ItzKiba</c> - Does progression on the Archipelago save \
<co>Backups by HJfod</c> - <cb>You should probably have this enabled just in case, but it may</c> backup the Archipelago save which is probably not desired \
<co>Globed by dank_meme</c> - Can probably work, but can break some things and can be used to completely break progression \
And possibly more!  \
Mods that are fully incompatible will not load. 
# Thanks
<cb>Tiago1257 (1257Plays)</c> - Making the orginal, yet unfinished mod, and letting others fork it! Your orginal code helped massively for me \
Others who helped original mod creator with this: \ 
<cb>N00byKing</c> - APCpp and general help with Archipelago \
<cb>dankmeme01</c> - Help with Geode SDK + cross-compiling (and like 2 lines of code i yoinked from globed) \
<cb>matcool</c> - Help with Geode SDK + cross-compiling \
<cb>Prevter</c> - Help with CMake and APCpp-gd \
<cb>Erymanthus, hiimjasmine00, SpaghettDev, km7dev, underscored (TechStudent10), Uproxide, TimeStepYT and many others</c> - Additional C++ and Geode Help \
<cb>The Archipelago, Rhythm Doctor Lounge and Geode SDK Discord Servers</c> - Emotional Support + Progression Planning \
If you find a bug, open an issue on the GitHub or join the Discord and find the Geometry Dash thread in #future-game-design!
