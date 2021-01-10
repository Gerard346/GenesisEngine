## Welcome to GitHub Pages

This is my website about a 3D engine I've made for the University for the Videogame's engine assignment. This engine is not entirely made by me, props to Marc Pagès Francesh, link for his Github -> https://github.com/marcpages2020/GenesisEngine. I've focus on doing the UI sub-system.

To load the scene for this Assignment just go to file->load->scenes->main_menu.

### Team

Gerard Gil->Everything from here https://github.com/Gerard346/GenesisEngine/commit/2a75ba8a97494f467f8d46a29975607bc5f8c864.
Marc Pagès Francesh -> Everything from before.

# UI Sub System
## Main core Sub Systems
- Function: Stores all the functions that our UI elements will use.
- Font Importer: Used to load .ttf fonts and creates textures from the fonts.
- Module UI: Sets the render at Ortho and swaps again for prespective.
- Fade: Fade used between screens.
- UI Game Objects:
    - Button: 3 stats: Button On, Button Hover and Button Off, has a texture, stores position printed in the window and has a function to call when                       pressed.
    - Canvas: Parent of all the UI elements.
    - Checkbox: Like the button, with one child.
    - Image: Prints a texture.
    - RectTransform: Stores all the info about our UI elements; position, visibility, interactive, stay on mid,...
    - Text: Stores the string that will be printed.
    
## Core Sub Systems explained
- Function: Stores all the functions that our UI elements will use.
- Font Importer: Used to load .ttf fonts and creates textures from the fonts.
- Module UI: Sets the render at Ortho and swaps again for prespective.
- Fade: Fade used between screens.
- UI Game Objects:
    - Button: 3 stats: Button On, Button Hover and Button Off, has a texture, stores position printed in the window and has a function to call when                       pressed.
    - Canvas: Parent of all the UI elements.
    - Checkbox: Like the button, with one child.
    - Image: Prints a texture.
    - RectTransform: Stores all the info about our UI elements; position, visibility, interactive, stay on mid,...
    - Text: Stores the string that will be printed.
    
## Link to Release

https://github.com/Gerard346/GenesisEngine/releases/tag/v0.99

https://github.com/Gerard346/GenesisEngine

## License

MIT License

Copyright (c) 2020 Gerard Gil Calvo & Marc Pagès Francesh

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files Genesis Engine, to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
