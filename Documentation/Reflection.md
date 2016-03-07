# Reflection

The engine uses a solution for reflection that operates entirely within the language - no preprocessor or special tools are needed.

Reflection in the engine serves several purposes:
- Automated serialization behavior
- Automated GUI behavior
- Safe and efficient down/side casting (without resorting to `dynamic_cast`)

## Basic usage

To get the reflection data for a type, use `TypeOf<T>()`. The returned reference will be of the exact type of reflection class (listed below) for `T`. So if you call `TypeOf<int*>()`, it will return a `const PointerInfo&`.  

To get the reflection data for an instance, use `TypeOf(x)`. The returned reference will be of the most specific type of reflection class that can be deduced at compile time for `x`.

Additionally, you may use `.GetType()` on an instance if you are sure that the type directly supports reflection (as is the case for Object types, and most structs).

To safely attempt to cast a value, use `Cast<TargetT>(x)`, which will return a pointer to `TargetT` with the same const qualification as `x`. If the type is not castable, this returns a null pointer. Note that this only works for types that are bitwise compatible with one another, so attempting to cast an `int` to a `float` will not work.

## Reflection Classes

The Core module defines several types of reflection data:
- TypeInfo (abstract base for all reflection classes)
- VoidInfo
- PrimitiveInfo
- PointerInfo (extends 'PrimitiveInfo')
- EnumInfo (extends 'PrimitiveInfo')
- CompoundInfo (abstract base for ClassInfo/StructInfo/InterfaceInfo)
- StructInfo (describes non-polymorphic types in the engine)
- ClassInfo (describes polymorphic types in the engine)
- InterfaceInfo (describes purely polymorphic types in the engine)

Some of these types can be extended to define additional runtime type information, such as "AssetInfo" in the Resource module.

## Reflecting your own types

Reflecting your own types is very easy, as long as your type fits one of categories below.

### Classes

"Classes" are defined as any polymorphic type that extends "Object" (directly, or indirectly). They are single-inheritance only.

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

Structs are non-polymorphic types. They should be marked as "final" and not inherit from any classes, though there are some exceptions.

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

Interfaces are purely-polymorphic types that extend "Interface". They may not have any members. Interfaces are *always* implemented by classes, so the `GetType` method returns a `ClassInfo` reference.

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

Use the following macro in same header as the enum, at global scope:
```
REFLECTABLE_ENUM(api, e)
```
Where 'api' is the API macro for the module the enum is part of, and 'e' is the enum to be reflected. If the enum is part of a template (and therefor has no canonical 'module'), you may use the NO_API macro. In the source file for the enum (or any source file in the same module, or the header file in the case of template enums), use the following macro:
```
BUILD_ENUM_REFLECTION(e)
// Describe the enum here
;
```

You may use the `.Value("Name", Value, [optional]"Description")` method to register values for the enum. Additionally, you may use `.IsBitFlag()` to indicate that an instance of this enum may be composed of multiple values, as is the case for bit flags.

### Describing Classes, Structs, and Interfaces

Classes, Interfaces, and Structs are all considered "Compounds" (in the sense that that are composed of multiple other types). You can describe Properties, Fields, and Data via the following methods:
- `.Property("Name", Getter, Setter, [optional]"Description", [optional]"Category", [optional]Flags)` - Registers a property that uses the given getter and setter. If 'nullptr' is provided as the setter, the property is considered read-only.
- `.Data("Name", Field, [optional]Flags)` - Registers a data member. Data members form the private interface of the type, and may only be actual fields.
- `.Field("Name", Field, [optional]"Description", [optional]"Category", [optional]Flags)` - Registers both a property and a data member that gets and sets with the given field.

In the case of structs you may also use `.IsStable()` to indicate that layout of this struct will never change. This is used to optimize some part of serialization, but should be used *very cautiously*, as changes to the layout will make this struct incompatible with old archives.

The reflection system will pick up on the default constructor for a type - if one exists - and allow for it to be invoked dynamically at runtime. If your type is not default-constructible but you still wish for it to be dynamically constructible, you may implement a constructor that accepts a `DynamicInitializer` object.

That's pretty much it. There's a few more intricacies to how all this works, but for the most part you don't really need to deal with those, and you'd be better off looking at the source anyway.
