// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#include "deviant_html.h"

extern shared_ptr<ISiteInfo> g_SiteInfo;

// main user page anchors:

// album page anchors:

// pic page anchors:


shared_ptr<IHtmlPageElm> IHtmlPageElmCtr(const wstring &strHtml)
{
    shared_ptr<IHtmlPageElm> retVal(new DeviantHtmlPageElmt(strHtml));
    return retVal;
}

DeviantHtmlPageElmt::DeviantHtmlPageElmt(const wstring &strHtml)
    : m_iTotalPhotoCount(-1)
{
    assert(!strHtml.empty());
    m_strHtml = strHtml;
    PreprocessPage();
}

bool DeviantHtmlPageElmt::IsSelfNamePresent() const
{
    return false;
}

wstring DeviantHtmlPageElmt::GetPersonalUserLink() const
{
// return something like "http://username.deviantart.com"
    return wstring();
}

wstring DeviantHtmlPageElmt::GetUserName() const
{
    return wstring();
}

wstring DeviantHtmlPageElmt::GetUserIdPicPage() const
{
    return wstring();
}

wstring DeviantHtmlPageElmt::GetLastActivityTime() const
{
    return wstring();
}

wstring DeviantHtmlPageElmt::GetFirstCommonAlbumUrl() const
{
    return wstring();
}

wstring DeviantHtmlPageElmt::GetNextCommonAlbumUrl(const wstring &strCurAlbmUrl)
{
    return wstring();
}

list<wstring> DeviantHtmlPageElmt::GetPicPageUrlsList() const
{
    list<wstring> lstRet;
    return lstRet;
}

list<wstring> DeviantHtmlPageElmt::GetPicPageUrlsListByImageIdOnly() const
{
    list<wstring> lstRet;
    return lstRet;
}

wstring DeviantHtmlPageElmt::GetBestPossibleDirectPicUrl() const
{
    return wstring();
}

wstring DeviantHtmlPageElmt::GetShownInBrowserDirectPicUrl() const
{
    return wstring();
}

// some preprocessing (replace '\n' '\r' to space, replace more than
// one space and tab to just one)
void DeviantHtmlPageElmt::PreprocessPage()
{
}

int DeviantHtmlPageElmt::GetTotalPhotoCount()
{
    if (m_iTotalPhotoCount == -1) {
        m_iTotalPhotoCount = 0;
    }
    return m_iTotalPhotoCount;
}

int DeviantHtmlPageElmt::GetHidePhotoCount()
{
    return 0;
}

int DeviantHtmlPageElmt::GetViewLimitedPhotoCount()
{
    return 0;
}
