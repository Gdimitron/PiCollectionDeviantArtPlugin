// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#pragma once

#include "../../PiCollectionSaver/src/plugin_interface.h"

class DeviantFileNames : public IFileSysBldr
{
public:
    std::wstring GetPicFileName(const std::wstring &strUserId,
                                const std::wstring &strFileId) const;
    std::wstring GetUserId(const std::wstring &wstrFileName) const;
};
