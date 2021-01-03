# Godex bench test

This repository is used to test the Godex performances.

### Compile the bench test
To execute this test follow the following instructions.

##### 1. Clone this repository:
```
git clone https://github.com/AndreaCatania/godex_tests.git 
```

##### 2. Clone the submodules
The following commands will clone _Godot_ and _Godex_
```
git submodule update --init --recursive
```

##### 3. Apply Godex patch at Godot
First go to Godot directory
```
cd source/godot/
```

Now apply the godex patch to Godot
```
git apply ../modules/godex/patches/add_custom_iterator.patch
```

##### 4. Compile
Godot is now ready, let's compile it:
```
# Linux
scons p=linuxbsd target=release_debug -j8 custom_modules=../modules
```

##### 5. Launch Godot editor
Once the compilation is done, you can simply launch the Editor with the following command:
```
./bin/godot.linuxbsd.opt.tools.64 --path ../../../game -e --single-window
```
At this point, the editor with the test is open and ready.


### Testing and considerations.
The project is setup to do a direct comparison of `Node` vs `Entities` performances. When you launch the project (by hitting F5 on the editor) `20000` `Nodes` will be added to the scene; half of them are _Debris_ that fly around the center, the other half are squares that are teleported to a random location each frame.

Open the script `World.gd`, you will have a script like this:
```gdscript
func _ready():

	# Spawn ECS entities
	var godex = false
	# Element to spawn
	var spawn_count = 10000

	# The spawned element uses or not use the mesh. 
	var no_mesh = false

	# Want to spawn debris
	var debris = true
	# Want to spawn random transform
	var random_transform = true

	for i in range(spawn_count):
		if godex == false:
			if debris:
				spawn_node_debris(...)
			if random_transform:
				spawn_node_random_transform(...)

		else:
			if debris:
				spawn_entity_debris(...)
			if random_transform:
				spawn_entity_random_transform(...)
```
You can tweak the above variables to spawn `Entities` instead of `Nodes`, change the amount of elements spawned.
**Note 1:** The default `spawn_count` number maybe too much or too low for you CPU, so tweak it accordingly.
**Note 2:** To see the performances, while the game is running, open the `Debugger > Monitors` and check the framerate. _This is really naive, but it's enough for now._

##### Considerations
The `Node`s and the `Entities` are doing exactly the same thing, but in different ways (check _modules/test_nodes_and_systems_).
On my machine the difference between `Node` and `Entities` is just about 30% in favor of `Entities`; however, this just because the _Rendering_ is a bottleneck.

If you really want to compare only the `Node` processing and the `Entity` processing, you have to set the parameter `var no_mesh = false` to `true`.
In this way will spawn `Node`s / `Entities` without meshes, so the rendering will not run. The performance gain will be order of magnitude more, just give it a check.
For example: with `Godex` my machine can handle 1'000'000 `Entities` (no meshes) with a frame rate of 30FPS; while it can handle at max only 220'000 `Nodes` at same frame rate. _Note, this is in single thread and Godex will automatically run this in multiple threads, once the feature is implemented._

As soon as you start introducing bottlenecks, the performance gain decreases. However, the gameplay code performs all the logic without dealing with rendering, so such part is still optimized anyway. The gameplay systems will be executed automatically in multiple threads, (a thing that can't be achieved with OO scripts) improving even more the performances.

By reducing the resource cost for the gameplay code, you will be able to increase the amount of data processed; or if you are working on a multiplayer game it's possible to lower the server costs (since, only the gameplay code runs on the server).

Also, probably, in future the slow parts like the rendering or the physics, will perform their operations with more cache friendly code (or even using ECS [so these would even use multiple threads efficiently]) so the current bottlenecks will be removed and the amount of elements on the screen is increased.
