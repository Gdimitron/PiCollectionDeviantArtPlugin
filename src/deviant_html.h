// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#pragma once

#include "../../PiCollectionSaver/src/plugin_interface.h"

//TODO: move namespace using from header to source
using namespace std;

class DeviantHtmlPageElmt : public IHtmlPageElm
{
    wstring m_strHtml;
    int m_iTotalPhotoCount;

public:
    DeviantHtmlPageElmt(const wstring &strHtml);

    bool IsSelfNamePresent() const { return false; }
    wstring GetPersonalUserLink() const;
    wstring GetUserName() const;
    wstring GetUserIdPicPage() const;
    wstring GetLastActivityTime() const;
    wstring GetFirstCommonAlbumUrl() const;
    wstring GetNextCommonAlbumUrl(const wstring &strCurAlbmUrl);
    list<wstring> GetPicPageUrlsList() const;
    list<wstring> GetPicPageUrlsListByImageIdOnly() const;

    wstring GetBestPossibleDirectPicUrl() const;
    wstring GetShownInBrowserDirectPicUrl() const;

    int GetTotalPhotoCount();
    int GetHidePhotoCount()  { return 0; }
    int GetViewLimitedPhotoCount()  { return 0; }

private: // interface
    void PreprocessPage();	// remove exceed spaces, all '\r' and '\n'

private:

};
