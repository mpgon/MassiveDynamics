﻿
// File generated by Wsutil Compiler version 1.0095 
#include <WebServices.h>
#include "tempuri.org.xsd.h"

typedef struct _tempuri_org_xsdLocalDefinitions 
{
    struct  // global elements
    {
    char unused;
        struct  // _authenticate
        {
            WS_FIELD_DESCRIPTION user;
            WS_FIELD_DESCRIPTION pass;
            WS_FIELD_DESCRIPTION* _authenticateFields [2]; 
        } _authenticatedescs; // end of _authenticate
        struct  // _authenticateResponse
        {
            WS_FIELD_DESCRIPTION authenticateResult;
            WS_FIELD_DESCRIPTION* _authenticateResponseFields [1]; 
        } _authenticateResponsedescs; // end of _authenticateResponse
        struct  // _getUsersResponse
        {
            WS_FIELD_DESCRIPTION getUsersResult;
            WS_FIELD_DESCRIPTION* _getUsersResponseFields [1]; 
        } _getUsersResponsedescs; // end of _getUsersResponse
        struct  // _getRelacoesResponse
        {
            WS_FIELD_DESCRIPTION getRelacoesResult;
            WS_FIELD_DESCRIPTION* _getRelacoesResponseFields [1]; 
        } _getRelacoesResponsedescs; // end of _getRelacoesResponse
    } globalElements;  // end of global elements
    struct  // XML dictionary
    {
        struct  // XML string list
        {
            WS_XML_STRING _authenticateTypeName;  // authenticate
            WS_XML_STRING _authenticateTypeNamespace;  // http://tempuri.org/
            WS_XML_STRING _authenticateuserLocalName;  // user
            WS_XML_STRING _authenticatepassLocalName;  // pass
            WS_XML_STRING _authenticateResponseTypeName;  // authenticateResponse
            WS_XML_STRING _authenticateResponseauthenticateResultLocalName;  // authenticateResult
            WS_XML_STRING _getUsersTypeName;  // getUsers
            WS_XML_STRING _getUsersResponseTypeName;  // getUsersResponse
            WS_XML_STRING _getUsersResponsegetUsersResultLocalName;  // getUsersResult
            WS_XML_STRING _getRelacoesTypeName;  // getRelacoes
            WS_XML_STRING _getRelacoesResponseTypeName;  // getRelacoesResponse
            WS_XML_STRING _getRelacoesResponsegetRelacoesResultLocalName;  // getRelacoesResult
        } xmlStrings;  // end of XML string list
        WS_XML_DICTIONARY dict;
    } dictionary;  // end of XML dictionary
} _tempuri_org_xsdLocalDefinitions;

