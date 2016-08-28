// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#include "deviant_file_names.h"
#include <regex>

shared_ptr<IFileSysBldr> IFileSysBldrCtr()
{
    shared_ptr<IFileSysBldr> retVal(new DeviantFileNames());
    return retVal;
}

wstring DeviantFileNames::GetPicFileName(const wstring &strUserId,
                                         const wstring &strFileId) const
{
    return strUserId + L"_" + strFileId + L".jpeg";
}

wstring DeviantFileNames::GetUserId(const wstring &strFileName) const
{
    wstring retVal;
    wsmatch match;
    if (regex_match(strFileName, match, wregex(L"([^_]+)_([^_]+).jpeg"))) {
        retVal = match[1].str();
    }
    return retVal;
}
