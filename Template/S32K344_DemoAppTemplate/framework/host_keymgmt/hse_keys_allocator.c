/**
 *   @file    hse_keys_allocator.c
 *
 *   @brief   Function implementations for host keys allocator
 *   @details This file will help with handling of key handles.
 *
 *   @addtogroup [KEYMGMT_FRAMEWORK]
 *   @{
 */
/*==================================================================================================
 *   (c) Copyright 2020 NXP.
 *
 *   This software is owned or controlled by NXP and may only be used strictly in accordance with
 *   the applicable license terms. By expressly accepting such terms or by downloading, installing,
 *   activating and/or otherwise using the software, you are agreeing that you have read, and that
 *   you agree to comply with and are bound by, such license terms. If you do not agree to
 *   be bound by the applicable license terms, then you may not retain, install, activate or
 *   otherwise use the software.
 ==================================================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
 *                                        INCLUDE FILES
 ==================================================================================================*/
#include "hse_interface.h"
#include "hse_keys_allocator.h"

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 ==================================================================================================*/
typedef struct
{
    bool_t             keyEmpty;
} keySlotContext_t;

typedef struct
{
    hseMuMask_t        muMask;
    hseKeyGroupOwner_t groupOwner;
    hseKeyType_t       keyType;
    uint8_t            numOfKeySlots;
    uint16_t           maxKeyBitLen;
    keySlotContext_t   key[0x100];
} groupContext_t;

typedef struct
{
    uint8_t noOfGroups;
    groupContext_t group[HSE_TOTAL_NUM_OF_KEY_GROUPS];
} catalogContext_t;

typedef struct
{
    catalogContext_t ctx[3];
} allocatorContext_t;
/*==================================================================================================
 *                                       LOCAL MACROS
 ==================================================================================================*/
#define HSE_KEY_IS_EMPTY       ((bool_t) 1U)
#define HSE_KEY_IS_NOT_EMPTY   ((bool_t) 0U)

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 ==================================================================================================*/

/*==================================================================================================
 *                                      LOCAL VARIABLES
 ==================================================================================================*/
static allocatorContext_t allocatorCtx = { 0U };

/*==================================================================================================
 *                                      GLOBAL CONSTANTS
 ==================================================================================================*/

/*==================================================================================================
 *                                      GLOBAL VARIABLES
 ==================================================================================================*/
/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 ==================================================================================================*/
static hseSrvResponse_t HKF_ParseCatalog(const hseKeyGroupCfgEntry_t *pCatalog, catalogContext_t *pCatalogCtx);

static bool_t verifyGroupMuFlags(hseMuMask_t reqMuMask, hseMuMask_t groupMuMask, bool_t strictMuMask);

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 ==================================================================================================*/
static hseSrvResponse_t HKF_ParseCatalog(const hseKeyGroupCfgEntry_t *pCatalog, catalogContext_t *pCatalogCtx)
{
    hseSrvResponse_t status = HSE_SRV_RSP_GENERAL_ERROR;
    hseKeyGroupIdx_t i;
    hseKeySlotIdx_t j;

    for(i = 0U; i < HSE_TOTAL_NUM_OF_KEY_GROUPS; ++i)
    {
        if( 0U == pCatalog[i].muMask          &&
            0U == pCatalog[i].groupOwner      &&
            0U == pCatalog[i].keyType         &&
            0U == pCatalog[i].numOfKeySlots   &&
            0U == pCatalog[i].maxKeyBitLen
        )
        {
            /* Entry with all zeros reached */
            status = HSE_SRV_RSP_OK;
            break;
        }

        /* Set group attributes */
        pCatalogCtx->group[i].muMask        = pCatalog[i].muMask;
        pCatalogCtx->group[i].groupOwner    = pCatalog[i].groupOwner;
        pCatalogCtx->group[i].keyType       = pCatalog[i].keyType;
        pCatalogCtx->group[i].numOfKeySlots = pCatalog[i].numOfKeySlots;
        pCatalogCtx->group[i].maxKeyBitLen  = pCatalog[i].maxKeyBitLen;

        /* Set keys as empty */
        for(j = 0U; j < pCatalog[i].numOfKeySlots; ++j)
        {
            pCatalogCtx->group[i].key[j].keyEmpty = HSE_KEY_IS_EMPTY;
        }
    }

    /* Set total number of groups for catalog */
    pCatalogCtx->noOfGroups = i;

    return status;
}

