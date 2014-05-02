cledex
======

A simple Linux command line pokedex written in C.

<a href="http://it.tinypic.com?ref=zjwfic" target="_blank"><img src="http://i58.tinypic.com/zjwfic.png" border="0" alt="Image and video hosting by TinyPic"></a>

Thanks to Veekun for the great database: https://github.com/veekun/pokedex.

"This is all the intellectual property of Nintendo, Creatures, inc., and GAME FREAK, inc. and is protected by various copyrights and trademarks. The author believes that the use of this intellectual property for a fan reference is covered by fair use and that the software is significantly impaired without said property included. Any use of this copyrighted property is at your own legal risk."


Installation
======

Pretty classic:

* cd src
* make
* make install (be root)

To uninstall:

* make uninstall (be root)

Usage
======

cledex "pokemon name"

eg.   
cledex alakazam  
cledex "lucario mega"  

Partial search is now supported, so you can use "%" to find partial matches  

eg.  
cledex charm% -> finds Charmander and Charmeleon  
cledex %eon -> finds Charmeleon, Vaporeon, Jolteon, Flareon, ...  
