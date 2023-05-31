#include <gtest/gtest.h>
#include "Circle.h"
#include "pugixml.hpp"
#include "Group.h"

TEST(TestReadXML, TestCircle) {

    std::string s = R"( <?xml version = "1.0"?>
    <Circle label="testCircle" x="5" y="6" r="7" color="Black"/>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description();
    pugi::xml_node node = doc.child("Circle");
    Circle c(node);
    std::string c_dump_ref = R"(Circle "testCircle", x: 5, y: 6, r: 7, color: "Black")";
    EXPECT_EQ(c.dump(),c_dump_ref);
}

TEST(TestAnalyseXML, TestGroup) {
    std::string g_dump_ref = R"(Group "testGroup", x: 0, y: 1, children: [
|  Circle "testCircle1", x: 2, y: 3, r: 4, color: "Black"
|  Circle "testCircle2", x: 5, y: 6, r: 7, color: "Black"
])";

    std::string s = R"( <?xml version = "1.0"?>
        <Group label="testGroup" x="0" y="1">
          <Circle label="testCircle1" x="2" y="3" r="4" color="Black"/>
          <Circle label="testCircle2" x="5" y="6" r="7" color="Black"/>
        </Group>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());

    ASSERT_TRUE(result) << result.description();

    pugi::xml_node node = doc.child("Group");
    Group g(node);
    EXPECT_EQ(g.dump(),g_dump_ref);
}

TEST(TestReadXML, TestGroupHybrid) {
    std::string s = R"( <?xml version = "1.0"?>
        <Group label="testGroupHybrid" x="0" y="1">
             <Circle label="testCircle" x="2" y="3" r="4" color="Black"/>
             <Group label="testGroup" x="5" y="6"/>
        </Group> )";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description();
    pugi::xml_node node = doc.child("Group");
    Group g(node);
    std::string gh_dump_ref = R"(Group "testGroupHybrid", x: 0, y: 1, children: [
|  Circle "testCircle", x: 2, y: 3, r: 4, color: "Black"
|  Group "testGroup", x: 5, y: 6, children: [
]
])";
    EXPECT_EQ(g.dump(),gh_dump_ref);
}