const static _tempuri_org_xsdLocalDefinitions tempuri_org_xsdLocalDefinitions =
{
    {  // global elements
        0,
        {  // _authenticate
            {  // field description for user
            WS_ELEMENT_FIELD_MAPPING,
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateuserLocalName, // user
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_WSZ_TYPE,
            0,
            WsOffsetOf(_authenticate, user),
             WS_FIELD_OPTIONAL| WS_FIELD_NILLABLE,
            0,
            0xffffffff
            },    // end of field description for user
            {  // field description for pass
            WS_ELEMENT_FIELD_MAPPING,
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticatepassLocalName, // pass
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_WSZ_TYPE,
            0,
            WsOffsetOf(_authenticate, pass),
             WS_FIELD_OPTIONAL| WS_FIELD_NILLABLE,
            0,
            0xffffffff
            },    // end of field description for pass
            {  // fields description for _authenticate
            (WS_FIELD_DESCRIPTION*)&tempuri_org_xsdLocalDefinitions.globalElements._authenticatedescs.user,
            (WS_FIELD_DESCRIPTION*)&tempuri_org_xsdLocalDefinitions.globalElements._authenticatedescs.pass,
            },
        },    // _authenticate
        {  // _authenticateResponse
            {  // field description for authenticateResult
            WS_ELEMENT_FIELD_MAPPING,
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateResponseauthenticateResultLocalName, // authenticateResult
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_BOOL_TYPE,
            0,
            WsOffsetOf(_authenticateResponse, authenticateResult),
             WS_FIELD_OPTIONAL,
            0,
            0xffffffff
            },    // end of field description for authenticateResult
            {  // fields description for _authenticateResponse
            (WS_FIELD_DESCRIPTION*)&tempuri_org_xsdLocalDefinitions.globalElements._authenticateResponsedescs.authenticateResult,
            },
        },    // _authenticateResponse
        {  // _getUsersResponse
            {  // field description for getUsersResult
            WS_ELEMENT_FIELD_MAPPING,
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._getUsersResponsegetUsersResultLocalName, // getUsersResult
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_WSZ_TYPE,
            0,
            WsOffsetOf(_getUsersResponse, getUsersResult),
             WS_FIELD_OPTIONAL| WS_FIELD_NILLABLE,
            0,
            0xffffffff
            },    // end of field description for getUsersResult
            {  // fields description for _getUsersResponse
            (WS_FIELD_DESCRIPTION*)&tempuri_org_xsdLocalDefinitions.globalElements._getUsersResponsedescs.getUsersResult,
            },
        },    // _getUsersResponse
        {  // _getRelacoesResponse
            {  // field description for getRelacoesResult
            WS_ELEMENT_FIELD_MAPPING,
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._getRelacoesResponsegetRelacoesResultLocalName, // getRelacoesResult
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_WSZ_TYPE,
            0,
            WsOffsetOf(_getRelacoesResponse, getRelacoesResult),
             WS_FIELD_OPTIONAL| WS_FIELD_NILLABLE,
            0,
            0xffffffff
            },    // end of field description for getRelacoesResult
            {  // fields description for _getRelacoesResponse
            (WS_FIELD_DESCRIPTION*)&tempuri_org_xsdLocalDefinitions.globalElements._getRelacoesResponsedescs.getRelacoesResult,
            },
        },    // _getRelacoesResponse
    }, // end of global elements
    {  // dictionary 
        {  // xmlStrings
            WS_XML_STRING_DICTIONARY_VALUE("authenticate",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 0),
            WS_XML_STRING_DICTIONARY_VALUE("http://tempuri.org/",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 1),
            WS_XML_STRING_DICTIONARY_VALUE("user",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 2),
            WS_XML_STRING_DICTIONARY_VALUE("pass",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 3),
            WS_XML_STRING_DICTIONARY_VALUE("authenticateResponse",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 4),
            WS_XML_STRING_DICTIONARY_VALUE("authenticateResult",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 5),
            WS_XML_STRING_DICTIONARY_VALUE("getUsers",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 6),
            WS_XML_STRING_DICTIONARY_VALUE("getUsersResponse",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 7),
            WS_XML_STRING_DICTIONARY_VALUE("getUsersResult",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 8),
            WS_XML_STRING_DICTIONARY_VALUE("getRelacoes",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 9),
            WS_XML_STRING_DICTIONARY_VALUE("getRelacoesResponse",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 10),
            WS_XML_STRING_DICTIONARY_VALUE("getRelacoesResult",&tempuri_org_xsdLocalDefinitions.dictionary.dict, 11),
        },  // end of xmlStrings
        
        {  // tempuri_org_xsddictionary
          // 120662ec-890a-4c69-b4d1-114893fab790 
        { 0x120662ec, 0x890a, 0x4c69, { 0xb4, 0xd1, 0x11,0x48, 0x93, 0xfa, 0xb7, 0x90 } },
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings,
        12,
        TRUE,
        },
    },  //  end of dictionary
}; //  end of tempuri_org_xsdLocalDefinitions

