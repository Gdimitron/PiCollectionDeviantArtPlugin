// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#include "deviant_urls.h"

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
    auto strRet = g_SiteInfo->GetHostName();
    return wstring();
}

wstring DeviantUrlBuilder::GetMainUserPageUrlById(
        const wstring& strUserId) const
{
 // return http://userId.deviantart.com/gallery/?catpath=/
    return wstring();
}

wstring DeviantUrlBuilder::GetPicUrlByPicId(const wstring& strPicId) const
{
// return http://userId.deviantart.com/art/picId
    return wstring();
}

wstring DeviantUrlBuilder::GetCommonAlbumUrlById(const wstring &strId) const
{
 // return http://userId.deviantart.com/gallery/?catpath=/
    return wstring();
}

wstring DeviantUrlBuilder::GetUserIdFromUrl(const wstring &strUrl) const
{
// get - // http://userId.deviantart.com/gallery/?catpath=/
// return - userId
    return wstring();
}

wstring DeviantUrlBuilder::GetUserNameFromUrl(const wstring &strUrl) const
{
    return GetUserIdFromUrl(strUrl);
}

wstring DeviantUrlBuilder::GetPicIdFromUrl(const wstring &strUrl) const
{
// get - http://userId.deviantart.com/art/picId
// return - picId
    return wstring();
}
