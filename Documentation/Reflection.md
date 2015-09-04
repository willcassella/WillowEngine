# Reflection

The engine uses a solution for reflection that operates entirely within the language - no preprocessor or special tools are needed.

Reflection in the engine serves several purposes:
- Automated serialization behavior
- Automated GUI behavior
- Safe and efficient down/side casting (without resorting to `dynamic_cast`)

## Reflection Classes

The engine defines several classes that contain reflection information, all defined in the Core module.
- TypeInfo (abstract base for all following classes)
- VoidInfo (describes 'void')
- PrimitiveInfo (describes primitives, and base for 'PointerInfo' and 'EnumInfo')
- PointerInfo (describes pointers. References are not recognized by the reflection system)
- EnumInfo (describes enums, providing a map associating a name to a value)
- CompoundInfo (abstract base for ClassInfo/StructInfo/InterfaceInfo)
- StructInfo (describes non-polymorphic types in the engine)
- ClassInfo (describes polymorphic types in the engine)
- InterfaceInfo (describes purely polymorphic types in the engine)

Some of these types can be extended to define additional runtime type information, such as "AssetInfo" in the Resource module.

## Reflecting your own types

Registering reflection data is very straighforward, provided your type follows the rhyme:

- If it is a Struct, it's `final` and has no bases, other than a Contract in some special cases.
- If it's a Class, it extends the "Object" class, as well as Interfaces (which add no mass*).
- If it's an Interface, it extends "Interface" and only contains a pointer to its vtable (otherwise inheritance would be unstable).

*Interfaces do add an additional vtable pointer, but whatever. It took me a while to come up with that.

### Classes

Use the following macros in the "Information" section of the class's definition:
```
REFLECTABLE_CLASS
EXTENDS(base)
IMPLEMENTS(interfaces...)
```

If your class does not implement any interfaces (excluding inherited interfaces), the `IMPLEMENTS` macro may be omitted.

Then you must use the following macro in the source file for the class:
```
BUILD_REFLECTION(class)
// Describe the class here
;
```

Describing classes is detailed below.

### Structs

Use the following macro in the "Information" section of the struct's definition:
```
REFLECTABLE_STRUCT
```

Then you must use the following macro in the source file for the struct:
```
BUILD_REFLECTION(struct)
// Describe the struct here
;
```

Describing structs is detailed below.

### Interfaces

Use the following macro in the "Information section of the interface's definition:
```
REFLECTABLE_INTERFACE
```

Then you must use the following macro in the source file for the interface:
```
BUILD_REFLECTION(interface)
// Describe the interface here
;
```

Describing interfaces is detailed below.

### Enums

Use the following macro in same header as the enum (or wherever I guess, it just has to be in the global namespace):
```
REFLECTABLE_ENUM(e)
```

Then in the source file for the enum, use the following macro:
```
BUILD_ENUM_REFLECTION(e)
// Describe the enum here
;
```

You may use the `.AddValue("Name", "Description", Value)` method to register values for the enum. Additionally, you may use `.IsBitFlag()` to indicate that an instance of this enum may be composed of multiple values, as is the case for bit flags.

### Describing Classes, Structs, and Interfaces

Classes, Interfaces, and Structs are all considered "Compounds" (in the sense that that are composed of multiple other types). You may describe properties on the type, via the following methods:
- `.AddProperty("Name", "Description", &T::Field, [optional]Flags)` - Creates a field property
- `.AddProperty("Name", "Description", &T::Field, nullptr, [optional]Flags)` - Creates a read-only property pointing to a field
- `.AddProperty("Name", "Description", &T::Field, &T::Setter, [optional]Flags)` - Creates a property that gets via a field, and sets via a method.
- `.AddProperty("Name", "Description", &T::Getter, nullptr, [optional]Flags)` - Creates a read-only property that gets via a method.
- `.AddProperty("Name", "Description", &T::Getter, &T::Setter, [optional]Flags)` - Creates a property that gets via a method, and sets via a method.

In the case of structs you may also use `.IsStable()` to indicate that layout of this struct will never change. This is used to optmize some part of serialization, but should be used *very cautiously*.

That's pretty much it. There's a few more intricacies to how all this works, but for the most part you don't really need to deal with those, and you'd be better off looking at the source anyway.
