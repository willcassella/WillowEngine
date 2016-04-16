import bpy
import xml.etree.ElementTree as XML

cube = bpy.context.scene.objects.active
anim = cube.animation_data.action
frameRange = anim.frame_range

root = XML.Element("root")
animNode = XML.SubElement(root, str(anim.name))

frame = frameRange[0]
while (frame < frameRange[1]):
    frameNode = XML.SubElement(animNode, "Frame")
    frameNode.set("time", str(frame))
    frameNode.set("x", str(anim.fcurves[0].evaluate(frame)))
    frameNode.set("y", str(anim.fcurves[1].evaluate(frame)))
    frameNode.set("z", str(anim.fcurves[2].evaluate(frame)))
    frame += 1

# Output result
tree = XML.ElementTree(root)
tree.write("C:/Users/Will/Downloads/Animation.xml")