static bool_t verifyGroupMuFlags(hseMuMask_t reqMuMask, hseMuMask_t groupMuMask, bool_t strictMuMask)
{
    bool_t result = FALSE;
    (void)result;

    if((TRUE == strictMuMask) && (reqMuMask == groupMuMask))
    {
        result = TRUE;
        goto exit;
    }

    if((FALSE == strictMuMask) && (0U != (reqMuMask | groupMuMask)))
    {
        result = TRUE;
        goto exit;
    }

exit:
    return result;
}

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 ==================================================================================================*/
hseSrvResponse_t HKF_Init(const hseKeyGroupCfgEntry_t *pNvmCatalog, const hseKeyGroupCfgEntry_t *pRamCatalog)
{
    hseSrvResponse_t status = HSE_SRV_RSP_GENERAL_ERROR;

    /* Avoid MISRA violation */
    (void)status;

    /* Parse NVM catalog */
    status = HKF_ParseCatalog(pNvmCatalog, &allocatorCtx.ctx[HSE_KEY_CATALOG_ID_NVM]);
    if(HSE_SRV_RSP_OK != status)
    {
        goto exit;
    }

    /* Parse RAM catalog */
    status = HKF_ParseCatalog(pRamCatalog, &allocatorCtx.ctx[HSE_KEY_CATALOG_ID_RAM]);
    if(HSE_SRV_RSP_OK != status)
    {
        goto exit;
    }

exit:
    return status;
}

hseSrvResponse_t HKF_AllocKeySlotAdvanced(
    uint8_t isNvmKey,
    hseMuMask_t muMask,
    bool_t strictMuMask,
    hseKeyGroupOwner_t groupOwner,
    hseKeyType_t keyType,
    uint16_t maxKeyBitLength,
    hseKeyHandle_t *pKeyHandle
)
{
    hseSrvResponse_t status = HSE_SRV_RSP_GENERAL_ERROR;
    hseKeyCatalogId_t catId = HSE_KEY_CATALOG_ID_RAM;
    catalogContext_t *catalogCtx = &allocatorCtx.ctx[catId];
    hseKeyGroupIdx_t i;
    hseKeySlotIdx_t j;

    /* Avoid MISRA violation */
    (void)status;

    if(NULL == pKeyHandle)
    {
        status = HSE_SRV_RSP_INVALID_ADDR;
        goto exit;
    }

    if(NVM_KEY == isNvmKey)
    {
        catId      = HSE_KEY_CATALOG_ID_NVM;
        catalogCtx = &allocatorCtx.ctx[catId];
    }

    /* Search for a perfect match */
    for(i = 0U; i < catalogCtx->noOfGroups; ++i)
    {
        if(groupOwner == catalogCtx->group[i].groupOwner &&
           verifyGroupMuFlags(muMask, catalogCtx->group[i].muMask, strictMuMask) &&
           keyType == catalogCtx->group[i].keyType && 
           maxKeyBitLength == catalogCtx->group[i].maxKeyBitLen)
        {
            groupContext_t *pGroupCtx = &catalogCtx->group[i];

            for(j = 0U; j < pGroupCtx->numOfKeySlots; ++j)
            {
                if(HSE_KEY_IS_EMPTY == pGroupCtx->key[j].keyEmpty)
                {
                    status                     = HSE_SRV_RSP_OK;
                    pGroupCtx->key[j].keyEmpty = HSE_KEY_IS_NOT_EMPTY;
                    *pKeyHandle                = GET_KEY_HANDLE(catId, i, j);
                    goto exit;
                }
            }
        }
    }

    /* Try again with bigger keys */
    for(i = 0U; i < catalogCtx->noOfGroups; ++i)
    {
        if(groupOwner == catalogCtx->group[i].groupOwner &&
           verifyGroupMuFlags(muMask, catalogCtx->group[i].muMask, strictMuMask) &&
           keyType == catalogCtx->group[i].keyType && 
           maxKeyBitLength <= catalogCtx->group[i].maxKeyBitLen)
        {
            groupContext_t *pGroupCtx = &catalogCtx->group[i];

            for(j = 0U; j < pGroupCtx->numOfKeySlots; ++j)
            {
                if(HSE_KEY_IS_EMPTY == pGroupCtx->key[j].keyEmpty)
                {
                    status                     = HSE_SRV_RSP_OK;
                    pGroupCtx->key[j].keyEmpty = HSE_KEY_IS_NOT_EMPTY;
                    *pKeyHandle                = GET_KEY_HANDLE(catId, i, j);
                    goto exit;
                }
            }
        }
    }

exit:
    return status;
}

