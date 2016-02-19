C++ is pretty great, but there are some ways I wish it were better

Things I like:
- Control over memory (RAII)
- Templates (syntax could be nicer though, esoteric rules would be better off as real features)
- Free functions (why don't more languages have this?)

Things I don't like about C++:
- Manual memory managment may be pretty easy, but I still don't sleep well at night
- Having some sort of rust-style ownership stuff would be great (and having it WELL INTEGRATED)
- A few aesthetic things kind of bother me (array syntax, semicolons after classes, non-public inheritance, etc etc)

Also having real "Interface" types would be great, that plus Mixins would remove the need for multiple inheritance

If C++ had real support for modules, a lot of things could be much simpler
- Componetization
- Friendship (same module = automatically friends)
- Compile-time reflection (able to iterate over types defined in module)

Another cool feature would be attributes
- Currently only certain attributes are supported, defined by standard. What if you could create your own?
- `[[identifer(args...{optional})]]` where 'identifier' identifies a constexpr function accepting
a template argument of the thing the attribute is applied to (may be type, function, or member)  

		namespace Attributes
		{
			template <Member M>
			constexpr void Transient()
			{
				// Do something	
			}
			
			template <MemberFunction F>
			constexpr void Deprecate(string message)
			{
				static_warning(true, message);	
			}
			
			template <typename T>
			constexpr void Serializable()
			{
				// Do something	
			}
		}
		
		[[Attributes::Serializable]]
		struct T
		{
			[[Attributes::Transient]]
			float Value;
			
			[[Attributes::Deprecate("Don't use this!")]]
			int Add(int a, int b);
		};
