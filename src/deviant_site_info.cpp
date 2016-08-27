// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#include "deviant_site_info.h"

const wstring c_HostName(L"http://deviantart.com");

const wstring c_Login(L"");
const wstring c_Password(L"");
const wstring c_AuthInfo(L"login=1&login=" + c_Login + L"&pass=" + c_Password);

const wstring c_DbFileName(L"deviantart.db");
const wstring c_DbTableName(L"users_url_and_activity_time");


shared_ptr<ISiteInfo> ISiteInfoCtr()
{
    shared_ptr<ISiteInfo> retVal(new DeviantSiteInfo());
    return retVal;
}

const wstring &DeviantSiteInfo::GetHostName() const
{
    return c_HostName;
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
