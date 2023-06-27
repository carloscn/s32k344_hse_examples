#include "hse_demo_app_services.h"
#include "hse_host_wrappers.h"
#include "hse_host_test.h"

hseSrvResponse_t SHE_CommandApp_Service()
{
    hseSrvResponse_t SHEServiceResponse = HSE_SRV_RSP_GENERAL_ERROR;
    SHEServiceResponse = Load_Relevant_She_Keys();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_ECB_ENC_DEC();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_CBC_ENC_DEC();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_CMAC_GENERATE_VERIFY();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_SHE_LOAD_KEYS();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_SHE_LOAD_PLAIN_KEY();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_EXPORT_RAM_KEY();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_CMD_EXTEND_SEED();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_RANDOM_NUM_REQ();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_SHE_GET_ID();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_CMD_DEBUG_CHAL_AUTH();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }

    SHEServiceResponse = Test_CMD_TRNG_RND();
    if (HSE_SRV_RSP_OK != SHEServiceResponse)
    {
        goto exit;
    }
exit:
    return SHEServiceResponse;
}
