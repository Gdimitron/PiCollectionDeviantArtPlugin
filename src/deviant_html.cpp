// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#include "deviant_html.h"
#include <regex>

extern shared_ptr<ISiteInfo> g_SiteInfo;
typedef const wchar_t* cwp;


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



// ============================== main user page ==============================

// <h1><span class="username-with-symbol u"><a class="u regular username"
// href="http://adam-varga.deviantart.com">UserName</a>
static cwp c_rgxUserName = L"<h1>[ ]+<span class=\"username-with-symbol u\">"
                           "[ ]+<a class[^>]+>[ ]+([^ ]+)[ ]+</a>";
wstring DeviantHtmlPageElmt::GetUserName() const
{
    wstring retVal;
    wsmatch match;
    if (regex_search(m_strHtml, match, wregex(c_rgxUserName))
            && match.size() == 2) {
        retVal = match[1].str();
    } else {
        throw parse_ex(L"No or more than one search pattern(:"
                       + to_wstring(__LINE__) + L"): "
                       + wstring(c_rgxUserName), m_strHtml);
    }
    return retVal;
}

// <strong>Last Visit: 2 hours ago</strong>
static cwp c_rgxLastVisit = L"<strong>Last Visit:[ ]*([^<]+)</strong>";
wstring DeviantHtmlPageElmt::GetLastActivityTime() const
{
    wstring retVal;
    wsmatch match;
    if (regex_search(m_strHtml, match, wregex(c_rgxLastVisit))
            && match.size() == 2) {
        retVal = match[1].str();
    } else {
        throw parse_ex(L"No or more than one search pattern(:"
                       + to_wstring(__LINE__) + L"): "
                       + wstring(c_rgxLastVisit), m_strHtml);
    }
    return retVal;
}

wstring DeviantHtmlPageElmt::GetFirstCommonAlbumUrl() const
{
    auto userName = GetUserName();
    wstring retVal = g_SiteInfo->GetProtocol() + userName + L"."
            + g_SiteInfo->GetHostName() + L"/gallery/?catpath=/";
    return retVal;
}

wstring DeviantHtmlPageElmt::GetNextCommonAlbumUrl(const wstring &strCurAlbmUrl,
                                                   int iPicOnPageCnt)
{
    wstring retVal;
    wsmatch match;
    if (regex_search(strCurAlbmUrl, match, wregex(L"&offset=([0-9]+)"))
            && match.size() == 2) {
        int cur_offset = stoi(match[1].str());
        assert(false); // not sure about next line
        retVal = regex_replace(strCurAlbmUrl, wregex(L"&offset=([0-9]+)"),
                               to_wstring(cur_offset + iPicOnPageCnt));

    } else {
        assert(strCurAlbmUrl.find(L"&offset=") == wstring::npos);
        retVal = strCurAlbmUrl + L"&offset=" + to_wstring(iPicOnPageCnt);
    }
    return retVal;
}



// ============================== album page ==============================
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



// ============================== pic page ==============================
// <span class="by">by</span> <span class="username-with-symbol u"> <a class=
// "u regular username" href="http://adam-varga.deviantart.com/">UserName</a>
static cwp c_rgxByUserName = L"<span class=\"by\">[^<]+</span>[ ]*<span "
                             "class=\"username-with-symbol u\">"
                             "[ ]*<a class[^>]+>[ ]*([^ <]+)[ ]*</a>";
wstring DeviantHtmlPageElmt::GetUserIdPicPage() const
{
    wstring retVal;
    wsmatch match;
    if (regex_search(m_strHtml, match, wregex(c_rgxByUserName))
            && match.size() == 2) {
        retVal = match[1].str();
    } else {
        throw parse_ex(L"No or more than one search pattern(:"
                       + to_wstring(__LINE__) + L"): "
                       + wstring(c_rgxByUserName), m_strHtml);
    }
    return retVal;
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
static cwp c_rgxPicCount = L"class=\"tighttt\"[>< ]+strong[> ]+"
                           "([0-9]+)[ </]+strong[ >]+Deviations";
int DeviantHtmlPageElmt::GetTotalPhotoCount()
{
    if (m_iTotalPhotoCount == -1) {
        wsmatch match;
        if (regex_search(m_strHtml, match, wregex(c_rgxPicCount))
                && match.size() == 2) {
            m_iTotalPhotoCount = stoi(match[1].str());
        } else {
            throw parse_ex(L"No or more than one search pattern(:"
                           + to_wstring(__LINE__) + L"): "
                           + wstring(c_rgxPicCount), m_strHtml);
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
