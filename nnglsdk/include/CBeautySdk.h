#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#ifdef CBEAUTYSDK_BUILD_SHARED_LIB
#define BEAUTYSDK_API __declspec(dllexport)
#else
#define BEAUTYSDK_API
#endif
#else
#define BEAUTYSDK_API __attribute__((visibility("default")))
#endif

typedef enum _BEAUTY_PARAM_NAME_TYPE {
    BEAUTY_PARAM_NAME_START = 0,
    BEAUTY_PARAM_NAME_WHITE = BEAUTY_PARAM_NAME_START, //����
    BEAUTY_PARAM_NAME_RUDDY,                           //����
    BEAUTY_PARAM_NAME_BUFFING,                         //ĥƤ
    BEAUTY_PARAM_NAME_SHARPNEN,                        //��
    BEAUTY_PARAM_NAME_NEWWHITE,                        //������
    BEAUTY_PARAM_NAME_FILTER_INSTENSITY,               //�˾�
    BEAUTY_PARAM_NAME_FILTER,                          //�˾�

    FACEWARP_PARAM_NAME_THINFACE,                      //����
    FACEWARP_PARAM_NAME_ENLARGEEYE,                    //����
    FACEWARP_PARAM_NAME_SHRINKNOSE,                    //�ݱ�
    BEAUTY_PARAM_NAME_END
} BEAUTY_PARAM_NAME_TYPE;


BEAUTYSDK_API const char* getVersion();
BEAUTYSDK_API void setLogLevel(int level);

BEAUTYSDK_API void* createBeautySdk(const char* license);
BEAUTYSDK_API void destoryBeautySdk(void* sdk);
BEAUTYSDK_API void createBeautyBundle(void* sdk, const char* tag, const char* data, int size);
BEAUTYSDK_API void setBeautySdkParameter(void* sdk, BEAUTY_PARAM_NAME_TYPE ntype, float val);
BEAUTYSDK_API void setBeautySdkStringParameter(void* sdk, BEAUTY_PARAM_NAME_TYPE ntype, const char* val);

BEAUTYSDK_API int getLicenseStatus(void* sdk);

BEAUTYSDK_API void initBeautySdk(void* sdk);
BEAUTYSDK_API void deinitBeautySdk(void* sdk);

//BEAUTYSDK_API void processBuffer(void* sdk, unsigned char* data, int width, int height);
BEAUTYSDK_API unsigned int processTexture(void* sdk, unsigned int texture, int width, int height);
BEAUTYSDK_API void renderTexture(void* sdk, unsigned int target, unsigned int texture);
#ifdef __cplusplus
}
#endif

