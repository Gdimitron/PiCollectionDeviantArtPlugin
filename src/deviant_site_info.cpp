// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#include "deviant_site_info.h"

const wstring c_HostName(L"deviantart.com");
const wstring c_HostProtocol(L"http://");
const wstring c_ProtocolHostName(c_HostProtocol + c_HostName);

const wstring c_Login(L"");
const wstring c_Password(L"");
const wstring c_AuthInfo(L""); //"login=" + c_Login + L"&pass=" + c_Password);

const wstring c_DbFileName(L"deviantart.db");
const wstring c_DbTableName(L"users_url_and_activity_time");
const wstring c_DbPicPreviewFileName(L"deviantartPicPreviewCache.db");


shared_ptr<ISiteInfo> ISiteInfoCtr()
{
    shared_ptr<ISiteInfo> retVal(new DeviantSiteInfo());
    return retVal;
}

const wstring &DeviantSiteInfo::GetHostName() const
{
    return c_HostName;
}

const wstring &DeviantSiteInfo::GetProtocol() const
{
    return c_HostProtocol;
}

const wstring &DeviantSiteInfo::GetProtocolHostName() const
{
    return c_ProtocolHostName;
}

const wstring &DeviantSiteInfo::GetLogin() const
{
    return c_Login;
}

const wstring &DeviantSiteInfo::GetAuthInfo() const
{
    return c_AuthInfo;
}

const wstring &DeviantSiteInfo::GetDBFileName() const
{
    return c_DbFileName;
}

const wstring &DeviantSiteInfo::GetDBTableName() const
{
    return c_DbTableName;
}

const wstring &DeviantSiteInfo::GetPicPreviewDBFileName() const
{
    return c_DbPicPreviewFileName;
}

bool DeviantSiteInfo::IsPagePicUrl(const wstring &url) const
{
    if (url.find(L"/art/") != wstring::npos) {
        return true;
    }
    return false;
}

bool DeviantSiteInfo::IsDirectPicUrl(const wstring &url) const
{
    if (url.find(L"http://orig") != wstring::npos) {
        return true;
    } else if (url.find(L"http://img") != wstring::npos) {
        return true;
    }
    return false;
}
