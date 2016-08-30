// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#include "deviant_urls.h"
#include <regex>

auto g_SiteInfo = ISiteInfoCtr();

shared_ptr<IUrlBuilder> IUrlBuilderCtr()
{
    shared_ptr<IUrlBuilder> retVal(new DeviantUrlBuilder());
    return retVal;
}

wstring DeviantUrlBuilder::GetMainUserPageUrlByName(
        const wstring& strUserName) const
{
    // return http://username.deviantart.com
    auto retVal = g_SiteInfo->GetProtocol() + strUserName + L"."
            + g_SiteInfo->GetHostName();
    return retVal;
}

wstring DeviantUrlBuilder::GetMainUserPageUrlById(
        const wstring& strUserId) const
{
    return GetMainUserPageUrlByName(strUserId);
}

wstring DeviantUrlBuilder::GetPicUrlByPicId(const wstring& strPicId) const
{
    // return http://userId.deviantart.com/art/picId
    auto retVal = g_SiteInfo->GetProtocol() + g_SiteInfo->GetHostName()
            + L"/art/" + strPicId;
    return retVal;
}

wstring DeviantUrlBuilder::GetCommonAlbumUrlById(const wstring &strUserId) const
{
    // return http://userId.deviantart.com/gallery/?catpath=/
    auto retVal = GetMainUserPageUrlByName(strUserId) + L"/gallery/?catpath=/";
    return retVal;
}

//TODO: add tests
/* GetUserIdFromUrl(L"http://userId.deviantart.com/gallery/?catpath=/");
GetUserIdFromUrl(L"userId.deviantart.com/gallery/?catpath=/");*/
wstring DeviantUrlBuilder::GetUserIdFromUrl(const wstring &strUrl) const
{
    // get - // http://userId.deviantart.com/gallery/?catpath=/
    // return - userId
    wstring retVal;
    wsmatch match;
    if (regex_match(strUrl, match,
                    wregex(L"(http://|)([^/.]+)[.]deviantart.*"))) {
        retVal = match[2].str();
    }
    return retVal;
}

wstring DeviantUrlBuilder::GetUserNameFromUrl(const wstring &strUrl) const
{
    return GetUserIdFromUrl(strUrl);
}

//TODO: add tests
/*GetPicIdFromUrl(L"http://userId.deviantart.com/art/picId");*/
wstring DeviantUrlBuilder::GetPicIdFromUrl(const wstring &strUrl) const
{
    // get - http://userId.deviantart.com/art/picId
    // return - picId
    wstring retVal;
    wsmatch match;
    if (regex_search(strUrl, match, wregex(L"/art/([^?]+)"))) {
        retVal = match[1].str();
    }
    return retVal;
}
