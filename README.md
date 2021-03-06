# Houdini Engine for Unreal - Version 2 - Alpha

Welcome to the Alpha repository for Version 2 of the Houdini Engine For Unreal Plugin.

This plug-in brings Houdini's powerful and flexible procedural workflow into Unreal Engine through Houdini Digital Assets. Artists can interactively adjust asset parameters inside the editor and use Unreal assets as inputs. Houdini's procedural engine will then "cook" the asset and the results will be available in the editor without the need for baking.

Version 2 is a significant rewrite of the core architecture of the existing Houdini Engine plugin, and comes  with many new features, and improvements.

Here are some of the new features and improvements already available in Alpha 3.1:


Core:
New and redesigned core architecture, more modular and lightweight.
All the Houdini Engine/HAPI logic is now Editor-only and contained in the “HoudiniEngine” module. All the custom runtime components and actors used by the plugin now simply acts as data-holders, and are processed by the HoudiniEngine modules, removing the need to bake HDA before packaging a game.
The plugin now relies exclusively on native, UProperties based serialization, so operations like cut and paste, move between level, duplicate etc.. do not exhibit any of the issues that version 1 had with those operations.

Outputs:
- Static Mesh creation time has been optimized and now uses Mesh Descriptions.
- Alternatively, you can also decide to use an even faster Proxy Mesh generation while editing the HDA.
  Those can then be automatically refined to Static Meshes, either on a timer, or when saving/playing the level.
- World composition support: Tiled heightfields can now be baked to multiple landscape actors/steaming proxies, and will create/update the levels needed for world composition.
  You can specify the level's path by using the new “unreal_level_path” attribute, that is also used by meshes and instancers so they can also be baked out to separate levels.
- Material overrides and generic uproperty attributes can either be applied on the instancer, or per instance (when using mesh split instancers or instanced Actors).
- It is possible to create foliage instances directly, without baking, when using the “unreal_foliage” attribute on an instancer.
- A class can be directly instantiated by the "unreal_instance" attribute (ie “PointLight”, “AudioVolume”… ).

Inputs:

- Colliders on a Static Mesh can now be imported as group geometry.
- World inputs can now read data from BSP brushes.
- Instancers and Foliage are now imported as packed primitives.
- World inputs have an improved bound selector mode, that lets them send all the actors and objects contained in the bounds of the selected object.
- World inputs can now import data from all supported input objects (landscape, houdini asset actors..)
- World inputs can now import data from actors placed in a different level than the Houdini Asset Actors's.
- A single curve input can now create and import any number of curves.
- You can alt-click on curve inputs or editable curves to create new points.
  
Parameters:
- HDA parameters and inputs editing now support multi-selection.
- Parameter UI/UX has been improved:
- Folder UI (tabs, radio, collapsible) has been improved
- Ramps UI has been improved, and it is easy to turn off auto-update while editing them.
- When an asset is dropped on a string parameter, it automatically sets its value to the asset ref.
- String parameters can now be turned into an asset picker via the “unreal_ref” tag.
- Support for File parameters has been improved (custom extension, directory, new file...)
- Multi-line strings, Column Labels, Button Strip, Log Int and Floats are now supported.

General:
- The plugin's UI has been completely revamped, a new Houdini Engine menu has been added to the editor.
- bgeo/bgeo.sc files can be imported natively in the content browser (Mesh and instancers).
- The PDG Asset Link has been added, allowing control of TOP networks nested in HDAs, and works similarly to the one in the Unity plugin.
- Session Sync is supported, allowing the plugin to connect to a session of Houdini Engine running inside Houdini. 
  The state of Houdini Engine can be viewed in Houdini while working with the plugin in Unreal, and changes on either end, whether in Unreal via the plugin or in Houdini via its various interfaces, will be synchronized across so that both applications will be able to make changes and see the same results.

