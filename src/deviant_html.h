// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#pragma once

#include "../../PiCollectionSaver/src/plugin_interface.h"

class DeviantHtmlPageElmt : public IHtmlPageElm
{
    std::wstring m_strHtml;
    int m_iTotalPhotoCount;

public:
    DeviantHtmlPageElmt(const std::wstring &strHtml);

    bool IsSelfNamePresent() const { return false; }

    std::wstring GetUserName() const;
    std::wstring GetLastActivityTime() const;
    std::wstring GetFirstCommonAlbumUrl() const;
    std::wstring GetNextCommonAlbumUrl(const std::wstring &strCurAlbmUrl,
                                       int iPicOnPageCnt);

    std::list<std::wstring> GetPicPageUrlsList() const;

    std::wstring GetUserIdPicPage() const;
    std::wstring GetBestPossibleDirectPicUrl() const;
    std::wstring GetShownInBrowserDirectPicUrl() const;

    int GetTotalPhotoCount();
    int GetHidePhotoCount()  { return 0; }
    int GetViewLimitedPhotoCount()  { return 0; }

private: // interface
    void PreprocessPage();	// remove exceed spaces, all '\r' and '\n'

private:

};
