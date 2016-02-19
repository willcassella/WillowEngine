GameObjects have different usages in the scene:
- Some have high degrees of behavior
 - Don't need to be persistent (cars, peds in a GTA-like game)
 - Have very short lifetimes (bullets, explosions)
 - Need to be persistent (item player drops in an RPG, must persist even if player leaves for a bit)
 - Need to be persistent, as well as maintaining behavior (NPC, may travel somewhere else while player is gone, or appear based on schedule)

- Others have little behavior
 - Bits of trash rolling around in scene, may be dropped and respawned once player leaves area
 - Static objects in scene, basically exist just so that the player can bump into them
 
One potential solution would be to use "Behaviors" to indicate this sort of thing
- GameObjects have behaviors, and as long as the behaviors still exist, the GameObject still exists

 
 Components just define the the presentation level of a GameObject
 - If components are not attached to a GameObject, they are considered orphaned, and will not persist
 (eg, a Bullet may leave a DecalComponent on a wall, but that Component does not have an owning GameObject)
 - Non-persistent GameObjects may also be cleaned up when the scene becomes too crowded
 
 Behaviors are consulted on what to do when a GameObject is leaving the scene
 - InventoryBehaviors don't care
 - AIBehavior might, depending on settings
 
Components have IDs, but those only uniquely identify the Component within a specific GameObject
- If the Component does not have an owning GameObject, then its ID is 0
 
 So Components are persistent as long as they have an attached GameObject (otherwise, they may only persist
 if they are part of the map)
 
 GameObjects have variable persistence
 Behaviors are as persistent as the GameObject they are attached to (but they can influence the persistance of
 the GameObject)
 
 So at the end of the day, GameObjects determine Persistence (for the sake of being conservative, orphaned componets
 are considered to not be persistent)
 
 While there are obvious downsides to this, I like this system because it strikes a nice balance between automatic
 management, and feeling too "magical"
 - Bad code is still bad code, no point in trying to allow it to work
 