For more details on the new features and improvements available on this alpha, please visit the [Wiki](https://github.com/sideeffects/HoudiniEngineForUnreal-v2/wiki/What's-new-%3F).

The main focus of this Alpha is to ensure proper compatibility with version 1 workflows and tools.
Therefore, some of the new features planned for the full release of version 2 are not available in the Alpha yet.
Noticeably, Alpha3.1 does not have Blueprint support, and the PDG integration is still in its early stage.

# Feedback

Please use this repository's "Issues" to report any bugs, problems, or simply to give us feedback on your experience with version2.

# Compatibility

Currently, the [Alpha3.1](https://github.com/sideeffects/HoudiniEngineForUnreal-v2/releases) release of V2 has binaries that have been built for UE4.25 and UE4.24, and is linked with Houdini 18.0.532.

Source code for the plugin is available on this repository for UE4.25, UE4.24, UE4.23 and the master branch of Unreal (4.26).

It is important to note that Version 2 is not backward compatible with version 1 of the Houdini Engine for Unreal plugin.

To that extent, it is important that you use version 2 of the plug-in only with projects that do not contain version 1 assets.

However, the Houdini Digital Assets themselves (the HDA files), that were created for version 1 of the plugin are fully compatible with version 2, as it supports most of version 1 workflows.

# Installing the plugin

01. Download the pre-built binaries of the plugin in the "Releases" section of this repository. 

01. Extract the "HoudiniEngine" folder in the release to the "Plugins/Runtime" folder of Unreal.
    You can install the plugin either directly in the engine folder (in "Engine/Plugins/Runtime/HoudiniEngine") or in your project folder (in "Plugins/Runtime/HoudiniEngine").
01. Start Unreal Engine, open the Plug-ins menu and make sure to enable the `HoudiniEngine v2` plug-in (in the `Rendering` section). Restart UE4 if you had to enable it.
01. To confirm that the plug-in has been successfully installed and enabled, you can check that the editor main menu bar now has a new "Houdini Engine" menu, between "Edit" and "Window".
01. You should now be able to import Houdini Digital Assets (HDA) `.otl` or `.hda` files or drag and drop them into the `Content Browser`.
01. Once you have an HDA in the `Content Browser` you should be able to drag it into the Editor viewport. This will spawn a new Houdini Asset Actor. Geometry cooking will be done in a separate thread and geometry will be displayed once the cooking is complete. At this point you will be able to see asset parameters and inputs in the `Details` panel. Modifying any of the parameters will force the asset to recook and possibly update its geometry.


# Building from source

01. Get the UE4 source code from: https://github.com/EpicGames/UnrealEngine/releases
01. Within the UE4 source, navigate to `Engine/Plugins/Runtime`, and clone this repo into a folder named `HoudiniEngine`.
01. Download and install the correct build of 64-bit Houdini. To get the build number, look at the header of `Source/HoudiniEngine/HoudiniEngine.Build.cs`, under `Houdini Version`.
01. Generate the UE4 Project Files (by running `GenerateProjectFiles`) and build Unreal, either in x64 `Debug Editor` or x64 `Development Editor`.
01. When starting the Unreal Engine editor, go to Plug-ins menu and make sure to enable the `HoudiniEngine v2` plug-in (in the `Rendering` section). Restart UE4 if you had to enable it.
01. To confirm that the plug-in has been successfully installed and enabled, you can check that the editor main menu bar now has a new "Houdini Engine" menu, between "Edit" and "Window".
01. You should now be able to import Houdini Digital Assets (HDA) `.otl` or `.hda` files or drag and drop them into the `Content Browser`.
01. Once you have an HDA in the `Content Browser` you should be able to drag it into the Editor viewport. This will spawn a new Houdini Asset Actor. Geometry cooking will be done in a separate thread and geometry will be displayed once the cooking is complete. At this point you will be able to see asset parameters in the `Details` pane. Modifying any of the parameters will force the asset to recook and possibly update its geometry.


# License

Please remember this the Alpha is currently private, and is therefore subject to our Alpha/Beta NDA and [License](https://github.com/sideeffects/HoudiniEngineForUnreal-v2/blob/4.24/LICENSE.md) agreement.