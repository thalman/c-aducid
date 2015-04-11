/* Copyright(c) 2015 ANECT a.s.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "textconstants.h"

/* ADUCID text constants begin */

const static char *aducidOperations[] = {
    "open",
    "init",
    "reinit",
    "change",
    "rechange",
    "delete",
    "link",
    "exuse",
    "autoChange",
    NULL
};

const static char *aducidAttributeSets[] = {
    "Status",
    "Basic",
    "All",
    "Validity",
    "Link",
    "Error",
    "PeigReturnName",
    NULL
};

const static char *aducidAIMStatuses[] = {
    "none",
    "error",
    "working",
    "Client-binding",
    "start",
    "finished",
    "active",
    "internal-error",
    "startTimeout",
    "processTimeout",
    "bindingTimeout",
    "end",
    "passive",
    "Auth-error",
    NULL
};

const static char *aducidMethods[] = {
    "Init",
    "Create",
    "Change",
    "Read",
    "Delete",
    "Write",
    "LegacyLogin",
    "Set",
    "GenKeyPair",
    "WriteCert",
    "LegacySign",
    "OTPverification",
    "ILread",
    "PasswdDecrypt",
    "SetExecuteRight",
    "ClearExecuteRight",
    "UploadCert",
    "TempEnableCAPI",
    "TempDisableCAPI",
    "PermEnableCAPI",
    "PermDisableCAPI",
    "PPOresult",
    "AIMread",
    "ReadPeigCount",
    "ActivateOtherPeigs",
    "DeactivateOtherPeigs",
    "ActivateThePeig",
    "DeactivateThePeig",
    "ReadPeigId",
    "ReadOtherPeigsId",
    "CreateRoomByName",
    "CreateRoomByStory",
    "EnterRoomByName",
    "EnterRoomByStory",
    "ConfirmTransaction",
    "VerifyLF",
    "PeigLocalLink",
    NULL
};

const static char *aducidAlgorithms[] = {
    "USER_ATTRIBUTE_SET",
    "PASSWD",
    "PASSWD-AIM",
    "BIN_STRING",
    "OTP-AIM_1",
    "X509-SIG",
    "ADUCID%23%23%23PEIG-MGMT",
    "PAYMENT",
    NULL
};

const static char *aducidAuthStatuses[] = {
    "OK",
    "ERR",
    "UV",
    "USP",
    "DI",
    "UPR",
    "CR",
    "UI",
    "MI",
    "VI",
    "UIP",
    "USSP",
    "NEO",
    "UOP",
    "NER",
    "IE",
    "NAU",
    "NU",
    "NTD",
    "DR",
    "SPE",
    "NAP",
    "UU",
    "UUS",
    "UTL",
    "UCC",
    "NOP",
    "UIL",
    "ILM",
    "ISE",
    "NSA",
    "KO",
    "PPNP",
    "NS",
    "CTO",
    "LI",
    "DMR",
    "UMR",
    "CMR",
    "MET",
    "BIM",
    "DLN",
    "MCT",
    "BEE",
    "UBM",
    "PCD",
    NULL
};


/* ADUCID text constants end */

const char *aducid_enum_to_str(const int aenum,const char *array[]) {
    int cnt=0;

    while( array[cnt] != NULL ) { cnt++; }
    if( aenum < 1 || aenum > cnt ) { return NULL; }
    return array[aenum - 1];
}

int aducid_str_to_enum(const char *aenum,const char *array[]) {
    int i;

    if(! aenum ) { return 0; }
    for(i=0 ; array[i] != NULL; i++) {
        if( strcasecmp(array[i],aenum) == 0 ) {
            return i+1;
        }
    }
    return 0;
}

ADUCID_PUBLIC_FUNC
const char *aducid_operation_str(AducidOperation_t operation) {
    return aducid_enum_to_str(operation,aducidOperations);
}

ADUCID_PUBLIC_FUNC
AducidOperation_t aducid_operation_enum(const char *operation) {
    return (AducidOperation_t)aducid_str_to_enum(operation,aducidOperations);
}

ADUCID_PUBLIC_FUNC
const char *aducid_attribute_set_str(AducidAttributeSet_t set) {
    return aducid_enum_to_str(set,aducidAttributeSets);
}

ADUCID_PUBLIC_FUNC
AducidAttributeSet_t aducid_attribute_set_enum(const char *set) {
    return (AducidAttributeSet_t)aducid_str_to_enum(set,aducidAttributeSets);
}

ADUCID_PUBLIC_FUNC
const char *aducid_aim_status_str(AducidAIMStatus_t status) {
    return aducid_enum_to_str(status,aducidAIMStatuses);
}

ADUCID_PUBLIC_FUNC
AducidAIMStatus_t aducid_aim_status_enum(const char *status) {
    return (AducidAIMStatus_t)aducid_str_to_enum(status,aducidAIMStatuses);
}

ADUCID_PUBLIC_FUNC
const char *aducid_method_str(AducidMethod_t method) {
    return aducid_enum_to_str(method,aducidMethods);
}

ADUCID_PUBLIC_FUNC
AducidMethod_t aducid_method_enum(const char *method) {
    return (AducidMethod_t)aducid_str_to_enum(method,aducidMethods);
}

ADUCID_PUBLIC_FUNC
const char *aducid_algorithm_str(AducidAlgorithm_t alg) {
    return aducid_enum_to_str(alg,aducidAlgorithms);
}

ADUCID_PUBLIC_FUNC
AducidAlgorithm_t aducid_algorithm_enum(const char *alg) {
    return (AducidAlgorithm_t)aducid_str_to_enum(alg,aducidAlgorithms);
}

ADUCID_PUBLIC_FUNC
const char *aducid_auth_status_str(AducidAuthStatus_t status) {
    return aducid_enum_to_str(status,aducidAuthStatuses);
}

ADUCID_PUBLIC_FUNC
AducidAuthStatus_t aducid_auth_status_enum(const char *status) {
    return (AducidAuthStatus_t)aducid_str_to_enum(status,aducidAuthStatuses);
}
