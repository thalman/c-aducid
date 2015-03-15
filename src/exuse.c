#include "aducid.h"

DLL_PUBLIC
const char *aducid_exuse(AducidHandle handle,
                         const char *methodName,
                         const AducidAttributeList methodParameters,
                         const AducidAttributeList personalObject,
                         const char *peigReturnName)
{
    return aducid_request_operation(handle,ADUCID_OPERATION_EXUSE,methodName,methodParameters,personalObject,NULL,NULL,peigReturnName);
}

