bl_info = {
    "name": "Level Exporter",
    "category": "Willow Engine",
}

import bpy
import xml.etree.ElementTree as XML

class LevelExporter(bpy.types.Operator):
    """Willow Engine level exporter"""
    bl_idname = "object.export_level"
    bl_label = "Level Exporter"
    bl_options = {'REGISTER', 'UNDO'}

    file = bpy.props.StringProperty(name="Output File", default="C:/Users/Will/Downloads/LevelExportTest.xml")

    def execute(self, context):
        root = XML.Element("root")
        world = XML.SubElement(root, "World")
        scene = context.scene
        nextID = 1

        for obj in scene.objects:
            # Create an XML node for this object, and add its name and ID
            xmlObj = XML.SubElement(world, "Entity")
            XML.SubElement(xmlObj, "ID").set("value", str(nextID))
            XML.SubElement(xmlObj, "Name").set("value", str(obj.name))
            
            # Serialize the object's transform
            transform = XML.SubElement(xmlObj, "Transform")
            
            # Serialize its location
            location = XML.SubElement(transform, "Location")
            XML.SubElement(location, "X").set("value", str(obj.location.x))
            XML.SubElement(location, "Y").set("value", str(obj.location.y))
            XML.SubElement(location, "Z").set("value", str(obj.location.z))
            
        # Output result
        tree = XML.ElementTree(root)
        tree.write(str(self.file))
        return {'FINISHED'}

def menu_func(self, context):
    self.layout.operator(LevelExporter.bl_idname)

def register():
    bpy.utils.register_class(LevelExporter)
    bpy.types.VIEW3D_MT_object.append(menu_func)

def unregister():
    bpy.types.VIEW3D_MT_object.remove(menu_func)
    bpy.utils.unregister_class(LevelExporter)

if __name__ == "__main__":
    register()
