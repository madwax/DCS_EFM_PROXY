# Proxy EFM for DCS 
## The Problem!
Writing an EFM can be fun as DCS keeps hold of your DLL once it has gotten it pores on it and so you have to shutdown it, then do your build and restart.  This process is a pain!

## What does this little project do?
1. Provides you Proxy EFM what loads your real EFM.  DCS will keep hold of the proxy but on:
	* ed_fm_set_plugin_data_install_path() - The proxy will load your real EFM, write it all up and proxy all the calls through.
	* ed_fm_release() - The proxy will do any clean up and unload your real EFM.  This means you can rebuild it with out any file locking problems.
2. A bunch of CMake files... I madwax use CMake for everything now as it gives me out of source tree builds and I can generate for any version of M$VS or XCode etc etc... See later on for breakdown on the cmake stuff
3. If you want to demo/play around I've added the CMakefile to build the EFM for nibbylot brill AH-6J mod as that has a basic EFM.

## CMake Stuff
There is a top level CMakeLists.txt file which includes the proxy and your efm.  The proxy and efm then have there own CMakeLists.txt file. 

You can do out of source builds without any problems. The CMake will copy the DLLs on build.

I (madwax) only generate MSVS solutions via CMakes CL or GUI.  I don't use M$VS new CMake instration stuff so try at your own risk.

### Which version of CMake?
Everything is setup for 3.15.0 but if you have an older version installed you can go down to 3.8.0

If you need it: https://cmake.org/download/

### Top Level Options
1. MOD_BIN_PATH - Were you want to put the build proxy and efm. This can be absolute or relative.  Relative paths are from the top level CMakeLists.txt file
2. MOD_BIN_FILENAME - The name of your efm.  This must be whats in your lua!
3. MOD_USE_PROXY - If On/True The proxy and efm will be built.  The proxy will be called ${MOD_BIN_FILENAME}.dll and your efm called ${MOD_BIN_FILENAME}.real.dll.  If Off/False then only your efm is build and named ${MOD_BIN_FILENAME}.dll
4. DCS_LOCATION - The root of your DCS install.  We pull in DCS header files so we need to know were to get them from.

## Intergation into AH-6J for Demo/Education!
1. Copy everything into the "EFM Source Code" dir.
2. Open up CMake GUI. 
	1. For "Where is the source code" Press "Browse Source" and select the "EFM Source Code" dir
	2. For "Where to build the binaries" Copy the source path and append "/build" to it.  All the build files will be generated here.
	3. Press "Configure"
		* Specify the generator for this project - Visual Studio 15 or 16 should be good (tested on 16)
		* Option platform for generator - If the default is NOT x64 select it! THIS IS IMPORTANT!
		* Finish
	4. Need to set options
		* DCS_LOCATION - The path to your DCS install
		* MOD_BIN_FILENAME - set to AH6
		* MOD_BIN_PATH - It should be "../bin" 
		* MOD_USE_PROXY - Select it so the tick is shown.  
	5. Press "Generate"
	6. Open M$VS, File->Open->Project/Solution - Select MOD_EFM.sln file in your "/build" dir
	7. Build->Build Solution.  You should then find two dlls in the mod's bin folder.  the proxy will be named AH6.dll and the real EFM AH6.real.dll
	8. Start a copy of DebugView (https://docs.microsoft.com/en-us/sysinternals/downloads/debugview), you have to launch it as admin. The proxy will output via OutputDebugString ;)
	9. Start DCS and do an AH-6J instant action
	10. You should have a few message about what the proxy has loaded in DebugView and be able to fly the Bird.
	11. Exit your flight and return to DCS's menu
	12. Edit something in the EFM that you know will have an effect. 
	13. In M$VS only rebuild the project (Solution panel, select the "efm" project, right click->Project Only->Build Only. It will compile and your uupdated efm will be in /bin
	14. Until you get board Goto 9.
	

	
	














