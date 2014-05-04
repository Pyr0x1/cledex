cledex
======

A simple Linux command line pokédex written in C.

<a href="http://it.tinypic.com?ref=15ea684" target="_blank"><img src="http://i60.tinypic.com/15ea684.png" border="0" alt="sample"></a>

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

cledex [-l language] "pokemon name"  

(note: currently only japanese, french, german, spanish, italian and english language are fully supported)

**eg.**   
```bash
cledex alakazam  
```
```bash
cledex "lucario mega"  
```
```bash
cledex -l it charizard  
```

Partial search is supported, so you can use "%" or "*" to find partial matches  

**eg.**  
```bash
cledex charm%  
```
finds Charmander and Charmeleon
```bash
cledex *eon
```
finds Charmeleon, Vaporeon, Jolteon, Flareon, ..

Output
======

A list of pokémon with following format
<pre>
--------------------

	[ID]	Name		Type 1 / Type 2
	
			Ability 1     
			Ability 2
			Ability 3
	
			PS: value
			Atk: value
			Def: value
			SpAtk: value
			SpDef: value
			Speed: value
	
			Egg Group 1
			Egg Group 2

--------------------
</pre>
