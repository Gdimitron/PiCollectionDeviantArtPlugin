// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#pragma once

#include "../../PiCollectionSaver/src/plugin_interface.h"

class DeviantUrlBuilder : public IUrlBuilder
{
public:
    std::wstring GetMainUserPageUrlByName(
            const std::wstring &strUserName) const;
    std::wstring GetMainUserPageUrlById(const std::wstring &strUserName) const;
    std::wstring GetPicUrlByPicId(const std::wstring &strPicId) const;
    std::wstring GetCommonAlbumUrlById(const std::wstring &strUserId) const;
    std::wstring GetUserIdFromUrl(const std::wstring &strUrl) const;
    std::wstring GetUserNameFromUrl(const std::wstring &strUrl) const;
    std::wstring GetPicIdFromUrl(const std::wstring &strUrl) const;
};
