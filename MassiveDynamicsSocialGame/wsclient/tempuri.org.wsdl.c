﻿
// File generated by Wsutil Compiler version 1.0095 
#include <WebServices.h>
#include "tempuri.org.xsd.h"
#include "tempuri.org.wsdl.h"

typedef struct _tempuri_org_wsdlLocalDefinitions 
{
    struct  // messages
    {
        WS_MESSAGE_DESCRIPTION IMassiveDynamicsWService_authenticate_InputMessage;
        WS_MESSAGE_DESCRIPTION IMassiveDynamicsWService_authenticate_OutputMessage;
        WS_MESSAGE_DESCRIPTION IMassiveDynamicsWService_getUsers_InputMessage;
        WS_MESSAGE_DESCRIPTION IMassiveDynamicsWService_getUsers_OutputMessage;
        WS_MESSAGE_DESCRIPTION IMassiveDynamicsWService_getRelacoes_InputMessage;
        WS_MESSAGE_DESCRIPTION IMassiveDynamicsWService_getRelacoes_OutputMessage;
    } messages;  // end of messages
    struct  // contracts
    {
        struct  // BasicHttpBinding_IMassiveDynamicsWService
        {
            struct  // BasicHttpBinding_IMassiveDynamicsWService_authenticate
            {
                WS_PARAMETER_DESCRIPTION params[3];
                WS_OPERATION_DESCRIPTION BasicHttpBinding_IMassiveDynamicsWService_authenticate;
            } BasicHttpBinding_IMassiveDynamicsWService_authenticate;
            struct  // BasicHttpBinding_IMassiveDynamicsWService_getUsers
            {
                WS_PARAMETER_DESCRIPTION params[1];
                WS_OPERATION_DESCRIPTION BasicHttpBinding_IMassiveDynamicsWService_getUsers;
            } BasicHttpBinding_IMassiveDynamicsWService_getUsers;
            struct  // BasicHttpBinding_IMassiveDynamicsWService_getRelacoes
            {
                WS_PARAMETER_DESCRIPTION params[1];
                WS_OPERATION_DESCRIPTION BasicHttpBinding_IMassiveDynamicsWService_getRelacoes;
            } BasicHttpBinding_IMassiveDynamicsWService_getRelacoes;
            WS_OPERATION_DESCRIPTION* operations[3];
            WS_CONTRACT_DESCRIPTION contractDesc;
        } BasicHttpBinding_IMassiveDynamicsWService;
    } contracts;  // endof contracts 
    struct  // policies
    {
        struct  // BasicHttpBinding_IMassiveDynamicsWService
        {
            WS_ENCODING encoding;
            WS_ADDRESSING_VERSION addressingVersion;
            WS_ENVELOPE_VERSION envelopeVersion;
            WS_CHANNEL_PROPERTY channelPropertiesArray[3];
        } BasicHttpBinding_IMassiveDynamicsWService;
    } policies;
    struct  // XML dictionary
    {
        struct  // XML string list
        {
            WS_XML_STRING IMassiveDynamicsWService_authenticate_InputMessageactionName;  // http://tempuri.org/IMassiveDynamicsWService/authenticate
            WS_XML_STRING IMassiveDynamicsWService_authenticate_OutputMessageactionName;  // http://tempuri.org/IMassiveDynamicsWService/authenticateResponse
            WS_XML_STRING IMassiveDynamicsWService_getUsers_InputMessageactionName;  // http://tempuri.org/IMassiveDynamicsWService/getUsers
            WS_XML_STRING IMassiveDynamicsWService_getUsers_OutputMessageactionName;  // http://tempuri.org/IMassiveDynamicsWService/getUsersResponse
            WS_XML_STRING IMassiveDynamicsWService_getRelacoes_InputMessageactionName;  // http://tempuri.org/IMassiveDynamicsWService/getRelacoes
            WS_XML_STRING IMassiveDynamicsWService_getRelacoes_OutputMessageactionName;  // http://tempuri.org/IMassiveDynamicsWService/getRelacoesResponse
        } xmlStrings;  // end of XML string list
        WS_XML_DICTIONARY dict;
    } dictionary;  // end of XML dictionary
} _tempuri_org_wsdlLocalDefinitions;


