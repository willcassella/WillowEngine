import bpy
import struct
import array

path = "C:/Users/Will/Downloads/test.wanim"
object = bpy.context.scene.objects.active
anim = object.animation_data.action
frameRange = anim.frame_range

xPosFrames = array.array('f')
yPosFrames = array.array('f')
zPosFrames = array.array('f')

frame = frameRange[0]
while (frame < frameRange[1]):
    xPosFrames.append(anim.fcurves[1].evaluate(frame))
    yPosFrames.append(anim.fcurves[2].evaluate(frame))
    zPosFrames.append(anim.fcurves[0].evaluate(frame))
    frame += 1

# Output result
with open(path, 'wb') as file:
    # Write number of frames
    file.write(struct.pack('I', len(xPosFrames)))
    
    # Write x frames
    file.write(struct.pack('B', 1))
    xPosFrames.tofile(file)
    
    # Write y frames
    file.write(struct.pack('B', 1))
    yPosFrames.tofile(file)
    
    # Write z frames
    file.write(struct.pack('B', 1))
    zPosFrames.tofile(file)
