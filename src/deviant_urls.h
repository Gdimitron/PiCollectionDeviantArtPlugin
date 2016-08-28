// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#pragma once

#include "../../PiCollectionSaver/src/plugin_interface.h"

using namespace std;

class DeviantUrlBuilder : public IUrlBuilder
{
public:
    wstring GetMainUserPageUrlByName(const wstring &strUserName) const;
    wstring GetMainUserPageUrlById(const wstring &strUserName) const;
    wstring GetPicUrlByPicId(const wstring &strPicId) const;
    wstring GetCommonAlbumUrlById(const wstring &strUserId) const;
    wstring GetUserIdFromUrl(const wstring &strUrl) const;
    wstring GetUserNameFromUrl(const wstring &strUrl) const;
    wstring GetPicIdFromUrl(const wstring &strUrl) const;
};
