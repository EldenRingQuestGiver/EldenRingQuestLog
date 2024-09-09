# Elden Ring Quest Log

A mod for Elden Ring that allows to check on the progress for all quests done so far.

Implemented as a DLL mod, which has several advantages:

- It can be used along with other mods that change files such as `regulation.bin` without merging
- It should be compatible with future game updates
- It can show a language for the mod different from the one used for the game (also for non officially supported languages, like turkish and vietnamese)

############################################

Installation (Option #1 - ModEngine2)

Download the latest version of ModEngine2 and extract it somewhere.
Download the mod and extract erquestlog.dll, erquestlog.ini and the questlog_lang folder into the ModEngine-2.1.0.0-win64 folder. You should have a fodler structure similar to this:

ModEngine-2.0.0     <--- exact name could change based on your Mod Engine version
    mod
    modengine2
    questlog_lang             <--- added by you
    -> config_eldenring.toml
    -> erquestlog.dll         <--- added by you
    -> erquestlog.ini         <--- added by you
    -> launchmod_eldenring.bat
    -> modengine2_launcher.exe

Open config_eldenring.toml in Notepad and look for the line starting with "external_dlls = ...". Add the mod to the DLL list:
    external_dlls = [
    "erquestlog.dll",
    ]
If you're using multiple DLLs, make sure they're separated by commas. For example:
    external_dlls = [
        "ertransmogrify.dll",
        "erquestlog.dll",
    ]
Double-click launchmod_eldenring.bat to start the game.

____________________________________________

Installation (Option #2 - Elden Mod Loader)

If you can't get ModEngine2 to work or you don't want to use it, you can also run the mod with Elden Mod Loader.

Install Elden Mod Loader according to the instructions in its Nexus page.
Extract erquestlog.dll, erquestlog.ini and questlog_lang folder into the ELDEN RING > mods folder.
Launch the game with the Elden Mod Loader offline launcher.

____________________________________________

Installation (The Convergence)

To use this with The Convergence mod:

Create a "questlog" folder into the ConvergenceER folder (the same folder that contains config_eldenring.toml), then extract erquestlog.dll, erquestlog.ini and questlog_lang folder inside this newly created folder.
Open config_eldenring.toml, and look for the section starting with "external_dlls = ...". Add the mod to the following location:
    external_dlls = [
        "SeamlessCoop/ersc.dll",
        "Convergence/ertransmogrify.dll",
        "Convergence/ErdTools.dll",
        "Convergence/eldenring_alt_saves.dll",
        "Convergence/Scripts-Data-Exposer-FS.dll",
        "questlog/erquestlog.dll",
    ]
Double-click launchmod_eldenring.bat to start the game

Keep in mind that this mod is not an official addon for The Convergence - please don't report issues from this mod to the convergence developers and community.

____________________________________________

Installation (ELDEN RING: Reforged)

To use this with ERR, follow this process for adding DLL mods instead.

Extract erquestlog.dll, erquestlog.ini and questlog_lang folder into the dll > active folder
Double-click Launch ELDEN RING Reforged to start the game.

Keep in mind that this mod is not an official addon for ERR Reforged - please don't report issues from this mod to the ERR developers and community.


############################################

Credits for translations go to:
- parklir for the Russian translation
- dimetequiero and EmMe94 for the Spanish (EU) translation
- EmMe94 for the Spanish (AR) translation
- Anonymous for the Italian translation
- brayanluc2 for the Brazilian Portuguese translation
- 3ND34V0R for the French translation
- furkandoganer for the Turkish translation
- tuananhjhin for the Vietnamese translation
- Drta04 for the Standard Chinese translation
- senninmoodo for the German translation

Full credits for the original code to make the .dll version and the support I got while making this mod go to Tom Clark, the original creator of the Glorious Merchant mod (https://www.nexusmods.com/eldenring/mods/5192), check out his mods.
Credit for ESDTools and ESDLang goes to thefifthmatt (github repo link: https://github.com/thefifthmatt/ESDLang)
Credit for Yabber goes to JKAnderson/TKGP (github repo link: https://github.com/JKAnderson/Yabber , Nexus link: https://www.nexusmods.com/sekiro/mods/42)