typedef struct BasicHttpBinding_IMassiveDynamicsWService_authenticateParamStruct 
{
    WCHAR** user;
    WCHAR** pass;
    BOOL* authenticateResult;
} BasicHttpBinding_IMassiveDynamicsWService_authenticateParamStruct;

#if (_MSC_VER >=1400) 
#pragma warning(push)
#endif
#pragma warning(disable: 4055) // conversion from data pointer to function pointer
HRESULT CALLBACK BasicHttpBinding_IMassiveDynamicsWService_authenticateOperationStub(
    _In_ const WS_OPERATION_CONTEXT* _context,
    _In_ void* _stackStruct,
    _In_ const void* _callback,
    _In_ const WS_ASYNC_CONTEXT* _asyncContext,
    _In_ WS_ERROR* _error)
{
    BasicHttpBinding_IMassiveDynamicsWService_authenticateCallback _operation = (BasicHttpBinding_IMassiveDynamicsWService_authenticateCallback)_callback;
    BasicHttpBinding_IMassiveDynamicsWService_authenticateParamStruct *_stack =(BasicHttpBinding_IMassiveDynamicsWService_authenticateParamStruct*)_stackStruct;
    return _operation( 
        _context,
        *(_stack->user),
        *(_stack->pass),
        (_stack->authenticateResult),
        (WS_ASYNC_CONTEXT*)_asyncContext,
        _error);
}
#pragma warning(default: 4055)  // conversion from data pointer to function pointer
#if (_MSC_VER >=1400) 
#pragma warning(pop)
#endif

typedef struct BasicHttpBinding_IMassiveDynamicsWService_getUsersParamStruct 
{
    WCHAR** getUsersResult;
} BasicHttpBinding_IMassiveDynamicsWService_getUsersParamStruct;

#if (_MSC_VER >=1400) 
#pragma warning(push)
#endif
#pragma warning(disable: 4055) // conversion from data pointer to function pointer
HRESULT CALLBACK BasicHttpBinding_IMassiveDynamicsWService_getUsersOperationStub(
    _In_ const WS_OPERATION_CONTEXT* _context,
    _In_ void* _stackStruct,
    _In_ const void* _callback,
    _In_ const WS_ASYNC_CONTEXT* _asyncContext,
    _In_ WS_ERROR* _error)
{
    BasicHttpBinding_IMassiveDynamicsWService_getUsersCallback _operation = (BasicHttpBinding_IMassiveDynamicsWService_getUsersCallback)_callback;
    BasicHttpBinding_IMassiveDynamicsWService_getUsersParamStruct *_stack =(BasicHttpBinding_IMassiveDynamicsWService_getUsersParamStruct*)_stackStruct;
    return _operation( 
        _context,
        (_stack->getUsersResult),
        (WS_ASYNC_CONTEXT*)_asyncContext,
        _error);
}
#pragma warning(default: 4055)  // conversion from data pointer to function pointer
#if (_MSC_VER >=1400) 
#pragma warning(pop)
#endif

typedef struct BasicHttpBinding_IMassiveDynamicsWService_getRelacoesParamStruct 
{
    WCHAR** getRelacoesResult;
} BasicHttpBinding_IMassiveDynamicsWService_getRelacoesParamStruct;

