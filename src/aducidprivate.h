#ifndef __ADUCIDPRIVATE_H__
#define __ADUCIDPRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

const char *
aducid_request_operation(
    AducidHandle_t handle,
    AducidOperation_t operation,
    const char* methodName,
    const AducidAttributeList_t methodParameters,
    const AducidAttributeList_t personalObject,
    const char *AAIM2,
    const char *ilData,
    const char *peigReturnName
);


#ifdef __cplusplus
}
#endif

#endif
