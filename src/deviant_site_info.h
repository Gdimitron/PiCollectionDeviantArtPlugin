// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#pragma once

#include "../../PiCollectionSaver/src/plugin_interface.h"

using namespace std;

class DeviantSiteInfo : public ISiteInfo
{
public:
    const wstring &GetHostName() const;
    const wstring &GetProtocol() const;
    const wstring &GetProtocolHostName() const;
    const wstring &GetLogin() const;
    const wstring &GetAuthInfo() const;

    const wstring &GetDBFileName() const;
    const wstring &GetDBTableName() const;
};
