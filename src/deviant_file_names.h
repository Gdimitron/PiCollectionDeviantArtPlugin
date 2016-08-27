// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#pragma once

#include "../../PiCollectionSaver/src/plugin_interface.h"

using namespace std;

class DeviantFileNames : public IFileSysBldr
{
public:
    wstring GetPicFileName(const wstring &strUserId,
                           const wstring &strFileId) const;
    wstring GetUserId(const wstring &wstrFileName) const;
};
