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


def write_custom_properties(object, root):
    # If it only has one property, we're not interested
    if len(obj.keys()) <= 1:
        return
    
    # First item is _RNA_UI
    for propName in [prop for prop in obj.keys() if prop not in '_RNA_UI']:
        XML.SubElement(root, propName).set("value", str(obj[propName]))


# XML root element
root = XML.Element("root")
gameObjects = XML.SubElement(root, "objects")
nextID = 1

# List of previously exported meshes
exportedMeshes = []

# Iterate over all objects in scene
for obj in bpy.context.scene.objects:

    # If the object is on the hidden layer
    if obj.layers[5]:
        continue

    # Create a node for the entity
    entityID = nextID
    nextID += 1
    entity = XML.SubElement(gameObjects, obj.get('TYPE', "willow::Entity"))
    entity.set("ref_id", str(entityID))
    
    # Serialize custom properties
    write_custom_properties(obj, entity)
    
    # Serialize its id, and name
    XML.SubElement(entity, "id").set("value", str(entityID))
    XML.SubElement(entity, "name").set("value", obj.name)
    
    # Serialize its transform
    transformNode = XML.SubElement(entity, "transform")
    
    # Serialize location (swizzled)
    locationNode = XML.SubElement(transformNode, "location")
    XML.SubElement(locationNode, "X").set("value", str(obj.location[1]))
    XML.SubElement(locationNode, "Y").set("value", str(obj.location[2]))
    XML.SubElement(locationNode, "Z").set("value", str(obj.location[0]))
    
    # Serialize rotation (swizzled)
    obj.rotation_mode = 'QUATERNION'
    rotationNode = XML.SubElement(transformNode, "rotation")
    XML.SubElement(rotationNode, "W").set("value", str(-obj.rotation_quaternion[0]))
    XML.SubElement(rotationNode, "X").set("value", str(obj.rotation_quaternion[2]))
    XML.SubElement(rotationNode, "Y").set("value", str(obj.rotation_quaternion[3]))
    XML.SubElement(rotationNode, "Z").set("value", str(obj.rotation_quaternion[1]))
    
    # Serialize scale (swizzled)
    scaleNode = XML.SubElement(transformNode, "scale")
    XML.SubElement(scaleNode, "X").set("value", str(obj.scale[1]))
    XML.SubElement(scaleNode, "Y").set("value", str(obj.scale[2]))
    XML.SubElement(scaleNode, "Z").set("value", str(obj.scale[0]))
    
    # Serialize physics mode
    if obj.game.physics_type == 'SENSOR':
        XML.SubElement(entity, "physics_mode").set("value", "Ghost")
    elif obj.game.physics_type == 'STATIC':
        XML.SubElement(entity, "physics_mode").set("value", "Kinematic")
    elif obj.game.physics_type == 'RIGID_BODY':
        XML.SubElement(entity, "physics_mode").set("value", "Dynamic")
    
    # Special case for Character physics objects: CharacterController
    elif obj.game.physics_type == 'CHARACTER':
        XML.SubElement(entity, "physics_mode").set("value", "Ghost")
        
        # Create a node for the CharacterControllerComponent
        characterControllerID = nextID
        nextID += 1
        characterController = XML.SubElement(gameObjects, "willow::CharacterControllerComponent")
        characterController.set("ref_id", str(characterControllerID))
        
        # Serialize its ID and entity reference
        XML.SubElement(characterController, "id").set("value", str(characterControllerID))
    
    # If the object is a mesh
    if obj.type == 'MESH':
        
        # Create a path for the mesh
        meshPath = "ExportedContent/Meshes/" + obj.data.name + ".wmesh"
        
        # If we haven't exported its mesh yet
        if meshPath not in exportedMeshes:
            # Apply mesh modifiers on the object and export it
            mesh = obj.to_mesh(bpy.context.scene, True, 'PREVIEW')
            export_mesh(mesh, meshPath)
            exportedMeshes.append(meshPath)
            bpy.data.meshes.remove(mesh)
        
        # Create a node for the StaticMeshComponent
        staticMeshID = nextID
        nextID += 1
        staticMesh = XML.SubElement(gameObjects, "willow::StaticMeshComponent")
        staticMesh.set("ref_id", str(staticMeshID))
        
        # Serialize its ID, and entity reference
        XML.SubElement(staticMesh, "id").set("value", str(staticMeshID))
        XML.SubElement(staticMesh, "entity").set("ref", str(entityID))
        
        # Serialize its mesh and material
        XML.SubElement(staticMesh, "mesh").set("value", meshPath)
        XML.SubElement(staticMesh, "material").set("value", "Content/Materials/Sponza.mat")
        
        # Serialize its instance params
        instanceParams = XML.SubElement(staticMesh, "instance_params")
        itemNode = XML.SubElement(instanceParams, "item")
        XML.SubElement(itemNode, "key").set("value", "diffuse")
        valueNode = XML.SubElement(itemNode, "value")
        
        if obj.active_material is not None and obj.active_material.active_texture is not None:
            texPath = obj.active_material.active_texture.image.filepath
            texPath = "Content\\Textures\\" + texPath.split("Textures\\")[1]
            XML.SubElement(valueNode, "willow::ResourceHandle").set("value", texPath)
            
        # Create a node for the StaticMeshColliderComponent
        staticMeshColliderID = nextID
        nextID += 1
        staticMeshCollider = XML.SubElement(gameObjects, "willow::StaticMeshColliderComponent")
        staticMeshCollider.set("ref_id", str(staticMeshColliderID))
        
        # Serialize its ID, and entity reference
        XML.SubElement(staticMeshCollider, "id").set("value", str(staticMeshColliderID))
        XML.SubElement(staticMeshCollider, "entity").set("ref", str(entityID))
        
        # Serialize its mesh
        XML.SubElement(staticMeshCollider, "mesh").set("value", meshPath)
        
    # If the object is a Camera
    if obj.type == 'CAMERA':
        
        # Create a node for the CameraComponent
        cameraID = nextID
        nextID += 1
        camera = XML.SubElement(gameObjects, obj.data.get('TYPE', "willow::CameraComponent"))
        camera.set("ref_id", str(cameraID))
        
        # Serialize ID and entity reference
        XML.SubElement(camera, "id").set("value", str(cameraID))
        XML.SubElement(camera, "entity").set("ref", str(entityID))

# Write next world id
XML.SubElement(root, "next_object_id").set("value", str(nextID))

# Output result
tree = XML.ElementTree(root)
tree.write("ExportedContent/" + bpy.context.scene.world.name + ".xml")
