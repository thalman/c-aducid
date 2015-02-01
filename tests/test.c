#if defined _WIN32 || defined _WIN64
#include "../src/aducid.h"
#else
#include "../src/aducid.h"
#endif

#include "test.h"

int test_enums() {
    printf("enums: open->string");
    if( strcmp("open",aducid_operation_str(ADUCID_OPERATION_OPEN) ) == 0 ) { printf(" ok\n"); } else { printf(" fail\n"); }
    printf("enums: string->open");
    if( aducid_operation_enum("open") == ADUCID_OPERATION_OPEN ) { printf(" ok\n"); } else { printf(" fail\n"); }
    printf("enums: exuse->string");
    if( strcmp("exuse",aducid_operation_str(ADUCID_OPERATION_EXUSE) ) == 0 ) { printf(" ok\n"); } else { printf(" fail\n"); }
    printf("enums: string->exuse");
    if( aducid_operation_enum("exuse") == ADUCID_OPERATION_EXUSE ) { printf(" ok\n"); } else { printf(" fail\n"); }

    printf("enums: nonsense->NULL");
    if( aducid_operation_str(30000) == NULL ) { printf(" ok\n"); } else { printf(" fail\n"); }
    printf("enums: nonsense->invalid");
    if( aducid_operation_enum("nonsense") == ADUCID_OPERATION_INVALID ) { printf(" ok\n"); } else { printf(" fail\n"); }
    return 0;
}

int test_soap_get(){
    AducidAIMRequestOperationResponse *resp;

    resp = aducid_aim_request_operation(OBOX,ADUCID_OPERATION_OPEN, NULL, NULL, NULL, NULL,NULL,NULL,NULL,NULL,NULL);
    printf("AIMRequestOperation authId:%s statusAIM: %i statusAuth: %i...",
	   resp->authId,
	   resp->statusAIM,
	   resp->statusAuth);
    if( resp->statusAuth == ADUCID_AUTHSTATUS_OK ) {
	printf("ok\n");
    } else {
	printf("failed\n");
    }
    aducid_free_aim_request_operation_response(resp);
    return 0;
}

int test_identity_use(){
    AducidHandle handle;
    char *URL;
    
    handle = aducid_new(TESTINGAIM,NULL,NULL,NULL,NULL);
    if( aducid_open(handle,NULL) ) {
	URL = aducid_get_aducid_url(handle);
	printf("AducidURL: %s\n",URL);
	free(URL);
	URL = aducid_get_aimproxy_url(handle);
	printf("PPURL: %s\n",URL);
	free(URL);
	aducid_peig_invoke(handle);
	if(aducid_wait_for_operation(handle) ) {
	    aducid_peig_get_authkey(handle);
	    printf("authKey: %s\nwait ok\n",handle->authId);
	    if( aducid_verify(handle) ) {
		printf("verify ok\n");
	    } else {
		printf("verify failed\n");
	    }
	} else {
	    printf("wait failed\n");
	}
    }
    if( aducid_close(handle) ) {
	printf("close ok\n");
    } else {
	printf("close failed\n");
    };
    aducid_free(handle);
    return 0;
}

int test_attr_list(){
    AducidAttributeList *h;

    h = aducid_attr_list_new();
    printf( "count 0?: %i\n", aducid_attr_list_count(h));
    aducid_attr_list_append(h,"c","c");
    aducid_attr_list_prepend(h,"a","a");
    aducid_attr_list_insert(h,"b","b",1);
    printf( "count 3?: %i\n", aducid_attr_list_count(h));
    printf( "item 0 is a: %s\n", aducid_attr_list_get_item_name(h,0));
    printf( "item 1 is b: %s\n", aducid_attr_list_get_item_name(h,1));
    printf( "item 2 is c: %s\n", aducid_attr_list_get_item_name(h,2));
    aducid_attr_list_delete(h,1);
    printf( "count 2?: %i\n", aducid_attr_list_count(h));
    printf( "item 1 is c: %s\n", aducid_attr_list_get_item_name(h,1));
    aducid_attr_list_insert(h,"b","b",1);
    aducid_attr_list_insert(h,"b","b",1);
    aducid_attr_list_insert(h,"b","b",1);
    printf( "count 5?: %i\n", aducid_attr_list_count(h));
    aducid_attr_list_delete_by_name(h,"b");
    printf( "count 2?: %i\n", aducid_attr_list_count(h));
    aducid_attr_list_free(h);
    return 0;
}

int main(int argc, char *argv[]) {
    int result = 0,i;
    aducid_library_init();

    result = result || test_soap_get();
    result = result || test_enums();
    for(i=0; i<10; i++) {
	result = result || test_identity_use();
    }
    for(i=0; i<10; i++) {
	result = result || test_attr_list();
    }
    if(result) {
	printf("ERROR ocured during test\n");
    }
    aducid_library_free();
    return result;
}
