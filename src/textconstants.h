#ifndef __TEXTCONSTANTS_H__
#define __TEXTCONSTANTS_H__

#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

ADUCID_PUBLIC_FUNC const char *
aducid_operation_str( AducidOperation_t operation );

ADUCID_PUBLIC_FUNC AducidOperation_t
aducid_operation_enum( char *operation );

ADUCID_PUBLIC_FUNC const char *
aducid_attribute_set_str( AducidAttributeSet_t set );

ADUCID_PUBLIC_FUNC AducidAttributeSet_t
aducid_attribute_set_enum( char *set );

ADUCID_PUBLIC_FUNC const char *
aducid_aim_status_str( AducidAIMStatus_t status );

ADUCID_PUBLIC_FUNC AducidAIMStatus_t
aducid_aim_status_enum( char *status );

ADUCID_PUBLIC_FUNC const char *
aducid_method_str( AducidMethod_t method );

ADUCID_PUBLIC_FUNC AducidMethod_t
aducid_method_enum(char *method);

ADUCID_PUBLIC_FUNC const char *
aducid_algorithm_str( AducidAlgorithm_t alg );

ADUCID_PUBLIC_FUNC AducidAlgorithm_t
aducid_algorithm_enum(char *alg);

ADUCID_PUBLIC_FUNC const char *
aducid_auth_status_str( AducidAuthStatus_t status );

ADUCID_PUBLIC_FUNC AducidAuthStatus_t
aducid_auth_status_enum( char *status );

#ifdef __cplusplus
}
#endif

#endif /* __TEXTCONSTANTS_H__ */
