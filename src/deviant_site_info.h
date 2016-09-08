// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#pragma once

#include "../../PiCollectionSaver/src/plugin_interface.h"

class DeviantSiteInfo : public ISiteInfo
{
public:
    const std::wstring &GetHostName() const;
    const std::wstring &GetProtocol() const;
    const std::wstring &GetProtocolHostName() const;

    const std::wstring &GetLogin() const;
    const std::wstring &GetAuthInfo() const;

    const std::wstring &GetDBFileName() const;
    const std::wstring &GetDBTableName() const;

    bool UsersIdAndNameSame() const { return true; }
    bool IsPagePicUrl(const std::wstring &url) const;
    bool IsDirectPicUrl(const std::wstring &url) const;
};
