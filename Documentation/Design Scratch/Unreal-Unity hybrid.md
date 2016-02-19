*Entity* - discreet object in the game world  
*Component* - Piece of data attached to an Entity  
*Actor* - Group of Entities, representing a single "Actor"  

Ideally I'd like the 'Entity' type to be as invisible as possible (only deal with Components). Maybe it won't even exist in code at all.  
Components should feel like full objects themselves.

Component types:
- StaticMeshComponent
- SkinnedMeshComponent
- LightComponent
- SpriteComponent
- ParticleComponent
- AudioComponent
- BoxColliderComponent
- CapsuleColliderComponent
- SphereColliderComponent
- MeshColliderComponent
- RigidBodyComponent
- SoftBodyComponent
- HingeConstraintComponent

Also the API needs to remain as simple as possible. It should still feel like the same parent-child hierarchy, with the addition of "siblings"

*Attach* - Adds the given type/object as a child  
*Connect* - Adds the given type/object as a sibling  
*SetParent* - Sets the given object as a parent  

Should you be able to move siblings to other objects?  
For now I'm going to wait until a real use case for that develops

`T& Component::Attach<T>(...)` - Attaches a new entity with the given component type as a child  
`T& Component::Connect<T>(...)` - Connects a new instance of the given Component to this Component's entity  
`auto Component::EnumerateChildren()` - Iterates over child Entities  
`auto Component::EnumerateConnected()` - Iterates over connected Components

Result?
- Better seperation of responsibility
- Components can have a stronger relationship than just parent-child (though admittedly I'm not clear on what a good use case for this is yet)  
- Complicates concepts and API, still not sure if this is the right way to go
