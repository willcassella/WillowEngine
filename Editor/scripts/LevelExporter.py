# LevelExporter.py

import bpy
import bmesh
import struct
import array
import xml.etree.ElementTree as XML

def export_mesh(data, path):
    
    # Copy and triangulify it's mesh data
    mesh = bmesh.new()
    mesh.from_mesh(data)
    bmesh.ops.triangulate(mesh, faces=mesh.faces)
    uvLayer = mesh.loops.layers.uv.active

    # Create float arrays for vertices and elements
    vertices = array.array('f')
    
    for face in mesh.faces:
        for loop in face.loops:
            # Serialize position (swizzled)
            vertices.append(loop.vert.co[1])
            vertices.append(loop.vert.co[2])
            vertices.append(loop.vert.co[0])
            
            # Serialize UV
            if uvLayer is not None:
                vertices.append(loop[uvLayer].uv[0])
                vertices.append(loop[uvLayer].uv[1])
            else:
                vertices.append(0)
                vertices.append(0)
            
            # Serialize normal (swizzled)
            vertices.append(loop.vert.normal[1])
            vertices.append(loop.vert.normal[2])
            vertices.append(loop.vert.normal[0])

    # Open a file to write to
    with open(path, 'wb') as file:
        # Write out vertices
        file.write(struct.pack('I', len(vertices) // 8))
        vertices.tofile(file)

# First, apply modifiers to all objects
for obj in bpy.data.objects:
    for mod in obj.modifiers:
        bpy.ops.object.modifier_apply(modifier=mod.name, apply_as='DATA')

# XML root element
root = XML.Element("root")
gameObjects = XML.SubElement(root, "GameObjects")
nextID = 1

# List of previously exported meshes
exportedMeshes = []

# Iterate over all objects in scene
for obj in bpy.data.objects:

    # If the object is on the hidden layer
    if obj.layers[5]:
        continue

    # Create a node for the entity
    entityID = nextID
    nextID += 1
    entity = XML.SubElement(gameObjects, obj.get('TYPE', "Willow::Entity"))
    entity.set("refID", str(entityID))
    
    # Serialize its id, and name
    XML.SubElement(entity, "ID").set("value", str(entityID))
    XML.SubElement(entity, "Name").set("value", obj.name)
    
    # Serialize its transform
    transformNode = XML.SubElement(entity, "Transform")
    
    # Serialize location (swizzled)
    locationNode = XML.SubElement(transformNode, "Location")
    XML.SubElement(locationNode, "X").set("value", str(obj.location[1]))
    XML.SubElement(locationNode, "Y").set("value", str(obj.location[2]))
    XML.SubElement(locationNode, "Z").set("value", str(obj.location[0]))
    
    # Serialize rotation (swizzled)
    obj.rotation_mode = 'QUATERNION'
    rotationNode = XML.SubElement(transformNode, "Rotation")
    XML.SubElement(rotationNode, "W").set("value", str(obj.rotation_quaternion[0]))
    XML.SubElement(rotationNode, "X").set("value", str(-obj.rotation_quaternion[2]))
    XML.SubElement(rotationNode, "Y").set("value", str(obj.rotation_quaternion[3]))
    XML.SubElement(rotationNode, "Z").set("value", str(obj.rotation_quaternion[1]))
    
    # Serialize scale (swizzled)
    scaleNode = XML.SubElement(transformNode, "Scale")
    XML.SubElement(scaleNode, "X").set("value", str(obj.scale[1]))
    XML.SubElement(scaleNode, "Y").set("value", str(obj.scale[2]))
    XML.SubElement(scaleNode, "Z").set("value", str(obj.scale[0]))
    
    # Serialize physics mode
    if obj.game.physics_type == 'SENSOR':
        XML.SubElement(entity, "PhysicsMode").set("value", "Ghost")
    elif obj.game.physics_type == 'STATIC':
        XML.SubElement(entity, "PhysicsMode").set("value", "Kinematic")
    elif obj.game.physics_type == 'RIGID_BODY':
        XML.SubElement(entity, "PhysicsMode").set("value", "Dynamic")
    
    # If the object is a mesh
    if obj.type == 'MESH':
        
        # Create a path for the mesh
        meshPath = "Meshes/" + obj.data.name + ".wmesh"
        
        # If we haven't exported its mesh yet
        if meshPath not in exportedMeshes:
            export_mesh(obj.data, meshPath)
            exportedMeshes.append(meshPath)
        
        # Create a node for the StaticMeshComponent
        staticMeshID = nextID
        nextID += 1
        staticMesh = XML.SubElement(gameObjects, "Willow::StaticMeshComponent")
        staticMesh.set("refID", str(staticMeshID))
        
        # Serialize its ID, and entity reference
        XML.SubElement(staticMesh, "ID").set("value", str(staticMeshID))
        XML.SubElement(staticMesh, "Entity").set("ref", str(entityID))
        
        # Serialize its mesh and material
        XML.SubElement(staticMesh, "Mesh").set("value", meshPath)
        XML.SubElement(staticMesh, "Material").set("value", "Content/Materials/Sponza.mat")
        
        # Serialize its instance params
        instanceParams = XML.SubElement(staticMesh, "InstanceParams")
        itemNode = XML.SubElement(instanceParams, "item")
        XML.SubElement(itemNode, "key").set("value", "diffuse")
        valueNode = XML.SubElement(itemNode, "value")
        XML.SubElement(valueNode, "Willow::AssetPtr").set("value", obj.active_material.active_texture.image.filepath[2:])
        
        # Create a node for the StaticMeshColliderComponent
        staticMeshColliderID = nextID
        nextID += 1
        staticMeshCollider = XML.SubElement(gameObjects, "Willow::StaticMeshColliderComponent")
        staticMeshCollider.set("refID", str(staticMeshColliderID))
        
        # Serialize its ID, and entity reference
        XML.SubElement(staticMeshCollider, "ID").set("value", str(staticMeshColliderID))
        XML.SubElement(staticMeshCollider, "Entity").set("ref", str(entityID))
        
        # Serialize its mesh
        XML.SubElement(staticMeshCollider, "Mesh").set("value", meshPath)
        
    # If the object is a Camera
    if obj.type == 'CAMERA':
        
        # Create a node for the CameraComponent
        cameraID = nextID
        nextID += 1
        camera = XML.SubElement(gameObjects, obj.data.get('TYPE', "Willow::CameraComponent"))
        camera.set("refID", str(cameraID))
        
        # Serialize ID and entity reference
        XML.SubElement(camera, "ID").set("value", str(cameraID))
        XML.SubElement(camera, "Entity").set("ref", str(entityID))

# Write next world id
XML.SubElement(root, "NextID").set("value", str(nextID))

# Output result
tree = XML.ElementTree(root)
tree.write("sanctuary.xml")
