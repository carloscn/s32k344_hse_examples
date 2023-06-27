
#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/

#include "hse_host.h"
#include "string.h"
#ifdef HSE_SPT_STREAM_CTX_IMPORT_EXPORT
#include "hse_host_impex_stream.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
static uint8_t          localMuIf = 0U;
static uint8_t          localMuChannelIdx = 0U;

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

hseSrvResponse_t StreamCtxImport(hseStreamId_t streamId, const uint8_t* pStreamingContext)
{
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[localMuIf][localMuChannelIdx];
    hseImportExportStreamCtxSrv_t* pStreamImpexSrv;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_IMPORT_EXPORT_STREAM_CTX;

    pStreamImpexSrv = &(pHseSrvDesc->hseSrv.importExportStreamCtx);

    pStreamImpexSrv->operation   = HSE_IMPORT_STREAMING_CONTEXT;
    pStreamImpexSrv->streamId = streamId;
    pStreamImpexSrv->pStreamContext = (HOST_ADDR)pStreamingContext;

    hseStatus = HSE_Send(localMuIf, localMuChannelIdx, gSyncTxOption, pHseSrvDesc);
    return hseStatus;
}

hseSrvResponse_t StreamCtxExport(hseStreamId_t streamId, uint8_t* pStreamingContext)
{
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[localMuIf][localMuChannelIdx];
    hseImportExportStreamCtxSrv_t* pStreamImpexSrv;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_IMPORT_EXPORT_STREAM_CTX;

    pStreamImpexSrv = &(pHseSrvDesc->hseSrv.importExportStreamCtx);

    pStreamImpexSrv->operation   = HSE_EXPORT_STREAMING_CONTEXT;
    pStreamImpexSrv->streamId = streamId;
    pStreamImpexSrv->pStreamContext = (HOST_ADDR)pStreamingContext;

    hseStatus = HSE_Send(localMuIf, localMuChannelIdx, gSyncTxOption, pHseSrvDesc);
    return hseStatus;
}

hseSrvResponse_t StreamCtxOp(hseStreamContextOp_t op, hseStreamId_t streamId, uint8_t* pStreamingContext)
{
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[localMuIf][localMuChannelIdx];
    hseImportExportStreamCtxSrv_t* pStreamImpexSrv;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_IMPORT_EXPORT_STREAM_CTX;

    pStreamImpexSrv = &(pHseSrvDesc->hseSrv.importExportStreamCtx);

    pStreamImpexSrv->operation   = op;
    pStreamImpexSrv->streamId = streamId;
    pStreamImpexSrv->pStreamContext = (HOST_ADDR)pStreamingContext;

    hseStatus = HSE_Send(localMuIf, localMuChannelIdx, gSyncTxOption, pHseSrvDesc);
    return hseStatus;
}

hseSrvResponse_t StreamCtxOpMuInstance(hseStreamContextOp_t op, hseStreamId_t streamId, uint8_t* pStreamingContext, uint8_t muInstance)
{
    hseSrvResponse_t hseStatus = HSE_SRV_RSP_GENERAL_ERROR;
    hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[muInstance][localMuChannelIdx];
    hseImportExportStreamCtxSrv_t* pStreamImpexSrv;

    memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

    pHseSrvDesc->srvId = HSE_SRV_ID_IMPORT_EXPORT_STREAM_CTX;

    pStreamImpexSrv = &(pHseSrvDesc->hseSrv.importExportStreamCtx);

    pStreamImpexSrv->operation   = op;
    pStreamImpexSrv->streamId = streamId;
    pStreamImpexSrv->pStreamContext = (HOST_ADDR)pStreamingContext;

    hseStatus = HSE_Send(muInstance, localMuChannelIdx, gSyncTxOption, pHseSrvDesc);
    return hseStatus;
}
#endif

#ifdef __cplusplus
}
#endif

/** @} */

