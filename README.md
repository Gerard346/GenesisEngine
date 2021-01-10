# Genesis Engine v0.3 Forked version

Genesis Engine is a game engine made in C and C++ by Marc Pagès Francesh, link for his Github -> https://github.com/marcpages2020/GenesisEngine.
This is a forked version of his engine, the commit where I forked from his engine is this one https://github.com/Gerard346/GenesisEngine/commit/2a75ba8a97494f467f8d46a29975607bc5f8c864.

This is where my forked version started https://github.com/Gerard346/GenesisEngine/commit/a15facd3862401ef333404d6ac45e8621d977dc5.

  Wiki Github page: https://gerard346.github.io/GenesisEngine/
  Engine GitHub page: https://github.com/Gerard346/GenesisEngine
  My personal GitHub profile: https://github.com/Gerard346/
  Marc Pagès Francesh profile: https://github.com/marcpages2020/

## Controls: 
 
  To freely move the camera in the scene, the scene window must be selected or focused.

### Camera Controls:

 - W / Up Arrow: Move Forward
 - A / Left Arrow: Move Left
 - S / Down Arrow: Move Backwards
 - D / Right Arrow: Move Right

 - Mouse Wheel: Zoom In/Out
 - Middle Mouse: Drag to move horizontally and vertically. 
 - Right Click: Orbit around the selected object. (If an object is not selected it will orbit around the center of the scene).
 - F: Focus the camera around the selected object.(If an object is not selected it will focus around the center of the scene).
 - O: Move Up.
 - L: Move Down.
 - Hold Shift: Duplicate movement speed.
 
### Game Objects Inspector actions
 - Transform: Translate, Rotate and Scale the object. 
 - Mesh: Toggle the view of the vertex and face normals. 
 - Material: 
     - Toggle the checkers image. 
     - Remove the current texture. 

### Actions in tabs:
 - Windows: Enable the engine windows. 
 - Edit: 
   - Configuration: Change the engine settings and view graphs about the performance. 

 - Game Object: There are six primitives available to be created at any time. These are: Cube, Plane, Cylinder, Sphere,
   Cone and Pyramid. These are duplicated, the firsts are generated automatically and have no texture coordinates and the 
   ones marked with FBX will be loaded from FBX files and will have texture coordinates. 

 - About: Get the pages where the project is held in GitHub and get more information about the engine.

### Scene Saving
 - Scenes can be saved and loaded from the editor main bar. Even though they can be saved anywhere it is recommended to do so in the scenes folder to keep everything organised. Select the desired folder and write the name of the scene with no extension, it will be added automatically. If an existing scene is selected it will be overwritten. 

### Importing Files
 For proper file import it is recommended that the files are already inside the Assets folder before starting the engine. If they are not, files can be dragged and dropped onto the engine in order to be imported. One last way to import files is copying them in the Assets folder and push the Reload button under the Assets hierarchy in the Assets window. Even though fbx files can be imported directly dropping them onto the engine it is recommended that for textures they are first copied in a folder inside assets and then dragged onto the engine to acces the importing options. 

### Importing Options
There are plenty of importing options specially for textures. When the file is dropped onto the engine an importing window will pop up to select the desired options. The only model format supported is fbx so if a warning or error message is displayed saying that a file from a different format can't be imported, this is the reason. 

### Camera Culling
 - The camera in the center of the screen is the main camera. Move it to see how camera culling is applied to objects. In the menu bar editor camera culling can be applied to see all objects in scene. 

### Things to take into account
 - At the end of the inspector window there is a tab called Resources. In this tab it is shown all the resources which are currently loaded into memory. If numbers seem to not match for textures take into account that assets window icon textures and preview textures are included in the list.

- When a file is deleted from the assets window the engine might crash if deleting access is not given to it. The main cause might be Avast so try disabling it while using the engine. 

## Third Assignment
 - To Start the UI menu, you have to load the scene main_menu.scene using the menus at the top bar.
 - To enables the funcionality of the UI you must press Play. The main menu has two functions:
	-Play Button: Pressed with the mouse or pressing Intro.(need play)
	-Input Box. where you can write your name or whatever you want.(need play)
 - The scene has a menu in-game, where you can Enables/Disable Vsync, and a crosshair to close the menu. To enable it again, you can press F1.
 - Gameobjects with ui components renders after all 3d objectas has been drawn, then we change the render type to ortho, and swap again when we are done.
 - New Gameobjects created:
	- Button: On, Hover, Off states. When clicked calls an assigned function.
	- Canvas: The parent of all ui objects. Has a debug draw inside. Can be dragged. And all the childs will follow her.
	- Checkbox: Has a gameobject child, with a component image inside. When clicked, his child changes his state. Has a function too, just like button.
	- Font: Stores all the characther inputs in a string and prints it on the screen, using FreeType
 - New Components:
	-Component Rect: Stores all the info of the ui gameobject. Has different settings:
		- Interactive: to enable the handling of input.
		- Set mid canvas: Set at the middle of screen. 
	- Image: Settings to display images in the UI.
		- Full Screen: puts the image with the same size of the viewport.
		- Lock Aspect Ratio of the image to mantain the size of the image.
	- Functions: to assign functions to the UI.
		-Start Game-> Starts Game.
		- VSYNC -> Enables/Disables VSYNC.
		- Close window -> Close UI.
 - Font Importer that load freetype fonts.
 - Fade to use between scenes.