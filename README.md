# :beers: Brack-Engine

This engine was created as part of the System-Programming minor which took place in the latter half of 2023.  
The engine was designed/build by a team of 5 people.  
The engine architecture mostly adheres to ECS, but due to some of the requirements items like behaviourscripts are also supported. 
A demo game was developed along side of the engine showcasing some of its features.

## Demo Links
- Code - [Brackocalypse](https://github.com/Quintemp99/Brackocalypse)
- Downloadable Game - [itch.io](https://jessemampaey.itch.io/brackocalypse)

## Engine Supported Features 
 - Scene management
 - Multiple camera support(cameras may be different sizes or rotations)
 - Input handling/Events
 - Managing of entities
 - Managing of entities/components
 - Layer support + ordering within the layers
 - Parent/child behaviour between entities(when a parent gets modified, the child is modified accordingly)
 - Persistent entities/components(entities that do not get removed upon scene change)
 - Gamemplay speed management(supported due to a deltaTime multiplier)
 - HUD layer which stays with the camera(Text + Box/Circle drawing)
 - Sprite sheet animations
 - component transformation support, through TransformComponent(scaling, rotation and movement)
 - Generic game save/load
 - Music(start, stop, pause)
 - Fire and forget audio
 - AI(pathfinding over a by the game dev specified graph, A* is provided out of the box)
 - Physics(includes, collision detection/handling for box and circle colliders, gravity, friction, mass)
 - Particles(supportes modifying of the lifetime, size, color, emit interval, max amount of particles, speed of said particles, order in layer and optional sprite path)
 - Replay(supports starting/stopping recording, and playing back a recording)
