/*******************************************************************************
*   Ledger Blue
*   (c) 2016 Ledger
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#include "tokens.h"
#include <stdbool.h>
#include <string.h>

const uint8_t token_public_key[] = {0x04,0x92,0x49,0x1c,0x3f,0x95,0x4d,0x0a,0x2a,0x71,0xe7,0xf4,0x75,0xe3,0x0f,0xfb,0xeb,0x96,0x7a,0xaf,0xde,0x67,0x8f,0x44,0xa3,0xa3,0x26,0x4d,0x81,0x3f,0x49,0x8d,0x95,0x4b,0x3e,0x00,0x0f,0x4a,0x71,0xcb,0xcd,0xf4,0xc9,0x7c,0x60,0x9d,0x3d,0x20,0x7b,0x75,0x13,0x2a,0xee,0x66,0xc0,0x84,0x2d,0xd8,0xd0,0xf6,0xdd,0x50,0x54,0xaa,0x6c};

const uint8_t SELECTOR[][4] = {{0xA9,0x05,0x9C,0xBB},{0x09,0x5E,0xA7,0xB3}};

const tokenDefinition_t const TOKENS_VRC20[NUM_TOKENS_VRC20] = {

    {{0x46,0xDB,0xF2,0xB7,0x3D,0xF1,0x23,0xED,0x12,0x89,0x99,0x51,0xA1,0x38,0x25,0x48,0x24,0x5E,0x52,0xB8,0xF9}, "$PKT ", 6},
    
};

int verifyTokenNameID(const char *tokenId, const char *tokenName, uint8_t decimals, uint8_t *signature, uint8_t signatureLength, publicKeyContext_t *publicKeyContext){
    uint8_t buffer[65];
    cx_sha256_t sha2;
    uint8_t hash[32];
    
    if (strlen(tokenId) > 32) return 0;

    snprintf((char *)buffer, sizeof(buffer), "%s%s%c",tokenId, tokenName, decimals);
   
    cx_sha256_init(&sha2); //init sha
    cx_hash((cx_hash_t *)&sha2, CX_LAST, buffer, strlen(tokenId)+strlen(tokenName)+1, hash, 32);
   
    cx_ecfp_init_public_key(CX_CURVE_256K1,(uint8_t *)PIC(&token_public_key), 65, &(publicKeyContext->publicKey));
    
    int ret = cx_ecdsa_verify((cx_ecfp_public_key_t WIDE *)&(publicKeyContext->publicKey), CX_LAST,
                    CX_SHA256, hash, 32, 
                    signature, signatureLength);

    return ret;
}

int verifyExchangeID(const unsigned char *exchangeValidation, uint8_t datLength, uint8_t *signature, uint8_t signatureLength, publicKeyContext_t *publicKeyContext){
    cx_sha256_t sha2;
    uint8_t hash[32];
    
    cx_sha256_init(&sha2); //init sha
    cx_hash((cx_hash_t *)&sha2, CX_LAST, exchangeValidation, datLength, hash, 32);
   
    cx_ecfp_init_public_key(CX_CURVE_256K1,(uint8_t *)PIC(&token_public_key), 65, &(publicKeyContext->publicKey));
    
    int ret = cx_ecdsa_verify((cx_ecfp_public_key_t WIDE *)&(publicKeyContext->publicKey), CX_LAST,
                    CX_SHA256, hash, 32, 
                    signature, signatureLength);

    return ret;
}


