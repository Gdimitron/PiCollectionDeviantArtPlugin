// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#include "deviant_html.h"
#include <regex>

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
    // "Last Visit: 22 minutes ago"
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

// <span class="tighttt"><strong>83 </strong> Deviations</span>
static const wchar_t *c_rgxPicCount = L".*class=\"tighttt\"[>< ]+strong[> ]+"
                                      "([0-9]+)[ </]+strong[ >]+Deviations.*";
int DeviantHtmlPageElmt::GetTotalPhotoCount()
{
    if (m_iTotalPhotoCount == -1) {
        wsmatch match;
        if (regex_match(m_strHtml, match, wregex(c_rgxPicCount))) {
            if (match.size() == 2) {
                m_iTotalPhotoCount = stoi(match[1].str());
            } else {
                throw parse_ex(L"No or more than one search pattern(:"
                               + to_wstring(__LINE__) + L"): "
                               + wstring(c_rgxPicCount), m_strHtml);
            }
        }
    }
    return m_iTotalPhotoCount;
}

// some preprocessing (replace '\n' '\r' to space, replace more than
// one space and tab to just one)
void DeviantHtmlPageElmt::PreprocessPage()
{
    m_strHtml = regex_replace(m_strHtml, wregex(L"[ \t\r\n]+"), L" ");
}
