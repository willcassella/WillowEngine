// ResourceLoader.cpp

#include <rapidxml.hpp>
#include <string>

char test[] =
"<scene name=\"Simple Scene\">"
"	<GameObject name=\"sponza\">"
"		<transform>"
"			<position x=\"4\" y=\"3\">"
"		</transform>"
"	</GameObject>"
"</scene>\0";

using namespace rapidxml;

void loadScene()
{
	xml_document<> doc;
	doc.parse<0>( test );
}