#if (_MSC_VER >=1400) 
#pragma warning(push)
#endif
#pragma warning(disable: 4055) // conversion from data pointer to function pointer
HRESULT CALLBACK BasicHttpBinding_IMassiveDynamicsWService_getRelacoesOperationStub(
    _In_ const WS_OPERATION_CONTEXT* _context,
    _In_ void* _stackStruct,
    _In_ const void* _callback,
    _In_ const WS_ASYNC_CONTEXT* _asyncContext,
    _In_ WS_ERROR* _error)
{
    BasicHttpBinding_IMassiveDynamicsWService_getRelacoesCallback _operation = (BasicHttpBinding_IMassiveDynamicsWService_getRelacoesCallback)_callback;
    BasicHttpBinding_IMassiveDynamicsWService_getRelacoesParamStruct *_stack =(BasicHttpBinding_IMassiveDynamicsWService_getRelacoesParamStruct*)_stackStruct;
    return _operation( 
        _context,
        (_stack->getRelacoesResult),
        (WS_ASYNC_CONTEXT*)_asyncContext,
        _error);
}
#pragma warning(default: 4055)  // conversion from data pointer to function pointer
#if (_MSC_VER >=1400) 
#pragma warning(pop)
#endif
const static _tempuri_org_wsdlLocalDefinitions tempuri_org_wsdlLocalDefinitions =
{
    {  // messages
        {  // message description for IMassiveDynamicsWService_authenticate_InputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_authenticate_InputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/authenticate
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.authenticate, 
        },    // message description for IMassiveDynamicsWService_authenticate_InputMessage
        {  // message description for IMassiveDynamicsWService_authenticate_OutputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_authenticate_OutputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/authenticateResponse
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.authenticateResponse, 
        },    // message description for IMassiveDynamicsWService_authenticate_OutputMessage
        {  // message description for IMassiveDynamicsWService_getUsers_InputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_getUsers_InputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/getUsers
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.getUsers, 
        },    // message description for IMassiveDynamicsWService_getUsers_InputMessage
        {  // message description for IMassiveDynamicsWService_getUsers_OutputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_getUsers_OutputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/getUsersResponse
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.getUsersResponse, 
        },    // message description for IMassiveDynamicsWService_getUsers_OutputMessage
        {  // message description for IMassiveDynamicsWService_getRelacoes_InputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_getRelacoes_InputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/getRelacoes
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.getRelacoes, 
        },    // message description for IMassiveDynamicsWService_getRelacoes_InputMessage
        {  // message description for IMassiveDynamicsWService_getRelacoes_OutputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_getRelacoes_OutputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/getRelacoesResponse
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.getRelacoesResponse, 
        },    // message description for IMassiveDynamicsWService_getRelacoes_OutputMessage
    },  // end of messages 
    {  // contracts
        {  // BasicHttpBinding_IMassiveDynamicsWService,
            {  // BasicHttpBinding_IMassiveDynamicsWService_authenticate
                {  // parameter descriptions for BasicHttpBinding_IMassiveDynamicsWService_authenticate
                    {WS_PARAMETER_TYPE_NORMAL, (USHORT)0, (USHORT)-1},
                    {WS_PARAMETER_TYPE_NORMAL, (USHORT)1, (USHORT)-1},
                    {WS_PARAMETER_TYPE_NORMAL, (USHORT)-1, (USHORT)0},
                },  // parameter descriptions for BasicHttpBinding_IMassiveDynamicsWService_authenticate
                {  // operation description for BasicHttpBinding_IMassiveDynamicsWService_authenticate
                    1,
                    (WS_MESSAGE_DESCRIPTION*)&tempuri_org_wsdl.messages.IMassiveDynamicsWService_authenticate_InputMessage, 
                    (WS_MESSAGE_DESCRIPTION*)&tempuri_org_wsdl.messages.IMassiveDynamicsWService_authenticate_OutputMessage, 
                    0,
                    0,
                    3,
                    (WS_PARAMETER_DESCRIPTION*)tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.BasicHttpBinding_IMassiveDynamicsWService_authenticate.params,
                    BasicHttpBinding_IMassiveDynamicsWService_authenticateOperationStub,
                    WS_NON_RPC_LITERAL_OPERATION
                }, //operation description for BasicHttpBinding_IMassiveDynamicsWService_authenticate
            },  // BasicHttpBinding_IMassiveDynamicsWService_authenticate
            {  // BasicHttpBinding_IMassiveDynamicsWService_getUsers
                {  // parameter descriptions for BasicHttpBinding_IMassiveDynamicsWService_getUsers
                    {WS_PARAMETER_TYPE_NORMAL, (USHORT)-1, (USHORT)0},
                },  // parameter descriptions for BasicHttpBinding_IMassiveDynamicsWService_getUsers
                {  // operation description for BasicHttpBinding_IMassiveDynamicsWService_getUsers
                    1,
                    (WS_MESSAGE_DESCRIPTION*)&tempuri_org_wsdl.messages.IMassiveDynamicsWService_getUsers_InputMessage, 
                    (WS_MESSAGE_DESCRIPTION*)&tempuri_org_wsdl.messages.IMassiveDynamicsWService_getUsers_OutputMessage, 
                    0,
                    0,
                    1,
                    (WS_PARAMETER_DESCRIPTION*)tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.BasicHttpBinding_IMassiveDynamicsWService_getUsers.params,
                    BasicHttpBinding_IMassiveDynamicsWService_getUsersOperationStub,
                    WS_NON_RPC_LITERAL_OPERATION
                }, //operation description for BasicHttpBinding_IMassiveDynamicsWService_getUsers
            },  // BasicHttpBinding_IMassiveDynamicsWService_getUsers
            {  // BasicHttpBinding_IMassiveDynamicsWService_getRelacoes
                {  // parameter descriptions for BasicHttpBinding_IMassiveDynamicsWService_getRelacoes
                    {WS_PARAMETER_TYPE_NORMAL, (USHORT)-1, (USHORT)0},
                },  // parameter descriptions for BasicHttpBinding_IMassiveDynamicsWService_getRelacoes
                {  // operation description for BasicHttpBinding_IMassiveDynamicsWService_getRelacoes
                    1,
                    (WS_MESSAGE_DESCRIPTION*)&tempuri_org_wsdl.messages.IMassiveDynamicsWService_getRelacoes_InputMessage, 
                    (WS_MESSAGE_DESCRIPTION*)&tempuri_org_wsdl.messages.IMassiveDynamicsWService_getRelacoes_OutputMessage, 
                    0,
                    0,
                    1,
                    (WS_PARAMETER_DESCRIPTION*)tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.BasicHttpBinding_IMassiveDynamicsWService_getRelacoes.params,
                    BasicHttpBinding_IMassiveDynamicsWService_getRelacoesOperationStub,
                    WS_NON_RPC_LITERAL_OPERATION
                }, //operation description for BasicHttpBinding_IMassiveDynamicsWService_getRelacoes
            },  // BasicHttpBinding_IMassiveDynamicsWService_getRelacoes
            {  // array of operations for BasicHttpBinding_IMassiveDynamicsWService
                (WS_OPERATION_DESCRIPTION*)&tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.BasicHttpBinding_IMassiveDynamicsWService_authenticate.BasicHttpBinding_IMassiveDynamicsWService_authenticate,
                (WS_OPERATION_DESCRIPTION*)&tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.BasicHttpBinding_IMassiveDynamicsWService_getUsers.BasicHttpBinding_IMassiveDynamicsWService_getUsers,
                (WS_OPERATION_DESCRIPTION*)&tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.BasicHttpBinding_IMassiveDynamicsWService_getRelacoes.BasicHttpBinding_IMassiveDynamicsWService_getRelacoes,
            },  // array of operations for BasicHttpBinding_IMassiveDynamicsWService
            {  // contract description for BasicHttpBinding_IMassiveDynamicsWService
            3,
            (WS_OPERATION_DESCRIPTION**)tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.operations,
            },  // end of contract description for BasicHttpBinding_IMassiveDynamicsWService
        },  // BasicHttpBinding_IMassiveDynamicsWService
    },  // end of contracts 
    {  // policies
        {
            WS_ENCODING_XML_UTF8,
            WS_ADDRESSING_VERSION_TRANSPORT,
            WS_ENVELOPE_VERSION_SOAP_1_1,
            { // channelPropertiesArray
                {
                    WS_CHANNEL_PROPERTY_ENCODING,
                    (void*)&tempuri_org_wsdlLocalDefinitions.policies.BasicHttpBinding_IMassiveDynamicsWService.encoding,
                    sizeof(tempuri_org_wsdlLocalDefinitions.policies.BasicHttpBinding_IMassiveDynamicsWService.encoding),
                },
                {
                    WS_CHANNEL_PROPERTY_ADDRESSING_VERSION,
                    (void*)&tempuri_org_wsdlLocalDefinitions.policies.BasicHttpBinding_IMassiveDynamicsWService.addressingVersion,
                    sizeof(tempuri_org_wsdlLocalDefinitions.policies.BasicHttpBinding_IMassiveDynamicsWService.addressingVersion),
                },
                {
                    WS_CHANNEL_PROPERTY_ENVELOPE_VERSION,
                    (void*)&tempuri_org_wsdlLocalDefinitions.policies.BasicHttpBinding_IMassiveDynamicsWService.envelopeVersion,
                    sizeof(tempuri_org_wsdlLocalDefinitions.policies.BasicHttpBinding_IMassiveDynamicsWService.envelopeVersion),
                },
            },
        },   // end of BasicHttpBinding_IMassiveDynamicsWService,
    }, // policies
    {  // dictionary 
        {  // xmlStrings
            WS_XML_STRING_DICTIONARY_VALUE("http://tempuri.org/IMassiveDynamicsWService/authenticate",&tempuri_org_wsdlLocalDefinitions.dictionary.dict, 0),
            WS_XML_STRING_DICTIONARY_VALUE("http://tempuri.org/IMassiveDynamicsWService/authenticateResponse",&tempuri_org_wsdlLocalDefinitions.dictionary.dict, 1),
            WS_XML_STRING_DICTIONARY_VALUE("http://tempuri.org/IMassiveDynamicsWService/getUsers",&tempuri_org_wsdlLocalDefinitions.dictionary.dict, 2),
            WS_XML_STRING_DICTIONARY_VALUE("http://tempuri.org/IMassiveDynamicsWService/getUsersResponse",&tempuri_org_wsdlLocalDefinitions.dictionary.dict, 3),
            WS_XML_STRING_DICTIONARY_VALUE("http://tempuri.org/IMassiveDynamicsWService/getRelacoes",&tempuri_org_wsdlLocalDefinitions.dictionary.dict, 4),
            WS_XML_STRING_DICTIONARY_VALUE("http://tempuri.org/IMassiveDynamicsWService/getRelacoesResponse",&tempuri_org_wsdlLocalDefinitions.dictionary.dict, 5),
        },  // end of xmlStrings
        
        {  // tempuri_org_wsdldictionary
          // 32ffb060-a8f9-4d77-bfce-184d5f140f6a 
        { 0x32ffb060, 0xa8f9, 0x4d77, { 0xbf, 0xce, 0x18,0x4d, 0x5f, 0x14, 0x0f, 0x6a } },
        (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings,
        6,
        TRUE,
        },
    },  //  end of dictionary
}; //  end of tempuri_org_wsdlLocalDefinitions

// Disable prefast warnings for the output parameters as their contract cannot be expressed in SAL.
#if (_MSC_VER >= 1400)
#pragma warning(push)
#endif
#pragma warning(disable: 6101 6054)

// operation: BasicHttpBinding_IMassiveDynamicsWService_authenticate
HRESULT WINAPI BasicHttpBinding_IMassiveDynamicsWService_authenticate(
    _In_ WS_SERVICE_PROXY* _serviceProxy,
    _In_opt_z_ WCHAR* user, 
    _In_opt_z_ WCHAR* pass, 
    _Out_ BOOL* authenticateResult, 
    _In_ WS_HEAP* _heap,
    _In_reads_opt_(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    _In_ const ULONG _callPropertyCount,
    _In_opt_ const WS_ASYNC_CONTEXT* _asyncContext,
    _In_opt_ WS_ERROR* _error)
{
    void* _argList[3]; 
    _argList[0] = &user;
    _argList[1] = &pass;
    _argList[2] = &authenticateResult;
    return WsCall(_serviceProxy,
        (WS_OPERATION_DESCRIPTION*)&tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.BasicHttpBinding_IMassiveDynamicsWService_authenticate.BasicHttpBinding_IMassiveDynamicsWService_authenticate,
        (const void **)&_argList,
        _heap,
        _callProperties,
        _callPropertyCount,
        _asyncContext,
        _error);
}

// operation: BasicHttpBinding_IMassiveDynamicsWService_getUsers
HRESULT WINAPI BasicHttpBinding_IMassiveDynamicsWService_getUsers(
    _In_ WS_SERVICE_PROXY* _serviceProxy,
    _Outptr_opt_result_z_ WCHAR** getUsersResult, 
    _In_ WS_HEAP* _heap,
    _In_reads_opt_(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    _In_ const ULONG _callPropertyCount,
    _In_opt_ const WS_ASYNC_CONTEXT* _asyncContext,
    _In_opt_ WS_ERROR* _error)
{
    void* _argList[1]; 
    _argList[0] = &getUsersResult;
    return WsCall(_serviceProxy,
        (WS_OPERATION_DESCRIPTION*)&tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.BasicHttpBinding_IMassiveDynamicsWService_getUsers.BasicHttpBinding_IMassiveDynamicsWService_getUsers,
        (const void **)&_argList,
        _heap,
        _callProperties,
        _callPropertyCount,
        _asyncContext,
        _error);
}

// operation: BasicHttpBinding_IMassiveDynamicsWService_getRelacoes
HRESULT WINAPI BasicHttpBinding_IMassiveDynamicsWService_getRelacoes(
    _In_ WS_SERVICE_PROXY* _serviceProxy,
    _Outptr_opt_result_z_ WCHAR** getRelacoesResult, 
    _In_ WS_HEAP* _heap,
    _In_reads_opt_(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    _In_ const ULONG _callPropertyCount,
    _In_opt_ const WS_ASYNC_CONTEXT* _asyncContext,
    _In_opt_ WS_ERROR* _error)
{
    void* _argList[1]; 
    _argList[0] = &getRelacoesResult;
    return WsCall(_serviceProxy,
        (WS_OPERATION_DESCRIPTION*)&tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.BasicHttpBinding_IMassiveDynamicsWService_getRelacoes.BasicHttpBinding_IMassiveDynamicsWService_getRelacoes,
        (const void **)&_argList,
        _heap,
        _callProperties,
        _callPropertyCount,
        _asyncContext,
        _error);
}
#if (_MSC_VER >= 1400)
#pragma warning(pop)
#endif

const _tempuri_org_wsdl tempuri_org_wsdl =
{
    {  // messages
        {  // message description for IMassiveDynamicsWService_authenticate_InputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_authenticate_InputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/authenticate
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.authenticate, 
        },    // message description for IMassiveDynamicsWService_authenticate_InputMessage
        {  // message description for IMassiveDynamicsWService_authenticate_OutputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_authenticate_OutputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/authenticateResponse
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.authenticateResponse, 
        },    // message description for IMassiveDynamicsWService_authenticate_OutputMessage
        {  // message description for IMassiveDynamicsWService_getUsers_InputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_getUsers_InputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/getUsers
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.getUsers, 
        },    // message description for IMassiveDynamicsWService_getUsers_InputMessage
        {  // message description for IMassiveDynamicsWService_getUsers_OutputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_getUsers_OutputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/getUsersResponse
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.getUsersResponse, 
        },    // message description for IMassiveDynamicsWService_getUsers_OutputMessage
        {  // message description for IMassiveDynamicsWService_getRelacoes_InputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_getRelacoes_InputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/getRelacoes
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.getRelacoes, 
        },    // message description for IMassiveDynamicsWService_getRelacoes_InputMessage
        {  // message description for IMassiveDynamicsWService_getRelacoes_OutputMessage
            (WS_XML_STRING*)&tempuri_org_wsdlLocalDefinitions.dictionary.xmlStrings.IMassiveDynamicsWService_getRelacoes_OutputMessageactionName, // http://tempuri.org/IMassiveDynamicsWService/getRelacoesResponse
            (WS_ELEMENT_DESCRIPTION*)&tempuri_org_xsd.globalElements.getRelacoesResponse, 
        },    // message description for IMassiveDynamicsWService_getRelacoes_OutputMessage
    },  // messages
    {  // contracts
        {  // BasicHttpBinding_IMassiveDynamicsWService
            3,
            (WS_OPERATION_DESCRIPTION**)tempuri_org_wsdlLocalDefinitions.contracts.BasicHttpBinding_IMassiveDynamicsWService.operations,
        },  // end of BasicHttpBinding_IMassiveDynamicsWService
    },  // contracts
    {  // policies
        {  // template description for BasicHttpBinding_IMassiveDynamicsWService
            {  // channel properties
                (WS_CHANNEL_PROPERTY*)&tempuri_org_wsdlLocalDefinitions.policies.BasicHttpBinding_IMassiveDynamicsWService.channelPropertiesArray,
                3,
            },
        },  // end of template description
    },  // policies
}; // end of _tempuri_org_wsdl

HRESULT BasicHttpBinding_IMassiveDynamicsWService_CreateServiceProxy(
    _In_opt_ WS_HTTP_BINDING_TEMPLATE* templateValue,
    _In_reads_opt_(proxyPropertyCount) const WS_PROXY_PROPERTY* proxyProperties,
    _In_ const ULONG proxyPropertyCount,
    _Outptr_ WS_SERVICE_PROXY** _serviceProxy,
    _In_opt_ WS_ERROR* error)
{
    return WsCreateServiceProxyFromTemplate(
        WS_CHANNEL_TYPE_REQUEST,
        proxyProperties,
        proxyPropertyCount,
        WS_HTTP_BINDING_TEMPLATE_TYPE,
        templateValue,
        templateValue == NULL ? 0 : sizeof(WS_HTTP_BINDING_TEMPLATE),
        &tempuri_org_wsdl.policies.BasicHttpBinding_IMassiveDynamicsWService,
        sizeof(tempuri_org_wsdl.policies.BasicHttpBinding_IMassiveDynamicsWService),
        _serviceProxy,
        error);
}

HRESULT BasicHttpBinding_IMassiveDynamicsWService_CreateServiceEndpoint(
    _In_opt_ WS_HTTP_BINDING_TEMPLATE* templateValue,
    _In_opt_ CONST WS_STRING* address,
    _In_opt_ struct BasicHttpBinding_IMassiveDynamicsWServiceFunctionTable* functionTable,
    _In_opt_ WS_SERVICE_SECURITY_CALLBACK authorizationCallback,
    _In_reads_opt_(endpointPropertyCount) WS_SERVICE_ENDPOINT_PROPERTY* endpointProperties,
    _In_ const ULONG endpointPropertyCount,
    _In_ WS_HEAP* heap,
    _Outptr_ WS_SERVICE_ENDPOINT** serviceEndpoint,
    _In_opt_ WS_ERROR* error)
{
    WS_SERVICE_CONTRACT serviceContract;
    serviceContract.contractDescription = &tempuri_org_wsdl.contracts.BasicHttpBinding_IMassiveDynamicsWService;
    serviceContract.defaultMessageHandlerCallback = 0;
    serviceContract.methodTable = (const void*)functionTable;
    
    return WsCreateServiceEndpointFromTemplate(
        WS_CHANNEL_TYPE_REPLY,
        endpointProperties,
        endpointPropertyCount,
        address,
        &serviceContract,
        authorizationCallback,
        heap,
        WS_HTTP_BINDING_TEMPLATE_TYPE,
        templateValue,
        templateValue == NULL ? 0 : sizeof(WS_HTTP_BINDING_TEMPLATE),
        &tempuri_org_wsdl.policies.BasicHttpBinding_IMassiveDynamicsWService,
        sizeof(tempuri_org_wsdl.policies.BasicHttpBinding_IMassiveDynamicsWService),
        serviceEndpoint,
        error);
}
