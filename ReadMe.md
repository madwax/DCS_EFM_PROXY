# Proxy EFM for DCS 
## The Problem!
Writing an EFM can be fun as DCS keeps hold of your DLL once it has gotten it pores on it and so you have to shutdown it, then do your build and restart.  This process is a pain!

## What does this little project do?
1. Provides you a proxy EFM that loads your real EFM on demand because DCS likes to keep the handles to efm dlls.  The proxy ed_fm_x calls will  
	* ed_fm_set_plugin_data_install_path() - The proxy will load your EFM dll.
	* ed_fm_release() - The proxy will unload your EFM dll so that you can replace it.
2. The proxy has a config file called efm.proxy.ini.  This is used to control where your EFM is located and a few other settings.
3. A bunch of CMake files... I madwax use CMake for everything now as it gives me out of source tree builds and I can generate for any version of M$VS or XCode etc etc... See later on for breakdown on the cmake stuff
4. You build the proxy standalone or as part of a bigger project. 

### Standalone build
Once you have built the proxy you can use it with any other mods as long as your rename the dll to the correct name.

## Config options
If you want to override default options without editing code you can create and place an ini file called efm.proxy.ini in the same directory as this proxy.  

Example
[General]
target=%PATH_TO_YOUR_EFM.DLL%

Notes
target - The path can be relative to your bin folder or absolute so you can have your real efm in your visual studio build area and not in your mods bin folder.


## CMake Stuff
There is just one CMake file and that builds the proxy.  The file dcs.cmake is used to define options and a few helpful functions. The proxy cmake should be embeddeable into other cmake projects.
Everything is out of source build if you want it and the project will copy the proxy dll into your mod's bin folder for you.

I only generate MSVS solutions via CMakes CL or GUI.  I don't use M$VS new CMake instration stuff so try at your own risk.

### Which version of CMake?
Everything is setup for 3.18.0 but if you have an older version installed you can go down to 3.8.0

If you need it: https://cmake.org/download/

### CMake Configure Options
1) DCS_GAMR_DIR - The root of your DCS install. DCS headers are pulled from the API dir below it location.
2) USER_MOD_DIR - Where your mod lives in saved games.
3) USER_MOD_NAME - The name of your mod
4) USER_MOD_EFM_BIN_NAME - If your EFM is named something other than USER_MOD_NAME set it here. Don't add .dll as that will be done for you.
5) USER_MOD_PROXY_SUPPORT - Will be forced On if you are building just the proxy. This is hear for embedding into a proper EFM template/project setup.

## Building
It's a cmake project ;)
	

	
	