const _tempuri_org_xsd tempuri_org_xsd =
{
    {  // globalElements
        {
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeName, // authenticate
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_STRUCT_TYPE,
            (void*)&tempuri_org_xsd.externallyReferencedTypes.authenticate,
        },
        {
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateResponseTypeName, // authenticateResponse
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_STRUCT_TYPE,
            (void*)&tempuri_org_xsd.externallyReferencedTypes.authenticateResponse,
        },
        {
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._getUsersTypeName, // getUsers
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_STRUCT_TYPE,
            (void*)&tempuri_org_xsd.externallyReferencedTypes.getUsers,
        },
        {
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._getUsersResponseTypeName, // getUsersResponse
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_STRUCT_TYPE,
            (void*)&tempuri_org_xsd.externallyReferencedTypes.getUsersResponse,
        },
        {
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._getRelacoesTypeName, // getRelacoes
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_STRUCT_TYPE,
            (void*)&tempuri_org_xsd.externallyReferencedTypes.getRelacoes,
        },
        {
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._getRelacoesResponseTypeName, // getRelacoesResponse
            (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
            WS_STRUCT_TYPE,
            (void*)&tempuri_org_xsd.externallyReferencedTypes.getRelacoesResponse,
        },
    },  // globalElements
    {  // begin of externallyReferencedTypes
        {
        sizeof(_authenticate),
        __alignof(_authenticate),
        (WS_FIELD_DESCRIPTION**)&tempuri_org_xsdLocalDefinitions.globalElements._authenticatedescs._authenticateFields,
        WsCountOf(tempuri_org_xsdLocalDefinitions.globalElements._authenticatedescs._authenticateFields),
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeName, // authenticate
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
        0,
        0,
        0,
        },   // end of struct description for _authenticate
        {
        sizeof(_authenticateResponse),
        __alignof(_authenticateResponse),
        (WS_FIELD_DESCRIPTION**)&tempuri_org_xsdLocalDefinitions.globalElements._authenticateResponsedescs._authenticateResponseFields,
        WsCountOf(tempuri_org_xsdLocalDefinitions.globalElements._authenticateResponsedescs._authenticateResponseFields),
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateResponseTypeName, // authenticateResponse
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
        0,
        0,
        0,
        },   // end of struct description for _authenticateResponse
        {
        0,
        1,
        0,
        0,
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._getUsersTypeName, // getUsers
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
        0,
        0,
        0,
        },   // end of struct description for _getUsers
        {
        sizeof(_getUsersResponse),
        __alignof(_getUsersResponse),
        (WS_FIELD_DESCRIPTION**)&tempuri_org_xsdLocalDefinitions.globalElements._getUsersResponsedescs._getUsersResponseFields,
        WsCountOf(tempuri_org_xsdLocalDefinitions.globalElements._getUsersResponsedescs._getUsersResponseFields),
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._getUsersResponseTypeName, // getUsersResponse
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
        0,
        0,
        0,
        },   // end of struct description for _getUsersResponse
        {
        0,
        1,
        0,
        0,
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._getRelacoesTypeName, // getRelacoes
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
        0,
        0,
        0,
        },   // end of struct description for _getRelacoes
        {
        sizeof(_getRelacoesResponse),
        __alignof(_getRelacoesResponse),
        (WS_FIELD_DESCRIPTION**)&tempuri_org_xsdLocalDefinitions.globalElements._getRelacoesResponsedescs._getRelacoesResponseFields,
        WsCountOf(tempuri_org_xsdLocalDefinitions.globalElements._getRelacoesResponsedescs._getRelacoesResponseFields),
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._getRelacoesResponseTypeName, // getRelacoesResponse
        (WS_XML_STRING*)&tempuri_org_xsdLocalDefinitions.dictionary.xmlStrings._authenticateTypeNamespace, // http://tempuri.org/
        0,
        0,
        0,
        },   // end of struct description for _getRelacoesResponse
    },  // end of externallyReferencedTypes;
}; // end of _tempuri_org_xsd
