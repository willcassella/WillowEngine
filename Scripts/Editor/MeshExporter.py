import bpy
import bmesh
import struct
import array

# Target file to save to
target = "C:/Users/Will/Source/WillowEngine/bin/Content/Maps/Sactuary.wmesh"

# Get the active object
active = bpy.context.object
active.update_from_editmode()

# Copy and triangulify it's mesh data
mesh = bmesh.new()
mesh.from_mesh(active.data)
bmesh.ops.triangulate(mesh, faces=mesh.faces)
uvLayer = mesh.loops.layers.uv.active

if uvLayer is None:
    print("No UV data!")

# Create float arrays for vertices and elements
vertices = array.array('f')
#elements = array.array('I')

for face in mesh.faces:
    for loop in face.loops:
        for item in loop.vert.co:  # Position
            vertices.append(item)
        for item in loop[uvLayer].uv:  # uv
            vertices.append(item)
        for item in loop.vert.normal:  # normal
            vertices.append(item)

# Open a file to write to
with open(target, 'wb') as file:
    # Write out vertices
    file.write(struct.pack('I', len(vertices) // 8))
    vertices.tofile(file)
    
    # Write out elements
    #file.write(struct.pack('I', len(elements)))
    #elements.tofile(file)