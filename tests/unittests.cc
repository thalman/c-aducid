#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "definitions.h"
#include "myxml.h"

char const *XMLExample = "<?xml version='1.0' encoding='UTF-8'?><soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\">\n"
"<soapenv:Body><ns1:AIMgetPSLAttributesResponse xmlns:ns1=\"http://iface.aducid.com\">\n"
"<statusAIM>active</statusAIM>\n"
"<statusAuth>OK</statusAuth>\n"
"<singleAttributeExample param1=\"present\" />"
"<operationName>exuse</operationName>\n"
"<userDatabaseIndex>1626953714</userDatabaseIndex>\n"
"<userId>D4ubaZ4O4II=</userId>\n"
"<validityCount xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:type=\"ns1:unlimitedTokenType\">unlimited</validityCount>\n"
"<validityTime xmlns:s332=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:type=\"s332:long\">63108813</validityTime>\n"
"<expirationCountdownUses xmlns:s333=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
"  xsi:type=\"s333:int\">0</expirationCountdownUses>\n"
"<expirationCountdownTime xmlns:s334=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
"  xsi:type=\"s334:long\">60430413</expirationCountdownTime>\n"
"<securityProfileName>AIM UCP-business-LAC</securityProfileName>\n"
"<authenticationProtocolName>UCP</authenticationProtocolName>\n"
"<securityLevel>LAC</securityLevel>\n"
"<personalObject>\n"
"<personalObjectName>payment</personalObjectName>\n"
"<personalObjectTypeName>payment</personalObjectTypeName>\n"
"<personalObjectAlgorithmName>PAYMENT</personalObjectAlgorithmName>\n"
"  <personalObjectAttribute ns1:attributeName=\"PaymentMessage\">\n"
"    <attributeValue xmlns:s335=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:s336=\"http://www.w3.org/2001/XMLSchema\"\n"
"    s335:type=\"s336:string\">too+yellow+horse</attributeValue>\n"
"  </personalObjectAttribute>\n"
"  <personalObjectAttribute ns1:attributeName=\"Return_Status\">\n"
"    <attributeValue xmlns:s337=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:s338=\"http://www.w3.org/2001/XMLSchema\"\n"
"    s337:type=\"s338:string\">ConfirmedByUser</attributeValue>\n"
"  </personalObjectAttribute>\n"
"  <personalObjectAttribute ns1:attributeName=\"PoPar##ObjectName\">\n"
"    <attributeValue xmlns:s339=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:s340=\"http://www.w3.org/2001/XMLSchema\""
"    s339:type=\"s340:string\">payment</attributeValue>\n"
"  </personalObjectAttribute>\n"
"  <personalObjectAttribute ns1:attributeName=\"PaymentSignature\">\n"
"    <attributeValue xmlns:s341=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:s342=\"http://www.w3.org/2001/XMLSchema\""
"    s341:type=\"s342:string\">t4vMYG5F1vG3/5WknYgqtfT0m5iJgp4gkHiXlB9bERLedUMLDnP4QPgiyVygEMmoQP8KEVmGkOS5iAoB+g7qoWIB5n1EFHiQD/oMpWkKM1t0wI+AXsBJvnAqDQ4Mdl9vZxrcQDJv8HrHpbvLNireQfHUX9BXP5laZTBVkeE4rwA=</attributeValue>\n"
"  </personalObjectAttribute>\n"
"</personalObject>\n"
"<authKey2>3BcKXWYnhLA=</authKey2>\n"
"</ns1:AIMgetPSLAttributesResponse>\n"
"</soapenv:Body></soapenv:Envelope>\n";

TEST_CASE( "simplified xml parsed", "[xml][single node]") {
    char *node = myxml_find_xpath_first( (const char *)XMLExample, "//singleAttributeExample");
    REQUIRE( node != NULL );
    REQUIRE( myxml_is_node_single( node ) ); 
    node = myxml_find_xpath_first( (const char *)XMLExample, "//attributeValue");
    REQUIRE( node != NULL );
    REQUIRE( ! myxml_is_node_single( node ) ); 
}

TEST_CASE( "aducid enums", "[enums][operation]") {
    REQUIRE( strcmp("open",aducid_operation_str(ADUCID_OPERATION_OPEN) ) == 0 );
    REQUIRE( aducid_operation_enum("open") == ADUCID_OPERATION_OPEN );
    REQUIRE( strcmp("exuse",aducid_operation_str(ADUCID_OPERATION_EXUSE) ) == 0 );
    REQUIRE( aducid_operation_enum("exuse") == ADUCID_OPERATION_EXUSE );
    REQUIRE( aducid_operation_str((AducidOperation_t)30000) == NULL );
    REQUIRE( aducid_operation_enum("nonsense") == ADUCID_OPERATION_INVALID );
}

TEST_CASE( "attr list", "[lists][operation]" ) {
    AducidAttributeList_t h;

    h = aducid_attr_list_new();
    REQUIRE( aducid_attr_list_count(h) == 0 );
    aducid_attr_list_append(h,"c","c");
    aducid_attr_list_prepend(h,"a","a");
    aducid_attr_list_insert(h,"b","b",1);
    REQUIRE( aducid_attr_list_count(h) == 3 );
    REQUIRE( std::string(aducid_attr_list_get_item_name(h,0)) == "a" );
    REQUIRE( std::string(aducid_attr_list_get_item_name(h,1)) == "b" );
    REQUIRE( std::string(aducid_attr_list_get_item_name(h,2)) == "c" );
    aducid_attr_list_delete(h,1);
    REQUIRE( aducid_attr_list_count(h) == 2 );
    REQUIRE( std::string(aducid_attr_list_get_item_name(h,1)) == "c");
    aducid_attr_list_insert(h,"b","b",1);
    aducid_attr_list_insert(h,"b","b",1);
    aducid_attr_list_insert(h,"b","b",1);
    REQUIRE( aducid_attr_list_count(h) == 5 );
    aducid_attr_list_delete_by_name(h,"b");
    REQUIRE( aducid_attr_list_count(h) == 2 );
    aducid_attr_list_free(h);
}