hseSrvResponse_t HKF_AllocKeySlot(
    uint8_t isNvmKey,
    hseKeyType_t keyType,
    uint16_t maxKeyBitLength,
    hseKeyHandle_t *pKeyHandle
)
{
    hseKeyGroupOwner_t groupOwner = HSE_KEY_OWNER_ANY;
    if(NVM_KEY == isNvmKey)
    {
        groupOwner = HSE_KEY_OWNER_CUST;
    }
    return HKF_AllocKeySlotAdvanced(isNvmKey, HSE_MU0_MASK, FALSE, groupOwner, keyType, maxKeyBitLength, pKeyHandle);
}

hseSrvResponse_t HKF_FreeKeySlot(hseKeyHandle_t *keyHandle)
{
    hseSrvResponse_t status  = HSE_SRV_RSP_GENERAL_ERROR;
    hseKeyCatalogId_t catId  = GET_CATALOG_ID(*keyHandle);
    hseKeyGroupIdx_t groupId = GET_GROUP_IDX(*keyHandle);
    hseKeySlotIdx_t slotId   = GET_SLOT_IDX(*keyHandle);
    keySlotContext_t * pKeySlot = NULL;

    if(HSE_INVALID_KEY_HANDLE == *keyHandle)
    {
        status = HSE_SRV_RSP_OK;
        goto exit;
    }

    pKeySlot = &allocatorCtx.ctx[catId].group[groupId].key[slotId];

    if(HSE_KEY_IS_NOT_EMPTY == pKeySlot->keyEmpty)
    {
        pKeySlot->keyEmpty = HSE_KEY_IS_EMPTY;
        *keyHandle = HSE_INVALID_KEY_HANDLE;
        status = HSE_SRV_RSP_OK;
    }

exit:
    return status;
}

hseSrvResponse_t HKF_IsKeyHandleAllocated(hseKeyHandle_t keyHandle)
{
    hseSrvResponse_t status  = HSE_SRV_RSP_INVALID_PARAM;
    hseKeyCatalogId_t catId  = GET_CATALOG_ID(keyHandle);
    hseKeyGroupIdx_t groupId = GET_GROUP_IDX(keyHandle);
    hseKeySlotIdx_t slotId   = GET_SLOT_IDX(keyHandle);
    keySlotContext_t * pKeySlot = NULL;

    if(HSE_INVALID_KEY_HANDLE == keyHandle)
    {
        goto exit;
    }

    pKeySlot = &allocatorCtx.ctx[catId].group[groupId].key[slotId];
    if(HSE_KEY_IS_NOT_EMPTY == pKeySlot->keyEmpty)
    {
        status = HSE_SRV_RSP_OK;
    }

exit:
    return status;
}

hseSrvResponse_t HKF_MarkAsAllocated(hseKeyHandle_t keyHandle)
{
    hseSrvResponse_t status  = HSE_SRV_RSP_INVALID_PARAM;
    hseKeyCatalogId_t catId  = GET_CATALOG_ID(keyHandle);
    hseKeyGroupIdx_t groupId = GET_GROUP_IDX(keyHandle);
    hseKeySlotIdx_t slotId   = GET_SLOT_IDX(keyHandle);

    keySlotContext_t * pKeySlot = &allocatorCtx.ctx[catId].group[groupId].key[slotId];

    if(HSE_KEY_IS_EMPTY == pKeySlot->keyEmpty)
    {
        pKeySlot->keyEmpty = HSE_KEY_IS_NOT_EMPTY;
        status = HSE_SRV_RSP_OK;
    }

    return status;
}

void HKF_FreeAllKeys(void)
{
    hseKeyCatalogId_t catId = HSE_KEY_CATALOG_ID_RAM;
    catalogContext_t *catalogCtx = &allocatorCtx.ctx[catId];
    hseKeyGroupIdx_t i;
    hseKeySlotIdx_t j;

    /* Free ram catalog */
    for(i = 0U; i < catalogCtx->noOfGroups; ++i)
    {
        groupContext_t *pGroupCtx = &catalogCtx->group[i];
        for(j = 0U; j < pGroupCtx->numOfKeySlots; ++j)
        {
            pGroupCtx->key[j].keyEmpty = HSE_KEY_IS_EMPTY;
        }
    }

    catId      = HSE_KEY_CATALOG_ID_NVM;
    catalogCtx = &allocatorCtx.ctx[catId];
    /* Free nvm catalog */
    for(i = 0U; i < catalogCtx->noOfGroups; ++i)
    {
        groupContext_t *pGroupCtx = &catalogCtx->group[i];
        for(j = 0U; j < pGroupCtx->numOfKeySlots; ++j)
        {
            pGroupCtx->key[j].keyEmpty = HSE_KEY_IS_EMPTY;
        }
    }
}

#ifdef __cplusplus
}
#endif

/** @} */
